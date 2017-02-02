package adventofcode.dec2015;

import java.util.function.Predicate;

import adventofcode.dec2016.Utils;

public class Day4
{
	
	private static final String INPUT = "yzbqklnj";

	public static void main(String[] args)
	{
		controller((String hashedText)->{return hashedText.startsWith("00000");});
		controller((String hashedText)->{return hashedText.startsWith("000000");});
	}

	private static void controller(Predicate<String> validator)
	{
		long lowestIndex;
		for(lowestIndex = 0; lowestIndex >= 0; ++lowestIndex)
		{
			if(validator.test(Utils.md5(INPUT + lowestIndex)))
			{
				break;
			}
		}
		System.out.println(lowestIndex);
	}
}
