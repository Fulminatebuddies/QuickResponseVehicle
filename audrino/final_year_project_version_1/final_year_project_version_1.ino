#include <avr/interrupt.h>
#include <LowPower.h>
int sensor_value_1;
int sensor_value_2;
int sensor_value_3;
int sensor_value_4;
int motor_1_encoder_value;
int motor_2_encoder_value;
int difference_encoder_value;
String sensor_1_data;
String sensor_2_data;
String sensor_3_data;
String sensor_4_data;
String motor_1_data;
String motor_2_data;
int sensor_1;
int sensor_2;
int sensor_3;
int sensor_4;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(19200);
  pinMode (13, INPUT_PULLUP); // Sensor_1
  pinMode (12, INPUT_PULLUP); //Sensor_2
  pinMode (11, INPUT_PULLUP); //Sensor_3
  pinMode (10, INPUT_PULLUP); //Sensor_4
  pinMode (7, OUTPUT); //MOTor HOtline signal  
  pinMode (6, OUTPUT); //MOTor HOtline signal
  digitalWrite (7, LOW); // signal intialize to 0 for motor
  digitalWrite (6, LOW); // signal intialize to 0 for motor
  cli();
  PCICR |= 0b00000001;    // turn on port b
  PCMSK0 |= 0b00111100;       // to enable pb2 pb3 pb4 pb5
  PCIFR |= bit(PCIF0);
  sei();
  pinMode (7, OUTPUT);
  pinMode(6,OUTPUT);
}

void loop() {
  receiveserialdata();
  categorize_data();
  moving_of_vehicle();
}
ISR (PCINT0_vect) { //Send command to motor to stop..
motorstop();
}

void motorstop()
{
  //let the hotline pin be pin number 8 and 9 

  digitalWrite (7, LOW); // signal intialize to 0 for motor
  digitalWrite (6, LOW); // signal intialize to 0 for motor
  digitalWrite (7, HIGH); // signal intialize to 1 for motor
  digitalWrite (6, HIGH); // signal intialize to 1 for motor
  delay(10);
  digitalWrite (7, LOW); // signal intialize to 0 for motor
  digitalWrite (6, LOW); // signal intialize to 0 for motor

}

void check_for_interrupt ()
{
  
}

void receiveserialdata()
{
  /* This function is related to communication betwwen master and slave. Just to be clear for a dummy like me,
     this code where this comment is written is the master controller.
     NOw how this code works is it polls data continously from sensor module one by one.
     It is like human body where the brain is the master controller and periphals are body parts.
  */
  
  
  //  // Lets start with sensor_1
  PCMSK0 &= 0b11011111;
  PCIFR |= bit(PCIF0);
  pinMode (13, OUTPUT); // Sensor_1
  digitalWrite (13, LOW); //Interpt for sensor_1
  digitalWrite(13, HIGH);
  delay(10);
  //now the interpt has been set. the data should start coming
  if (Serial.available() > 0)
    sensor_1_data = Serial.readStringUntil('t');
  sensor_value_1 = sensor_1_data.toInt();
  Serial.println(sensor_1_data);
  serialFlush();
  pinMode (13, INPUT_PULLUP); // Sensor_1
  PCMSK0 |= 0b00111100;
  //now we are done with sensor_1 , lets go to sensor_2

    // Lets start with sensor_2
   PCMSK0 &= 0b11101111;
    pinMode (12, OUTPUT); //Sensor_2
    digitalWrite (12, LOW); //Interpt for sensor_2
    digitalWrite(12, HIGH);
    delay(10);
    //now the interpt has been set. the data should start coming
    if (Serial.available() > 0)
      sensor_2_data = Serial.readStringUntil('t');
    sensor_value_2 = sensor_2_data.toInt();
    Serial.println(sensor_2_data);
    serialFlush();
    pinMode (12, INPUT_PULLUP); // Sensor_2
    PCMSK0 |= 0b00111100;
    //now we are done with sensor_2 , lets go to sensor_3
  
    // Lets start with sensor_3
    PCMSK0 &= 0b11110111;
    pinMode (11, OUTPUT);
    digitalWrite (11, LOW); //Interpt for sensor_3
    digitalWrite(11, HIGH);
    delay(10);
    //now the interpt has been set. the data should start coming
    if (Serial.available() > 0)
      sensor_3_data = Serial.readStringUntil('t');
    sensor_value_3 = sensor_3_data.toInt();
    Serial.println(sensor_3_data);
    serialFlush();
    pinMode (11, INPUT_PULLUP); // Sensor_3
    PCMSK0 |= 0b00111100;
    //now we are done with sensor_3 , lets go to sensor_4
  
    // Lets start with sensor_4
    PCMSK0 &= 0b11111011;
    pinMode (10, OUTPUT);
    digitalWrite (10, LOW); //Interpt for sensor_4
    digitalWrite(10, HIGH);
    delay(10);
    //now the interpt has been set. the data should start coming
    if (Serial.available() > 0)
      sensor_4_data = Serial.readStringUntil('t');
    sensor_value_4 = sensor_4_data.toInt();
    Serial.println(sensor_4_data);
    serialFlush();
    pinMode (10, INPUT_PULLUP); // Sensor_4
    PCMSK0 |= 0b00111100;
    //now we are done with sensor_4 , this was the last sensor.

}
void categorize_data() {
  // put your main code here, to run repeatedly:
  /* This function defines the movment of motor according to the input received from the sensor module.
     This is the third time i am writing this comment and reading it the 100th time so bear with me if this explanation is boaring.
     NOw for the forward sensor there are 3 settings
     If the distance is in between object and sensor is between 10cm and 5 cm i.e sensor value is in between 1023 and 511 the sensor is said to be in far position
     far = 3
     If the distance is in between object and sensor is between 5cm and 2 cm i.e sensor value is in between 510 and 240 the sensor is said to be in medium position
     medium = 2
     If the distance is in between object and sensor is between 2cm and .5 cm i.e sensor value is in between 239 and 51 the sensor is said to be in zaval position
     zaval=1
  */
  if (sensor_value_1 >= 511 || sensor_value_1 <= 1023)
  {
    sensor_1 = 3;
  }

  else if  (sensor_value_1 >= 240 || sensor_value_1 <= 510)
  {
    sensor_1 = 2;
  }

  else if (sensor_value_1 >= 51 || sensor_value_1 <= 239)
  {
    sensor_1 = 1;
  }
  //Similarly for the sensor_4 .. If not clear yet these are the two sensors detecting forward direction
  if (sensor_value_4 >= 511 || sensor_value_4 <= 1023)
  {
    sensor_4 = 3;
  }

  else if  (sensor_value_4 >= 240 || sensor_value_4 <= 510)
  {
    sensor_4 = 2;
  }

  else if (sensor_value_4 >= 51 || sensor_value_4 <= 239)
  {
    sensor_4 = 1;
  }
  /* Now lets try to pin down the postion of the sensor 2 and sensor 3 . These are used for the detection of left and right turn respectively.
     These sensors ideally will always detect something because the road the robot will follow will be almost be enclosed.
     So in this case, for sensor 2 and sensor 3 we have to detect if there is a free turn.
     notavailable = 0
     available = 1

  */
  if (sensor_value_2 >= 51 || sensor_value_2 <= 511) // need to check this value depending upon the size of vehicle.
  {
    sensor_2 = 0;
  }

  else if (sensor_value_1 >= 512 || sensor_value_1 <= 1023) // valuses are subject to change without further notice.
  {
    sensor_2 = 1;
  }
  if (sensor_value_3 >= 51 || sensor_value_3 <= 511) // need to check this value depending upon the size of vehicle.
  {
    sensor_3 = 0;
  }

  else if (sensor_value_3 >= 512 || sensor_value_3 <= 1023) // valuses are subject to change without further notice.
  {
    sensor_3 = 1;
  }

}

