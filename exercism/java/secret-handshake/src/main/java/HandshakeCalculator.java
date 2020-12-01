import java.util.Collections;
import java.util.stream.Collectors;
import java.util.List;
import java.util.Map;
import java.util.LinkedHashMap;

public final class HandshakeCalculator
{
	private static final Map<Integer, Signal> container = new LinkedHashMap<>(4);
	
	static
	{
		container.put(1, Signal.WINK);
		container.put(2, Signal.DOUBLE_BLINK);
		container.put(4, Signal.CLOSE_YOUR_EYES);
		container.put(8, Signal.JUMP);
	}
	
	public HandshakeCalculator()
	{
	}
	
	public List<Signal> calculateHandshake(final int input)
	{
		final List<Signal> result = container.keySet().stream().filter(no->isValidHandShake(input, no)).map(container::get).collect(Collectors.toList());
		if(isValidHandShake(input, 16))
		{
			Collections.reverse(result);
		}
		return result;
	}
	
	private boolean isValidHandShake(final int input, final int no)
	{
		return (input&no) == no;
	}
}
