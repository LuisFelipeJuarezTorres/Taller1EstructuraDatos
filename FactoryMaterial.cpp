#include "FactoryMaterial.h"
#include <iostream>
#include <string>

MaterialBibliografico* FactoryMaterial::factoryM(std::string tipo,std::string lista[5]){
    
    if(tipo == "Libro" || tipo == "LIBRO"){
        MaterialBibliografico* p = new Libro(lista[0],lista[1],lista[2],lista[3],lista[4]);
        return p;

    }else if(tipo == "Revista" || tipo == "REVISTA"){
        MaterialBibliografico* p = new Revista(lista[0],lista[1],lista[2],lista[3],lista[4]);
        return p;

    }else{

        return nullptr;

    }
}