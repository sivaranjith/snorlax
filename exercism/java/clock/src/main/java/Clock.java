public final class Clock
{
	private int hours, minutes;
	
	public Clock(final int hours, final int minutes)
	{
		this.hours = hours < 0 ? hours%24 + 24 : hours%24;
		add(minutes);
	}
	
	public void add(int minutes)
	{
		if(minutes < 0)
		{
			minutes = (minutes % 1440) + 1440;
		}
		
		this.hours = (this.hours + (this.minutes + minutes)/60) % 24;
		this.minutes = (this.minutes + minutes)%60;
	}
	
	@Override
	public boolean equals(Object o)
	{
		boolean isEquals = false;
		
		if(o instanceof Clock)
		{
			Clock other = (Clock)o;
			isEquals = (this.hours == other.hours) && (this.minutes == other.minutes);
		}
		
		return isEquals;
	}
		
	@Override
	public String toString()
	{
		return getNum(this.hours) + ":" + getNum(this.minutes);
	}
	
	private String getNum(final int num)
	{
		return (num < 10 ? "0" : "") + num;
	}
}