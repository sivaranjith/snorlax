import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.function.Function;
import java.util.stream.Collectors;

public final class Bookstore
{

	private final Map<Integer, Long> bookCollection;

	public Bookstore(final List<Integer> bookCollection)
	{
		this.bookCollection = bookCollection.stream().collect(Collectors.groupingBy(Function.identity(), Collectors.counting()));
	}

	public double calculateTotalCost()
	{
		final List<List<Integer>> bookSets = new ArrayList<>();

		while(!this.bookCollection.isEmpty())
		{
			addBookSets(bookSets);
		}

		return calculateCost(bookSets);
	}

	private void addBookSets(final List<List<Integer>> bookSets)
	{
		Iterator<Integer> bookIt = bookCollection.keySet().iterator();
		final List<Integer> currentSet = new ArrayList<>();

		while(bookIt.hasNext())
		{
			final Integer book = bookIt.next();
			final Long count = bookCollection.get(book);

			if(count == 1)
			{
				bookIt.remove();
			}
			else
			{
				bookCollection.put(book, count - 1);
			}

			currentSet.add(book);
		}

		bookSets.add(currentSet);

		if(currentSet.size() == 3)
		{
			bookSets.stream().filter(list->list.size() == 5).findFirst().ifPresent(list->currentSet.add(list.remove(0)));
		}
	}

	private double calculateCost(final List<List<Integer>> bookSets)
	{
		return bookSets.stream().mapToDouble(set->8 * set.size() * (1 - getDiscountPercentage(set.size()))).sum();
	}

	private double getDiscountPercentage(final int size)
	{
		return size == 1 ? 0 : (size == 2 ? 0.05 : (size == 3 ? 0.1 : (size == 4 ? 0.2 : 0.25)));
	}
}