public final class GridPosition
{

    final int x;
    final int y;

    GridPosition(final int x, final int y)
    {
        this.x = x;
        this.y = y;
    }
    
    @Override
    public int hashCode()
    {
    	return this.x ^ this.y;
    }
    
    @Override
    public boolean equals(final Object obj)
    {
    	boolean returnValue = false;
    	if(obj instanceof GridPosition)
        {
    		GridPosition gridPosition = (GridPosition)obj;
    		returnValue = this.x == gridPosition.x && this.y == gridPosition.y;
        }
    	return returnValue;
    }
}