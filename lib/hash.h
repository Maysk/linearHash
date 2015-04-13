class Hash{
    Armazenamento entradasDeDados;
    ListaDeBuckets listaDeBuckets;
    int level;
    int next;
    int quantidadeDeBucketsDoLevel;

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
