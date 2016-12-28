package adventofcode.dec2016;

import java.util.ArrayList;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Day15
{
	
	private static List<Disk> container = new ArrayList<>();
	private static int startTime;

	public static void main(String[] args)
	{
		Utils.fileReader("day15input.txt", (String s)->getInput(s), ()->{getInitialTime();printDetails();});
	}

	private static void printDetails()
	{
		System.out.println(startTime);
	}

	private static void getInitialTime()
	{
		Disk d = container.get(0);
		int i, size = container.size(), inc = d.totalPosition;
		startTime = d.totalPosition - 1 - d.initPosition;
		while(true)
		{
			for(i = 0; i < size; ++i)
			{
				if(!isValidTime(i))
				{
					break;
				}
			}
			if(i == size)
			{
				break;
			}
			startTime += inc;
		}
	}

	private static boolean isValidTime(int i)
	{
		Disk d = container.get(i);
		return (d.totalPosition - startTime - d.initPosition - i - 1)%d.totalPosition == 0;
	}

	private static void getInput(String line)
	{
		int totalPosition, initPosition;
		Matcher m = Pattern.compile("\\d+").matcher(line);
		m.find();
		m.find();
		totalPosition = Integer.parseInt(m.group());
		m.find();
		m.find();
		initPosition = Integer.parseInt(m.group());
		container.add(new Disk(totalPosition, initPosition));
	}
	
	private static class Disk
	{
		int totalPosition,initPosition;
		
		public Disk(int totalPosition, int initPosition)
		{
			this.totalPosition = totalPosition;
			this.initPosition = initPosition;
		}
		
		@Override
		public boolean equals(Object o)
		{
			if(o instanceof Disk)
			{
				return this.totalPosition == ((Disk)o).totalPosition && this.initPosition == ((Disk)o).initPosition;
			}
			return false;
		}
	}

}
