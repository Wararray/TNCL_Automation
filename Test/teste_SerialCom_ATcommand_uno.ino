/* Comments and explanation done by Brandon Dias at First Integrated Command of Air Defense and Air Traffic - Defense Department
 * Contact: dias.unb@gmail.com
 */
#include <SoftwareSerial.h>

#define RX 13
#define TX 12

int     countTrueCommand;
int     countTimeCommand; 
int     valSensor = 1;
boolean found = false; 

SoftwareSerial esp8266(RX,TX); 
   
void setup() {
    Serial.begin(9600);
    esp8266.begin(115200);
    sendCommand("AT",5,"OK");
}

void loop() {
    sendCommand("",1,"");
    sendCommand("AT",5,"OK");
    delay(1000);                // Important to program don't get stuck 
}

void sendCommand(String command, int maxTime, char readReplay[]) {
  
    Serial.print(countTrueCommand);
    Serial.print(". at command => ");
    Serial.print(command);
    Serial.print(" ");
    
    while(countTimeCommand < (maxTime*1))  {
        esp8266.println(command);                      //command = AT
  //      Serial.print("Dentro do While");

        if(esp8266.find(readReplay)){                  //Searching for "OK"
  //      Serial.print("Preso no Esp?");
            found = true;
            break;
        }  
        countTimeCommand++;
    }
    
    if(found == true){
        Serial.println("Done");
        countTrueCommand++;
        countTimeCommand = 0;
    }    
    if(found == false){
        Serial.println("Fail");
        countTrueCommand = 0;
        countTimeCommand = 0;
    }    
    found = false;
//    Serial.print("Final da Funcao\n");
}
