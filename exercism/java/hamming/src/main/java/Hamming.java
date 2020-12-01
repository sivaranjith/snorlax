import java.util.function.IntBinaryOperator;
import java.util.stream.IntStream;

final public class Hamming
{
	private Hamming()
	{	
	}
	
	//not my solution
	public static int compute(final String DNA1, final String DNA2) throws IllegalArgumentException
	{
		inputValidator(DNA1, DNA2);		
		return IntStream.range(0, DNA1.length()).reduce(0, reducerOperation(DNA1, DNA2));
	}
	
	private static IntBinaryOperator reducerOperation(final String DNA1, final String DNA2)
	{
		return (result, index) -> (DNA1.charAt(index) != DNA2.charAt(index)) ? result + 1 : result;
	}
	
	private static void inputValidator(final String DNA1, final String DNA2) throws IllegalArgumentException
	{
		if(DNA1.length() != DNA2.length())
		{
			throw new IllegalArgumentException();
		}
	}
}