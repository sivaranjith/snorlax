package blockchain;

import java.util.LinkedList;
import java.util.List;
import java.util.Scanner;

public class BlockChain
{
	public static void main(String... args)
	{
		List<BlockData> blockChain = new LinkedList<>();
		Scanner reader = new Scanner(System.in);
		
		for(String inputLine = reader.nextLine(), preHash = "000000000000000000000"; !inputLine.equals("exit"); inputLine = reader.nextLine())
		{
			blockChain.add(new BlockData(inputLine, preHash)); 
			preHash = blockChain.get(blockChain.size() - 1).getHash();
		}
		
		reader.close();
	}
}