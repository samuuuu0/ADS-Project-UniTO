package test;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;

import java.util.Comparator;

import org.junit.Test;

import base.PriorityQueue;

public class PriorityQueueTest {

    public class IntegerComparator implements Comparator<Integer> {

        @Override
        public int compare(Integer x, Integer y) {
            return x.compareTo(y);
        }
    }

    private PriorityQueue<Integer> queue = new PriorityQueue<>(new IntegerComparator());

    @Test
    public void testEmptyQueue() {
        assertTrue("Queue should be empty.", queue.empty());
        queue.push(1);
        assertFalse("Queue should not be empty.", queue.empty());
    }

    @Test
    public void testPushQueue() {
        queue.push(1);
        assertEquals("Queue size should be 1.", 1, queue.size());
    }

    @Test
    public void testContainsQueue() {
        queue.push(1);
        queue.push(1);
        queue.pop();
        assertTrue("Queue should contain element 1.", queue.contains(1));
        queue.pop();
        assertTrue("Queue should be empty.", queue.empty());
    }

    @Test
    public void testTopQueue() {
        queue.push(10);
        assertEquals("Top element should be 10.", Integer.valueOf(10), queue.top());
        queue.push(5);
        assertEquals("Top element should be 5.", Integer.valueOf(5), queue.top());
        queue.push(20);
        assertEquals("Top element should be 5.", Integer.valueOf(5), queue.top());
    }

    @Test
    public void testPopQueue() {
        queue.push(10);
        queue.push(5);
        queue.push(20);

        assertEquals("Top element should be 5.", Integer.valueOf(5), queue.top());
        queue.pop();
        assertEquals("Top element should be 10.", Integer.valueOf(10), queue.top());
        queue.pop();
        assertEquals("Top element should be 20.", Integer.valueOf(20), queue.top());
        queue.pop();
        assertTrue("Queue should be empty after popping element.", queue.empty());
    }

    @Test
    public void testRemoveQueue() {
        queue.push(1);
        queue.push(2);
        queue.push(3);

        queue.remove(1);
        assertEquals("Top element should be 2 after removal.", Integer.valueOf(2), queue.top());
        assertFalse("Queue should not contain element 1 after removal.", queue.contains(1));
    }

    @Test
    public void testMultipleInsertsAndExtracts() {
        queue.push(3);
        queue.push(1);
        queue.push(4);
        queue.push(1);
        queue.push(5);
        queue.push(9);
        queue.push(2);
        queue.push(6);
        queue.push(5);
        queue.push(3);
        queue.push(5);

        assertEquals(Integer.valueOf(1), queue.top());
        queue.pop();
        assertEquals(Integer.valueOf(1), queue.top());
        queue.pop();
        assertEquals(Integer.valueOf(2), queue.top());
        queue.pop();
        assertEquals(Integer.valueOf(3), queue.top());
        queue.pop();
        assertEquals(Integer.valueOf(3), queue.top());
        queue.pop();
        assertEquals(Integer.valueOf(4), queue.top());
        queue.pop();
        assertEquals(Integer.valueOf(5), queue.top());
        queue.pop();
        assertEquals(Integer.valueOf(5), queue.top());
        queue.pop();
        assertEquals(Integer.valueOf(5), queue.top());
        queue.pop();
        assertEquals(Integer.valueOf(6), queue.top());
        queue.pop();
        assertEquals(Integer.valueOf(9), queue.top());
        queue.pop();

        assertTrue(queue.empty());
    }
}
