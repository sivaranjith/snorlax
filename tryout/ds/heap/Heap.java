package tryout.ds.List;

public class Heap 
{
	int capacity;
	int size = 0;
	public int getSize() {
		return size;
	}

	public void setSize() {
		this.size = this.getArray().length-1;
	}

	public int getCapacity() {
		return capacity;
	}

	public void setCapacity(int capacity) {
		this.capacity = capacity;
	}

	public int[] getArray() {
		return array;
	}

	public void setArray(int[] array) {
		this.array = array;
		setSize();
	}

	int [] array;
	
	public Heap()
	{
		capacity = 10;
		array =  new int[10];
	}
	
	public void add(int value)
	{
		this.array[this.getSize()] = value;

		if(this.getSize() > 0)
		{
			heapify(this.getSize());
		}
		
		this.size ++;
	}
	
	public int getTop()
	{
		int []a =  this.getArray();
		
		if(this.size ==  0)
		{
			return a[0];
		}
		
		int temp = a[this.size];
		int top = a[0];
		a[0] =  temp;
		this.size--;
		heapify(this.getSize());		
		
		return top;
	}
	
	public void heapify(int i)
	{
		int [] a =  this.getArray();
		int r = this.getRightChild(i);
		int l =  this.getLeftChild(i);
		int max = i;
		
		if(r <= this.size && a[r] < a[max])
		{
			max = r;
		}
		if(l <= this.size && a[l] < a[max])
		{
			max = l;
		}
		
		if(max  != i )
		{
			int temp = a[max];
			a[max] = a[i];
			a[i] = temp;
			
		}
		
		if(i!=0)
		{
			heapify(this.getParentIndex(max));
		}
		
		
		
	}
	
	public int getParentIndex(int i)
	{
		return (i-1)/2;
	}
	
	public int getRightChild(int i)
	{
		return  2*i+2;
	}
	
	public int getLeftChild(int i)
	{
		return  2*i+1;
	}
	

}
