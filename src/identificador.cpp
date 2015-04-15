#include "../lib/imports.h"
Identificador::Identificador(int nSlot, int nPagina, bool isOverflow){
    this->numeroDaPagina = nPagina;
    this->numeroDoSlot = nSlot;
    this->isOverflow = isOverflow;
}
int Identificador::getNumeroDaPagina(){
    return numeroDaPagina;
}
int Identificador::getNumeroDoSlot(){
    return numeroDoSlot;
}
bool Identificador::getIsOverflow(){
    return isOverflow;
}

