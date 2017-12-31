package Lib.SegmentTree;

public interface AccessCollection<C, T> {
    T access(C collectionCookie, int index);
}
