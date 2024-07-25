package base;

/**
 * An interface representing an abstract queue structure.
 * 
 * @param <E> The type of elements in the queue
 */
public interface AbstractQueue<E> {

    /**
     * Checks if the queue is empty.
     * 
     * @return True if the queue is empy, otherwise false
     */
    public boolean empty(); // controlla se la coda è vuota -- O(1)

    /**
     * Adds an element to the queue.
     * 
     * @param e The element to add
     * @return True if the element is successfully added, otherwise false
     */
    public boolean push(E e); // aggiunge un elemento alla coda -- O(logN)

    /**
     * Checks if the queue contains a specific element.
     * 
     * @param e The element to check
     * @return True if the priority queue contains the element, otherwise false
     */
    public boolean contains(E e); // controlla se un elemento è in coda -- O(1)

    /**
     * Gets the element at the top of the queue
     * 
     * @return The element at the top of the queue
     */
    public E top(); // accede all'elemento in cima alla coda -- O(1)

    /**
     * Removes the element at the top of the queue
     */
    public void pop(); // rimuove l'elemento in cima alla coda -- O(logN)

    /**
     * Removes a specific element from the queue
     * 
     * @param e The element to remove
     * @return True if the element is successfully removed, otherwise false
     */
    public boolean remove(E e); // rimuove un elemento se presente in coda -- O(logN)
}
