#include "../lib/imports.h"

Armazenamento::Armazenamento(string entradaDeDados, string overflow){

	FILE *arqDados = fopen(entradaDeDados.c_str(),"rb+");
	int numPaginas = 0; //esta variavel sera usada caso nao existam os arquivos

	if (arqDados == NULL){ //checa se o arquivo existe
		cout<<"O arquivo de entrada de dados não existe e sera criado"<<endl;
		arqDados = fopen(entradaDeDados.c_str(),"wb+");
		fwrite(&numPaginas, sizeof(int),1,arqDados);
		this->numeroDePaginasDados = 0;
		this->entradaDeDados = arqDados;
	}
    else { //arquivo existe
        this->entradaDeDados = arqDados;
		cout<<"O arquivo de entrada de dados existe"<<endl;
        fread(&(this->numeroDePaginasDados),4,1,this->entradaDeDados);
        cout<<"Leu o arquivo de dados com "<<this->numeroDePaginasDados<<" paginas"<<endl<<endl;
	}



	FILE *arqOverflow = fopen(overflow.c_str(),"rb+");

	if (arqOverflow == NULL){
		cout<<"O arquivo de dados de overflow não existe e sera criado"<<endl;
		arqOverflow = fopen(overflow.c_str(),"wb+");
		fwrite(&numPaginas, sizeof(int),1,arqOverflow);
		this->numeroDePaginasOverflow = 0;
		this->overflow = arqOverflow;

	}
	else { //arquivo existe
		this->overflow = arqOverflow;
		cout<<"O arquivo de dados de overflow existe"<<endl;
		fread(&(this->numeroDePaginasOverflow),4,1,this->overflow);
		cout<<"Leu o arquivo de overflow com "<<this->numeroDePaginasOverflow<<" paginas"<<endl;

	}


}

Armazenamento::~Armazenamento(){

	fclose(this->entradaDeDados);
	fclose(this->overflow);

}

int Armazenamento::adicionarPagina(Pagina p){

	int numPags = this->numeroDePaginasDados;
	int pagIdReturned;
	rewind(this->entradaDeDados); //Funcao apenas por garantia

	fseek(this->entradaDeDados,4, SEEK_SET); //pular os 4 primeiros bytes do inteiro que diz o numero de paginas

	//Chegar ate a posicao onde se deve colocar a pagina
	for (int pagId = 0; pagId < numPags; pagId++){
		fseek(this->entradaDeDados,128,SEEK_CUR); //pula de 128 em 128 bytes
		pagIdReturned = pagId;
	}

	//Escrever bytes do vetor de controle:
	for (int i = 0; i < ARRAY_DE_CONTROLE; i++){
		fwrite(&p.arrayDeControle[i],sizeof(int),1,this->entradaDeDados);
		//Alterar acima quando(se) tiver as funcoes get

	}

	//Escrever bytes do vetor de pares:
	for (int i = 0; i < ARRAY_DE_PARES; i++){
		fwrite(&p.arrayDosPares[i].chave,sizeof(int),1,this->entradaDeDados);
		fwrite(&p.arrayDosPares[i].rid,sizeof(int),1,this->entradaDeDados);

		//Alterar acima quando(se) tiver as funcoes get
	}

	//Preencher os 8 bytes que sobraram dos 128 com algum numero que nunca sera lido (algo como um caractere especial)
	int trash = -1;
	//fwrite(&trash,sizeof(int),1,this->entradaDeDados);
	//fwrite(&trash,sizeof(int),1,this->entradaDeDados);
	fprintf(this->entradaDeDados,"fimpage|");

    this->numeroDePaginasDados = this->numeroDePaginasDados + 1;

    //Atualizar numero de paginas no arquivo:
    rewind(this->entradaDeDados);
    fwrite(&(this->numeroDePaginasDados),sizeof(int),1,this->entradaDeDados);

	return pagIdReturned; //Esta variavel vem do primeiro loop



}

int Armazenamento::adicionarPaginaOverflow(Pagina p){



}


void Armazenamento::exluirPagina(int pagId){







}


Pagina Armazenamento::carregarPagina(int pagId){









}

Pagina carregarPaginaOverflow(int pagID){


}


void Armazenamento::salvarPagina(Pagina p, int pagId){








}
