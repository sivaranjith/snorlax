package structures;

import java.util.*;

/**
 * Created by scarecrow on 18/10/16.
 */
public class EdgeWeightedGraph extends Graph{

    private Map<Integer, List<Edge>> adj;

    public EdgeWeightedGraph () {
        this.adj = new LinkedHashMap<Integer, List<Edge>>();
    }

    public void addEdge (Edge e) {
        int v = e.either();
        addEdge(v, e);
        int w = e.other(v);
        addEdge(w, e);
    }

    private void addEdge (int v, Edge e) {
        if (this.adj.containsKey(v)) {
            this.adj.get(v).add(e);
        } else {
            List<Edge> edgeList = new LinkedList<Edge>();
            edgeList.add(e);
            this.adj.put(v, edgeList);
        }
        if (this.edges != null) {
            addToEdgeCache(e);
        }
    }

    public List adj (int v) {
        return this.adj.get(v);
    }

    private Set<Edge> edges; //cache edges

    public Iterable<Edge> edges () {
        if (edges == null) {
            loadEdges();
        }
        return this.edges;
    }

    private void loadEdges () {
        //lazy load edges
        if (edges == null) {
            edges = new LinkedHashSet<Edge>();
        }
        Set<Map.Entry<Integer, List<Edge>>> entrySet = adj.entrySet();
        for (Map.Entry<Integer, List<Edge>> entry : entrySet) {
            edges.addAll(entry.getValue());
        }
    }

    private void addToEdgeCache (Edge e) {
        if (edges == null) {
            edges = new LinkedHashSet<Edge>();
        }
        edges.add(e);
    }

//    public int V() {
//
//    }
//
//    public int E() {
//
//    }
}
