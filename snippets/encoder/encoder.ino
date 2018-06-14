// This is just a code snippet, provided in case it helps you.
// My setup: This encoder has pin C (middle pin of the three on one side) and 
// one of the pair on the other side connected to ground.  The other pins are 
// connected as follows to my Arduino Mega:
//      'A': digital pin 22
//      'B': digital pin 24
//      'press': digital pin 26
// In "real" code, you'd want a state machine to keep track of the rotation,
// and only take note of the "forward" or "back" when the encoder is reporting
// 0 again.

enum enDigitalPins
{
  dpInEncoderA=3,
  dpInEncoderB=4,
  dpInEncoderPress=2,
};


static void _ResetPins()
{
  // Rotary encoder input lines
  // Configure as input, turn on pullup resistors
  pinMode(dpInEncoderA, INPUT_PULLUP);
  //digitalWrite(dpInEncoderA, HIGH);
  pinMode(dpInEncoderB, INPUT_PULLUP);
  //digitalWrite(dpInEncoderB, HIGH);
  pinMode(dpInEncoderPress, INPUT_PULLUP);
  //digitalWrite(dpInEncoderPress, HIGH);

  attachInterrupt(digitalPinToInterrupt(dpInEncoderA), ISR_A, CHANGE);
  attachInterrupt(digitalPinToInterrupt(dpInEncoderPress), ISR_PRESS, CHANGE);
}
volatile uint8_t value;
void ISR_A()
{
  value = digitalRead(dpInEncoderB) * 2 + digitalRead(dpInEncoderA);
}

volatile bool press;
void ISR_PRESS()
{
  press = digitalRead(dpInEncoderPress);
}

/*void _lowlevel_ReadEncoder(int &rotate, int& press)
{
  rotate = (digitalRead(dpInEncoderB) * 2) + digitalRead(dpInEncoderA);
  //Serial.print("B: "); Serial.print(digitalRead(dpInEncoderB)); Serial.print("\tA: "); Serial.println(digitalRead(dpInEncoderA));
  press = digitalRead(dpInEncoderPress);
}*/


void ReadEncoder() {
  //Serial.print(value); Serial.print("\t"); Serial.println(press);
  static uint8_t lastVal = 3;
  if (lastVal == 1) {/* turns left */ 
    if (value == 2) { /* a tick to the left is detected */
      Serial.println("DOWN");
    } else if (value == 0 || value == 3) {
      Serial.println("UP");
    }
  } else if (lastVal == 3) { /* turns right */
    if (value == 0) { /* a tick to the right is detected */
      Serial.println("UP");
    } else if (value == 2 || value == 1) {
      Serial.println("DOWN");
    }
  }
  if (press == 0) {
    Serial.println("CENTER");
  } else {
    //Serial.println("-");
  }
  lastVal = value;
}


void setup()
{
  // configure the pins
  _ResetPins();

  // init serial communication
  Serial.begin(9600); 
  Serial.println("Ready to begin");
}


void loop()
{
  ReadEncoder();
}

