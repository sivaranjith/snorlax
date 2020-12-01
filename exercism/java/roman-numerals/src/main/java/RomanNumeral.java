import java.util.Map;
import java.util.stream.Collectors;
import java.util.stream.IntStream;
import java.util.HashMap;

public final class RomanNumeral
{
	
	private final int arabicNumber;
	
	public RomanNumeral(final int arabicNumber)
	{
		this.arabicNumber = arabicNumber;
	}
	
	public String getRomanNumeral()
	{
		return computeRomanNumeral(); 
	}
	
	private String computeRomanNumeral()
	{
		String result = "";
		
		result += getRomalNumeralForDigit(1000, "M", "", "");
		
		result += getRomalNumeralForDigit(100, "C", "D", "M");
		
		result += getRomalNumeralForDigit(10, "X", "L", "C");
		
		result += getRomalNumeralForDigit(1, "I", "V", "X");
		
		return result;
	}
	
	private String getRomalNumeralForDigit(final int divider, final String val1, final String val2, final String val3)
	{
		int digit = (this.arabicNumber/divider)%10;
		String result = "";

		if(digit == 0)
		{
		}
		else if(digit < 4)
		{
			result = multiplyString(val1, digit);
		}
		else if(digit == 4)
		{
			result = val1 + val2;
		}
		else if(digit == 5)
		{
			result = val2;
		}
		else if(digit < 9)
		{
			result = val2 + multiplyString(val1, digit - 5);
		}
		else if(digit == 9)
		{
			result = val1 + val3;
		}
		
		return result;
	}
	
	private String multiplyString(final String val, final int digit)
	{
		return IntStream.range(0, digit).mapToObj(__->val).collect(Collectors.joining());
	}
}