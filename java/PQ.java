
import java.util.Comparator;
import java.util.PriorityQueue;

public class PQ{
    public static void main(String[] args) {
        PriorityQueue<Integer> pq = new PriorityQueue<>(); //by default min priority queue
        pq.offer(12);
        pq.offer(19);
        pq.offer(8);
        System.out.println(pq.peek());

        while(pq.peek() != null){
            System.out.println(pq.peek());
            pq.poll();
        }
        // max priority queus
        PriorityQueue<Integer> mxPq = new PriorityQueue<>(Comparator.reverseOrder()); //by default min priority queue
        

    }
}