class Hash{
    Armazenamento entradasDeDados;
    std::vector<Bucket> listaDeBuckets;
    int quantidadeDeBucketsDoLevel;
    int quantidadeDePaginasPorBucket;
    int level;
    int next;

public:
    Hash();
    ~Hash();

    Hash loadHashInfo();
    void saveHashInfo();
    void redistribui();

    int hashChave(int k);
    int localizarChave(int k);
    int adicionarPar(int k);
    int excluirPar(int k);

};
