import java.util.stream.IntStream;

public final class NaturalNumber
{
	private final Classification type;
	
	public NaturalNumber(final int num) throws IllegalArgumentException
	{
		checkInput(num);
		type = getType(getFactorsSum(num)/2, num);
	}
	
	public Classification getClassification()
	{
		return type;
	}
	
	private int getFactorsSum(final int num)
	{
		return IntStream.rangeClosed(1, (int)Math.sqrt(num)).map(val->getFactorsSumIfDivisible(num, val)).sum();
	}
	
	private int getFactorsSumIfDivisible(final int num, final int val)
	{
		return num%val == 0 ? (num/val == val ? val : num/val + val) : 0;
	}
	
	private Classification getType(final int sum, final int num)
	{
		return sum == num ? Classification.PERFECT : (sum < num ? Classification.DEFICIENT : Classification.ABUNDANT);
	}
	
	private void checkInput(final int num) throws IllegalArgumentException
	{
		if(num < 1)
		{
			throw new IllegalArgumentException("You must supply a natural number (positive integer)");
		}
	}
}