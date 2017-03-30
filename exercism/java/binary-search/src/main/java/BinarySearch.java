import java.util.List;

public class BinarySearch<T>
{
	private final List<T> inputList;
	
	public BinarySearch(final List<T> inputList)
	{
		this.inputList = inputList;
	}
	
	@SuppressWarnings("unchecked")
	public int indexOf(final T obj)
	{
		return inputList.isEmpty() ? -1 : indexOf((T[])inputList.toArray(), obj, 0, inputList.size() - 1);
	}
	
	private int indexOf(final T[] elementArray, final T obj, final int startPos, final int endPos)
	{
		final int pos = (startPos + endPos)/2;
		final T val = elementArray[pos];
		int resultIndex = -1;
		
		if(val.hashCode() == obj.hashCode())
		{
			resultIndex = pos;
		}
		else if(pos != startPos)
		{
			if(val.hashCode() > obj.hashCode())
			{
				resultIndex = indexOf(elementArray, obj, startPos, endPos - 1);
			}
			else if(val.hashCode() < obj.hashCode())
			{
				resultIndex = indexOf(elementArray, obj, pos + 1, endPos);
			}
		}
		return resultIndex;
	}
}