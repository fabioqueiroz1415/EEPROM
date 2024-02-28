// Biblioteca para acesso à EEPROM
#include <EEPROM.h>

/* 
 * Declaração de:
 * uma matriz 2x10 representando as duas listas de 10 valores cada;
 * uma lista com 20 posições para mesclar as duas.
 */
 
int lista[2][10], lista_mesclada[20];

// Função de setup
void setup() {
  // Inicializa a comunicação serial em 9600 baud
  Serial.begin(9600);

  // Inicializa a EEPROM com 512 bytes de tamanho
  EEPROM.begin(512);
}

// Função loop principal
void loop() {
  // Exibe o menu principal
  Serial.println("\n\n\tMENU PRINCIPAL\t");
  Serial.println("1 - Preencher Lista 1");
  Serial.println("2 - Preencher Lista 2");
  Serial.println("3 - Mesclar Listas");
  Serial.println("4 - Salvar Lista Mesclada");
  Serial.println("5 - Carregar Lista Mesclada");
  Serial.println("0 - Limpar Lista Mesclada da Memória");

  Serial.print("\nDigite uma opção: ");
  Serial.read(); // Limpa o buffer

  // Aguarda entrada do teclado
  while (!Serial.available());

  // Lê a opção do usuário e converte a entrada para inteiro
  int escolha = Serial.parseInt();

  // Switch para tratar as opções do menu
  switch (escolha) {
    case 1:
      // Preenche a lista 1
      Serial.println(" 1 - Preencher Lista 1");
      delay(800);
      preenche_lista(0);
      break;
    case 2:
      // Preenche a lista 2
      Serial.println(" 2 - Preencher Lista 2");
      delay(800);
      preenche_lista(1);
      break;
    case 3:
      // Mescla as duas listas
      Serial.println(" 3 - Mesclar Listas");
      delay(800);
      mescla_listas();
      break;
    case 4:
      // Salva a lista mesclada na EEPROM
      Serial.println(" 4 - Salvar Lista Mesclada");
      delay(800);
      salva_na_memoria();
      break;
    case 5:
      // Carrega a lista mesclada da EEPROM
      Serial.println(" 5 - Carregar Lista Mesclada");
      delay(800);
      le_da_memoria();
      break;
    case 0:
      // Limpa a lista mesclada da EEPROM
      Serial.println(" 0 - Limpar Lista Mesclada da Memória");
      delay(800);
      limpaMemoria();
      break;
    default:
      // Mensagem de erro para opção inválida
      Serial.print("Digite uma opção válida: ");
      delay(800);
      break;
  }
}

// Função para preencher uma das listas
void preenche_lista(int numero_lista) {
  Serial.read();

  // Pede os valores da lista ao usuário
  Serial.print("Valores da lista " + String(numero_lista + 1) + ", separados por espaço: ");
  while (!Serial.available());

  delay(200);
  Serial.println();

  // Lê os 10 valores da lista
  for (int i = 0; i < 10; i++) {
    lista[numero_lista][i] = Serial.parseInt();

    Serial.print("Inserindo valor: " + String(lista[numero_lista][i]) + "... (");
    Serial.print(((i + 1.0) / 10.0) * 100.0, 0);
    Serial.println("%)");
    delay(100);
  }

  delay(300);
  Serial.print("Valores inseridos na lista " + String(numero_lista + 1) + ".");
  delay(400);
}

// Função para mesclar as duas listas
void mescla_listas() {
  // Concatena as duas listas em "lista_mesclada"
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 10; j++) {
      lista_mesclada[i * 10 + j] = lista[i][j];
      Serial.println("Mesclando listas... (" + String(i * 10 + j + 1) + "/20)");
      delay(100);
    }
  }

  delay(300);
  Serial.print("Listas mescladas!");
  delay(400);
}

// Função para salvar a lista mesclada na EEPROM
void salva_na_memoria() {
  Serial.println("Mémoria:");
  Serial.print("\t");
  Serial.println("Valor:");

  // Escreve os valores da lista na EEPROM
  for (int endereco = 0; endereco < 20; endereco++) {
    int valor = lista_mesclada[endereco];
    EEPROM.write(endereco, valor);

    Serial.print(endereco);
    Serial.print("\t");
    Serial.print(valor);
    Serial.println();

    delay(100);
  }

  // Confirma a gravação na EEPROM
  if (EEPROM.commit()) {
    delay(300);
    Serial.print("Salvo na EEPROM com sucesso!");
    delay(400);
  } else {
    delay(300);
    Serial.print("ERRO! Não foi salvo na EEPROM.");
    delay(400);
  }
}

// Função para ler a lista mesclada da EEPROM
void le_da_memoria() {
  Serial.println("Endereço:");
  Serial.print("\t");
  Serial.println("Valor:");

  // Lê os valores da EEPROM e imprime na serial
  for (int endereco = 0; endereco < 20; endereco++) {
    byte valor = EEPROM.read(endereco);
    Serial.print(endereco);
    Serial.print("\t");
    Serial.print(valor, DEC);
    Serial.println();
    delay(100);
  }

  delay(300);
  Serial.println("Fim da leitura!");
  delay(400);
}

// Função para limpar a lista mesclada da EEPROM
void limpaMemoria() {
  // Escreve zero em todos os endereços da lista
  for (int endereco = 0; endereco < 20; endereco++) {
    EEPROM.write(endereco, 0);
    Serial.println("Limpando dados...(" + String(endereco + 1) + "/20)");
    delay(100);
  }

  // Confirma a limpeza da EEPROM
  if (EEPROM.commit()) {
    delay(300);
    Serial.println("Todos os dados foram limpos.");
    delay(400);
  } else {
    delay(300);
    Serial.println("Ocorreu um erro inesperado, tente novamente.");
    delay(400);
  }
}
