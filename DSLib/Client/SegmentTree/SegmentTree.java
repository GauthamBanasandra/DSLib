package Client.SegmentTree;

import java.util.Vector;

public class SegmentTree {
    public static void main(String[] args) {
        Vector<Integer> numbers = new Vector<>();
        numbers.add(1);
        numbers.add(11);
        numbers.add(15);
        numbers.add(95);
        numbers.add(2);

        Lib.SegmentTree.SegmentTree segTree = new Lib.SegmentTree.SegmentTree(numbers, numbers.size(),
                (collectionCookie, index) -> {
                    Vector<Integer> collection = (Vector<Integer>) collectionCookie;
                    return collection.get(index);
                },
                (d1, d2) -> {
                    Integer p1 = (Integer) d1;
                    Integer p2 = (Integer) d2;
                    return p1 <= p2 ? p1 : p2;
                });

        segTree.preOrder(n -> System.out.println(n.data));
    }
}