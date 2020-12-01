package adventofcode.dec2016;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;

public class Day4
{
	public static void main(String... args)
	{
		System.out.println("output::" + getSumSectorIds());
	}

	private static int getSumSectorIds()
	{
		int sectorSum = 0,tempVal = 0;
		BufferedReader br = null;
		FileWriter fw = null;
		try
		{
			String line,encryptedName,nonCheckSum,checkSum,splitArray[];
			br = new BufferedReader(new FileReader(new File("/home/local/ZOHOCORP/siva-2239/workspace/java8/bin/adventofcode/day4input.txt")));
			fw = new FileWriter("/home/local/ZOHOCORP/siva-2239/workspace/java8/bin/adventofcode/day4output.txt");
			
			while((line = br.readLine()) != null)
			{
				splitArray = line.split("\\[");
				nonCheckSum = splitArray[0];
				checkSum = splitArray[1].substring(0, splitArray[1].length() - 1);
				
				tempVal = nonCheckSum.lastIndexOf('-');
				encryptedName = nonCheckSum.substring(0, tempVal);
				tempVal = Integer.parseInt(nonCheckSum.substring(tempVal + 1));
				boolean returnedValue = checkForCondition(encryptedName.replaceAll("-",""),checkSum);
				if(returnedValue)
				{
					sectorSum += tempVal;
				}
				line = decryptCipher(nonCheckSum,tempVal%26);
				fw.write(line + "\n");
			}
		}
		catch(Exception e)
		{
			
		}
		finally
		{
			try
			{
				if(br != null)
				{
					br.close();
				}
				if(fw != null)
				{
					fw.close();
				}
			}
			catch(Exception e)
			{
				e.printStackTrace();
			}
		}
		return sectorSum;
	}

	private static String decryptCipher(String nonCheckSum,int rotationValue)
	{
		int itr,temp;
		StringBuilder sb = new StringBuilder(nonCheckSum.length());
		for(itr = 0; itr < nonCheckSum.length(); ++itr)
		{
			if(nonCheckSum.charAt(itr) >= 'a' && nonCheckSum.charAt(itr) <= 'z')
			{
				temp = (((nonCheckSum.charAt(itr) - 'a') + rotationValue)%26);
				sb.append( (char)('a' + temp));
			}
		}
		return sb.toString();
	}

	private static boolean checkForCondition(String encryptedName, String checkSum)
	{
		int counter[] = new int[26],itr1,itr2,largestNoIndex;
		for(itr1 = 0; itr1 < encryptedName.length(); ++itr1)
		{
			counter[encryptedName.charAt(itr1) - 'a'] += 1;
		}
		
		for(itr1 = 0; itr1 < checkSum.length(); ++itr1)
		{
			for(itr2 = 1, largestNoIndex = 0; itr2 < 26; ++itr2)
			{
				if(counter[itr2] > counter[largestNoIndex])
				{
					largestNoIndex = itr2;
				}
			}
			counter[largestNoIndex] = -1;
			if('a' + largestNoIndex != (int)checkSum.charAt(itr1))
			{
				return false;
			}
			if(itr1 == 4)
			{
				break;
			}
		}
		return true;
	}
}
