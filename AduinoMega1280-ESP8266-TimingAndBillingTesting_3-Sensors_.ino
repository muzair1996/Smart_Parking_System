//#include <SoftwareSerial.h> //set Serial Communication (for sending Analog data) between Arduino (MEGA1280) and Node MCU (ESP8266)
#include <SharpIR.h>
//SoftwareSerial nodemcu(2,3); //2-Tx, 3-Rx

SharpIR sensor1( SharpIR::GP2Y0A41SK0F, A0 );
SharpIR sensor2( SharpIR::GP2Y0A41SK0F, A1 );
SharpIR sensor3( SharpIR::GP2Y0A41SK0F, A2 );

//int slot[4] = {0, 0, 0, 0};
//int Sensor[4]= {0, 0, 0, 0};

//String bitvector;
//String dist;
int slot1; //Parking Slot 1 (IR Sensor 1) connected with (Digital) PIN No.4 (Arduino)
int slot2;
int slot3;
int noSlot;

int dsensor1; //message from IR Sensor 1 (distance value from ".getDistance" Function)
int dsensor2;
int dsensor3;

unsigned long previousTime1 = 0, previousTime2 = 0, previousTime3 = 0;
byte seconds1, seconds2, seconds3;
byte minutes1, minutes2, minutes3;
byte hours1, hours2, hours3;
int pCost1, pMcost1, pH1cost1, pH2cost1;
int pCost2, pMcost2, pH1cost2, pH2cost2;
int pCost3, pMcost3, pH1cost3, pH2cost3;

//String cdata //complete message of all IR sensors
  
void setup() {  
  pinMode(A0, INPUT); //IR Sensor -> Analog Input PIN
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  
  pinMode(34, OUTPUT); //LED -> 0=Low, 1=High
  pinMode(36, OUTPUT);
  pinMode(38, OUTPUT);

  pinMode(35, OUTPUT); //Buzzer -> 0=Low, 1=High
  pinMode(37, OUTPUT);
  pinMode(39, OUTPUT);
  
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial.println("Initializing...");
  Serial1.println("Initializing...");
  }

 void buzzer()
  {
      dsensor1=sensor1.getDistance();
      dsensor2=sensor2.getDistance();
      dsensor3=sensor3.getDistance();
      if(dsensor1<=4){
      digitalWrite(35, HIGH); //turn ON Buzzer  
      }
      else
      {digitalWrite(35, LOW); //turn
      }

      if(dsensor2<=4){
      digitalWrite(37, HIGH); //turn ON Buzzer  
      }
      else
      {digitalWrite(37, LOW); //turn
      }

      if(dsensor3<=4)
      {
      digitalWrite(39, HIGH); //turn ON Buzzer  
      }
      else
      {
        digitalWrite(39, LOW); //turn
      }
  }
void billing1(){
  if (minutes1<1){
    if (seconds1<=30){
     pMcost1=0; 
    }
    else{
     pMcost1=20;
    }
   pCost1 = pMcost1;
  }
  if (minutes1>=1){
    if (seconds1<=30){
      pH1cost1=minutes1*50;
      pCost1 = pH1cost1; 
    }
    else{
      pH2cost1=(minutes1+1)*50;
      pCost1 = pH2cost1;
    }
  }
//    Serial.print("Parking1 cost: ");
//    Serial.print(pCost1);
//    Serial.println(" THB");
}
void billing2(){
  if (minutes2<1){
    if (seconds2<=30){
     pMcost2=0; 
    }
    else{
     pMcost2=20;
    }
   pCost2 = pMcost2;
  }
  if (minutes2>=1){
    if (seconds2<=30){
      pH1cost2=minutes2*50;
      pCost2 = pH1cost2; 
    }
    else{
      pH2cost2=(minutes2+1)*50;
      pCost2 = pH2cost2;
    }
  }
//    Serial.print("Parking2 cost: ");
//    Serial.print(pCost2);
//    Serial.println(" THB");
}
void billing3(){
  if (minutes3<1){
    if (seconds3<=30){
     pMcost3=0; 
    }
    else{
     pMcost3=20;
    }
   pCost3 = pMcost3;
  }
  if (minutes3>=1){
    if (seconds3<=30){
      pH1cost3=minutes3*50;
      pCost3 = pH1cost3; 
    }
    else{
      pH2cost3=(minutes3+1)*50;
      pCost3 = pH2cost3;
    }
  }
//    Serial.print("Parking3 cost: ");
//    Serial.print(pCost3);
//    Serial.println(" THB");
}

