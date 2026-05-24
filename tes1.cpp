struct Delivery {
        string id;
        double x, y, weight, deadline;
    };

    struct NFZ {
        string shape;
        double cx, cy, radius;
        double rx1, ry1, rx2, ry2;
        double T_start, T_end;
    };

    struct DroneState {
        string id;
        double max_payload;
        double t_avail;
        Json::Value path;
    };

    // 1. Parse Deliveries
    vector<Delivery> delivs;
    delivs.reserve(deliveries.size());
    for (const auto& d : deliveries) {
        delivs.push_back({
            d["id"].asString(),
            d["x"].asDouble(), d["y"].asDouble(),
            d["weight"].asDouble(), d["deadline"].asDouble()
        });
    }

    // Sort deliveries by earliest deadline
    sort(delivs.begin(), delivs.end(), [](const Delivery& a, const Delivery& b) {
        return a.deadline < b.deadline;
    });

    // 2. Parse NFZs
    vector<NFZ> nfz_list;
    nfz_list.reserve(no_fly_zones.size());
    for (const auto& n : no_fly_zones) {
        NFZ nz;
        nz.shape = n["shape"].asString();
        nz.T_start = n["T_start"].asDouble();
        nz.T_end = n["T_end"].asDouble();
        if (nz.shape == "circle") {
            nz.cx = n["center"][0].asDouble();
            nz.cy = n["center"][1].asDouble();
            nz.radius = n["radius"].asDouble();
        } else {
            nz.rx1 = n["corners"][0][0].asDouble();
            nz.ry1 = n["corners"][0][1].asDouble();
            nz.rx2 = n["corners"][1][0].asDouble();
            nz.ry2 = n["corners"][1][1].asDouble();
        }
        nfz_list.push_back(nz);
    }

    // 3. Initialize Drones
    vector<DroneState> drone_states;
    drone_states.reserve(drones.size());
    for (const auto& d : drones) {
        DroneState ds;
        ds.id = d["id"].asString();
        ds.max_payload = d["max_payload"].asDouble();
        ds.t_avail = 0.0;
        ds.path = Json::arrayValue;
        drone_states.push_back(ds);
    }

    // 4. O(1) Mathematical Collision Detection
    auto check_path = [&](double start_x, double start_y, double start_t, double end_x, double end_y, double& block_end_time) {
        double dx = end_x - start_x;
        double dy = end_y - start_y;
        double L = hypot(dx, dy);

        for (const auto& nfz : nfz_list) {
            double s_in = 0.0, s_out = 1.0;
            bool hit = false;

            if (nfz.shape == "circle") {
                double fx = start_x - nfz.cx;
                double fy = start_y - nfz.cy;
                double A = L * L;
                double B = 2 * (fx * dx + fy * dy);
                double C = fx * fx + fy * fy - nfz.radius * nfz.radius;
                
                if (A < 1e-9) { 
                    if (C <= 0) { hit = true; s_in = 0.0; s_out = 1.0; }
                } else {
                    double discriminant = B * B - 4 * A * C;
                    if (discriminant >= 0) {
                        double sqrt_d = sqrt(discriminant);
                        double s1 = (-B - sqrt_d) / (2 * A);
                        double s2 = (-B + sqrt_d) / (2 * A);
                        s_in = max(0.0, min(s1, s2));
                        s_out = min(1.0, max(s1, s2));
                        if (s_in <= s_out) hit = true; 
                    }
                }
            } else if (nfz.shape == "rectangle") {
                auto update_s = [&](double p, double q, double& sin, double& sout) {
                    if (abs(p) < 1e-9) {
                        if (q < 0) return false;
                    } else {
                        double r = q / p;
                        if (p > 0) sout = min(sout, r);
                        else sin = max(sin, r);
                    }
                    return sin <= sout;
                };
                
                double s1 = 0.0, s2 = 1.0;
                if (update_s(-dx, start_x - nfz.rx1, s1, s2) &&
                    update_s(dx, nfz.rx2 - start_x, s1, s2) &&
                    update_s(-dy, start_y - nfz.ry1, s1, s2) &&
                    update_s(dy, nfz.ry2 - start_y, s1, s2)) {
                    hit = true;
                    s_in = s1;
                    s_out = s2;
                }
            }

            if (hit) {
                double t_in = start_t + s_in * L;
                double t_out = start_t + s_out * L;
                if (max(t_in, nfz.T_start) <= min(t_out, nfz.T_end) + 1e-7) {
                    block_end_time = nfz.T_end;
                    return false;
                }
            }
        }
        return true;
    };

    // 5. Charging Station Route Generator & Evaluator
    struct Stop {
        double x, y;
        int type; // 0=DELIVERY, 1=STATION, 2=WAREHOUSE
        string id;
    };

    auto evaluate_route = [&](const vector<Stop>& sequence, double start_t, const Delivery& deliv, Json::Value& out_path) {
        double current_t = start_t;
        double battery = 500.0;
        double cx = warehouseX, cy = warehouseY;
        bool carried = true;
        
        Json::Value path(Json::arrayValue);
        
        Json::Value pickup;
        pickup["x"] = cx; pickup["y"] = cy; pickup["t"] = current_t;
        pickup["action"] = "PICKUP";
        Json::Value d_ids(Json::arrayValue); d_ids.append(deliv.id);
        pickup["delivery_ids"] = d_ids;
        path.append(pickup);
        
        for (size_t i = 0; i < sequence.size(); ++i) {
            const auto& stop = sequence[i];
            
            double block_end = 0.0;
            double wait_start_t = current_t;
            while (!check_path(cx, cy, current_t, stop.x, stop.y, block_end)) {
                current_t = block_end + 1e-5;
            }
            
            if (current_t > wait_start_t + 1e-4) {
                Json::Value wait_act;
                wait_act["x"] = cx; wait_act["y"] = cy; wait_act["t"] = wait_start_t;
                wait_act["action"] = "WAIT";
                path.append(wait_act);
            }
            
            double dist = hypot(stop.x - cx, stop.y - cy);
            double energy_cost = dist * (carried ? (1.0 + deliv.weight) : 1.0);
            
            if (battery < energy_cost) return -1.0; // Fail: Battery depleted
            
            double arr_t = current_t + dist;
            battery -= energy_cost;
            
            if (stop.type == 0) { // DELIVERY
                if (arr_t > deliv.deadline) return -1.0; 
                Json::Value deliver;
                deliver["x"] = stop.x; deliver["y"] = stop.y; deliver["t"] = arr_t;
                deliver["action"] = "DELIVER"; deliver["delivery_id"] = stop.id;
                path.append(deliver);
                carried = false;
                current_t = arr_t;
            } 
            else if (stop.type == 1) { // STATION
                Json::Value charge;
                charge["x"] = stop.x; charge["y"] = stop.y; charge["t"] = arr_t;
                charge["action"] = "CHARGE";
                path.append(charge);
                
                // Calculate minimum energy needed to reach the next safe harbor (Station or Warehouse)
                double needed_energy = 0;
                double sim_x = stop.x, sim_y = stop.y;
                bool sim_carried = carried;
                for (size_t j = i + 1; j < sequence.size(); ++j) {
                    double d = hypot(sequence[j].x - sim_x, sequence[j].y - sim_y);
                    needed_energy += d * (sim_carried ? (1.0 + deliv.weight) : 1.0);
                    sim_x = sequence[j].x; sim_y = sequence[j].y;
                    if (sequence[j].type == 0) sim_carried = false;
                    if (sequence[j].type == 1 || sequence[j].type == 2) break;
                }
                
                if (needed_energy > 500.0) return -1.0; // Impossible distance
                
                double charge_amt = max(0.0, needed_energy - battery);
                double charge_time = charge_amt / 2.0; // Charge rate is 2 units/timestep
                
                battery += charge_amt;
                current_t = arr_t + charge_time;
                
                Json::Value charge_comp;
                charge_comp["x"] = stop.x; charge_comp["y"] = stop.y; charge_comp["t"] = current_t;
                charge_comp["action"] = "CHARGE_COMPLETE";
                path.append(charge_comp);
            }
            else if (stop.type == 2) { // WAREHOUSE
                Json::Value ret;
                ret["x"] = stop.x; ret["y"] = stop.y; ret["t"] = arr_t;
                ret["action"] = "RETURN";
                path.append(ret);
                current_t = arr_t;
            }
            
            cx = stop.x; cy = stop.y;
        }
        
        out_path = path;
        return current_t;
    };

    // Generate all viable sequence permutations 
    auto generate_sequences = [&](const Delivery& d) {
        vector<vector<Stop>> seqs;
        Stop deliv_stop = {d.x, d.y, 0, d.id};
        Stop return_stop = {warehouseX, warehouseY, 2, ""};
        
        seqs.push_back({deliv_stop, return_stop}); // 1. Direct
        
        vector<Stop> stats;
        for (const auto& s : charging_stations) {
            stats.push_back({s["x"].asDouble(), s["y"].asDouble(), 1, ""});
        }
        
        // 2. Detour via 1 Station (Either Outbound or Inbound)
        for (auto& s : stats) {
            seqs.push_back({s, deliv_stop, return_stop});
            seqs.push_back({deliv_stop, s, return_stop});
        }
        
        // 3. Detour via 2 Stations (Outbound and Inbound)
        for (auto& s1 : stats) {
            for (auto& s2 : stats) {
                seqs.push_back({s1, deliv_stop, s2, return_stop});
            }
        }
        return seqs;
    };

    // 6. Optimal Assignment with Charging capabilities
    for (const auto& deliv : delivs) {
        int best_drone_idx = -1;
        double best_return_time = 1e18;
        Json::Value best_path;
        
        vector<vector<Stop>> candidate_seqs = generate_sequences(deliv);
        
        for (size_t i = 0; i < drone_states.size(); ++i) {
            if (drone_states[i].max_payload < deliv.weight) continue;
            
            double d_start_t = drone_states[i].t_avail;
            
            for (const auto& seq : candidate_seqs) {
                Json::Value path_out;
                double return_time = evaluate_route(seq, d_start_t, deliv, path_out);
                
                // Track the route that gets the drone back to the warehouse the earliest
                if (return_time >= 0 && return_time < best_return_time) {
                    best_return_time = return_time;
                    best_drone_idx = i;
                    best_path = path_out;
                }
            }
        }
        
        if (best_drone_idx != -1) {
            for (const auto& action : best_path) {
                drone_states[best_drone_idx].path.append(action);
            }
            drone_states[best_drone_idx].t_avail = best_return_time;
        }
    }

    // 7. Build Final Output
    for (const auto& d : drone_states) {
        if (!d.path.empty()) {
            Json::Value drone_manifest;
            drone_manifest["drone_id"] = d.id;
            drone_manifest["path"] = d.path;
            flight_manifest.append(drone_manifest);
        }
    }