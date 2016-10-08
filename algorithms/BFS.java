package algorithms;

import structures.Graph;
import structures.Queue;

public class BFS {
    private Queue q;
    private HashMap<int, boolean> visited = new HashMap<int, boolean>();

    public void bfs(Graph g, int u) {
        q = new Queue();
        q.enqueue(u);
        visited.put(u, true);
        while (!q.isEmpty()) {
            q.dequeue(); //assign to a variable if needed
            for (int v : g.adj(u)) {
                if (!visited.containsKey(v) || !visited.get(v)) {
                    visited.put(v, true);
                    q.enqueue(v);
                }
            }
        }
    }
}
