package adventofcode.dec2016;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;

public class Day3
{
	public static void main(String... args)
	{
		System.out.println(getTriangleCount());
	}

	private static int getTriangleCount()
	{
		BufferedReader br = null;
		int total = 0,s1,s2,s3;
		try
		{
			br = new BufferedReader(new FileReader(new File("/home/local/ZOHOCORP/siva-2239/workspace/java8/bin/adventofcode/day3input.txt")));
			String line1,line2,line3,sides1[],sides2[],sides3[];
			while((line1 = br.readLine()) != null)
			{
				line2 = br.readLine();
				line3 = br.readLine();
				sides1 = line1.trim().split("  ");
				sides2 = line2.trim().split("  ");
				sides3 = line3.trim().split("  ");
				
				s1 = Integer.parseInt(sides1[0].trim());
				s2 = Integer.parseInt(sides2[0].trim());
				s3 = Integer.parseInt(sides3[0].trim());
				if(s1 + s2 > s3 && s2 + s3 > s1 && s3 + s1 > s2)
				{
					++total;
				}
				
				s1 = Integer.parseInt(sides1[1].trim());
				s2 = Integer.parseInt(sides2[1].trim());
				s3 = Integer.parseInt(sides3[1].trim());
				if(s1 + s2 > s3 && s2 + s3 > s1 && s3 + s1 > s2)
				{
					++total;
				}
				
				s1 = Integer.parseInt(sides1[2].trim());
				s2 = Integer.parseInt(sides2[2].trim());
				s3 = Integer.parseInt(sides3[2].trim());
				if(s1 + s2 > s3 && s2 + s3 > s1 && s3 + s1 > s2)
				{
					++total;
				}
			}
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
		return total;
	}
}
