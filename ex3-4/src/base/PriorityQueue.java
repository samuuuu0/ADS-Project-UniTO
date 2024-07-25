package base;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.HashMap;
import java.util.Map;

/**
 * Implementation of a priority queue using a binary (minimum) heap.
 * 
 * @param <E> The type of elements in the pririty queue
 */
public class PriorityQueue<E> implements AbstractQueue<E> {

    // ArrayList to represent the binary heap
    private ArrayList<E> heap;
    // Map to keep track of the index of each element in the heap
    private Map<E, Integer> map;
    // Comparator to define the ordering of elements
    private Comparator<? super E> comparator;

    /**
     * Costructor to create a new priority queue.
     * 
     * @param comparator To define the ordering of elements
     */
    public PriorityQueue(Comparator<? super E> comparator) {
        this.heap = new ArrayList<>();
        this.map = new HashMap<>();
        this.comparator = comparator;
    }

    /**
     * Checks if the priority queue is empty,
     * 
     * @return True if the priority queue is empty, otherwise false
     */
    @Override
    public boolean empty() {
        return heap.isEmpty();
    }

    /**
     * Adds an element to the priority queue.
     * 
     * @param e The element to add
     * @return True if the element is successfully added, otherwise false
     */
    @Override
    public boolean push(E e) {
        if (e == null)
            throw new IllegalArgumentException("Cannot push null element into the priority queue.");

        heap.add(e);
        map.put(e, heap.size() - 1);
        heapifyUp(heap.size() - 1);

        return true;
    }

    /**
     * Checks if the priority queue contains a specific element.
     * 
     * @param e The element to check
     * @return True if the priority queue contains the element, otherwise false
     */
    @Override
    public boolean contains(E e) {
        if (e == null)
            throw new IllegalArgumentException("Null elements are not supported in the priority queue.");

        return map.containsKey(e);
    }

    /**
     * Gets the highest priority element in the priority queue.
     * 
     * @return The highest priority element
     */
    @Override
    public E top() {
        if (empty())
            throw new IllegalStateException("Priority queue is empty.");

        return heap.get(0);
    }

    /**
     * Removes the highest priority element from the priority queue.
     */
    @Override
    public void pop() {
        if (empty())
            throw new IllegalStateException("Priority queue is empty, cannot pop.");

        E removed = heap.get(0);
        int lastIndex = heap.size() - 1;
        E last = heap.remove(lastIndex);

        map.remove(removed);

        if (lastIndex > 0) {
            heap.set(0, last);
            map.put(last, 0);

            heapifyDown(0);
        }
    }

    /**
     * Removes a specific element from the priority queue.
     * 
     * @param e The element to remove
     * @return True if the element is successfully removed, otherwise false
     */
    @Override
    public boolean remove(E e) {
        if (e == null)
            throw new IllegalArgumentException("Null elements are not supported in the priority queue.");

        if (!contains(e))
            throw new IllegalArgumentException("Element not found in the priority queue.");

        int index = map.get(e);
        int lastIndex = heap.size() - 1;
        E last = heap.remove(lastIndex);

        map.remove(e);

        if (index != lastIndex) {
            heap.set(index, last);
            map.put(last, index);

            if (index > 0 && comparator.compare(last, heap.get(parent(index))) < 0)
                heapifyUp(index);
            else
                heapifyDown(index);
        }

        return true;
    }

    /**
     * Calculates the index of the parent node for a given index.
     * 
     * @param index The index of the node
     * @return The index of the parent node
     */
    private int parent(int index) {
        return (index - 1) / 2;
    }

    /**
     * Calculates the index of the left child node for a given index.
     * 
     * @param index The index of the node
     * @return The index of the left child node
     */
    private int left(int index) {
        return 2 * index + 1;
    }

    /**
     * Calculates the index of the right child node for a given index.
     * 
     * @param index The index of the node
     * @return The index of the right child node
     */
    private int right(int index) {
        return 2 * index + 2;
    }

    /**
     * Swaps two elements in the heap and updates their indices in the map
     * 
     * @param x The index of the first element
     * @param y The index of the second element
     */
    private void swap(int x, int y) {
        E temp = heap.get(x);
        heap.set(x, heap.get(y));
        heap.set(y, temp);

        map.put(heap.get(x), x);
        map.put(heap.get(y), y);
    }

    /**
     * Gets the number of elements in the priority queue
     * 
     * @return The number of elements
     */
    public int size() {
        return heap.size();
    }

    /**
     * Performs the heapify operation upwards.
     * 
     * @param index The index to start the operation from
     */
    private void heapifyUp(int index) {
        while (index > 0 && comparator.compare(heap.get(index), heap.get(parent(index))) < 0) {
            swap(index, parent(index));
            index = parent(index);
        }
    }

    /**
     * Performs the heapify operation downwards.
     * 
     * @param index The index to start the operation from
     */
    private void heapifyDown(int index) {
        int left = left(index);
        int right = right(index);
        int minElement = index;

        if (left < heap.size() && comparator.compare(heap.get(left), heap.get(minElement)) < 0) {
            minElement = left;
        }
        if (right < heap.size() && comparator.compare(heap.get(right), heap.get(minElement)) < 0) {
            minElement = right;
        }

        if (minElement != index) {
            swap(index, minElement);
            heapifyDown(minElement);
        }
    }
}