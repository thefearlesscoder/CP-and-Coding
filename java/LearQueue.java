
import java.util.LinkedList;
import java.util.Queue;

public class LearQueue{
    public static void main(String[] args) {
        Queue<Integer> q = new LinkedList<>();
        // qeueu is implemted ising LinkedLis
        q.offer(12); // push elements in the queue
        q.offer(13);
        q.offer(14);

        System.out.println(q);
        System.out.println(q.peek());
        System.out.println(q.poll()); // q.front in c++; + q.pop bhi ho jata hai
        System.out.println(q);

    }
}