package adventofcode.dec2016;

import java.util.HashMap;
import java.util.Map;

public class Day12
{

	private static long register[] = new long[4],currentInstruction = 0,instructionCount = 0;
	private static Map<Long,String> input = new HashMap<>();
	private static int expectedValue = 0, correctCount = 0;
	
	public static void main(String[] args)
	{
		Utils.fileReader("day12input.txt", (String line)->inputListner(line), ()->{instructionExecutor();printDetails();});
		
		clearRegisters();
		register[2] = 1;
		
		Utils.fileReader("day12input.txt", (String line)->inputListner(line), ()->{instructionExecutor();printDetails();});
	}

	public static void inputListner(String line)
	{
		input.put(instructionCount++, line);
	}

	public static void printDetails()
	{
		System.out.println(register[0]);
	}
	
	public static void instructionExecutor()
	{
		instructionExecutor(0);
	}
	
	public static boolean instructionExecutor(long initialValue)
	{
		String split[],line = null;
		
		register[0] = initialValue;
		while(currentInstruction < instructionCount)
		{
			line = input.get(currentInstruction);
			split = line.split(" ");
			if(line.contains("cpy"))
			{
				char c = split[1].charAt(0);
				
				if(split[2].charAt(0) >= 'a' && split[2].charAt(0) <= 'd')
				{
					if(c >= 'a' && c <= 'd')
					{
						register[split[2].charAt(0) - 'a'] = register[split[1].charAt(0) - 'a'];
					}
					else
					{
						register[split[2].charAt(0) - 'a'] = Integer.parseInt(split[1]);
					}
				}
			}
			else if(line.contains("inc"))
			{
				++register[split[1].charAt(0) - 'a'];
			}
			else if(line.contains("dec"))
			{
				--register[split[1].charAt(0) - 'a'];
			}
			else if(line.contains("jnz"))
			{
				if((split[1].charAt(0) - 'a' >= 0 && register[split[1].charAt(0) - 'a'] != 0) || (split[1].charAt(0) - 'a' < 0 && Integer.parseInt(split[1]) != 0))
				{
					char c = split[2].charAt(0);
					if(c >= 'a' && c <= 'd')
					{
						currentInstruction += register[c - 'a'];
					}
					else
					{
						currentInstruction += Integer.parseInt(split[2]);
					}
					continue;
				}
			}
			else if(line.contains("tgl"))
			{
				int registerIndex = split[1].charAt(0) - 'a';
				long toggleInstruction = currentInstruction + register[registerIndex];
				if(toggleInstruction >= 0 && toggleInstruction < instructionCount)
				{
					line = input.get(toggleInstruction);
					if(line.contains("cpy"))
					{
						line = line.replace("cpy", "jnz");
					}
					else if(line.contains("jnz"))
					{
						line = line.replace("jnz", "cpy");
					}
					else if(line.contains("inc"))
					{
						line = line.replace("inc", "dec");
					}
					else if(line.contains("dec") || line.contains("tgl"))
					{
						line = line.replaceAll("(dec|tgl)", "inc");
					}
					input.put(toggleInstruction, line);
				}
			}
			else if(line.contains("out"))
			{
				if(outRegister(split[1].charAt(0) - 'a') && correctCount == 10)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			++currentInstruction;
		}
		return false;
	}
	
	private static boolean outRegister(int index)
	{
		if(expectedValue == register[index])
		{
			expectedValue ^= 1;
			++correctCount;
			return true;
		}
		else
		{
			expectedValue = correctCount = 0;
			return false;
		}
	}

	public static void clearRegisters()
	{
		clearRegisters(false);
	}
	
	public static void clearRegisters(boolean clearCurrentInstruction)
	{
		register[0] = 0;
		register[1] = 0;
		register[2] = 0;
		register[3] = 0;
		if(clearCurrentInstruction)
		{
			currentInstruction = 0;
		}
	}
}
