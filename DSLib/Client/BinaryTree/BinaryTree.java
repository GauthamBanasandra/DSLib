package Client.BinaryTree;

import Lib.Tree.Node;
import Lib.Tree.NodeType;

public class BinaryTree {
    public static void main(String[] args) {
        Lib.BinaryTree.BinaryTree<Integer> binaryTree = new Lib.BinaryTree.BinaryTree<>();
        binaryTree.root = new Node<>(NodeType.ROOT, 3);
        Node<Integer> n1 = new Node<>(NodeType.LEFT_CHILD, 1);
        binaryTree.root.leftChild = n1;
        Node<Integer> n2 = new Node<>(NodeType.RIGHT_CHILD, 2);
        binaryTree.root.rightChild = n2;
        n1.leftChild = new Node<>(NodeType.LEFT_CHILD, 10);
        n1.rightChild = new Node<>(NodeType.RIGHT_CHILD, 18);
        n2.leftChild = new Node<>(NodeType.LEFT_CHILD, 11);
        n2.rightChild = new Node<>(NodeType.RIGHT_CHILD, 8);

        binaryTree.inOrder(n -> System.out.println(n.data));

        System.out.println("Tree height:\t" + binaryTree.height());
    }
}
