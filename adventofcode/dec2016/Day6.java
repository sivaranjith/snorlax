package adventofcode.dec2016;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;

public class Day6
{

	public static void main(String[] args)
	{
		int[][] output = new int[10][26];
		int i,j,largest,length = 0;
		char c;
		StringBuilder sb = new StringBuilder(10);
		BufferedReader br = null;
		try
		{
			br = new BufferedReader(new FileReader(new File("/home/local/ZOHOCORP/siva-2239/workspace/java8/bin/adventofcode/day6input.txt")));
			String line;
			while((line = br.readLine()) != null)
			{
				length = line.length();
				for(i = 0; i < line.length(); ++i)
				{
					++output[i][line.charAt(i) - 'a'];
				}
			}
			
			System.out.println(output[0][3] + "::" + output[0][4]);
			for(i = 0; i < length; ++i)
			{
				for(j = 1,largest = 0; j < 26; ++j)
				{
					if(output[i][j] < output[i][largest] && output[i][j] != 0)
					{
						largest = j;
//						System.out.println(i + "//" + largest);
					}
				}
				c = (char)('a' + largest);
//				System.out.println(output[i][largest] + "::" + i);
				sb.append(c);
			}
			System.out.println(sb);
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
		finally
		{
			try
			{
				if(br != null)
				{
					br.close();
				}				
			}
			catch(Exception e)
			{
				e.printStackTrace();
			}
		}
	}

}
