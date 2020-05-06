#define trigger 5 // dispenser ultrasonic
#define echo 4    // dispenser ultrasonic
#define levelTrigger 2 // level indicator ultrasonic 
#define levelEcho 3 // level indicator ultrasonic
#define Relay 6
#define buzzPin 7 // buzzer

float time=0,distance=0;
int lowLevel = 2;
 

void setup() {
 Serial.begin(9600);

 pinMode(trigger,OUTPUT);
 pinMode(echo,INPUT);
 pinMode(Relay,OUTPUT);

 delay(2000);
}

void loop()
{
 measure_distance();

 indicate_level();


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

 if(distance<5)
 {
   digitalWrite(Relay,HIGH);
 }
 else
 {
   digitalWrite(Relay,LOW);
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

 
  
  if(inches<=lowLevel){
   digitalWrite(buzzPin,HIGH);
   delay(1000);
   digitalWrite(buzzPin,LOW);
   delay(1000);}
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
