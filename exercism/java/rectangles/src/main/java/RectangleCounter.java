import java.util.ArrayList;
import java.util.List;
import java.util.function.BiPredicate;
import java.util.stream.IntStream;

public final class RectangleCounter
{
	
	private String[] inputGrid;
	private final List<Point> plusLocations = new ArrayList<>();
	private int rectangleCount = 0;
	
	public RectangleCounter()
	{
	}
	
	public int countRectangles(final String[] inputGrid)
	{
		this.inputGrid = inputGrid; 

		IntStream.range(0, inputGrid.length).forEach(this::getPlusIndexInRow); 

		findRectangles();

		return rectangleCount;
	}
	
	private void findRectangles()
	{
		plusLocations.stream().forEach(this::findDiagonalPoint);
	}
	
	private void findDiagonalPoint(final Point tlPoint)
	{
		rectangleCount += plusLocations.stream().mapToInt(brPoint->getRectangleCount(tlPoint, brPoint)).sum();
	}
	
	private int getRectangleCount(final Point tlPoint, final Point brPoint)
	{
		return isRecatanglePossible(tlPoint, brPoint) ? 1 : 0;
	}
	
	private boolean isRecatanglePossible(final Point tlPoint, final Point brPoint)
	{
		return tlPoint.isBottomRight(brPoint) && isPlusLocated(tlPoint.x, brPoint.y) && isPlusLocated(brPoint.x, tlPoint.y) && isTravesalPossible(tlPoint, brPoint);
	}
	
	private boolean isTravesalPossible(final Point tlPoint, final Point brPoint)
	{
		return isHorizontalTravesalPossible(tlPoint.x, tlPoint.y, brPoint.y) && isHorizontalTravesalPossible(brPoint.x, tlPoint.y, brPoint.y) && isVerticalTravesalPossible(tlPoint.y, tlPoint.x, brPoint.x) && isVerticalTravesalPossible(brPoint.y, tlPoint.x, brPoint.x);
	}
	
	private boolean isHorizontalTravesalPossible(int fixedX, int startingY, int endingY)
	{
		BiPredicate<Integer, Integer> isHorizontal = (x, y)-> inputGrid[x].charAt(y) == '+' || inputGrid[x].charAt(y) == '-';
		return IntStream.rangeClosed(startingY, endingY).allMatch(currentY->isHorizontal.test(fixedX, currentY));
	}
	
	private boolean isVerticalTravesalPossible(int fixedY, int startingX, int endingX)
	{
		BiPredicate<Integer, Integer> isVertical = (x, y)-> inputGrid[x].charAt(y) == '+' || inputGrid[x].charAt(y) == '|';
		return IntStream.rangeClosed(startingX, endingX).allMatch(currentX->isVertical.test(currentX, fixedY));
	}
	
	private void getPlusIndexInRow(final int rowIndex)
	{
		IntStream.range(0, inputGrid[0].length()).filter(colIndex->isPlusLocated(rowIndex, colIndex)).forEach(colIndex->plusLocations.add(new Point(rowIndex, colIndex)));
	}
	
	private boolean isPlusLocated(final int x, final int y)
	{
		return inputGrid[x].charAt(y) == '+';
	}
	
	private static final class Point
	{
		final int x, y;
		
		Point(final int x, final int y)
		{
			this.x = x;
			this.y = y;
		}
		
		boolean isBottomRight(Point brPoint)
		{
			return brPoint.y > this.y && brPoint.x > this.x;
		}
		
		@Override
		public int hashCode()
		{
			return x^y;
		}
		
		@Override
		public boolean equals(final Object obj)
		{
			boolean isEqual = false;
			if(obj instanceof Point)
			{
				final Point otherPoint = (Point)obj;
				isEqual = this.x == otherPoint.x && this.y == otherPoint.y;
			}
			return isEqual;
		}
		
		@Override
		public String toString()
		{
			return "x = " + x + ", y = " + y + ";";
		}
	}
}