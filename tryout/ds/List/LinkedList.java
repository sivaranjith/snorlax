package tryout.ds.List;

public class LinkedList<T> {
	
	Node<T> headNode;
	int size = 0;
	private class Node<T> 
	{
		T data;
		Node<T> nextNode;
		
		public Node(T data)
		{
			this.data =  data;
		}
		
		public Node(T data, Node<T>nextNode)
		{
			this.data =  data;
			this.nextNode =  nextNode;
		}
		
		
		public T getData() {
			return data;
		}
		public void setData(T data) {
			this.data = data;
		}
		public Node<T> getNextNode() {
			return nextNode;
		}
		public void setNextNode(Node nextNode) {
			this.nextNode = nextNode;
		}
		
		public boolean hasNext()
		{
			return this.getNextNode() != null;
		}
	}
	
	public LinkedList()
	{
		
	}
	
	public boolean add(T data)
	{
		if(headNode == null)
		{
			headNode =  new Node<T>(data,null);
			return Boolean.TRUE;
		}
		else
		{
			Node <T> tempNode = headNode;
			while(tempNode.hasNext())
			{
				tempNode = tempNode.getNextNode();
			}
			
			Node<T> newNode =  new Node<T>(data,null);
			tempNode.setNextNode(newNode);
			return Boolean.TRUE;
		}
	}
	
	public boolean add(T data, int position)
	{
		int i=0;
		Node<T> tempNode = headNode;
		while(i< position-1 && tempNode.hasNext())
		{
			tempNode = tempNode.getNextNode();
			i++;
		}
		
		if (i == (position-1))
		{
			Node<T> newNode =  new Node<T>(data,tempNode.getNextNode());
			tempNode.nextNode =  newNode;
			return Boolean.TRUE;
		}
		else
		{
			throw new IllegalAccessError("There is no node at the give index");
		}
		
	}
	
	public void traverse()
	{
		Node<T> tempNode = headNode;
		System.out.println();
		System.out.print("the structure of the node is :\n " + tempNode.getData());
		while(tempNode.hasNext())
		{
			tempNode = tempNode.getNextNode();
			System.out.print("-->"+tempNode.getData());
		}
	}
	public void delete(int position)
	{
		Node<T> tempNode = headNode;
		if(position <= 0)
		{
			headNode = headNode.getNextNode();
		}
		else
		{
			int i=0;
			while(i< position-1 && tempNode.hasNext())
			{
				tempNode = tempNode.getNextNode();
				i++;
			}
			
			if (i == position-1)
			{
				tempNode.setNextNode(tempNode.getNextNode().getNextNode());
			}
			else
			{
				throw new IllegalAccessError("There is no node at the give index");
			}
		}
	}
	

}
