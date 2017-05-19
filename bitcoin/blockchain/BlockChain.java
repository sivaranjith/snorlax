package blockchain;

import java.util.Scanner;

public class BlockChain
{
	public static void main(String... args)
	{
		Block<BlockData<String>> blockChain = null;
		final Scanner reader = new Scanner(System.in);
		String  preHash = "000000000000000000000";
		
		for(String inputLine = reader.nextLine(); !inputLine.equals("exit"); inputLine = reader.nextLine())
		{
			blockChain = new Block<>(new BlockData<>(inputLine, preHash), blockChain);
			preHash = blockChain.getBlock().getHash();
			System.out.println("block added to the chain");
		}
		
		printLedger(blockChain, preHash);
		
		reader.close();
	}
	
	private static <T> void printLedger(Block<T> blockChain, final String currentHeadHash)
	{
		System.out.println();
		
		for(; blockChain != null; blockChain = blockChain.getPreviousBlock())
		{
			System.out.println(blockChain.getBlock());
		}
		
		System.out.println("\ncurrent head hash::" + currentHeadHash);
	}
	
	private static final class Block<T>
	{
		private final T node;
		
		private final Block<T> previousNode;
		
		Block(final T node, final Block<T> previousNode)
		{
			this.node = node;
			this.previousNode = previousNode;
		}
		
		T getBlock()
		{
			return this.node;
		}
		
		Block<T> getPreviousBlock()
		{
			return this.previousNode;
		}
	}
}
