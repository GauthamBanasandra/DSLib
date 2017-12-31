package SegmentTree;

import Lib.SegmentTree.Range;
import Lib.SegmentTree.Response;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

import java.util.HashMap;
import java.util.Map;
import java.util.Random;

class SegmentTreeGold {         // the segment tree is stored like a heap array
    private int[] st, A;
    private int n;

    private int left(int p) {
        return p << 1;
    } // same as binary heap operations

    private int right(int p) {
        return (p << 1) + 1;
    }

    private void build(int p, int L, int R) {
        if (L == R)                            // as L == R, either one is fine
            st[p] = L;                                         // store the index
        else {                                // recursively compute the values
            build(left(p), L, (L + R) / 2);
            build(right(p), (L + R) / 2 + 1, R);
            int p1 = st[left(p)], p2 = st[right(p)];
            st[p] = (A[p1] <= A[p2]) ? p1 : p2;
        }
    }

    private int rmq(int p, int L, int R, int i, int j) {          // O(log n)
        if (i > R || j < L) return -1; // current segment outside query range
        if (L >= i && R <= j) return st[p];               // inside query range

        // compute the min position in the left and right part of the interval
        int p1 = rmq(left(p), L, (L + R) / 2, i, j);
        int p2 = rmq(right(p), (L + R) / 2 + 1, R, i, j);

        if (p1 == -1) return p2;   // if we try to access segment outside query
        if (p2 == -1) return p1;                               // same as above
        return (A[p1] <= A[p2]) ? p1 : p2;
    }          // as as in build routine

    private int update_point(int p, int L, int R, int idx, int new_value) {
        // this update code is still preliminary, i == j
        // must be able to update range in the future!
        int i = idx, j = idx;

        // if the current interval does not intersect
        // the update interval, return this st node value!
        if (i > R || j < L)
            return st[p];

        // if the current interval is included in the update range,
        // update that st[node]
        if (L == i && R == j) {
            A[i] = new_value; // update the underlying array
            return st[p] = L; // this index
        }

        // compute the minimum position in the
        // left and right part of the interval
        int p1, p2;
        p1 = update_point(left(p), L, (L + R) / 2, idx, new_value);
        p2 = update_point(right(p), (L + R) / 2 + 1, R, idx, new_value);

        // return the position where the overall minimum is
        return st[p] = (A[p1] <= A[p2]) ? p1 : p2;
    }

    public SegmentTreeGold(int[] _A) {
        A = _A;
        n = A.length;                   // copy content for local usage
        st = new int[4 * n];
        for (int i = 0; i < 4 * n; i++) st[i] = 0; // create vector with length `len' and fill it with zeroes
        build(1, 0, n - 1);                                  // recursive build
    }

    public int rmq(int i, int j) {
        return rmq(1, 0, n - 1, i, j);
    } // overloading

    public int update_point(int idx, int new_value) {
        return update_point(1, 0, n - 1, idx, new_value);
    }
}

class SegmentTree {
    private int[] generateData(int dataSize) {
        int[] data = new int[dataSize];
        Random random = new Random();
        for (int i = 0; i < dataSize; i++) {
            data[i] = random.nextInt();
        }

        return data;
    }

    private void extensiveQuery(int[] data, Lib.SegmentTree.SegmentTree<int[], Integer> segTree, SegmentTreeGold segTreeGold) {
        for (int i = 0; i < data.length; i++) {
            for (int j = i; j < data.length; j++) {
                Range querySegment = new Range(i, j);
                int expected = data[segTreeGold.rmq(i, j)];
                Response<Integer> actual = segTree.query(querySegment);

//                System.out.printf("Expected: %d\tActual: %d\n", expected, actual.data);
                Assertions.assertEquals(true, actual.isValid, "Query must be valid");
                Assertions.assertEquals(expected, actual.data.intValue());
            }
        }
    }

    @Test
    void queryTest() {
        int[] data = new int[7];
        data[0] = 18;
        data[1] = 17;
        data[2] = 13;
        data[3] = 19;
        data[4] = 15;
        data[5] = 11;
        data[6] = 20;

        SegmentTreeGold segTreeGold = new SegmentTreeGold(data);
        Lib.SegmentTree.SegmentTree<int[], Integer> segTree = new Lib.SegmentTree.SegmentTree<>(data, data.length,
                ((collectionCookie, index) -> collectionCookie[index]), ((d1, d2) -> d1 <= d2 ? d1 : d2));

        extensiveQuery(data, segTree, segTreeGold);
    }

    @Test
    void randomQueryTest() {
        int[] data = generateData(1000);
        SegmentTreeGold segTreeGold = new SegmentTreeGold(data);
        Lib.SegmentTree.SegmentTree<int[], Integer> segTree = new Lib.SegmentTree.SegmentTree<>(data, data.length,
                ((collectionCookie, index) -> collectionCookie[index]), ((d1, d2) -> d1 <= d2 ? d1 : d2));

        extensiveQuery(data, segTree, segTreeGold);
    }

    @Test
    void benchmarkBuildTree() {
        int[] data = generateData(100000);
        new Lib.SegmentTree.SegmentTree<>(data, data.length,
                (collection, index) -> {
                    HashMap<Integer, Integer> f = new HashMap<>();
                    f.put(collection[index], 1);
                    return f;
                },
                (d1, d2) -> {
                    HashMap<Integer, Integer> f = new HashMap<>();
                    for (Map.Entry<Integer, Integer> entry : d1.entrySet()) {
                        f.put(entry.getKey(), entry.getValue());
                    }

                    for (Map.Entry<Integer, Integer> entry : d2.entrySet()) {
                        Integer key = entry.getKey();
                        f.put(key, f.getOrDefault(key, 0) + entry.getValue());
                    }

                    return f;
                });
    }
}
