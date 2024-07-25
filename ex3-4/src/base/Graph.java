package base;

import java.util.*;

/**
 * Implementation of a generic graph.
 * 
 * @param <V> The type of nodes in the graph
 * @param <L> The type of edge labels in the graph
 */
public class Graph<V, L> implements AbstractGraph<V, L> {

    private final boolean directed;
    private final boolean labelled;
    // Adjacency Matrix to represent the graph
    private final Map<V, Map<V, Edge<V, L>>> adj;
    // Set to store the edges of the graph
    private final Set<Edge<V, L>> edges;

    /**
     * Constructor to create a new graph.
     * 
     * @param directed Indicates whether the graph is directed (true) or undirected
     *                 (false)
     * @param labelled Indicates whether the graph is labelled (true) or unlabelled
     *                 (false)
     */
    public Graph(boolean directed, boolean labelled) {
        this.directed = directed;
        this.labelled = labelled;
        this.adj = new HashMap<>();
        this.edges = new HashSet<>();
    }

    /**
     * Checks if the graph is directed.
     * 
     * @return True if the graph is directed, otherwise false
     */
    @Override
    public boolean isDirected() {
        return directed;
    }

    /**
     * Checks if the graph is labelled.
     * 
     * @return True if the graph is labelled, otherwise false.
     */
    @Override
    public boolean isLabelled() {
        return labelled;
    }

    /**
     * Add a node to the graph.
     * 
     * @param a The node to add
     * @return True if the node is successfully added, otherwise false
     */
    @Override
    public boolean addNode(V a) {
        if (adj.containsKey(a))
            return false;

        adj.put(a, new HashMap<>());
        return true;
    }

    /**
     * Adds an edge to the graph.
     * 
     * @param a The starting node of the edge
     * @param b The ending node of the edge
     * @param l The label of the edge
     * @return True if the edge is successfully added, otherwise false
     */
    @Override
    public boolean addEdge(V a, V b, L l) {
        if (!adj.containsKey(a) || !adj.containsKey(b))
            return false;

        // check that the edge is not already in the matrix
        if (adj.get(a).containsKey(b))
            return false;

        if (labelled && l == null)
            return false;

        // create the edge
        Edge<V, L> edge = new Edge<V, L>(a, b, labelled ? l : null);
        adj.get(a).put(b, edge);
        edges.add(edge);
        // in a not directed graph A -> B and B -> A are the same
        // but in a directed graph is not
        // the corresponding edge will be added only if the graph is not directed
        if (!directed) {
            Edge<V, L> reversed = new Edge<>(b, a, labelled ? l : null);
            adj.get(b).put(a, reversed);
            edges.add(reversed);
        }

        return true;
    }

    /**
     * Checks if the graph contains a specific node.
     * 
     * @param a The node to check
     * @return True if the graph contains the node, otherwise false
     */
    @Override
    public boolean containsNode(V a) {
        return adj.containsKey(a);
    }

    /**
     * Checks if the graph contains a specific edge between two nodes.
     * 
     * @param a The starting node of the edge
     * @param b The ending node of the edge
     * @return True if the graph contains the edge, otherwise false
     */
    @Override
    public boolean containsEdge(V a, V b) {
        return adj.containsKey(a) && adj.get(a).containsKey(b);
    }

    /**
     * Removes a node from the graph.
     * 
     * @param a The node to remove
     * @return True if the node is successfully removed, otherwise false
     */
    @Override
    public boolean removeNode(V a) {
        if (!adj.containsKey(a))
            return false;

        // Remove edges pointing to the node
        for (V node : adj.keySet()) {
            Edge<V, L> removed = adj.get(node).remove(a);

            if (removed != null)
                edges.remove(removed);

        }

        // remove edges startig from the node
        for (Edge<V, L> edge : adj.get(a).values())
            edges.remove(edge);

        // remove the node itself
        adj.remove(a);

        return true;
    }

    /**
     * Removes an edge from the graph.
     * 
     * @param a The starting node of the edge
     * @param b The ending node of the edge
     * @return True if the edge is successfully removed, otherwise false
     */
    @Override
    public boolean removeEdge(V a, V b) {
        if (!adj.containsKey(a) || !adj.get(a).containsKey(b))
            return false;

        Edge<V, L> removed = adj.get(a).remove(b);
        edges.remove(removed);

        // check if the graph is not directed
        if (!directed) {
            // then remove the corresponding
            Edge<V, L> reversed = adj.get(b).remove(a);
            edges.remove(reversed);
        }

        return true;
    }

