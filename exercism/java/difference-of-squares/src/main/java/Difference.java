public final class Difference
{
	private Difference()
	{
	}
	
	public static int betweenSquareOfSumAndSumOfSquaresTo(final int input)
	{
		return computeSquareOfSumTo(input) - computeSumOfSquaresTo(input);
	}
	
	public static int computeSumOfSquaresTo(final int input)
	{
		return (input * (input + 1) * (input*2 + 1))/6;
	}
	
	public static int computeSquareOfSumTo(final int input)
	{
		return square((input * (input + 1))/2);
	}
	
	private static int square(final int input)
	{
		return input*input;
	}
}
