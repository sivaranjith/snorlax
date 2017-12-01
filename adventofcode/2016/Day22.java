package adventofcode.dec2016;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.Iterator;
import java.util.List;
import java.util.Set;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Day22
{

	private static List<Node> container = new ArrayList<Node>();
	private static int viablePairCount = 0, stepsCount = 0, x, y;
	private static final int MAX_X = 34, MAX_Y = 30, INITIAL_X = MAX_X - 1, INITIAL_Y = 0, FINAL_X = 0, FINAL_Y = 0;
	private static final boolean isVisited[][] = new boolean[MAX_X][MAX_Y];
	
	public static void main(String[] args)
	{
		Utils.fileReader("day22input.txt", (String line)->parseInput(line), ()->{findViablePairs();findStepsCount();printDetails();});
	}
	
	private static void parseInput(String line)
	{
		if(!line.startsWith("/dev"))
		{
			return;
		}
		
		Node nodeDetails = new Node();
		Matcher m = Pattern.compile("\\d+").matcher(line);
		m.find();
		nodeDetails.x = Integer.parseInt(m.group());
		m.find();
		nodeDetails.y = Integer.parseInt(m.group());
		m.find();
		nodeDetails.size = Integer.parseInt(m.group());
		m.find();
		nodeDetails.used = Integer.parseInt(m.group());
		m.find();
		nodeDetails.available = Integer.parseInt(m.group());
		m.find();
		nodeDetails.usage = Integer.parseInt(m.group());
		
		container.add(nodeDetails);
	}
	
	private static void findViablePairs()
	{
		int i, j;
		for(i = 0; i < container.size(); ++i)
		{
			for(j = 0; j < container.size(); ++j)
			{
				if(i != j && container.get(i).isViable(container.get(j)))
				{
					++viablePairCount;
				}
			}
		}
	}
	
	private static void findStepsCount()
	{
		findInitialLocation();
		
		char[] shortestPathIntToFinal = getShortestPath(INITIAL_X, INITIAL_Y, FINAL_X, FINAL_Y), tempPath = null;
		int i, mx = INITIAL_X, my= INITIAL_Y;

		clearVisitedMatrix();
		if(shortestPathIntToFinal[0] == 'L')
		{
			tempPath = getShortestPath(x, y, INITIAL_X - 1, INITIAL_Y);
		}
		else if(shortestPathIntToFinal[0] == 'R')
		{
			tempPath = getShortestPath(x, y, INITIAL_X + 1, INITIAL_Y);
		}
		else if(shortestPathIntToFinal[0] == 'U')
		{
			tempPath = getShortestPath(x, y, INITIAL_X, INITIAL_Y - 1);
		}
		else if(shortestPathIntToFinal[0] == 'D')
		{
			tempPath = getShortestPath(x, y, INITIAL_X, INITIAL_Y + 1);
		}
		
		Point p = Node.move(x, y, tempPath);
		
		x = p.x;
		y = p.y;
		stepsCount += tempPath.length;
		
		for(i = 1; i < shortestPathIntToFinal.length; ++i)
		{
			container.get(x*MAX_Y + y).moveFromNode(container.get(mx*MAX_Y + my));
			++stepsCount;
			
			clearVisitedMatrix();
			isVisited[x][y] = true;
			
			if(shortestPathIntToFinal[i] == 'L')
			{
				tempPath = getShortestPath(mx, my, x - 1, y);
			}
			else if(shortestPathIntToFinal[i] == 'R')
			{
				tempPath = getShortestPath(mx, my, x + 1, y);
			}
			else if(shortestPathIntToFinal[i] == 'U')
			{
				tempPath = getShortestPath(mx, my, x, y - 1);
			}
			else if(shortestPathIntToFinal[i] == 'D')
			{
				tempPath = getShortestPath(mx, my, x, y + 1);
			}
			
			p = Node.move(mx, my, tempPath);
			
			mx = x;
			my = y;
			x = p.x;
			y = p.y;
			stepsCount += tempPath.length;
			
		}
		
		container.get(x*MAX_Y + y).moveFromNode(container.get(mx*MAX_Y + my));
		++stepsCount;
	}
	
	private static char[] getShortestPath(int startX, int startY, int endX, int endY)
	{
		Set<Point> temp1 = new HashSet<>(), temp2;
		Point p = null;
		
		temp1.add(new Point(startX, startY, ""));
		isVisited[startX][startY] = true;
		
		while(!temp1.isEmpty())
		{
			temp2 = new HashSet<>();
			Iterator<Point> pointIt = temp1.iterator();

			while(pointIt.hasNext())
			{
				p = pointIt.next();
			
				if(p.x == endX && p.y == endY)
				{
					return p.path.toCharArray();
				}
				if(p.x != 0 && !isVisited[p.x - 1][p.y] && container.get(p.x * MAX_Y + p.y).isMoveable(container.get((p.x - 1) * MAX_Y + p.y)))
				{
					isVisited[p.x - 1][p.y] = true;
					temp2.add(new Point(p.x - 1, p.y, p.path + "L"));
				}
				if(p.x < MAX_X - 1 && !isVisited[p.x + 1][p.y] && container.get(p.x * MAX_Y + p.y).isMoveable(container.get((p.x + 1)*MAX_Y + p.y)))
				{
					isVisited[p.x + 1][p.y] = true;
					temp2.add(new Point(p.x + 1, p.y, p.path + "R"));
				}
				if(p.y != 0 && !isVisited[p.x][p.y - 1] && container.get(p.x * MAX_Y + p.y).isMoveable(container.get(p.x * MAX_Y + p.y - 1)))
				{
					isVisited[p.x][p.y - 1] = true;
					temp2.add(new Point(p.x, p.y - 1, p.path + "U"));
				}
				if(p.y < MAX_Y - 1 && !isVisited[p.x][p.y + 1] && container.get(p.x * MAX_Y + p.y).isMoveable(container.get(p.x * MAX_Y + p.y + 1)))
				{
					isVisited[p.x][p.y + 1] = true;
					temp2.add(new Point(p.x, p.y + 1, p.path + "D"));
				}
			}
			temp1 = temp2;
		}
		
		p.x = 1/0;
		return null;
	}
	
	private static void findInitialLocation()
	{
		for(x = 0; x < MAX_X; ++x)
		{
			for(y = 0; y < MAX_Y; ++y)
			{
				if(container.get(x*MAX_Y + y).isEmpty())
				{
					return;
				}
			}
		}
		x = 1/0;
	}
	
	private static void clearVisitedMatrix()
	{
		for(int i = 0, j; i < MAX_X; ++i)
		{
			for(j = 0; j < MAX_Y; ++j)
			{
				isVisited[i][j] = false;
			}
		}
	}
	
	private static void printDetails()
	{
		System.out.println(viablePairCount + ";;;;;;RESULT;;;;;;" + stepsCount);
	}
	
	private static class Node
	{
		int x, y, size, used, available, usage;
		
		public boolean isViable(Node otherNode)
		{
			return this.used > 0 && this.used <= otherNode.available;
		}
		
		public boolean isMoveable(Node otherNode)
		{
			return this.size >= otherNode.used;
		}
		
		public boolean isEmpty()
		{
			return this.used == 0;
		}
		
		public void moveFromNode(Node otherNode)
		{
			if(otherNode.used > this.size)
			{
				this.used = 1/0;
			}
			this.used = otherNode.used;
			otherNode.used = 0;
		}
		
		public static Point move(int x, int y, char[] movePath)
		{
			int i;
			for(i = 0; i < movePath.length; ++i)
			{
				if(movePath[i] == 'L')
				{
					container.get(x*MAX_Y + y).moveFromNode(container.get((x-1)*MAX_Y + y));
					--x;
				}
				else if(movePath[i] == 'R')
				{
					container.get(x*MAX_Y + y).moveFromNode(container.get((x+1)*MAX_Y + y));
					++x;
				}
				else if(movePath[i] == 'U')
				{
					container.get(x*MAX_Y + y).moveFromNode(container.get(x*MAX_Y + y - 1));
					--y;
				}
				else if(movePath[i] == 'D')
				{
					container.get(x*MAX_Y + y).moveFromNode(container.get(x*MAX_Y + y + 1));
					++y;
				}
			}
			return new Point(x,y,"");
		}
		
		@Override
		public String toString()
		{
			return this.x + "::" + this.y + "::" + this.size + "::" + this.used + "::" + this.available + "::" + this.usage;
		}
	}

	private static class Point
	{
		int x, y;
		String path;
		
		public Point(int x, int y, String path)
		{
			this.x = x;
			this.y = y;
			this.path = path;
		}
		
		@Override
		public boolean equals(Object o)
		{
			if(o instanceof Point)
			{
				Point other = (Point)o;
				return this.x == other.x && this.y == other.y;
			}
			return false;
		}
		
		@Override
		public int hashCode()
		{
			return x^y;
		}
		
		@Override
		public String toString()
		{
			return x + "//" + y + "//" + path;
		}
		
	}
	
}
