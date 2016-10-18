package structures;

import java.util.Comparator;

/**
 * Created by scarecrow on 18/10/16.
 */
public class Edge implements Comparable<Edge>{
    /*
    representation of a weighted edge. referred from Sedgewick & Weiss
    */

    private final int v, w; //vertex endpoints
    private final double weight;

    public Edge (int v, int w, double weight) {
        this.v = v;
        this.w = w;
        this.weight = weight;
    }

    public int either() {
        return this.v;
    }

    public int other(int v) {
        if (v == this.v) {
            return this.w;
        } else {
            return this.v;
        }

    }

    public double weight() {
        return this.weight;
    }

    public int compareTo(Edge that) {
        if (this.weight > that.weight) {
            return 1;
        } else if (this.weight < that.weight){
            return -1;
        } else {
            return 0;
        }
    }

    public boolean equals(Edge that) {
        return this.v == that.v && this.w == that.w && this.weight == that.weight;
    }
}
