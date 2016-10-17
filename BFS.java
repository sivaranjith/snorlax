package com.test.play;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Scanner;
import java.util.Stack;

public class BFS 
{

	public static void main(String [] args)
	{
		try
		{
			int vertices;
			int edges[][];
			boolean visited[];
			
			LinkedList a  =  new LinkedList<String>();
			a.get
			
			Scanner s  = new Scanner(System.in);
			
			System.out.println("enter the number of vertices:");
			vertices = s.nextInt();

			edges = new int[vertices][vertices];
			visited = new boolean[vertices];
			
			for(int i=0;i<vertices;i++)
			{
				for(int j=0;j<vertices;j++)
				{
					System.out.println("enter the next co-ordinate I,J ::"+ i + ","+j);
					edges[i][j] = s.nextInt();
				}
			}
			
			System.out.println("enter the vertices to start from::");
			int startvertices =  s.nextInt();
			visited[startvertices] = Boolean.TRUE;
			
			Stack <Integer> stack =  new Stack<Integer>();
			stack.add(startvertices);
			
			List route =  new ArrayList();
			
			//printBFSRoute
			System.out.println("the path is ");
			while(stack.size() >0)
			{
				int index = stack.pop();
				route.add(index);
				
				for(int j=0;j<vertices;j++)
				{
					int path  = edges[index][j];
					System.out.println("edges::"+index+","+j +"::"+path);
					if(path == 1 && !visited[j])
					{
						visited[j] = Boolean.TRUE;
						System.out.println(index);
						stack.push(j);
					}
					
				}
				
				
				
				
			}
			
			System.out.println("the route is:::"+route);
			
			
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
	}
}
