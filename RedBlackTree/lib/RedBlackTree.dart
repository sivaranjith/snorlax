//NOTE: initial skeleton. Not verified and not even sure if this is correct
class RedBlackTreeNode {
  var data;
  RedBlackTreeNode left, right, parent;
}

class RedBlackTree {
  RedBlackTreeNode root;

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
}
