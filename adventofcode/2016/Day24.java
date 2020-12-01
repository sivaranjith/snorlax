package adventofcode.dec2016;

import java.util.Arrays;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Set;

public class Day24
{
	private static int ROW_SIZE = 37, COLUMN_SIZE = 183, NO_OF_VALUES = 8;
	private static char grid[][] = new char[ROW_SIZE][COLUMN_SIZE];
	private static int i = 0, minimumSteps = 0, x, y;
	private static boolean visitedIndex[] = new boolean[NO_OF_VALUES];
	
	public static void main(String... args)
	{
		Utils.fileReader("day24input.txt", (String line)->inputParser(line), ()->{findInitialPosition();findShortestPathLength(false);printDetails();});
	}
	
	private static void inputParser(String line)
	{
		grid[i++] = line.toCharArray();
	}
	
	private static int findShortestPathLength(boolean isRecursiveCall)
	{
		int x = 0, y = 0, steps = 0;
		Set<Point> temp1 = new HashSet<>(), temp2, minPoints = new HashSet<>();
		boolean isVisited[][] = new boolean[ROW_SIZE][COLUMN_SIZE], tempVisited[], shouldChange;
		Point p = new Point(Day24.x, Day24.y, 0);
		
		temp1.add(p);
		isVisited[p.x][p.y] = true;
		visitedIndex[0] = true;
		
		while(!temp1.isEmpty())
		{
			temp2 = new HashSet<>();
			Iterator<Point> pointIt = temp1.iterator();
			
			shouldChange = false;
			while(pointIt.hasNext())
			{
				p = pointIt.next();
				x = p.x;
				y = p.y;
				steps = p.steps;
				isVisited[x][y] = true;
				
				if(isNumberAvailable(x, y) && !visitedIndex[grid[x][y] - '0'])
				{
					shouldChange = true;
					minPoints.add(new Point(x, y, steps));
					visitedIndex[grid[x][y] - '0'] = true;
					System.out.println(steps + ";;" + grid[x][y]);
					if(!isRecursiveCall && isFullyVisited(visitedIndex) && (minimumSteps == 0 || minimumSteps > steps))
					{
						steps = minimumSteps;
					}
				}
				
				if(minPoints.isEmpty())
				{
					if(!isVisited[x - 1][y] && isMoveable(x - 1, y))
					{
						isVisited[x - 1][y] = true;
						temp2.add(new Point(x - 1, y, steps + 1));
					}
					if(!isVisited[x + 1][y] && isMoveable(x + 1, y))
					{
						isVisited[x + 1][y] = true;
						temp2.add(new Point(x + 1, y, steps + 1));
					}
					if(!isVisited[x][y - 1] && isMoveable(x, y - 1))
					{
						isVisited[x][y - 1] = true;
						temp2.add(new Point(x, y - 1, steps + 1));
					}
					if(!isVisited[x][y + 1] && isMoveable(x, y + 1))
					{
						isVisited[x][y + 1] = true;
						temp2.add(new Point(x, y + 1, steps + 1));
					}
				}
			}
			
			if(minPoints.size() > 1)
			{
				int i = -1, j, index1 = 0, index2 = 0;
				Iterator<Point> minPointsIt = minPoints.iterator();
				
				tempVisited = Arrays.copyOf(visitedIndex, NO_OF_VALUES);
				
				while(minPointsIt.hasNext())
				{
					p = minPointsIt.next();
					visitedIndex[grid[p.x][p.y]] = true;
				}
				
				minPointsIt = minPoints.iterator();
				while(minPointsIt.hasNext())
				{
					p = minPointsIt.next();
					x = p.x;
					y = p.y;
					j = findShortestPathLength(true);
					if(i == -1 || i < j)
					{
						i = j;
						index2 = index1;
					}
					++index1;
				}
				
				index1 = 0;
				minPointsIt = minPoints.iterator();
				while(minPointsIt.hasNext())
				{
					if(index1 == index2)
					{
						continue;
					}
					++index1;
					minPointsIt.remove();
				}
				
				visitedIndex = Arrays.copyOf(tempVisited, NO_OF_VALUES);
			}
			
			if(isRecursiveCall)
			{
				return temp2.iterator().next().steps;
			}
			
			if(shouldChange)
			{
				p = temp2.iterator().next();
				System.out.println("hi");
				isVisited = new boolean[ROW_SIZE][COLUMN_SIZE];
				isVisited[p.x][p.y] = true;
			}
			System.out.println(temp2);
			temp1 = temp2;
		}
		
		return -1;
	}
	
	private static boolean isNumberAvailable(int x, int y)
	{
		return grid[x][y] >= 48 && grid[x][y] <= 57;
	}
	
	private static boolean isMoveable(int x, int y)
	{
		return grid[x][y] != '#';
	}
	
	private static boolean isFullyVisited(boolean visitedValues[])
	{
		boolean returnVal = true;
		
		for(i = 0; i < NO_OF_VALUES; ++i)
		{
			if(!visitedValues[i])
			{
				returnVal = false;
				break;
			}
		}
		
		return returnVal;
	}
	
	private static void findInitialPosition()
	{
		for(x = 0; x < ROW_SIZE; ++x)
		{
			for(y = 0; y < grid[0].length; ++y)
			{
				if(grid[x][y] == '0')
				{
					return;
				}
			}
		}
	}

	private static void printDetails()
	{
		System.out.println("minSteps::" + minimumSteps);
	}
	
	private static class Point
	{
		int x, y, steps;
		
		public Point(int x, int y, int steps)
		{
			this.x = x;
			this.y = y;
			this.steps = steps;
		}
		
		@Override
		public String toString()
		{
			return this.x + "$$" + this.y + "$$" + this.steps;
		}
		
		@Override
		public int hashCode()
		{
			return this.x ^ this.y;
		}
		
		@Override
		public boolean equals(Object o)
		{
			if(o instanceof Point)
			{
				Point p = (Point)o;
				return this.x == p.x && this.y == p.y;
			}
			return false;
		}
	}
	
}