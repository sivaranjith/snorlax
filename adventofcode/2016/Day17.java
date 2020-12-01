package adventofcode.dec2016;

import java.util.HashMap;
import java.util.Iterator;
import java.util.LinkedHashMap;

public class Day17
{

	private static final String PASS_CODE = "pslxynzg";
	private static String path = "";
	private static int longestPathLength = 0;
	
	public static void main(String[] args)
	{
		breathFirstSearch();
		deapthFirstSearch("", 0, 0);
		printDetails();
	}
	
	private static void deapthFirstSearch(String currentTravellingPath, int x, int y)
	{
		if(x == 3 && y == 3)
		{
			if(longestPathLength < currentTravellingPath.length())
			{
				longestPathLength = currentTravellingPath.length();
			}
			return;
		}
		
		String md5String = Utils.md5(PASS_CODE + currentTravellingPath);
		
		if(md5String.charAt(0) >= 'b' && md5String.charAt(0) <= 'f' && x != 0)
		{
			deapthFirstSearch(currentTravellingPath + 'U', x - 1 , y);
		}
		
		if(md5String.charAt(1) >= 'b' && md5String.charAt(1) <= 'f' && x != 3)
		{
			deapthFirstSearch(currentTravellingPath + 'D', x + 1, y);
		}
		
		if(md5String.charAt(2) >= 'b' && md5String.charAt(2) <= 'f' && y != 0)
		{
			deapthFirstSearch(currentTravellingPath + 'L', x, y - 1);
		}
		
		if(md5String.charAt(3) >= 'b' && md5String.charAt(3) <= 'f' && y != 3)
		{
			deapthFirstSearch(currentTravellingPath + 'R', x, y + 1);
		}
		return;
	}

	private static void printDetails()
	{
		System.out.println(path + "/////" + longestPathLength);
	}
	
	private static void breathFirstSearch()
	{
		int length = 0;
		String md5String, currentTravellingPath;
		HashMap<Point, String> nextDirection = new LinkedHashMap<>(), temp = null;
		Point p;
		
		nextDirection.put(new Point(0,0),"");
		
		while(path == "" && !nextDirection.isEmpty())
		{
			temp = new LinkedHashMap<>();
			Iterator<Point> it = nextDirection.keySet().iterator();
			
			while(it.hasNext())
			{
				p = it.next();
				currentTravellingPath = nextDirection.get(p);
				
				if(p.x == 3 && p.y == 3)
				{
					path = currentTravellingPath;
					if(length < path.length())
					{
						length = path.length();
					}
					break;
				}
				
				md5String = Utils.md5(PASS_CODE + currentTravellingPath);
				
				if(md5String.charAt(0) >= 'b' && md5String.charAt(0) <= 'f' && p.x != 0)
				{
					temp.put(new Point(p.x-1, p.y), currentTravellingPath + 'U');
				}
				
				if(md5String.charAt(1) >= 'b' && md5String.charAt(1) <= 'f' && p.x != 3)
				{
					temp.put(new Point(p.x+1, p.y), currentTravellingPath + 'D');
				}
				
				if(md5String.charAt(2) >= 'b' && md5String.charAt(2) <= 'f' && p.y != 0)
				{
					temp.put(new Point(p.x, p.y-1), currentTravellingPath + 'L');
				}
				
				if(md5String.charAt(3) >= 'b' && md5String.charAt(3) <= 'f' && p.y != 3)
				{
					temp.put(new Point(p.x, p.y+1), currentTravellingPath + 'R');
				}
			}
			nextDirection = temp;
		}
	}
	
	private static class Point
	{
		int x, y;
		public Point(int x, int y)
		{
			this.x = x;
			this.y = y;
		}
	}

}
