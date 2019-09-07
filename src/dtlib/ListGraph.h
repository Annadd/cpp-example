#ifndef LISTGRAPH_H
#define LISTGRAPH_H

#include "Graph.h"
#include "LinkList.h"
#include "Edge.h"

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
                value = *(vertex->data);
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

    void removeVertex()
    {
        if(mList.length() > 0){
            int index = mList.length() - 1;
            Vertex* v = mList.get(index);

            if(mList.remove(index)){
                for(int i = (mList.move(0), 0); !mList.end(); i++, mList.next()){
                    int pos = mList.current()->edge.find(Edge<E>(i, index));

                    if(pos >= 0){
                        mList.current()->edge.remove(pos);
                    }
                }

                delete v->data;
                delete v;
            }
        } else {
            THROW_EXCEPTION(InvalidOperationException, "No vertex in crrent graph ...");
        }
    }

    SharedPointer<Array<int> > getAdjacent(int i) override
    {
        Array<int>* ret = nullptr;

        if((0 <= i) && (i < vCount())){
            Vertex* vertex = mList.get(i);

            ret = new DynamicArray<int>(vertex->edge.length());

            if(ret != nullptr){
                for (int k = (vertex->edge.move(0), 0); !vertex->edge.end(); k++, vertex->edge.next()) {
                    ret->set(k, vertex->edge.current().e);
                }
            }
            else {
                THROW_EXCEPTION(NoEnoughMemeoryException, "No memory to create ret object ...");
            }
        } else {
            THROW_EXCEPTION(InvalidParameterException, "Index i is invalid ...");
        }

        return ret;
    }

    bool isAdjacent(int i, int j) override
    {
        return (0 <= i) && (i < vCount()) && (0 <= j) && (j < vCount()) && (mList.get(i)->edge.find(Edge<E>(i, j)) >= 0);
    }

    E getEdge(int i, int j) override
    {
        E ret;

        if(!getEdge(i, j, ret)){
            THROW_EXCEPTION(InvalidParameterException, "Edge <i, j> is invalid ...");
        }

        return ret;
    }

    bool getEdge(int i, int j, E &value) override
    {
        bool ret = ((0 <= i) && (i < vCount())) && ((0 <= j) && (j < vCount()));

        if(ret){
            Vertex* vertex = mList.get(i);

            int pos = vertex->edge.find(Edge<E>(i, j));

            if(pos >= 0){
                value = vertex->edge.get(pos).data;
            } else {
                THROW_EXCEPTION(InvalidOperationException, "No value assigned to this edge ...");
            }
        }

        return ret;
    }

    bool setEdge(int i, int j, const E &value) override
    {
        bool ret = ((0 <= i) && (i < vCount())) && ((0 <= j) && (j < vCount()));

        if(ret){
            Vertex* vertex = mList.get(i);

            int pos = vertex->edge.find(Edge<E>(i, j));

            if(pos >= 0){
                ret = vertex->edge.set(pos, value);
            } else {
                ret = vertex->edge.insert(0, Edge<E>(i, j, value));
            }
        }

        return ret;
    }

    bool removeEdge(int i, int j) override
    {
        bool ret = ((0 <= i) && (i < vCount())) && ((0 <= j) && (j < vCount()));

        if(ret){
            Vertex* vertex = mList.get(i);

            int pos = vertex->edge.find(Edge<E>(i, j));

            if(pos >= 0){
                ret = vertex->edge.remove(pos);
            }
        }

        return ret;
    }

    int vCount() override
    {
        return mList.length();
    }

    int eCount() override
    {
        int ret = 0;

        for (mList.move(0); !mList.end(); mList.next()) {
            ret += mList.current()->edge.length();
        }

        return ret;
    }

    int ID(int i) override
    {
        int ret = 0;

        if((0 <= i) && (i < vCount())){
            for (mList.move(0); !mList.end(); mList.next()) {
                LinkList<Edge<E>>& edge = mList.current()->edge;

                for (edge.move(0); !edge.end(); edge.next()) {
                    if(edge.current().e == i){
                        ret++;
                        break;
                    }
                }
            }
        } else {
            THROW_EXCEPTION(InvalidParameterException, "Index i is invalid ...");
        }

        return ret;
    }

    int OD(int i) override
    {
        int ret = 0;

        if((0 <= i) && (i < vCount())){
            ret = mList.get(i)->edge.length();
        } else {
            THROW_EXCEPTION(InvalidParameterException, "Index i is invalid ...");
        }

        return ret;
    }

    ~ListGraph()
    {
        while(mList.length() > 0){
            Vertex* toDel = mList.get(0);

            mList.remove(0);

            delete toDel->data;
            delete toDel;
        }
    }
};

}

#endif//LISTGRAPH_H
