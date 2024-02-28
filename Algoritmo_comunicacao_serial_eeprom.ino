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

  pinMode(D1, OUTPUT);//1 laranja
  pinMode(D3, OUTPUT); //2 laranja
  pinMode(D6, OUTPUT); //1 verde
  pinMode(D8, OUTPUT); //2 verde

  carregar_led_da_memoria(D1);
  carregar_led_da_memoria(D3);
  carregar_led_da_memoria(D6);
  carregar_led_da_memoria(D8);
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
      preenche_lista(0, D8);
      break;
    case 2:
      // Preenche a lista 2
      Serial.println(" 2 - Preencher Lista 2");
      delay(800);
      preenche_lista(1, D6);
      break;
    case 3:
      // Mescla as duas listas
      Serial.println(" 3 - Mesclar Listas");
      delay(800);
      mescla_listas(D8, D6);
      break;
    case 4:
      // Salva a lista mesclada na EEPROM
      Serial.println(" 4 - Salvar Lista Mesclada");
      delay(800);
      salva_na_memoria(D3, D1);
      break;
    case 5:
      // Carrega a lista mesclada da EEPROM
      Serial.println(" 5 - Carregar Lista Mesclada");
      delay(800);
      le_da_memoria(D1);
      break;
    case 0:
      // Limpa a lista mesclada da EEPROM
      Serial.println(" 0 - Limpar Lista Mesclada da Memória");
      delay(800);
      limpa_memoria(D8, D6, D3, D1);
      break;
    default:
      // Mensagem de erro para opção inválida
      Serial.print("Digite uma opção válida: ");
      delay(800);
      break;
  }
}

// Função para preencher uma das listas
void preenche_lista(int numero_lista, uint8_t led) {
  acender_led(led);
  Serial.read();

  // Pede os valores da lista ao usuário
  
  Serial.print("Valores da lista " + String(numero_lista + 1) + ", separados por espaço: ");
  while (!Serial.available()) {
    delay(400);
    inverter_led(led);
    delay(400);
    inverter_led(led);
  }
  Serial.println();  

  char car;
  String str_num = "";
  int num;
  // Lê os 10 valores da lista
  for (int i = 0; i < 10; i++) {
    str_num = "";
    car = Serial.read();
    while(car != ' ' && car != '\n' && car != '\r') {
      str_num.concat(car);
      car = Serial.read();
    }
    if(str_num == "" || str_num == "\n" || str_num == "\r") {
      Serial.println("\nEntrada inválida!");
      while(Serial.available()) Serial.read();
      delay(800);
      apagar_led(led);
      salvar_led_na_memoria(led);
      return;
    }
    num = str_num.toInt();
    lista[numero_lista][i] = num;

    inverter_led(led);

    Serial.print("Inserindo valor: " + String(lista[numero_lista][i]) + "... (");
    Serial.print(((i + 1.0) / 10.0) * 100.0, 0);
    Serial.println("%)");

    delay(100);
    inverter_led(led);
    delay(100);

    //aguardar o proximo valor apenas até o penúltimo
    if(i < 9) {
      Serial.print("Aguardando o " + String(i + 2) + "º valor: ");
      while (!Serial.available()) {
        inverter_led(led);
        delay(400);
        inverter_led(led);
        delay(400);
      }
      Serial.println();
    }
  }
  salvar_led_na_memoria(led);

  while(Serial.available()) Serial.read();

  delay(300);
  Serial.print("Valores inseridos na lista " + String(numero_lista + 1) + ".");
  delay(400);
}

// Função para mesclar as duas listas
void mescla_listas(uint8_t led_lista1, uint8_t led_lista2) {

  // Concatena as duas listas em "lista_mesclada"
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 10; j++) {
      inverter_led(led_lista1);
      inverter_led(led_lista2);
      

      lista_mesclada[i * 10 + j] = lista[i][j];
      Serial.println("Mesclando listas... (" + String(i * 10 + j + 1) + "/20)");
      delay(100);
      inverter_led(led_lista1);
      inverter_led(led_lista2);
      delay(100);
    }
  }
  acender_led(led_lista1);
  acender_led(led_lista2);
  salvar_led_na_memoria(led_lista1);
  salvar_led_na_memoria(led_lista2);
  delay(300);
  Serial.print("Listas mescladas!");
  delay(400);
}

