import java.util.ArrayList;
import java.util.function.BiConsumer;
import java.util.function.ObjIntConsumer;
import java.util.function.Supplier;
import java.util.concurrent.atomic.AtomicInteger;

final public class Scrabble
{
	
	private final int scrabbleScore;
	private static final int[] scrabbleValues = new int[26];
	
	static
	{
		scrabbleValues[0] = 1;
		scrabbleValues[1] = 3;
		scrabbleValues[2] = 3;
		scrabbleValues[3] = 2;
		scrabbleValues[4] = 1;
		scrabbleValues[5] = 4;
		scrabbleValues[6] = 2;
		scrabbleValues[7] = 4;
		scrabbleValues[8] = 1;
		scrabbleValues[9] = 8;
		scrabbleValues[10] = 5;
		scrabbleValues[11] = 1;
		scrabbleValues[12] = 3;
		scrabbleValues[13] = 1;
		scrabbleValues[14] = 1;
		scrabbleValues[15] = 3;
		scrabbleValues[16] = 10;
		scrabbleValues[17] = 1;
		scrabbleValues[18] = 1;
		scrabbleValues[19] = 1;
		scrabbleValues[20] = 1;
		scrabbleValues[21] = 4;
		scrabbleValues[22] = 4;
		scrabbleValues[23] = 8;
		scrabbleValues[24] = 4;
		scrabbleValues[25] = 10;
	}
	
	public Scrabble(final String scrabbleInput)
	{
		this.scrabbleScore = Scrabble.calculateScore(scrabbleInput);
	}
	
	private static int calculateScore(final String scrabbleInput)
	{
		int scrabbleScore = 0;
		if(scrabbleInput != null)
		{
			scrabbleScore = scrabbleInput.toUpperCase().chars().map(c-> Character.isUpperCase(c) ? scrabbleValues[c - 'A'] : 0).sum();			
		}
		return scrabbleScore;
	}
	
	public int getScore()
	{
		return scrabbleScore;
	}
}