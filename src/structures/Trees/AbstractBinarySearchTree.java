package structures.Trees;

/**
 * Created by scarecrow on 12/10/16.
 */

class BinarySearchTreeNode {
    int key;
    BinarySearchTreeNode left, right, parent;

    BinarySearchTreeNode(int key, BinarySearchTreeNode left,
                         BinarySearchTreeNode right, BinarySearchTreeNode parent) {
        this.key = key;
        this.left = left;
        this.right = right;
        this.parent = parent;
    }

    boolean isNil() {
        return this.left == null && this.right == null && this.key == 0;
    }
}

public abstract class AbstractBinarySearchTree {
    BinarySearchTreeNode root;

    void insert(BinarySearchTreeNode node) {
        BinarySearchTreeNode y = null;
        BinarySearchTreeNode x = this.root;

        while (y != null) {
            y = x;
            if (node.key < x.key) {
                x = x.left;
            } else {
                x = x.right;
            }
            node.parent = y;

            if (y == null) {
                this.root = node;
            } else if (node.key < y.key) {
                y.left = node;
            } else {
                y.right = node;
            }
        }
    }

    void inOrderWalk(BinarySearchTreeNode node) {
        if (node != null) {
            inOrderWalk(node.left);
            System.out.println(node.key);
            inOrderWalk(node.right);
        }
    }

    void preOrderWalk(BinarySearchTreeNode node) {
        if (node != null) {
            System.out.println(node.key);
            preOrderWalk(node.left);
            preOrderWalk(node.right);
        }
    }

    void postOrderWalk(BinarySearchTreeNode node) {
        if (node != null) {
            postOrderWalk(node.left);
            postOrderWalk(node.right);
            System.out.println(node.key);
        }
    }

    void print() {
        inOrderWalk(this.root);
    }

    BinarySearchTreeNode search(BinarySearchTreeNode node, int key) {
        if (node == null || node.isNil() || node.key == key) {
            return node;
        }
        BinarySearchTreeNode nextNode;
        if (key < node.key) {
            nextNode = node.left;
        } else {
            nextNode = node.right;
        }
        return search(nextNode, key);
    }

    BinarySearchTreeNode search(int key) {
        return search(this.root, key);
    }

    BinarySearchTreeNode min(BinarySearchTreeNode node) {
        if (node != null && node.left!= null) {
            return min(node.left);
        }
        return node;
    }

    BinarySearchTreeNode min() {
        return min(this.root);
    }

    BinarySearchTreeNode max(BinarySearchTreeNode node) {
        if (node != null && node.right != null) {
            return max(node.right);
        }
        return node;
    }

    BinarySearchTreeNode max() {
        return max(this.root);
    }

    BinarySearchTreeNode successor(BinarySearchTreeNode node) {
        if (node != null && node.right != null) {
            return min(node.right);
        }
        BinarySearchTreeNode parent = node.parent;
        while (parent != null && !parent.isNil() && node == parent.right) {
            node = parent;
            parent = parent.parent;
        }
        return parent;
    }
}