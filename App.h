#pragma once
#include <iostream>
#include <string>
#include "Sistema.h"

class App{
private: 
    Sistema* s;
public:
    void Menu();
    void agregarMaterial();
    void cargarDatosM(const std::string& nombreArchivo);
    void guardarDatosM(const std::string& nombreArchivo);
    void buscarMaterialB();
    App();
    ~App();
    void buscarUsuario();
    void eliminarUsuario();
    void crearUsuario();
    void cargarDatosUsuario(const std::string& nombreArchivo);
    void guardarDatosUsuario(const std::string& nombreArchivo);
    void prestarMaterial();
    void devolverMaterial();
    void listaMateriales();
};