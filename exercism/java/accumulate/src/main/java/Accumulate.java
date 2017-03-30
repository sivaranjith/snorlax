import java.util.List;
import java.util.ArrayList;
import java.util.function.UnaryOperator;

public final class Accumulate
{
	private Accumulate()
	{
	}
	
	public static <T> List<T> accumulate(List<T> input, UnaryOperator<T> operation)
	{
		List<T> result = new ArrayList<>();
		
		for(T ele : input)
		{
			result.add(operation.apply(ele));
		}
		
		return result;
	}
}