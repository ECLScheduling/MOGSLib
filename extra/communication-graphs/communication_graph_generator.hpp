#pragma once

#include <algorithm>
#include <cstdint>

/* Classes involved in the generation of communication graphs */
class GraphGenerator;
class RingGenerator;

/* This will be migrated to another file soon*/
// Communication between two tasks (vertices)
struct Edge {
    size_t   src;   //source task
    size_t   dest;  //destination task
    uint64_t msgs;
    uint64_t bytes;
};

// All edges related to a task (vertix)
typedef std::vector< Edge > Edges;
typedef std::vector< Edges > Graph;

/* end of migration */

/* Implemented communication graphs */
enum PossibleGraphs {
    RING,
    MESH2D
};

/* Factory class for communication graph generators
 * Currently implements only graphs with the same uniform numbers of messages and data communicated
 */
class GraphGenerator {
    protected:
        uint64_t msgs;  //Number of messages between two tasks
        uint64_t bytes; //Number of bytes communicated between two tasks

    public:
        /* Factory method */
        static GraphGenerator* makeGenerator (
                PossibleGraphs graph,
                uint64_t msgs, uint64_t bytes,
                size_t dim1, size_t dim2
                );

        /* Communication graph generator */
        virtual Graph generateGraph ( ) = 0;
};

class RingGenerator : public GraphGenerator {
    private:
        size_t tasks; // number of tasks in the graph

    public:
        RingGenerator (size_t tasks_, uint64_t msgs_, uint64_t bytes_) {
            tasks = tasks_;
            msgs = msgs_;
            bytes = bytes_;
        }
        Graph generateGraph ( );
};

class Mesh2DGenerator : public GraphGenerator {
    private:
        size_t dim1;
        size_t dim2;

    public:
        Mesh2DGenerator (size_t dim1_, size_t dim2_, uint64_t msgs_, uint64_t bytes_) {
            dim1 = dim1_;
            dim2 = dim2_;
            msgs = msgs_;
            bytes = bytes_;
        }
        Graph generateGraph ( );
        size_t positionInMesh (size_t x, size_t y);
};

/* Methods */
GraphGenerator* GraphGenerator::makeGenerator (
                PossibleGraphs graph,
                uint64_t msgs, uint64_t bytes,
                size_t dim1, size_t dim2 = 0
        ) {
    GraphGenerator* generator = NULL;
    if (graph == RING)
        generator = new RingGenerator(dim1, msgs, bytes);
    else if (graph == MESH2D)
        generator = new Mesh2DGenerator(dim1, dim2, msgs, bytes);

    return generator;
}

/* Generates a graph in the shape of a ring */
Graph RingGenerator::generateGraph ( ) {
    Graph ring = Graph(tasks);

    //for each task, we add an edge to the neighbor to the right
    //and another to the neighbor to the left
    for (size_t i = 0; i < tasks; ++i) {
        Edge left = {i, (tasks+i-1)%tasks, msgs, bytes}; //neighbor to the left
        Edge right = {i, (tasks+i+1)%tasks, msgs, bytes};//neighbor to the right
        ring[i].push_back(left);
        ring[i].push_back(right);
    }
    return ring;
}

/* Generates a graph in the shape of a 2D mesh */
Graph Mesh2DGenerator::generateGraph ( ) {
    Graph mesh = Graph(dim1*dim2);

    //for each task, we add edges to the four neighbors (right, up, left, down)
    //tasks are organized with contiguous lines (in dim1)
    for (size_t x = 0; x < dim1; ++x){
        for (size_t y = 0; y < dim2; ++y){
            /* Example for dim1 = 2 & dim2 = 4
             * 1,0 (4) 1,1 (5) 1,2 (6) 1,3 (7)
             * 0,0 (0) 0,1 (1) 0,2 (2) 0,3 (3)*/
            size_t pos = positionInMesh(x,y); //position in the communication graph
            /* Adds neighbor to the right (if it exists) */
            if (y != dim2-1) {
                Edge right = {pos, positionInMesh(x,y+1), msgs, bytes};
                mesh[pos].push_back(right);
            }
            /* Adds neighbor above (if it exists) */
            if (x != dim1-1) {
                Edge up = {pos, positionInMesh(x+1,y), msgs, bytes};
                mesh[pos].push_back(up);
            }
            /* Adds neighbor to the left (if it exists) */
            if (y != 0) {
                Edge left = {pos, positionInMesh(x,y-1), msgs, bytes};
                mesh[pos].push_back(left);
            }
            /* Adds neighbor below (if it exists) */
            if (x != 0) {
                Edge down = {pos, positionInMesh(x-1,y), msgs, bytes};
                mesh[pos].push_back(down);
            }
        }
    }

    return mesh;
}

size_t Mesh2DGenerator::positionInMesh (size_t x, size_t y) {
    return x*dim2 + y;
}
