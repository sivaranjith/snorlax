public final class Triangle
{
	private final double side1, side2, side3;
	
	public Triangle(final double side1, final double side2, final double side3) throws TriangleException
	{
		this.side1 = side1;
		this.side2 = side2;
		this.side3 = side3;
		
		checkForValidation();
	}
	
	private void checkForValidation() throws TriangleException
	{
		if(!isValidSides() || !isValidTriangleInEquality())
		{
			throw new TriangleException();
		}
	}
	
	private boolean isValidSides()
	{
		return this.side1 > 0 && this.side2 > 0 && this.side3 > 0;
	}
	
	private boolean isValidTriangleInEquality()
	{
		return (this.side1 + this.side2 > this.side3) && (this.side3 + this.side2 > this.side1) && (this.side1 + this.side3 > this.side2);
	}
	
	public TriangleKind getKind()
	{
		TriangleKind triangleKind = TriangleKind.SCALENE;
		
		if(isEquilateral())
		{
			triangleKind = TriangleKind.EQUILATERAL;
		}
		else if(isIsosceles())
		{
			triangleKind = TriangleKind.ISOSCELES;
		}
		
		return triangleKind;
	}
	
	private boolean isEquilateral()
	{
		return this.side1 == this.side2 && this.side2 == this.side3;
	}
	
	private boolean isIsosceles()
	{
		return this.side1 == this.side2 || this.side2 == this.side3 || this.side1 == this.side3;
	}
}