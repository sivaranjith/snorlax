package algorithms;

import structures.Graph;
import java.util.Map;
import java.util.HashMap;

public class DFS {

    private Map<Integer, Boolean> visited = new HashMap<Integer, Boolean>();

    public void dfs(Graph g, int u) {
        visited.put(u, true);
        for (int i : g.adj(u)) {
            if (!visited.containsKey(u) || !visited.get(u)) {
                dfs(g, i);
            }
        }
    }
}