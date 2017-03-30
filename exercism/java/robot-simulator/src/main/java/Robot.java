//not my idea of implemtation
public final class Robot
{
	private GridPosition currentPosition;
	private Orientation direction;
	
	public Robot(final GridPosition initialPosition, final Orientation direction)
	{
		this.currentPosition = initialPosition;
		this.direction = direction;
	}
	
	public void turnRight()
	{
		direction = direction.turnRight();
	}
	
	public void turnLeft()
	{
		direction = direction.turnLeft();
	}
	
	public void advance()
	{
		final int x = currentPosition.x, y = currentPosition.y;
		currentPosition = direction.advance(x, y);
	}
	
	public Orientation getOrientation()
	{
		return this.direction;
	}
	
	public GridPosition getGridPosition()
	{
		return this.currentPosition;
	}
	
	public void simulate(final String instructions)
	{
		instructions.chars().forEach(this::controller);
	}
	
	private void controller(final int instruction)
	{
		if(instruction == 'L')
		{
			this.turnLeft();
		}
		else if(instruction == 'R')
		{
			this.turnRight();
		}
		else if(instruction == 'A')
		{
			this.advance();
		}
	}
}