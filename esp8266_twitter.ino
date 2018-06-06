/*      TWITTER ESP8266
 *      
 * Author: Arthur R Aragão
 * 
 */


//LIRARIES:

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

//BOTÕES:

const int botao = 0;  //pino do botão utilizado -- button pin


//VARIAVEIS GLOBAIS:

int botaoestado = 0;
String comando = "Event_Name";
String key = "IFTT webhooks key";

ESP8266WiFiMulti wifiMulti;


void setup() {
    pinMode(LED_BUILTIN, OUTPUT);      //inicia o led como output -- initialize led as output


    Serial.begin(115200);             //inicializa comunicação serial --start serial port
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
    wifiMulti.addAP("ssid_of_AP_1", "password_AP_1");
    wifiMulti.addAP("ssid_of_AP_2", "password_AP_2");
    wifiMulti.addAP("ssid_of_AP_3", "password_AP_3");
    wifiMulti.addAP("ssid_of_AP_4", "password_AP_4");
    wifiMulti.addAP("ssid_of_AP_5", "password_AP_5");
    wifiMulti.addAP("ssid_of_AP_6", "password_AP_6");


    wificonectar();

   
    
}

void loop() {

    botaoestado = digitalRead(botao);

    if(botaoestado == LOW){          //o botão tem um resistor pullup integrado -- the button has a integrated pullup resistor
      Serial.println("button pressed");
      Serial.println("");
      Serial.println("");
      httpget(comando);
      delay(1000);
    }
    
  

}




//===========CONECT TO WIFI================

void wificonectar(){         
    digitalWrite(LED_BUILTIN,HIGH);
    Serial.println("trying to connect to wifi");
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
      Serial.println("WiFi conected");
      Serial.println("IP address: ");
      Serial.println(WiFi.localIP());
      Serial.println("");
      Serial.println("");
      Serial.println("everything done, waiting for button press");
      
    } else {
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.println("");
      Serial.println("WiFi not connected");
      Serial.println("");
      Serial.println("");
      Serial.println("reboot the board");
    }
    delay(1000);
    
}





//=============HTTP GET REQUEST================

void httpget(String mensagem){    //mandar um pedido get com uma mensagem -- send a get request with a message 
    
    HTTPClient http;
    digitalWrite(LED_BUILTIN,HIGH);
    Serial.println("");
    Serial.println("initializing http...");
    Serial.println("");

    //escolha a URL
    //choose a URL
    http.begin("http://maker.ifttt.com/trigger/" + mensagem + "/with/key/"  +key); //HTTP

    Serial.println("making http request");
    Serial.println("");

    //iniciar conexão e mandar header http
    //inicialize cconnection and send http header
    int httpCode = http.GET();

    //o número retorna negativo se ocorrer erro
    //the number returns negative in case of error
    if(httpCode > 0) {
      //o header http foi enviado e a resposta recebida
      //the header was sent and the messagee received
      Serial.printf("the request worked with code: %d\n", httpCode);
      Serial.println("");
      digitalWrite(LED_BUILTIN,LOW);
      if(httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        Serial.print("response: ");
        Serial.println(payload);
      }
      delay(1000);
    } else {
      Serial.printf("the request faailed wit error code: %s\n", http.errorToString(httpCode).c_str());
      digitalWrite(LED_BUILTIN,HIGH);   
      delay(1000); 
    }
    http.end();
    wificonectar();
    
}




