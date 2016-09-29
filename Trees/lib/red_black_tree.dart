import 'abstract_binary_search_tree.dart';

//NOTE: initial skeleton. Not verified and not even sure if this is correct
class RedBlackTreeNode extends BinarySearchTreeNode {
  var color;

  RedBlackTreeNode(var color, var key, RedBlackTreeNode left,
     RedBlackTreeNode right, RedBlackTreeNode parent) : super(key, left, right, parent) {
    this.color = color;
  }
}

class RedBlackTree extends AbstractBinarySearchTree{
  RedBlackTreeNode root;
  static final String RED = "red";
  static final String BLACK = "black";

  RedBlackTree(RedBlackTreeNode root) {
    this.root = root;
  }

  void leftRotate(RedBlackTreeNode x) {
    RedBlackTreeNode y = x.right;
    x.right = y.left;
    y.left.parent = x;
    y.parent = x.parent;
    if(x.parent == null) {
      root = y;
    } else if (x == x.parent.left) {
      x.parent.left = y;
    } else if (x == x.parent.right) {
      x.parent.right = y;
    }
    y.left = x;
    x.parent = y;
  }

  void rightRotate(RedBlackTreeNode x) {
    RedBlackTreeNode y = x.left;
    x.left = y.right;
    y.right.parent = x;
    y.parent = x.parent;
    if (x.parent == null) {
      root = y;
    } else if (x == x.parent.right) {
      x.parent.right = y;
    } else {
      x.parent.left = y;
    }
    y.right = x;
    x.parent = y;
  }

  void insert(RedBlackTreeNode toInsert) {
    toInsert.left = null;
    toInsert.right = null;
    toInsert.color = RED;
    insertFixUp(toInsert);
  }

  void insertFixUp(RedBlackTreeNode toInsert) {
    //TODOps
  }
}
