import java.util.Arrays;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

final public class Acronym
{
	private Acronym()
	{
	}
	
	public static String generate(final String input)
	{
		return Arrays.stream(input.split("[^a-zA-Z]")).filter(token->!token.isEmpty()).map(Acronym::parseToken).collect(Collectors.joining());
	}
	
	private static String parseToken(final String token)
	{
		return IntStream.range(0, token.length()).filter(index->isValidIndex(token, index)).mapToObj(index->getCharacter(token, index)).collect(Collectors.joining());
	}
	
	private static boolean isValidIndex(final String token, final int index)
	{
		return index == 0 || (Character.isUpperCase(token.charAt(index)) && Character.isLowerCase(token.charAt(index - 1)));
	}
	
	private static String getCharacter(final String token, final int index)
	{
		return String.valueOf(token.charAt(index)).toUpperCase();
	}
}
