import java.util.Arrays;
import java.util.function.Function;
import java.util.function.IntUnaryOperator;
import java.util.stream.IntStream;

public final class PascalsTriangle
{
	private PascalsTriangle()
	{
	}
	
	public static int[][] computeTriangle(final int rowCount) throws IllegalArgumentException
	{
		checkInput(rowCount);
		return IntStream.rangeClosed(1, rowCount).collect(()->new int[rowCount][], (acc,res)->printer(acc,res), (res1, res2)->{});
	}
	
	private static void printer(final int[][] val, final int rowNo)
	{
		val[rowNo - 1] = new int[rowNo];
		IntStream.rangeClosed(1, rowNo).forEach(colNo->fillVal(val,rowNo,colNo));
	}
	
	private static void fillVal(final int[][] val, final int rowNo, final int colNo)
	{
		val[rowNo - 1][colNo - 1] = (colNo == 1 || colNo == rowNo) ? 1 : val[rowNo - 2][colNo - 2] + val[rowNo - 2][colNo - 1];
	}
	
	public static boolean isTriangle(final int[][] input)
	{
		final int[][] result = computeTriangle(input.length);
		return IntStream.range(0, input.length).allMatch(index->isEqual(input[index], result[index], index));
	}
	
	private static boolean isEqual(final int[] input, final int[] result, final int rowNo)
	{
		return IntStream.range(0, rowNo).allMatch(colNo->input[colNo] == result[colNo]);
	}
	
	private static void checkInput(final int rowCount) throws IllegalArgumentException
	{
		if(rowCount < 0)
		{
			throw new IllegalArgumentException();
		}
	}
}