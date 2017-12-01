package adventofcode.dec2015;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Optional;
import java.util.stream.IntStream;
import java.util.stream.Stream;

import adventofcode.dec2016.Utils;

public class Day17
{
	private static final int TOTAL_QUANTITY = 150;
	private static final List<Integer> containers = new ArrayList<>();

	public static void main(String[] args)
	{
		Utils.fileReader("../dec2015/day17input.txt", Day17::parseInput, ()->{findCombinationsI();findCombinationsII();});
	}
	
	private static void parseInput(final String line)
	{
		containers.add(Integer.parseInt(line));
	}
	
	private static void findCombinationsI()
	{
		System.out.println(IntStream.range(0, (int)Math.pow(2, containers.size())).map(no->isFilled(no) ? 1 : 0 ).sum());
	}
	
	private static boolean isFilled(final int no)
	{
		return IntStream.range(0, containers.size()).map(index-> ((no>>index)&1) == 1 ? containers.get(index) : 0).sum() == TOTAL_QUANTITY;
	}

	private static void findCombinationsII()
	{
		final Stream<Integer> list = IntStream.range(0, (int)Math.pow(2, containers.size())).mapToObj(no->isFilled(no) ? Integer.bitCount(no) : 0 ).filter(val->val != 0).sorted();
		final Map<Integer, Integer> listAsMap = list.collect(HashMap::new, (cont, val)->cont.put(val, Optional.ofNullable(cont.get(val)).orElse(0) + 1), (r1, r2)->{});
		System.out.println(listAsMap.values().iterator().next());
	}
}
