import java.util.stream.Collectors;
import java.util.stream.IntStream;
import java.util.Arrays;
import java.util.List;

public final class DiamondPrinter
{
	
	private int totalLength;
	private char letter;
	
	public DiamondPrinter()
	{
	}
	
	public List<String> printToList(final char letter)
	{
		this.letter = letter;
		this.totalLength = (this.letter - 'A')*2 + 1;

		//nmi but just trying with String.format
		return IntStream.rangeClosed('A', 'A' + this.totalLength - 1).mapToObj(val->getPattern(getLetter(val))).collect(Collectors.toList());
	}
	
	private char getLetter(final int val)
	{
		return ((this.totalLength + 1)/2 > val - 'A') ? (char)val : (char)(2*this.letter - val);
	}
	
	private String getPattern(final int val)
	{
		String pattern;
		final String internalSpace = getSpace(2*(val - 'A') - 1), externalSpace = getSpace(this.letter - val), strVal = String.valueOf((char)val);
		
		if(val == 'A')
		{
			pattern = String.format("%s%s%s", externalSpace, strVal, externalSpace);
		}
		else
		{
			pattern = String.format("%s%s%s%s%s", externalSpace, strVal, internalSpace, strVal, externalSpace);
		}
		
		return pattern;
	}
	
	private String getSpace(final int length)
	{
		return IntStream.range(0, length).mapToObj(__->" ").collect(Collectors.joining());
	}
}