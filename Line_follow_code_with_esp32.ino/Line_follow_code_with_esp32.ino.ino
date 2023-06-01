// Arduino Line Follower Robot Code

//Communication with ESP32 part
String pathvalue; 
String currentlocation = "";

#define in1 11 //Motor1  L293 Pin in1 
#define in2 10 //Motor1  L293 Pin in1 
#define in3 6 //Motor2  L293 Pin in1 
#define in4 5 //Motor2  L293 Pin in1 


const int pingPin = 2; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 4; // Echo Pin of Ultrasonic Sensor

int R_S = A5; //ir sensor Right
int L_S = A4; //ir sensor Left
int turn_counter = 0; //if turn_count inside turn180 function is 0; make it as 1

String decision;
int k=1;
int l=2;
void setup(){ 
  Serial.begin(9600);

  pinMode(R_S, INPUT); 
  pinMode(L_S, INPUT); 
  
  pinMode(in1, OUTPUT); 
  pinMode(in2, OUTPUT); 
  pinMode(in3, OUTPUT); 
  pinMode(in4, OUTPUT);  
  
  delay(1000);

}


void loop(){  
  if(pathvalue==""){
  while (!Serial.available()){}
  while (Serial.available())
 {
  pathvalue = Serial.readString();
//  Serial.println(pathvalue);
//  Serial.println(pathvalue[0]);
   }  
 }  
  decision=pathvalue;

  if((digitalRead(R_S) == 0)&&(digitalRead(L_S) == 0)){forward();}   //if Right Sensor and Left Sensor are at White color then it will call forword function
  
  if((digitalRead(R_S) == 1)&&(digitalRead(L_S) == 0)){turnRight();} //if Right Sensor is Black and Left Sensor is White then it will call turn Right function  
  
  if((digitalRead(R_S) == 0)&&(digitalRead(L_S) == 1)){turnLeft();}  //if Right Sensor is White and Left Sensor is Black then it will call turn Left function
  
  if((digitalRead(R_S) == 1)&&(digitalRead(L_S) == 1)){Stop();}      //if Right Sensor and Left Sensor are at Black color then it will call Stop function


  long duration, inches, cm;
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  cm = microsecondsToCentimeters(duration);
//  Serial.println(cm);

  if(cm<6){
    Serial.println("Obastacle Detected");
    turn180();
    } //if obstacle detected then make a U_Turn

  
}

  long microsecondsToCentimeters(long microseconds) {
     return microseconds / 29 / 2;
  }
  
void forward(){  //forword
digitalWrite(in1, HIGH); //Right Motor forword Pin 
digitalWrite(in2, LOW);  //Right Motor backword Pin 
digitalWrite(in3, LOW);  //Left Motor backword Pin 
digitalWrite(in4, HIGH); //Left Motor forword Pin 
}

void turnRight(){ //turnRight
digitalWrite(in1, LOW);  //Right Motor forword Pin 
digitalWrite(in2, HIGH); //Right Motor backword Pin  
digitalWrite(in3, LOW);  //Left Motor backword Pin 
digitalWrite(in4, HIGH); //Left Motor forword Pin 
}
void turnstrongright(){//turnRight
//Serial.println("inside right");
digitalWrite(in1, HIGH); //Right Motor forword Pin 
digitalWrite(in2, LOW);  //Right Motor backword Pin 
digitalWrite(in3, LOW); //Left Motor backword Pin 
digitalWrite(in4, HIGH);  //Left Motor forword Pin 
delay(2000);

while(digitalRead(R_S) != 1) {
  digitalWrite(in1, LOW);  //Right Motor forword Pin 
  digitalWrite(in2, HIGH); //Right Motor backword Pin  
  digitalWrite(in3, LOW);  //Left Motor backword Pin 
  digitalWrite(in4, HIGH); //Left Motor forword Pin
  }
  
while(digitalRead(L_S) != 1) {
  digitalWrite(in1, LOW);  //Right Motor forword Pin 
  digitalWrite(in2, HIGH); //Right Motor backword Pin  
  digitalWrite(in3, LOW);  //Left Motor backword Pin 
  digitalWrite(in4, HIGH); //Left Motor forword Pin
  }
digitalWrite(in1, HIGH); //Right Motor forword Pin 
digitalWrite(in2, LOW);  //Right Motor backword Pin 
digitalWrite(in3, HIGH); //Left Motor backword Pin 
digitalWrite(in4, LOW); //Left Motor forword Pin 
delay(500);
}

