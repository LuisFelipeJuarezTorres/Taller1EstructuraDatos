#include "App.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <limits>


App::App(){
    s = new Sistema();
}

void App::Menu(){

    cargarDatosM("MaterialB.txt");
    cargarDatosUsuario("Usuarios.txt");

    bool continuar = true;
    while(continuar){
        std::cout<<"\nMenu"<<"\n1.Agregar nuevo libro o revista."<<"\n2.Listar los materiales de la biblioteca."
        <<"\n3.Buscar materiales por título o autor."<<"\n4.Prestar material"<<"\n5.Devolver material"<<"\n6.Ingresar nuevo usuario."
        <<"\n7.Buscar usuario."<<"\n8.Eliminar Usuario"<<"\n9.Salir"<<std::endl;
        std::string opcion;

        getline(std::cin,opcion);
        
        if(opcion == "1"){
            agregarMaterial();
        }else if(opcion == "2"){
            listaMateriales();
        }else if(opcion == "3"){
            buscarMaterialB();
        }else if(opcion == "4"){
            prestarMaterial();
        }else if(opcion == "5"){
            devolverMaterial();
        }else if(opcion == "6"){
            crearUsuario();
        }else if(opcion == "7"){
            buscarUsuario();
        }else if(opcion == "8"){
            eliminarUsuario();
        }else if(opcion == "9"){
            std::cout<<"Saliendo...."<<std::endl;
            guardarDatosM("MaterialB.txt");
            guardarDatosUsuario("Usuarios.txt");
            delete s;
            continuar = false;
        }else{
            std::cout<<"Opcion incorrecta, ingresa una valida."<<std::endl;
        }
    }
}

void App::listaMateriales(){
    MaterialBibliografico* listaAuxiliar[100] = {nullptr};
    s -> listaMaterialBiblioteca(listaAuxiliar);
    
    for(int i = 0;i<100;i++){
        if(listaAuxiliar[i] != nullptr){
            std::string informacion = listaAuxiliar[i] ->mostrarInformacion();
            std::cout<<informacion<<std::endl;
        }
    }
}

void App::prestarMaterial(){

    std::string idUsuario,isbnMaterial;

    std::cout<<"Ingrese el ID del usuario: ";
    std::getline(std::cin,idUsuario);
    std::cout<<"Ingrese el Isbn del material: ";
    std::getline(std::cin,isbnMaterial);

    if(s->prestarMaterial(idUsuario,isbnMaterial)){
        std::cout<<"Material prestado";
    }else{
        std::cout<<"Material no prestado";
    }
}

void App::agregarMaterial(){
    std::string lista[5];
    std::string opcionNombreAutor;
    std::string opcionNombreMaterial;
    std::string opcionIsbn;
    std::string tipo;
    std::string opcion1;
    std::string opcion2;

    std::cout<<"Ingrese nombre del material: ";
    std::cin.clear();
    std::getline(std::cin,opcionNombreMaterial);

    lista[0] = opcionNombreMaterial;
    std::cout<<"Ingrese Isbn del material: ";

    std::getline(std::cin,opcionIsbn);
    lista[2] = opcionIsbn;

    std::cout<<"Ingrese nombre del autor: ";

    std::getline(std::cin,opcionNombreAutor);
    lista[1] = opcionNombreAutor;

    std::cout<<"Ingrese tipo de material: Libro - Revista ";

    std::getline(std::cin, tipo);

    if(tipo == "Revista"){
        std::cout<<"Ingrese numero de edición: ";
   
        getline(std::cin,opcion1);
        lista[3] = opcion1;
        std::cout<<"Ingrese mes de publicación: ";
       
        getline(std::cin,opcion2);
        lista[4] = opcion2;
        if(s -> agregarNuevoMaterial(tipo,lista)){
            std::cout<<"Material ingresado";
        }else{
            std::cout<<"Almacenamiento lleno";
        }

    }else if(tipo == "Libro"){
        std::cout<<"Ingrese fecha de publicación: ";
    
        getline(std::cin,opcion1);
        lista[3] = opcion1;
        std::cout<<"Ingrese el resumen del libro: ";
   
        getline(std::cin,opcion2);
        lista[4] = opcion2;
        if(s -> agregarNuevoMaterial(tipo,lista)){
            std::cout<<"Material ingresado";
        }else{
            std::cout<<"Almacenamiento lleno";
        }


    }else{
        std::cout<<"Opcion incorrecta, ingrese una opcion valida";
    }
}

App::~App(){
    delete s;
}

void App::cargarDatosUsuario(const std::string& nombreArchivo){
    std::fstream archivo(nombreArchivo, std::ios::in);
    if(!archivo.is_open()){
        std::cerr << "Error al abrir el archivo: " << nombreArchivo << std::endl;
        return;
    }
     std::string linea;

    while(std::getline(archivo,linea)){
        std::string lista[5];
        std::string nombreUsuario;
        std::string idUsuario;
        std::istringstream stream(linea);

        std::getline(stream,nombreUsuario,';');
        std::getline(stream,idUsuario,';');

        for(int i = 0;i<5;i++){
            if(!std::getline(stream,lista[i],';')){
                std::getline(stream,lista[i]);
                break;
            }
        }

        s -> cargarUsuario(nombreUsuario,idUsuario,lista);

    }
        
}

