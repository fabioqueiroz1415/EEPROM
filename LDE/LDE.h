// Definição da estrutura do nó da lista
struct No {
    int dado;
    No* prox;
    No* ant;
};

class LDE {
private:
    No* primeiro;
    No* ultimo;

public:
    int size;
    
    LDE();
    ~LDE();

    // Método para adicionar um elemento no final da lista
    void add(int valor);

    // Método para obter o valor em uma posição específica da lista
    No* get(int pos);

    void setProx(int pos, No* proximo);
    void setAnt(int pos, No* anterior);

    // Método para obter o tamanho da lista
    int getSize();

    void clear();

    No *getPrimeiro();

    No *getUltimo();

    void setPrimeiro(No* no);

    void setUltimo(No* no);
};
