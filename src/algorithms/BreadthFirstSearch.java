package algorithms;

import structures.Graph;
import structures.Queue;

import java.util.HashMap;

public class BreadthFirstSearch {
    private Queue q;
    private HashMap<Integer, Boolean> visited = new HashMap<Integer, Boolean>();

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
