#include "MaterialBibliografico.h"

MaterialBibliografico::MaterialBibliografico(std::string nombreL, std::string nombreAutor, std::string isbn){
    this->nombre = nombreL;
    this->autor = nombreAutor;
    this->isbn = isbn;
    this->estado = false;
   
}

std::string MaterialBibliografico::getNombre(){
    return nombre;
}
std::string MaterialBibliografico::getAutor(){
    return autor;
}
std::string MaterialBibliografico::getIsbn(){
    return isbn;
}
bool MaterialBibliografico::getEstado(){
    return estado;
}

void MaterialBibliografico::modificarEstado(bool newEstado){
    this->estado = newEstado;
}

MaterialBibliografico::~MaterialBibliografico(){

}
void MaterialBibliografico::guardarArchivo(std::fstream& archivo) const{
    
}





