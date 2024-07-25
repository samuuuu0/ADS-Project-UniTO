package base;

import java.io.BufferedReader;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Comparator;
import java.util.HashSet;
import java.util.Set;

public class Prim {

    public static <V, L extends Number> Collection<? extends AbstractEdge<V, L>> minimumSpanningForest(
            Graph<V, L> graph) {

        // set to keep trace of visited nodes
        Set<V> visited = new HashSet<>();
        // list to save all the nodes that form the MST
        Collection<Graph.Edge<V, L>> msf = new ArrayList<>();
        // priority queue to save edges sorted by weight
        PriorityQueue<Graph.Edge<V, L>> heap = new PriorityQueue<>(new Comparator<Graph.Edge<V, L>>() {
            @Override
            public int compare(Graph.Edge<V, L> x, Graph.Edge<V, L> y) {
                // compare edges based on their weight
                return Double.compare(x.getLabel().doubleValue(), y.getLabel().doubleValue());
            }
        });

        for (V node : graph.getNodes()) {
            // checks if the node has already been visited
            if (!visited.add(node))
                continue;

            // add all neighbors to the priority queue
            Collection<V> neighbors = graph.getNeighbours(node);
            for (V neighbor : neighbors)
                heap.push(new Graph.Edge<>(node, neighbor, graph.getLabel(node, neighbor)));

            while (!heap.empty()) {
                // extract the minimum edge from the priority queue
                Graph.Edge<V, L> min = heap.top();
                heap.pop();

                // checks the end node of the edge
                if (!visited.add(min.getEnd()))
                    continue;

                // add the minimum edge to the minimum spanning forest
                msf.add(min);

                // work with the last node of the minimal edge
                Collection<V> minNeighbours = graph.getNeighbours(min.getEnd());
                for (V neighbor : minNeighbours)
                    if (!visited.contains(neighbor))
                        heap.push(
                            new Graph.Edge<>(
                                min.getEnd(), 
                                neighbor, 
                                graph.getLabel(min.getEnd(), neighbor)
                            )
                        );
            }
        }

        return msf;
    }

    // Required Arguments: java -cp bin base.Prim <input_file.csv>
    public static void main(String[] args) {
        if (args.length != 1)
            throw new IllegalArgumentException("Usage: java -cp bin base.Prim <input_file.csv>");
        String path = args[0];

        Graph<String, Double> graph = initializeGraph(path);
        // collection to store the minimum spanning forest of the graph
        Collection<? extends AbstractEdge<String, Double>> msf = minimumSpanningForest(graph);
        printResults(msf);
    }

    // undirected and weighted graph initialization
    private static Graph<String, Double> initializeGraph(String path) {
        Graph<String, Double> graph = new Graph<>(false, true);

        try (BufferedReader reader = new BufferedReader(new FileReader(path))) {
            String line;
            while ((line = reader.readLine()) != null) {
                String[] fields = line.split(",");
                if (fields.length == 3) {
                    graph.addNode(fields[0]);
                    graph.addNode(fields[1]);
                    graph.addEdge(fields[0], fields[1], Double.parseDouble(fields[2]));
                }
            }
        } catch (Exception e) {
            System.err.println("Error reading file: " + path);
            e.printStackTrace();
            System.exit(1);
        }

        return graph;
    }

    private static void printResults(Collection<? extends AbstractEdge<String, Double>> msf) {
        Set<String> nodes = new HashSet<>();
        double distance = 0;

        for (AbstractEdge<String, Double> edge : msf) {
            distance += edge.getLabel();
            nodes.add(edge.getStart());
            nodes.add(edge.getEnd());
        }

        System.out.println("nodes: " + nodes.size() + ", edges: " + msf.size() + ", total distance :"
                + String.format("%.3f", distance / 1000) + " km");
    }
}