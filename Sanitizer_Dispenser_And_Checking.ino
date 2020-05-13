#define trigger 5 // dispenser ultrasonic
#define echo 4    // dispenser ultrasonic
#define levelTrigger 2 // level indicator ultrasonic 
#define levelEcho 3 // level indicator ultrasonic
#define Relay 6
#define buzzPin 7 // buzzer

float time=0,distance=0;
int lowLevel = 9;
bool stopTime;

void setup() {
 stopTime = false;
 Serial.begin(9600);

 pinMode(trigger,OUTPUT);
 pinMode(echo,INPUT);
 pinMode(Relay,OUTPUT);
 pinMode(buzzPin,OUTPUT);
 pinMode(levelTrigger,OUTPUT);
 pinMode(levelEcho,INPUT);

 delay(2000);
}

void loop()
{
indicate_level(); 
measure_distance();
 

 


}


void measure_distance()
{
 digitalWrite(trigger,LOW);
 delayMicroseconds(2);
 digitalWrite(trigger,HIGH);
 delayMicroseconds(10);
 digitalWrite(trigger,LOW);
 delayMicroseconds(2);
 time=pulseIn(echo,HIGH);
 
 distance=time*200/20000;

 if(distance<15 && stopTime == true)
 {
   digitalWrite(Relay,HIGH);
   delay (3000);
   digitalWrite(Relay,LOW);
   Serial.print("looping");
   stopTime = false;
  }
 else
 {
   digitalWrite(Relay,LOW);
 }
 if(distance>15 && stopTime == false){
  stopTime = true;
   Serial.print("bool change");
 }

 delay(500);
}

void indicate_level()
{
  long duration, inches, cm;



  pinMode(levelTrigger, OUTPUT);
  digitalWrite(levelTrigger, LOW);
  delayMicroseconds(2);
  digitalWrite(levelTrigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(levelTrigger, LOW);
  pinMode(levelEcho, INPUT);
  duration = pulseIn(levelEcho, HIGH);
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  Serial.print(inches);
  Serial.print("in");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  delay(100);

 
  
  if(inches>=lowLevel){
   digitalWrite(buzzPin,HIGH);
   }
   else{
    digitalWrite(buzzPin,LOW);
   }

}

 long microsecondsToInches( long microseconds )
{
 return microseconds / 74 / 2;
}

long microsecondsToCentimeters( long microseconds )
{
 return microseconds / 29 / 2;
}
