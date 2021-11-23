#ifndef SUPER_ROBOT_H
#define SUPER_ROBOT_H
#include "Prohledavac.h"
#include <vector>
#include <algorithm>

typedef struct pathPoint {
    bool up;
    bool down;
    bool left;
    bool right;
    bool canUp;
    bool canDown;
    bool canLeft;
    bool canRight;
} PathPoint;


class SuperRobot: public Prohledavac
{
    public:
        bool start(Bludiste & map);
        bool start(BludisteOdkryte & map);
        bool stop();
        void krok(Bludiste & map);
        void krok(BludisteOdkryte & map);
        std::string jmeno();
    protected:

    private:
        std::vector<PathPoint*> route;
        std::vector<Souradnice*> navstivene;
        PathPoint* newPoint();
        Souradnice* newCoord(int x,int y);
        void checkDuplicatePath(PathPoint* point,Souradnice pos);
        bool visited(Souradnice* s);
};

#endif // SUPER_ROBOT_H
