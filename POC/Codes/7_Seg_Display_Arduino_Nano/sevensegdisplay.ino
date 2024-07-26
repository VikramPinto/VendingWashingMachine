/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
*/

// the setup function runs once when you press reset or power the board

void send_disp(void);
void disp_val(char *);
char pos[4]={0,0,0,0};
#define DIG1 12
#define DIG2 10
#define DIG3 11

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  digitalWrite(2, HIGH); // a
  digitalWrite(3, HIGH); // b
  digitalWrite(4, HIGH); // c
  digitalWrite(5, HIGH); // d
  digitalWrite(6, HIGH); // e
  digitalWrite(7, HIGH); // f
  digitalWrite(8, HIGH); // g
  digitalWrite(9, HIGH); // dp
  digitalWrite(DIG1, LOW); // dig1 
  digitalWrite(DIG2, LOW); // dig2 
  digitalWrite(DIG3, LOW); // dig3 

  Serial.begin(9600);
  TCCR1A = 0;           // Init Timer1
  TCCR1B = 0;           // Init Timer1
  TCCR1B |= B00000011;  // Prescalar = 64
  OCR1A = 25000;        // Timer CompareA Register
  TIMSK1 |= B00000010;  // Enable Timer COMPA Interrupt
  
}

// the loop function runs over and over again forever
void loop() {
  unsigned int ones, tens, hundreds,number;
  for (number =0; number<1000; number++)
  {
    ones = number % 10; 
    tens = (number / 10) % 10; 
    hundreds = number / 100; 

    pos[0] = (hundreds + 0x30) ;
    pos[1] = (tens + 0x30) ;
    pos[2] = (ones + 0x30) ;
    pos[3] = ' ' ;
    // Serial.println(pos[0]);
    // Serial.println(pos[1]);
    // Serial.println(pos[2]);
    
    delay(500); 

  }
  
}

void send_disp(void)
{
  digitalWrite(DIG1 , HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(1);                      // wait for a second
  digitalWrite(DIG1, LOW);   // turn the LED off by making the voltage LOW
  delay(1);  
  disp_val(pos+3);
  disp_val(pos);


  digitalWrite(DIG2 , HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(1);                      // wait for a second
  digitalWrite(DIG2, LOW);   // turn the LED off by making the voltage LOW
  delay(1); 
  disp_val(pos+3);
  disp_val(pos+1);

  digitalWrite(DIG3 , HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(1);                      // wait for a second
  digitalWrite(DIG3, LOW);   // turn the LED off by making the voltage LOW
  delay(1);                      // wait for a second
  disp_val(pos+3);
  disp_val(pos+2);

}



void disp_val(char *val)
{
  
  //Serial.println(val[0]);
  switch(val[0])
  {
    case '0' :
              //Serial.println("reached here -> 0");
              digitalWrite(2, LOW); // a
              digitalWrite(3, LOW); // b
              digitalWrite(4, LOW); // c
              digitalWrite(5, LOW); // d
              digitalWrite(6, LOW); // e
              digitalWrite(7, LOW); // f
              digitalWrite(8, HIGH); // g
              digitalWrite(9, HIGH); // dp
    break;

    case '1' : 
              //Serial.println("reached here -> 1");
              digitalWrite(2, HIGH); // a
              digitalWrite(3, LOW); // b
              digitalWrite(4, LOW); // c
              digitalWrite(5, HIGH); // d
              digitalWrite(6, HIGH); // e
              digitalWrite(7, HIGH); // f
              digitalWrite(8, HIGH); // g
              digitalWrite(9, HIGH); // dp
    break;

    case '2' : 
              //Serial.println("reached here -> 2");
              digitalWrite(2, LOW); // a
              digitalWrite(3, LOW); // b
              digitalWrite(4, HIGH); // c
              digitalWrite(5, LOW); // d
              digitalWrite(6, LOW); // e
              digitalWrite(7, HIGH); // f
              digitalWrite(8, LOW); // g
              digitalWrite(9, HIGH); // dp
    break;

    case '3' : 
              //Serial.println("reached here -> 2");
              digitalWrite(2, LOW); // a
              digitalWrite(3, LOW); // b
              digitalWrite(4, LOW); // c
              digitalWrite(5, LOW); // d
              digitalWrite(6, HIGH); // e
              digitalWrite(7, HIGH); // f
              digitalWrite(8, LOW); // g
              digitalWrite(9, HIGH); // dp
    break;

    case '4' : 
              //Serial.println("reached here -> 2");
              digitalWrite(2, HIGH); // a
              digitalWrite(3, LOW); // b
              digitalWrite(4, LOW); // c
              digitalWrite(5, HIGH); // d
              digitalWrite(6, HIGH); // e
              digitalWrite(7, LOW); // f
              digitalWrite(8, LOW); // g
              digitalWrite(9, HIGH); // dp
    break;

    case '5' : 
              //Serial.println("reached here -> 2");
              digitalWrite(2, LOW); // a
              digitalWrite(3, HIGH); // b
              digitalWrite(4, LOW); // c
              digitalWrite(5, LOW); // d
              digitalWrite(6, HIGH); // e
              digitalWrite(7, LOW); // f
              digitalWrite(8, LOW); // g
              digitalWrite(9, HIGH); // dp
    break;

    case '6' : 
              //Serial.println("reached here -> 2");
              digitalWrite(2, LOW); // a
              digitalWrite(3, HIGH); // b
              digitalWrite(4, LOW); // c
              digitalWrite(5, LOW); // d
              digitalWrite(6, LOW); // e
              digitalWrite(7, LOW); // f
              digitalWrite(8, LOW); // g
              digitalWrite(9, HIGH); // dp
    break;

    case '7' : 
              //Serial.println("reached here -> 2");
              digitalWrite(2, LOW); // a
              digitalWrite(3, LOW); // b
              digitalWrite(4, LOW); // c
              digitalWrite(5, HIGH); // d
              digitalWrite(6, HIGH); // e
              digitalWrite(7, HIGH); // f
              digitalWrite(8, HIGH); // g
              digitalWrite(9, HIGH); // dp
    break;

    case '8' : 
              //Serial.println("reached here -> 2");
             digitalWrite(2, LOW); // a
              digitalWrite(3, LOW); // b
              digitalWrite(4, LOW); // c
              digitalWrite(5, LOW); // d
              digitalWrite(6, LOW); // e
              digitalWrite(7, LOW); // f
              digitalWrite(8, LOW); // g
              digitalWrite(9, HIGH); // dp
    break;

    case '9' : 
              //Serial.println("reached here -> 2");
              digitalWrite(2, LOW); // a
              digitalWrite(3, LOW); // b
              digitalWrite(4, LOW); // c
              digitalWrite(5, LOW); // d
              digitalWrite(6, HIGH); // e
              digitalWrite(7, LOW); // f
              digitalWrite(8, LOW); // g
              digitalWrite(9, HIGH); // dp
    break;

    default:
              digitalWrite(2, HIGH); // a
              digitalWrite(3, HIGH); // b
              digitalWrite(4, HIGH); // c
              digitalWrite(5, HIGH); // d
              digitalWrite(6, HIGH); // e
              digitalWrite(7, HIGH); // f
              digitalWrite(8, HIGH); // g
              digitalWrite(9, HIGH); // dp
    break;
  }
}

ISR(TIMER1_COMPA_vect)
{
  OCR1A += 2500; // Advance The COMPA Register
  // Handle The 100ms Timer Interrupt
 send_disp();
}