package adventofcode.dec2015;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.function.BinaryOperator;
import java.util.function.UnaryOperator;
import java.util.regex.Pattern;

import adventofcode.dec2016.Utils;

public class Day7
{

	private static final Map<String, Integer> register = new HashMap<>();
	private static final List<String> instructions = new ArrayList<>();
	private static final String DESTINATION_WIRE = "a";
	
	public static void main(String[] args)
	{
		Utils.fileReader("../dec2015/day7input.txt", (String line)->processInstruction(line), ()->{processInstruction();partTwo();printDetails();});
	}

	private static void processInstruction(String line)
	{
		instructions.add(line);
	}
	
	private static void processInstruction()
	{
		for(String instruction : instructions)
		{
			parseInstruction(instruction);
		}
		
		if(register.get(DESTINATION_WIRE) == null && !instructions.isEmpty())
		{
			processInstruction();
		}
	}
	
	private static void parseInstruction(String instruction)
	{
		String tokens[] = instruction.split(" ");
		
		if(instruction.contains("AND"))
		{
			doubleInputInstruction(tokens[0], tokens[2], tokens[4], (num1, num2)-> num1&num2);
		}
		else if(instruction.contains("OR"))
		{
			doubleInputInstruction(tokens[0], tokens[2], tokens[4], (num1, num2)-> num1|num2);
		}
		else if(instruction.contains("LSHIFT"))
		{
			doubleInputInstruction(tokens[0], tokens[2], tokens[4], (num1, num2)-> num1<<num2);
		}
		else if(instruction.contains("RSHIFT"))
		{
			doubleInputInstruction(tokens[0], tokens[2], tokens[4], (num1, num2)-> num1>>num2);
		}
		else if(instruction.contains("NOT"))
		{
			singleInputInstruction(tokens[1], tokens[3], (num)-> ~num);
		}
		else
		{
			singleInputInstruction(tokens[0], tokens[2], (num)->num);
		}
	}
	
	private static void doubleInputInstruction(String inputRegister1, String inputRegister2, String outputRegister, BinaryOperator<Integer> operation)
	{
		Integer num1 = parsedValue(inputRegister1), num2 = parsedValue(inputRegister2);
		
		if(num1 != null && num2 != null)
		{
			register.put(outputRegister, operation.apply(num1, num2));
		}
		
	}
	
	private static void singleInputInstruction(String inputRegister, String outputRegister, UnaryOperator<Integer> operation)
	{
		Integer outputVal = parsedValue(inputRegister);
		
		if(outputVal != null)
		{
			register.put(outputRegister, operation.apply(outputVal));
		}
	}
	
	private static Integer parsedValue(String inputRegister)
	{
		Integer outputVal = null;

		if(register.get(inputRegister) == null)
		{
			if(Character.isDigit(inputRegister.charAt(0)))
			{
				outputVal = Integer.parseInt(inputRegister);
			}
		}
		else
		{
			outputVal = register.get(inputRegister);
		}
		
		return outputVal;
	}
	
	private static void partTwo()
	{
		printDetails();
		
		final Pattern p = Pattern.compile("^(\\d)+ -> b$");
		final int DESTINATION_WIRE_VALUE = register.get(DESTINATION_WIRE);
		final String matchedInstruction = instructions.stream().filter((instruction)->p.matcher(instruction).find()).findFirst().get();
	
		instructions.remove(matchedInstruction);
		instructions.add(DESTINATION_WIRE_VALUE + " -> b");
		register.clear();
		
		processInstruction();
	}

	private static void printDetails()
	{
		System.out.println(register.get(DESTINATION_WIRE));
	}
	
}