package adventofcode.dec2016;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Day7
{

	public static void main(String[] args)
	{
		BufferedReader br = null;
		try
		{
			br = new BufferedReader(new FileReader(new File("/home/local/ZOHOCORP/siva-2239/workspace/java8/bin/adventofcode/day7input.txt")));
			String line;
			int totalTCL = 0,totalSSL = 0;
			while((line = br.readLine()) != null)
			{
				if(isTCL(line))
				{
					++totalTCL;
				}
				if(isSSL(line))//258
				{
					++totalSSL;
				}
			}
			System.out.println("tcl total: " + totalTCL);
			System.out.println("ssl total: " + totalSSL);
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
	}
	
	private static boolean isTCL(String line)
	{
		String[] split = line.split("\\[\\w+\\]");
		Matcher m = Pattern.compile("\\[([^]]+)\\]").matcher(line);
		for(;m.find();)
		{
			if(isTCLPatternAvailable(m.group(1)))
			{
				return false;
			}
		}
		for(String s : split)
		{
			if(isTCLPatternAvailable(s))
			{						
				return true;
			}
		}
		return false;
	}
	
	private static boolean isSSL(String line)
	{
		String[] split = line.split("\\[\\w+\\]"),hypernet = new String[5];
		Matcher m = Pattern.compile("\\[([^]]+)\\]").matcher(line);
		int k;
		for(k = 0; m.find(); ++k)
		{
			hypernet[k] = m.group(1);
		}
		List<String> l1 = getChars(split, false);
		List<String> l2 = getChars(hypernet, true);
		for(String s : l1)
		{
			if(l2.contains(s))
			{
				return true;
			}
		}
		return false;
	}
	
	private static List<String> getChars(String[] split,boolean shouldReverse)
	{
		List<String> list = new ArrayList<String>();
		for(String s : split)
		{
			if(s == null)
			{
				break;
			}
			for(int i = 0; i + 2 < s.length(); ++i)
			{
				if(s.charAt(i) != s.charAt(i+1) && s.charAt(i+2) == s.charAt(i))
				{
					if(shouldReverse)
					{
						list.add(s.charAt(i + 1) + "" + s.charAt(i));
					}
					else
					{
						list.add(s.charAt(i) + "" + s.charAt(i + 1));
					}
				}
			}
		}
		return list;
	}

	private static boolean isTCLPatternAvailable(String str)
	{
		int i,j;
		for(i = 0,j = 3; j < str.length(); ++i,++j)
		{
			if(str.charAt(i) == str.charAt(j) && str.charAt(i + 1) == str.charAt(j - 1) && str.charAt(i) != str.charAt(i + 1))
			{
				return true;
			}
		}
		return false;
	}

}
