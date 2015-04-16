#include "../lib/imports.h"

Hash::Hash(){

}
Hash::~Hash(){}

void Hash::adicionarNovoBucket(){
    Bucket *b = new Bucket();
    listaDeBuckets.push_back(*b);
    Pagina *paginaVazia = new Pagina();
    entradasDeDados->adicionarPagina(*paginaVazia);
    entradasDeDados->adicionarPagina(*paginaVazia);

}

Hash Hash::loadHashInfo(){
    FILE *arquivo = fopen(NOME_PADRAO,"r+");
    if(arquivo==NULL){
        arquivo = fopen(NOME_PADRAO,"w+");
        fprintf(arquivo, "4\n");    //qtd buckets
        fprintf(arquivo, "2\n");    //qtd pagina por bucket
        fprintf(arquivo,"0\n");     //qtd de overflow
        fprintf(arquivo,"0\n");     //menorlevel
        fprintf(arquivo,"0\n");     //posicaoDoNext
        fprintf(arquivo,"B0: f\n");
        fprintf(arquivo,"Overflow: f\n");
        fprintf(arquivo,"Bucket: 2 3\n");
        fprintf(arquivo,"Overflow: f\n");
        fprintf(arquivo,"Bucket: 4 5\n");
        fprintf(arquivo,"Overflow: f\n");
        fprintf(arquivo,"Bucket: 6 7\n");
        fprintf(arquivo,"Overflow: f\n");
    }
    else{
        fscanf(arquivo, "%d", &(this->quantidadeDeBucketsInicial));
        fscanf(arquivo, "%d", &(this->quantidadeDePaginasPorBucket));
        fscanf(arquivo, "%d", &(this->quantidadeDeOverflow));
        fscanf(arquivo, "%d", &(this->level));
        fscanf(arquivo, "%d", &(this->next));

    }
}
void Hash::saveHashInfo(){
    FILE *arquivo = fopen(NOME_PADRAO,"r+");

}

void Hash::redistribuir(){
    Bucket* bucketDividido;
    Par par;
    Pagina paginaSendoPercorrida;
    Pagina *paginaParaOBucketA;
    Pagina *paginaParaOBucketB;
    Pagina *vazia;
    std::list<Pagina> bucketA;
    std::list<Pagina> bucketB;
    std::list<Pagina>::iterator iterador;
    int paginaDeOverflow;
    int numeroDePaginasJaAdicionadas;

    this->quantidadeDeOverflow =- listaDeBuckets.at(next).getPaginasDeOverflow().size();
    this->adicionarNovoBucket();

    vazia= new Pagina();
    paginaParaOBucketA = new Pagina();
    paginaParaOBucketB = new Pagina();

    for(int j=0; j<quantidadeDePaginasPorBucket; j++){
         paginaSendoPercorrida = entradasDeDados->carregarPagina(next*quantidadeDePaginasPorBucket + j);
         for(int i=0; i<10;i++){
            par = (paginaSendoPercorrida.arrayDosPares)[i];
            if(((par.chave) % ((2^(level+1)) * quantidadeDeBucketsInicial))== next){
                paginaParaOBucketA->adicionarParNaPagina(par.chave, par.rid);
            }
            else{
                paginaParaOBucketB->adicionarParNaPagina(par.chave, par.rid);
            }

            if(!(paginaParaOBucketA->temPosicaoVazia())){
                bucketA.push_back(*paginaParaOBucketA);
                delete paginaParaOBucketA;
                paginaParaOBucketA = new Pagina();
            }

            if(!(paginaParaOBucketB->temPosicaoVazia())){
                bucketB.push_back(*paginaParaOBucketA);
                delete paginaParaOBucketB;
                paginaParaOBucketB = new Pagina();
            }

         }

    }

    while(!(bucketDividido->getPaginasDeOverflow().empty())){
        paginaDeOverflow = bucketDividido->getPaginasDeOverflow().back();
        bucketDividido->getPaginasDeOverflow().pop_back();
        paginaSendoPercorrida = entradasDeDados->carregarPaginaOverflow(paginaDeOverflow);
        entradasDeDados->exluirPagina(paginaDeOverflow);
        for(int i=0; i<10;i++){
            par = (paginaSendoPercorrida.arrayDosPares)[i];
            if(((par.chave) % ((2^(level+1)) * quantidadeDeBucketsInicial))== next){
                paginaParaOBucketA->adicionarParNaPagina(par.chave, par.rid);
            }
            else{
                paginaParaOBucketB->adicionarParNaPagina(par.chave, par.rid);
            }

            if(!(paginaParaOBucketA->temPosicaoVazia())){
                bucketA.push_back(*paginaParaOBucketA);
                delete paginaParaOBucketA;
                paginaParaOBucketA = new Pagina();
            }

            if(!(paginaParaOBucketB->temPosicaoVazia())){
                bucketB.push_back(*paginaParaOBucketA);
                delete paginaParaOBucketB;
                paginaParaOBucketB = new Pagina();
            }
        }
    }


    if(bucketA.size()<1){bucketA.push_back(*vazia);}
    if(bucketA.size()<2){bucketA.push_back(*vazia);}
    if(bucketB.size()<1){bucketA.push_back(*vazia);}
    if(bucketB.size()<2){bucketA.push_back(*vazia);}

    numeroDePaginasJaAdicionadas = 0;
    iterador = bucketA.begin();
    while(iterador != bucketA.end()){
            if(numeroDePaginasJaAdicionadas<quantidadeDePaginasPorBucket){
                entradasDeDados->salvarPagina(*iterador, quantidadeDePaginasPorBucket*next + numeroDePaginasJaAdicionadas);
                numeroDePaginasJaAdicionadas++;
            }
            else{
                listaDeBuckets.at(next).adicionarPaginaDeOverflowAoBucket(entradasDeDados->adicionarPaginaOverflow(*iterador));

                quantidadeDePaginasPorBucket++;
            }

    }

    numeroDePaginasJaAdicionadas = 0;
    iterador = bucketB.begin();
    while(iterador != bucketB.end()){
            if(numeroDePaginasJaAdicionadas<quantidadeDePaginasPorBucket){
                entradasDeDados->salvarPagina(*iterador, quantidadeDePaginasPorBucket*(listaDeBuckets.size()-1) + numeroDePaginasJaAdicionadas);
                numeroDePaginasJaAdicionadas++;
            }
            else{
                listaDeBuckets.at(listaDeBuckets.size()-1).adicionarPaginaDeOverflowAoBucket(entradasDeDados->adicionarPaginaOverflow(*iterador));
                quantidadeDePaginasPorBucket++;
            }
    }


}


