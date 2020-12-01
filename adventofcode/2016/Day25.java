package adventofcode.dec2016;

public class Day25
{

	public static void main(String[] args)
	{
		Utils.fileReader("day25input.txt", (String line)->Day12.inputListner(line), ()->generateValue());
	}
	
	private static void generateValue()
	{
		long l;
		for(l = 0; l >= 0; ++l)
		{
			Day12.clearRegisters(true);
			if(Day12.instructionExecutor(l))
			{
				break;
			}
		}
		System.out.println(l);
	}
}
