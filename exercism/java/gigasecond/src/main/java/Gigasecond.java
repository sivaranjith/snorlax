import java.time.LocalDate;
import java.time.LocalDateTime;

final public class Gigasecond
{
	private final LocalDateTime gigathSecond;
	private static final long GIGA_SECONDS = 1_000_000_000L;
	
	public Gigasecond(final LocalDate birthTime)
	{
		this(birthTime.atStartOfDay());
	}
	
	public Gigasecond(final LocalDateTime birthTime)
	{
		gigathSecond = Gigasecond.calculateGigaSecond(birthTime);
	}
	
	private static LocalDateTime calculateGigaSecond(final LocalDateTime birthTime)
	{
		return birthTime.plusSeconds(GIGA_SECONDS);
	}
	
	public LocalDateTime getDate()
	{
		return gigathSecond;
	}
}