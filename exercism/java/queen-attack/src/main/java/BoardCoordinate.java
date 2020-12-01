public final class BoardCoordinate
{
	
	private final int x, y;
	
	public BoardCoordinate(final int x, final int y) throws IllegalArgumentException
	{
		checkCoordinate(x, "rank");
		checkCoordinate(y, "file");
		this.x = x;
		this.y = y;
		
	}
	
	private void checkCoordinate(final int coordinate, final String type) throws IllegalArgumentException
	{
		if(coordinate < 0)
		{
			throw new IllegalArgumentException("Coordinate must have positive " + type + ".");
		}
		else if(coordinate >= 8)
		{
			throw new IllegalArgumentException("Coordinate must have " + type + " <= 7.");
		}
	}
	
	public int getX()
	{
		return this.x;
	}
	
	public int getY()
	{
		return this.y;
	}
	
	@Override
	public int hashCode()
	{
		return this.x ^ this.y;
	}
	
	@Override
	public boolean equals(final Object obj)
	{
		boolean isEqual = false;
		
		if(obj instanceof BoardCoordinate)
		{
			final BoardCoordinate other = (BoardCoordinate)obj;
			isEqual = (this.x == other.x && this.y == other.y);
		}
		
		return isEqual;
	}
}