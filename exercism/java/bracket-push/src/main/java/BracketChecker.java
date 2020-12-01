import java.util.Stack;

public final class BracketChecker
{
	
	private final boolean isComplete;
	
	public BracketChecker(final String input)
	{
		isComplete = isBracketComplete(input);
	}
	
	private boolean isBracketComplete(final String input)
	{
		final Stack<Character> container = new Stack<>();
		final boolean allMatch = input.chars().filter(this::isBracket).allMatch(val->modifiyStack(container, val));
		return allMatch && container.isEmpty();
	}
	
	private boolean isBracket(final int val)
	{
		return isOpenBracket(val) || isClosedBracket(val);
	}
	
	private boolean isOpenBracket(final int val)
	{
		return val == '{' || val == '[' || val == '(' || val == '<'; 
	}
	
	private boolean isClosedBracket(final int val)
	{
		return val == '}' || val == ']' || val == ')' || val == '>';
	}
	
	private boolean modifiyStack(final Stack<Character> container, final int val)
	{
		boolean returnValue = false;
		if(isOpenBracket(val))
		{
			container.push((char)val);
			returnValue = true;
		}
		else if(!container.isEmpty())
		{
			final char popedVal = container.pop();
			if((val == ')' && popedVal == '(') || (val == popedVal + 2))
			{
				returnValue = true;
			}
		}
		return returnValue;
	}
	
	public boolean areBracketsMatchedAndNestedCorrectly()
	{
		return isComplete;
	}
}