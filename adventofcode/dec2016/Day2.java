package adventofcode.dec2016;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;

public class Day2
{

	public static void main(String[] args)
	{
		System.out.println(getBathroomCode());
	}

	private static StringBuilder getBathroomCode()
	{
		StringBuilder sb = new StringBuilder();
		BufferedReader br = null;
		try
		{
			br = new BufferedReader(new FileReader(new File("/home/local/ZOHOCORP/siva-2239/workspace/java8/bin/adventofcode/day2input.txt")));
			String line;
			int x = 2, y = 0, index;
			char c,keypad[][] = new char[5][5];
			keypad[0][2] = '1';
			keypad[1][1] = '2';
			keypad[1][2] = '3';
			keypad[1][3] = '4';
			keypad[2][0] = '5';
			keypad[2][1] = '6';
			keypad[2][2] = '7';
			keypad[2][3] = '8';
			keypad[2][4] = '9';
			keypad[3][1] = 'A';
			keypad[3][2] = 'B';
			keypad[3][3] = 'C';
			keypad[4][2] = 'D';
			while((line = br.readLine()) != null)
			{
				for(index = 0; index < line.length(); ++index)
				{
					c = line.charAt(index);
					if(c == 'D' && x != 4 && keypad[x+1][y] != '\u0000')
					{
						++x;
					}
					else if(c == 'U' && x != 0 && keypad[x-1][y] != '\u0000')
					{
						--x;
					}
					else if(c == 'R' && y != 4 && keypad[x][y+1] != '\u0000')
					{
						++y;
					}
					else if(c == 'L' && y != 0 && keypad[x][y-1] != '\u0000')
					{
						--y;
					}
				}
				sb.append(keypad[x][y]);
				System.out.println();
			}
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
		finally
		{
			try
			{
				if(br != null)
				{
					br.close();
				}				
			}
			catch(Exception e)
			{
				e.printStackTrace();
			}
		}
		return sb;
	}

}
