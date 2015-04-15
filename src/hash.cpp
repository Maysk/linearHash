#include "../lib/imports.h"

Hash::Hash(){}
Hash::~Hash(){}
/*
Hash Hash::loadHashInfo(){}
void Hash::saveHashInfo(){}
*/
void Hash::redistribuir(){}


int Hash::hashChave(int k){
    int numeroDoBucket = k % ((2^level) * quantidadeDeBucketsDoLevel);
    if (numeroDoBucket < next) {
        numeroDoBucket = k%((2^(level+1)) * quantidadeDeBucketsDoLevel);
    }
    return numeroDoBucket;
}

Identificador* Hash::localizarChave(int k){
    int numeroDoBucket = hashChave(k);
    Bucket b = listaDeBuckets.at(numeroDoBucket);

    int numeroDoSlot;
    Identificador* identificador;
    Pagina paginaSendoPercorrida;

    std::list<int>::iterator i =  b.getNumeroDasPaginas().begin();

    while( b.getNumeroDasPaginas().end()!=i){
        paginaSendoPercorrida = entradasDeDados->carregarPagina(*i);
        numeroDoSlot = paginaSendoPercorrida.buscarChaveNaPagina(k);
        if(numeroDoSlot>=0 ){
                identificador = new Identificador(numeroDoSlot,*i,true);
                return identificador;
        }
        i++;
    }

    i = b.getPaginasDeOverflow().begin();
    while( b.getPaginasDeOverflow().end()!=i){
        paginaSendoPercorrida = entradasDeDados->carregarPaginaOverflow(*i);
        numeroDoSlot = paginaSendoPercorrida.buscarChaveNaPagina(k);
        if(numeroDoSlot>=0){
            identificador = new Identificador(numeroDoSlot,*i,false);
            return identificador;
        }
        i++;
    }

    return NULL;

}

int Hash::adicionarPar(int k){
    int numeroDoBucket = hashChave(k);
    Bucket b = listaDeBuckets.at(numeroDoBucket);


    if(quantidadeDeOverflow > 0){
        redistribuir();
    }
    return 0;
}

/*
int Hash::excluirPar(int k){
    int numeroDoBucket = hashChave(k);
    Bucket b = listaDeBuckets.at(numeroDoBucket);
    return 0;
}


*/
