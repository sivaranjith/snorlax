import java.util.List;
import java.util.concurrent.atomic.AtomicLong;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.stream.Collector;
import java.util.stream.Collectors;

final public class Anagram
{
	private final String source;
	
	public Anagram(final String source)
	{
		this.source = source.toLowerCase();
	}
	
	public List<String> match(final List<String> tokenList)
	{
		return tokenList.stream().filter(this::isAnagram).distinct().collect(Collectors.toList());
	}
	
	private boolean isAnagram(final String candidate)
	{
		boolean isCandidateAnagram = false;
		
		if(!this.source.equalsIgnoreCase(candidate))
		{			
			final int[] bucket = new int[26];
			this.source.toLowerCase().chars().forEach(c->++bucket[c - 'a']);
			candidate.toLowerCase().chars().forEach(c->--bucket[c - 'a']);
			isCandidateAnagram = Arrays.stream(bucket).allMatch(bucketValue->bucketValue == 0);
		}
		
		return isCandidateAnagram;
	}
}