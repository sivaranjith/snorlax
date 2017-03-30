import java.io.File;
import java.io.FileOutputStream;
import java.io.PrintWriter;
import java.util.Arrays;

public final class Matrix
{
	
	private final int[][] matrix;
	
	public Matrix(final String input)
	{
		matrix = getMatrix(input);
	}
	
	private int[][] getMatrix(final String input)
	{
		return Arrays.stream(input.split("\\n")).map(this::splitColumn).toArray(int[][]::new);
	}
	
	private int[] splitColumn(final String row)
	{
		return Arrays.stream(row.split(" ")).mapToInt(Integer::parseInt).toArray();
	}
	
	public int getColumnsCount()
	{
		return matrix[0].length;
	}
	
	public int getRowsCount()
	{
		return matrix.length;
	}
	
	public int[] getRow(final int index)
	{
		return Arrays.copyOf(matrix[index], matrix[index].length);
	}
	
	public int[] getColumn(final int index)
	{
		return Arrays.stream(this.matrix).mapToInt(row->row[index]).toArray();
	}
}