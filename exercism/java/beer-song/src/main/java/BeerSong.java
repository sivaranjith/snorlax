import java.util.stream.Collectors;
import java.util.stream.IntStream;

public class BeerSong
{
	private BeerSong()
	{
	}
	
	public static String verse(final int lineNo)
	{
		return getVerse(lineNo);
	}
	
	public static String sing(final int startNo, final int endNo)
	{
		return iterateSong(startNo, endNo);
	}
	
	public static String singSong()
	{
		return iterateSong(99, 0);
	}
	
	private static String iterateSong(final int startNo, final int endNo)
	{
		return IntStream.iterate(startNo, i->i-1).limit(startNo - endNo + 1).mapToObj(BeerSong::getVerse).collect(Collectors.joining());
	}
	
	private static String getVerse(final int lineNo)
	{
		String result;
		
		if(lineNo > 0)
		{
			result = getNumberOfBottles(lineNo) + " of beer on the wall, " + getNumberOfBottles(lineNo) + " of beer.\nTake " + getToken(lineNo) + " down and pass it around, " + getNumberOfBottles(lineNo - 1) + " of beer on the wall.\n\n";
		}
		else
		{
			result = "No more bottles of beer on the wall, no more bottles of beer.\nGo to the store and buy some more, 99 bottles of beer on the wall.\n\n";
		}
		
		return result;
	}
	
	private static String getToken(final int lineNo)
	{
		return lineNo != 1 ? "one" : "it";
	}
	
	private static String getNumberOfBottles(final int lineNo)
	{
		return lineNo == 0 ? "no more bottles" : (lineNo == 1 ? "1 bottle" : lineNo + " bottles");
	}
}