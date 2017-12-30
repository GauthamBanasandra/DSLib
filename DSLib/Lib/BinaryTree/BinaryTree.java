package Lib.BinaryTree;

import Lib.Tree.Node;

public class BinaryTree<T> {
    public BinaryTree() {
        this.root = null;
    }

    // A utility function to get the height of the node
    public long height() {
        return height(root);
    }

    public static <U> long height(Node<U> n) {
        if (n == null) {
            return 0L;
        }

        long leftChildHeight = height(n.leftChild);
        long rightChildHeight = height(n.rightChild);
        return Math.max(leftChildHeight, rightChildHeight) + 1L;
    }

    // Traversal methods with visitAction as a lambda
    public void preOrder(VisitAction<T> visitAction) {
        preOrder(root, visitAction);
    }

    public void postOrder(VisitAction<T> visitAction) {
        postOrder(root, visitAction);
    }

    public void inOrder(VisitAction<T> visitAction) {
        inOrder(root, visitAction);
    }

    private void preOrder(Node<T> n, VisitAction<T> visitAction) {
        if (n == null) {
            return;
        }

        visitAction.visit(n);
        preOrder(n.leftChild, visitAction);
        preOrder(n.rightChild, visitAction);
    }

    private void postOrder(Node<T> n, VisitAction<T> visitAction) {
        if (n == null) {
            return;
        }

        postOrder(n.leftChild, visitAction);
        postOrder(n.rightChild, visitAction);
        visitAction.visit(n);
    }

    private void inOrder(Node<T> n, VisitAction<T> visitAction) {
        if (n == null) {
            return;
        }

        inOrder(n.leftChild, visitAction);
        visitAction.visit(n);
        inOrder(n.rightChild, visitAction);
    }

    // TODO : Add replace method to replace a node in the tree
    public Node<T> root;
}

