package adventofcode.dec2016;

import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;

public class Day20
{

	private static long minVal = -1, maxVal = -1, allowedIps = 0;
	private static List<Range> input = new LinkedList<>();
	
	public static void main(String[] args)
	{
		Utils.fileReader("day20input.txt", (String s)->{processInput(s);}, ()->{calculateResult();printDetails();});
	}

	private static void processInput(String line)
	{
		String split[] = line.split("-");
		insertInIncreasingOrder(Long.parseLong(split[0]), Long.parseLong(split[1]));
	}
	
	private static void calculateResult()
	{
		Range rangeObj = null;
		boolean isFirstIpFound = false;
		int i;
		long temp1, temp2;
		
		while(input.size() > 0)
		{
			rangeObj = getRange(0);
			i = rangeObj.inputIndex;
			temp1 = rangeObj.minVal;
			temp2 = rangeObj.maxVal;
			if(!isFirstIpFound)
			{
				minVal = temp1;
				maxVal = temp2;
				isFirstIpFound = true;
			}
			
			if(i != input.size())
			{
				allowedIps += input.get(i).minVal - temp2 - 1;
			}
			
			while(i-- > 0)
			{
				input.remove(0);
			}
		}
		
		temp1 = Long.valueOf(9) - rangeObj.maxVal;
		if(temp1 > 0)
		{
			allowedIps += temp1;
		}
		
	}
	
	private static Range getRange(int i)
	{
		Range rangeObj = input.get(i);
		long minVal = rangeObj.minVal, maxVal = rangeObj.maxVal;
		
		for(; i < input.size(); ++i)
		{
			rangeObj = input.get(i);
			if(maxVal + 1 < rangeObj.minVal)
			{
				break;
			}
			else if(maxVal < rangeObj.maxVal)
			{
				maxVal = rangeObj.maxVal;
			}
		}
		return new Range(minVal, maxVal, i);
	}
	
	private static void printDetails()
	{
		if(minVal != 0)
		{
			System.out.println("min ip::" + 0);
		}
		else if(maxVal < Integer.MAX_VALUE)
		{
			System.out.println("min ip::" + (maxVal + 1));
		}
		
		System.out.println("allowed::" + allowedIps);
	}
	
	private static void insertInIncreasingOrder(long startingRange, long endingRange)
	{
		Range rangeObj;
		Iterator<Range> rangeIt = input.iterator();
		int i = 0;
		while(rangeIt.hasNext())
		{
			rangeObj = rangeIt.next();
			if(rangeObj.minVal == startingRange)
			{
				if(rangeObj.maxVal < endingRange)
				{
					rangeObj.maxVal = endingRange;
				}
				else
				{
					return;
				}
			}
			else if(rangeObj.minVal > startingRange)
			{
				break;
			}
			++i;
		}
		input.add(i, new Range(startingRange, endingRange, i));
	}

	
	private static class Range
	{
		long minVal, maxVal;
		int inputIndex;
		
		public Range(long minVal,long maxVal, int inputIndex)
		{
			this.minVal = minVal;
			this.maxVal = maxVal;
			this.inputIndex = inputIndex;
		}
		
		@Override
		public String toString()
		{
			return this.minVal + "::" + this.maxVal;
		}
	}
}
