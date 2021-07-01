
int PinMotorPot = 0;      // Motor Pot Connected to A0
int PinMAX_PWM = 1;   // Maximum PWM is controlled through a pot connected to A1 to limit power to motor
int PinPot = 0;      // Input Pot Connected to A1
int PinMotorPWM = 6;   // Motor PWM on D6
int PinMotorDir = 7;   // Motor Direction on D7
int PinDirection = 8;
int PinCentered = 13;

int MotorPotValue = 0;
int PotValueFixed = 0;
int PotValue = 0;
int MotorPotError = 0;
int MotorDriveValue = 0;

int PotMAX_PWM = 0;
int BasePWM = 5; // Where motor kicks in to remove large dead zone in accelerator.
int MinPWM = 80;  // PWM at minimum pot position.
int MaxPWM = 255; // This value will change with pot.

int ErrorClamp = 255;
int DeadZone = 2;
int EndStopLeft = 300;
int EndStopRight = 730;

int maximum = 550;
int minimum = 550;
int counter;

int ch1;
int ch2;
int interlocked;
int interlock_count;

 /*
  * Channel A
  * 1445-1465 - Center
  * 1210 - Full Brake
  * 1580 - Full Accelerator
  * 
  * Channel B
  * 1470-1490 - Center
  * 1820 - Fill Right
  * 1130 - Full Left
  * 
  * Channel C 
  * 1450-1480 - no signal
  * 1060-1080 - default C off
  * 1850-1870 - C ON
  * 
  */

void setup() {

  pinMode(2, INPUT); // RC Reciever C
  pinMode(3, INPUT); // RC Reciever Throttle

  pinMode(PinDirection, INPUT);
  pinMode(PinMotorPWM, OUTPUT);  // sets the pin as output
  pinMode(PinMotorDir, OUTPUT);  // sets the pin as output
  pinMode(PinCentered, OUTPUT);  // sets the pin as output
  Serial.begin(115200);
}

void loop() {
  ch1 = pulseIn(2, HIGH, 25000); // Read the pulse width of 
  ch2 = pulseIn(3, HIGH, 25000); // each channel

  PotMAX_PWM = analogRead(PinMAX_PWM);
  MaxPWM = map(PotMAX_PWM, 0, 1024, MinPWM, 255);
  
  PotValue = analogRead(PinPot);

/*
  if (ch1 > 1800) // Remote Disable.
    {
      interlocked = 1;
      digitalWrite(PinCentered, 1);
    }
  if ((ch1 > 1000) && (ch1 < 1800))
    {
      interlocked = 0;
      digitalWrite(PinCentered, 0);
    }
*/
 
  PotValueFixed = map(PotValue, EndStopLeft, EndStopRight, BasePWM, MaxPWM);
  if (PotValueFixed <= BasePWM)
    {
      PotValueFixed = 0;
    }
  PotValueFixed = constrain(PotValueFixed, 0, 255);

  analogWrite(PinMotorPWM, PotValueFixed);

  if (digitalRead(PinDirection) == 1)
    {
    digitalWrite(PinMotorDir,1);    
    }
  else
    {
    digitalWrite(PinMotorDir,0);    
    }

  if (PotValue < minimum)
    {
      minimum = PotValue;
    }

  if (PotValue > maximum)
    {
      maximum = PotValue;
    }
/*
  Serial.print("Channel C:");
  Serial.println(ch1);
  Serial.print("Channel T:");
  Serial.println(ch2);

  Serial.print("accel:");
  Serial.println(PotValueFixed);
*/
 

/*
  MotorPotValue = analogRead(PinMotorPot);

  if ((MotorPotValue >= 510) && (MotorPotValue <= 514))
    {
    digitalWrite(PinCentered, 1);
    }
  else
    {
    digitalWrite(PinCentered, 0);
    }
  PotValueFixed = PotValue;
  if (PotValue > EndStopRight) PotValueFixed = EndStopRight;
  if (PotValue < EndStopLeft) PotValueFixed = EndStopLeft;

  MotorPotError = MotorPotValue - PotValueFixed;

  MotorDriveValue = abs(MotorPotError);
  
  if (MotorDriveValue > ErrorClamp)
    {
      MotorDriveValue = ErrorClamp;
    }
  if (MotorPotError > 0)
    {
      digitalWrite(PinMotorDir, 0);
    }
   else
    {
      digitalWrite(PinMotorDir, 1);
    }

  if (MotorDriveValue >= DeadZone)
    {
    analogWrite(PinMotorPWM, MotorDriveValue);
    }
  else
    {
    analogWrite(PinMotorPWM, 0);
    }

  */    
  
/*  
  Serial.print(PotValue);
  Serial.print("\t");
  Serial.print(PotValueFixed);
  Serial.print("\t");
  Serial.print(minimum);
  Serial.print("\t");
  Serial.println(maximum);
*/

/*  
  Serial.print(PotValueFixed);
  Serial.print("\t");
  Serial.print(MotorPotValue);
  Serial.print("\t");
  Serial.print(MotorPotError);
  Serial.print("\t");
  Serial.println(MotorDriveValue);
*/
}
