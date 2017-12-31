package SegmentTree;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.util.HashMap;
import java.util.Map;
import java.util.Random;
import java.util.Vector;

class SegmentTree {
    private Vector<Integer> data;
    private static final int dataSize = 100000;

    @BeforeEach
    void setUp() {
        data = new Vector<>();
        Random random = new Random();
        for (int i = 0; i < dataSize; i++) {
            data.add(random.nextInt());
        }
    }

    @Test
    void benchmarkBuildTree() {
        new Lib.SegmentTree.SegmentTree<>(data, data.size(),
                (collection, index) -> {
                    HashMap<Integer, Integer> f = new HashMap<>();
                    f.put(collection.get(index), 1);
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
