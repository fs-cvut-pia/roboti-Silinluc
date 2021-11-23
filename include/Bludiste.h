#ifndef BLUDISTE_H
#define BLUDISTE_H

#include <vector>
#include <string>

// Tyto tridy nemente, slouzi pro praci s bludistem - na takoveto tride budou testovani vsichni roboti

struct Souradnice { // struct je vicemene to same jako class, akorat jsou vsechny promenne a metody standardne public
    int x;
    int y;
    const bool operator==(Souradnice const& v) { return x == v.x && y == v.y; }
};

// Trida obdelnikoveho bludiste
// Metody pro posun vraci true kdyz se posun zdaril, false kdyz robot narazil do zdi nebo okraje bludiste
// Metoda cil() vraci true pokud je robot v cili, jinak false
// Metoda poloha() vraci aktualni souradnice robota

// Nic vic zde robot nevidi a bludiste musi prozkoumat sam
// Trida si sama eviduje pocty kroku robota a pocty "narazu" do prekazek

class Bludiste {
public:
    Bludiste(int _n, int _m);
    Bludiste(int _n, int _m, Souradnice f);
    Bludiste(int _n, int _m, Souradnice f, std::vector<bool> zdi);
    bool nahoru();
    bool dolu();
    bool vlevo();
    bool vpravo();
    bool cil();
    Souradnice poloha();
    int pocet_kroku();
    int pocet_narazu();
    bool uloz_cestu(std::string nazev_souboru);
protected:
    int n, m; // Rozmery mapy (obdelnik)
    Souradnice r_finish;
    std::vector<bool> wall; // Pole predstavujici steny
private:
    Souradnice r;
    std::vector<Souradnice> cesta;
    int steps, touches; 
    bool finish;
};

// Jednodussi varianta - odkryte bludiste
// Obsahuje stejne metody jako trida Bludiste a navic umi odhalit polohu cile a to, zdali je na libovolnem poli zed

class BludisteOdkryte : public Bludiste {
public:
    BludisteOdkryte(int _n, int _m);
    BludisteOdkryte(int _n, int _m, Souradnice f);
    BludisteOdkryte(int _n, int _m, Souradnice f, std::vector<bool> zdi);
    bool zed(Souradnice u);
    Souradnice poloha_cile();
};

#endif
