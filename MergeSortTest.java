package com.test.play;

public class MergeSortTest 
{
	public static void main(String[] args)
	{
		try
		{
			int [] a ={3,2,1};
			
			a = mergeSort(a);
			
			System.out.println("******final print ********");
			for(int index :a )
			{
				System.out.print(index+",");
			}
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
	}
	
	public static int [] mergeSort(int[] a)
	{
		if(a.length ==1)
		{
			return a;
		}
		int [] b =new int[a.length/2];
		int [] c =new int[a.length-b.length];
		
		System.arraycopy(a, 0, b, 0, b.length);
		System.arraycopy(a, b.length, c, 0, c.length);
				
		mergeSort(b);
		mergeSort(c);
		
		
		return mergeSplit(b,c,a);
		
		
	}
	
	public static int [] mergeSplit(int[]b, int[] c,int []a)
	{
		int i =0;
		int j=0;
		int index =0;
		while((i < b.length&& j<c.length))
		{
			if(b[i]<c[j])
			{
				a[index] = b[i++];
			}
			else
			{
				a[index] = c[j++];
			}
			
			index++;
		}
		
		System.arraycopy(b, i, a, index, b.length-i);
		System.arraycopy(c, j, a, index, c.length-j);
		
		for(int ind :a )
		{
			System.out.print(ind+",");
		}
		System.out.println("*** end of print ***");
		return a;
			
	}

}
