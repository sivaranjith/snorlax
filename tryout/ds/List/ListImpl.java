package tryout.ds;

public class ListImpl<T> implements List<T>
{
	T source[];
	int size=0;
	
	public ListImpl()
	{
		source =  (T[]) new Object[9];
	}
	
	public ListImpl(int size)
	{
		source =  (T[]) new Object[size-1];
	}

	public T get(int index) 
	{
		if(index < this.size-1)
		{
			return source[index];
		}
		return null;
	}

	public void spanNewLength()
	{
		T [] tempArray = (T[]) new Object[this.size+10];
		int i=0;
		for(T tempElem : this.source)
		{
			tempArray[i++] = tempElem;
		}
		
		source = tempArray;
	}
	
	public boolean add(T t) 
	{
		if(this.size >= this.source.length)
		{
			spanNewLength();
		}

		source[size] = t;
		size+=1;
		return Boolean.TRUE;
	}

	public boolean remove(T t) 
	{
		int index = -1;
		for(int i=0;i<=this.size;)
		{
			System.out.println("the value of t"+i);
			if(t.equals(this.source[i]))
			{
				System.out.println("coming inside t"+i);
				index = i;
				break;
						
			}
			i++;
		}
		
		if(index == -1) {return Boolean.FALSE;}
		
		for(int i = index; i<=this.size;i++)
		{
			System.out.println("in the second loop ::"+i);
			source[i] = source[i+1];
		}
		
		this.size-= 1;
		
		
		return Boolean.TRUE;
	}

	public boolean contains(T t) 
	{
		for(int i=0;i<this.size;i++)
		{
			T temp = this.source[i];
			if(temp.equals(t))
			{
				return  Boolean.TRUE;
			}
		}

		return false;
	}
	
	public String toString()
	{
		StringBuffer outString = new StringBuffer();
		
		outString.append("[");
		for(T temp : this.source)
		{
			if(temp != null)
			{
				outString.append(temp+",");
			}
			
		}
		outString.append("]");
		return outString.toString();
	}

}
