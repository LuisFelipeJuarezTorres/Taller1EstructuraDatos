#include "Usuario.h"
#include <iostream>
#include <string>

Usuario::Usuario(std::string _nombreUsuario,std::string _idUsuario){
    this -> nombreUsuario = _nombreUsuario;
    this -> idUsuario = _idUsuario;
    for(int i = 0;i<5;i++){

        materialesPrestados[i] = nullptr;
    }

}

void Usuario::guardarArchivo(std::fstream& archivo) const{
    
    if(!archivo.is_open()){
        std::cerr<<"Error al abrir el archivo para escritura: "<< std::endl;
        return;
    }

    archivo << nombreUsuario << ";" <<idUsuario<<";";
    bool primero = true;
    for(int i = 0;i<5;i++){
        if(materialesPrestados[i] != nullptr){
            if(!primero){
                archivo<<";";
            }
            archivo << materialesPrestados[i]->getIsbn();
            primero = false;
        }
    }
    archivo << std::endl; 
}

bool Usuario::prestarMaterial(MaterialBibliografico* material1){
    for(int i = 0;i<5;i++){
        if(materialesPrestados[i] == nullptr){
            material1 -> modificarEstado(true);
            materialesPrestados[i] = material1;
            return true;
        }
    }
    return false;
}

bool Usuario::devolverMaterial(MaterialBibliografico* material2){
    for(int i = 0;i<5;i++){
        if(materialesPrestados[i] == material2){
            material2 -> modificarEstado(false);
            materialesPrestados[i] = nullptr;
            return true;
        }
    }
    return false;
}

void Usuario::mostrarMaterialesPrestados() const{
    for(int i = 0;i<5;i++){
        if(materialesPrestados[i] != nullptr){
            materialesPrestados[i] -> mostrarInformacion();
        }
    }
}


std::string Usuario::getNombreUsuario(){
    return  nombreUsuario;
}
std::string Usuario::getIdUsuario(){
    return idUsuario;
}



