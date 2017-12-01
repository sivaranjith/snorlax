package adventofcode.dec2016;

import java.util.Iterator;
import java.util.LinkedHashSet;
import java.util.Set;

public class Day13
{
	
	private static final int FAV_NO = 1358, STARTING_ROW = 1, STARTING_COLUMN = 1, DESTINATION_ROW = 31, DESTINATION_COLUMN = 39, SIZE = 50;
	private static int grid[][] = new int[SIZE][SIZE], stepsBFS = 0;
	static boolean b[][] = new boolean[SIZE][SIZE];
	private static Set<Point> queue = new LinkedHashSet<Point>(), temp;
	
	public static void main(String[] args)
	{
		populateGrid();
		breathFirstSearch();
		Point p = new Point(1, 1);
		
		queue = new LinkedHashSet<>();
		temp = new LinkedHashSet<>();
		temp.add(p);
		
		b[1][1] = true;
		deapthFirstSearch(1, 1, 1);
		printDetails();
	}

	private static void printDetails()
	{
		System.out.println(stepsBFS);
		System.out.println(queue.size());
	}
	
	private static void deapthFirstSearch(int x,int y,int count)
	{
		if(count > 50)
		{
			return;
		}
		queue.addAll(temp);
		
		Point p;
		if(x != SIZE - 1 && !b[x + 1][y] && gridVal(x + 1, y) == 0)
		{
			b[x + 1][y] = true;
			p = new Point(x + 1, y);
			temp.add(p);
			deapthFirstSearch(x + 1, y, count + 1);
//			temp.remove(p);
			b[x + 1][y] = false;
		}
		if(x != 0 && !b[x - 1][y] && gridVal(x - 1, y) == 0)
		{
			b[x - 1][y] = true;
			p = new Point(x - 1, y);
			temp.add(p);
			deapthFirstSearch(x - 1, y, count + 1);
//			temp.remove(p);
			b[x - 1][y] = false;
		}
		if(y != SIZE - 1 && !b[x][y + 1] && gridVal(x, y + 1) == 0)
		{
			b[x][y + 1] = true;
			p = new Point(x, y + 1);
			temp.add(p);
			deapthFirstSearch(x, y + 1, count + 1);
//			temp.remove(p);
			b[x][y + 1] = false;
		}
		if(y != 0 && !b[x][y - 1] && gridVal(x, y - 1) == 0)
		{
			b[x][y - 1] = true;
			p = new Point(x, y - 1);
			temp.add(p);
			deapthFirstSearch(x, y - 1, count + 1);
//			temp.remove(p);
			b[x][y - 1] = false;
		}
	}

	private static void breathFirstSearch()
	{
		queue.add(new Point(STARTING_ROW,STARTING_COLUMN));
		grid[STARTING_ROW][STARTING_COLUMN] += 10;
		while(true)
		{
			temp = new LinkedHashSet<>();
			Iterator<Point> queueIt = queue.iterator();
			while(queueIt.hasNext())
			{
				Point p = queueIt.next();
//				System.out.println(p.x + "##" + p.y);
				if(p.x == DESTINATION_ROW && p.y == DESTINATION_COLUMN)
				{
					return;
				}
				if(p.x != 99 && grid[p.x + 1][p.y] < 10 && (grid[p.x + 1][p.y]&1) == 0)
				{
					grid[p.x + 1][p.y] += 10;
					temp.add(new Point(p.x + 1, p.y));
				}
				if(p.x != 0 && grid[p.x - 1][p.y] < 10 && (grid[p.x - 1][p.y]&1) == 0)
				{
					grid[p.x - 1][p.y] += 10;
					temp.add(new Point(p.x - 1, p.y));
				}
				if(p.y != 99 && grid[p.x][p.y + 1] < 10 && (grid[p.x][p.y + 1]&1) == 0)
				{
					grid[p.x][p.y + 1] += 10;
					temp.add(new Point(p.x, p.y + 1));
				}
				if(p.y != 0 && grid[p.x][p.y - 1] < 10 && (grid[p.x][p.y - 1]&1) == 0)
				{
					grid[p.x][p.y - 1] += 10;
					temp.add(new Point(p.x, p.y - 1));
				}
			}
			if(temp.isEmpty())
			{
				break;
			}
			queue = temp;
			++stepsBFS;
		}
	}
	
	private static int gridVal(int i, int j)
	{
		int temp = FAV_NO + i*i + 3*i + 2*i*j + j + j*j;
		return (Integer.bitCount(temp)&1);
	}

	private static void populateGrid()
	{
		int i, j;
		for(i = 0; i < SIZE; ++i)
		{
			for(j = 0; j < SIZE; ++j)
			{
				grid[i][j] = gridVal(i,j);
				/*if(grid[i][j] == 0)
				{
					System.out.print(".");
				}
				else
				{
					System.out.print("#");
				}*/
			}
//			System.out.println();
		}
		
	}
	
	public static class Point
	{
		int x,y;
		public Point(int x,int y)
		{
			this.x = x;
			this.y = y;
		}
		
		@Override
		public int hashCode()
		{
			return x*10 + y;
		}

		@Override
		public boolean equals(Object o)
		{
			if(o instanceof Point)
			{
				return ( (Point)o ).x == this.x && ( (Point)o ).y == this.y;
			}
			return false;
		}
	}

}