void App::cargarDatosM(const std::string& nombreArchivo){
    std::fstream archivo(nombreArchivo, std::ios::in);
    if(!archivo.is_open()){
        std::cerr << "Error al abrir el archivo: " << nombreArchivo << std::endl;
        return;
    }
    std::string linea;
    while(std::getline(archivo,linea)){
        std::string lista[5];
        std::string tipo;
        std::string estado;
        std::istringstream stream(linea);

        std::getline(stream,tipo,';');
        std::getline(stream,lista[0],';');
        std::getline(stream,lista[1],';');
        std::getline(stream,lista[2],';');
        std::getline(stream,estado,';');
        std::getline(stream,lista[3],';');
        std::getline(stream,lista[4]);
        

        std::string contenido,lineaResumen;
        bool estadox;

        if(tipo=="LIBRO"){
            while(std::getline(archivo,lineaResumen) && lineaResumen != "CONTENIDO FIN"){
                contenido += lineaResumen;
            }
            
            lista[4] = contenido;
            if(estado == "true"){
                estadox = true;
            }else if(estado == "false"){
                estadox = false;
            }
            
            s -> cargarMaterial(tipo,lista,estadox);

        }else if(tipo == "REVISTA"){

             if(estado == "true"){
                estadox = true;
            }else if(estado == "false"){
                estadox = false;
            }

            s -> cargarMaterial(tipo,lista,estadox);
            std::getline(archivo,lineaResumen);
            
        }

    }
    archivo.close();
}

void App::guardarDatosUsuario(const std::string& nombreArchivo){
    std::fstream archivo(nombreArchivo, std::ios::out | std::ios::trunc);
    if(!archivo.is_open()){
        std::cerr<<"Error al abrir el archivo para escritura: " << nombreArchivo << std::endl;
        return;
    }
    s ->guardarUsuarios(archivo);
}

void App::guardarDatosM(const std::string& nombreArchivo){
    std::fstream archivo(nombreArchivo, std::ios::out | std::ios::trunc);
    if(!archivo.is_open()){
        std::cerr<<"Error al abrir el archivo para escritura: " << nombreArchivo << std::endl;
        return;
    }
    s ->guardarArchivos(archivo);
}

void App::buscarMaterialB(){
    std::cout<<"Desea realizar la busqueda por titulo o autor: ";
    std::string opcion;
    getline(std::cin,opcion);
    std::transform(opcion.begin(),opcion.end(),opcion.begin(), ::tolower);
    std::string opcionNombre;
    if(opcion == "titulo"){
        std::cout<<"Ingrese el titulo del material: ";
        getline(std::cin,opcionNombre);
        std::string informacion;
        if(s ->buscarInformacionMateriales(opcion,opcionNombre,informacion)){
            std::cout<<informacion<<std::endl;
        }else{
            std::cout<<"No se encontro material relacionado con los parámetros ingresados";
        }

    }else if(opcion == "autor"){
        std::cout<<"Ingrese del autor: ";
        getline(std::cin,opcionNombre);
        std::string informacion;
        if(s ->buscarInformacionMateriales(opcion,opcionNombre,informacion)){
            std::cout<<informacion<<std::endl;
        }else {
            std::cout<<"No se encontro material relacionado con los parámetros ingresados";
        }

    }else{
        std::cout<<"Opcion incorrecta, ingrese titulo o autor"<<std::endl;
    }

}

void App::crearUsuario(){
    std::string nombreU,id;
    std::cout<<"Ingrese nombre del nuevo usuario: ";
    getline(std::cin,nombreU);
    
    std::cout<<"Ingrese el ID del nuevo usuario: ";
    getline(std::cin,id);

    if(s->agregarUsuario(nombreU,id)){
        std::cout<<"Usuario ingresado.";
    }else{
        std::cout<<"Lista usuario llena, no se aceptan mas usuarios.";
    }
}
void App::eliminarUsuario(){
    std::string id;
    std::cout<<"Ingrese el ID del usuario que desea eliminar: ";

    getline(std::cin,id);
    if(s -> eliminarUsuario(id)){
        std::cout<<"Usuario eliminado.";
    }else{
        std::cout<<"No se encontro al usuario por lo tanto no se elimino.";
    }
}


void App::buscarUsuario(){
    std::string id;
    std::cout<<"Ingrese el ID del usuario que desea buscar: ";
    getline(std::cin,id);
    std::string informacion;
    if(s -> buscarUsuario(id,informacion)){
        std::cout<<informacion<<std::endl;
    }else{
        std::cout<<"No se encontro al usuario.";
    }

}

void App::devolverMaterial(){

    std::string idUsuario,isbnMaterial;

    std::cout<<"Ingrese el ID del usuario: ";
    std::getline(std::cin,idUsuario);
    std::cout<<"Ingrese el Isbn del material: ";
    std::getline(std::cin,isbnMaterial);

    if(s->devolverMaterial(idUsuario,isbnMaterial)){
        std::cout<<"Material devuelto";
    }else{
        std::cout<<"Material no devuelto";
    }

}





