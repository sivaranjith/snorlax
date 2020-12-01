package adventofcode.dec2016;

public class Day9
{
	static long totalLength;
	
	public static void main(String[] args)
	{
		Utils.fileReader("day9input.txt", (String s)->{totalLength = getLength(s);}, ()->printDetails());
		Utils.fileReader("day9input.txt", (String s)->{totalLength = getLength1(s);}, ()->printDetails());
	}
	
	private static long getLength1(String line)
	{
		int x,y,t,i;
		long length = 0;
		String sub,split[];
		for(i = 0; i < line.length(); ++i)
		{
			if(line.charAt(i) == '(')
			{
				t = line.indexOf(')',i);
				sub = line.substring(i+1,t);
				split = sub.split("x");
				x = Integer.parseInt(split[0]);
				y = Integer.parseInt(split[1]);
				sub = line.substring(t+1,t+x+1);
				length += getLength1(sub)*y;
				i = t + x;
			}
			else if(line.charAt(i) != ' ')
			{
				++length;
			}
		}
		return length;
	}

	private static void printDetails()
	{
		System.out.println(totalLength);
	}

	private static int getLength(String line)
	{
		int i,x,y,t,length = 0;
		String sub,split[];
		for(i = 0; i < line.length(); ++i)
		{
			if(line.charAt(i) == '(')
			{
				t = line.indexOf(')', i);
				sub = line.substring(i+1,t);
				split = sub.split("x");
				x = Integer.parseInt(split[0]);
				y = Integer.parseInt(split[1]);
				i = t + x;
				length += x*y;
			}
			else if(line.charAt(i) != ' ')
			{
				++length;
			}
		}
		return length;
	}

}
