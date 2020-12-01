import java.util.HashSet;
import java.util.Random;
import java.util.Set;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public final class Robot
{
	
	private String name;
	private static final Set<String> cache = new HashSet<>();
	private static final Random randomObj = new Random();
	
	public Robot()
	{
		setName();
	}
	
	public String getName()
	{
		return this.name;
	}
	
	public void reset()
	{
		setName();
	}
	
	private String getValidName()
	{
		return IntStream.range(0, 5).mapToObj(this::getRandomCharacter).collect(Collectors.joining());
	}
	
	private void setName()
	{
		cache.remove(this.name);
		
		this.name = IntStream.iterate(0,__->0).mapToObj(__->getValidName()).filter(this::isValidName).findFirst().orElse(null);
		
		cache.add(this.name);
	}
	
	private boolean isValidName(final String name)
	{
		return !cache.contains(name);
	}
	
	private String getRandomCharacter(final int index)
	{
		final int randomCharacter = index < 2 ? getRandomNumber(26) + 'A' : getRandomNumber(10) + '0';
		return String.valueOf((char)randomCharacter);
	}
	
	private int getRandomNumber(final int limit)
	{
		return randomObj.nextInt(limit);
	}
}