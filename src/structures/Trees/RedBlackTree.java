package structures.Trees;

/**
 * Created by scarecrow on 12/10/16.
 */

enum RedBlackColor{
    RED, BLACK;
}

class RedBlackTreeNode extends BinarySearchTreeNode {
    RedBlackColor color;

    RedBlackTreeNode(RedBlackColor color, int key, RedBlackTreeNode left,
                     RedBlackTreeNode right, RedBlackTreeNode parent) {
        super(key, left, right, parent);
        this.color = color;
    }

    static RedBlackTreeNode getNilNode() {
        RedBlackTreeNode nil = new RedBlackTreeNode(RedBlackColor.BLACK, 0, null, null, null);
        return nil;
    }

    boolean isNil() {
        return this.color == RedBlackColor.BLACK && this.key == 0 && this.left == null &&
                                    this.right == null && this.parent == null;
    }

    boolean isRed() {
        return this.color == RedBlackColor.RED;
    }

    boolean isBlack() {
        return this.color == RedBlackColor.BLACK;
    }
}
public class RedBlackTree extends AbstractBinarySearchTree{
    RedBlackTreeNode root;
    static final RedBlackTreeNode NIL = RedBlackTreeNode.getNilNode();

    RedBlackTree (RedBlackTreeNode root) {
        this.root = root;
    }

    void leftRotate (RedBlackTreeNode node) {
        //TODO
    }
}
