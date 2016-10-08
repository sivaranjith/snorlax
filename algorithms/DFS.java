package algorithms;

import structures.Graph;

public class DFS {

    private Map<int, boolean> visited = new HashMapM<int, boolean>();

    public void dfs(Graph g, int u) {
        visited.put(u, true);
        for (int i : g.adj(u)) {
            if (!visited.containsKey(u) || !visited.get(u)) {
                dfs(g, v);
            }
        }
    }
}