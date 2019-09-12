#ifndef LONGESTDESCENDSOLUTION_H
#define LONGESTDESCENDSOLUTION_H

#include "DynamicArray.h"
#include "ListGraph.h"

namespace DTLib
{

class LongestDescendSolution
{
protected:
    int searchMaxPath(Graph<int, int>& g, int v, Array<int>& count, Array<LinkList<int>*>& path, Array<bool>& mark)
    {
        int ret = 0;
        auto aj = g.getAdjacent(v);

        for(int i = 0; i < aj->length(); i++){
            int num = 0;

            if(!mark[(*aj)[i]]){
                num = searchMaxPath(g, (*aj)[i], count, path, mark);
            } else {
                num = count[(*aj)[i]];
            }

            if(ret < num){
                ret = num;
            }
        }

        for (int i = 0; i < aj->length(); i++) {
            if(ret == count[(*aj)[i]]){
                path[v]->insert((*aj)[i]);
            }
        }

        ret++;
        count[v] = ret;
        mark[v] = true;
        return ret;
    }

    SharedPointer<Graph<int, int>> createGraph(int* a, int len)
    {
        ListGraph<int, int>* ret = new ListGraph<int, int>(static_cast<unsigned int>(len));

        for (int i = 0; i < len; i++) {
            ret->setVertex(i, a[i]);
        }

        for (int i = 0; i < len; i++) {
            for (int j = i + 1; j < len; j++) {
                if(a[i] <= a[j]){
                    ret->setEdge(i, j, 1);
                }
            }
        }

        return ret;
    }

    void initArray(DynamicArray<int>& count, DynamicArray<LinkList<int>*>& path, DynamicArray<bool>& mark)
    {
        for (int i = 0; i < count.length(); i++) {
            count[i] = 0;
        }

        for (int i = 0; i < path.length(); i++) {
            path[i] = new LinkList<int>();
        }

        for (int i = 0; i < mark.length(); i++) {
            mark[i] = false;
        }
    }

    void searchMaxPath(Graph<int, int>& g, DynamicArray<int>& count, DynamicArray<LinkList<int>*>& path, DynamicArray<bool>& mark)
    {
        for (int i = 0; i < g.vCount(); i++) {
            if(!mark[i]){
                searchMaxPath(g, i, count, path, mark);
            }
        }
    }

    void printPath(Graph<int, int>& g, int v, DynamicArray<LinkList<int>*>& path, LinkList<int>& cp)
    {
        cp.insert(v);

        if(path[v]->length() > 0){
            for (path[v]->move(0); !path[v]->end(); path[v]->next()) {
                printPath(g, path[v]->current(), path, cp);
            }
        } else {
             std::cout << "Elemnt:";

             for (cp.move(0); !cp.end(); cp.next()) {
                 std::cout << g.getVertex(cp.current()) << " ";
             }

             std::cout << std::endl;
        }

        cp.remove(cp.length() - 1);
    }

    void printMaxPath(Graph<int, int>& g, DynamicArray<int>& count, DynamicArray<LinkList<int>*>& path)
    {
        int max = 0;
        LinkList<int> cp;

        for (int i = 0; i < count.length(); i++) {
            if(max < count[i]){
                max = count[i];
            }
        }

        std::cout << "Len: " << max << std::endl;

        for (int i = 0; i < count.length(); i++) {
            if(max == count[i]){
                printPath(g, i, path, cp);
            }
        }
    }

public:
    void solution(int* a, int len)
    {
        DynamicArray<int> count(len);
        DynamicArray<LinkList<int>*> path(len);
        DynamicArray<bool> mark(len);
        SharedPointer<Graph<int, int>> g;

        g = createGraph(a, len);

        initArray(count, path, mark);

        searchMaxPath(*g, count, path, mark);

        printMaxPath(*g, count, path);
    }

};

}

#endif//LONGESTDESCENDSOLUTION_H
