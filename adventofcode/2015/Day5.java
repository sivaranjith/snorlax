package adventofcode.dec2015;

import java.util.regex.Pattern;

import adventofcode.dec2016.Utils;

public class Day5
{

	private static int count1 = 0, count2 = 0;
	
	public static void main(String[] args)
	{
		Utils.fileReader("../dec2015/day5input.txt", (String line)->checkForNiceString(line), ()->printDetails());
	}
	
	private static void checkForNiceString(String line)
	{
		if(!Pattern.compile("ab|cd|pq|xy").matcher(line).find() && (Pattern.compile("([aeiou].*){3}").matcher(line).find() && Pattern.compile("(\\w)\\1").matcher(line).find()))
		{
			++count1;
		}
		
		if(Pattern.compile("(\\w)(\\w).*\\1\\2").matcher(line).find() && Pattern.compile("(\\w).\\1").matcher(line).find())
		{
			++count2;
		}
	}

	private static void printDetails()
	{
		System.out.println(count1 + "\n" + count2);
	}

}
