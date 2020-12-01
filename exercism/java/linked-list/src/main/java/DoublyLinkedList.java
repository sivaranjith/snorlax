public final class DoublyLinkedList<T>
{
	
	private Node<T> head, tail;
	
	public DoublyLinkedList()
	{
	}
	
	public void push(final T obj)
	{
		final Node<T> temp = new Node<>(obj, tail, null);
		if(tail != null)
		{
			tail.next = temp;
		}
		else
		{
			head = temp;
		}
		tail = temp;
	}
	
	public T pop()
	{
		T returnVal = null;
		if(tail != null)
		{
			returnVal = tail.val;
			tail = tail.pre;
			if(tail == null)
			{
				head = null;
			}
		}
		return returnVal;
	}
	
	public void unshift(final T obj)
	{
		final Node<T> temp = new Node<>(obj, null, head);
		if(head != null)
		{
			head.pre = temp;
		}
		else
		{
			tail = temp;
		}
		head = temp;
	}
	
	public T shift()
	{
		T returnVal = null;
		if(head != null)
		{
			returnVal = head.val;
			head = head.next;
			if(head == null)
			{
				tail = null;
			}
		}
		return returnVal;
	}
	
	
	private static final class Node<T>
	{
		final T val;
		Node<T> pre, next;
		
		public Node(final T val, final Node<T> pre, final Node<T> next)
		{
			this.val = val;
			this.pre = pre;
			this.next = next;
		}
	}
}