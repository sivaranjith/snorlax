import java.util.function.IntUnaryOperator;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

final public class RnaTranscription
{
	private RnaTranscription()
	{
	}
	
	public static String ofDna(final String DNA)
	{
		//not my solution
		return DNA.chars().mapToObj(RnaTranscription::dnaToRnaConverter).collect(Collectors.joining());
	}
	
	private static String dnaToRnaConverter(final int dnaNucleotide)
	{
		String rnaNucleotide = "";
		switch(dnaNucleotide)
		{
			case 'G': rnaNucleotide = "C";
					  break;
			case 'C': rnaNucleotide = "G";
					  break;
			case 'T': rnaNucleotide = "A";
					  break;
			case 'A': rnaNucleotide = "U";
					  break;
		}
		return rnaNucleotide;
	}
}