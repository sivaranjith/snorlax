//not my idea of implemtation
enum Orientation implements Rotation
{
    NORTH
    {
    	@Override
    	public Orientation turnRight()
    	{
    		return EAST;
    	}
    	
    	@Override
    	public Orientation turnLeft()
    	{
    		return WEST;
    	}

		@Override
		public GridPosition advance(final int x, final int y)
		{
			return new GridPosition(x, y + 1);
		}
    },
    EAST
    {
    	@Override
    	public Orientation turnRight()
    	{
    		return SOUTH;
    	}
    	
    	@Override
    	public Orientation turnLeft()
    	{
    		return NORTH;
    	}

		@Override
		public GridPosition advance(final int x, final int y)
		{
			return new GridPosition(x + 1, y);
		}
    },
    SOUTH
    {
    	@Override
    	public Orientation turnRight()
    	{
    		return WEST;
    	}
    	
    	@Override
    	public Orientation turnLeft()
    	{
    		return EAST;
    	}

		@Override
		public GridPosition advance(final int x, final int y)
		{
			return new GridPosition(x, y - 1);
		}
    },
    WEST
    {
    	@Override
    	public Orientation turnRight()
    	{
    		return NORTH;
    	}
    	
    	@Override
    	public Orientation turnLeft()
    	{
    		return SOUTH;
    	}

		@Override
		public GridPosition advance(final int x, final int y)
		{
			return new GridPosition(x - 1, y);
		}
    };
}

interface Rotation
{
	Orientation turnRight();
	Orientation turnLeft();
	GridPosition advance(int x, int y);
}