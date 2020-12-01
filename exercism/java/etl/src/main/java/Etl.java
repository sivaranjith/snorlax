import java.util.List;
import java.util.Map;
import java.util.function.Function;
import java.util.HashMap;

public class Etl
{
	public Map<String, Integer> transform(Map<Integer, List<String>> old)
	{
		Map<String, Integer> newPattern = new HashMap<>();
		
		old.forEach((key, value)->value.forEach((ele)->newPattern.put(ele.toLowerCase(), key)));
		
		return newPattern;
	}
}
