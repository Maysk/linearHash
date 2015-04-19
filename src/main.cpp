#include "../lib/imports.h"
int  main(){

    remove(NOME_ARQUIVO_ENTRADAS_DE_DADOS);
    remove(NOME_ARQUIVO_OVERFLOW);
    remove(NOME_PADRAO);

    Hash *obj = new Hash();
    obj->loadHashInfo();

    for(int i=0; i<161; i++ ){
        obj->adicionarPar(i,i);
    }

    //obj->excluirPar(82);
    obj->imprimeInformacoes();
    obj->saveHashInfo();
    //cout<<obj->quantidadeDeBucketsInicial<<"\n";     //Quantidade inicial de buckets no level
    //cout<<obj->quantidadeDePaginasPorBucket<<"\n";
    //cout<<obj->level<<"\n";
    //cout<<obj->next<<"\n";
    //cout<<obj->quantidadeDeOverflow<<"\n";
    //cout<<obj->listaDeBuckets.size()<<"\n";
    /*
    for(int i= 0;i<200;i++){
        int qtd = obj->quantidadeDeOverflow;
        obj->adicionarPar(i,i);
    }

    cout<<obj->localizarChave(1)<<endl;
    cout<<obj->localizarChave(5)<<endl;
    cout<<obj->excluirPar(1)<<endl;
    cout<<obj->localizarChave(1)<<endl;

    obj->excluirPar(0);
    obj->adicionarPar(80)
    obj->imprimeInformacoes();

    */





}
