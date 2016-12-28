package adventofcode.dec2016;

public class Day16
{

	private static final int LENGTH = 35651584;
	private static String input = "10010000000110000", finalString;
	
	public static void main(String[] args)
	{
		dragonCurve();
		calculateCheckSum();
		printDetails();
	}

	private static void printDetails()
	{
		System.out.println(finalString);
	}

	private static void calculateCheckSum()
	{
		StringBuilder sb; 
		while(finalString.length() % 2 == 0)
		{
			sb = new StringBuilder( (finalString.length()/2) + 1);
			for(int i = 0; i < finalString.length(); i += 2)
			{
				if(finalString.charAt(i) == finalString.charAt(i+1))
				{
					sb.append('1');
				}
				else
				{
					sb.append('0');
				}
			}
			finalString = sb.toString();
		}
	}

	private static void dragonCurve()
	{
		String a = input, b;
		while(a.length() < LENGTH)
		{
			b = a;
			b = reverseAndBinaryToggle(b);
			a = a + "0" + b;
		}
		finalString = a.substring(0, LENGTH);
	}

	private static String reverseAndBinaryToggle(String b)
	{
		StringBuilder returnVal = new StringBuilder(b.length());
		for(int i = b.length() - 1; i >= 0; --i)
		{
			returnVal.append(b.charAt(i) == '0' ? '1' : '0');
		}
		return returnVal.toString();
	}

}
