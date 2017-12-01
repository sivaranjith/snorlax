package adventofcode.dec2016;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Day11
{
	
	private static final int NO_OF_ROWS = 4, NO_OF_COLUMNS = 10;
	private static int[][] grid = new int[NO_OF_ROWS][NO_OF_COLUMNS];
	private static Map<String,Integer> noBackPack = new HashMap<>();
	private static Set<Grid> duplicateFinder = new HashSet<>();
	private static int i = 0, j = 0, elementNo = 1, shortestLength = 0;

	public static void main(String[] args)
	{
		Utils.fileReader("day11input.txt", (String s)->loadDetails(s), ()->{calculateSteps();printDetails();});
	}

	private static void loadDetails(String line)
	{
		Matcher m = Pattern.compile("a [a-zA-Z\\-]+ ").matcher(line);
		String element,match;
		int temp;
		
		while(m.find())
		{
			match = m.group();
			element = match.split("[\\ |\\-]")[1];
			
			if(noBackPack.get(element) == null)
			{
				noBackPack.put(element, elementNo++);
			}
			
			temp = noBackPack.get(element)*10;
			
			if(!match.contains("compatible"))
			{
				++temp;
			}
			
			grid[i][j++] = temp;
			
		}
		
		++i;
	}
	
	private static void calculateSteps()
	{
		int ii = 0;
		List<Grid> container = new ArrayList<>(), temp;
		Grid g = new Grid(grid,"",0,0);
		container.add(g);
		
		while(!container.isEmpty())
		{
			temp = new ArrayList<>();
			Iterator<Grid> gridIt = container.iterator();
			
			while(gridIt.hasNext())
			{
				g = gridIt.next();
				if(isAtFinalState(g.grid))
				{
					System.out.println("found da see here" + g.stepsCount);
					shortestLength = g.stepsCount;
					return;
				}
				
				getAllPossibleStates(temp,g);
			}
			System.out.println(++ii + ")printing temp:: " + temp.size());

			container = temp;
		}
		
		System.out.println("empty");
	}
	
	private static void getAllPossibleStates(List<Grid> container, Grid g)
	{
		int grid[][] = g.grid, temp[][], startingPoistion = g.startingPosition, i, j;
		
		for(i = 0; i < NO_OF_COLUMNS; ++i)
		{
			if(grid[startingPoistion][i] == 0)
			{
				continue;
			}
			
			temp = getCopy(grid);
			if(startingPoistion < NO_OF_ROWS - 1 && isPossibleToMove(temp, startingPoistion, startingPoistion + 1, i, true))
			{
				moveThings(container, g, temp, startingPoistion, startingPoistion + 1, i, i);
				temp = getCopy(grid);
			}
			
			if(startingPoistion != 0  && isPossibleToMove(temp, startingPoistion, startingPoistion - 1, i, true))
			{
				moveThings(container, g, temp, startingPoistion, startingPoistion - 1, i, i);
			}
		}
		
		int val;
		for(i = 0; i < NO_OF_COLUMNS; ++i)
		{
			for(j = i + 1; j < NO_OF_COLUMNS; ++j)
			{
				if(grid[startingPoistion][i] == 0 || grid[startingPoistion][j] == 0)
				{
					continue;
				}
				
				temp = getCopy(grid);
				if(temp[startingPoistion][i]/10 == temp[startingPoistion][j]/10)
				{
					val = (temp[startingPoistion][i]&1) == 1 ? i : j;
					if(startingPoistion != NO_OF_ROWS -1 && isPossibleToMove(temp, startingPoistion, startingPoistion + 1, val, false))
					{
						moveThings(container, g, temp, startingPoistion, startingPoistion + 1, i, j);
						temp = getCopy(grid);
					}
					
					if(startingPoistion != 0 && isPossibleToMove(temp, startingPoistion, startingPoistion - 1, val, false))
					{
						moveThings(container, g, temp, startingPoistion, startingPoistion - 1, i, j);
					}
				}
				else if((temp[startingPoistion][i]&1) == (temp[startingPoistion][j]&1))
				{
					if(startingPoistion != NO_OF_ROWS - 1 && isPossibleToMove2(temp, startingPoistion, startingPoistion + 1, i, j))
					{
						moveThings(container, g, temp, startingPoistion, startingPoistion + 1, i, j);
						temp = getCopy(grid);
					}
					if(startingPoistion != 0 && isPossibleToMove2(temp, startingPoistion, startingPoistion - 1, i, j))
					{
						moveThings(container, g, temp, startingPoistion, startingPoistion - 1, i, j);
					}
				}
			}
		}
	}
	
	private static boolean isPossibleToMove2(int temp[][], int startingPosition, int toPosition, int i, int j)
	{
		int i1, j1;
		if((temp[startingPosition][i]&1) == 0)
		{
			return isPossibleToMove(temp, startingPosition, toPosition, i, true) && isPossibleToMove(temp, startingPosition, toPosition, j, true);
		}
		else
		{
			boolean thisChipAvailable = false, otherGenAvailable = false;
			for(i1 = 0; i1 < NO_OF_COLUMNS; ++i1)
			{
				if( (i != i1 && temp[startingPosition][i]/10 == temp[startingPosition][i1]/10) || (j != i1 && temp[startingPosition][j]/10 == temp[startingPosition][i1]/10))
				{
					thisChipAvailable = true;
				}
				else if( (i != i1 && j != i1 && (temp[startingPosition][i1]&1) == 1))
				{
					otherGenAvailable = true;
				}
			}
			
			if(thisChipAvailable && otherGenAvailable)
			{
				return false;
			}
			
			for(i1 = 0; i1 < NO_OF_COLUMNS; ++i1)
			{
				if(temp[toPosition][i1] != 0 && (temp[toPosition][i1]&1) == 0 && temp[toPosition][i1]/10 != temp[startingPosition][i]/10 && temp[toPosition][i1]/10 != temp[startingPosition][j]/10)
				{
					for(j1 = 0; j1 < NO_OF_COLUMNS; ++j1)
					{
						if(i1 != j1 && temp[toPosition][i1]/10 == temp[toPosition][j1]/10)
						{
							break;
						}
					}
					if(j1 == NO_OF_COLUMNS)
					{
						return false;
					}
				}
			}
		}
		return true;
	}

	private static boolean isPossibleToMove(int[][] temp, int fromPosition, int toPosition, int i2, boolean isThisChipCheckRequired)
	{
		int val = temp[fromPosition][i2];
		int i, j;
		if((val&1) == 1)
		{
			if(isThisChipCheckRequired)
			{
				boolean otherGenerators = false, thisChip = false;
				for(i = 0; i < NO_OF_COLUMNS; ++i)
				{
					if(i == i2 || temp[fromPosition][i] == 0)
					{
						continue;
					}
					if((temp[fromPosition][i]&1) == 1)
					{
						otherGenerators = true;
					}
					else if(temp[fromPosition][i]/10 == temp[fromPosition][i2]/10)
					{
						thisChip = true;
					}
				}
				
				if(otherGenerators && thisChip)
				{
					return false;
				}
			}
			
			for(i = 0; i < NO_OF_COLUMNS; ++i)
			{
				if(temp[toPosition][i] != 0 && (temp[toPosition][i]&1) == 0 && temp[toPosition][i]/10 != temp[toPosition][i2]/10)
				{
					for(j = 0; j < NO_OF_COLUMNS; j++)
					{
						if(i != j && temp[toPosition][i]/10 == temp[toPosition][j]/10)
						{
							break;
						}
					}
					if(j == NO_OF_COLUMNS)
					{
						return false;
					}
				}
			}
		}
		else
		{
			for(i = 0; i < NO_OF_COLUMNS; ++i)
			{
				if(temp[toPosition][i]/10 == val/10)
				{
					return true;
				}
			}
			
			for(i = 0; i < NO_OF_COLUMNS; ++i)
			{
				if((temp[toPosition][i]&1) == 1)
				{
					return false;
				}
			}
		}
		return true;
	}

	private static void moveThings(List<Grid> container, Grid g, int grid[][], int fromPosition, int toPosition, int i, int j)
	{
		int stepsCount = g.stepsCount;
//		String previousState = getState(grid), parentState = g.parentState;
		
		grid[toPosition][i] = grid[fromPosition][i];
		grid[fromPosition][i] = 0;
		
		if(i != j)
		{
			grid[toPosition][j] = grid[fromPosition][j];
			grid[fromPosition][j] = 0;
		}
//		String currentState = getState(grid);
		
		
		Grid gNew = new Grid(grid, "previousState", toPosition, stepsCount + 1);
		if(/*!currentState.equals(parentState) && */!duplicateFinder.contains(gNew))
		{
			duplicateFinder.add(gNew);
			container.add(gNew);
		}
	}
	
	/*private static String getState(int grid[][])
	{
		int i, j;
		StringBuilder sb = new StringBuilder((NO_OF_ROWS + 1)*NO_OF_COLUMNS);
		
		for(i = 0; i < NO_OF_ROWS; ++i)
		{
			for(j = 0; j < NO_OF_COLUMNS; ++j)
			{
				sb.append(grid[i][j]);
			}
		}
		
		return sb.toString();
	}*/
	
	private static int[][] getCopy(int[][] grid)
	{
		int temp[][] = new int[NO_OF_ROWS][NO_OF_COLUMNS], i ,j;
		for(i = 0; i < NO_OF_ROWS; ++i)
		{
			for(j = 0; j < NO_OF_COLUMNS; ++j)
			{
				temp[i][j] = grid[i][j];
			}
		}
		return temp;
	}

	private static void printDetails()
	{
		System.out.println("///" + shortestLength);
	}
	
	private static boolean isAtFinalState(int[][] grid)
	{
		int i;
		boolean returnVal = true;
		
		for(i = 0; i < NO_OF_COLUMNS; ++i)
		{
			if(grid[NO_OF_ROWS - 1][i] == 0)
			{
				returnVal = false;
				break;
			}
		}
		
		return returnVal;
	}

	private static class Grid
	{
		int startingPosition, stepsCount;
		int[][] grid;
//		String parentState;
		
		public Grid(int[][] grid, String parentState, int startingPosition, int stepsCount)
		{
			this.grid = grid;
			this.startingPosition = startingPosition;
			this.stepsCount = stepsCount;
//			this.parentState = parentState;
		}
		
		@Override
		public String toString()
		{
			System.out.println("grid::");
			for(int i = 0; i < NO_OF_ROWS; ++i)
			{
				for(int j = 0; j < NO_OF_COLUMNS; ++j)
				{
					System.out.print(grid[i][j] + ",");
				}
				System.out.println();
			}
			System.out.println("start::" + startingPosition);
			System.out.println("steps:: " + stepsCount);
			return "";
		}
		
		@Override
		public boolean equals(Object o)
		{
			if(o instanceof Grid)
			{
				Grid g = ((Grid)o);
				for(int i = 0; i < NO_OF_ROWS; ++i)
				{
					for(int j = 0; j < NO_OF_COLUMNS; ++j)
					{
						if(this.grid[i][j] != g.grid[i][j])
						{
							return false;
						}
					}
				}
				return g.startingPosition == this.startingPosition;
			}
			return false;
		}
		
		@Override
		public int hashCode()
		{
			int val = 0;
			for(int i = 0; i < NO_OF_ROWS; ++i)
			{
				for(int j = 0; j < NO_OF_COLUMNS; ++j)
				{
					val += i*grid[i][j];
				}
			}
			return val + startingPosition;
		}
	}
}
