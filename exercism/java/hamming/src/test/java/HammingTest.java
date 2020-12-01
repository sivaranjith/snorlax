import static org.hamcrest.CoreMatchers.*;
import static org.junit.Assert.*;

import org.junit.Test;
import org.junit.Ignore;
import org.junit.Rule;
import org.junit.rules.ExpectedException;

public class HammingTest {
    

    @Rule
    public ExpectedException thrown = ExpectedException.none();
    
    @Test
    public void testNoDifferenceBetweenIdenticalStrands() {
        assertThat(Hamming.compute("A", "A"), is(0));
    }

    
    @Test
    public void testHammingDistanceForSingleNucleotideStrand() {
        assertThat(Hamming.compute("A", "G"), is(1));
    }

    
    @Test
    public void testHammingDistanceForSmallStrand() {
        assertThat(Hamming.compute("AG", "CT"), is(2)); 
    }

    
    @Test
    public void testSmallHammingDistance() {
        assertThat(Hamming.compute("AT", "CT"), is(1));
    }

    
    @Test
    public void testSmallHammingDistanceInLongerStrand() {
        assertThat(Hamming.compute("GGACG", "GGTCG"), is(1));
    }

    
    @Test
    public void testValidatesFirstStrandNotLonger() {
        thrown.expect(IllegalArgumentException.class);
        Hamming.compute("AAAG", "AAA");                
    }

    
    @Test
    public void testValidatesOtherStrandNotLonger() {
        thrown.expect(IllegalArgumentException.class);
        Hamming.compute("AAA", "AAAG");
    }

    
    @Test
    public void testLargeHammingDistance() {
        assertThat(Hamming.compute("GATACA", "GCATAA"), is(4));
    }

    
    @Test
    public void testHammingDistanceInVeryLongStrand() {
        assertThat(Hamming.compute("GGACGGATTCTG", "AGGACGGATTCT"), is(9));
    }

}
