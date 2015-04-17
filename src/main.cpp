#include "../lib/imports.h"
int  main(){
    Hash *obj = new Hash(4,2);
    for(int i=0;i<80;i++){
        obj->adicionarPar(i,i);
    }

    cout<<"\n\n\n\n Aqui: "<<obj->localizarChave(5);

}
