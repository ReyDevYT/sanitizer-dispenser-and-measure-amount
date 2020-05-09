#define trigger 5 // dispenser ultrasonic
#define echo 4    // dispenser ultrasonic
#define levelTrigger 2 // level indicator ultrasonic 
#define levelEcho 3 // level indicator ultrasonic
#define Relay 6
#define buzzPin 7 // buzzer

float time = 0, distance = 0;
int lowLevel = 8;  // distance of lower plane from indicator sensor
int handLevel = 15; // maximum hand limit from dispenser sensor
bool isOK;


void setup() {
    Serial.begin(9600);

    pinMode(trigger, OUTPUT);
    pinMode(echo, INPUT);
    pinMode(levelTrigger, OUTPUT);
    pinMode(levelEcho, INPUT);
    pinMode(Relay, OUTPUT);
    pinMode(buzzPin, OUTPUT);

    delay(2000);


}
void loop()
{
    long duration, inches, cm;

    indicate_level();

    if (isOK == true) {
        measure_distance();
    }
    else {
       
    }

}

void measure_distance()
{
    digitalWrite(trigger, LOW);
    delayMicroseconds(2);
    digitalWrite(trigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger, LOW);
    delayMicroseconds(2);
    time = pulseIn(echo, HIGH);

    distance = time * 200 / 20000;

    if (distance < handLevel)
    {
        digitalWrite(Relay, HIGH);
        delay (5000);
    }
    else
    {
        digitalWrite(Relay, LOW);
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



    if (inches < lowLevel) {
        isOK = false;
        digitalWrite(buzzPin, HIGH);
        delay(1000);
        digitalWrite(buzzPin, LOW);
        delay(1000);
    }
    else {
        isOK = true;
        digitalWrite(buzzPin, LOW);
        
    }

}

long microsecondsToInches(long microseconds)
{
    return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
    return microseconds / 29 / 2;
}
