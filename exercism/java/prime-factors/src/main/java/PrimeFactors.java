import java.util.Arrays;
import java.util.concurrent.atomic.AtomicLong;
import java.util.stream.Collectors;
import java.util.stream.IntStream;
import java.util.stream.LongStream;
import java.util.List;

public final class PrimeFactors
{
	private PrimeFactors()
	{
	}
	
	public static List<Long> getForNumber(final long input)
	{
		final AtomicLong mutableInput = new AtomicLong(input); 
		return LongStream.rangeClosed(2, input).flatMap(factor->validateAndGetFactorStream(mutableInput, factor)).boxed().collect(Collectors.toList());
	}
	
	private static LongStream validateAndGetFactorStream(final AtomicLong mutableInput, final long factor)
	{
		final long input = mutableInput.get();
		return (input == 1 || input % factor != 0) ? LongStream.empty() : getFactorStream(mutableInput, factor);
	}
	
	private static LongStream getFactorStream(final AtomicLong mutableInput, final long factor)
	{
		int count = (int)IntStream.iterate(0, i->i+1).filter(__->isStillDivisible(mutableInput, factor)).count();
		return LongStream.range(0, count).map(__->factor);
	}
	
	private static boolean isStillDivisible(final AtomicLong mutableInput, final long  factor)
	{
		long i = mutableInput.get() / factor;
		mutableInput.set(i);
		return i%factor == 0;
	}
}