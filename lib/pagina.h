#define TAMANHO_DO_ARRAY_DE_CONTROLE 5
#define TAMANHO_DO_ARRAY_DE_PARES 5


typedef struct Par_{
    int chave;
    int rid;
} Par;

class Pagina{
    int arrayDeControle [TAMANHO_DO_ARRAY_DE_CONTROLE];
    Par arrayDosPares [TAMANHO_DO_ARRAY_DE_PARES];

};

