#include "../lib/imports.h"

Bucket::Bucket(){}

std::list<int> Bucket::getPaginasDeOverflow(){
    return paginasDeOverflow;
}

void Bucket::resetarListaDeOverflow(){
    paginasDeOverflow.clear();
}