void moving_of_vehicle()
{

 /* This first condition is when it is a open space that is the path has no constraints.
  *  So here the code will eneter a new loop which will run in infinite times unless hotline condition occures, and when it does the 
  *  controller goes in kind of reset condition. Function of this Hotline is explained in the function itself.
  *  
  *  
  *  
  *  
  *                                 ******************************************
  *                                 *                                        * 
  *                                 *                                        *   
  *                                 *                                        *
  *                                 *                                        *   
  *                                 *                                        * 
  *                                 *                                        *
  *                                 *                                        * 
  *                                 *                                        * 
  *                                 *                                        * 
  *                                 *                                        * 
  *                                 *                                        * 
  *                                 *                                        * 
  *                                 *                                        * 
  *                                 *                                        * 
  *                                 *                                        * 
  *                                 *               ^^                       *     
  *                                 *                                        * 
  *                                 *                                        * 
  *                                 ******************************************                                       
  *                                 
  *                                 
  *  
  */

   if ( sensor_1 == 3 && sensor_4 ==3 && sensor_2 == 1 && sensor_3 == 1 )
   {
    freeloop();
   }
  
  /* now lets explore conditions where the bot has to make decisions
    First lets start with staright condition
    Depending upon the condition of sensor lets decide the speed of motor.
                                    *  *
                                    *  *
                                    *  *
                                    *  *
                                    *  *
                                    *  *
                                    *  *
                                    *  *
                                    *  *
                                     ^^
  */
  if (sensor_2 == 0 && sensor_3 == 0)// Checking if the path is straight
  {
    if ( sensor_1 == 3 && sensor_4 == 3)
    {
      //Motor should run at max speed in staraight direction. Code to be written when format for communication is provided.
    }
    else if ( sensor_1 == 2 && sensor_4 == 2)
    {
      //Motor should run at medium speed
    }
    else if (sensor_1 == 1 && sensor_4 == 1)
    {
      //Motor should run at 30% speed
    }
  }
  /*Lets look at the turn cronologically. Lets start with + junction.
                      *  *
                      *  *
                      *  *
                   ****  ****
                   ****  ****
                      *  *
                      *  *
                      *  *
                       ^^


  */
  else if ( sensor_1 == 3 && sensor_4 == 3 && sensor_2 == 1 && sensor_3 == 1 )
  {
    // This is a + node. As decided previously we will always go in the left direction.
    // Motor should take a left turn.
    // Send Left command to motor module.
  }
  /* Lets got to a T junction now.
                *************

                *****  ******
                    *  *
                    *  *
                    *  *
                    *  *
                    *  *
                    *  *
                     ^^
  */
  else if (sensor_2 == 1 && sensor_3 == 1 && sensor_1 == 2 && sensor_4 == 2)
  {
    // T junction detected.
    // Still we will go left.
    // Send Left command to motor module
  }
  /* NOw lets explore another area of T junction only just a little different
               *  *
               *  *
               *  *
               *  *****

               *  *****
               *  *
               *  *
               *  *
                ^^
  */
  else if ( sensor_1 == 3 && sensor_4 == 3 && sensor_3 == 1 && sensor_2 == 0 )
  {
    // Ihave not decided what priority to be given if left turn isn't available
    // For now we will send the motor to take right turn
  }
  /* NOw lets explore another area of T junction only just a little more different
               *  *
               *  *
               *  *
           *****  *

           *****  *
               *  *
               *  *
               *  *
                ^^
  */
  else if (  sensor_1 == 3 && sensor_4 == 3 && sensor_3 == 0 && sensor_2 == 1 )
  {
    // Here left tuen is available na so we will take left turn.
    // send left command to motor module.
  }



  /*Now what if the path has a right turn
    UNtil the path detects a left turn the above straight path loop will go on
                                      *********

                                      *  ******
                                      *  *
                                      *  *
                                      *  *
                                      *  *
                                       ^^
  */
  else if ( sensor_2 == 0 && sensor_3 == 1 && sensor_1 == 2 && sensor_4 == 2)
  {
    // Simply take a right turn
  }
  /*Now what if the path has a left turn
    UNtil the path detects a left turn the above straight path loop will go on
                                   *******

                                   ****  *
                                      *  *
                                      *  *
                                      *  *
                                      *  *
                                       ^^
  */
  else if ( sensor_2 == 1 && sensor_3 == 0 && sensor_1 == 2 && sensor_4 == 2)
  {
    // Simply take a left turn
  }
}

