import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.stream.Collectors;
import java.util.stream.IntStream;
import java.util.stream.Stream;

public final class ChangeCalculator
{
	private List<Integer> coins;
	
	public ChangeCalculator(final List<Integer> coins)
	{
		this.coins = coins.stream().sorted(Comparator.reverseOrder()).collect(Collectors.toList());
	}
	
	public List<Integer> computeMostEfficientChange(final int inputAmount)
	{
		checkInputAmount(inputAmount);
		
		final List<Integer> result = IntStream.range(0, coins.size()).mapToObj(startingIndex->getChange(inputAmount, startingIndex)).min(Comparator.comparingInt(List::size)).get();
		checkResult(result, inputAmount);

		Collections.reverse(result);
		return result;
	}
	
	private List<Integer> getChange(final int inputAmount, final int startingIndex)
	{
		final AtomicInteger amount = new AtomicInteger(inputAmount);
		final List<Integer> result = this.coins.stream().skip(startingIndex).flatMap(coin->getChangeCoins(amount, coin)).collect(Collectors.toList());
		
		return amount.get() == 0 ? result : Collections.emptyList();
	}
	
	private void checkInputAmount(final int inputAmount)
	{
		if(inputAmount < 0)
		{
			throw new IllegalArgumentException("Negative totals are not allowed.");
		}
	}
	
	private void checkResult(final List<Integer> result, final int inputAmount)
	{
		if(result.size() == 0 && inputAmount != 0)
		{
			throw new IllegalArgumentException("The total " + inputAmount + " cannot be represented in the given currency.");
		}
	}
	
	private Stream<Integer> getChangeCoins(final AtomicInteger amount, final int coin)
	{
		final int times = amount.get() / coin;
		amount.set(amount.get() - times * coin);
	
		return IntStream.rangeClosed(1, times).map(index->coin).boxed();
	}
}