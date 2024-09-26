#include "Sistema.h"
#include <iostream>
#include <string>
#include "FactoryMaterial.h"
#include "MaterialBibliografico.h"
#include <fstream>
#include <algorithm>
#include <vector>

Sistema::Sistema(){
    for(int i = 0;i<100;i++){
        biblioteca[i] = nullptr;
    }
    for(int i = 0;i<30;i++){
        listaUsuarios[i] = nullptr;
    }
}

void Sistema::cargarMaterial(std::string tipo, std::string lista[5],bool estado){
    FactoryMaterial factory;
    MaterialBibliografico* nuevoMaterial = factory.factoryM(tipo,lista);
    if (nuevoMaterial == nullptr) {
        std::cerr << "Error: No se pudo crear el material de tipo: " << tipo << std::endl;
        
    }
    for(int i = 0;i<100;i++){
        if(biblioteca[i] == nullptr){
            biblioteca[i] = nuevoMaterial;
            nuevoMaterial ->modificarEstado(estado);
            break;
        }
    }
}


bool Sistema::agregarNuevoMaterial(std::string tipo, std::string lista[5]){
    FactoryMaterial factory;
    MaterialBibliografico* nuevoMaterial = factory.factoryM(tipo,lista);
    if (nuevoMaterial == nullptr) {
        std::cerr << "Error: No se pudo crear el material de tipo: " << tipo << std::endl;
        return false;
    }
    for(int i = 0;i<100;i++){
        if(biblioteca[i] == nullptr){
            biblioteca[i] = nuevoMaterial;
            return true;
        }
    }
    delete nuevoMaterial;
    return false;
}

Sistema::~Sistema(){
    for(int i = 0;i<100;i++){
        if(biblioteca[i] != nullptr){
            delete biblioteca[i];    
        }
    }
    for(int i = 0;i<30;i++){
        if(listaUsuarios[i] != nullptr){
            delete listaUsuarios[i];    
        }
    } 
}

void Sistema::guardarArchivos(std::fstream& archivo){
    for(int i = 0;i<100;i++){
        if (biblioteca[i] != nullptr) { 
            biblioteca[i]->guardarArchivo(archivo);
        } else {
        }
    }

}

void Sistema::guardarUsuarios(std::fstream& archivo){
    if(!archivo.is_open()){
        std::cerr<<"Error al abrir el archivo para escritura: " << std::endl;
        return;
    }
    for(int i = 0;i<30;i++){
        if(listaUsuarios[i] != nullptr){ 
            listaUsuarios[i] -> guardarArchivo(archivo);
        }
    }
}

void Sistema::listaMaterialBiblioteca(MaterialBibliografico* listaAuxiliar[100]){
    int count = 0;
    for(int i = 0;i<100;i++){
        if(biblioteca[i] != nullptr){
            listaAuxiliar[count] = biblioteca[i];
            count += 1;
        }
    }
}

bool Sistema::buscarInformacionMateriales(std::string tipo,std::string nombre,std::string& informacion){
    std::transform(nombre.begin(),nombre.end(),nombre.begin(), ::tolower);
    bool encontrado = false;
    if(tipo == "autor"){
        for(int i = 0;i<100;i++){
            if(biblioteca[i] != nullptr){
                std::string autor = biblioteca[i]->getAutor();
                std::transform(autor.begin(),autor.end(),autor.begin(), ::tolower);
                if(autor  == nombre){
                    informacion += biblioteca[i] -> mostrarInformacion();
                    encontrado = true;
                }
            }
        }
    
    }else if(tipo == "titulo"){
        for(int i = 0;i<100;i++){
            if(biblioteca[i] != nullptr){
                std::string titulo = biblioteca[i]->getNombre();
                std::transform(titulo.begin(),titulo.end(),titulo.begin(), ::tolower);
                if(titulo  == nombre){ 
                    informacion = biblioteca[i] -> mostrarInformacion();
                    return true;
                }
            }
        }    
    }
    return encontrado;
}

