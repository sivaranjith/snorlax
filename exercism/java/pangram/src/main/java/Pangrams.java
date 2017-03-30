import java.util.Arrays;
import java.util.function.Predicate;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

final public class Pangrams
{
	public static boolean isPangram(final String line)
	{
		//not my idea
		final String lowerCaseLine = line.toLowerCase();
		return IntStream.rangeClosed('a', 'z').allMatch(c->lowerCaseLine.indexOf(c) >= 0);
	}
}
