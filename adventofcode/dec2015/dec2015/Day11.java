package adventofcode.dec2015;

final public class Day11
{

	private static final String INPUT = "hxbxwxba";
	private static final char[] newPassword = INPUT.toCharArray();
	
	public static void main(final String[] args)
	{
		controller(newPassword);
		controller(newPassword);
	}
	
	private static void controller(char[] newPassword)
	{
		nextPassword(newPassword);
		printDetails();		
	}
	
	private static void nextPassword(char[] newPassword)
	{
		do
		{
			generateNextPassword(newPassword);
		}
		while(!isValidPassword(newPassword));
	}
	
	private static boolean isValidPassword(char[] newPassword)
	{
		boolean isValid = true;
		int repeatedCharactersCount = 0, continuesChar = 0;
		char lastChar = 0, lastBeforeChar = 0, lastRepeatedChar = 0;
		
		for(int index = 0; index < newPassword.length; ++index)
		{
			if(isInvalidCharacter(newPassword[index]))
			{
				isValid = false;
				break;
			}
			
			if(index != 0 && lastChar == newPassword[index] && lastChar != lastRepeatedChar)//non overlapping
			{
				++repeatedCharactersCount;
				lastRepeatedChar = lastChar;
			}

			if(index > 2 && lastBeforeChar + 1 == lastChar && lastChar + 1 == newPassword[index])
			{
				++continuesChar;
			}

			if(index > 1)
			{
				lastBeforeChar = lastChar;
			}
			lastChar = newPassword[index];
		}
		return isValid && repeatedCharactersCount >= 2 && continuesChar >= 1;
	}
	
	private static void generateNextPassword(char[] newPassword)
	{
		for(int index = newPassword.length - 1; index >= 0; --index)
		{
			if(newPassword[index] != 'z')
			{
				newPassword[index] += 1;
				break;
			}
			else
			{
				newPassword[index] = 'a';
			}
		}
		
		for(int index = 0; index < newPassword.length; ++index)
		{
			if(isInvalidCharacter(newPassword[index]))
			{
				newPassword[index] += 1;
				for(++index; index < newPassword.length; ++index)
				{
					newPassword[index] = 'a';
				}
				break;
			}
		}
	}
	
	private static boolean isInvalidCharacter(char inputChar)
	{
		return inputChar == 'i' || inputChar == 'o' || inputChar == 'l';
	}
	
	private static void printDetails()
	{
		System.out.println(newPassword);
	}
}
