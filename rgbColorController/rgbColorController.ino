const int xPin = A0;
const int yPin = A1;
const int sPin = 2;

const int redLED = 7;
const int greenLED = 4;
const int blueLED = 8;

const int redRGB = 5;
const int greenRGB = 6;
const int blueRGB = 9;

int redComponent = 0;
int greenComponent = 0;
int blueComponent = 0;

bool isRed = true;
bool isGreen = false;
bool isBlue = false;

int x;
int y;
int s;

int dt = 200;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(sPin, INPUT_PULLUP); // pulls pin up to high by default

  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);

  pinMode(redRGB, OUTPUT);
  pinMode(blueRGB, OUTPUT);
  pinMode(greenRGB, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

  x = analogRead(xPin);
  y = analogRead(yPin);
  s = digitalRead(sPin);

  delay(dt);

  Serial.print("X Value = ");
  Serial.print(x);
  Serial.print(", ");
  Serial.print("Y Value = ");
  Serial.print(y);
  Serial.print(", ");
  Serial.print("Switch state is ");
  Serial.println(s);

  checkComponent();
  if(s == 0) switchComponent();

  if(s == 1){
    setComponent();
  }
  
}

void checkComponent() {
  if(isRed == true) {
    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, LOW);
    digitalWrite(blueLED, LOW);
  }
  if(isGreen == true) {
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, HIGH);
    digitalWrite(blueLED, LOW);
  }
  if(isBlue == true){
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, LOW);
    digitalWrite(blueLED, HIGH);
  }

  
}

void switchComponent() {
  if(x>523){
    if(isRed == true){
      isRed = false;
      isGreen = true;
      isBlue = false;
    }

    else if(isGreen == true){
      isRed = false;
      isGreen = false;
      isBlue = true;
    }

    else{
      isRed = true;
      isGreen = false;
      isBlue = false;
    }
  }

  else{

    if(isRed == true){
      isRed = false;
      isGreen = false;
      isBlue = true;
    }

    else if(isGreen == true){
      isRed = true;
      isGreen = false;
      isBlue = false;
    }

    else{
      isRed = false;
      isGreen = true;
      isBlue = false;
    }
  }
} 

void setComponent() {
  if(y < 450){
    if(isRed == true){
      redComponent += 1;
      redComponent = constrain(redComponent, 0, 255);
    }

    else if(isGreen == true){
      greenComponent += 1;
      greenComponent = constrain(greenComponent, 0, 255);
    }

    else{
      blueComponent += 1;
      blueComponent = constrain(blueComponent, 0, 255);
    }
  }

  else if(y > 550){
    if(isRed == true){
      redComponent -= 1;
      redComponent = constrain(redComponent, 0, 255);
    }

    else if(isGreen == true){
      greenComponent -= 1;
      greenComponent = constrain(greenComponent, 0, 255);
    }

    else{
      blueComponent -= 1;
      blueComponent = constrain(blueComponent, 0, 255);
    }
  }

  analogWrite(redRGB, redComponent);
  analogWrite(greenRGB, greenComponent);
  analogWrite(blueRGB, blueComponent);
  
  delay(10);

  

  
}
