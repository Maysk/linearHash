#include "../lib/imports.h"


Pagina::Pagina(){ //construtor

	for(int i = 0; i < ARRAY_DE_CONTROLE; i++){
		this->arrayDeControle[i] = 0;
	}

	for(int i = 0; i < ARRAY_DE_PARES; i ++){
		this->arrayDosPares[i].chave = -1;
		this->arrayDosPares[i].rid = -1;
	}

}

//Metodos mais ligados ao array de controle
void Pagina::setPreenchido(int posicao){

	this->arrayDeControle[posicao] = 1;

}

void Pagina::setVazio(int posicao){

	this->arrayDeControle[posicao] = 0;

}


bool Pagina::isPosicaoVazia(int posicao){

	if (this->arrayDeControle[posicao] == 0){
		return true;
	}
	else{
		return false;
	}


}
bool Pagina::temPosicaoVazia(){

	for (int i = 0;i < ARRAY_DE_CONTROLE; i++){

		if(this->arrayDeControle[i] == 0){
			return true; //se acha alguma posicao do vetor de controle igual a 0, returna que tem posicao vazia
		}

	}

	return false;

}

//Metodos mais ligados ao array de pares
int Pagina::buscarChaveNaPagina(int chave){ // retorna o slot onde está a chave caso ela exista; caso contrario retorna -1

	int posicao = -1;

	for (int i = 0; i < ARRAY_DE_PARES; i++){

		if (     !(this->isPosicaoVazia(i))     ){ //se a posicao nao for vazio, comparar valores
			if (this->arrayDosPares[i].chave == chave ){

				posicao = i;

			}
		}
	}
	return posicao;


}// retorna o slot onde está a chave caso ela exista; caso contrario retorna -1

int Pagina::buscarRidDaChaveNaPagina(int chave){

	int posicao = this->buscarChaveNaPagina(chave);

	if (posicao == -1){
		return -1;
	}
	else{
		return this->arrayDosPares[posicao].rid;

	}

}

bool Pagina::adicionarParNaPagina(int chave, int rid){

	if (!this->temPosicaoVazia()){ //se nao ha posicao pra inserir, retorna falso
        //cout<<"Nao e possivel adicionar o par <"<<chave<<","<<rid<<"> pois a pagina esta cheia."<<endl;
		return false;
	}


	else{

        if (this->checarSeExistePar(chave,rid)){ //mais uma garantia
            //cout<<"Nao e possivel adicionar o par <"<<chave<<","<<rid<<"> pois a chave ou o rid ja existe(m)"<<endl;
            return false;
        }

		int primeiraPosicaoVazia = 0;
		while (!(this->isPosicaoVazia(primeiraPosicaoVazia))){ //enquanto a posicao nao for vazia, incrementa.
			primeiraPosicaoVazia++;

		}

		this->setPreenchido(primeiraPosicaoVazia); //indica no vetor de controle que a posicao eh preenchida
		this->arrayDosPares[primeiraPosicaoVazia].chave = chave; //insere a chave
		this->arrayDosPares[primeiraPosicaoVazia].rid = rid; //insere o rid

        //cout<<"Par <"<<chave<<","<<rid<<"> adicionado na pagina na posicao "<<primeiraPosicaoVazia<<"."<<endl;
		return true;
	}

}


bool Pagina::excluirChaveDaPagina(int chave){

    int posicaoChave = this->buscarChaveNaPagina(chave);
    if (posicaoChave == -1){
        //cout<<"Chave "<<chave<<" nao existe na pagina."<<endl;
        return false;
    }
    else{
            this->setVazio(posicaoChave);
            //cout<<"Chave "<<chave<<" excluida com sucesso da pagina."<<endl;
            return true;
    }



}

bool Pagina::checarSeExistePar(int chave, int rid){


    for(int i = 0; i < ARRAY_DE_PARES;i++){

        if (this->arrayDeControle[i] == 1){

            if (      (this->arrayDosPares[i].rid == rid) || (this->arrayDosPares[i].chave == chave)     ){
                return true;
            }

        }
    }


    return false;

}

void Pagina::show(){

    for(int i = 0; i < ARRAY_DE_CONTROLE; i++){
            if (this->arrayDeControle[i] == 1){
                cout<<"A posicao "<<i<<" contem o par <"<<this->arrayDosPares[i].chave<<","<<this->arrayDosPares[i].rid<<">."<<endl;

            }
            else{
                cout<<"A posicao "<<i<<" esta vazia."<<endl;
                 //  cout<<"A posicao "<<i<<" contem o par <"<<this->arrayDosPares[i].chave<<","<<this->arrayDosPares[i].rid<<">."<<endl;

            }
    }

}
