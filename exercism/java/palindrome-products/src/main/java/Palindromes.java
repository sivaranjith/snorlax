import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.SortedMap;
import java.util.TreeMap;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public final class Palindromes
{
	private Palindromes()
	{
	}

	public static SortedMap<Long, List<List<Integer>>> getPalindromeProductsWithFactors(final int startingIndex, final int endingIndex)
	{
		final long largestVal = IntStream.iterate(endingIndex, val -> val - 1).limit(endingIndex - startingIndex + 1).mapToLong(multiplicand->getLargestPalindromeNo(startingIndex, endingIndex, multiplicand)).max().getAsLong();
		final long smallestVal = IntStream.range(startingIndex, endingIndex).mapToLong(multiplicand -> getSmallestPalindrome(startingIndex, endingIndex, multiplicand)).filter(val -> val != 0).min().getAsLong();
		
		final SortedMap<Long, List<List<Integer>>> result = new TreeMap<>();
		result.put(largestVal, getFactors(startingIndex, endingIndex, largestVal));
		result.put(smallestVal, getFactors(startingIndex, endingIndex, smallestVal));
		
		return Collections.unmodifiableSortedMap(result);
	}
	
	private static long getLargestPalindromeNo(final int startingIndex, final int endingIndex, final int multiplicand)
	{
		return IntStream.iterate(endingIndex, val -> val - 1).limit(endingIndex - startingIndex + 1).filter(multiplier->isPalindrome(multiplicand * multiplier)).max().orElse(0) * (long)multiplicand;
	}
	
	private static long getSmallestPalindrome(final int startingIndex, final int endingIndex, final int multiplicand)
	{
		return IntStream.iterate(endingIndex, val -> val - 1).limit(endingIndex - startingIndex + 1).filter(multiplier->isPalindrome(multiplicand * multiplier)).min().orElse(0) * (long)multiplicand;
	}
	
	private static List<List<Integer>> getFactors(final int startingIndex, final int endingIndex, final long no)
	{
		final int limit = (int)( endingIndex < no/2 || no == 1 ? endingIndex : no/2 ); 
		return IntStream.range(startingIndex, limit).filter(val -> no%val == 0 && no/val <= endingIndex && no/val >= val).mapToObj(val->Arrays.asList(val, (int)no/val)).collect(Collectors.toList());
	}
	
	private static boolean isPalindrome(final long no)
	{
		final String inputNoStr = String.valueOf(no);
		final int length = inputNoStr.length();
		return IntStream.rangeClosed(0, length/2).allMatch(index->inputNoStr.charAt(index) == inputNoStr.charAt(length - index - 1));
	}
}