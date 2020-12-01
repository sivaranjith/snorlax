import java.util.function.Predicate;
import java.util.function.Supplier;
import java.util.regex.Pattern;

public final class PhoneNumber
{
	
	private String number;
	private static final Predicate<String> checker = (num)->Pattern.compile("[^0-9]+").matcher(num).find();
	
	public PhoneNumber(final String number) throws IllegalArgumentException
	{
		this.number = number.replaceAll("(\\(|\\)|\\-| |\\.)", "");
		checkNumber();
	}
	
	public String getNumber()
	{
		return this.number;
	}
	
	private void checkNumber() throws IllegalArgumentException
	{
		if(checker.test(this.number))
		{
			throw new IllegalArgumentException(ExceptionMessage.ILLEGAL_CHARACTER);
		}
		else if(this.number.length() != 10)
		{
			if(this.number.length() == 11)
			{
				if(this.number.charAt(0) != '1')
				{
					throw new IllegalArgumentException(ExceptionMessage.NUMBER_IS_11_DIGITS_BUT_DOES_NOT_START_WITH_1);
				}
				else
				{
					this.number = this.number.substring(1);
				}
			}
			else
			{
				throw new IllegalArgumentException(ExceptionMessage.WRONG_LENGTH);
			}
		}
	}
	
	private static final class ExceptionMessage
	{
		static final String ILLEGAL_CHARACTER = "Illegal character in phone number. Only digits, spaces, parentheses, hyphens or dots accepted."; 
		static final String NUMBER_IS_11_DIGITS_BUT_DOES_NOT_START_WITH_1 = "Can only have 11 digits if number starts with '1'";
		static final String WRONG_LENGTH = "Number must be 10 or 11 digits";
	}
}