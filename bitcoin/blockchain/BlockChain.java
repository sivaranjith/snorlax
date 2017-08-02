package blockchain;

public final class BlockChain<T>
{
	private Block<T> headPointer;
	private String previousHash = "000000000000000000000";
	
	public void addData(T data)
	{
		this.headPointer = new Block<>(new BlockData<>(data, this.previousHash), headPointer);
		this.previousHash = this.headPointer.getBlockData().getHash();
	}
	
	public void printLedger()
	{
		System.out.println();
		
		for(Block<T> blockItr = this.headPointer; blockItr != null; blockItr = blockItr.getPreviousBlock())
		{
			System.out.println(blockItr.getBlockData());
		}

		System.out.println("\ncurrent head hash::" + this.previousHash);
	}
	
	private static final class Block<T>
	{
		private final BlockData<T> node;
		
		private final Block<T> previousNode;
		
		Block(final BlockData<T> node, final Block<T> previousBlock)
		{
			this.node = node;
			this.previousNode = previousNode;
		}
		
		BlockData<T> getBlockData()
		{
			return this.node;
		}
		
		Block<T> getPreviousBlock()
		{
			return this.previousNode;
		}
	}
}
