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

  public bool isNil() {
    return this.left == null && this.right == null && this.key == null;
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

  void inOrderWalk() {
    if (this.root != null) {
      if (this.root.left != null) {
        this.root.left.inOrderWalk();
      }
      //print this.root.key
      if (this.root.right != null) {
        this.root.right.inOrderWalk();
      }
    }
  }

  void preOrderWalk() {
    if (this.root != null) {
      //print this.root.key
      if (this.root.left != null) {
        this.root.left.preOrderWalk();
      }
      if (this.root.right != null) {
        this.root.right.preOrderWalk();
      }
    }
  }

  void postOrderWalk() {
    if (this.root != null) {
      if (this.root.left != null) {
        this.root.left.postOrderWalk();
      }
      if (this.root.right != null) {
        this.root.right.postOrderWalk();
      }
      //print this.root.key
    }
  }

  void print() {
    inOrderWalk();
  }

  var search(var key) {
    if (this.root.isNil() || this.key == key) {
      return this.root;
    }
    if (k < this.key) {
      return this.root.left.search(key);
    } else {
      return this.root.right.search(key);
    }
  }

  var min() {
    if (!this.root.left.isNil()) {
      return this.root.left.min();
    }
    return this.root;
  }

  var max() {
    if (!this.root.right.isNil()) {
      return this.root.right.max();
    }
    return this.root;
  }

  static var successor(BinarySearchTreeNode x) {
    if (!x.right.isNil()) {
      return x.right.min();s
    }
    var y = x.parent;
    while (!y.isNil() && x == y.right) {
      x = y;
      y = y.parent;
    }
    return y;
  }
}
