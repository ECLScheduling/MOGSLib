#include <iostream>
#include "communication_graph_generator.hpp"

int main () {
    GraphGenerator* generator;
    generator = GraphGenerator::makeGenerator (RING, 2, 3, 5);
    Graph graph = generator->generateGraph();

    std::cout << "Communication Graph: Ring" << std::endl;
    for (Graph::iterator vertex = graph.begin(); vertex != graph.end(); ++vertex) {
        for (Edges::iterator edge = vertex->begin(); edge != vertex->end(); ++edge) {
            std::cout << "Edge from vertex " << edge->src << " to " << edge->dest << " with " << edge->msgs << " messages and " << edge->bytes << " bytes" << std::endl;
        }
    }

    GraphGenerator* mesh_gen = GraphGenerator::makeGenerator (MESH2D, 1, 100, 2, 4);
    Graph mesh = mesh_gen->generateGraph();
    std::cout << "Communication Graph: Mesh" << std::endl;
    for (Graph::iterator vertex = mesh.begin(); vertex != mesh.end(); ++vertex) {
        for (Edges::iterator edge = vertex->begin(); edge != vertex->end(); ++edge) {
            std::cout << "Edge from vertex " << edge->src << " to " << edge->dest << " with " << edge->msgs << " messages and " << edge->bytes << " bytes" << std::endl;
        }
    }

}
