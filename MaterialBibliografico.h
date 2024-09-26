#pragma once
#include <iostream>
#include <string>
#include <fstream>

class MaterialBibliografico{
    protected:
        std::string nombre;
        std::string autor;
        std::string isbn;
        bool estado;

    public:
        MaterialBibliografico(std::string nombreL, std::string nombreAutor, std::string isbn);
        virtual ~MaterialBibliografico();
        std::string getNombre();
        std::string getAutor();
        std::string getIsbn();
        bool getEstado();
        void modificarEstado(bool newEstado);
        virtual std::string mostrarInformacion() const = 0; 
        virtual void guardarArchivo(std::fstream& archivo) const;
         
};
