package adventofcode.dec2016;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.math.BigInteger;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.function.Consumer;

public class Utils
{
	public static void fileReader(String fileName, Consumer<String> fn1, Runnable fn2)
	{
		BufferedReader br = null;
		try
		{
			br = new BufferedReader(new FileReader(new File("/home/local/ZOHOCORP/siva-2239/workspace/java8/bin/adventofcode/dec2016/" + fileName)));
			String line;
			while((line = br.readLine()) != null)
			{
				fn1.accept(line);
			}
			fn2.run();
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
	
	public static String md5(String input)
	{
		String md5 = null;
		if(null == input) return null;
		try
		{
			//Create MessageDigest object for MD5
			MessageDigest digest = MessageDigest.getInstance("MD5");
			//Update input string in message digest
			digest.update(input.getBytes(), 0, input.length());
			//Converts message digest value in base 16 (hex) 
			md5 = new BigInteger(1, digest.digest()).toString(16);
			while(md5.length() < 32 )
			{
				md5 = "0" + md5;
			}
		}
		catch (NoSuchAlgorithmException e)
		{
			e.printStackTrace();
		}
		return md5.toLowerCase();
	}
}
