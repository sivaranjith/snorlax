package adventofcode.dec2016;

public class Day5
{

	public static void main(String[] args)
	{
		long currentTime = System.currentTimeMillis();
		String inputString = "abbhdwsy",hashedString;
		long i = 0;
		char[] c = new char[8];
		StringBuilder sb = new StringBuilder(8);
		while(true)
		{
			hashedString = Utils.md5(inputString + i);
			int index = hashedString.charAt(5) - '0';
			if(hashedString.startsWith("00000") && index >= 0 && index <= 7 && c[index] == '\u0000')
			{
				c[index] = hashedString.charAt(6);
				sb.append(hashedString.charAt(5));
			}
			++i;
			boolean b = false;
			for(int ii = 0; ii < 8; ++ii)
			{
				if(c[ii] == '\u0000')
				{
					b = true; 
				}
			}
			if(!b)
			{
				break;
			}
		}
		System.out.println(new String(c));
		System.out.println(System.currentTimeMillis() - currentTime);
		System.out.println(i);
	}
}
