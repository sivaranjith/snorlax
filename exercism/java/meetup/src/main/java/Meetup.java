import java.time.DayOfWeek;
import java.time.LocalDate;

public final class Meetup
{
	
	private final int month, year;
	
	public Meetup(final int month, final int year)
	{
		this.month = month;
		this.year = year;
	}
	
	public LocalDate day(final DayOfWeek dayOfWeek, final MeetupSchedule schedule)
	{
		LocalDate startingDate;

		if(schedule == MeetupSchedule.TEENTH)
		{
			startingDate = LocalDate.of(this.year, this.month, 13);
		}
		else
		{
			startingDate = LocalDate.of(this.year, this.month, 1);
		}

		int diff = (7 + dayOfWeek.compareTo(startingDate.getDayOfWeek()))%7;

		if(schedule == MeetupSchedule.SECOND)
		{
			diff += 7;
		}
		else if(schedule == MeetupSchedule.THIRD)
		{
			diff += 14;
		}
		else if(schedule == MeetupSchedule.FOURTH || schedule == MeetupSchedule.LAST)
		{
			diff += 21;
			if(schedule == MeetupSchedule.LAST && diff >= 21 && diff <= 23 && startingDate.lengthOfMonth() >= diff + 7)
			{
				diff += 7;
			}
		}

		startingDate = startingDate.plusDays(diff);
		
		return startingDate;
	}
}