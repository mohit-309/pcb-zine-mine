// stage 2 output 1
// Controlling LED intensity using PWM registers directly. (without using analogWrite/digitalWrite function) .

const int potPin = A0;  // Potentiometer connected to analog pin A0
const int ledPin = 9;   // LED connected to digital pin 9

void setup() {
  pinMode(ledPin, OUTPUT);
 
  //SET TIMER MODE
  TCCR1A |= (1<<WGM10)|(1<<WGM11);
  //TCCR1B 
  TCCR1B &= ~(1<<WGM13) & ~(1<<WGM12);;
  
  TCCR1A |= (1<<COM1A1);
  TCCR1A &= ~(1<<COM1A0); //PIN IN NON INVERTING MOD    

  OCR1A = 255;  // Set the TOP value for the counter (maximum value)
  Serial.begin(9600);
}

void loop() {
  int potValue = analogRead(potPin);  // Read the analog value from the potentiometer
  int brightness = map(potValue, 0, 1023, 0, 255);  // Map the potentiometer value to PWM range
  
  OCR1A = brightness;  // Set the duty cycle based on the potentiometer reading
  Serial.println(OCR1A);
  delay(10);  // Add a small delay for stability
}
