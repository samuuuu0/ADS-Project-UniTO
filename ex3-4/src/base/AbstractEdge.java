package base;

/**
 * An interface representing an abstract edge in a graph.
 * 
 * @param <V> The type of nodes connected by the edge
 * @param <L> The type of labels associated with the edge
 */
public interface AbstractEdge<V, L> {

    /**
     * Gets the starting node of the edge.
     * 
     * @return The starting node of the edge
     */
    public V getStart(); // il nodo di partenza dell'arco

    /**
     * Gets the ending node of the edge.
     * 
     * @return The ending node of the edge
     */
    public V getEnd(); // il nodo di arrivo dell'arco

    /**
     * Gets the label associated with the edge.
     * 
     * @return The label associated with the edge
     */
    public L getLabel(); // l'etichetta dell'arco
};
