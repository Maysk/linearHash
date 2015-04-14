class Bucket{
    std::list<int> numeroDasPaginas;
public:
    void adicionarPaginaAoBucket();
    void excluirPaginaDoBucket();
    std::list<int> getNumeroDasPaginas();
};
