class BinarySearchTreeNode {
  var key;
  BinarySearchTreeNode left, right, parent;

  BinarySearchTreeNode(var key, BinarySearchTreeNode left,
    BinarySearchTreeNode right, BinarySearchTreeNode parent) {
    this.key = key;
    this.left = left;
    this.right = right;
    this.parent = parent;
  }
}

abstract class AbstractBinarySearchTree {
  BinarySearchTreeNode root;
}
