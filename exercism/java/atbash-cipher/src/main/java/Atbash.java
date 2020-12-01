import java.util.Map;
import java.util.stream.Collectors;
import java.util.stream.IntStream;
import java.util.HashMap;

public final class Atbash
{
	
	private static final Map<Character, Character> converstionDetails;
	
	static
	{
		converstionDetails = IntStream.rangeClosed(0, 25).boxed().collect(Collectors.toMap(val->(char)('a' + val), val->(char)('z' - val)));
		IntStream.rangeClosed('0', '9').forEach(val->converstionDetails.put((char)val, (char)val));
	}
	
	private Atbash()
	{
	}
	
	public static String encode(final String plainText)
	{
		return convert(plainText.toLowerCase()).replaceAll("\\w{5}", "$0 ").trim();
	}
	
	public static String decode(final String cipherText)
	{
		return convert(cipherText);
	}
	
	private static String convert(final String text)
	{
		return text.chars().filter(Atbash::isValidCharacter).mapToObj(val->converstionDetails.get((char)val).toString()).collect(Collectors.joining());
	}
	
	private static boolean isValidCharacter(final int val)
	{
		return (val >= 'a' && val <= 'z') || (val >= '0' && val <= '9');
	}
}