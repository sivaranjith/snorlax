import java.util.Arrays;
import java.util.NoSuchElementException;

public final class SimpleLinkedList
{
	private int size = 0;
	private Node head = null;
	
	public SimpleLinkedList()
	{
	}
	
	public SimpleLinkedList(Integer[] input)
	{
		Arrays.stream(input).forEach(this::push);
	}
	
	public void push(final Integer val)
	{
		head = new Node(val, head);
		++size;
	}
	
	public int size()
	{
		return this.size;
	}
	
	public int pop()
	{
		if(size == 0)
		{
			throw new NoSuchElementException();
		}
		
		final int result = head.val;
		head = head.next;
		--size;
		return result;
	}
	
	public void reverse()
	{
		final Node temp = reverse(head);
		temp.next = null;
	}
	
	private Node reverse(Node temp)
	{
		if(temp != null)
		{
			final Node temp1 = reverse(temp.next);
			if(temp1 != null)
			{
				temp1.next = temp;
			}
			else
			{
				head = temp;
			}
		}
		return temp;
	}
	
	@SuppressWarnings("unchecked")
	public <T> T[] asArray(T expectedClass)
	{
		final Integer[] result = new Integer[size];
		Node temp = head;
		for(int index = 0; temp != null; ++index, temp = temp.next)
		{
			result[index] = temp.val;
		}
		return (T[])result;
	}
	
	private static final class Node
	{
		final Integer val;
		Node next;
		
		Node(final Integer val, final Node next)
		{
			this.val = val;
			this.next = next;
		}
	}
}