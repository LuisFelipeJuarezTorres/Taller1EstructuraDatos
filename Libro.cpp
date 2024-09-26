#include "Libro.h"
#include <iostream>
#include <string>
#include <fstream>

Libro::Libro(std::string nombreL, std::string nombreAutor, std::string isbn, std::string _fechaPublicacion, std::string _resumen):MaterialBibliografico(nombreL,nombreAutor,isbn) {
    this->fechaPublicacion = _fechaPublicacion;
    this->resumen = _resumen;
}

std::string Libro::mostrarInformacion() const{
    std::string informacion = "Libro: " + nombre + "\nISBN: " + isbn + "\nAutor: " + autor
    +"\nFecha de publicación: " + fechaPublicacion + "\nResumen: " + resumen
    +"\nPrestado: " + (estado? "Sí":"No");
    return informacion;
}

void Libro::guardarArchivo(std::fstream& archivo) const{
    archivo << "LIBRO;" << nombre << ";" << autor << ";" << isbn << ";" << (estado? "true":"false") << ";" << fechaPublicacion <<std::endl;
    archivo << resumen<<std::endl;
    archivo << "CONTENIDO FIN" <<std::endl;
}

Libro::~Libro(){
    
}
    