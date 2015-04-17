#include "../lib/imports.h"

#define NOME_ARQUIVO_ENTRADAS_DE_DADOS "entradasDeDados.luke"
#define NOME_ARQUIVO_OVERFLOW "overflow.luke"

Hash::Hash(){}
/*
Hash::Hash(int quantidadeDeBucketsInicial, int quantidadeDePaginasPorBucket){

    this->quantidadeDeBucketsInicial = quantidadeDeBucketsInicial;
    this->quantidadeDePaginasPorBucket = quantidadeDePaginasPorBucket;
    this->level = 0;
    this->next = 0;
    this->quantidadeDeOverflow = 0;
    this->entradasDeDados = new Armazenamento(NOME_ARQUIVO_ENTRADAS_DE_DADOS,NOME_ARQUIVO_OVERFLOW);
    for(int i = 0; i<4; i++){
            this->listaDeBuckets.push_back(*(new Bucket));
            this->entradasDeDados->adicionarPagina(*vazia);
            this->entradasDeDados->adicionarPagina(*vazia);
    }
}*/
Hash::~Hash(){}

void Hash::adicionarNovoBucket(){
    Bucket *b = new Bucket();
    listaDeBuckets.push_back(*b);
    Pagina *paginaVazia = new Pagina();
    entradasDeDados->adicionarPagina(*paginaVazia);
    entradasDeDados->adicionarPagina(*paginaVazia);

}

void Hash::loadHashInfo(){

    FILE *arquivo = fopen(NOME_PADRAO,"r+");
    Pagina *vazia = new Pagina();
    if(arquivo == NULL){

        arquivo = fopen(NOME_PADRAO,"w");
        fprintf(arquivo, "4\n");    //qtd buckets
        fprintf(arquivo, "2\n");    //qtd pagina por bucket
        fprintf(arquivo,"0\n");     //qtd de overflow
        fprintf(arquivo,"0\n");     //menorlevel
        fprintf(arquivo,"0\n");     //posicaoDoNext
        fprintf(arquivo,"B: f\n");
        fprintf(arquivo,"B: f\n");
        fprintf(arquivo,"B: f\n");
        fprintf(arquivo,"B: f\n");

        this->quantidadeDeBucketsInicial = 4;
        this->quantidadeDePaginasPorBucket = 2;
        this->level = 0;
        this->next = 0;
        this->quantidadeDeOverflow = 0;
        this->entradasDeDados = new Armazenamento(NOME_ARQUIVO_ENTRADAS_DE_DADOS,NOME_ARQUIVO_OVERFLOW);
        for(int i = 0; i<4; i++){
            this->listaDeBuckets.push_back(*(new Bucket));
            this->entradasDeDados->adicionarPagina(*vazia);
            this->entradasDeDados->adicionarPagina(*vazia);
        }


    }
    else{
        fscanf(arquivo, "%d", &(this->quantidadeDeBucketsInicial));
        fscanf(arquivo, "%d", &(this->quantidadeDePaginasPorBucket));
        fscanf(arquivo, "%d", &(this->quantidadeDeOverflow));
        fscanf(arquivo, "%d", &(this->level));
        fscanf(arquivo, "%d", &(this->next));

        char a;
        int pagId;


        for (int i = 0; i < (pow(2,this->level)*this->quantidadeDeBucketsInicial + this->next) ; i ++  ){
            fseek(arquivo,3,SEEK_CUR); //pular o "B: "
            pagId = -1;
            a = getc(arquivo);

            this->listaDeBuckets.push_back(*(new Bucket));
            while(a != 'f'){
                fseek(arquivo,-1,SEEK_CUR);
                fscanf(arquivo,"%d ",&pagId);

                //TODO: (SE pagId != -1) adicionar indice de pagina de overflow pagId ao bucket de indice i
                if(pagId!=-1){
                    this->listaDeBuckets.back().adicionarPaginaDeOverflowAoBucket(pagId);
                }

                a = getc(arquivo);
            }


        }



    }


}

void Hash::saveHashInfo(){



}


void Hash::redistribuir(){
    Par par;
    int divisor;
    int controle;
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
            divisor = pow(2,(level+1)) * quantidadeDeBucketsInicial;
            if( par.chave % divisor == next){
                paginaParaOBucketA->adicionarParNaPagina(par.chave, par.rid);
            }
            else{
                paginaParaOBucketB->adicionarParNaPagina(par.chave, par.rid);
            }

            if(!(paginaParaOBucketA->temPosicaoVazia())){
                bucketA.push_back(*paginaParaOBucketA);
                //delete paginaParaOBucketA;
                paginaParaOBucketA = new Pagina();
            }

            if(!(paginaParaOBucketB->temPosicaoVazia())){
                bucketB.push_back(*paginaParaOBucketB);
                //delete paginaParaOBucketB;
                paginaParaOBucketB = new Pagina();
            }

         }

    }
    std::list<int> listaDasPaginasDeOverflow = listaDeBuckets.at(next).getPaginasDeOverflow();
    listaDeBuckets.at(next).resetarPaginaDeOverflow();

    while(!(listaDasPaginasDeOverflow.empty())){
        paginaDeOverflow = listaDasPaginasDeOverflow.back();
        listaDasPaginasDeOverflow.pop_back();
        paginaSendoPercorrida = entradasDeDados->carregarPaginaOverflow(paginaDeOverflow);
        entradasDeDados->exluirPagina(paginaDeOverflow);
        for(int i=0; i<10;i++){
            controle = (paginaSendoPercorrida.arrayDeControle)[i];
            par = (paginaSendoPercorrida.arrayDosPares)[i];
            divisor = pow(2,(level+1)) * quantidadeDeBucketsInicial;
            if(controle && par.chave % divisor == next){
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

                quantidadeDeOverflow++;
            }
            iterador++;
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
                quantidadeDeOverflow++;
            }
            iterador++;
    }


}


