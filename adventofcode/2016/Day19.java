package adventofcode.dec2016;

import java.util.function.UnaryOperator;

public class Day19
{

	private static final int INPUT = 3012210;
	
	public static void main(String[] args)
	{
		System.out.println(removeNext(INPUT));
		System.out.println(removeMiddle(INPUT));
	}

	private static int removeNext(int input)
	{
		return (int)( 2*(input - Math.pow(2, (int)(Math.log(input)/Math.log(2)))) + 1);
	}

	private static int removeMiddle(int input)
	{
		double inputLog = Math.log(input);
		UnaryOperator<Integer> previousLogVal = (Integer input1) -> {return (int)(Math.pow(input1, (int)(inputLog/Math.log(input1))));};  
		int result = 0, log2 = previousLogVal.apply(2), log3 = previousLogVal.apply(3), deleteVal = getDeleteVal(log3);
		
		if(input == log3)
		{
			result = input;
		}
		else if(deleteVal < log2)
		{
			result = (input - deleteVal + 1)*2 + (deleteVal - 1 - log3);
		}
		else if(deleteVal > log2)
		{
			if(input < deleteVal)
			{
				result = input - log3;
			}
			else
			{
				result = (input - deleteVal + 1)*2 + (deleteVal - 1 - log3);
			}
		}
		else
		{
			System.out.println("what");
		}
		
		return result;
	}
	
	private static int getDeleteVal(int log3)
	{
		int temp, i, j;
		for(i = log3 + 1, j = 1; ; ++i, ++j)
		{
			temp = i/2 + 1;
			if(temp == j)
			{
				break;
			}
		}
		return (i&1) == 1 ? i : i - 1;
	}
}



/**
 * for remove middle the pattern is 
 
1	1

2	1
3	3
<>>>>>>>>>>>>>>>>>>>>>>

4	1
5	2
6	3
7	5

8	7
9	9
<>>>>>>>>>>>>>>>>>>>>>>
10	1
11	2
12	3
13	4
14	5
15	6

16	7
17	8
18	9
19	11
20	13
21	15
22	17
23	19
24	21
25	23
26	25
27	27
<>>>>>>>>>>>>>>>>>>>>>>
28	1
29	2
30	3
31	4
32	5

33	6
 * 
 */