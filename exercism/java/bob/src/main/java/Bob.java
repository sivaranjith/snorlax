import java.util.Arrays;
import java.util.function.BiFunction;
import java.util.function.Predicate;
import java.util.regex.Pattern;

public final class Bob
{
	public Bob()
	{
	}
	
	public String hey(final String myConv)
	{
		String reply = "Whatever.";
		if(myConv.trim().isEmpty())
		{
			reply = "Fine. Be that way!";
		}
		//\\p{L} means like all unicode characters
		//not my implementation
		else if(myConv.matches(".*\\p{L}.*") && myConv.equals(myConv.toUpperCase()))
		{
			reply = "Whoa, chill out!";
		}
		else if(myConv.endsWith("?"))
		{
			reply = "Sure.";
		}
		return reply;
	}
}