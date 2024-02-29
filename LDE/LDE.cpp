#include "LDE.h"

LDE::LDE() {
    primeiro = nullptr;
    ultimo = nullptr;
    size = 0;
}

LDE::~LDE() {
    No* aux = primeiro;
    while (aux != nullptr) {
        No* temp = aux;
        aux = aux -> prox;
        delete temp;
    }
}

void LDE::add(int valor) {
    No* novoNo = new No();
    novoNo -> dado = valor;
    novoNo -> prox = nullptr;
    novoNo -> ant = ultimo;

    if (ultimo != nullptr) {
        ultimo -> prox = novoNo;
    }

    ultimo = novoNo;

    if (primeiro == nullptr) {
        primeiro = ultimo;
    }

    size++;
}

No* LDE::get(int pos) {
    if(pos >= size) return nullptr;
    No *no_temp = primeiro;
    for (int i = 0; no_temp != nullptr && i != pos; i++) {
        no_temp = no_temp -> prox;
    }

    return no_temp;
}

void LDE:: setProx(int pos, No* proximo) {
  get(pos) -> prox = proximo;
}

void LDE:: setAnt(int pos, No* anterior) {
  get(pos) -> ant = anterior;
}

int LDE::getSize() {
    return size;
}

void LDE::clear() {
    primeiro = nullptr;
    ultimo = nullptr;
    size = 0;
}

No* LDE::getPrimeiro() {
    return primeiro;
}

No* LDE::getUltimo() {
    return ultimo;
}

void LDE::setPrimeiro(No *no) {
    primeiro = no;
}

void LDE::setUltimo(No *no) {
    no = ultimo;
}