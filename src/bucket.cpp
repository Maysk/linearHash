#include "../lib/imports.h"

Bucket::Bucket(){}

std::list<int> Bucket::getPaginasDeOverflow(){
    return paginasDeOverflow;
}

void Bucket::adicionarPaginaDeOverflowAoBucket(int idDaPagina){
    paginasDeOverflow.push_back(idDaPagina);
}
