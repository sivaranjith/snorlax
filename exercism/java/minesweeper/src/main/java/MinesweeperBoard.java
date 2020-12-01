import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public final class MinesweeperBoard
{
	private final int[][] inputMatrix;
	
	public MinesweeperBoard(final List<String> inputBoard) throws IllegalArgumentException
	{
		checkInput(inputBoard);
		inputMatrix = inputBoard.stream().map(this::stringToIntArray).toArray(int[][]::new);
	}
	
	private int[] stringToIntArray(final String row) throws IllegalArgumentException
	{
		return row.chars().toArray();
	}
	
	public List<String> getAnnotatedRepresentation()
	{
		return IntStream.range(0, inputMatrix.length).mapToObj(this::fillPositions).collect(Collectors.toList());
	}
	
	private String fillPositions(final int rowIndex)
	{
		return IntStream.range(0, inputMatrix[0].length).mapToObj(colIndex->getPositionCount(rowIndex, colIndex)).collect(Collectors.joining());
	}
	
	private String getPositionCount(final int rowIndex, final int colIndex)
	{
		return inputMatrix[rowIndex][colIndex] == '*' ? "*" : getRowCount(rowIndex, colIndex);
	}
	
	private String getRowCount(final int rowIndex, final int colIndex)
	{
		int count = getColumnCount(rowIndex, colIndex);
		if(rowIndex != 0)
		{
			count += getColumnCount(rowIndex - 1, colIndex);
		}
		if(rowIndex + 1 != inputMatrix.length)
		{
			count += getColumnCount(rowIndex + 1, colIndex);
		}
		return count == 0 ? " " : String.valueOf(count);
	}
	
	private int getColumnCount(final int rowIndex, final int colIndex)
	{
		int count = 0;
		if(inputMatrix[rowIndex][colIndex] == '*')
		{
			++count;
		}
		if(colIndex != 0 && inputMatrix[rowIndex][colIndex - 1] == '*')
		{
			++count;
		}
		if(colIndex + 1 != inputMatrix[0].length && inputMatrix[rowIndex][colIndex + 1] == '*')
		{
			++count;
		}
		return count;
	}

	private void checkInput(final List<String> obj) throws IllegalArgumentException
	{
		if(obj == null)
		{
			throw new IllegalArgumentException("Input board may not be null.");
		}
		else if(obj.stream().anyMatch(ele->ele.matches(".*[^* ].*")))
		{
			throw new IllegalArgumentException("Input board can only contain the characters ' ' and '*'.");
		}
		else if(!obj.stream().allMatch(ele->ele.length() == obj.get(0).length()))
		{
			throw new IllegalArgumentException("Input board rows must all have the same number of columns.");
		}
		
	}
}