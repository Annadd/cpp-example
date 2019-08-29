#ifndef LISTGRAPH_H
#define LISTGRAPH_H

#include "Graph.h"
#include "LinkList.h"

namespace DTLib
{

template<typename V, typename E>
class ListGraph : public Graph<V, E>
{
protected:
    struct Vertex : public Object
    {
        V* data;
        LinkList<Edge<E>> edge;

        Vertex(): data(nullptr) {}
    };

    LinkList<Vertex*> mList;

    // Graph interface
public:
    ListGraph(unsigned int n = 0)
    {
        for (unsigned int i = 0; i < n; i++) {
            addVertex();
        }
    }

    int addVertex()
    {
        int ret = -1;

        Vertex* v = new Vertex();

        if(v != nullptr){
            mList.insert(v);

            ret = mList.length() - 1;
        } else {
            THROW_EXCEPTION(NoEnoughMemeoryException, "No memory to create new vertex object ...");
        }

        return ret;
    }

    int addVertex(const V& value)
    {
        int ret = addVertex();

        if(ret >= 0){
            setVertex(ret, value);
        }

        return ret;
    }

    V getVertex(int i) override
    {
        V ret;

        if(!getVertex(i, ret)){
            THROW_EXCEPTION(InvalidParameterException, "Index i is invalid ...");
        }

        return ret;
    }

    bool getVertex(int i, V &value) override
    {
        bool ret = (0 <= i) && (i < vCount());

        if(ret){
            Vertex* vertex = mList.get(i);

            if(vertex->data != nullptr){
                value = vertex->data;
            } else {
                THROW_EXCEPTION(InvalidOperationException, "No value assigned to this vertex ...");
            }
        }

        return ret;
    }

    bool setVertex(int i, const V &value) override
    {
        bool ret = (0 <= i) && (i < vCount());

        if(ret){
            Vertex* vertex = mList.get(i);
            V* data = vertex->data;

            if(data == nullptr){
                data = new V();
            }

            if(data != nullptr){
                *data = value;

                vertex->data = data;
            } else {
                THROW_EXCEPTION(NoEnoughMemeoryException, "No memory to create new vertex value ...");
            }
        }

        return ret;
    }

    SharedPointer<Array<int> > getAdjacent(int i) override;

    E getEdge(int i, int j) override;

    bool getEdge(int i, int j, E &value) override;

    bool setEdge(int i, int j, const E &value) override;

    bool removeEdge(int i, int j) override;

    int vCount() override;

    int eCount() override;

    int OD(int i) override;

    int ID(int i) override;

    ~ListGraph()
    {

    }
};

}

#endif//LISTGRAPH_H