void loop(){
if (sensor1.getDistance()<=10){
    slot1=1;
    digitalWrite(34, HIGH); //enable HIGH on Input PIN
    if (millis() >= (previousTime1)) {
     previousTime1 = previousTime1 + 1000;  // use 100000 for uS
     seconds1 = seconds1 +1;
     if (seconds1 == 60){
        seconds1 = 0;
        minutes1 = minutes1 +1;
     }
     if (minutes1 == 60){
        minutes1 = 0;
        hours1 = hours1 +1;
     }
//     if (hours1 == 13){
//        hours1 = 1;
//     }
    }// end 1 second
  }
  else{
      slot1=0;
      digitalWrite(34, LOW); //enable LOW on Input PIN
      hours1=0;
      minutes1=0;
      seconds1=0;
  }
if (sensor2.getDistance()<=10){
    slot2=1;
    digitalWrite(36, HIGH); //enable HIGH on Input PIN
    if (millis() >= (previousTime2)) {
     previousTime2 = previousTime2 + 1000;  // use 100000 for uS
     seconds2 = seconds2 +1;
     if (seconds2 == 60){
        seconds2 = 0;
        minutes2 = minutes2 +1;
     }
     if (minutes2 == 60){
        minutes2 = 0;
        hours2 = hours2 +1;
     }
//     if (hours2 == 13){
//        hours2 = 1;
//     }
    }// end 1 second
  }
  else{
      slot2=0;
      digitalWrite(36, LOW); //enable LOW on Input PIN
      hours2=0;
      minutes2=0;
      seconds2=0;
  }
  if (sensor3.getDistance()<=10){
    slot3=1;
    digitalWrite(38, HIGH); //enable HIGH on Input PIN
    if (millis() >= (previousTime3)) {
     previousTime3 = previousTime3 + 1000;  // use 100000 for uS
     seconds3 = seconds3 +1;
     if (seconds3 == 60){
        seconds3 = 0;
        minutes3 = minutes3 +1;
     }
     if (minutes3 == 60){
        minutes3 = 0;
        hours3 = hours3 +1;
     }
//     if (hours3 == 13){
//        hours3 = 1;
//     }
    }// end 1 second
  }
  else{
      slot3=0;
      digitalWrite(38, LOW); //enable LOW on Input PIN
      hours3=0;
      minutes3=0;
      seconds3=0;
  }
  buzzer();
  noSlot=slot1+slot2+slot3;
  Serial.println("slot status ");
//  Serial.println(slot1);
//use:  String cdata = String(slot1)+","+String(slot2)+","+String(slot3)+";"; //use "," as a delimeter
//  Serial.println(cdata);
//  Serial1.println(cdata); //serial communication (physical connection)
// Time Duration
  Serial.print("slot1 time duration ");  
  String duration1 = String(hours1)+" hr:"+String(minutes1)+" m:"+String(seconds1)+" s"; 
  Serial.println(duration1);
//  Serial1.println(duration1); //serial communication (physical connection)
  Serial.print("slot2 time duration "); 
  String duration2 = String(hours2)+" hr,"+String(minutes2)+" m,"+String(seconds2)+" s"+";"; 
  Serial.println(duration2);
//  Serial1.println(duration2); //serial communication (physical connection)
  Serial.print("slot3 time duration "); 
  String duration3 = String(hours3)+" hr,"+String(minutes3)+" m,"+String(seconds3)+" s"+";"; 
  Serial.println(duration3);
//  Serial1.println(duration3); //serial communication (physical connection)
  
// Billing  
  billing1(); 
  billing2(); 
  billing3();
//  Serial.print("Parking3 cost: ");
//  Serial.print(pCost3);
//  Serial.println(" THB");
//use:  Serial.println("Parking Billing: ");
//  String PBilling = "Slot1 "+String(pCost1)+" THB,"+"Slot2 "+String(pCost2)+" THB,"+"Slot3 "+String(pCost3)+" THB"+";";   
// use:  String PBilling = String(pCost1)+","+String(pCost2)+","+String(pCost3)+";";
//  Serial.println(PBilling);
//  Serial1.println(PBilling); //serial communication (physical connection)
//String cdata = String(noSlot)+","+String(slot1)+","+String(slot2)+","+String(slot3)+","+String(pCost1)+","+String(pCost2)+","+String(pCost3)+";"; //use "," as a delimeter
//String cdata = String(slot1)+","+String(slot2)+","+String(slot3)+","+String(pCost1)+","+String(pCost2)+","+String(pCost3)+","+String(duration1)+";"; //use "," as a delimeter
String cdata = String(slot1)+","+String(slot2)+","+String(slot3)+","+String(pCost1)+","+String(pCost2)+","+String(pCost3)+";"; //use "," as a delimeter
Serial.println(cdata);
Serial1.println(cdata); //serial communication (physical connection)
  delay (900); //200   
} //end loop