int Hash::hashChave(int k){
    int numeroDoBucket = k % ((2^level) * quantidadeDeBucketsInicial);
    if (numeroDoBucket < next) {
        numeroDoBucket = k%((2^(level+1)) * quantidadeDeBucketsInicial);
    }
    return numeroDoBucket;
}

int Hash::localizarChave(int chave){
    int numeroDoBucket = hashChave(chave);
    Bucket b = listaDeBuckets.at(numeroDoBucket);
    int ridDaChave = -1;
    int k, j;


    Pagina paginaSendoPercorrida;
    std::list<int>::iterator i;

    k = numeroDoBucket*quantidadeDePaginasPorBucket;
    j =0;
    while(j < this->quantidadeDePaginasPorBucket && ridDaChave == -1){
        paginaSendoPercorrida = entradasDeDados->carregarPagina(k);
        ridDaChave = paginaSendoPercorrida.buscarRidDaChaveNaPagina(chave);
        k++;
        j++;
    }

    i = b.getPaginasDeOverflow().begin();
    while( b.getPaginasDeOverflow().end()!=i  && ridDaChave == -1){
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
    int k,j;

    Pagina paginaSendoPercorrida;
    std::list<int>::iterator i;

    //Checa se o par existe nas paginas "normais"
    k = numeroDoBucket*quantidadeDePaginasPorBucket;
    j = 0;
    while(j < (this->quantidadeDePaginasPorBucket)){
        paginaSendoPercorrida = entradasDeDados->carregarPagina(k);
        if(paginaSendoPercorrida.checarSeExistePar(chave, rid)){
            return false;
        }
        k++;
        j++;
    }

    //Checa se o par existe nas paginas overflow
    i = b.getPaginasDeOverflow().begin();
    while(b.getPaginasDeOverflow().end()!=i){
        paginaSendoPercorrida = entradasDeDados->carregarPaginaOverflow(*i);
        if(paginaSendoPercorrida.checarSeExistePar(chave, rid)){
            return false;
        }
        i++;
    }

    //Tenta adicionar o par nas paginas "normais"
    k = numeroDoBucket*quantidadeDePaginasPorBucket;
    j = 0;
    while( j < (this->quantidadeDePaginasPorBucket) && !paginaFoiAdicionada){
        paginaSendoPercorrida = entradasDeDados->carregarPagina(k);
        paginaFoiAdicionada = paginaSendoPercorrida.adicionarParNaPagina(chave,rid);
        k++;
        j++;
    }

    //Tenta adicionar o par nas paginas overflow
    i = b.getPaginasDeOverflow().begin();
     while(b.getPaginasDeOverflow().end()!=i && !paginaFoiAdicionada){
        paginaSendoPercorrida = entradasDeDados->carregarPaginaOverflow(*i);
        paginaFoiAdicionada = paginaSendoPercorrida.adicionarParNaPagina(chave,rid);
        i++;
    }

    if(!paginaFoiAdicionada){
        Pagina *novaPagina = new Pagina();
        novaPagina->adicionarParNaPagina(chave,rid);
        entradasDeDados->adicionarPagina(*novaPagina);
        paginaFoiAdicionada = true;
        (this->quantidadeDeOverflow)++;
    }

    if(quantidadeDeOverflow > 0){
        redistribuir();
        (this->next)++;
        if (this->next > ((2^level) * quantidadeDeBucketsInicial)){
            this->next = 0;
            (this->level)++;
        }
    }
    return true;
}


bool Hash::excluirPar(int chave){
    int numeroDoBucket = hashChave(chave);
    Bucket b = listaDeBuckets.at(numeroDoBucket);
    bool exclusaoFeita = false;

    int k, j;

    Pagina paginaSendoPercorrida;
    std::list<int>::iterator i;

    k = numeroDoBucket*quantidadeDePaginasPorBucket;
    j = 0;
    //Checa se o par existe nas paginas "normais"
    while( j < this->quantidadeDePaginasPorBucket && !exclusaoFeita){
        paginaSendoPercorrida = entradasDeDados->carregarPagina(k);
        exclusaoFeita = paginaSendoPercorrida.excluirChaveDaPagina(chave);
        k++;
        j++;
    }

    //Checa se o par existe nas paginas overflow
    i = b.getPaginasDeOverflow().begin();
    while(b.getPaginasDeOverflow().end()!=i && !exclusaoFeita){
        paginaSendoPercorrida = entradasDeDados->carregarPaginaOverflow(*i);
        paginaSendoPercorrida.excluirChaveDaPagina(chave);
        i++;
    }

    return exclusaoFeita;
}



