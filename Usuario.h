#pragma once
#include "MaterialBibliografico.h"
#include <iostream>
#include <string>


class Usuario{
    private:

        std::string nombreUsuario;
        std::string idUsuario;
        MaterialBibliografico* materialesPrestados[5];

    public:

        Usuario( std::string _nombreUsuario,std::string _idUsuario);
        bool prestarMaterial(MaterialBibliografico* material1);
        bool devolverMaterial(MaterialBibliografico* material2);
        void mostrarMaterialesPrestados() const;
        std::string getNombreUsuario();
        std::string getIdUsuario();
        void guardarArchivo(std::fstream& archivo) const;
       

};