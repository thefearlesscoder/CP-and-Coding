
import java.util.*;

public class LearnSet{
    public static void main(String[] args) {
        // Set<Integer> st = new HashSet<>();
        Set<Integer> st = new TreeSet<>();
        // elementsin sorted form in form of BST

        st.add(22);
        st.add(2);
        st.add(5);
        st.add(5);

        System.out.println(st);
        st.remove(5);

        

        System.out.println(st.contains(22));
        System.out.println(st.isEmpty());

        System.out.println(st.size());

        st.clear();
        System.out.println(st);
    }
}