# Código para Acesso à EEPROM

[Este código](https://github.com/fabioqueiroz1415/ESP8266/blob/main/algoritmo.ino) é um exemplo de como utilizar a biblioteca EEPROM em um microcontrolador Arduino para armazenar e manipular dados na memória EEPROM.

## Funcionalidades

O programa oferece as seguintes funcionalidades:

1. Preencher duas listas de 10 valores cada.
2. Mesclar as duas listas em uma lista única de 20 valores.
3. Salvar a lista mesclada na memória EEPROM.
4. Carregar a lista mesclada da memória EEPROM.
5. Limpar a lista mesclada da memória EEPROM.

## Como Utilizar

1. Conecte o Arduino ao computador.
2. Abra a porta serial a uma taxa de 9600 baud.
3. Siga as instruções exibidas no menu principal para escolher uma opção.
4. Insira os valores conforme solicitado para preencher as listas.
5. Execute as operações desejadas, como mesclar listas, salvar na EEPROM ou carregar da EEPROM.
6. Confirme as operações e acompanhe as mensagens na porta serial para obter feedback.

## Observações

- Este código foi desenvolvido para ser utilizado com um Arduino e requer a biblioteca EEPROM.
- Certifique-se de ajustar as configurações de comunicação serial, se necessário.
- Cuidado ao executar a operação de limpeza da memória, pois ela irá apagar todos os dados armazenados na EEPROM.

Divirta-se experimentando e explorando as capacidades de armazenamento da memória EEPROM do seu Arduino!
