package tryout.ds.List;

public class HeapSort 
{
	public static void main(String[]args)
	{
		try
		{
			int [] a = {12,11,10,13,9,8,7,6,5,4,3,2,1};
			
			Heap h =  new Heap();
			h.setArray(a);
			h.heapify(a.length-1);
			
			for(int i=0; i<a.length;i++)
			{
				System.out.print(h.getTop()+",");
			}
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}

	}

}
