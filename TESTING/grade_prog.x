

struct grade_request {
    int auth_token;
    int student_id;
    int encrypted_score;
};

program GRADE_PROG {
    version GRADE_VERSION {
        char CALCULATE_GRADE(grade_request) = 1; 
    } = 1;
} = 0x20000002;