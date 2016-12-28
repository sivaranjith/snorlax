package adventofcode.dec2016;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Day10
{
	private static final int findValue1 = 61,findValue = 17;
	private static boolean isFound = false;
	private static Map<Integer, List<Integer>> hmBot = new HashMap<>(250), hmOutput = new LinkedHashMap<>(250);
	private static Map<Integer, String> container = new LinkedHashMap<>();
	private static List<Integer> bots = new ArrayList<>();
	private static int lastSize = -1;
	private static long product = 1;
	
	public static void main(String[] args)
	{
		Utils.fileReader("day10input.txt",(String s)->evaluateInstructions(s,true),()->calculateAndPrintDetails());
	}
	
	private static void calculateAndPrintDetails()
	{
		if(!isFound)
		{
			processContainer();
		}
		System.out.println(bots);
		for(Integer i = 0; i < 3; ++i)
		{
			List<Integer> l = hmOutput.get(i);
			if(l != null)
			{
				for(Integer output : l)
				{
					product *= output;
				}
			}
			if(i == 2)
			{
				break;
			}
		}
		System.out.println(product);
	}

	private static void processContainer()
	{
		if(container.isEmpty() || container.size() == lastSize)
		{
			return;
		}
		lastSize = container.size();

		String line;
		Iterator<Integer> it = container.keySet().iterator();
		for(;it.hasNext();)
		{
			Integer bot = it.next();
			line = container.get(bot);
			int evaluationStatus = evaluateInstructions(line,false);
			if(evaluationStatus == 1)
			{
				container.clear();
				return;
			}
			else if(evaluationStatus == 2)
			{
				it.remove();
			}
		}
		processContainer();
	}

	private static int evaluateInstructions(String line,boolean shouldInsert)
	{
		int bot,value;
		Matcher m = Pattern.compile("\\d+").matcher(line);
		
		if(line.contains(" goes to bot "))
		{
			m.find();
			value = Integer.parseInt(m.group());
			m.find();
			bot = Integer.parseInt(m.group());
			List<Integer> l = addToBot(bot,value);
			
			if(isConditionSatisfied(l))
			{
				bots.add(bot);
				return 2;
			}
		}
		else if(line.contains("gives low to"))
		{
			m.find();
			bot = Integer.parseInt(m.group());
			List<Integer> l = hmBot.get(bot);
			
			if(l == null || l.size() != 2)
			{
				if(shouldInsert)
				{
					container.put(bot, line);
				}
				return 0;
			}
			
			m.find();
			value = Integer.parseInt(m.group());
			m.find();
			int value1 = Integer.parseInt(m.group());
			
			l = putValueAway(line,bot,value,"low");
			if(isConditionSatisfied(l))
			{
				bots.add(value);
				return 2;
			}
			
			l = putValueAway(line,bot,value1,"high");
			if(isConditionSatisfied(l))
			{
				bots.add(value1);
				return 2;
			}
		}
		return 2;
	}

	private static List<Integer> putValueAway(String line, int bot, int value, String chipType)
	{
		if(line.contains(chipType + " to bot"))
		{
			return addToBot(value, removeBotValue(bot, chipType));
		}
		else
		{
			return addToOutput(value, removeBotValue(bot, chipType));
		}
	}
	
	private static int removeBotValue(int bot,String chipType)
	{
		if(chipType.equals("low"))
		{
			return hmBot.get(bot).remove(1);
		}
		else
		{
			return hmBot.get(bot).remove(0);
		}
	}

	private static List<Integer> addToOutput(int bot,int value)
	{
		return addToMap(hmOutput,bot,value);
	}
	
	private static List<Integer> addToBot(int bot, int value)
	{
		return addToMap(hmBot,bot,value);
	}
	
	private static List<Integer> addToMap(Map<Integer, List<Integer>> hm,int bot, int value)
	{
		List<Integer> l = hm.get(bot);
		if(l == null)
		{
			l = new ArrayList<>();
			hm.put(bot, l);
			l.add(value);
		}
		else
		{
			if(l.get(0) > value)
			{
				l.add(1,value);
			}
			else
			{
				l.add(0,value);
			}
		}
		return l;		
	}

	private static boolean isConditionSatisfied(List<Integer> l)
	{
		if(l.size() == 2 && (l.contains(findValue) && l.contains(findValue1)))
		{
			return true;
		}
		return false;
	}

}
