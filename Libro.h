#pragma once
#include "MaterialBibliografico.h"
#include <iostream>
#include <string>
#include <fstream>



class Libro : public MaterialBibliografico{
    
    private:
    std::string fechaPublicacion;
    std::string resumen;

    public:

    Libro(std::string nombreL, std::string nombreAutor, std::string isbn,std::string _fechaPublicacion,std::string _resumen);
    std::string mostrarInformacion() const override;
    void guardarArchivo(std::fstream& archivo) const override;
    ~Libro() override;
};