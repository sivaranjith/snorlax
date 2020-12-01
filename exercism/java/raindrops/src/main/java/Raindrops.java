import java.util.Map;
import java.util.stream.Collectors;
import java.util.stream.Stream;

final public class Raindrops
{
	private Raindrops()
	{
	}
	
	public static String convert(final int input)
	{
		String result = getStaticStream().filter(pair->isDivisible(input, pair.number)).map(pair->pair.value).collect(Collectors.joining());
		return result.isEmpty() ? String.valueOf(input) : result;
	}
	
	public static Stream<Pair> getStaticStream()
	{
		return Stream.of(new Pair(3, "Pling"), new Pair(5, "Plang"), new Pair(7, "Plong"));
	}
	
	private static boolean isDivisible(final int dividend, final int divisor)
	{
		return dividend%divisor == 0;
	}
	
	private static final class Pair
	{
		private final Integer number;
		private final String value;
		
		public Pair(final Integer number, final String value)
		{
			this.number = number;
			this.value = value;
		}
	}
	
}