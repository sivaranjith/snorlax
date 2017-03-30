package example;

import java.util.HashSet;
import java.util.Set;

public final class IsogramChecker
{
	
	public IsogramChecker()
	{
	}

	public boolean isIsogram(final String inputString)
	{
		final Set<Integer> container = new HashSet<>();
		return inputString.replaceAll("\\P{IsAlphabetic}", "").toLowerCase().chars().allMatch(c->container.add(c));
	}
}
