
// assigning pins:
// int pinName = pinVal -- outside of loops

// pinMode(pinName, INPUT/OUTPUT)
// declares what the pin is going to be used for -- in setup

// digitalWrite(pinName, VAL)
// used to apply a binary vlotage (HI/LO) to the pin -- in loop

// digitalRead(pin)
// same thing, but for boolean voltages input (1/0)-- in loop

// Serial.begin(9600)
// start the clock of the serial monitor to 9600 bps

// digitals are in the D-number pins
// analogues are in the A-number
// nodemcu only has A0 for analogue

// sensors usually have VCC, ground and output pins
// GND to GND, VCC to 3V3 or 1v8 or else, output goes to As or Ds
// NC pins -- no connect pins -- literally no conection

// DHT protocols -- DHT.h library
// one-wire protocol (i.e. humidity/temp sensors) -- similar to PWM
// MCU pulls low (18ms) to start, pulls high (20-40 microsecs) to prompt, DHT responds (80us) and pulls low, then high (80us) to send get-ready message
// pulls low 50 microsecs and transfers bits (each bit separated by 50 microsecs low)
// (low) smallPulse(=0) (low) largePulse(=1) (low) etc...
// 26-28 microsecs = 0, 70 microsecs = 1

// DHT dht(pin, DHTTYPE) -- to initialize dht protocol instance. DHTTYPE is the type (DHT11 or DHT22)

// dht.begin()
// initializes the DHT protocol
// dht.Methods() --> many static methods for DHT to read and write stuff from sensors
// example: dht.readHumidity() in a humidity sensor (float)

// ultrasonic sensors
// 4 pins: vcc, trigger, echo, gnd
// trigger and echo go in D-nums
// trigger input -- single pulse: sends a buffer signal (?): OUTPUT mode
// transmit wave -- 8-pulses (very small) like aquaman ))))
// echo input -- remains on until the first echo is received: INPUT mode
// distance = 0.5 * time between emission and reception (round trip) * speed of sound in medium
// trig pin must be activated for no more than 10us (digWrite high, delaymicroseconds(10), digWrite low)
// then get the duration = pulseIn(echoPin, HIGH); --> returns the round trip time in microsecs

// analogue sensors -- require an ADC to be processed by mcu
// potentiometre / potential dividers --> analogue devices
// the voltage in a potential divider can be anywhere from 0 to the input potential
// connecting the Vout pin to A-num pins lets us measure analogue
// having multiple bits lets you have different permutations of binary potential
// ergo, having multiple i/o bits can model a time-varying signal as a semi-discrete "ladder"
// i.e. a least squares discrete approximation to the curve
// input voltages are separated into ranges through hardware stuff and an  equation that im too tired to pay attention to
// the analogue pin is read with analogRead(Apin)
// (Vcc / 2^n - 1) * Vanalog where n is the memory of the ADC

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
