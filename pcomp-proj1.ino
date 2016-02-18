const byte POT = A0;
const byte LDR = A1;
const byte RED_OUT = 9;
const byte GREEN_OUT = 10;
const byte BLUE_OUT = 11;

#define DEBUG

unsigned long previous = 0;

struct Color {
  int r;
  int g;
  int b;
};

void setup() {
  // put your setup code here, to run once:
  pinMode(POT, INPUT);
  pinMode(LDR, INPUT);
  pinMode(RED_OUT, OUTPUT);
  pinMode(GREEN_OUT, OUTPUT);
  pinMode(BLUE_OUT, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int potVal = analogRead(POT);
  int ldrVal = analogRead(LDR);
  int interval = getRate(potVal);
  Color color = getColor(ldrVal);
  blink(interval, color);
  #ifdef DEBUG
  output(interval, color);
  #endif
  delay(1);
}

int getRate(int potVal) {
  //placeholder
  return potVal;
}

Color getColor(int ldrVal) {
  int val = map(ldrVal, 0, 1023, 0, 510);

  if (val >= 0 && val <= 255) {
    return (Color) { 255 - val, val, 0 };
  } else if (val >= 255 && val <= 510) {
    return (Color) { 0, 255 - val, 255 - (255 - val) };
  }
}

void blink(int rate, Color color) {
  unsigned long current = millis();
  
  if (current - previous >= rate) {
    previous = current;
    analogWrite(RED_OUT, color.r);
    analogWrite(GREEN_OUT, color.g);
    analogWrite(BLUE_OUT, color.b);
  } else {
    analogWrite(RED_OUT, 0);
    analogWrite(GREEN_OUT, 0);
    analogWrite(BLUE_OUT, 0);
  }
}

void output(int interval, Color color) {
  Serial.print(interval);
  Serial.print("\t");
  Serial.print(color.r);
  Serial.print(",");
  Serial.print(color.g);
  Serial.print(",");
  Serial.println(color.b);
}

