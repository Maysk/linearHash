#define ARRAY_DE_CONTROLE 10
#define ARRAY_DE_PARES 10


typedef struct Par_{
    int chave;
    int rid;
} Par;

class Pagina{
    //int arrayDeControle [ARRAY_DE_CONTROLE];
    //Par arrayDosPares [ARRAY_DE_PARES];
public:

	//Atributos:
    int arrayDeControle [ARRAY_DE_CONTROLE];
    Par arrayDosPares [ARRAY_DE_PARES];

    Pagina(); //construtor
    //Metodos mais ligados ao array de controle
    void setPreenchido(int posicao);
    void setVazio(int posicao);
    bool isPosicaoVazia(int posicao);
    bool temPosicaoVazia();

    //Metodos mais ligados ao array de pares

    int buscarChaveNaPagina(int chave);// retorna o slot onde está a chave caso ela exista; caso contrario retorna -1
    int buscarRidDaChaveNaPagina(int chave); //retorna o rid da chave caso ela existe, caso contrario retorna -1
    bool adicionarParNaPagina(int chave, int rid);
    bool excluirChaveDaPagina(int chave);
    bool checarSeExistePar(int chave, int rid); //Verifica tanto se ja existe a chave, quanto se ja existe o rid na Pagina

    void show();

};

