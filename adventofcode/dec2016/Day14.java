package adventofcode.dec2016;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Day14
{
	private static List<Triplet> container;  
	private static final String SALT = "zpqevtbw";
	private static int key;

	public static void main(String[] args)
	{
		generateKeys(1);
		generateKeys(2017);
	}
	
	private static void generateKeys(int noOfHashes)
	{
		int i = 0 , j, returnVal = 0;
		String s;
		Matcher m;

		key = 0;
		container = new ArrayList<>();
		
		while(key < 64)
		{
			s = SALT + i;
			for(j = 0; j < noOfHashes ; ++j)
			{
				s = Utils.md5(s);
			}
			m = Pattern.compile("(\\d|a|b|c|d|e|f)\\1{2}").matcher(s);
			if(m.find())
			{
				container.add(new Triplet(i, m.group().charAt(0)));
			}
			
			returnVal = getKeysCount(s,i);
			++i;
		}
		System.out.println(returnVal);
	}
	
	private static int getKeysCount(String s,int i)
	{
		int returnVal = 0;
		Triplet t;
		Iterator<Triplet> tripletIt = container.iterator();
		Matcher m;
		while(tripletIt.hasNext())
		{
			t = tripletIt.next();
			m = Pattern.compile("(" + t.c + "){5}").matcher(s);
			if(t.i != i && t.i + 1000 >= i && m.find())
			{
				++key;
				returnVal = t.i;
				if(key == 64)
				{
					break;
				}
				tripletIt.remove();
			}
			else if(t.i + 1000 == i)
			{
				tripletIt.remove();
			}
		}
		return returnVal;
	}
	
	private static class Triplet
	{
		char c;
		int i;
		public Triplet(int i,char c)
		{
			this.i = i;
			this.c = c;
		}
		
		@Override
		public boolean equals(Object o)
		{
			if(o instanceof Triplet)
			{
				return this.i == ((Triplet)o).i && this.c == ((Triplet)o).c; 
			}
			return false;
		}
		
		@Override
		public int hashCode()
		{
			return c^i;
		}
	}

}
