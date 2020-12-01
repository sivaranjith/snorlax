import java.util.ArrayList;
import java.util.List;
import java.util.stream.IntStream;

public final class Prime
{
	private Prime()
	{
	}
	
	public static int nth(final int n) throws IllegalArgumentException
	{
		checkN(n);
		
		int returnVal = 2;
		if(n != 1)
		{
			List<Integer> prime = new ArrayList<>();
			prime.add(2);
			
			returnVal = IntStream.iterate(3, val->val+2).filter(no->isNthPrime(prime, n, no)).findFirst().getAsInt();
		}
		return returnVal;
	}
	
	private static boolean isNthPrime(final List<Integer> prime, final int n, final int no)
	{
		if(isPrime(prime, no))
		{
			prime.add(no);
		}
		
		return prime.size() == n;
	}
	
	private static boolean isPrime(final List<Integer> prime, final int no)
	{
		return !prime.stream().filter(val->Math.sqrt(no) >= val).anyMatch(val->no%val == 0);
	}
	
	private static void checkN(final int n) throws IllegalArgumentException
	{
		if(n < 1)
		{
			throw new IllegalArgumentException();
		}
	}
}