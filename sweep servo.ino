#define DECODE_NEC

#if !defined(RAW_BUFFER_LENGTH)
// Maximum length of raw duration buffer. Must be even. 100 supports up to 48 bit codings inclusive 1 start and
// 1 stop bit.
#define RAW_BUFFER_LENGTH 100                                                                                              \
// #define RAW_BUFFER_LENGTH  112    // MagiQuest requires 112 bytes.
#endif

#define EXCLUDE_UNIVERSAL_PROTOCOLS   // Saves up to 1000 bytes program space.
#define EXCLUDE_EXOTIC_PROTOCOLS      // saves around 650 bytes program space if all other protocols are active


# include <IRremote.hpp>

int ir_pin = 9; 
int servopin = 11;
IRrecv irrecv(ir_pin);
decode_results results;

int Position = 0;

void setup(){
  Serial.begin(115200); 
  delay(1000);
  irrecv.enableIRIn(); // Start the receiver
  
  IrReceiver.begin(ir_pin, ENABLE_LED_FEEDBACK);
  printActiveIRProtocols(&Serial);
  Serial.println(ir_pin);
  
  pinMode(ir_pin, INPUT_PULLUP); // IR Sensor pin INPUT
  pinMode(servopin, OUTPUT); // servo motor Pin Output
}

void loop(){
 if (IrReceiver.decode()) {
   	switch(IrReceiver.decodedIRData.command) {        
        case 0x10:	Serial.println("1");  // Button 1
        			rotation(0,180,1);
      				
          			break;
          
        case 0x11:  Serial.println("2"); // Button 2     				
                    reverse(180,0,1);
      				
                    break;
 
        default: IrReceiver.printIRResultShort(&Serial);
    } 
    delay(65);
    IrReceiver.resume(); // Receive the next value
  }
}

void rotation (int from, int to, int step) {
  for (int i = from; i <= to; i += step) {
    Position = i;
    
    int pulseWidth = map(Position, 0, 180, 500, 2500);

      digitalWrite(servopin, HIGH);
      delayMicroseconds(pulseWidth);
      digitalWrite(servopin, LOW);
    delay(25);
  }
}
void reverse(int from, int to, int step) {
  for (int i = from; i >= to; i -= step) {
    Position = i;
    int pulseWidth = map(Position, 0, 180, 500, 2500);
   
      digitalWrite(servopin, HIGH);
      delayMicroseconds(pulseWidth);
      digitalWrite(servopin, LOW);
    delay(25);
  }
}
// changing direction of servo takes time
