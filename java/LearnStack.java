
import java.util.Stack;

public class LearnStack{
    public static void main(String[] args) {
        Stack<String> st = new Stack<>();

        st.push("Vivek");
        st.push("pandey");
        st.push("neesha");
        st.push("hulk");

        System.out.println("peek elemenr" + st.peek());

        st.pop();

        System.out.println("Print the elementsof the stack");

        for(var ele: st){
            System.out.println(ele);
        }

    }
}