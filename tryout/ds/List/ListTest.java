package tryout.ds.List;

public class ListTest 
{
	public static void main(String [] args)
	{
		try
		{
			List<Integer> a= new ListImpl<Integer>();
			
			//test add
			for(int i =0;i<20;i++)
			{
				a.add(i);
			}
			
			System.out.println("the array a"+a);
			
			System.out.println("the remove ::"+a.remove(13));
			System.out.println("the array a"+a);
			
			System.out.println("the elem from  a @ 9:::"+a.get(9));
			
			System.out.println("the contains for 13"+a.contains(13));
			System.out.println("the contains for 3"+a.contains(3));
			
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
	}

}
