/*      TWITTER ESP8266
 *      
 * criado por: Arthur R Aragão
 * 
 */


//LIRARIES:

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

//BOTÕES:

const int botao = 0;  //pino do botão utilizado


//VARIAVEIS GLOBAIS:

int botaoestado = 0;
String comando = "botao_pressionado";
String key = "IFTT webhooks key";

ESP8266WiFiMulti wifiMulti;


void setup() {
    pinMode(LED_BUILTIN, OUTPUT);      //inicia o led como output


    Serial.begin(115200);             //inicializa comunicação serial
    delay(2000);
    Serial.println("");
    Serial.println("");
    Serial.println("########### starting program ###########");
    Serial.println("");
    delay(200);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(200);
    digitalWrite(LED_BUILTIN, LOW);
    delay(200);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(200);
    digitalWrite(LED_BUILTIN, LOW);
    delay(200);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(200);
    digitalWrite(LED_BUILTIN, LOW);
    delay(200);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(200);


    //REDES WIFI SALVAS:
    wifiMulti.addAP("ssid_do_PA_1", "senha_do_PA_1");
    wifiMulti.addAP("ssid_do_PA_2", "senha_do_PA_2");
    wifiMulti.addAP("ssid_do_PA_3", "senha_do_PA_3");
    wifiMulti.addAP("ssid_do_PA_4", "senha_do_PA_4");
    wifiMulti.addAP("ssid_do_PA_5", "senha_do_PA_5");
    wifiMulti.addAP("ssid_do_PA_6", "senha_do_PA_6");


    wificonectar();

   
    
}

void loop() {

    botaoestado = digitalRead(botao);

    if(botaoestado == LOW){          //o botão tem um resistor pullup integrado
      Serial.println("botão apertado");
      Serial.println("");
      Serial.println("");
      httpget(comando);
      delay(1000);
    }
    
  

}




//===========CONECTAR WIFI================

void wificonectar(){          //conctar-se a uma rede wifi
    digitalWrite(LED_BUILTIN,HIGH);
    Serial.println("tentando conectar-se ao wifi");
    WiFi.mode(WIFI_AP);
    delay(10);
    WiFi.mode(WIFI_STA);
    wifiMulti.run();
    
    int x = 0;
    while ((wifiMulti.run() != WL_CONNECTED) && (x < 20) ) {
        delay(500);
        Serial.print(".");
        x++;
    }

    if(wifiMulti.run() == WL_CONNECTED){
      digitalWrite(LED_BUILTIN, LOW);
      Serial.println("");
      Serial.println("WiFi conectado");
      Serial.println("endereço IP: ");
      Serial.println(WiFi.localIP());
      Serial.println("");
      Serial.println("");
      Serial.println("tudo pronto esperado botão");
      
    } else {
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.println("");
      Serial.println("WiFi não conectado");
      Serial.println("");
      Serial.println("");
      Serial.println("reinicie a placa");
    }
    delay(1000);
    
}





//=============HTTP GET REQUEST================

void httpget(String mensagem){    //mandar um pedido get com uma mensagem 
    
    HTTPClient http;
    digitalWrite(LED_BUILTIN,HIGH);
    Serial.println("");
    Serial.println("inicializando HTTP...");
    Serial.println("");

    //escolha a URL
    http.begin("http://maker.ifttt.com/trigger/" + mensagem + "/with/key/"  +key); //HTTP

    Serial.println("fazendo HTTP request");
    Serial.println("");

    //iniciar conexão e mandar header http
    int httpCode = http.GET();

    //o número retorna negativo se ocorrer erro
    if(httpCode > 0) {
      //o header http foi enviado e a resposta recebida
      Serial.printf("o pedido funciounou e retorno codigo: %d\n", httpCode);
      Serial.println("");
      digitalWrite(LED_BUILTIN,LOW);
      if(httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        Serial.print("resposta: ");
        Serial.println(payload);
      }
      delay(1000);
    } else {
      Serial.printf("o pedido falhou com codigo de erro: %s\n", http.errorToString(httpCode).c_str());
      digitalWrite(LED_BUILTIN,HIGH);   
      delay(1000); 
    }
    http.end();
    wificonectar();
    
}




