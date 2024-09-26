#pragma once
#include <iostream>
#include <string>
#include "MaterialBibliografico.h"
#include "Usuario.h"
#include <vector>

class Sistema{
    private:
        MaterialBibliografico* biblioteca[100];
        Usuario* listaUsuarios[30];


    public:
        Sistema();
        bool agregarNuevoMaterial(std::string tipo, std::string lista[5]);
        ~Sistema();
        void guardarArchivos(std::fstream& archivo);
        void listaMaterialBiblioteca(MaterialBibliografico* listaAuxiliar[100]);
        bool buscarInformacionMateriales(std::string tipo,std::string nombre,std::string& informacion);
        bool agregarUsuario(std::string nombreUsuario,std::string idUsuario);
        bool eliminarUsuario(std::string idUsuario);
        bool buscarUsuario(std::string idUsuario,std::string& informacion);
        void cargarUsuario(std::string nombreUsuario,std::string id,std::string lista[5]);
        MaterialBibliografico* devolverMaterialxID(std::string idMaterial);
        void guardarUsuarios(std::fstream& archivo);
        void cargarMaterial(std::string tipo, std::string lista[5],bool estado);
        bool prestarMaterial(std::string idUsuario,std::string isbnMaterial);
        bool devolverMaterial(std::string idUsuario,std::string isbnMaterial);
        bool verificarEstadoMaterial(std::string isbnMaterial);
        Usuario* devolverUsuarioxID(std::string idUsuario);
};