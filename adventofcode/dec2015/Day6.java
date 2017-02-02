package adventofcode.dec2015;

import java.util.function.Predicate;
import java.util.function.UnaryOperator;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import adventofcode.dec2016.Utils;

public class Day6
{
	
	private static final int ROW_SIZE = 1000, COLUMN_SIZE = 1000;
	private static boolean[][] booleanGrid = new boolean[ROW_SIZE][COLUMN_SIZE];
	private static int startRow, startColumn, endRow, endColumn, grid[][] = new int[ROW_SIZE][COLUMN_SIZE];

	public static void main(String[] args)
	{
		Utils.fileReader("../dec2015/day6input.txt", (String line)->proccessInput(line), ()->printDetails());
	}

	private static void proccessInput(String line)
	{
		Matcher m = Pattern.compile("\\d+").matcher(line);
		m.find();
		startRow = Integer.parseInt(m.group());
		m.find();
		startColumn = Integer.parseInt(m.group());
		m.find();
		endRow = Integer.parseInt(m.group());
		m.find();
		endColumn = Integer.parseInt(m.group());
		if(line.startsWith("turn on"))
		{
			gridLightProcess((Boolean lightState)->true);
			gridLightProcessSlide((Integer lightVal)->lightVal + 1);
		}
		else if(line.contains("turn off"))
		{
			gridLightProcess((Boolean lightState)->false);
			gridLightProcessSlide((Integer lightVal)->lightVal < 1 ? 0 : lightVal - 1);
		}
		else if(line.contains("toggle"))
		{
			gridLightProcess((Boolean lightState)->!lightState);
			gridLightProcessSlide((Integer lightVal)->lightVal + 2);
		}
	}
	
	private static void gridLightProcessSlide(UnaryOperator<Integer> bulbState)
	{
		int rowIndex, columnIndex;
		for(rowIndex = startRow; rowIndex <= endRow; ++rowIndex)
		{
			for(columnIndex = startColumn; columnIndex <= endColumn; ++columnIndex)
			{
				grid[rowIndex][columnIndex] = bulbState.apply(grid[rowIndex][columnIndex]);
			}
		}
	}
	
	private static void gridLightProcess(Predicate<Boolean> bulbState)
	{
		int rowIndex, columnIndex;
		for(rowIndex = startRow; rowIndex <= endRow; ++rowIndex)
		{
			for(columnIndex = startColumn; columnIndex <= endColumn; ++columnIndex)
			{
				booleanGrid[rowIndex][columnIndex] = bulbState.test(booleanGrid[rowIndex][columnIndex]);
			}
		}
	}

	private static void printDetails()
	{
		int count = 0, rowIndex = 0, columnIndex = 0;
		long totalBrightness = 0;
		for(; rowIndex < ROW_SIZE; ++rowIndex)
		{
			for(columnIndex = 0; columnIndex < COLUMN_SIZE; ++columnIndex)
			{
				if(booleanGrid[rowIndex][columnIndex])
				{
					++count;
				}
				totalBrightness += grid[rowIndex][columnIndex];
			}
		}
		System.out.println(count + "\n" + totalBrightness);
	}

}
