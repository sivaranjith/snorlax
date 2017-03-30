import java.util.HashSet;
import java.util.List;
import java.util.Set;
import java.util.stream.Collectors;

public final class CustomSet<T>
{
	private final Set<T> set;
	
	public CustomSet(final List<T> inputList)
	{
		this.set = inputList.stream().collect(Collectors.toSet()); 
	}
	
	private CustomSet(final Set<T> inputSet)
	{
		this.set = new HashSet<>();
		this.set.addAll(inputSet);
	}
	
	public boolean isEmpty()
	{
		return this.set.isEmpty();
	}
	
	public boolean contains(final T ele)
	{
		return this.set.contains(ele);
	}
	
	public boolean isSubset(final CustomSet<T> other)
	{
		return this.set.containsAll(other.set);
	}
	
	public boolean equals(final CustomSet<T> other)
	{
		return this.set.equals(other.set);
	}
	
	public boolean add(T ele)
	{
		return this.set.add(ele);
	}
	
	public boolean isDisjoint(final CustomSet<T> other)
	{
		return !this.set.stream().anyMatch(ele->other.contains(ele));
	}
	
	public CustomSet<T> getIntersection(final CustomSet<T> other)
	{
		return new CustomSet<T>(set.stream().filter(ele->other.set.contains(ele)).collect(Collectors.toSet()));
	}
	
	public CustomSet<T> getDifference(final CustomSet<T> other)
	{
		return new CustomSet<T>(set.stream().filter(ele->!other.set.contains(ele)).collect(Collectors.toSet()));
	}
	
	public CustomSet<T> getUnion(final CustomSet<T> other)
	{
		final CustomSet<T> temp = new CustomSet<>(this.set);
		temp.set.addAll(other.set);
		return temp;
	}
}