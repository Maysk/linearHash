#include "../lib/imports.h"

Hash::Hash(){}
Hash::~Hash(){}

Hash Hash::loadHashInfo(){}
void Hash::saveHashInfo(){}
void Hash::redistribui(){}

int Hash::hashChave(int k){
    int numeroDoBucket = k % ((2^level) * quantidadeDeBucketsDoLevel);
    if (numeroDoBucket < next) {
        numeroDoBucket = k%((2^(level+1)) * quantidadeDeBucketsDoLevel);
    }
    return numeroDoBucket;
}

int Hash::localizarChave(int k){
    int numeroDoBucket = hashChave(k);
    Bucket b = listaDeBuckets.at(k);
    std::list<int> listaDePaginas = b.getNumeroDasPaginas();
    std::list<int>::iterator i = listaDePaginas.begin();
    bool isFound = false;

    while(listaDePaginas.end()!=i && !isFound){
        //CarregarPagina da classe armazenamento
    }

}

int Hash::adicionarPar(int k){
    int numeroDoBucket = hashChave(k);

}
int Hash::excluirPar(int k){
    int numeroDoBucket = hashChave(k);

}


