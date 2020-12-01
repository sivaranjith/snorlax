package adventofcode.dec2016;

public class Day23
{
	public static void main(String[] args)
	{
		Utils.fileReader("day23input.txt", (String line)->Day12.inputListner(line), ()->findSafeCode(7));
		Utils.fileReader("day23input.txt", (String line)->Day12.inputListner(line), ()->findSafeCode(12));
	}
	
	private static void findSafeCode(int initialCode)
	{
		Day12.clearRegisters();
		Day12.instructionExecutor(initialCode);
		Day12.printDetails();
	}
}
