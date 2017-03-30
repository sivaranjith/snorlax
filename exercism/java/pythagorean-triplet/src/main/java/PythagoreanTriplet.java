import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.IntStream;
import java.util.stream.Stream;

public final class PythagoreanTriplet
{

	private static final int STARTING_RANGE = 1, ENDING_RANGE = 1000;
	
	private final int s1, s2, s3; 

	public PythagoreanTriplet(final int s1, final int s2, final int s3)
	{
		this.s1 = s1;
		this.s2 = s2;
		this.s3 = s3;
	}

	public int calculateSum()
	{
		return this.s1 + this.s2 + this.s3;
	}

	public long calculateProduct()
	{
		return this.s1 * this.s2 * this.s3;
	}

	public boolean isPythagorean()
	{
		return Math.pow(this.s3, 2) == Math.pow(this.s1, 2) + Math.pow(this.s2, 2);
	}

	public static PythagoreanTripletList makeTripletsList()
	{
		return new PythagoreanTripletList(getPossibleValues());
	}
	
	private boolean isAllFactorsLess(final int limit)
	{
		return this.s1 <= limit && this.s2 <= limit && this.s3 <= limit;
	}
	
	private boolean isAllFactorsGreater(final int limit)
	{
		return this.s1 >= limit && this.s2 >= limit && this.s3 >= limit;
	}

	private static Stream<PythagoreanTriplet> getPossibleValues()
	{
		return IntStream.range(STARTING_RANGE, ENDING_RANGE).mapToObj(val -> val).flatMap(val->getPythagoreanTriplet(val));
	}
	
	private static Stream<PythagoreanTriplet> getPythagoreanTriplet(final int val1)
	{
		return IntStream.range(val1 + 1, ENDING_RANGE).mapToObj(val2 -> getPythagoreanTriplet(val1, val2)).filter(val -> val != null);
	}
	
	private static PythagoreanTriplet getPythagoreanTriplet(final int val1, final int val2)
	{
		final double val3 = Math.sqrt(Math.pow(val1, 2) + Math.pow(val2, 2));
		return (int)Math.ceil(val3) == (int)val3 ? new PythagoreanTriplet(val1, val2, (int)val3) : null;
	}

	public static final class PythagoreanTripletList
	{
		private Stream<PythagoreanTriplet> listStream;
		
		PythagoreanTripletList(final Stream<PythagoreanTriplet> pythagoreanNos)
		{
			listStream = pythagoreanNos;
		}

		public PythagoreanTripletList withFactorsLessThanOrEqualTo(final int limit)
		{
			listStream = listStream.filter(val -> val.isAllFactorsLess(limit));
			return this;
		}
		
		public PythagoreanTripletList withFactorsGreaterThanOrEqualTo(final int limit)
		{
			listStream = listStream.filter(val -> val.isAllFactorsGreater(limit));
			return this;
		}
		
		public PythagoreanTripletList thatSumTo(final int sum)
		{
			listStream = listStream.filter(val -> val.calculateSum() == sum);
			return this;
		}

		public List<PythagoreanTriplet> build()
		{
			return listStream.collect(Collectors.toList());
		}
	}
}
