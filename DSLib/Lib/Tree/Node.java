package Lib.Tree;

public class Node<T> {
    public Node(NodeType type, T data) {
        this.type = type;
        this.data = data;
    }

    public void remove(Node<T> n) {
        n.leftChild = n.rightChild = null;
        Node<T> ancestor = n.ancestor;
        switch (n.type) {
            case LEFT_CHILD:
                ancestor.leftChild = null;
                break;

            case RIGHT_CHILD:
                ancestor.rightChild = null;
                break;

            case ROOT:
                break;

            default:
                // Unhandled node type
                assert false;
        }
    }

    public NodeType type;
    public Node<T> ancestor;
    public Node<T> leftChild;
    public Node<T> rightChild;
    public long height;
    public T data;
}
