import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public final class Sieve
{
	
	private final int upperLimit;
	
	public Sieve(final int upperLimit)
	{
		this.upperLimit = upperLimit;
	}
	
	public List<Integer> getPrimes()
	{
		final List<Integer> composite = new ArrayList<>();
		
		return IntStream.rangeClosed(2, this.upperLimit).filter(val->!isComposite(composite, val)).boxed().collect(Collectors.toList());
	}
	
	private boolean isComposite(final List<Integer> composite, final int val)
	{
		final boolean isAvaliable = composite.contains(val);
		
		if(!isAvaliable)
		{
			generateCompositeNumbers(composite, val);
		}
		
		return isAvaliable;
	}
	
	private void generateCompositeNumbers(final List<Integer> composite, final int val)
	{
		IntStream.rangeClosed(2, this.upperLimit/val).forEach(multiplicand->composite.add(val * multiplicand));
	}
}