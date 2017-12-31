package Lib.SegmentTree;

import Lib.BinaryTree.BinaryTree;
import Lib.Tree.Node;
import Lib.Tree.NodeType;

import java.util.HashMap;

public class SegmentTree<T> extends BinaryTree<T> {
    public SegmentTree(Object collectionCookie, int size, AccessCollection<T> accessCollection, MergeNodes<T> mergeNodes) {
        this.collectionCookie = collectionCookie;
        this.size = size;
        this.accessCollection = accessCollection;
        this.mergeNodes = mergeNodes;
        lazyStore = new HashMap<>();

        Range segment = new Range(0, size - 1);
        super.root = buildTree(NodeType.ROOT, segment);
    }

    public Response<T> query(Range querySegment) {
        Range segment = new Range(0, size - 1);
        return query(super.root, segment, querySegment);
    }

    private Response<T> query(Node<T> n, Range segment, Range querySegment) {
        if ((querySegment.lowerBound > segment.upperBound) || (querySegment.upperBound < segment.lowerBound)) {
            return new Response<>(false, null);
        }

        if (lazyStore.containsKey(n)) {
            T lazyData = lazyStore.get(n);
            n.data = mergeNodes.merge(n.data, lazyData);
            propagateLaziness(n, lazyData);
            lazyStore.remove(n);
        }

        if ((segment.lowerBound >= querySegment.lowerBound) && (segment.upperBound <= querySegment.upperBound)) {
            return new Response<>(true, n.data);
        }

        Range leftSegment = new Range(segment.lowerBound, (segment.lowerBound + segment.upperBound) >> 1);
        Response<T> leftResponse = query(n.leftChild, leftSegment, querySegment);

        Range rightSegment = new Range(leftSegment.upperBound + 1, segment.upperBound);
        Response<T> rightResponse = query(n.rightChild, rightSegment, querySegment);

        if (!leftResponse.isValid) {
            return rightResponse;
        }

        if (!rightResponse.isValid) {
            return leftResponse;
        }

        return new Response<>(true, mergeNodes.merge(leftResponse.data, rightResponse.data));
    }

    private void propagateLaziness(Node<T> n, T data) {
        if (n.leftChild != null && n.rightChild != null) {
            return;
        }

        if (lazyStore.containsKey(n.leftChild)) {
            T lazyData = lazyStore.get(n.leftChild);
            lazyStore.put(n.leftChild, mergeNodes.merge(lazyData, data));
        } else {
            lazyStore.put(n.leftChild, data);
        }

        if (lazyStore.containsKey(n.rightChild)) {
            T lazyData = lazyStore.get(n.rightChild);
            lazyStore.put(n.rightChild, mergeNodes.merge(lazyData, data));
        } else {
            lazyStore.put(n.rightChild, data);
        }
    }

    private Node<T> buildTree(NodeType type, Range segment) {
        if (segment.lowerBound == segment.upperBound) {
            return new Node<>(accessCollection.access(collectionCookie, segment.lowerBound), type);
        }

        Range leftSegment = new Range(segment.lowerBound, (segment.lowerBound + segment.upperBound) >> 1);
        Node<T> leftChild = buildTree(NodeType.LEFT_CHILD, leftSegment);

        Range rightSegment = new Range(leftSegment.upperBound + 1, segment.upperBound);
        Node<T> rightChild = buildTree(NodeType.RIGHT_CHILD, rightSegment);

        Node<T> parent = new Node<>(mergeNodes.merge(leftChild.data, rightChild.data), type);
        parent.leftChild = leftChild;
        parent.rightChild = rightChild;
        leftChild.ancestor = rightChild.ancestor = parent;
        return parent;
    }

    public Object collectionCookie;
    public int size;
    public MergeNodes<T> mergeNodes;
    public AccessCollection<T> accessCollection;

    private HashMap<Node<T>, T> lazyStore;
}
