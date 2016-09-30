import 'abstract_binary_search_tree.dart';

//NOTE: initial skeleton. Not verified and not even sure if this is correct
class RedBlackTreeNode extends BinarySearchTreeNode {
  var color;

  static final String RED = "red";
  static final String BLACK = "black";

  RedBlackTreeNode(var color, var key, RedBlackTreeNode left,
     RedBlackTreeNode right, RedBlackTreeNode parent) : super(key, left, right, parent) {
    this.color = color;
  }

  static RedBlackTreeNode getNilNode() {
    RedBlackTreeNode nil = new RedBlackTreeNode(RedBlackTreeNode.BLACK,
                                  null, null, null, null);
    return nil;
  }

  static bool isNil(RedBlackTreeNode node) {
    return node.color == RedBlackTreeNode.BLACK && node.key == null &&
                            node.left == null && node.right == null && node.parent == null;
  }
}

class RedBlackTree extends AbstractBinarySearchTree{
  RedBlackTreeNode root;
  static final RedBlackTreeNode nil = RedBlackTreeNode.getNilNode();

  RedBlackTree(RedBlackTreeNode root) {
    this.root = root;
  }

  void leftRotate(RedBlackTreeNode x) {
    //Page: 278 Cormen
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
    //Page: 278 Cormen
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
    //Page: 280 Cormen
    super.insert(toInsert);
    toInsert.left = null;
    toInsert.right = null;
    toInsert.color = RedBlackTreeNode.RED;
    insertFixUp(toInsert);
  }

  void insertFixUp(RedBlackTreeNode toInsert) {
    //TODO
  }
}
