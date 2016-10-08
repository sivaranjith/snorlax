package structures;

public class Queue {

  private class Node {
    Node next;
    int item;
  }

  private Node first, last;

  public void enqueue(int u) {
    Node oldLast = this.last;
    this.last = new Node();
    this.last.item = u;
    this.last.next = null;
    if (isEmpty()) {
      this.first =  this.last;
    } else {
      oldLast.next = this.last;
    }
  }

  public int dequeue() {
    int item = this.first.item;
    this.first = this.first.next;
    if (isEmpty()) {
      this.last = null;
    }
    return item;
  }

  public boolean isEmpty() {
    return this.first == this.last;
  }
}
