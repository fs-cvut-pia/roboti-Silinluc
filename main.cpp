#include "Prohledavac.h"
#include "Bludiste.h"

// include na hlavicku vasi tridy
#include "VasRobot.h" 

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>

struct Problem {
    std::string nazev;
    Bludiste bludiste;
    BludisteOdkryte bludiste_odkryte;
};

template <class BL>
void projdi(BL & bludiste, Prohledavac & robot) {         
    
    if (!robot.start(bludiste))
        std::cout << "Nepodarilo se inicializovat robota :(\n";
    else {
        while (!bludiste.cil() && bludiste.pocet_kroku() < 50000)
            robot.krok(bludiste);
        
        if (bludiste.cil())    
            std::cout << robot.jmeno() << " potreboval " << bludiste.pocet_kroku() << " kroku a " << bludiste.pocet_narazu() << " narazu.\n";
        else 
            std::cout << robot.jmeno() << " nenasel cestu.\n";
            
        if (!robot.stop())
            std::cout << "Pomoc, robota nejde vypnout!!!\n";
    }
}

bool nacti_bludiste(std::string nazev_souboru, std::vector<Problem> & ukoly) {
    std::ifstream soubor;
    std::string radka;
    soubor.open(nazev_souboru,std::ios::in);
    
    if (!soubor) return false;
    
    while (std::getline(soubor, radka)) {
        std::stringstream radka_buffer;
        radka_buffer << radka;
        
        int n,m;
        std::string nazev;
        Souradnice f;
        radka_buffer >> nazev >> n >> m >> f.x >> f.y;
        
        std::vector<bool> zdi(n*m);
        for (int i=0; i<zdi.size(); ++i) {
            int h;
            radka_buffer >> h;
            zdi[i] = h == 1;
        }
        
        ukoly.push_back(Problem{nazev,Bludiste(n,m,f,zdi),BludisteOdkryte(n,m,f,zdi)});
    }
    
    soubor.close();
    return true;
}

int main() {
  
    std::vector<Problem> ukoly;
    
    if (!nacti_bludiste("bludiste.dat",ukoly)) {
        std::cout << "Nepovedlo se nacist bludiste.\n";
        return 1;
    }
    
    //ukoly.push_back(Problem{"Prazdny1",Bludiste(20,30,{15,27}),BludisteOdkryte(20,30,{15,27})});
    
    Prohledavac* robot = new VasRobot(); // tady doplnite konstruktor tridy vaseho robota
    
    for (auto & ukol : ukoly) {
        std::cout << "Prohledavam bludiste " << ukol.nazev << ": \n";
        
        projdi(ukol.bludiste, *robot);

	    ukol.bludiste.uloz_cestu(ukol.nazev + "_cesta.dat");
        
        projdi(ukol.bludiste_odkryte, *robot);
	
	    ukol.bludiste_odkryte.uloz_cestu(ukol.nazev + "_odkryte_cesta.dat");
    }
    
    delete robot;

    return 0;
}
