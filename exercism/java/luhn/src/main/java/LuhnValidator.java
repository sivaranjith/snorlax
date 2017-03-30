import java.util.function.IntUnaryOperator;
import java.util.function.Predicate;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.util.stream.IntStream;

public final class LuhnValidator
{
	
	private static final Predicate<String> checker = cardNo->Pattern.compile("[^0-9 ]").matcher(cardNo).find();
	
	public LuhnValidator()
	{
	}
	
	public boolean isValid(final String cardString)
	{
		String cardNo = cardString.replaceAll(" ", "");
		boolean isValidCard = false;
		
		if(cardNo.length() > 1 && !checker.test(cardNo))
		{
			int sum = IntStream.range(0, cardNo.length()).map(index->getValue(cardNo, index)).sum();
			isValidCard = isValidSum(sum);
		}
		
		return isValidCard;
	}
	
	private int getValue(final String cardNo, final int index)
	{
		int val = cardNo.charAt(index) - '0';

		if(isIndexToCheck(cardNo.length(), index))
		{
			val = (val > 4) ? val*2 - 9 : val*2;
		}
		
		return val;
	}
	
	private boolean isIndexToCheck(final int length, final int index)
	{
		return isEven(length) ? isEven(index) : !isEven(index);
	}
	
	private boolean isEven(final int val)
	{
		return (val & 1) == 0;
	}
	
	private boolean isValidSum(final int sum)
	{
		return sum % 10 == 0;
	}
}