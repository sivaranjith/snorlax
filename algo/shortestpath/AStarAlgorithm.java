package algo.shortestpath;

import java.util.HashSet;
import java.util.LinkedHashSet;
import java.util.Set;
import java.util.function.BiConsumer;

import adventofcode.dec2016.Utils;

public class AStarAlgorithm
{
	
	private static final int ROW_SIZE = 37, COLUMN_SIZE = 183;
	private static char grid[][] = new char[ROW_SIZE][COLUMN_SIZE], startChar = '1', finalChar = '7';
	private static int lineCount, initX, initY, finalX, finalY, directions[] = {-1, 0, 1};
	private static Set<Point> openList = new HashSet<>(), closedList = new HashSet<>(), path = new LinkedHashSet<>();
	
	public static void main(String... args)
	{
		Utils.fileReader("day24input.txt", (String line)->inputParser(line), ()->{calculateShortestPath();printDetails();});
	}
	
	private static void inputParser(String line)
	{
		grid[lineCount++] = line.toCharArray();
	}
	
	private static void calculateShortestPath()
	{
		findStartAndDestination();
		openList.add(new Point(null, initX, initY, 0));
		
		while(true)
		{
			Point p = getNextPoint();
			closedList.add(p);
			if(isFinalPoint(p))
			{
				findPath();
				return;
			}
			addSurroundingPoints(p);
		}
	}
	
	private static void addSurroundingPoints(Point centerNode)
	{
		int i, j, newX, newY, gCost;
		Point tempPoint1;
		
		for(i = 0; i < directions.length; ++i)
		{
			for(j = 0; j < directions.length; ++j)
			{
				newX = centerNode.x + directions[i];
				newY = centerNode.y + directions[j];
				if((i == 1 && j == 1) || newX < 0 || newX >= ROW_SIZE || newY < 0 || newY >= COLUMN_SIZE || getPoint(closedList, newX, newY) != null || !isMoveAble(grid[newX][newY]))
				{
					continue;
				}
				
				if(i == 1 || j == 1)
				{
					gCost = 10;
				}
				else
				{
					gCost = 14;
				}
				
				tempPoint1 = getPoint(openList, newX, newY);
				
				if(tempPoint1 == null)
				{
					openList.add(new Point(centerNode, newX, newY, centerNode.gCost + gCost));
				}
				else if(tempPoint1.gCost > centerNode.gCost + gCost)
				{
					tempPoint1.gCost = centerNode.gCost + gCost;
					tempPoint1.parentPoint = centerNode;
				}
			}
		}
	}
	
	private static Point getNextPoint()
	{
		Point minPoint = null;
		
		for(Point p : openList)
		{
			if(minPoint == null)
			{
				minPoint = p;
				continue;
			}
			
			if(p.fCost < minPoint.fCost || (p.fCost == minPoint.fCost && p.hCost < minPoint.hCost))
			{
				minPoint = p;
			}
		}
		
		openList.remove(minPoint);
		return minPoint;
	}
	
	private static void findStartAndDestination()
	{
		findPosition((x, y)->{initX = x; initY = y;}, startChar);
		findPosition((x, y)->{finalX = x; finalY = y;}, finalChar);
		
	}
	
	private static void findPosition(BiConsumer<Integer, Integer> fnPt, char c)
	{
		int x, y;
		for(x = 0; x < ROW_SIZE; ++x)
		{
			for(y = 0; y < COLUMN_SIZE; ++y)
			{
				if(grid[x][y] == c)
				{
					fnPt.accept(x, y);
					return;
				}
			}
		}
	}
	
	private static boolean isFinalPoint(Point p)
	{
		return p.x == finalX && p.y == finalY;
	}
	
	private static boolean isInitialPoint(Point p)
	{
		return p.x == initX && p.y == initY;
	}
	
	private static boolean isMoveAble(char c)
	{
		return c != '#';
	}
	
	private static void findPath()
	{
		int x = finalX, y = finalY;
		Point p;
		
		while(true)
		{
			p = getPoint(closedList, x, y);
			path.add(p);
			
			if(isInitialPoint(p))
			{
				break;
			}
			x = p.parentPoint.x;
			y = p.parentPoint.y;
		}
	}
	
	private static void printDetails()
	{
		System.out.println(path);
		System.out.println(path.size() - 1);
	}
	
	private static Point getPoint(Set<Point> pointSet, int x, int y)
	{
		for(Point p : pointSet)
		{
			if(p.x == x && p.y == y)
			{
				return p;
			}
		}
		return null;
	}
	
	private static class Point
	{
		Point parentPoint;
		int x, y, gCost, hCost, fCost;

		Point(Point parentPoint, int x, int y, int gCost)
		{
			this.parentPoint = parentPoint;
			this.x = x;
			this.y = y;
			this.gCost = gCost;
			calculateFCost();
		}
		
		void calculateFCost()
		{
			hCost = (finalX - x) + (finalY - y);
			fCost = gCost + hCost;
		}
		
		@Override
		public String toString()
		{
			return x + "$$" + y;
		}
	}
}