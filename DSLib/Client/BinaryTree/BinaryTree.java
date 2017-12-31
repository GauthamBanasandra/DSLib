package Client.BinaryTree;

import Lib.Tree.Node;
import Lib.Tree.NodeType;

public class BinaryTree {
    public static void main(String[] args) {
        Lib.BinaryTree.BinaryTree<Integer> binaryTree = new Lib.BinaryTree.BinaryTree<>();
        binaryTree.root = new Node<>(3, NodeType.ROOT);
        Node<Integer> n1 = new Node<>(1, NodeType.LEFT_CHILD);
        binaryTree.root.leftChild = n1;
        Node<Integer> n2 = new Node<>(2, NodeType.RIGHT_CHILD);
        binaryTree.root.rightChild = n2;
        n1.leftChild = new Node<>(10, NodeType.LEFT_CHILD);
        n1.rightChild = new Node<>(18, NodeType.RIGHT_CHILD);
        n2.leftChild = new Node<>(11, NodeType.LEFT_CHILD);
        n2.rightChild = new Node<>(8, NodeType.RIGHT_CHILD);

        binaryTree.inOrder(n -> System.out.println(n.data));

        System.out.println("Tree height:\t" + binaryTree.height());
    }
}
