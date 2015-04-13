#include "../lib/imports.h"

Hash::Hash(){

}
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

}

int Hash::adicionarPar(int k){
    int numeroDoBucket = hashChave(k);

}
int Hash::excluirPar(int k){
    int numeroDoBucket = hashChave(k);


}


