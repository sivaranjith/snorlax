import java.util.concurrent.atomic.AtomicInteger;
import java.util.function.Predicate;
import java.util.stream.IntStream;
import java.util.regex.Pattern;

public class LargestSeriesProductCalculator
{
	
	private final String input;
	private static final Predicate<String> checkeForNumbers = (input)->Pattern.compile("[^\\d]").matcher(input).find();
	
	public LargestSeriesProductCalculator(final String input) throws IllegalArgumentException
	{
		checkInput(input);

		this.input = input;
	}
	
	public long calculateLargestProductForSeriesLength(final int digit) throws IllegalArgumentException
	{
		checkDigit(digit);
		
		return IntStream.rangeClosed(digit, input.length()).mapToLong(index->getProduct(digit, index)).max().getAsLong();
	}
	
	private long getProduct(final int digit, final int index)
	{
		return input.substring(index - digit, index).chars().mapToLong(c->c - '0').reduce(1L, (res1, res2)->res1 * res2);
	}
	
	private void checkInput(final String input) throws IllegalArgumentException
	{
		if(input == null)
		{
			throw new IllegalArgumentException("String to search must be non-null.");
		}
		else if(checkeForNumbers.test(input))
		{
			throw new IllegalArgumentException("String to search may only contains digits.");
		}
	}
	
	private void checkDigit(final int digit) throws IllegalArgumentException
	{
		if(digit < 0)
		{
			throw new IllegalArgumentException("Series length must be non-negative.");
		}
		else if(digit > input.length())
		{
			throw new IllegalArgumentException("Series length must be less than or equal to the length of the string to search.");
		}
	}
}