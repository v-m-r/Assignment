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
/*app
These timer are depend on real time clock. If we handle them rigth we can will no - negligible error in real time.
In this program I have used timer0 with preScaler value of 1/64.
*/
#define Timer_Register_A TCCR0A      //TCCR0A-timer counter / controller register0 A
#define Timer_Register_B TCCR0B      //TCCR0B-timer counter / controller register0 B
#define Timer_Interrupt TIMSK0       //TIMSK0-timer interrupt mask regiser0
#define Timer_Threshold OCR0A        //OCR0A Output compare register0 A
#define Interrupt TIMER0_COMPA_vect  //Timer 0 compare match register a vector is a interrupt
const int LM_35_Sensor = A0;
// LM35 sensor is assigend to A0 i.e. 14 pin
const int LED = 13;
//LED is assigned to 13
bool status = 0;
int counter = 0;
//to count no.of millisecond passed
void setup() {

  pinMode(LED, OUTPUT);
  //configuring LED pin 13 as a output pin
  Timer_Register_A |= 2;  // can also do t_reg_a |= (1<<WGM01) or t_reg_a |=B00000010
  //setting WGM01 to 1 Enabling CTC int. so that when it reachs the threshold value it will reset the timer
  Timer_Threshold = 250;  //
  //Giving the Threshold value to 250 to count exactly 1ms.
  Timer_Interrupt |= 2;  //.can also do t_int |= (1<<OCIEA) or t_int |=B00000010
  //setting OCIEA to 1in TIMSK i.e. Timer_Interrupt to enable Compare interrupt.
  Timer_Register_B |= 3;  //can also do t_reg_b |= (1<<CS00), (1<<CS01) or t_reg_b |=B00000011
  //setting CS00 and CS01 to 1 to make the timer preScaler value to 64.
  sei();
  //Enable Inturrpt
}

void loop() {
  int Vs = analogRead(LM_35_Sensor);
  //getting the voltage from the LM35 Sensor.
  float Temperature = ((Vs * 4.9) - 500) / 10;
  //converting voltage to Celicus.
  if (Temperature < 30) {
    BlinkLed(250);
  } else {
    BlinkLed(500);
  }
}
void BlinkLed(int delayTime) {
  //this way we can count upto 500/250 milliseconds
  if (counter >= delayTime) {
    status = !status;
    counter = 0;
  }
  digitalWrite(LED, status);
}
ISR(Interrupt) {  //requests the Interrupt
  counter++;      //counting milliseconds.
}
