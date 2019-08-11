#ifndef QUEUESOLUTION_H
#define QUEUESOLUTION_H

#include "Object.h"
#include "LinkList.h"

namespace DTLib
{

template<int SIZE>
class QueueSolution : public Object
{
protected:
    enum { N = SIZE + 2 };
    enum { EmptyPosition, QueuePosition ,BorderPosition };

    struct Pos : public Object
    {
        Pos(int px = 0, int py = 0):x(px), y(py) {}
        int x;
        int y;
    };

    int chessboard[N][N];
    Pos direction[3];
    LinkList<Pos> solution;
    int count;

    void init()
    {
        count = 0;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                chessboard[j][i] = chessboard[i][j] = BorderPosition;
            }
        }

        for (int i = 1; i <= SIZE; i++) {
            for (int j = 1; j <= SIZE; j++) {
                chessboard[i][j] = EmptyPosition;
            }
        }

        direction[0].x = -1;
        direction[0].y = -1;
        direction[1].x = 0;
        direction[1].y = -1;
        direction[2].x = 1;
        direction[2].y = -1;
    }

    void print()
    {
        for (solution.move(0); !solution.end(); solution.next()) {
            std::cout << "(" << solution.current().x << "," << solution.current().y << ")";
        }
        std::cout << std::endl;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                switch (chessboard[i][j]) {
                case EmptyPosition:
                    std::cout << " ";
                    break;
                case QueuePosition:
                    std::cout << "#";
                    break;
                case BorderPosition:
                    std::cout << "*";
                    break;
                }
            }

            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    //no queue
    bool check(int x, int y, int d)
    {
        bool flag = true;

        do{
            x += direction[d].x;
            y += direction[d].y;
            flag = flag && (chessboard[x][y] == EmptyPosition);
        } while(flag);

        return (chessboard[x][y] == BorderPosition);
    }

    void run(int j)
    {
        if(j <= SIZE)
        {
            for (int i = 1; i <= SIZE; i++) {
                if(check(i, j, 0) && check(i, j, 1) && check(i, j, 2)){
                    chessboard[i][j] = QueuePosition;

                    solution.insert(Pos(i, j));

                    run(j + 1);

                    chessboard[i][j] = EmptyPosition;
                    solution.remove(solution.length() - 1);
                }
            }
        }
        else {
            count++;
            print();
        }
    }

public:
    QueueSolution()
    {
        init();
    }

    void run()
    {
        run(1);
        std::cout << "Total: " << count << std::endl;
    }
};

}
#endif // QUEUESOLUTION_H
