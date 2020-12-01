import java.util.ArrayList;
import java.util.Collections;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;


public final class BST<T>
{

	private Node<T> root = null;

	public BST()
	{
	}

	public void insert(final T val)
	{
		root = insert(root, new Node<>(val));
	}
	
	private Node<T> insert(Node<T> parent, final Node<T> newNode)
	{
		Node<T> temp = newNode;
		
		if(parent != null)
		{
			if(parent.val.hashCode() >= newNode.val.hashCode())
			{
				parent.left = insert(parent.left, newNode);
			}
			else
			{
				parent.right = insert(parent.right, newNode);
			}
			temp = parent;
		}
		
		return temp;
	}
	
	public Node<T> getRoot()
	{
		return this.root;
	}
	
	public List<T> getAsLevelOrderList()
	{
		final Queue<Node<T>> container = new LinkedList<>();
		final List<T> resultList = new ArrayList<>();
		
		container.add(root);
		
		while(!container.isEmpty())
		{
			final Node<T> temp = container.poll();
			
			if(temp != null)
			{
				resultList.add(temp.val);
				container.add(temp.left);
				container.add(temp.right);
			}
		}
		
		return Collections.unmodifiableList(resultList);
	}
	
	public List<T> getAsSortedList()
	{
		final List<T> resultList = new ArrayList<>();
		
		preOrderTraversal(root, resultList);
		
		return Collections.unmodifiableList(resultList);
	}
	
	private void preOrderTraversal(final Node<T> temp, final List<T> resultList)
	{
		if(temp != null)
		{
			preOrderTraversal(temp.getLeft(), resultList);
			
			resultList.add(temp.val);
			
			preOrderTraversal(temp.getRight(), resultList);
			
		}
	}

	public static final class Node<T>
	{
		private final T val;
		private Node<T> left, right;

		private Node(final T val)
		{
			this.val = val;
		}

		public T getData()
		{
			return this.val;
		}
		
		public Node<T> getLeft()
		{
			return this.left;
		}
		
		public Node<T> getRight()
		{
			return this.right;
		}
	}
}