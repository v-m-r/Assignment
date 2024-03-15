To approach this method without using any keywords delay(),micros(),millis() and additional
function related to time I have used a concept called as internal timers in arduino. There are **3** internal timer in the arduino.
they are:
<b>
1. Timer0
2. Timer1
3. Timer2
4. </b>

**timer 0** is 8 bit counter count 0 - 255.

**timer 1** is 16 bit counter counts 0 - 65600.

**timer 2** is 8 bit counter same as timer 0.

These timer are depend on real time clock. If we handle them rigth we can will no - negligible error in real time.
For this program I have used **timer0** with preScaler value of 1/64.
