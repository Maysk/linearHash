#include "../lib/imports.h"
int  main(){
    Hash *obj = new Hash();
    obj->loadHashInfo();
    for(int i=0; i<100; i++ ){
        obj->adicionarPar(i,i);
    }


}
