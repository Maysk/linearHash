class Bucket{
    std::list<int> numeroDasPaginas;
    std::list<int> paginasDeOverflow;
public:
    void adicionarPaginaAoBucket();
    void excluirPaginaDoBucket();
    std::list<int> getNumeroDasPaginas();
    std::list<int> getPaginasDeOverflow();

};
