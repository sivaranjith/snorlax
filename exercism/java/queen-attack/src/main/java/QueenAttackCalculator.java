public final class QueenAttackCalculator
{
	
	private final boolean canQueenAttack;
	
	public QueenAttackCalculator(final BoardCoordinate whiteQueen, final BoardCoordinate blackQueen) throws IllegalArgumentException
	{
		checkCoordinate(whiteQueen, blackQueen);
		canQueenAttack = canAttack(whiteQueen, blackQueen);
	}
	
	public boolean canQueensAttackOneAnother()
	{
		return canQueenAttack;
	}
	
	private boolean canAttack(final BoardCoordinate whiteQueen, final BoardCoordinate blackQueen)
	{
		return isSameRow(whiteQueen, blackQueen) || isSameColumn(whiteQueen, blackQueen) || isDiagonal(whiteQueen, blackQueen);
	}
	
	private boolean isSameRow(final BoardCoordinate whiteQueen, final BoardCoordinate blackQueen)
	{
		return whiteQueen.getX() == blackQueen.getX();
	}
	
	private boolean isSameColumn(final BoardCoordinate whiteQueen, final BoardCoordinate blackQueen)
	{
		return whiteQueen.getY() == blackQueen.getY();
	}
	
	private boolean isDiagonal(final BoardCoordinate whiteQueen, final BoardCoordinate blackQueen)
	{
		return Math.abs(whiteQueen.getX() - blackQueen.getX()) == Math.abs(whiteQueen.getY() - blackQueen.getY());
	}
	
	private void checkCoordinate(final BoardCoordinate whiteQueen, final BoardCoordinate blackQueen) throws IllegalArgumentException
	{
		if(whiteQueen == null || blackQueen == null)
		{
			throw new IllegalArgumentException("You must supply valid board coordinates for both Queens.");
		}
		else if(whiteQueen.equals(blackQueen))
		{
			throw new IllegalArgumentException("Queens may not occupy the same board coordinate.");
		}
	}
}