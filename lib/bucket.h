class Bucket{
    std::list<int> paginasDeOverflow;
public:
    Bucket();
    void adicionarPaginaDeOverflowAoBucket(int idDaPagina);
    void resetarPaginaDeOverflow();
    std::list<int> getPaginasDeOverflow();

};
