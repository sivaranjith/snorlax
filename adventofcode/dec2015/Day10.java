package adventofcode.dec2015;

public final class Day10
{

	private static String inputString = "1113122113"; 
	private static final int FIRST_ITERATION_COUNT = 40;
	private static final int SECOND_ITERATION_COUNT = 50;
	
	public static void main(final String[] args)
	{
		processString(inputString, FIRST_ITERATION_COUNT);
		processString(inputString, SECOND_ITERATION_COUNT);
	}

	private static void processString(String inputString, final int iterationsCount)
	{
		for(int iteration = 0; iteration < iterationsCount; ++iteration)
		{
			inputString = lookAndSaySequence(inputString);
		}
		
		System.out.println(inputString.length());
	}
	
	private static String lookAndSaySequence(final String inputString)
	{
		final StringBuffer sb = new StringBuffer(inputString.length()*2);
		int oldValue = -1, newValue = 0, count = 0;

		for(int index = 0; index < inputString.length(); ++index)
		{
			newValue = inputString.charAt(index) - '0';
			
			if(oldValue == -1)
			{
				oldValue = newValue;
			}

			if(oldValue != newValue)
			{
				sb.append(count + "" + oldValue);
				oldValue = newValue;
				count = 1;
			}
			else if(oldValue == newValue)
			{
				++count;
			}
		}
		sb.append(count + "" + oldValue);
		return sb.toString();
	}
}
