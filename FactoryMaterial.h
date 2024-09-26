#pragma once
#include <iostream>
#include <string>
#include "MaterialBibliografico.h"
#include "Libro.h"
#include "Revista.h"

class FactoryMaterial{
    public:

    MaterialBibliografico* factoryM(std::string tipo,std::string lista[5]);
    
};