package adventofcode.dec2015;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.function.BiPredicate;
import java.util.stream.IntStream;

import adventofcode.dec2016.Utils;

public class Day16
{
	
	private static final Map<String, Integer> content = new HashMap<>();
	private static final List<Map<String, Integer>> sueDetails = new ArrayList<>();
	
	public static void main(String... args)
	{
		Utils.fileReader("../dec2015/day16input1.txt", Day16::parseContents, ()->{});
		Utils.fileReader("../dec2015/day16input.txt", Day16::parseInput, ()->{findSue(Day16::partI);findSue(Day16::partII);});
	}

	private static void parseContents(final String contentLine)
	{
		final String[] tokens = contentLine.split(": ");
		content.put(tokens[0].intern(), Integer.parseInt(tokens[1]));
	}
	
	private static void parseInput(final String sueDetailsline)
	{
		final String[] tokens = sueDetailsline.split("(: |, )");
		final Map<String, Integer> sueDetailsMap = new HashMap<>();
		
		IntStream.iterate(1, i->i+2).limit(tokens.length/2).forEach(index->sueDetailsMap.put(tokens[index].intern(), Integer.parseInt(tokens[index + 1])));
		
		sueDetails.add(sueDetailsMap);
	}
	
	private static void findSue(BiPredicate<String, Integer> checker)
	{
		int maxMatch = 0, maxMatchedIndex = -1, tempMatch = 0, index = 0;
		
		for(Map<String, Integer> sue : sueDetails)
		{
			if((tempMatch = getMatches(sue, checker)) > maxMatch || maxMatch == 0)
			{
				maxMatch = tempMatch;
				maxMatchedIndex = index;
			}
			++index;
		}
		
		System.out.println(maxMatchedIndex + 1);
	}
	
	private static int getMatches(Map<String, Integer> sue, BiPredicate<String, Integer> checker)
	{
		Iterator<String> items = sue.keySet().iterator();
		int count = 0;
		
		while(items.hasNext())
		{
			final String item = items.next();
			count += checker.test(item, sue.get(item)) ? 1 : 0;
		}
		
		return count;
	}
	
	private static boolean partI(final String item, final Integer count)
	{
		boolean result = false;
		
		if(count == content.get(item))
		{
			result = true;
		}
		
		return result;
	}
	
	private static boolean partII(final String item, final Integer count)
	{
		boolean result = false;
		
		if(item == "cats" || item == "trees")
		{
			if(count > content.get(item))
			{
				result = true;
			}
		}
		else if(item == "pomeranians" || item == "goldfish")
		{
			if(count < content.get(item))
			{
				result = true;
			}
		}
		else if(count == content.get(item))
		{
			result = true;
		}
		
		return result;
	}
}
