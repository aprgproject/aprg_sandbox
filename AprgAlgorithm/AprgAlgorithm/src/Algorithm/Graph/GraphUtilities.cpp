#include "GraphUtilities.hpp"

namespace alba
{

namespace algorithm
{

unsigned int getDegreeAt(
        BaseUndirectedGraph const& graph,
        Vertex const vertex)
{
    return graph.getAdjacentVerticesAt(vertex).size();
}

unsigned int getMaxDegree(
        BaseUndirectedGraph const& graph)
{
    unsigned int result(0);
    unsigned int numberOfVertices(graph.getNumberOfVertices());
    for(Vertex vertex=0; vertex<numberOfVertices; vertex++)
    {
        result = std::max(result, getDegreeAt(graph, vertex));
    }
    return result;
}

double getAverageDegree(
        BaseUndirectedGraph const& graph)
{
    return 2 * graph.getNumberOfEdges() / graph.getNumberOfVertices();
}

unsigned int getNumberOfSelfLoops(
        BaseUndirectedGraph const& graph)
{
    unsigned int count(0);
    unsigned int numberOfVertices(graph.getNumberOfVertices());
    for(Vertex vertex=0; vertex<numberOfVertices; vertex++)
    {
        Vertices const& adjacentVertices(graph.getAdjacentVerticesAt(vertex));
        for(Vertex const adjacentVertex : adjacentVertices)
        {
            if(vertex == adjacentVertex)
            {
                count++;
            }
        }
    }
    return count/2; //Loops are counted twice so divide by 2
}

}

}