bool salvar_led_na_memoria(uint8_t led) {
  int endereco;
  uint8_t estado = digitalRead(led);
  switch(led) {
    case D1:
      endereco = 101;
      break;
    case D3:
      endereco = 102;
      break;
    case D6:
      endereco = 103;
      break;
    case D8:
      endereco = 104;
      break;
    default:
      endereco = 105;
      break;
  }
  EEPROM.write(endereco, estado);

  if(EEPROM.commit()) return true;
  else return false;
}

// Função para salvar a lista mesclada na EEPROM
void salva_na_memoria(uint8_t led, uint8_t led_delete) {
  Serial.println("Mémoria:");
  Serial.print("\t");
  Serial.println("Valor:");

  // Escreve os valores da lista na EEPROM
  for (int endereco = 0; endereco < 20; endereco++) {
    inverter_led(led);
    int valor = lista_mesclada[endereco];
    EEPROM.write(endereco, valor);

    Serial.print(endereco);
    Serial.print("\t");
    Serial.print(valor);
    Serial.println();

    delay(100);
    inverter_led(led);
    delay(100);
  }

  // Confirma a gravação na EEPROM
  if (EEPROM.commit()) {
    delay(300);
    Serial.print("Salvo na EEPROM com sucesso!");
    delay(400);
    acender_led(led);
    apagar_led(led_delete);
    salvar_led_na_memoria(led);
    salvar_led_na_memoria(led_delete);
  } else {
    delay(300);
    Serial.print("ERRO! Não foi salvo na EEPROM.");
    apagar_led(led);
    salvar_led_na_memoria(led);
    salvar_led_na_memoria(led_delete);
    delay(400);
  }
}

void carregar_led_da_memoria(uint8_t led) {
  int endereco;
  switch(led) {
    case D1:
      endereco = 101;
      break;
    case D3:
      endereco = 102;
      break;
    case D6:
      endereco = 103;
      break;
    case D8:
      endereco = 104;
      break;
    default:
      endereco = 105;
      break;
  }
  
  byte estado = EEPROM.read(endereco);
  digitalWrite(led, (int)estado);
}

// Função para ler a lista mesclada da EEPROM
void le_da_memoria(int8_t led) {
  Serial.println("Endereço:");
  Serial.print("\t");
  Serial.println("Valor:");

  // Lê os valores da EEPROM e imprime na serial
  for (int endereco = 0; endereco < 20; endereco++) {
    inverter_led(led);
    byte valor = EEPROM.read(endereco);
    Serial.print(endereco);
    Serial.print("\t");
    Serial.print(valor, DEC);
    Serial.println();
    delay(100);
    inverter_led(led);
    delay(100);
  }

  delay(300);
  Serial.println("Fim da leitura!");
  delay(400);
}

// Função para limpar a lista mesclada da EEPROM
void limpa_memoria(uint8_t led_lista1, uint8_t led_lista2, uint8_t led_salvo, uint8_t led_delete) {
  acender_led(led_lista1);
  acender_led(led_lista2);
  acender_led(led_salvo);
  // Escreve zero em todos os endereços da lista
  int endereco;
  for(int i = 0; i < 2; i ++) {
    for(int j = 0; j < 10; j ++) {
      endereco = i * 10 + j;
      apagar_led(led_delete);
      lista_mesclada[endereco] = 0;
      lista[i][j] = 0;
      EEPROM.write(endereco, 0);
      Serial.println("Limpando dados...(" + String(endereco + 1) + "/20)");
      if(endereco == 4) apagar_led(led_lista1);
      else if(endereco == 9) apagar_led(led_lista2);
      else if(endereco == 14) apagar_led(led_salvo);
      delay(100);
      for(int i = 0; i < 7; i ++) {
        inverter_led(led_delete);
        delay(100);
      }
    }
  }

  // Confirma a limpeza da EEPROM
  if (EEPROM.commit()) {
    delay(300);
    Serial.println("Todos os dados foram limpos.");
    acender_led(led_delete);
    salvar_led_na_memoria(led_lista1);
    salvar_led_na_memoria(led_lista2);
    salvar_led_na_memoria(led_salvo);
    salvar_led_na_memoria(led_delete);
    delay(400);
  } else {
    delay(300);
    Serial.println("Ocorreu um erro inesperado, tente novamente.");
    delay(400);
  }
}

void acender_led(uint8_t led) {
  digitalWrite(led, HIGH);
}

void apagar_led(uint8_t led) {
  digitalWrite(led, LOW);
}

void inverter_led(uint8_t led) {
  if(digitalRead(led) == 0) digitalWrite(led, HIGH);
  else digitalWrite(led, LOW);
}
