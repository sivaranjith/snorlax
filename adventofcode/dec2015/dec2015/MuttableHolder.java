package adventofcode.dec2015;

public class MuttableHolder<T>
{
	private T value;
	
	public MuttableHolder(T value)
	{
		this.value = value;
	}
	
	public void apply(T change)
	{
		this.value = change;
	}
	
	public T getValue()
	{
		return this.value;
	}
	
}