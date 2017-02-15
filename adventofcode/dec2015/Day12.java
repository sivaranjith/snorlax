package adventofcode.dec2015;

import java.util.Stack;
import java.util.function.BinaryOperator;
import java.util.function.UnaryOperator;

import adventofcode.dec2016.Utils;

public class Day12
{
    
    private static String input;
    private static int sum;

    public static void main(String[] args)
    {
        Utils.fileReader("../dec2015/day12input.txt", Day12::inputReader, ()->{controller(true);controller(false);});
    }
    
    private static void controller(boolean isRedAllowed)
    {
    	sum = 0;
    	parseInput(Day12.input, isRedAllowed);
    	printDetails();
    }
    
    private static void inputReader(String line)
    {
        Day12.input = line;
    }
    
    private static void parseInput(String line, boolean isRedAllowed)
    {
        Stack<BracketSession> stack = new Stack<>();
        BracketSession sessionObj = new BracketSession();
        MuttableHolder<Boolean> muttableBoolean = new MuttableHolder<>(false);
        
        UnaryOperator<Integer> originalValue = (temp)->(muttableBoolean.getValue() ? temp*-1 : temp);
        BinaryOperator<Integer> consumeDigit = (temp, index)->temp*10 + line.charAt(index) - '0';
        
        stack.push(sessionObj);
        sessionObj.addValue(0);
        sessionObj.setRed(false);
        
        for(int index = 0, temp = 0; index < line.length(); ++index)
        {
            if(Character.isDigit(line.charAt(index)))
            {
                temp = consumeDigit.apply(temp, index);
                continue;
            }
            else if(line.charAt(index) == '-')
            {
                muttableBoolean.apply(true);
                continue;
            }
            else if(line.charAt(index) == '[' || line.charAt(index) == '{')
            {
                sessionObj = new BracketSession();
                sessionObj.addValue(0);
                sessionObj.setRed(stack.peek().isRed());
                sessionObj.setBracket(line.charAt(index));
                stack.push(sessionObj);
            }
            else if(line.charAt(index) == 'r' && line.charAt(index + 1) == 'e' && line.charAt(index + 2) == 'd' && stack.peek().getBracket() == '{')
            {
                stack.peek().setRed(true);
                index += 2;
            }
            else if(line.charAt(index) == ']' || line.charAt(index) == '}')
            {
                sessionObj = stack.pop();
                int temp1 = sessionObj.getValue();
                if(Character.isDigit(line.charAt(index - 1)))
                {
                    temp1 += originalValue.apply(temp);
                }
                
                if(isRedAllowed || ((!sessionObj.isRed() && line.charAt(index) == '}') || line.charAt(index) == ']'))
                {
                    stack.peek().addValue(temp1);
                }
            }
            else if(temp != 0)
            {
                stack.peek().addValue(originalValue.apply(temp));
            }
            
            sessionObj = null;
            temp = 0;
            muttableBoolean.apply(false);
        }
        sum += stack.pop().getValue();
    }
    
    private static void printDetails()
    {
        System.out.println(sum);
    }
    
    private static class BracketSession
    {
        private char bracket;
        private int value;
        private boolean isRed;
        
        public char getBracket()
		{
			return bracket;
		}

		public BracketSession setBracket(char bracket)
		{
			this.bracket = bracket;
			return this;
		}

		public int getValue()
		{
			return value;
		}

		public boolean isRed()
		{
			return isRed;
		}

		public BracketSession setRed(boolean isRed)
		{
			this.isRed = isRed;
			return this;
		}

        public void addValue(int value)
        {
            this.value += value;
        }
    }

}
