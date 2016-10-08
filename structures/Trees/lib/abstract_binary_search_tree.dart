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

  void insert(BinarySearchTreeNode toInsert) {
    BinarySearchTreeNode y = null;
    BinarySearchTreeNode x = this.root;

    while (y != null) {
      y = x;
      if (toInsert.key < x.key) {
        x = x.left;
      } else {
        x = x.right;
      }
      toInsert.parent = y;

      if (y == null) {
        this.root = toInsert;
      } else if (toInsert.key < y.key) {
        y.left = toInsert;
      } else {
        y.right = toInsert;
      }
    }
  }
}
