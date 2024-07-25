package test;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertNull;
import static org.junit.Assert.assertTrue;

import java.util.HashSet;
import java.util.Set;

import org.junit.Before;
import org.junit.Test;

import base.Graph;

public class GraphTest {

    private Graph<Integer, String> graph;

    @Before
    public void setUp() {
        graph = new Graph<>(false, true);
    }

    @Test
    public void testAddNode() {
        assertTrue(graph.addNode(1));
        assertTrue(graph.addNode(2));
        // adding an existing node should return false
        assertFalse(graph.addNode(1));
    }

    @Test
    public void testAddEdge() {
        graph.addNode(1);
        graph.addNode(2);
        assertTrue(graph.addEdge(1, 2, "Edge1"));

        // adding an existing edge should return false
        assertFalse(graph.addEdge(1, 2, "Edge4"));
        
        // adding an edge with null label should return false
        assertFalse(graph.addEdge(1, 3, null));
    }

    @Test
    public void testContainsNode() {
        graph.addNode(1);
        assertTrue(graph.containsNode(1));

        // node not added yet
        assertFalse(graph.containsNode(2));
    }

    @Test
    public void testContainsEdge() {
        graph.addNode(1);
        graph.addNode(2);
        graph.addEdge(1, 2, "Edge1");
        assertTrue(graph.containsEdge(1, 2));

        // for undirected graph, edges are added both ways
        assertTrue(graph.containsEdge(2, 1));

        // edge not added yet
        assertFalse(graph.containsEdge(1, 3));
    }

    @Test
    public void testRemoveNode() {
        graph.addNode(1);
        assertTrue(graph.removeNode(1));

        // removing non-existent node should return false
        assertFalse(graph.removeNode(1));
    }

    @Test
    public void testRemoveEdge() {
        graph.addNode(1);
        graph.addNode(2);
        graph.addEdge(1, 2, "Edge1");
        assertTrue(graph.removeEdge(1, 2));

        // removing non-existent edge should return false
        assertFalse(graph.removeEdge(1, 2));
    }

    @Test
    public void testNumNodes() {
        assertEquals(0, graph.numNodes());
        graph.addNode(1);
        assertEquals(1, graph.numNodes());
    }

    @Test
    public void testNumEdges() {
        assertEquals(0, graph.numEdges());
        graph.addNode(1);
        graph.addNode(2);
        graph.addEdge(1, 2, "Edge1");
        assertEquals(1, graph.numEdges());
    }

    @Test
    public void testGetNodes() {
        graph.addNode(1);
        graph.addNode(2);
        Set<Integer> expected = new HashSet<>();
        expected.add(1);
        expected.add(2);
        assertEquals(expected, new HashSet<>(graph.getNodes()));
    }

    @Test
    public void testGetEdges() {
        graph.addNode(1);
        graph.addNode(2);
        graph.addEdge(1, 2, "Edge1");
        Set<Graph.Edge<Integer, String>> expected = new HashSet<>();
        expected.add(new Graph.Edge<Integer, String>(1, 2, "Edge1"));
        expected.add(new Graph.Edge<Integer, String>(2, 1, "Edge1"));
        assertEquals(expected, new HashSet<>(graph.getEdges()));
    }

    @Test
    public void testGetNeighbours() {
        graph.addNode(1);
        graph.addNode(2);
        graph.addNode(3);
        graph.addEdge(1, 2, "Edge1");
        graph.addEdge(1, 3, "Edge1");
        Set<Integer> expected = new HashSet<>();
        expected.add(2);
        expected.add(3);
        assertEquals(expected, new HashSet<>(graph.getNeighbours(1)));
    }

    @Test
    public void testGetLabel() {
        graph.addNode(1);
        graph.addNode(2);
        graph.addEdge(1, 2, "Edge1");
        assertEquals("Edge1", graph.getLabel(1, 2));
        assertEquals("Edge1", graph.getLabel(2, 1));
        assertNull(graph.getLabel(3, 1));
    }
}
