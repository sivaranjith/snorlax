import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Optional;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public final class OpticalCharacterReader
{
	
	private static final Map<String, String> numbers = new HashMap<>();
	
	static
	{
		numbers.put(" _ | ||_|", "0");
		numbers.put("     |  |", "1");
		numbers.put(" _  _||_ ", "2");
		numbers.put(" _  _| _|", "3");
		numbers.put("   |_|  |", "4");
		numbers.put(" _ |_  _|", "5");
		numbers.put(" _ |_ |_|", "6");
		numbers.put(" _   |  |", "7");
		numbers.put(" _ |_||_|", "8");
		numbers.put(" _ |_| _|", "9");
	}

	public OpticalCharacterReader()
	{
	}

	public String parse(final List<String> inputList) throws IllegalArgumentException
	{
		checkInput(inputList);
		return IntStream.iterate(0, val->val + 4).limit(inputList.size() / 4).mapToObj(startingRow->getCharactersFromRow(inputList, startingRow)).collect(Collectors.joining(","));
	}
	
	private String getCharactersFromRow(final List<String> inputList, final int startingRow)
	{
		return IntStream.iterate(0, val->val + 3).limit(inputList.get(startingRow).length() / 3).mapToObj(startingColumn->getCharacter(inputList, startingRow, startingColumn)).collect(Collectors.joining());
	}
	
	private void checkInput(final List<String> inputList) throws IllegalArgumentException
	{
		if(inputList.size() % 4 != 0)
		{
			throw new IllegalArgumentException("Number of input rows must be a positive multiple of 4");
		}
		
		if(inputList.get(0).length() % 3 != 0)
		{
			throw new IllegalArgumentException("Number of input columns must be a positive multiple of 3");
		}
	}
	
	private String getCharacter(final List<String> inputList, final int startingRow, final int startingColumn)
	{
		final String charAsString = IntStream.range(0, 3).mapToObj(val->inputList.get(startingRow + val).substring(startingColumn, startingColumn + 3)).collect(Collectors.joining());
		return Optional.ofNullable(numbers.get(charAsString)).orElse("?");
	}
}