class Bucket{
    std::list<int> paginasDeOverflow;
public:
    Bucket();
    void adicionarPaginaDeOverflowAoBucket(int idDaPagina);
    void resetarListaDeOverflow();
    std::list<int> getPaginasDeOverflow();

};
