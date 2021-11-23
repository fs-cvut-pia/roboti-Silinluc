#include "SuperRobot.h"



bool SuperRobot::start(BludisteOdkryte & map) {
    route.clear();
    navstivene.clear();
    Souradnice* s = this->newCoord(map.poloha().x,map.poloha().y);
    navstivene.push_back(s);
    PathPoint* p = this->newPoint();
    this->checkDuplicatePath(p,map.poloha());
    route.push_back(p);
    return true;
}

bool SuperRobot::start(Bludiste & map) {
    route.clear();
    navstivene.clear();
    Souradnice* s = this->newCoord(map.poloha().x,map.poloha().y);
    navstivene.push_back(s);
    PathPoint* p = this->newPoint();

    route.push_back(p);
    return true;
}
bool SuperRobot::stop() {
    for (Souradnice*  point : navstivene) {
        free(point);
    }

    for (PathPoint*  point : route) {
        free(point);
    }
    route.clear();
    navstivene.clear();
    return true;
}
void SuperRobot::krok(Bludiste & map) {
    if ((route.size() == 0) || map.cil()) {
                return;
    }
    PathPoint* currentPoint = route.back();
    Souradnice currentPosition = map.poloha();
    bool success = false;

    if (currentPoint->canRight) {
        currentPoint->canRight = false;
        currentPoint->right = true;
        navstivene.push_back(this->newCoord(currentPosition.x+1,currentPosition.y));
        if (map.vpravo()) {
            success = true;
        } else {
            currentPoint->right = false;
        }
    } else if (currentPoint->canLeft) {
        currentPoint->canLeft = false;
        currentPoint->left = true;
        navstivene.push_back(this->newCoord(currentPosition.x-1,currentPosition.y));
        if (map.vlevo()) {
            success = true;
        } else {
            currentPoint->left = false;
        }
    } else if (currentPoint->canUp) {
        currentPoint->canUp = false;
        currentPoint->up = true;
        navstivene.push_back(this->newCoord(currentPosition.x,currentPosition.y+1));
        if (map.nahoru()) {
            success = true;
        } else {
            currentPoint->up = false;
        }
    } else if (currentPoint->canDown) {
        currentPoint->canDown = false;
        currentPoint->down = true;
        navstivene.push_back(this->newCoord(currentPosition.x,currentPosition.y-1));
        if (map.dolu()) {
            success = true;
        } else {
            currentPoint->down = false;
        }
    } else {
        //jdeme zpatky dokud nenajdeme jinou odbocku
        bool validPoint = false;
        while (!validPoint) {

            free(route.back());
            route.pop_back();
            if (route.size() == 0) {
                break;
            }
            PathPoint* prev = route.back();
            if (prev->right) {
                map.vlevo();
            } else if (prev->left) {
                map.vpravo();
            } else if (prev->down) {
                map.nahoru();
            } else if (prev->up) {
                map.dolu();
            }
            if (prev->canDown || prev->canLeft || prev->canRight || prev->canUp) {
                validPoint = true;

                prev->up = prev->down = prev->left = prev->right = false;
                this->checkDuplicatePath(prev,map.poloha());
            }
        }
        return;
    }

    if (success) {
        PathPoint* p = this->newPoint();
        this->checkDuplicatePath(p,map.poloha());
        route.push_back(p);
    }
}
void SuperRobot::krok(BludisteOdkryte & map) {
    if ((route.size() == 0) || map.cil()) {
                return;
    }
    PathPoint* curr = route.back();
    Souradnice curPos = map.poloha();
    bool sucess = false;

    if (curr->canRight) {
        curr->canRight = false;
        curr->right = true;
        navstivene.push_back(this->newCoord(curPos.x+1,curPos.y));
        if (map.vpravo()) {
            sucess = true;
        } else {
            curr->right = false;
        }
    } else if (curr->canLeft) {
        curr->canLeft = false;
        curr->left = true;
        navstivene.push_back(this->newCoord(curPos.x-1,curPos.y));
        if (map.vlevo()) {
            sucess = true;
        } else {
            curr->left = false;
        }
    } else if (curr->canUp) {
        curr->canUp = false;
        curr->up = true;
        navstivene.push_back(this->newCoord(curPos.x,curPos.y+1));
        if (map.nahoru()) {
            sucess = true;
        } else {
            curr->up = false;
        }
    } else if (curr->canDown) {
        curr->canDown = false;
        curr->down = true;
        navstivene.push_back(this->newCoord(curPos.x,curPos.y-1));
        if (map.dolu()) {
            sucess = true;
        } else {
            curr->down = false;
        }
    } else {
        //jdeme zpatky dokud nenajdeme jinou odbocku
        bool validPoint = false;
        while (!validPoint) {

            free(route.back());
            route.pop_back();
            if (route.size() == 0) {
                break;
            }
            PathPoint* prev = route.back();
            if (prev->right) {
                map.vlevo();
            } else if (prev->left) {
                map.vpravo();
            } else if (prev->down) {
                map.nahoru();
            } else if (prev->up) {
                map.dolu();
            }
            if (prev->canDown || prev->canLeft || prev->canRight || prev->canUp) {
                validPoint = true;

                prev->up = prev->down = prev->left = prev->right = false;
                this->checkDuplicatePath(prev,map.poloha());
            }
        }
        return;
    }

    if (sucess) {
        PathPoint* p = this->newPoint();
        this->checkDuplicatePath(p,map.poloha());
        route.push_back(p);
    }
}
std::string SuperRobot::jmeno() {
    return "Lucie Silingova";
}

PathPoint* SuperRobot::newPoint() {
    PathPoint* p = (PathPoint*) malloc(sizeof(PathPoint));
    p->canDown = true;
    p->canLeft = true;
    p->canRight = true;
    p->canUp = true;
    p->down = false;
    p->left = false;
    p->right = false;
    p->up = false;
    return p;
}

Souradnice* SuperRobot::newCoord(int x,int y) {
    Souradnice* s = (Souradnice*) malloc(sizeof(Souradnice));
    s->x = x;
    s->y = y;
    return s;
 }

 bool SuperRobot::visited(Souradnice* s)  {
    for (Souradnice*  point : navstivene) {
            if (point->x == s->x && point->y == s->y) return true;
    }
    return false;
 }

void SuperRobot::checkDuplicatePath(PathPoint* ppoint,Souradnice pos) {
    for (Souradnice*  point : navstivene) {
        if (point->x == pos.x && point->y == pos.y-1) ppoint->canDown = false;
        if (point->x == pos.x && point->y == pos.y+1) ppoint->canUp = false;
        if (point->x == pos.x-1 && point->y == pos.y) ppoint->canLeft = false;
        if (point->x == pos.x+1 && point->y == pos.y) ppoint->canRight = false;
        if (pos.x == 0) ppoint->canLeft = false;
        if (pos.y == 0) ppoint->canDown = false;
    }
}
