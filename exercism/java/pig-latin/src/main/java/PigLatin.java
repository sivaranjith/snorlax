import java.util.Arrays;
import java.util.stream.Collectors;

public final class PigLatin
{
	//values taken from @DeepspaceFreelancer
	private static final String[] SINGLE_CONSONANT = {"ch", "qu", "thr", "th", "sch", "bqu", "cqu", "dqu", "fqu", "gqu", "hqu", "jqu", "kqu", "lqu", "mqu", "nqu", "pqu", "qqu", "rqu", "squ", "tqu", "vqu", "wqu", "xqu", "yqu", "zqu", "b", "c", "d", "f", "g", "h", "j", "k", "l", "m", "n", "p", "q", "r", "s", "t", "v", "w", "x", "y", "z"};
	private static final String[] SINGLE_VOWEL = {"yt", "xr"};
	
	private PigLatin()
	{
	}
	
	public static String translate(final String englishWord)
	{
		return Arrays.stream(englishWord.split(" ")).map(PigLatin::firstRuleTranslation).collect(Collectors.joining(" "));
	}
	
	private static String firstRuleTranslation(final String englishWord)
	{		
		return secondRuleTranslation(englishWord) + "ay";
	}
	
	private static String secondRuleTranslation(final String englishWord)
	{
		return isVowel(englishWord.charAt(0)) ? englishWord : consonantTranslation(englishWord);
	}
	
	private static String consonantTranslation(final String englishWord)
	{
		String start = "";

		if(getPrefixSingleVowel(englishWord) == null)
		{
			start = getPrefixSingleConstant(englishWord);
		}
		
		return englishWord.substring(start.length()) + start;
	}
	
	private static String getPrefixSingleConstant(final String englishWord)
	{
		return Arrays.stream(SINGLE_CONSONANT).filter(cons->englishWord.startsWith(cons)).findFirst().orElse(null);
	}
	
	private static String getPrefixSingleVowel(final String englishWord)
	{
		return Arrays.stream(SINGLE_VOWEL).filter(vow->englishWord.startsWith(vow)).findFirst().orElse(null);
	}
	
	private static boolean isVowel(final char letter)
	{
		return letter == 'a' || letter == 'e' || letter == 'i' || letter == 'o' || letter == 'u';
	}
}