void freeloop()
{
  //So we know for a fact that there are no restrictions on path. Lets take this opportunity to make motor go on full speed. 
  //IN this loop the vehicle will run unless it gets hotline condition.
// For the very first condition lets get the motors running .
// First data packet for each module is the id of that motor 
// 001 for left motor
// 011 for the right motor 
Serial.write ("001"); // ID for left motor
Serial.write("t");
Serial.write ("M Max S"); //This stands for "Motor Max Speed"
Serial.write("t");
Serial.write("tt");
Serial.write ("011"); // ID for motor right motor
Serial.write("t");
Serial.write ("M Max S"); //This stands for "Motor Max Speed"
Serial.write("tt");
LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF); 
//  while (1)
//  {
//    //motor should start running at max speed
//    for (int i= 1; i<=5 ; i++)
//    {
//    Serial.write ("001"); // ID for left motor
//    Serial.write("t");
//    Serial.write("S ME D"); //Stands for "Send Motor Encoder Data"
//    Serial.write("t");
//     if (Serial.available() > 0)
//      motor_1_data = Serial.readStringUntil('t');
//    motor_1_encoder_value_i = motor_1_data.toInt();
//    Serial.write ("011"); // ID for right motor
//    Serial.write("t");
//    Serial.write("S ME D"); //Stands for "Send Motor Encoder Data"
//    Serial.write("t");
//     if (Serial.available() > 0)
//      motor_2_data = Serial.readStringUntil('t');
//    motor_2_encoder_value = motor_2_data.toInt();
//   difference_encoder_value_i = motor_2_encoder_value - motor_2_encoder_value
//   //now the difference indicates which motor will move more 
//    }
//     motor_2_encoder_value = motor_2_encoder_value_1 + motor_2_encoder_value_2 + motor_2_encoder_value_3 + motor_2_encoder_value_4 + motor_2_encoder_value_5;
//     motor_1_encoder_value = motor_1_encoder_value_1 + motor_1_encoder_value_2 + motor_1_encoder_value_3 + motor_1_encoder_value_4 + motor_1_encoder_value_5;  
//  int temp = 0;
//  int x = 2000; // Assuming 2k is the [max rpm - 500 (a compensation factor) ] of motor 
//  int y;
//  temp = motor_2_encoder_value - motor_1_encoder_value;
//  
//  y = x + temp
//  if (temp > 0)
//  {
//    Serial.write("001");
//    Serial.write("t");
//    Serial.write("T RPM"); // Stands for "Take RPM"
//    Serial.write("t");
//    Serial.write(y);
//    Serial.write("t");
//    Serial.write("011");
//    Serial.write("t");
//    Serial.write("T RPM"); // Stands for "Take RPM"
//    Serial.write("t");
//    Serial.write(x);
//    Serial.write("t");
//  }
//     
//  }
}

void serialFlush() {
  while (Serial.available() > 0) {
    char t = Serial.read();
  }
  sensor_1_data = "0";
  sensor_2_data = "0";
  sensor_4_data = "0";
  sensor_3_data = "0";
}
