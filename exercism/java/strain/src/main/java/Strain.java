import java.util.ArrayList;
import java.util.List;
import java.util.function.Predicate;

public final class Strain
{
	private Strain()
	{
	}
	
	public static <T> List<T> keep(final List<T> inputList, final Predicate<T> operation)
	{
		return filter(inputList, operation);
	}
	
	public static <T> List<T> discard(final List<T> inputList, final Predicate<T> operation)
	{
		return filter(inputList, operation.negate());
	}
	
	private static <T> List<T> filter(final List<T> inputList, final Predicate<T> operation)
	{
		final List<T> result = new ArrayList<>();
		
		for(T ele : inputList)
		{
			if(operation.test(ele))
			{
				result.add(ele);
			}
		}
		
		return result;
	}
}