#define ARRAY_DE_CONTROLE 10
#define ARRAY_DE_PARES 10


typedef struct Par_{
    int chave;
    int rid;
} Par;

class Pagina{
    int arrayDeControle [ARRAY_DE_CONTROLE];
    Par arrayDosPares [ARRAY_DE_PARES];
public:
    //Metodos mais ligados ao array de controle
    void setPreenchido(int posicao);
    void setVazio(int posicao);
    bool isPosicaoVazia();
    bool temPosicaoVazia();

    //Metodos mais ligados ao array de pares
    void buscarChaveNaPagina(int chave);
    bool adicionarParNaPagina(int chave, int rid);
    void excluirChaveDdPagina(int chave);

};

