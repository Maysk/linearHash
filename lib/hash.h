#define NOME_PADRAO "hashInfo.maysk"


class Hash{
    Armazenamento *entradasDeDados;
    std::vector<Bucket> listaDeBuckets;
    int quantidadeDeBucketsInicial;     //Quantidade inicial de buckets no level
    int quantidadeDePaginasPorBucket;
    int level;
    int next;
    int quantidadeDeOverflow;

public:
    Hash();
    ~Hash();

    void adicionarNovoBucket();

    Hash loadHashInfo();
    void saveHashInfo();
    void redistribuir();

    int hashChave(int k);
    int localizarChave(int k);
    bool adicionarPar(int chave, int rid);
    bool excluirPar(int k);


};
