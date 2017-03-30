import java.util.ArrayList;
import java.util.Collection;
import java.util.List;
import java.util.Objects;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public final class Flattener
{

	public Flattener()
	{
	}
	
	public List<Object> flatten(final List<Object> list)
	{
		return this.getStreamFromObj(list).filter(Objects::nonNull).collect(Collectors.toList());
	}
	
	private Stream<Object> getStreamFromObj(final Object element)
	{
		return (element instanceof List) ? ((List<?>)element).stream().flatMap(this::getStreamFromObj) : Stream.of(element);
	}
}