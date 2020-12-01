import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public final class Crypto
{
	
	private final String plainText;
	private int row, column;
	private final List<String> encryptedTextSegments;
	
	public Crypto(final String inputText)
	{
		this.plainText = inputText.replaceAll("[^a-zA-Z0-9]", "").toLowerCase();

		column = (int)Math.ceil(Math.sqrt(this.plainText.length()));
		row = (int)Math.ceil((this.plainText.length() * 1.0) / column);

		encryptedTextSegments = IntStream.rangeClosed(0, column - 1).mapToObj(this::encryptPlainText).collect(Collectors.toList());
	}
	
	public String getCipherText()
	{
		return getCipher("");
	}
	
	public String getNormalizedCipherText()
	{
		return getCipher(" ");
	}
	
	private String getCipher(final String joiner)
	{
		return this.encryptedTextSegments.stream().collect(Collectors.joining(joiner));
	}

	private String encryptPlainText(final int startingPoint)
	{
		return IntStream.iterate(startingPoint, index->index + column).limit(row).mapToObj(index->index < this.plainText.length() ? String.valueOf(this.plainText.charAt(index)) : "").collect(Collectors.joining());
	}

	public List<String> getPlaintextSegments()
	{
		return IntStream.iterate(0, index->index + column).limit(row).mapToObj(this::getRow).filter(str->!str.isEmpty()).collect(Collectors.toList());
	}
	
	private String getRow(final int startingIndex)
	{
		String returnValue = "";
		if(startingIndex + column <= this.plainText.length())
		{
			returnValue = this.plainText.substring(startingIndex, startingIndex + column);
		}
		else if(startingIndex < this.plainText.length())
		{
			returnValue = this.plainText.substring(startingIndex);
		}
		return returnValue;
	}
	
	public int getSquareSize()
	{
		return this.column;
	}
	
	public String getNormalizedPlaintext()
	{
		return this.plainText;
	}
}
