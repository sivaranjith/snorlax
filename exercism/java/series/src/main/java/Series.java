import java.util.stream.Collectors;
import java.util.stream.IntStream;
import java.util.List;

public final class Series
{
	
	private final String input;
	
    public Series(final String input)
    {
    	this.input = input;
    }
    
    public List<Integer> getDigits()
    {
    	return toList(this.input.length(), 0);
    }
    
    public List<List<Integer>> slices(final int windowLength) throws IllegalArgumentException
    {
    	checkWindowLength(windowLength);
    	return IntStream.rangeClosed(0, input.length() - windowLength).mapToObj(index->toList(windowLength, index)).collect(Collectors.toList());
    }
    
    private List<Integer> toList(final int windowLength, final int index)
    {
    	return IntStream.range(index, index + windowLength).mapToObj(val->this.input.charAt(val) - '0').collect(Collectors.toList());
    }
    
    private void checkWindowLength(final int windowLength) throws IllegalArgumentException
    {
    	if(this.input.length() < windowLength)
    	{
    		throw new IllegalArgumentException();
    	}
    }
}
