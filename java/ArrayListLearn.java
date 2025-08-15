import java.util.*;
public class ArrayListLearn{
    public static void main(String[] args){
        ArrayList<Integer> list = new ArrayList<>();

        list.add(10);
        list.add(20);
        list.add(30);
        list.add(40);
        list.add(50);
        list.add(60);
        list.add(70);
        list.add(80);
        list.add(90);
        list.add(100);
        list.add(110);
        list.add(120);

        System.out.println(list);

        list.set(2, 22);

        System.out.println(list);

        System.out.println(list.get(3));

        list.remove(9);

        System.out.println(list);

        //check 50 is present in the lsit
        System.out.println(list.contains(50));

        //iteration of list;
        // list.size() -> number of elements
        for(int i =0; i < list.size(); i++){
            System.out.println(list.get(i));
        }
        // using for each loop
        System.out.println("Print using for each loop");
        for(var element: list){
            System.out.println(element);
        }

        //using iterator
        Iterator<Integer> it = list.iterator();

        while(it.hasNext()){
            System.out.println("Value at iterator = " + it.next());
        }

    }
}