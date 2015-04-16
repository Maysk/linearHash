class Bucket{
    std::list<int> paginasDeOverflow;
public:
    Bucket();
    void adicionarPaginaDeOverflowAoBucket(int idDaPagina);
    std::list<int> getPaginasDeOverflow();

};
