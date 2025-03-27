#include <RHReliableDatagram.h>                      // biblioteca Radiohead reliableDatagram
#include <RH_ASK.h>                                  // biblioteca Radiohead ASK
#include <SPI.h>                                     // biblioteca SPI
#include <Keypad.h>          

#define TX_ADDRESS 1                                 // endereço do transmissor
#define RX_ADDRESS 2                                 // endereço do receptor

const int pinoVibracao = 9;
uint8_t count = 0;                                   // contador
uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];                 // buffer da mensagem
uint8_t tamanho;                                     // tamanho da mensagem
uint8_t from;                                        // endereço de quem transmite

bool busline_conhecida = false;
int     busline_temp_pos = 0;
uint8_t busline_temp[4+1];           //variável de armazenamento intermediário
uint8_t busline[4+1];                                //4 é quantidade max de digitos da varial e 1 /0
RH_ASK driver;                                       // instância RH ASK
RHReliableDatagram gerente(driver, RX_ADDRESS);      // configurando o gerenciador

const byte ROWS = 4;            //4 linhas
const byte COLS = 3;                                //3 colunas
char keys[ROWS][COLS] = {
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'},
    {'*','0','#'}
};

byte rowPins[ROWS] = {10,8,7,6};                 //pinos das linhas
byte colPins[COLS] = {5,2,3};                    //pinos das colunas

char key;

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup()
{
  pinMode(pinoVibracao, OUTPUT);                     // Configura o pino como saída
  Serial.begin(9600);                                // inicializa console serial 9600 bps
  if (!gerente.init())                               // se a inicialização do gerenciador falhar
    Serial.println("Falha na inicializacao");        // print na console serial
  keypad.addEventListener(keypadEvent);              // adiciona evento
}

void loop()
{
  key = keypad.getKey();
  if (gerente.available())                           // se gerenciador estiver ativo
  {
    tamanho = sizeof(buf);                           // determina o tamanho do buffer
    if (gerente.recvfromAck(buf, &tamanho, &from))   // se o gerenciador receber mensagem
    {
      Serial.print("Recebido de: 0x");               // print na console serial
      Serial.print(from, HEX);                       // print do endereço do transmissor em Hexadecimal
      Serial.print(": ");                            // print na console serial
      Serial.println((char*)buf);                    // print da mensagem recebida

      if (strcmp((char*)buf, (char*)busline) == 0) {
        // Ativa o pino de vibração
        digitalWrite(pinoVibracao, HIGH);
        delay(1000);                                 // Ativa por 1 segundo
        digitalWrite(pinoVibracao, LOW);
        }
      }
      
    }
    if (busline_conhecida == true){
      Serial.print("envio periodico");
      gerente.sendtoWait(busline, sizeof(busline), TX_ADDRESS);
    delay(1000);
    }
  }
 
 // cuidando dos eventos
void keypadEvent(KeypadEvent key){
    if (keypad.getState() == PRESSED){
        if (key == '#') {                           //Apagar
    busline[0] = '0';
    busline[1] = '0';
    busline[2] = '0';
    busline[3] = '0';
    busline[4] = '\0';
    busline_temp_pos = 0 ;
    busline_conhecida = false;
    Serial.print("Apagar");
        }
        else if (key == '*') {                       //Enviar e quando envia apaga
            strcpy((char*)busline, (char*)busline_temp);
    busline_temp[0] = '\0';        
    busline_temp_pos = 0 ;
    Serial.print("Enviar");  
        Serial.println((char*)busline);
//        Serial.println((char*)busline_temp);
        busline_conhecida =true;
        }
  else {
    Serial.println(key);
    if (busline_temp_pos > 4) {
      digitalWrite(pinoVibracao, HIGH);
      delay(1000);                       // Ativa por 1 segundo
      digitalWrite(pinoVibracao, LOW);
    }
    else {
      busline_temp[busline_temp_pos++] = key;
      busline_temp[busline_temp_pos] = '\0'; 
      }
  }

    }
}
