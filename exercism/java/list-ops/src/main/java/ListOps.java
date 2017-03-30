import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.function.BiFunction;
import java.util.function.BinaryOperator;
import java.util.function.Predicate;
import java.util.function.UnaryOperator;

public final class ListOps
{
	
	private ListOps()
	{
	}

	public static <T> int length(final List<T> inputList)
	{
		Iterator<T> listIt = inputList.iterator();
		int size = 0;
		
		while(listIt.hasNext())
		{
			listIt.next();
			++size;
		}
		
		return size;
	}
	
	public static <T> List<T> reverse(final List<T> inputList)
	{
		Iterator<T> listIt = inputList.iterator();
		final List<T> result = new ArrayList<>();
		
		while(listIt.hasNext())
		{
			result.add(0, listIt.next());
		}
		
		return result;
	}
	
	public static <T> List<T> map(final List<T> inputList, final UnaryOperator<T> operation)
	{
		Iterator<T> listIt = inputList.iterator();
		final List<T> result = new ArrayList<>();
		
		while(listIt.hasNext())
		{
			result.add(operation.apply(listIt.next()));
		}
		
		return result;
	}
	
	public static <T> List<T> filter(final List<T> inputList, final Predicate<T> operation)
	{
		Iterator<T> listIt = inputList.iterator();
		final List<T> result = new ArrayList<>();
		
		while(listIt.hasNext())
		{
			final T ele = listIt.next();
			if(operation.test(ele))
			{
				result.add(ele);
			}
		}
		
		return result;
	}
	
	public static <T> List<T> concat(@SuppressWarnings("unchecked") final List<T>... lists)
	{
		List<T> result = new ArrayList<>();
		
		for(List<T> list : lists)
		{
			addAll(result, list);
		}
		
		return result;
	}
	
	public static <T> T reduce(final List<T> inputList, final T initialValue, final BinaryOperator<T> accumulator, final BinaryOperator<T> reducer)
	{
		T result = initialValue;
		Iterator<T> listIt = inputList.iterator();
		
		while(listIt.hasNext())
		{
			result = accumulator.apply(result, listIt.next());
		}
		
		return result;
	}
	
	public static <T> List<T> reduce(final List<T> inputList1, final List<T> inputList2, final BiFunction<List<T>, T, List<T>> accumulator, final BinaryOperator<List<T>> combiner)
	{
		List<T> result = new ArrayList<>();
		addAll(result, inputList2);
		Iterator<T> listIt = inputList1.iterator();
		
		while(listIt.hasNext())
		{
			result = accumulator.apply(result, listIt.next());
		}
		
		return result;
	}
	
	private static <T> void addAll(final List<T> result, final List<T> list)
	{
		Iterator<T> listIt = list.iterator();
		
		while(listIt.hasNext())
		{
			result.add(listIt.next());
		}
	}
}