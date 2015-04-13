class Hash{
    int level;
    int next;
    int quantidadeDeBucketsDoLevel;
    int temOverflow;
public:
    Hash();
    ~Hash();

    void loadHashInfo();
    void saveHashInfo();
    void redistribui();

    int hashChave(int k);
    int localizarChave(int k);
    int adicionarPar(int k);
    int excluirPar(int k);

};