int Hash::hashChave(int k){
    int divisor = pow(2,level) * quantidadeDeBucketsInicial;
    int numeroDoBucket = k % divisor;
    if (numeroDoBucket < next) {
        divisor = pow(2, level+1) * quantidadeDeBucketsInicial;
        numeroDoBucket = k % divisor;
    }
    return numeroDoBucket;
}

int Hash::localizarChave(int chave){
    int numeroDoBucket = hashChave(chave);
    Bucket b = listaDeBuckets.at(numeroDoBucket);
    int ridDaChave = -1;
    int k, j;


    Pagina paginaSendoPercorrida;
    std::list<int> listaDasPaginasDeOverflow = b.getPaginasDeOverflow();
    std::list<int>::iterator i;

    k = numeroDoBucket*quantidadeDePaginasPorBucket;
    j =0;
    while(j < this->quantidadeDePaginasPorBucket && ridDaChave == -1){
        paginaSendoPercorrida = entradasDeDados->carregarPagina(k);
        ridDaChave = paginaSendoPercorrida.buscarRidDaChaveNaPagina(chave);
        k++;
        j++;
    }

    i = listaDasPaginasDeOverflow.begin();
    while( listaDasPaginasDeOverflow.end()!=i  && ridDaChave == -1){
        paginaSendoPercorrida = entradasDeDados->carregarPaginaOverflow(*i);
        ridDaChave = paginaSendoPercorrida.buscarRidDaChaveNaPagina(chave);
        if(ridDaChave>=0){
            return ridDaChave;
        }
        i++;
    }



    return ridDaChave;

}




bool Hash::adicionarPar(int chave, int rid){
    int numeroDoBucket = hashChave(chave);
    Bucket b = listaDeBuckets.at(numeroDoBucket);
    bool paginaFoiAdicionada = false;
    int k, j;

    Pagina paginaSendoPercorrida;
    std::list<int> listaDasPaginasDeOverflow = b.getPaginasDeOverflow();
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
    i = listaDasPaginasDeOverflow.begin();
    while(i != listaDasPaginasDeOverflow.end()){
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
        if(paginaFoiAdicionada){
                entradasDeDados->salvarPagina(paginaSendoPercorrida,k);
        }
        k++;
        j++;
    }

    //Tenta adicionar o par nas paginas overflow
    i = listaDasPaginasDeOverflow.begin();
     while(listaDasPaginasDeOverflow.end()!=i && !paginaFoiAdicionada){
        paginaSendoPercorrida = entradasDeDados->carregarPaginaOverflow(*i);
        paginaFoiAdicionada = paginaSendoPercorrida.adicionarParNaPagina(chave,rid);
        if(paginaFoiAdicionada){
                entradasDeDados->salvarPaginaOverflow(paginaSendoPercorrida,k);
        }
        i++;
    }

    if(!paginaFoiAdicionada){
        Pagina *novaPagina = new Pagina();
        novaPagina->adicionarParNaPagina(chave,rid);
        b.adicionarPaginaDeOverflowAoBucket(entradasDeDados->adicionarPagina(*novaPagina));
        paginaFoiAdicionada = true;
        (this->quantidadeDeOverflow)++;
        entradasDeDados->adicionarPaginaOverflow(*novaPagina);
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
    std::list<int> listaDasPaginasDeOverflow = b.getPaginasDeOverflow();
    std::list<int>::iterator i;

    k = numeroDoBucket*quantidadeDePaginasPorBucket;
    j = 0;
    //Checa se o par existe nas paginas "normais"
    while( j < this->quantidadeDePaginasPorBucket && !exclusaoFeita){
        paginaSendoPercorrida = entradasDeDados->carregarPagina(k);
        exclusaoFeita = paginaSendoPercorrida.excluirChaveDaPagina(chave);
        if(exclusaoFeita){
                entradasDeDados->salvarPagina(paginaSendoPercorrida,k);}
        k++;
        j++;
    }

    //Checa se o par existe nas paginas overflow
    i = listaDasPaginasDeOverflow.begin();
    while(listaDasPaginasDeOverflow.end()!=i && !exclusaoFeita){
        paginaSendoPercorrida = entradasDeDados->carregarPaginaOverflow(*i);
        paginaSendoPercorrida.excluirChaveDaPagina(chave);
        if(exclusaoFeita){
                entradasDeDados->salvarPaginaOverflow(paginaSendoPercorrida,k);}
        i++;
    }

    return exclusaoFeita;
}



