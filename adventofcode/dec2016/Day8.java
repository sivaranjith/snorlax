package adventofcode.dec2016;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Day8
{
	static int display[][] = new int[6][50],x,y,temp[] = new int[50];
	final static int ROW_SIZE = 6, COLUMN_SIZE = 50;
	
	public static void main(String[] args)
	{
		Utils.fileReader("day8input.txt", (String s)->operations(s), ()->printDetails());
	}

	private static void printDetails()
	{
		int i,j;
		for(i = 0,x = 0; i < ROW_SIZE; ++i)
		{
			for(j = 0; j < COLUMN_SIZE; ++j)
			{
				if(display[i][j] == 1)
				{
					System.out.print("#");
					++x;
				}
				else
				{
					System.out.print(".");
				}
			}
			System.out.println();
		}
		System.out.println(x);
	}
	
	private static void operations(String line)
	{
		if(line.startsWith("rect"))
		{
			rect(line);
		}
		else if(line.startsWith("rotate"))
		{
			rotate(line);
		}
	}

	private static void rotate(String line)
	{
		Matcher m = Pattern.compile("\\d+ by \\d+").matcher(line);
		m.find();
		String[] split = m.group(0).split(" by ");
		x = Integer.parseInt(split[0]);
		y = Integer.parseInt(split[1]);
		if(line.contains("column"))
		{
			rotateDown(line);
		}
		else if(line.contains("row"))
		{
			rotateRight(line);
		}
	}

	private static void rect(String line)
	{
		int i,j;
		Matcher m = Pattern.compile("\\d+x\\d+").matcher(line);
		m.find();
		String[] split = m.group(0).split("x");
		x = Integer.parseInt(split[0]);
		y = Integer.parseInt(split[1]);
		for(i = 0; i < y; ++i)
		{
			for(j = 0; j < x; ++j)
			{
				display[i][j] = 1;
			}
		}
	}
	
	private static void rotateDown(String line)
	{
		int i;
		for(i = 0; i < y; ++i)
		{
			temp[y-i-1] = display[ROW_SIZE - 1 - i][x];
		}
		for(i = ROW_SIZE-1-y; i >= 0; --i)
		{
			display[i+y][x] = display[i][x];
		}
		for(i = 0; i < y; ++i)
		{
			display[i][x] = temp[i];
		}
	}

	private static void rotateRight(String line)
	{
		int i;
		for(i = 0; i < y; ++i)
		{
			temp[y-i-1] = display[x][COLUMN_SIZE-1-i];
		}
		for(i = COLUMN_SIZE-1-y; i >= 0; --i)
		{
			display[x][i+y] = display[x][i];
		}
		for(i = 0; i < y; ++i)
		{
			display[x][i] = temp[i];
		}
	}
	
}
