import java.util.List;
import java.util.stream.IntStream;

public final class RelationshipComputer<E extends Comparable<?>>
{
	public RelationshipComputer()
	{
	}

	public Relationship computeRelationship(final List<E> list1, final List<E> list2)
	{
		Relationship returnValue = Relationship.UNEQUAL;
		if(list1.size() == list2.size() && contains(list1, list2))
		{
			returnValue = Relationship.EQUAL;
		}
		else if(list1.size() > list2.size() && contains(list2, list1))
		{
			returnValue = Relationship.SUPERLIST;
		}
		else if(list1.size() < list2.size() && contains(list1, list2))
		{
			returnValue = Relationship.SUBLIST;
		}
		return returnValue;
	}
	
	private boolean contains(final List<E> list1, final List<E> list2)
	{
		return list1.isEmpty() || IntStream.rangeClosed(0, list2.size() - list1.size()).anyMatch(index->isStart(list1, list2, index));
	}
	
	private boolean isStart(final List<E> list1, final List<E> list2, final int startIndex)
	{
		final boolean isStart = (list2.get(startIndex) == list1.get(0)) && (startIndex + list1.size()  <= list2.size());
		return isStart && contains(list1, list2, startIndex);
	}
	
	private boolean contains(final List<E> list1, final List<E> list2, final int startIndex)
	{
		return IntStream.range(0, list1.size()).allMatch(index->list1.get(index) == list2.get(startIndex + index));
	}
}