import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.function.BiFunction;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public final class WordProblemSolver
{
	
	private static final Map<String, BiFunction<String, String, Integer>> operations = new HashMap<>();
	
	private static final BiFunction<String, String, Integer> addOperation = (op1, op2)->Integer.parseInt(op1) + Integer.parseInt(op2);
	private static final BiFunction<String, String, Integer> minusOperation = (op1, op2)->Integer.parseInt(op1) - Integer.parseInt(op2);
	private static final BiFunction<String, String, Integer> mulOperation = (op1, op2)->Integer.parseInt(op1) * Integer.parseInt(op2);
	private static final BiFunction<String, String, Integer> divOperation = (op1, op2)->Integer.parseInt(op1) / Integer.parseInt(op2);
	private static final BiFunction<String, String, Integer> powerOperation = (op1, op2)->Integer.parseInt(op1) ^ Integer.parseInt(op2);
	
	static
	{
		operations.put("plus", addOperation);
		operations.put("minus", minusOperation);
		operations.put("multiplied", mulOperation);
		operations.put("divided", divOperation);
		operations.put("raised", powerOperation);
	}
	
	public WordProblemSolver()
	{
	}

	public int solve(final String instruction) throws IllegalArgumentException
	{
		checkInstruction(instruction);
		return compute(formatInput(instruction));
	}
	
	private String[] formatInput(final String instruction)
	{
		return instruction.substring(8).replaceAll("( by|\\?)", "").split(" ");
	}
	
	private int compute(final String[] instruction)
	{
		final List<String> tokens = Arrays.stream(instruction).collect(Collectors.toList());

		operations(tokens, Arrays.asList("raised"));
		operations(tokens, Arrays.asList("multiplied", "divided"));
		operations(tokens, Arrays.asList("plus", "minus"));
		
		return Integer.parseInt(tokens.get(0));
	}
	
	private void operations(final List<String> tokens, final List<String> operators)
	{
		while(IntStream.range(0, tokens.size()).filter(index->operators.contains(tokens.get(index))).anyMatch(index->operate(tokens, index)));
	}
	
	private boolean operate(final List<String> tokens, final int index)
	{
		final String val = operations.get(tokens.get(index)).apply(tokens.get(index - 1), tokens.get(index + 1)).toString();
		tokens.remove(index + 1);
		tokens.remove(index);
		tokens.remove(index - 1);
		tokens.add(index - 1, val);
		return true;
	}
	
	private void checkInstruction(final String instruction) throws IllegalArgumentException
	{
		if(instruction == null || !instruction.matches(".*(" + operations.keySet().stream().collect(Collectors.joining("|")) + ").*"))
		{
			throw new IllegalArgumentException("I'm sorry, I don't understand the question!");
		}
	}
}