    /**
     * Gets the number of nodes in the graph.
     * 
     * @return The number of nodes
     */
    @Override
    public int numNodes() {
        return adj.size();
    }

    /**
     * Gets the number of edges in the graph.
     * 
     * @return The number of edges
     */
    @Override
    public int numEdges() {
        // initialize the counter
        // int size = 0;
        // get the neighbor list of each node
        // for (Map<V, Edge<V, L>> neighborMap : adj.values())
        // size += neighborMap.size();

        // check if the graph is directed or not
        // then divide by 2 if it is 'case the values ​​will be duplicated
        // return directed ? size : size / 2;

        return directed ? edges.size() : edges.size() / 2;
    }

    /**
     * Gets a collection of all nodes in the graph.
     * 
     * @return A collection of nodes
     */
    @Override
    public Collection<V> getNodes() {
        return Collections.unmodifiableSet(adj.keySet());
    }

    /**
     * Gets a collection of all edges in the graph.
     * 
     * @return A collection of edges
     */
    @Override
    public Collection<? extends AbstractEdge<V, L>> getEdges() {
        // Set<Edge<V, L>> edges = new HashSet<>();
        // get the neighbor list of each node
        // for (Map<V, Edge<V, L>> neighborMap : adj.values())
        // add all the edges to the HashSet
        // edges.addAll(neighborMap.values());

        // return Collections.unmodifiableSet(edges);
        return edges;
    }

    /**
     * Gets a collection of neighbor nodes of a specific node in the graph
     * 
     * @param a The node to get neighbors for
     * @return A collection of neighbor nodes
     */
    @Override
    public Collection<V> getNeighbours(V a) {
        if (!adj.containsKey(a))
            return Collections.emptySet();

        return Collections.unmodifiableSet(adj.get(a).keySet());
    }

    /**
     * Gets the label of the edge between two specified nodes.
     * 
     * @param a The starting node of the edge
     * @param b The ending node of the edge
     * @return The label of the edge if it exists, otherwise null
     */
    @Override
    public L getLabel(V a, V b) {
        if (!adj.containsKey(a) || !adj.get(a).containsKey(b))
            return null;

        return adj.get(a).get(b).getLabel();
    }

    /**
     * Inner class representing an edge in the graph.
     * 
     * @param <V> The type of nodes in the graph
     * @param <L> The type of edge labels in the graph
     */
    public static class Edge<V, L> implements AbstractEdge<V, L> {

        private final V start;
        private final V end;
        private final L label;

        /**
         * Constructor to create a new edge.
         * 
         * @param start The starting node of the edge
         * @param end   The ending node of the edge
         * @param label The label of the edge
         */
        public Edge(V start, V end, L label) {
            this.start = start;
            this.end = end;
            this.label = label;
        }

        /**
         * Gets the starting node of the edge.
         * 
         * @return The starting node
         */
        @Override
        public V getStart() {
            return start;
        }

        /**
         * Gets the ending node of the edge.
         * 
         * @return The ending node
         */
        @Override
        public V getEnd() {
            return end;
        }

        /**
         * Gets the label of the edge.
         * 
         * @return The label of the edge
         */
        @Override
        public L getLabel() {
            return label;
        }

        /**
         * Returns a hash code value for the edge.
         * 
         * @return The hash code value for this edge
         */
        @Override
        public int hashCode() {
            return Objects.hash(start, end, label);
        }

        /**
         * Compares this edge to the specified object. 
         *
         * @param obj The object to compare this edge against
         * @return True if the given object represents an Edge equivalent to this edge, otherwise false
         */
        @Override
        public boolean equals(Object obj) {
            if (this == obj)
                return true;

            if (obj == null || getClass() != obj.getClass())
                return false;

            Edge<?, ?> edge = (Edge<?, ?>) obj;
            return Objects.equals(start, edge.start) &&
                    Objects.equals(end, edge.end) &&
                    Objects.equals(label, edge.label);
        }
    }
}