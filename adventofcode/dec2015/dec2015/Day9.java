package adventofcode.dec2015;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import adventofcode.dec2016.Utils;

public class Day9
{
	
	private static final List<Integer> pathDistances = new ArrayList<Integer>();
	private static final Map<String, Map<String, Integer>> pathDetails = new HashMap<>();

	public static void main(String[] args)
	{
		Utils.fileReader("../dec2015/day9input.txt", Day9::processInput, ()->{printDetails();findShortestPath();});
	}
	
	private static void processInput(String line)
	{
		
	}
	
	private static void findShortestPath()
	{
		
	}
	
	private static void printDetails()
	{
		System.out.println(pathDistances.stream().min(Integer::min).get());
	}

}
