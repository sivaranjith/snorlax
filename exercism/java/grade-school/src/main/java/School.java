import java.util.Map;
import java.util.Optional;
import java.util.stream.Collector;
import java.util.stream.Collectors;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map.Entry;
import java.util.AbstractMap.SimpleEntry;

public final class School
{
	
	private final Map<Integer, List<String>> details = new HashMap<>();
	
	public School()
	{
	}
	
	public void add(final String name, final int grade)
	{
		final List<String> nameList = Optional.ofNullable(details.get(grade)).orElse(new ArrayList<String>()); 
		details.putIfAbsent(grade, nameList);
		nameList.add(name);
	}
	
	public int numberOfStudents()
	{
		return details.keySet().stream().mapToInt(key->details.get(key).size()).sum();
	}
	
	public List<String> grade(final int grade)
	{
		final List<String> result = Optional.ofNullable(details.get(grade)).orElse(Collections.EMPTY_LIST);
		return Collections.unmodifiableList(result);
	}
	
	public Map<Integer, List<String>> studentsByGradeAlphabetical()
	{
		details.keySet().stream().forEach(key->details.get(key).sort(String::compareTo));
		return Collections.unmodifiableMap(details);
	}
}