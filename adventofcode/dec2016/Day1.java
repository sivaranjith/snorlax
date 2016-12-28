package adventofcode.dec2016;

import java.util.ArrayList;
import java.util.List;

public class Day1
{

	public static void main(String[] args)
	{
		int x1 = 0,y1 = 0,x2 = 0,y2 = 0,length = 0,directionCount = 0;
		char direction[] = {'N','E','S','W'},c;
		List<Line> lineList = new ArrayList<Line>();
		
		String input[] = "R3, L5, R2, L2, R1, L3, R1, R3, L4, R3, L1, L1, R1, L3, R2, L3, L2, R1, R1, L1, R4, L1, L4, R3, L2, L2, R1, L1, R5, R4, R2, L5, L2, R5, R5, L2, R3, R1, R1, L3, R1, L4, L4, L190, L5, L2, R4, L5, R4, R5, L4, R1, R2, L5, R50, L2, R1, R73, R1, L2, R191, R2, L4, R1, L5, L5, R5, L3, L5, L4, R4, R5, L4, R4, R4, R5, L2, L5, R3, L4, L4, L5, R2, R2, R2, R4, L3, R4, R5, L3, R5, L2, R3, L1, R2, R2, L3, L1, R5, L3, L5, R2, R4, R1, L1, L5, R3, R2, L3, L4, L5, L1, R3, L5, L2, R2, L3, L4, L1, R1, R4, R2, R2, R4, R2, R2, L3, L3, L4, R4, L4, L4, R1, L4, L4, R1, L2, R5, R2, R3, R3, L2, L5, R3, L3, R5, L2, R3, R2, L4, L3, L1, R2, L2, L3, L5, R3, L1, L3, L4, L3".split(", ");
		for(String inputDetails : input)
		{
			c = inputDetails.charAt(0);
			length = Integer.parseInt(inputDetails.substring(1));

			if(c == 'L') 
			{
				--directionCount; 
			}
			else
			{
				++directionCount;
			}
			directionCount = directionCount&1 | directionCount&2;
			
			switch(direction[directionCount])
			{
				case 'N': x2 += length;
						  break;
				case 'S': x2 -= length;
						  break;
				case 'E': y2 += length;
						  break;
				case 'W': y2 -= length;
			}
//			System.out.println("11::" + x2 + "::" + y2);
			
			Line currentLine = new Line(x1,y1,x2,y2);
			for(Line line : lineList)
			{
				if(line.x2 != currentLine.x1 && line.y2 != currentLine.y1)
				{
					int cuttingPoint = line.getIntersectionDistance(currentLine);
					if(cuttingPoint != -1)
					{
						System.out.println(cuttingPoint);
						return;
					}
				}
			}
			
			lineList.add(currentLine);
			
			
			x1 = x2;
			y1 = y2;
		}
		System.out.println("1::" + Math.abs(x2) + Math.abs(y2));
	}

	
	private static class Line
	{
		int x1,y1,x2,y2;
		Line(int x1,int y1,int x2,int y2)
		{
			this.x1 = x1;
			this.y1 = y1;
			this.x2 = x2;
			this.y2 = y2;
		}
		
		int getIntersectionDistance(Line otherLine)
		{
//			System.out.println("0.1::" + x1 + "::" + y1 + "::" + x2 + "::" + y2);
//			System.out.println("0.2::" + otherLine.x1 + "::" + otherLine.y1 + "::" + otherLine.x2 + "::" + otherLine.y2);
			
			if(this.x1 == this.x2 && ( (this.y1 > otherLine.y1 && this.y2 < otherLine.y1) || (this.y1 < otherLine.y1 && this.y2 > otherLine.y1)))
			{
				if(otherLine.x2 == this.x1)
				{
					System.out.println("return 1");
					return Math.abs(this.x1) + Math.abs(otherLine.y2);
				}
				else if((this.x1 > otherLine.x1 && this.x1 < otherLine.x2) || (this.x1 < otherLine.x1 && this.x1 > otherLine.x2))
				{
					System.out.println("return 2");
					return Math.abs(this.x1) + Math.abs(otherLine.y2);
				}
			}
			else if(this.y1 == this.y2 && ( (this.x1 > otherLine.x1 && this.x2 < otherLine.x1) || (this.x1 < otherLine.x1 && this.x2 > otherLine.x1)))
			{
				if(otherLine.y2 == this.y1)
				{
					System.out.println("return 3");
					return Math.abs(this.y1) + Math.abs(otherLine.x2);
				}
				else if((this.y1 > otherLine.y1 && this.y1 < otherLine.y2) || (this.y1 < otherLine.y1 && this.y1 > otherLine.y2))
				{
					System.out.println("return 4");
					return Math.abs(this.y1) + Math.abs(otherLine.x2);
				}
			}
			
			return -1;
		}
	}
}
