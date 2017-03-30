import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.stream.IntStream;

public final class BaseConverter
{
	
	private int val;
	
	public BaseConverter(final int currentBase, final int[] digits) throws IllegalArgumentException
	{
		checkInput(currentBase, digits);
		val = convertToDecimal(currentBase, digits);
	}
	
	private int convertToDecimal(final int currentBase, final int[] digits)
	{
		return IntStream.range(0, digits.length).map(index->(int)(digits[digits.length - index - 1]*Math.pow(currentBase, index))).sum();
	}
	
	public int[] convertToBase(final int toBase)
	{
		checkBase(toBase);
		
		final List<Integer> temp = new ArrayList<>();
		
		do
		{
			temp.add(0, val%toBase);
			val /= toBase;
		}while(val != 0);
		
		return temp.stream().mapToInt(val->val).toArray();
	}
	
	private void checkInput(final int currentBase, final int[] digits) throws IllegalArgumentException
	{
		checkBase(currentBase);
		if(digits.length == 0)
		{
			throw new IllegalArgumentException("You must supply at least one digit.");
		}
		else if(digits.length > 1 && digits[0] == 0)
		{
			throw new IllegalArgumentException("Digits may not contain leading zeros.");
		}
		Arrays.stream(digits).forEach(digit->checkDigits(digit, currentBase));
	}
	
	private void checkDigits(final int digit, final int base)
	{
		if(digit < 0)
		{
			throw new IllegalArgumentException("Digits may not be negative.");
		}
		else if(digit >= base)
		{
			throw new IllegalArgumentException("All digits must be strictly less than the base.");
		}
	}
	
	private void checkBase(final int base) throws IllegalArgumentException
	{
		if(base < 2)
		{
			throw new IllegalArgumentException("Bases must be at least 2.");
		}
	}
}