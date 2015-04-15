class Identificador{
    bool isOverflow;
    int numeroDaPagina;
    int numeroDoSlot;
public:
    Identificador(int nSlot, int nPagina, bool isOverflow);
    int getNumeroDaPagina();
    int getNumeroDoSlot();
    bool getIsOverflow();
};
