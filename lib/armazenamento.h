class Armazenamento{
    int numeroDePaginas; //Interessante para ter algum controle sobre a qtd durante a execu��o
public:
    int adicionarPagina();
    int exluirPagina();
    Pagina carregarPagina(int pagId);
    int salvarPagina(Pagina p);
};
