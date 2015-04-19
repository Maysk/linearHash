#include "../lib/imports.h"

Armazenamento::Armazenamento(string entradaDeDados, string overflow){

	//ENTRADAS DE DADOS
	FILE *arqDados = fopen(entradaDeDados.c_str(),"rb+");
	int numPaginas = 0; //esta variavel sera usada caso nao existam os arquivos

	if (arqDados == NULL){ //checa se o arquivo existe
		cout<<"\nO arquivo de entrada de dados não existe e sera criado"<<endl;
		arqDados = fopen(entradaDeDados.c_str(),"wb+");
		fwrite(&numPaginas, sizeof(int),1,arqDados);
		//EDICAO COMECA AQUI
		//fclose(arqDados);
		//arqDados = fopen(entradaDeDados.c_str(),"rb+");
		//EDICAO ACABA AQUI
		this->numeroDePaginasDados = 0;
		this->entradaDeDados = arqDados;
	}
    else { //arquivo existe
        this->entradaDeDados = arqDados;
		cout<<"\nO arquivo de entrada de dados existe"<<endl;
        fread(&(this->numeroDePaginasDados),4,1,this->entradaDeDados);
        cout<<"Leu o arquivo de dados com "<<this->numeroDePaginasDados<<" paginas"<<endl<<endl;
	}

	//OVERFLOW:
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
		cout<<"Leu o arquivo de overflow com "<<this->numeroDePaginasOverflow<<" paginas"<<endl<<endl;

	}


}

Armazenamento::~Armazenamento(){

	fclose(this->entradaDeDados);
	fclose(this->overflow);

}

int Armazenamento::adicionarPagina(Pagina p){

	int numPags = this->numeroDePaginasDados;
	int pagIdReturned = 0;
	rewind(this->entradaDeDados); //Funcao apenas por garantia

	fseek(this->entradaDeDados,4, SEEK_SET); //pular os 4 primeiros bytes do inteiro que diz o numero de paginas

	//Chegar ate a posicao onde se deve colocar a pagina
	for (int pagId = 0; pagId < numPags; pagId++){
		fseek(this->entradaDeDados,128,SEEK_CUR); //pula de 128 em 128 bytes
		//pagIdReturned = pagId;
		pagIdReturned++;
	}

	//Escrever bytes do vetor de controle:
	for (int i = 0; i < ARRAY_DE_CONTROLE; i++){

		fwrite(&p.arrayDeControle[i],sizeof(int),1,this->entradaDeDados);


	}

	//Escrever bytes do vetor de pares:
	for (int i = 0; i < ARRAY_DE_PARES; i++){
		fwrite(&p.arrayDosPares[i].chave,sizeof(int),1,this->entradaDeDados);
		fwrite(&p.arrayDosPares[i].rid,sizeof(int),1,this->entradaDeDados);


	}

	//Preencher os 8 bytes que sobraram dos 128 com algum numero que nunca sera lido (algo como um caractere especial)

	fprintf(this->entradaDeDados,"fimpage|");

    this->numeroDePaginasDados = this->numeroDePaginasDados + 1;

    //Atualizar numero de paginas no arquivo:
    rewind(this->entradaDeDados);
    fwrite(&(this->numeroDePaginasDados),sizeof(int),1,this->entradaDeDados);

	return pagIdReturned; //Esta variavel vem do primeiro loop



}

int Armazenamento::adicionarPaginaOverflow(Pagina p){

	//Estrutura de uma pagina como sera gravada no arquivo overflow:
	// |indicadorLivre|bytesControle|bytesConteudo|4bytesLivres|

	int numPags = this->numeroDePaginasOverflow;
	int pagIdReturned;
	rewind(this->overflow); //Funcao apenas por garantia

	fseek(this->overflow,4, SEEK_SET); //pular os 4 primeiros bytes do inteiro que diz o numero de paginas

	//Chegar ate a posicao onde se deve colocar a pagina

	bool achouPaginaLivre = false;
	int indicadorVazio;
	int pagId = 0;
	int estaCheio = 1; //variavel trash

	while( (pagId < numPags) && (achouPaginaLivre == false) ){

		fread(&indicadorVazio,4,1,this->overflow);

		if (indicadorVazio == 0){ //se a pagina estiver vazia
			achouPaginaLivre = true;

		}
		else{ //se a pagina estiver cheia, testa a proxima pagina
			pagId++;
			fseek(this->overflow,124,SEEK_CUR);
		}
	}

	//Escrever bytes de indicacao de pagina livre

	if (achouPaginaLivre == true){ //se a pagina 0 ja existia e ficou livre
		fseek(this->overflow,-4,SEEK_CUR);
	}

	fwrite(&estaCheio,sizeof(int),1,this->overflow); //grava que agora aquela pagina estara cheia


	//Escrever bytes de controle:
	for (int i = 0; i < ARRAY_DE_CONTROLE; i++){
		//cout<<p.arrayDeControle[i]<<endl;
		fwrite(&p.arrayDeControle[i],sizeof(int),1,this->overflow);

	}

	//Escrever bytes do vetor de pares:
	for (int i = 0; i < ARRAY_DE_PARES; i++){
		fwrite(&(p.arrayDosPares[i].chave),sizeof(int),1,this->overflow);
		fwrite(&(p.arrayDosPares[i].rid),sizeof(int),1,this->overflow);
	}

	//Preencher os 4 bytes que sobraram dos 128 com algo que nunca sera lido (algo como um caractere especial)
	fprintf(this->overflow,"fimp");

	//Atualizar numero de paginas no arquivo, se ele nao achou nenhuma pagina livre:
	if (achouPaginaLivre == false){
		this->numeroDePaginasOverflow = this->numeroDePaginasOverflow + 1;
		rewind(this->overflow);
		fwrite(&(this->numeroDePaginasOverflow),sizeof(int),1,this->overflow);
	}


	return pagId; //Esta variavel vem do primeiro loop






}