void turnLeft(){ //turnLeft
digitalWrite(in1, HIGH); //Right Motor forword Pin 
digitalWrite(in2, LOW);  //Right Motor backword Pin 
digitalWrite(in3, HIGH); //Left Motor backword Pin 
digitalWrite(in4, LOW);  //Left Motor forword Pin 

}
void turnstrongleft(){ //turnLeft
//Serial.println("inside left");
digitalWrite(in1, HIGH); //Right Motor forword Pin 
digitalWrite(in2, LOW);  //Right Motor backword Pin 
digitalWrite(in3, LOW); //Left Motor backword Pin 
digitalWrite(in4, HIGH);  //Left Motor forword Pin 
delay(2000);

while(digitalRead(L_S) != 1) {
  digitalWrite(in1, HIGH);  //Right Motor forword Pin 
  digitalWrite(in2, LOW); //Right Motor backword Pin  
  digitalWrite(in3, HIGH);  //Left Motor backword Pin 
  digitalWrite(in4, LOW); //Left Motor forword Pin
  }

while(digitalRead(R_S) != 1) {
  digitalWrite(in1, HIGH);  //Right Motor forword Pin 
  digitalWrite(in2, LOW); //Right Motor backword Pin  
  digitalWrite(in3, HIGH);  //Left Motor backword Pin 
  digitalWrite(in4, LOW); //Left Motor forword Pin
  }
digitalWrite(in1, LOW);  //Right Motor forword Pin 
digitalWrite(in2, HIGH); //Right Motor backword Pin  
digitalWrite(in3, LOW);  //Left Motor backword Pin 
digitalWrite(in4, HIGH); //Left Motor forword Pin 
delay(500);
}

void(*resetFunc)(void)=0;

void turn180(){
  while(digitalRead(R_S) != 1) {
  digitalWrite(in1, HIGH);  //Right Motor forword Pin 
  digitalWrite(in2, LOW); //Right Motor backword Pin  
  digitalWrite(in3, HIGH);  //Left Motor backword Pin 
  digitalWrite(in4, LOW); //Left Motor forword Pin
  }
  while(digitalRead(L_S) != 1) {
  digitalWrite(in1, HIGH);  //Right Motor forword Pin 
  digitalWrite(in2, LOW); //Right Motor backword Pin  
  digitalWrite(in3, HIGH);  //Left Motor backword Pin 
  digitalWrite(in4, LOW); //Left Motor forword Pin
  }
  while(digitalRead(R_S) != 1) {
  digitalWrite(in1, HIGH);  //Right Motor forword Pin 
  digitalWrite(in2, LOW); //Right Motor backword Pin  
  digitalWrite(in3, HIGH);  //Left Motor backword Pin 
  digitalWrite(in4, LOW); //Left Motor forword Pin
  }
  digitalWrite(in1, LOW);  //Right Motor forword Pin 
  digitalWrite(in2, HIGH); //Right Motor backword Pin  
  digitalWrite(in3, LOW);  //Left Motor backword Pin 
  digitalWrite(in4, HIGH); //Left Motor forword Pin  
  delay(500);  

  if(turn_counter==0){
    turn_counter = 1;    
  }
  else{
    turn_counter = 0;
  }
}

void Stop(){ //stop

//digitalWrite(in1, LOW); //Right Motor forword Pin 
//digitalWrite(in2, LOW); //Right Motor backword Pin 
//digitalWrite(in3, LOW); //Left Motor backword Pin 
//digitalWrite(in4, LOW); //Left Motor forword Pin 
//Serial.println("enter decision");
//Serial.println(decision[k]);
//decision = Serial.read();
//if (turn_counter==1){
//  forward();
//  delay(4000);
//  turn180();
//}
if (decision[k]=='s'){
  forward();
  delay(1500);
  k=k+1;
}
else if (decision[k]=='r'){
  turnstrongright();
  k=k+1;
}
else if (decision[k]=='l'){
  turnstrongleft();
  k=k+1;
}
else if (decision[k]=='"'){
  digitalWrite(in1, LOW); //Right Motor forword Pin 
  digitalWrite(in2, LOW); //Right Motor backword Pin 
  digitalWrite(in3, LOW); //Left Motor backword Pin 
  digitalWrite(in4, LOW); //Left Motor forword Pin 
  decision="";
  pathvalue="";
  resetFunc();
}
}