bool Sistema::prestarMaterial(std::string idUsuario,std::string isbnMaterial){

    Usuario* usuario = devolverUsuarioxID(idUsuario);

    if(usuario == nullptr){
        std::cout<<"Usuario no encontrado";
        return false;
    }
    
    bool estadoMaterial = verificarEstadoMaterial(isbnMaterial);

    if(estadoMaterial){
      std::cout<<"El material ya ha sido prestado";
      return false;  
    }

    MaterialBibliografico* material = devolverMaterialxID(isbnMaterial);
    
    if(material == nullptr){
        std::cout<<"Material no encontrado"<<std::endl;
        return false;
    }

    if(usuario ->prestarMaterial(material)){
        return true;
    }else{
        std::cout<<"El usuario a superado el maximo de materiales que puede solicitar prestados";
        return false;
    }
}

bool Sistema::devolverMaterial(std::string idUsuario,std::string isbnMaterial){
     Usuario* usuario = devolverUsuarioxID(idUsuario);

    if(usuario == nullptr){
        std::cout<<"Usuario no encontrado";
        return false;
    }

    bool estadoMaterial = verificarEstadoMaterial(isbnMaterial);

    if(estadoMaterial == false){
      std::cout<<"El material ya se encontraba en la biblioteca, no era necesario devolverlo.";
      return false;  
    }

    MaterialBibliografico* material = devolverMaterialxID(isbnMaterial);
    
    if(material == nullptr){
        std::cout<<"Material no encontrado"<<std::endl;
        return false;
    }

    if(usuario ->devolverMaterial(material)){
        return true;
    }else{
        std::cout<<"No se a encontrado el material entre los materiales prestados al usuario.";
        return false;
    }
}


Usuario* Sistema::devolverUsuarioxID(std::string idUsuario){
    for(int i = 0;i<30;i++){
        if(listaUsuarios[i] != nullptr){
            if(listaUsuarios[i] -> getIdUsuario() == idUsuario){
                return listaUsuarios[i];
            }
        }
    }
    return nullptr;
}

bool Sistema::verificarEstadoMaterial(std::string isbnMaterial){
    for(int i = 0;i<100;i++){
       if(biblioteca[i] != nullptr && (biblioteca[i] ->getIsbn() == isbnMaterial)){
            if(biblioteca[i] -> getEstado() == true){
                return true;
            }
       }
    }    
    return false;
}

void Sistema::cargarUsuario(std::string nombreUsuario,std::string id,std::string lista[5]){
    
    Usuario* usuario;
    for(int i = 0;i<30;i++){
        if(listaUsuarios[i] == nullptr){
            usuario = new Usuario(nombreUsuario,id);
            listaUsuarios[i] = usuario;
            break;
        }
    }

    for(int i = 0;i<5;i++){
        if(!lista[i].empty()){
            usuario -> prestarMaterial(devolverMaterialxID(lista[i]));
        }
    }
}

MaterialBibliografico* Sistema::devolverMaterialxID(std::string isbn){
    for(int i = 0;i<100;i++){
        if(biblioteca[i] != nullptr){
            if(biblioteca[i] -> getIsbn() == isbn){
                return biblioteca[i];
            }
        }   
    }  
    return nullptr;  
}



bool Sistema::agregarUsuario(std::string nombreUsuario,std::string idUsuario){
    for(int i = 0;i<30;i++){
        if(listaUsuarios[i] == nullptr){
            listaUsuarios[i] = new Usuario(nombreUsuario,idUsuario);
            return true;
        }
    }
    return false;
}

bool Sistema::eliminarUsuario(std::string idUsuario){
    for(int i = 0;i<30;i++){
        if(listaUsuarios[i] != nullptr){

            if(listaUsuarios[i] -> getIdUsuario() == idUsuario){
                delete listaUsuarios[i];
                listaUsuarios[i] = nullptr;
                return true;
            }
        }

    }
    return false;
}
bool Sistema::buscarUsuario(std::string idUsuario,std::string& informacion){
    for(int i = 0;i<30;i++){
        if(listaUsuarios[i] != nullptr){
            if(listaUsuarios[i] -> getIdUsuario() == idUsuario){
                informacion = "\nNombre" + (listaUsuarios[i] -> getNombreUsuario()) + "\nID de usuario:  " + (listaUsuarios[i]->getIdUsuario());
                return true;
            }
        }

    }
    return false;
}

