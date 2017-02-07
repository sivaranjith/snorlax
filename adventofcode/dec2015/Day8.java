package adventofcode.dec2015;

import java.util.concurrent.atomic.AtomicInteger;

import adventofcode.dec2016.Utils;

public class Day8
{

	private static int totalSize, memorySize, encodedSize;
	
	public static void main(String[] args)
	{
		Utils.fileReader("../dec2015/day8input.txt", (line)->processLine(line), ()->printDetails());
	}

	private static void processLine(String line)
	{
		totalSize += line.length();
		memorySize += processedLength(line) - 2;
		encodedSize += encodedLength(line) + 2;
	}
	
	private static int encodedLength(String line)
	{
		AtomicInteger outputLengh = new AtomicInteger(0);
		line.chars().forEach((c) -> outputLengh.addAndGet(isSpecialCharacter(c) ? 2 : 1));
		return outputLengh.get();
	}
	
	private static int processedLength(String line)
	{
		int outputLength = 0;
		for(int index = 0; index < line.length(); ++index, ++outputLength)
		{
			if(line.charAt(index) == '\\' && index + 1 < line.length())
			{
				if(isSpecialCharacter(line.charAt(index + 1)))
				{
					++index;
				}
				else if(index + 3 < line.length() && (line.charAt(index + 1) == 'x' || line.charAt(index + 1) == 'X') && isHexaDecimal(line.charAt(index + 2)) && isHexaDecimal(line.charAt(index + 3)))
				{
					index += 3;
				}
			}
		}
		return outputLength;
	}
	
	private static boolean isSpecialCharacter(int c)
	{
		return (c == '\"' || c == '\\');
	}
	
	private static boolean isHexaDecimal(char c)
	{
		return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c<= 'F'));
	}
	
	private static void printDetails()
	{
		System.out.println(totalSize - memorySize);
		System.out.println(encodedSize - totalSize);
	}
}
