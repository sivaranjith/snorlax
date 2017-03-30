final public class SpaceAge
{
	private final long ageInSec;
	private static final long EARTH_REVOLUTION_TIME_IN_SECONDS = 31557600L;
	
	public SpaceAge(final long ageInSec)
	{
		this.ageInSec = ageInSec;
	}
	
	public long getSeconds()
	{
		return this.ageInSec;
	}
	
	public double onMercury()
	{
		return calculateAge(RevolutionTime.MERCURY);
	}
	
	public double onVenus()
	{
		return calculateAge(RevolutionTime.VENUS);
	}
	
	public double onEarth()
	{
		return calculateAge(RevolutionTime.EARTH);
	}

	public double onMars()
	{
		return calculateAge(RevolutionTime.MARS);
	}
	
	public double onJupiter()
	{
		return calculateAge(RevolutionTime.JUPITER);
	}
	
	public double onSaturn()
	{
		return calculateAge(RevolutionTime.SATURN);
	}
	
	public double onUranus()
	{
		return calculateAge(RevolutionTime.URANUS);
	}
	
	public double onNeptune()
	{
		return calculateAge(RevolutionTime.NEPTUNE);
	}
	
	private double calculateAge(final double revolutionTime)
	{
		return this.ageInSec/revolutionTime;
	}
	
	private static final class RevolutionTime
	{
		private static final double MERCURY = 0.2408467 * EARTH_REVOLUTION_TIME_IN_SECONDS;
		private static final double VENUS = 0.61519726 * EARTH_REVOLUTION_TIME_IN_SECONDS;
		private static final double EARTH = 1.0 * EARTH_REVOLUTION_TIME_IN_SECONDS;
		private static final double MARS = 1.8808158 * EARTH_REVOLUTION_TIME_IN_SECONDS;
		private static final double JUPITER = 11.862615 * EARTH_REVOLUTION_TIME_IN_SECONDS;
		private static final double SATURN = 29.447498 * EARTH_REVOLUTION_TIME_IN_SECONDS;
		private static final double URANUS = 84.016846 * EARTH_REVOLUTION_TIME_IN_SECONDS;
		private static final double NEPTUNE = 164.79132 * EARTH_REVOLUTION_TIME_IN_SECONDS;
	}
}