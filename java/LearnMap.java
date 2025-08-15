
import java.util.*;

public class LearnMap{
    public static void main(String[] args) {
        Map<Integer, String> mp = new HashMap<>();
        // Map<Integer, String> mp = new TreeMap<>(); -> for sorted order of values


        mp.put(1, "vivek");
        mp.put(2, "kunal");
        mp.put(3, "ragini");

        // check if key id present
        if(mp.containsKey(1)){
            System.out.println("present");
        }

        mp.putIfAbsent(2, "Kumar");

        //interation inize the map
        for(var e: mp.entrySet()){
            System.out.println(e);
            System.out.println(e.getKey());
            System.out.println("value = " + e.getValue());
        }

        // List<Integer> keys = new ArrayList<>(); --> error
        // keys = mp.keySet();
        List<Integer> keys = new ArrayList<>(mp.keySet());
        System.out.println(keys);
        // for(var keys: mp.keySet()){
        //     System.out.println(keys);
        // }

        mp.isEmpty();
        mp.containsKey(3);
        System.out.println(mp.containsValue("vivek"));

        mp.clear();
    }
}