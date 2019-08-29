#ifndef MATRIXGRAPH_H
#define MATRIXGRAPH_H

#include "Graph.h"
#include "DynamicArray.h"

namespace DTLib
{

template<int N, typename V, typename E>
class MatrixGraph : public Graph<V, E>
{
protected:
    V* mVertexes[N];
    E* mEdges[N][N];
    int mEdgeCount;

    // Graph interface
public:
    MatrixGraph()
    {
        for (int i = 0; i < vCount(); i++) {
            mVertexes[i] = nullptr;

            for (int j = 0; j < vCount(); j++) {
                mEdges[i][j] = nullptr;
            }
        }

        mEdgeCount = 0;
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
            if(mVertexes[i] != nullptr){
                value = *(mVertexes[i]);
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
            V* data = mVertexes[i];

            if(data == nullptr){
                data = new V();
            }

            if(data != nullptr){
                *data = value;

                mVertexes[i] = data;
            }
            else {
                THROW_EXCEPTION(NoEnoughMemeoryException, "No memory to store new vertex value ...");
            }
        }

        return ret;
    }

    SharedPointer<Array<int>> getAdjacent(int i) override
    {
        DynamicArray<int>* ret = nullptr;

        if((0 <= i) && (i < vCount())){
            int n = 0;

            for (int j = 0; j < vCount(); j++) {
                if(mEdges[i][j] != nullptr){
                    n++;
                }
            }

            ret = new DynamicArray<int>(n);

            if(ret != nullptr){
                for (int j = 0, k = 0; j < vCount(); j++) {
                    if(mEdges[i][j] != nullptr){
                        ret->set(k++, j);
                    }
                }
            } else {
                THROW_EXCEPTION(NoEnoughMemeoryException, "No memory to create ret object ...");
            }

        } else {
            THROW_EXCEPTION(InvalidParameterException, "Index i is invalid ...");
        }

        return ret;
    }

    E getEdge(int i, int j) override
    {
        E ret;

        if(!getEdge(i, j, ret)){
            THROW_EXCEPTION(InvalidParameterException, "Index <i, j> is invalid ...");
        }

        return ret;
    }

    bool getEdge(int i, int j, E &value) override
    {
        bool ret = ((0 <= i) && (i < vCount())) && ((0 <= j) && (j < vCount()));

        if(ret){
            if(mEdges[i][j] != nullptr){
                value = *(mEdges[i][j]);
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
            E* ne = mEdges[i][j];

            if(ne == nullptr){
                ne = new E();

                if(ne != nullptr){
                    *ne = value;

                    mEdges[i][j] = ne;

                    mEdgeCount++;
                } else {
                    THROW_EXCEPTION(NoEnoughMemeoryException, "No memory to store new edge value ...");
                }

            } else {
                *ne = value;
            }
        }

        return ret;
    }

    bool removeEdge(int i, int j) override
    {
        bool ret = ((0 <= i) && (i < vCount())) && ((0 <= j) && (j < vCount()));

        if(ret){
            E* toDel = mEdges[i][j];

            mEdges[i][j] = nullptr;

            if(toDel != nullptr){
                mEdgeCount--;

                delete toDel;
            }
        }

        return ret;
    }

    int vCount() override
    {
        return N;
    }

    int eCount() override
    {
        return mEdgeCount;
    }

    int OD(int i) override
    {
        int ret = 0;

        if(0 <= i && i < vCount()){
            for (int j = 0; j < vCount(); j++) {
                if(mEdges[i][j] != nullptr){
                    ret++;
                }
            }
        } else {
            THROW_EXCEPTION(InvalidParameterException, "Index i is invalid ...");
        }

        return ret;
    }

    int ID(int i) override
    {
        int ret = 0;

        if(0 <= i && i < vCount()){
            for (int j = 0; j < vCount(); j++) {
                if(mEdges[j][i] != nullptr){
                    ret++;
                }
            }
        } else {
            THROW_EXCEPTION(InvalidParameterException, "Index i is invalid ...");
        }

        return ret;
    }

    ~MatrixGraph()
    {
        for (int i = 0; i < vCount(); i++) {
            for (int j = 0; j < vCount(); j++) {
                if(mEdges[i][j] != nullptr)
                    delete mEdges[i][j];
            }

            if(mVertexes[i] != nullptr)
                delete mVertexes[i];
        }
    }
};

}

#endif //MATRIXGRAPH_H
