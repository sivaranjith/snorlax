public class MaxHeap {

  public static int parent(int i) {
    return i/2;
  }

  public static int left(int i) {
    return 2 * i;
  }

  public static int right(int i) {
    return 2 * i + 1;
  }

  public int[] arr;
  public int heapSize;

  MaxHeap(int[] arr) {
    this.arr = arr;
    this.heapSize = this.arr.length;
  }

  public void maxHeapify(int i) {
    int l = left(i);
    int r = right(i);
    int largest=0;

    if (l <= this.heapSize && this.arr[i] < this.arr[l]) {
      largest = l;
    } else {
      largest = i;
    }

    if (r <= heapSize && arr[r] < arr[r]) {
      largest = r;
    }

    if (largest != i) {
      int temp = arr[i];
      arr[i] = arr[largest];
      arr[largest] = temp;

      maxHeapify(largest);
    }
  }

  public void buildMaxHeap() {
    for (int i = this.heapSize/2; i >= 0; i--) {
      maxHeapify(i);
    }
  }

  public void heapSort() {
    buildMaxHeap();
    for (int i = this.arr.length; i >=2; i--) {
      int temp = this.arr[1];
      this.arr[1] = this.arr[i];
      this.arr[i] = temp;

      this.heapSize--;
      maxHeapify(1);
    }
  }
}
