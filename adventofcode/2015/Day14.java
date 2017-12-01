package adventofcode.dec2015;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.function.BiFunction;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.util.stream.IntStream;

import adventofcode.dec2016.Utils;

public final class Day14
{
	
	private static final int FINISHING_TIME_IN_SECONDS = 2503;
	private static final BiFunction<String, Matcher, Integer> numFinder = (line, numMatcher)->{numMatcher.find(); return Integer.parseInt(numMatcher.group());};
	private static final List<RaindeerDetails> raindeerCollection = new ArrayList<>();
	
	public static void main(final String... args)
	{
		Utils.fileReader("../dec2015/day14input.txt", Day14::parseInput, Day14::findFastestRaindeer);
		
		IntStream.range(0, FINISHING_TIME_IN_SECONDS).forEach(time->addPointsToLeader());
		System.out.println(raindeerCollection.stream().max(Comparator.comparing(RaindeerDetails::getPoint)).get().point);
	}
	
	private static void addPointsToLeader()
	{
		final int maxDistance = raindeerCollection.stream().map(Day14::moveRaindeer).max(Comparator.comparing(RaindeerDetails::getCurrentDistance)).get().currentDistance;
		raindeerCollection.stream().filter(rainDeer->rainDeer.currentDistance == maxDistance).forEach(rainDeer->++rainDeer.point);
	}
	
	private static RaindeerDetails moveRaindeer(final RaindeerDetails rainDeer)
	{
		if(rainDeer.time > 0)
		{
			--rainDeer.time;
			if(rainDeer.time == 0)
			{
				rainDeer.time = -1 * rainDeer.restingTime;
			}
			rainDeer.currentDistance += rainDeer.speed;
		}
		else
		{
			++rainDeer.time;
			if(rainDeer.time == 0)
			{
				rainDeer.time = rainDeer.travellingTime;
			}
		}
		return rainDeer;
	}
	
	private static void findFastestRaindeer()
	{
		final int index = IntStream.range(0, raindeerCollection.size()).reduce((i, j)->raindeerCollection.get(i).travellingDistance < raindeerCollection.get(j).travellingDistance ? j : i ).getAsInt();
		System.out.println(index + "::" + raindeerCollection.get(index).travellingDistance);
	}

	private static void parseInput(String line)
	{
		Matcher numMatcher = Pattern.compile("\\d+").matcher(line);
		raindeerCollection.add(new RaindeerDetails(numFinder.apply(line, numMatcher), numFinder.apply(line, numMatcher), numFinder.apply(line, numMatcher)));
	}

	private static final class RaindeerDetails
	{
		final int speed, travellingTime, restingTime, travellingDistance;
		int currentDistance, time, point;
		
		public RaindeerDetails(final int speed, final int travellingTime, final int restingTime)
		{
			this.speed = speed;
			this.travellingTime = travellingTime;
			this.restingTime = restingTime;
			this.travellingDistance = getDistance();
			this.currentDistance = 0;
			this.time = this.travellingTime;
			this.point = 0;
		}
		
		private int getDistance()
		{
			final double completedTimes = FINISHING_TIME_IN_SECONDS / (double)(this.travellingTime + this.restingTime);
			int distance = (int)completedTimes * this.speed * this.travellingTime;
			final int remaining = (int)((completedTimes - (int)completedTimes) * (this.travellingTime + this.restingTime));

			return remaining > this.travellingTime ? distance + (this.speed * this.travellingTime) : distance + (this.speed * remaining) ;
		}
		
		int getCurrentDistance()
		{
			return this.currentDistance;
		}
		
		int getPoint()
		{
			return this.point;
		}
	}
}
