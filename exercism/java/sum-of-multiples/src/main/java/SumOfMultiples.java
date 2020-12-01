import java.util.Arrays;
import java.util.stream.Collectors;
import java.util.stream.IntStream;
import java.util.stream.Stream;
import java.util.Set;
import java.util.function.Function;

public final class SumOfMultiples
{
	private SumOfMultiples()
	{
	}
	
	public static int sum(final int limit, final int[] set)
	{
		return IntStream.range(1, limit).filter(val->isDivisible(val, set)).sum();
	}
	
	private static boolean isDivisible(final int val, final int[] set)
	{
		return Arrays.stream(set).anyMatch(no->val%no == 0);
	}
}
