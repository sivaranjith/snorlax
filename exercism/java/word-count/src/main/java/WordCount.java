import java.util.Map;
import java.util.function.Function;
import java.util.stream.Collectors;
import java.util.stream.Stream;
import java.util.HashMap;
import java.util.Arrays;

public class WordCount
{
	
	public Map<String, Integer> phrase(String line)
	{
		//not my solution
		return Stream.of(line.toLowerCase().split("[^a-z0-9]")).filter(x->!x.isEmpty()).collect(Collectors.toMap(Function.identity(), __->1, Integer::sum));
	}
	
}
