
class Hash{
    Armazenamento *entradasDeDados;
    std::vector<Bucket> listaDeBuckets;
    int quantidadeDeBucketsDoLevel;
    int quantidadeDePaginasPorBucket;
    int level;
    int next;
    int quantidadeDeOverflow;

public:
    Hash();
    ~Hash();

    Hash loadHashInfo();
    void saveHashInfo();
    void redistribuir();

    int hashChave(int k);
    Identificador* localizarChave(int k);
    int adicionarPar(int k);
    int excluirPar(int k);

};
