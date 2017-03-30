import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;

public final class Allergies
{
	
	private final int val;
	private List<Allergen> allAllergicItems;
	
	public Allergies(final int val)
	{
		this.val = val;
		this.allAllergicItems = getAllegricItems((byte)val);
	}
	
	public boolean isAllergicTo(final Allergen type)
	{
		return (val & type.getScore()) == type.getScore();
	}
	
	public List<Allergen> getList()
	{
		return this.allAllergicItems;
	}
	
	private List<Allergen> getAllegricItems(final byte val)
	{
		return Arrays.stream(Allergen.values()).filter(this::isAllergicTo).collect(Collectors.toList());
	}
}