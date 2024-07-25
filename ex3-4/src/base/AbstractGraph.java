package base;

import java.util.Collection;

/**
 * An interface representing an abstract graph structure.
 * 
 * @param <V> The type of nodes in the graph
 * @param <L> The type of labels associated with edges in the graph
 */
public interface AbstractGraph<V, L> {

    /**
     * Determines whether the graph is directed.
     * 
     * @return True if the graph is directed, false otherwise
     */
    public boolean isDirected(); // dice se il grafo è diretto o meno -- O(1)

    /**
     * Determines whether the graph is labelled.
     * 
     * @return True if the graph is labelled, otherwise false
     */
    public boolean isLabelled(); // dice se il grafo è etichettato o meno -- O(1)

    /**
     * Adds node to the graph.
     * 
     * @param a The node to add
     * @return True if the node is successfully added, otherwise false
     */
    public boolean addNode(V a); // aggiunge un nodo -- O(1)

    /**
     * Adds an edge between two node with an optional label.
     * 
     * @param a The starting node of the edge
     * @param b The ending node of the edge
     * @param l The label of the edge
     * @return True if the edge is successfully added, otherwise false
     */
    public boolean addEdge(V a, V b, L l); // aggiunge un arco dati estremi ed etichetta -- O(1) (*)

    /**
     * Checks if the node exists in the graph.
     * 
     * @param a The node to check
     * @return True if the node exists, otherwise false
     */
    public boolean containsNode(V a); // controlla se un nodo è nel grafo -- O(1)

    /**
     * Checks if the edge exists in the graph.
     * 
     * @param a The starting node of the edge
     * @param b The ending node of the edge
     * @return True if the edge exists, otherwise false
     */
    public boolean containsEdge(V a, V b); // controlla se un arco è nel grafo -- O(1) (*)

    /**
     * Removes a node from the graph.
     * 
     * @param a The node to remove
     * @return True if the node is successfully removed, otherwise false
     */
    public boolean removeNode(V a); // rimuove un nodo dal grafo -- O(N)

    /**
     * Removes a edges from the graph.
     * 
     * @param a The starting node of the edge
     * @param b The ending node of the edge
     * @return True if the edge is successfully removed, otherwise false
     */
    public boolean removeEdge(V a, V b); // rimuove un arco dal grafo -- O(1) (*)

    /**
     * Gets the number of nodes in the graph.
     * 
     * @return The number of nodes
     */
    public int numNodes(); // numero di nodi -- O(1)

    /**
     * Gets the number of edges in the graph.
     * 
     * @return The number of edges
     */
    public int numEdges(); // numero di archi -- O(N)

    /**
     * Gets a collection of all nodes in the graph.
     * 
     * @return A collection of all nodes
     */
    public Collection<V> getNodes(); // recupero dei nodi del grafo -- O(N)

    /**
     * Gets a collection of all edges in the graph.
     * 
     * @return A collection of all edges
     */
    public Collection<? extends AbstractEdge<V, L>> getEdges(); // recupero degli archi del grafo -- O(N)

    /**
     * Gets a collection of all neighbors of a given node.
     * 
     * @param a The node to retrieve neighbors for
     * @return A collection of all neighbors
     */
    public Collection<V> getNeighbours(V a); // recupero dei nodi adiacenti ad un dato nodo -- O(1) (*)

    /**
     * Gets the label associated with an edge between two nodes.
     * 
     * @param a The starting node of the edge
     * @param b The ending node of the edge
     * @return The label associated with the edge, or null if no such edge exists
     */
    public L getLabel(V a, V b); // recupero dell'etichetta di un arco -- O(1) (*)
};
