/* Author: Brandon Dias 
 * Developer at First Integrated Command of Air Defense and Air Traffic - Defense Department of Brazil
 * Control and Automation Engineering Student
 * Contact: dias.unb@gmail.com
 */
#include <SoftwareSerial.h>

#define RX 4                            //After some trial and error     
#define TX 5                            //Those are the two ports that worked

int     countValidResponse;             //Check How many commands returned valid with specific tag (usually "OK")
int     countTimeResponse;              //Something to ensure not wait forever 
boolean found = false;                  //A control flag

SoftwareSerial esp8266(RX,TX);          //Initialize the virtual port. Don't forget: Rx1 <---> Tx2
                                        //                                           Tx1 <---> Rx2
void setup() {
    Serial.begin(9600);                 //Monitoring activity from Serial Monitor at 9600 baud            
    esp8266.begin(115200);              //Start comunication with module. Usually fabricant rate: 115200 baud
    sendCommand("AT",5,"OK");           //First atempt to comunicate: Sending "AT" and waiting "OK" as response 
}

void loop() {
    sendCommand("",1,"");               //Ensure that this program is working
    delay(1000);                        //Some erros of comunication can be avoided just giving more time to things happen
    sendCommand("AT",5,"OK");           //Attempt to comunicate
    delay(2000);                        //Important to program don't get stuck; Same reason as before
}

//This function was taken (part of it) from some random forum and, unfurtunelly, there is no author descrived there.
void sendCommand(String command, int maxTime, char readReplay[]) {
  
    Serial.print(countValidResponse);
    Serial.print(". at command => ");
    Serial.print(command);
    Serial.print(" ");
    
    while(countTimeResponse < (maxTime*1))  {
        esp8266.println(command);                      //command = AT
        if(esp8266.find(readReplay)){                  //Searching for "OK"
            found = true;
            break;                                     //Remember to change this ugly thing
        }  
        countTimeResponse++;
    }
    
    if(found == true){
        Serial.println("Done");
        countValidResponse++;
        countTimeResponse = 0;
    }    
    if(found == false){
        Serial.println("Fail");
        countValidResponse = 0;
        countTimeResponse = 0;
    }    
    found = false;
}
