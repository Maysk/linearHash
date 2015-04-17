#include <stdio.h>
using namespace std;

#define NOME_ARQUIVO_ENTRADAS_DE_DADOS "entradasDeDados.luke"
#define NOME_ARQUIVO_OVERFLOW "overflow.luke"


class Armazenamento{
	int numeroDePaginasDados; //Interessante para ter algum controle sobre a qtd durante a execucao
	int numeroDePaginasOverflow;
	FILE* entradaDeDados;
	FILE* overflow;

public:
	Armazenamento(string entradaDeDados, string overflow); //Contrutor que recebe como parametro o nome do arquivo de entrada de dados e o nome do arquivo de overflow
	~Armazenamento();
	int adicionarPagina(Pagina p); //adiciona pagina de dados no armazenamento e retorna pagID
	int adicionarPaginaOverflow(Pagina p); //adicionar pagina de overflow no armazenamento e retorna pagID
	void exluirPagina(int pagID); //exclui uma pagina do arquivo
    Pagina carregarPagina(int pagId); //Pegar uma pagina do arquivo de dados e coloca na memoria
	Pagina carregarPaginaOverflow(int pagID); //Pegar uma pagina do arquivo de overflow e coloca na memoria
    void salvarPagina(Pagina p, int pagID); //Salva alteracoes feitas em uma pagina, a entrada e o id da pagina e a pagina com alteracoes

};
