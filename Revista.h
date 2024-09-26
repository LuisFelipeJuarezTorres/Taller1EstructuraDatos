#pragma once
#include <iostream>
#include <string>
#include "MaterialBibliografico.h"
#include <fstream>

class Revista : public MaterialBibliografico{
    private:
    std::string numeroEdicion;
    std::string mesPublicacion;

    public:

    Revista(std::string nombreL, std::string nombreAutor, std::string isbn,std::string _numeroEdicion,std::string _mesPublicacion);
    std::string mostrarInformacion() const override;
    void guardarArchivo(std::fstream& archivo) const override;
    ~Revista() override;
    

};