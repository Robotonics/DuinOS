/*
 DuinOS SiezeofPC
 
 Blinks the LED on an arduino board (13) to indicate that the system is alive.
 
 Created 2013.03.20 (yyyy.mm.dd)
 by Nicolas Sanz
 based on MoreComplexBlinking example of DuinOS
 
 Instructions
   Compile and load it
   check that the led is blinking
   Open a serial comunications
   write a 'g' to get the sizeof pointer to task functions
 */

#define INITIAL_GREEN_DELAY  200
#define NEW_GREEN_DELAY  20

int ledPinRed =  13;
int ledPinGreen =  12;
char* st1 = "ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";
char* st2 = "22222222222222222222222222222222222222222222222222222222222222222222222";
char* st3 = "111111111111111111111111111111111111111111vcvcxv111111111111111111111111111111111111111111111111111111111111111";
char* st4 = "ssssssssssssssssssssssssweewdradsssssssvcxsssssssssssssssssssssssssssssssss";
char* st5 = "ssssssssssssadsfssssssssssssfssssscxfsssssssssssssssssssssvczxvczcxvzxvzxvszxvzxcvzxsssssssssssssssssss";
char* st6 = "vzxcvv hgjhkghklhkjljlk.,cxv";
char* st7 = "sssssssssssssssdsfssssssssssssvxcvsssssssssssscssvvcxsssssssssssssssssssssssssssssss";
char* st8 = "sssssssssssssdafasdfsadfsscvcxssssdfsdesdssssssssssfdfdsfdsfzsssssssssssssssssssssssssssssssssssssssssss";
char* st9 = "ssssssssssssssssssssssssssssssssssssssssss mg h gdf afssssssssssssssssssssssssssssss";
char* st0 = "sssssssssssssdfsdfasdfsssssssssssssssssssssfad f fdfcsdvfcsfasdfsssssssssssssssssssssssssssssssssssssss";
char* st11 = "ssssssssssssssssssssssssssssvzcxvzxcvzxcvsssssssssssssssssssssssssssssssasdfasdfdsfdsfsssssssssssss";
boolean redLED_isOn = false;

taskLoop(redLED)
{
  redLED_isOn = false;
  delay(1000);
  redLED_isOn = true; 
  delay(1000);
}

/*taskLoop(sizeofPC)
{
  char inChar;
  unsigned long val;
  if((inChar = Serial.read())=='g')
  {
    Serial.print("Sizeof for the name of the function: ");
    val = (unsigned long) &redLED;
    Serial.print(val, HEX);
    Serial.print("/");
    delay(100);
    val = (unsigned long) redLED;
    Serial.print(val, HEX);
    Serial.print("/");
    delay(100);
    Serial.println(sizeof(redLED));
    delay(100);
    
    Serial.print("Sizeof for the name of the function declaration in freeRTOS: ");
    val = (unsigned long) *redLEDFunction;
    Serial.print(val, HEX);
    Serial.print("/");
    delay(100);
    val = (unsigned long) &redLEDFunction;
    Serial.print(val, HEX);
    Serial.print("/");
    delay(100);
    val = (unsigned long) redLEDFunction;
    Serial.print(val, HEX);
    Serial.print("/");
    delay(100);
    Serial.println(sizeof(&redLEDFunction));
    delay(100);
    
    Serial.print("Sizeof for the name of the task DECLARATION: ");
    val = (unsigned long) *redLED_Task;
    Serial.print(val, HEX);
    Serial.print("/");
    delay(100);
    val = (unsigned long) &redLED_Task;
    Serial.print(val, HEX);
    Serial.print("/");
    delay(100);
    val = (unsigned long) redLED_Task;
    Serial.print(val, HEX);
    Serial.print("/");
    Serial.println(sizeof(&redLED_Task));
    delay(100);
    
    Serial.print("Sizeof for setup(): ");
    val = (unsigned long) *setup;
    Serial.print(val, HEX);
    Serial.print("/");
    delay(100);
    val = (unsigned long) &setup;
    Serial.print(val, HEX);
    Serial.print("/");
    delay(100);
    val = (unsigned long) setup;
    Serial.print(val, HEX);
    Serial.print("/");
    delay(100);
    Serial.println(sizeof(&setup));
    delay(100);
    
    Serial.print("Sizeof for loop(): ");
    val = (unsigned long) *loop;
    Serial.print(val, HEX);
    Serial.print("/");
    delay(100);
    val = (unsigned long) &loop;
    Serial.print(val, HEX);
    Serial.print("/");
    delay(100);
    val = (unsigned long) loop;
    Serial.print(val, HEX);
    Serial.print("/");
    delay(100);
    Serial.println(sizeof(&loop));
    delay(100);
    val = sizeof(&loop);
    Serial.println(val);
  }
  delay(100);
}
*/

// The setup() method runs once, when the sketch starts

void setup()   
{                
  Serial.begin(9600);
  // Initialize the digital pins as outputs:
  pinMode(ledPinRed, OUTPUT);
  
  createTaskLoop(redLED, NORMAL_PRIORITY);
  //createTaskLoop(sizeofPC, NORMAL_PRIORITY);

}


// This is the main loop() method, wich runs over and over again,
// as long as the Arduino has power. Is a LOW_PRIORITY taskLoop:

void loop()                     
{
  if (redLED_isOn)
  {
    digitalWrite(ledPinRed, LOW);  // set the LED off
    delay(25);                      // The OS can be tested reducing these delays, and seeing how both LEDs work together...
    digitalWrite(ledPinRed, HIGH);   // set the LED on
    delay(25);    
  }
  else
  {
    digitalWrite(ledPinRed, LOW);  //  LED is off
    //If nextTask is not called, the application will not hang, because the OS is preemptive. BUT, the current task
    //will consume a lot of computational resources (due to it's lack of a delay() in this branch), the application will 
    //turn slower, and the other tasks may be affected by this, loossing precision in their timing:
    nextTask();
  }
}


