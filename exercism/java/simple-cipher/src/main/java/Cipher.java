import java.security.SecureRandom;
import java.util.function.BinaryOperator;
import java.util.function.UnaryOperator;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public final class Cipher
{

	private final String key;
	
	public Cipher()
	{
		final SecureRandom sr = new SecureRandom();
		key = IntStream.range(0, 100).mapToObj(val->String.valueOf((char)(sr.nextInt(26) + 'a'))).collect(Collectors.joining());
	}
	
	public Cipher(final String key) throws IllegalArgumentException
	{
		checkKey(key);
		this.key = key;
	}

	public String getKey()
	{
		return key;
	}
	
	public String encode(final String plainText)
	{
		return operate(plainText, Integer::sum, inputChar->(inputChar - 97)%26 + 97);
	}
	
	public String decode(final String encryptedText)
	{
		return operate(encryptedText, (x, y)->x - y, inputChar->(inputChar - 97 + 26)%26 + 97);
	}
	
	private String operate(final String inputText, final BinaryOperator<Integer> operation, UnaryOperator<Integer> transformation)
	{
		return IntStream.range(0, inputText.length()).mapToObj(index->String.valueOf((char)(int)transformation.apply(getCharacter(inputText, index, operation)))).collect(Collectors.joining());
	}
	
	private int getCharacter(final String inputText, final int index, final BinaryOperator<Integer> operation)
	{
		return operation.apply((int)inputText.charAt(index), (this.key.charAt(index % this.key.length()) - 'a'));
	}
	
	private void checkKey(final String key) throws IllegalArgumentException
	{
		if(key == "" || !key.matches("[a-z]+"))
		{
			throw new IllegalArgumentException();
		}
	}
}