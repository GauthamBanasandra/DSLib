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

        Lib.SegmentTree.SegmentTree<Vector<Integer>, Integer> segTree = new Lib.SegmentTree.SegmentTree<>(numbers, numbers.size(),
                Vector::get,
                (d1, d2) -> d1 <= d2 ? d1 : d2);

        segTree.preOrder(n -> System.out.println(n.data));
    }
}