void Armazenamento::exluirPagina(int pagId){

    rewind(this->overflow);

    fseek(this->overflow,4,SEEK_SET);

    fseek(this->overflow,(128*pagId),SEEK_CUR);

    int indicadorPaginaLivre = 0;

    fwrite(&indicadorPaginaLivre,sizeof(int),1,this->overflow);

}


Pagina Armazenamento::carregarPagina(int pagId){

    rewind(this->entradaDeDados);

    Pagina *p = new Pagina(); //variavel que vai armazenar a pagina lida

	fseek(this->entradaDeDados,4, SEEK_SET); //pula os 4 primeiros bytes

	fseek(this->entradaDeDados,(128*pagId),SEEK_CUR);

    int controle[ARRAY_DE_CONTROLE];
    int conteudo[2*ARRAY_DE_PARES];

    fread(&controle,4,(ARRAY_DE_CONTROLE),this->entradaDeDados);
    fread(&conteudo,4,(2*ARRAY_DE_PARES),this->entradaDeDados);

    for(int i = 0; i < ARRAY_DE_CONTROLE; i++){

        p->arrayDeControle[i] = controle[i];
        p->arrayDosPares[i].chave = conteudo[2*i];
        p->arrayDosPares[i].rid = conteudo[(2*i)+1];

    }

    return *p;

}

Pagina Armazenamento::carregarPaginaOverflow(int pagId){

	rewind(this->overflow);

	Pagina *p = new Pagina(); //variavel que vai armazenar a pagina lida

	fseek(this->overflow,4, SEEK_SET); //pula os 4 primeiros bytes do arquivo

	fseek(this->overflow,(128*pagId),SEEK_CUR); //coloca o cursor do arquivo na posicao da pagina

	fseek(this->overflow,4, SEEK_CUR); //pula os 4 primeiros bytes da pagina

        int controle[ARRAY_DE_CONTROLE];
        int conteudo[2*ARRAY_DE_PARES];

        fread(&controle,4,(ARRAY_DE_CONTROLE),this->overflow);
	fread(&conteudo,4,(2*ARRAY_DE_PARES),this->overflow);

	for(int i = 0; i < ARRAY_DE_CONTROLE; i++){

		p->arrayDeControle[i] = controle[i];
		p->arrayDosPares[i].chave = conteudo[2*i];
		p->arrayDosPares[i].rid = conteudo[(2*i)+1];

	}

	return *p;


}


void Armazenamento::salvarPagina(Pagina p, int pagId){

    rewind(this->entradaDeDados);

    fseek(this->entradaDeDados,4,SEEK_SET); //pula primeiros 4 bytes que indicam o numero de paginas

    fseek(this->entradaDeDados,(128*pagId),SEEK_CUR);


    //Sobrescrever bytes de controle:
    for (int i = 0; i < ARRAY_DE_CONTROLE; i++){

        fwrite(&(p.arrayDeControle[i]),sizeof(int),1,this->entradaDeDados);

    }

    //Sobrescrever bytes de conteudo:

    for (int i = 0;i < ARRAY_DE_PARES;i++){


        fwrite(&(p.arrayDosPares[i].chave),sizeof(int),1,this->entradaDeDados);
        fwrite(&(p.arrayDosPares[i].chave),sizeof(int),1,this->entradaDeDados);

    }


}

void Armazenamento::salvarPaginaOverflow(Pagina p, int pagId){

    rewind(this->overflow);

    fseek(this->overflow,4,SEEK_SET);

    fseek(this->overflow,(128*pagId),SEEK_CUR);

    fseek(this->overflow,4,SEEK_CUR);

    for (int i = 0; i < ARRAY_DE_CONTROLE; i++){

        fwrite(&(p.arrayDeControle[i]),sizeof(int),1,this->overflow);

    }

    for (int i = 0; i < ARRAY_DE_PARES; i++){

        fwrite(&(p.arrayDosPares[i].chave),sizeof(int),1,this->overflow);
        fwrite(&(p.arrayDosPares[i].chave),sizeof(int),1,this->overflow);

    }

}


