#include <RHReliableDatagram.h>                      // biblioteca Radiohead reliableDatagram
#include <RH_ASK.h>                                  // biblioteca Radiohead ASK
#include <SPI.h>                                     // biblioteca SPI

#define TX_ADDRESS 1                                 // endereço do transmissor
#define RX_ADDRESS 2                                 // endereço do recept

RH_ASK driver;                                       // instância RH ASK
RHReliableDatagram gerente(driver, TX_ADDRESS);      // configurando o gerenciador

const int pinoLED = 13;
uint8_t count = 1;                                   // contador
uint8_t data[] = "177";                             // mensagem a ser enviada
uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];                 // buffer da mensagem
uint8_t tamanho;                                     // tamanho da mensagem
uint8_t from;                                        // endereço de quem transmite

void setup()
{
  pinMode(pinoLED, OUTPUT);                     // Configura o pino como saída
  Serial.begin(9600);                                // inicializa console serial 9600 bps
  if (!gerente.init())                               // se a inicialização do gerenciador falhar
    Serial.println("Falha na inicializacao");        // print na console serial
}

void loop()
{

  if (gerente.available())                           // se gerenciador estiver ativo
  {
    tamanho = sizeof(buf);                           // determina o tamanho do buffer
    if (gerente.recvfromAck(buf, &tamanho, &from))   // se o gerenciador receber mensagem
    {
      Serial.print("Recebido de: 0x");               // print na console serial
      Serial.print(from, HEX);                       // print do endereço do transmissor em Hexadecimal
      Serial.print(": ");                            // print na console serial
      Serial.println((char*)buf);                    // print da mensagem recebida

      if (strcmp((char*)buf, (char*)data) == 0) {
        // Ativa o led'
        digitalWrite(pinoLED, HIGH);
        delay(1000);                                 // Ativa por 1 segundo
        digitalWrite(pinoLED, LOW);
        }
      }
      
    }
    else {
      Serial.print("Transmitindo mensagem n. ");                // print na console serial
      Serial.println(count);                                    // print do contador 
      if (!gerente.sendtoWait(data, sizeof(data), RX_ADDRESS))  // se gerenciador enviar mensagem 
      {
        count++;                                                // incrementa contador 
      }
      delay(1000);                                               // atraso 0,5 segundo

      }
}
