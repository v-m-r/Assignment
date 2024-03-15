/*To approach this method without using any keywords delay(),micros(),millis() and additional
function related to time we have to use the internal timer present in the micro controller.
in arduino we have 3 timers 
they are:
1. Timer0
2. Timer1
3. Timer2
timer 0 is 8 bit counter count 0 - 255.
timer 1 is 16 bit counter counts 0 - 65600.
timer 2 is 8 bit counter same as timer 0.

These timer are depend on real time clock. If we handle them rigth we can will no - negligible error in real time.
In this program I have used timer0 with preScaler value of 1/64.
*/
const int LM_35_Sensor = A0;
// LM35 sensor is assigend to A0 i.e. 14 pin
const int LED = 13;
//LED is assigned to 13 
bool status =0;
int counter = 0;
//to count no.of millisecond passed
void setup() {
  pinMode(LED,OUTPUT);
  TCCR0A |= B00000010;//Short for Timer / counter control register.
  //in TCCR0A timer register WGM01 Set to 1 for CTC
  OCR0A=0xFA;// short for Ouptup compare register
  //OCR0A is initialized with 0xfa i.e. (250) base 10.
  TIMSK0 |=B00000010;//short for timer interrup mask register.
  //TIMSK 0 is set OCIE0A set to 1 to enable overflow interrupt after 250 count.
  TCCR0B |=B00000011;
  //TCCR0B is bot cs00,01 bit are set to 1 therefore PreScaler = 64
  sei();
  //Enable Inturrpt
}

void loop() {
  int Vs = analogRead(LM_35_Sensor);
  //getting the voltage from the LM35 Sensor.
  float Temperature = (Vs*500)/1023;
  //converting voltage to Celicus.
  if(Temperature<30){
    BlinkLed(250);
  }
  else{
    BlinkLed(500);
  }
}
void BlinkLed(int delayTime){
  //this way we can count upto 500/250 milliseconds 
  if(counter >=delayTime){
   status = !status;
  	counter = 0;
  }
  digitalWrite(LED,status);
}
ISR(TIMER0_COMPA_vect){//requests the Interrupt
  counter++;//counting milliseconds.
}
