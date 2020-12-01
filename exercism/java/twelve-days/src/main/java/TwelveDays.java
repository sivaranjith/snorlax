import java.util.stream.Collectors;
import java.util.stream.IntStream;
import java.util.stream.Stream;

public final class TwelveDays
{
	
	private static final String[] numberInWord = {"", "first", "second", "third", "fourth", "fifth", "sixth", "seventh", "eighth", "ninth", "tenth", "eleventh", "twelfth"};
	private static final String[] items= {"", "a Partridge", "two Turtle Doves, and ", "three French Hens, ", "four Calling Birds, ", "five Gold Rings, ", "six Geese-a-Laying, ", "seven Swans-a-Swimming, ", "eight Maids-a-Milking, ", "nine Ladies Dancing, ", "ten Lords-a-Leaping, ", "eleven Pipers Piping, ", "twelve Drummers Drumming, "};
	
	private TwelveDays()
	{
	}
	
	public static String sing()
	{
		return verses(1, 12);
	}
	
	public static String verses(final int startingDay, final int endingDay)
	{
		return IntStream.rangeClosed(startingDay, endingDay).mapToObj(val->verse(val)).collect(Collectors.joining("\n"));
	}
	
	public static String verse(final int endingDay)
	{
		return "On the " + numberInWord[endingDay] + " day of Christmas my true love gave to me, " + getItems(endingDay) + " in a Pear Tree.\n";
	}

	private static String getItems(final int endingDay)
	{
		return IntStream.iterate(endingDay, val->val-1).limit(endingDay).mapToObj(val->items[val]).collect(Collectors.joining());
	}
}