#include "Bludiste.h"
#include <fstream>

Bludiste::Bludiste(int _n, int _m) : n(_n), m(_m), r({0,0}), r_finish({n,m}), steps(0), touches(0), finish(false), wall(n*m) { cesta.push_back({0,0}); }
Bludiste::Bludiste(int _n, int _m, Souradnice f) : Bludiste(_n,_m) { r_finish = f; }
Bludiste::Bludiste(int _n, int _m, Souradnice f, std::vector<bool> zdi) : Bludiste(_n,_m,f) { wall = zdi; }

bool Bludiste::nahoru() { 
    if (r.y < m - 1 && !wall[r.x + (r.y+1)*n]) {
        r.y++;
        steps++;
        if (cil()) finish = true;
	cesta.push_back(r);
        return true;
    }
    else {
        touches++;
        return false;
    }
}
bool Bludiste::dolu() { 
    if (r.y > 0 && !wall[r.x + (r.y-1)*n]) {
        r.y--;
        steps++;
        if (cil()) finish = true;
	cesta.push_back(r);
        return true;
    }
    else {
        touches++;
        return false;
    }
}
bool Bludiste::vlevo() { 
    if (r.x > 0 && !wall[r.x - 1 + r.y*n]) {
        r.x--;
        steps++;
        if (cil()) finish = true;
	cesta.push_back(r);
        return true;
    }
    else {
        touches++;
        return false;
    }
}
bool Bludiste::vpravo() { 
    if (r.x < n - 1 && !wall[r.x + 1 + r.y*n]) {
        r.x++;
        steps++;
        if (cil()) finish = true;
	cesta.push_back(r);
        return true;
    }
    else {
        touches++;
        return false;
    }
}
bool Bludiste::cil() { 
    if (r == r_finish || finish) return true;
}
Souradnice Bludiste::poloha() { return r; }

int Bludiste::pocet_kroku() { return steps; }
int Bludiste::pocet_narazu() { return touches; }

bool Bludiste::uloz_cestu(std::string nazev_souboru) {
    std::ofstream soubor;
    soubor.open(nazev_souboru,std::ios::out);
    
    if (!soubor) return false;
    
    for (auto & step : cesta) {
      soubor << step.x << " " << step.y << "\n";
    }
    
    soubor.close();
    return true;
}

BludisteOdkryte::BludisteOdkryte(int _n, int _m) : Bludiste(_n,_m) { }
BludisteOdkryte::BludisteOdkryte(int _n, int _m, Souradnice f) : Bludiste(_n,_m,f) { }
BludisteOdkryte::BludisteOdkryte(int _n, int _m, Souradnice f, std::vector<bool> zdi) : Bludiste(_n,_m,f,zdi) { }

bool BludisteOdkryte::zed(Souradnice u) { return wall[u.x + u.y*n]; }
Souradnice BludisteOdkryte::poloha_cile() { return r_finish; }
