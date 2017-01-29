package tryout.ds.List;

public class LinkedListTest 
{
	public static void main(String[] args)
	{
		LinkedList<String> stringLinkedList =  new LinkedList<String>();
		stringLinkedList.add("karthick");
		stringLinkedList.add("siva");
		stringLinkedList.add("seelan");
		stringLinkedList.add("lala");
		stringLinkedList.traverse();
		
		stringLinkedList.add("middleinsert",2);
		stringLinkedList.traverse();
		
		
		stringLinkedList.delete(2);
		stringLinkedList.traverse();
		
		stringLinkedList.delete(2);
		stringLinkedList.traverse();
	}

}
