package structures;

import java.util.List;

public class Graph {
  Graph() {
    this.edges = new LinkedHashMap<List<Integer>>();
  }

  private Map<List<Integer>> edges;

  public void addEdge(int u, int v) {
    if (this.edges.containsKey(u)) {
      this.edges.get(u).add(v);
    } else {
      List<Integer> destList = new LinkedList<Integer>();
      destList.add(v);
      this.edges.put(u, destList);
    }
  }


  public List<Integer> adj(int u) {
    return this.edges.get(u);
  }
}
