import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;
import java.util.function.Function;
import java.util.function.Supplier;
import java.util.stream.Collectors;
import java.util.stream.Stream;

final public class DNA
{
	private final Map<Character, Integer> nucleotideCount = new HashMap<>();
	private static final Map<Character, Integer> temp;
	
	static
	{
		//not my idea to use stream.of
		temp = Stream.of('A','C','G','T').collect(Collectors.toMap(Function.identity(), __->0));
	}
	
	public DNA(final String input)
	{
		this.nucleotideCount.putAll(DNA.temp);
		this.nucleotideCount.putAll(input.chars().boxed().collect(Collectors.toMap((i)->(char)(int)i, __->1, Integer::sum)));
	}
	
	public int count(final char nucleotide) throws IllegalArgumentException
	{
		Integer countValue = this.nucleotideCount.get(nucleotide);
		if(countValue == null)
		{
			throw new IllegalArgumentException();
		}
		return countValue;
	}
	
	public Map<Character, Integer> nucleotideCounts()
	{
		return this.nucleotideCount;
	}
}
