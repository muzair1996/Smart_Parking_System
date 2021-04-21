  #include <MicroGear.h> //NETPIE  
  #include <ESP8266WiFi.h>
  #include <SoftwareSerial.h> //Serial Communication
  #include <SimpleTimer.h> //set Timer in every xx time interval
  #include <DateTime.h>
//  #include <DateTimeStrings.h>

  // ----- Change following 6 config variables ---------------------

  const char* ssid     = "HUAWEI P30";       // WiFi ssid
  const char* password = "MeowMeow";   // WiFi password
  
  #define APPID   "iotworkshopuzair"              // use group AppID 
  #define KEY     "hDDEBwXQqLZN8HO"                // use group Key
  #define SECRET  "piNcMGXol0OZlxhj8P87WaBRn"             // use group Secret
  #define ALIAS   "workshop"  // your device name, ex. "A01"
  // -------------------------------------------------------------------
  #define LED01STATETOPIC "/led01state/" ALIAS  // topic for LED status
  #define LED02STATETOPIC "/led02state/" ALIAS  // topic for LED status
  #define LED03STATETOPIC "/led03state/" ALIAS  // topic for LED status

  #define FREESLOTSTOPIC "/freeslots/" ALIAS  // topic for no of avalivle slots

  #define LED01BILLINGTOPIC "/led01bill/" ALIAS  // topic for LED1 billing
  #define LED02BILLINGTOPIC "/led02bill/" ALIAS  // topic for LED2 billing
  #define LED03BILLINGTOPIC "/led03bill/" ALIAS  // topic for LED3 billing

  #define LED01TIMINGTOPIC "/led01time/" ALIAS  // topic for LED1 timing

  WiFiClient client;

  int timer = 0;
  String bitvector, test;

  int currentLED01State = 1;
  int currentLED02State = 1;
  int currentLED03State = 1;
  int nofreeslots;
  unsigned long started, finished, elapsed;

  
  int notify = 0;
  MicroGear microgear(client);

  String myString, myString2; // complete message from arduino (all sensors data)
  char rdata; // received charactors (slot status)
  int firstVal, secondVal,thirdVal; // sensors 
  int led1,led2,led3;
  int bill1,bill2,bill3;
  String t1;

/* If a new message arrives, do this */
void onMsghandler(char *topic, uint8_t* msg, unsigned int msglen) {
    Serial.print("Incoming message --> ");
    msg[msglen] = '\0';
    Serial.println((char *)msg);
}
void onFoundgear(char *attribute, uint8_t* msg, unsigned int msglen) {
    Serial.print("Found new member --> ");
    for (int i=0; i<msglen; i++)
        Serial.print((char)msg[i]);
    Serial.println();  
}
void onLostgear(char *attribute, uint8_t* msg, unsigned int msglen) {
    Serial.print("Lost member --> ");
    for (int i=0; i<msglen; i++)
        Serial.print((char)msg[i]);
    Serial.println();
}
/* When a microgear is connected, do this */
void onConnected(char *attribute, uint8_t* msg, unsigned int msglen) {
    Serial.println("Connected to NETPIE...");
    /* Set the alias of this microgear ALIAS */
    microgear.setAlias(ALIAS);
}
void setup() {
  
    /* Add Event listeners */
    Serial.begin(9600); //9600
    Serial.println("Starting...");
        
    /* Call onMsghandler() when new message arraives */
    microgear.on(MESSAGE,onMsghandler);

    /* Call onFoundgear() when new gear appear */
    microgear.on(PRESENT,onFoundgear);

    /* Call onLostgear() when some gear goes offline */
    microgear.on(ABSENT,onLostgear);

    /* Call onConnected() when NETPIE connection is established */
    microgear.on(CONNECTED,onConnected);
   
    /* Initial WIFI, this is just a basic method to configure WIFI on ESP8266.                       */
    /* You may want to use other method that is more complicated, but provide better user experience */
    if (WiFi.begin(ssid, password)) {
        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print(".");
        }
    }
    Serial.println("WiFi connected");  
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    /* Initial with KEY, SECRET and also set the ALIAS here */
    microgear.init(KEY,SECRET,ALIAS);
    /* connect to NETPIE to a specific APPID */
    microgear.connect(APPID);  
}
void loop() {
    /* To check if the microgear is still connected */
    if (microgear.connected()) {
        //Serial.println("connected");
        /* Call this method regularly otherwise the connection may be lost */
        microgear.loop();
        if(Serial.available()){
           myString = Serial.readStringUntil(';'); //received data of slot status (each sensor)
                Serial.println(myString);
                String l = getValue(myString, ',', 0);
                String m = getValue(myString, ',', 1);
                String n = getValue(myString, ',', 2);
                led1 = l.toInt(); microgear.publish(LED01STATETOPIC, led1);
                led2 = m.toInt(); microgear.publish(LED02STATETOPIC, led2);
                led3 = n.toInt(); microgear.publish(LED03STATETOPIC, led3);
                String a = getValue(myString, ',', 3); 
                String b = getValue(myString, ',', 4);
                String c = getValue(myString, ',', 5); 
                bill1 = a.toInt(); microgear.publish(LED01BILLINGTOPIC, bill1);            
                bill2 = b.toInt(); microgear.publish(LED02BILLINGTOPIC, bill2);   
                bill3 = c.toInt(); microgear.publish(LED03BILLINGTOPIC, bill3); 
//                String t1 = getValue(myString, ',', 6); microgear.publish(LED01TIMINGTOPIC, t1);    
//          delay(2000);
//            delay(1000);
            if((led1==1)&&(led2==1)&&(led3==1)){
              if (notify==0){
              notify = 1;
              microgear.publish("/@push/owner","Parking Lot is FULL!");
//              microgear.publish("/@push/owner","Please use next Parking Lot");
              }
            }
            else notify = 0;
            delay(900);
        }
    }
    else {
        Serial.println("connection lost, reconnect...");
        if (timer >= 5000) { 
            microgear.connect(APPID);
            timer = 0;
        }
        else timer += 100;
    }
    delay(100);   
}

void updateslot()
 {
          microgear.publish(LED01STATETOPIC, led1);
          microgear.publish(LED02STATETOPIC, led2);
          microgear.publish(LED03STATETOPIC, led3);
 }
 void freeslots(){
  nofreeslots = 3-(led1+led2+led3);
  microgear.publish(FREESLOTSTOPIC, nofreeslots);
 }
 void updatebilling()
 {
          microgear.publish(LED01BILLINGTOPIC, bill1);
          microgear.publish(LED02BILLINGTOPIC, bill2);
          microgear.publish(LED03BILLINGTOPIC, bill3);
 }

String getValue(String data, char separator, int index){
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
