#include <iostream>
#include <string>
#include "Revista.h"
#include <fstream>

Revista::Revista(std::string nombreL, std::string nombreAutor, std::string isbn,std::string _numeroEdicion,std::string _mesPublicacion):MaterialBibliografico(nombreL,nombreAutor,isbn){
    this -> numeroEdicion = _numeroEdicion;
    this -> mesPublicacion = _mesPublicacion;
}

std::string Revista::mostrarInformacion() const{

    std::string informacion = "Revista: " + nombre + "\nISBN: " + isbn + "\nAutor: " + autor
    + "\nNúmero de edición: " + numeroEdicion + "\nMes de publicación: " + mesPublicacion
    +"\nPrestado: " + (estado? "Si" : "No");

    return informacion;

}

void Revista::guardarArchivo(std::fstream& archivo) const{
    archivo << "REVISTA;" << nombre << ";"<< autor << ";" << isbn << ";" << (estado? "true":"false") << ";" << numeroEdicion << ";" << mesPublicacion <<std::endl;
    archivo << "CONTENIDO FIN" << std::endl;
}

Revista::~Revista(){
    
}

