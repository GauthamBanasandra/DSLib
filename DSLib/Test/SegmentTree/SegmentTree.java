package SegmentTree;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.util.HashMap;
import java.util.Map;
import java.util.Random;

class SegmentTree {
    private HashMap<Integer, Integer> data;
    private static final int dataSize = 100000;

    @BeforeEach
    void setUp() {
        data = new HashMap<>();
        Random random = new Random();
        for (int i = 0; i < dataSize; i++) {
            data.put(random.nextInt(), random.nextInt());
        }
    }

    @Test
    void benchmarkBuildTree() {
        Lib.SegmentTree.SegmentTree<HashMap<Integer, Integer>> segTree = new Lib.SegmentTree.SegmentTree(data, data.size(),
                (collectionCookie, index) -> {
                    HashMap<Integer, Integer> collection = (HashMap<Integer, Integer>) collectionCookie;
                    HashMap<Integer, Integer> f = new HashMap<>();
                    f.put(collection.get(index), 1);
                    return f;
                },
                (d1, d2) -> {
                    HashMap<Integer, Integer> p1 = (HashMap<Integer, Integer>) d1;
                    HashMap<Integer, Integer> p2 = (HashMap<Integer, Integer>) d2;

                    HashMap<Integer, Integer> f = new HashMap<>();
                    for (Map.Entry<Integer, Integer> entry : p1.entrySet()) {
                        f.put(entry.getKey(), entry.getValue());
                    }

                    for (Map.Entry<Integer, Integer> entry : p2.entrySet()) {
                        Integer key = entry.getKey();
                        f.put(key, f.getOrDefault(key, 0) + entry.getValue());
                    }

                    return f;
                });
    }
}
