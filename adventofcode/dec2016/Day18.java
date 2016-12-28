package adventofcode.dec2016;

public class Day18
{
	
	private static final String INPUT = "......^.^^.....^^^^^^^^^...^.^..^^.^^^..^.^..^.^^^.^^^^..^^.^.^.....^^^^^..^..^^^..^^.^.^..^^..^^^..";
	private static int safeTileCount = 0;

	public static void main(String[] args)
	{
		findSafeTileCount(40);
		printDetails();
		
		findSafeTileCount(400000);
		printDetails();
	}
	
	private static void printDetails()
	{
		System.out.println(safeTileCount);
	}
	
	private static void findSafeTileCount(int noOfRows)
	{
		int length = INPUT.length(), i, rowCount = 1;
		String currentRow = INPUT;
		StringBuilder sb;
		safeTileCount = 0;
		
		for(i = 0; i < length; ++i)
		{
			if(currentRow.charAt(i) == '.')
			{
				++safeTileCount;
			}
		}
		
		
		while(rowCount++ != noOfRows)
		{
			sb = new StringBuilder(length);
			for(i = 0; i < length; ++i)
			{
				if(i != 0)
				{
					if(i != length - 1)
					{
						if(currentRow.charAt(i - 1) != currentRow.charAt(i + 1))
						{
							sb.append('^');
						}
						else
						{
							sb.append('.');
							++safeTileCount;
						}
					}
					else
					{
						safeTileSetter(currentRow, sb, i - 1);
					}
				}
				else
				{
					safeTileSetter(currentRow, sb, i + 1);
				}
			}
			currentRow = sb.toString();
		}
	}
	
	private static void safeTileSetter(String currentRow, StringBuilder sb, int index)
	{
		if(currentRow.charAt(index) == '^')
		{
			sb.append('^');
		}
		else
		{
			sb.append('.');
			++safeTileCount;
		}
	}

}
