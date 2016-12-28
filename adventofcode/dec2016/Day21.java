package adventofcode.dec2016;

import java.util.ArrayList;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Day21
{
	
	private static char[] input="abcdefgh".toCharArray(), input1 = "fbgdceah".toCharArray();
	private static List<String> inputList = new ArrayList<>();

	public static void main(String[] args)
	{
		Utils.fileReader("day21input.txt", (String line)->processInput(line, false), ()->printDetails());
		input = input1;
		Utils.fileReader("day21input.txt", (String line)->inputList.add(line), ()->{processStoredInput();printDetails();});
	}
	
	private static void processStoredInput()
	{
		for(int i = inputList.size() - 1; i >= 0; --i)
		{
			processInput(inputList.get(i), true);
		}
	}

	private static void processInput(String line, boolean isReversed)
	{
		int temp1 = 0, temp2;
		char c1, c2;
		Matcher m = Pattern.compile("\\d+").matcher(line);
		if(m.find())
		{
			temp1 = Integer.parseInt(m.group());
		}
		if(line.contains("swap"))
		{
			if(line.contains("position"))
			{
				m.find();
				temp2 = Integer.parseInt(m.group());
				swapPosition(temp1, temp2);
			}
			else if(line.contains("letter"))
			{
				m = Pattern.compile(" [a-z] ").matcher(line);
				m.find();
				c1 = m.group().charAt(1);
				c2 = line.charAt(line.length() - 1);
				swapLetter(c1, c2);
			}
		}
		else if(line.contains("rotate"))
		{
			if(line.contains("based on position"))
			{
				c2 = line.charAt(line.length() - 1);
				if(!isReversed)
				{
					rotateCharacter(c2);
				}
				else
				{
					reverseRotateCharacter(c2);
				}
			}
			else
			{
				if(!isReversed)
				{
					rotate(temp1, line.contains("right"));
				}
				else
				{
					rotate(temp1, !line.contains("right"));
				}
			}
		}
		else if(line.contains("reverse"))
		{
			m.find();
			temp2 = Integer.parseInt(m.group());
			reverseSubString(temp1, temp2);
		}
		else if(line.contains("move"))
		{
			m.find();
			temp2 = Integer.parseInt(m.group());
			if(!isReversed)
			{
				moveCharacter(temp1, temp2);
			}
			else
			{
				moveCharacter(temp2, temp1);
			}
		}
	}
	
	private static void reverseRotateCharacter(char c2)
	{
		int i, j;
		for(i = 0; i < input.length; ++i)
		{
			if(input[i] == c2)
			{
				break;
			}
		}
		
		if((i&1) == 1)
		{
			j = (i-1)/2;
		}
		else
		{
			if(i == 0)
			{
				j = 7;
			}
			else
			{
				j = i/2 + 3;
			}
		}
		
		i = (input.length + i - j)%input.length;
		
		rotate(i, false);
	}

	private static void swapPosition(int temp1, int temp2)
	{
		char c1 = input[temp1], c2 = input[temp2];
		input[temp1] = c2;
		input[temp2] = c1;
	}

	private static void swapLetter(char temp1, char temp2)
	{
		for(int i = 0; i < input.length; ++i)
		{
			if(input[i] == temp1)
			{
				input[i] = (char)temp2;
			}
			else if(input[i] == temp2)
			{
				input[i] = (char)temp1;
			}
		}
	}

	private static void rotateCharacter(char temp1)
	{
		int i;
		for(i = 0; i < input.length; ++i)
		{
			if(input[i] == temp1)
			{
				break;
			}
		}
		
		if(i >= 4)
		{
			++i;
		}
		rotate(i+1, true);
	}

	private static void rotate(int temp1, boolean isRight)
	{
		if((temp1 %= input.length) == 0)
		{
			return;
		}
		
		char newArray[] = new char[input.length];
		int i;
		
		if(isRight)
		{
			for(i = 0; i < temp1; ++i)
			{
				newArray[temp1 - i - 1] = input[input.length - i -1];
			}
			
			for(; i < input.length; ++i)
			{
				newArray[i] = input[i - temp1];
			}
		}
		else
		{
			for(i = 0; i < temp1; ++i)
			{
				newArray[input.length - temp1 + i] = input[i]; 
			}
			
			for(; i < input.length; ++i)
			{
				newArray[i - temp1] = input[i];
			}
		}
		
		input = newArray;
	}

	private static void reverseSubString(int temp1, int temp2)
	{
		char c;
		for(; temp1 < temp2; ++temp1, --temp2)
		{
			c = input[temp1];
			input[temp1] = input[temp2];
			input[temp2] = c;
		}
	}

	private static void moveCharacter(int temp1, int temp2)
	{
		char c = input[temp1];
		if(temp1 < temp2)
		{
			for(; temp1 < temp2; ++temp1)
			{
				input[temp1] = input[temp1 + 1];
			}
		}
		else if(temp1 > temp2)
		{
			for(; temp1 > temp2; --temp1)
			{
				input[temp1] = input[temp1 - 1];
			}
		}
		input[temp1] = c;
	}

	private static void printDetails()
	{
		System.out.println(new String(input));
	}

}
