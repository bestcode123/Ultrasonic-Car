#define trig1 9
#define echo1 8
#define trig2 7
#define echo2 6
#define forwardl 5
#define backwardl 4
#define forwardr 3
#define backwardr 2

// TODO:
// 1. Continue with the movement functions:  IN PROGRESS

// Initial Variable Declaration:
long duration1, distance1, duration2, distance2;
long sens = 2;
char mode = 'S'; // D = Division*, S = Subtraction**
int todoa;

// Defining the movement functions
void forward() {
  digitalWrite(forwardl, HIGH);
  digitalWrite(forwardr, HIGH);
  digitalWrite(backwardl, LOW);
  digitalWrite(backwardr, LOW);
}

void turn(int lr) { // lr: 0 = left, 1 = right
  if(lr == 0) {
    // Forward Left:
    digitalWrite(forwardl, LOW);
    digitalWrite(forwardr, HIGH);
    digitalWrite(backwardl, HIGH);
    digitalWrite(backwardr, LOW);
  } else if(lr == 1) {
    digitalWrite(forwardl, HIGH);
    digitalWrite(forwardr, LOW);
    digitalWrite(backwardl, LOW);
    digitalWrite(backwardr, HIGH);
  } else {
    Serial.println("TURN VALUE INCORRECT, MUST BE OF INTEGER 0/1"); 
  }
}

void backward() {
  digitalWrite(forwardl, LOW);
  digitalWrite(forwardr, LOW);
  digitalWrite(backwardl, HIGH);
  digitalWrite(backwardr, HIGH);
}

void setup() 
{
  // Defining the motor pins as OUTPUTS:
  pinMode(forwardl, OUTPUT);
  pinMode(forwardr, OUTPUT);
  pinMode(backwardl, OUTPUT);
  pinMode(backwardr, OUTPUT); 

  // Defining the HC_SR04 Pins:
  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);

  // Initialising the serial interface (9600 baud rate)
  Serial.begin(9600);
}

void loop() 
{
  // Getting the ultrasound distances:
  // Timing the ultrasound pulses (1)
  digitalWrite(trig1, LOW);
  delayMicroseconds(2);
  digitalWrite(trig1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig1, LOW);
  // Calculating the distance in cm (1)
  duration1 = pulseIn(echo1, HIGH);
  distance1 = duration1 * 0.037 / 2;
  
  // Timing the ultrasound pulses (2)
  digitalWrite(trig2, LOW);
  delayMicroseconds(2);
  digitalWrite(trig2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig2, LOW);
  // Calculating the distance in cm (2)
  duration2 = pulseIn(echo2, HIGH);
  distance2 = duration2 * 0.037 / 2;
  
  
  // Logic to decide action:
  if(distance1 >= 5 && distance1 <= 100 && distance2 >= 5 && distance2 <= 100) {
    // Division Mode*
    if(mode == 'D') {
      if(distance1 > distance2) {
        if(distance1 / distance2 > sens) {
          Serial.println("A1");
        }
      } else if(distance1 < distance2) {
        if(distance2 / distance1 > sens) {
          Serial.println("B1");
        }
      }
    // Subtraction Mode**
    } else if(mode == 'S') {
      if(distance1 > distance2) {
        if(distance1 - distance2 > sens) {
          Serial.println("A2");
        }
      } else if(distance1 < distance2) {
        if(distance2 - distance1 > sens) {
          Serial.println("B2");
        }
      }
    }
  } else { forward(); }
  
  
  // L/R STAT Situation Handling logic:
  if(distance1 >= 5 && distance1 <= 100 && distance2 >= 5 && distance2 <= 100) {
    // Division Mode*
    if(distance1 >= 5 && distance1 <= 10 && distance2 >= 5 && distance2 <= 10) {
      turn(random(2));
    } 
  } else { forward(); }
  
}
