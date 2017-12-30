package Lib.BinaryTree;

import Lib.Tree.Node;

public interface VisitAction<T> {
   void visit(Node<T> n);
}
