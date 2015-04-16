#include "../lib/imports.h"

Hash::Hash(){}
Hash::~Hash(){}

Hash Hash::loadHashInfo(){
    FILE *arquivo = fopen(NOME_PADRAO,"r+");
    if(arquivo==NULL){
        arquivo = fopen(NOME_PADRAO,"w+");
        fprintf(arquivo, "4\n");    //qtd buckets
        fprintf(arquivo,"0\n");       //menorNivel
        fprintf(arquivo,"0\n")         //posicaoDoNext
        fprintf(arquivo,"Bucket: 0 1");
        fprintf(arquivo,"Overflow: f");
        fprintf(arquivo,"Bucket: 2 3");
        fprintf(arquivo,"Overflow: f");
        fprintf(arquivo,"Bucket: 4 5");
        fprintf(arquivo,"Overflow: f");
        fprintf(arquivo,"Bucket: 6 7");
        fprintf(arquivo,"Overflow: f");
    }
    else{
        fscanf(arquivo, "%d", &(this->quantidadeDeBucketsDoLevel) );
        fscanf(arquivo, "%d", )

    }
}
void Hash::saveHashInfo(){
    FILE *arquivo = fopen(NOME_PADRAO,"r+");

}

void Hash::redistribuir(){


}


int Hash::hashChave(int k){
    int numeroDoBucket = k % ((2^level) * quantidadeDeBucketsDoLevel);
    if (numeroDoBucket < next) {
        numeroDoBucket = k%((2^(level+1)) * quantidadeDeBucketsDoLevel);
    }
    return numeroDoBucket;
}

int Hash::localizarChave(int chave){
    int numeroDoBucket = hashChave(chave);
    Bucket b = listaDeBuckets.at(numeroDoBucket);
    int ridDaChave;


    Pagina paginaSendoPercorrida;
    std::list<int>::iterator i =  b.getNumeroDasPaginas().begin();

    while( b.getNumeroDasPaginas().end()!=i){
        paginaSendoPercorrida = entradasDeDados->carregarPagina(*i);
        ridDaChave = paginaSendoPercorrida.buscarRidDaChaveNaPagina(chave);
        if(ridDaChave>=0 ){
                return ridDaChave;
        }
        i++;
    }

    i = b.getPaginasDeOverflow().begin();
    while( b.getPaginasDeOverflow().end()!=i){
        paginaSendoPercorrida = entradasDeDados->carregarPaginaOverflow(*i);
        ridDaChave = paginaSendoPercorrida.buscarRidDaChaveNaPagina(chave);
        if(ridDaChave>=0){
            return ridDaChave;
        }
        i++;
    }

    return -1;

}

bool Hash::adicionarPar(int chave, int rid){
    int numeroDoBucket = hashChave(chave);
    Bucket b = listaDeBuckets.at(numeroDoBucket);
    bool paginaFoiAdicionada = false;

    Pagina paginaSendoPercorrida;
    std::list<int>::iterator i =  b.getNumeroDasPaginas().begin();

    //Checa se o par existe nas paginas "normais"
    while( b.getNumeroDasPaginas().end()!=i){
        paginaSendoPercorrida = entradasDeDados->carregarPagina(*i);

        if(paginaSendoPercorrida.checarSeExitePar(chave, rid)){
            return false;
        }
        i++;
    }

    //Checa se o par existe nas paginas overflow
    i = b.getPaginasDeOverflow().begin();
    while(b.getPaginasDeOverflow().end()!=i){
        paginaSendoPercorrida = entradasDeDados->carregarPaginaOverflow(*i);
        if(paginaSendoPercorrida.checarSeExitePar(chave, rid)){
            return false;
        }
        i++;
    }

    //Tenta adicionar o par nas paginas "normais"
    i =  b.getNumeroDasPaginas().begin();
    while(b.getNumeroDasPaginas().end()!=i && !paginaFoiAdicionada){
        paginaSendoPercorrida = entradasDeDados->carregarPagina(*i);
        paginaFoiAdicionada = paginaSendoPercorrida.adicionarParNaPagina(chave,rid);
        i++;
    }

    //Tenta adicionar o par nas paginas overflow

    i = b.getPaginasDeOverflow().begin();
     while(b.getPaginasDeOverflow().end()!=i && !paginaFoiAdicionada){
        paginaSendoPercorrida = entradasDeDados->carregarPaginaOverflow(*i);
        paginaFoiAdicionada = paginaSendoPercorrida.adicionarParNaPagina(chave,rid);
        i++;
    }

    if(!paginaFoiAdicionada){
        Pagina novaPagina = new Pagina();
        novaPagina.adicionarParNaPagina(chave,rid);
        entradasDeDados->adicionarPagina(novaPagina);
        paginaFoiAdicionada = true;
    }

    if(quantidadeDeOverflow > 0){
        redistribuir();
    }
    return true;
}


bool Hash::excluirPar(int chave){
    int numeroDoBucket = hashChave(chave);
    Bucket b = listaDeBuckets.at(numeroDoBucket);

    Pagina paginaSendoPercorrida;
    std::list<int>::iterator i =  b.getNumeroDasPaginas().begin();

    //Checa se o par existe nas paginas "normais"
    while( b.getNumeroDasPaginas().end()!=i){
        paginaSendoPercorrida = entradasDeDados->carregarPagina(*i);
        paginaSendoPercorrida.excluirChaveDdPagina(chave);
        i++;
    }

    //Checa se o par existe nas paginas overflow
    i = b.getPaginasDeOverflow().begin();
    while(b.getPaginasDeOverflow().end()!=i){
        paginaSendoPercorrida = entradasDeDados->carregarPaginaOverflow(*i);
        paginaSendoPercorrida.excluirChaveDdPagina(chave);
        i++;
    }

    return 0;
}



