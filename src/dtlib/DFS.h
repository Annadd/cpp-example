#ifndef DFS_H
#define DFS_H

#include "Graph.h"
#include "SharedPointer.h"
#include "DynamicArray.h"

namespace DTLib
{

template<typename V, typename E>
void DFS(Graph<V, E>& g, int v, Array<bool>& visited)
{
    if((0 <= v) && (v < g.vCount())){
        std::cout << v << std::endl;

        visited[v] = true;

        SharedPointer<Array<int>> aj = g.getAdjacent(v);

        for (int i = 0; i < aj->length(); i++) {
            if(!visited[(*aj)[i]]){
                DFS(g, (*aj)[i], visited);
            }
        }
    } else {
        THROW_EXCEPTION(InvalidParameterException, "Index v is invalid ...");
    }
}


template<typename V, typename E>
void DFS(Graph<V, E>& g, int v)
{
    DynamicArray<bool> visited(g.vCount());

    for (int j = 0; j < visited.length(); j++) {
        visited[j] = false;
    }

    DFS(g, v, visited);
}

}

#endif
