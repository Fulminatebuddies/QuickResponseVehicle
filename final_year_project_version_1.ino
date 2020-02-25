void setup() {
  // put your setup code here, to run once:
  int sensor_value_1;
  int sensor_value_2;
  int sensor_value_3;
  int sensor_value_4;
  char sensor_1;
  char sensor_4;
  char sensor_2;
  char sensor_3;
  Serial.begin(19200);
}

void loop() {
  
readSensor();




}
void sendserialdata()
{
  /* This function is related to communication betwwen master and slave. Just to be clear for a dummy like me, 
   * this code where this comment is written is the master controller.  
   * NOw how this code works is it polls data continously from sensor module one by one.  
   * It is like human body where the brain is the master controller and periphals are body parts. 
   * Each body part (or slave controller) is given a specific unique address. This address is the first bit of information sent by the controller. 
   * Whichever peripheral has that address will only respond
   * Following are the ids for sensor 
   * sensor_1 = 001 or 001
   * sensor_2 = 002 or 010 
   * sensor_3 = 003 or 011
   * sensor_4 = 004 or 100
   *  motor_1 = 005 or 101
   *  motor_2 = 006 or 110
   */
   int sensor_1_data = 0, sensor_2_data = 0, sensor_3_data = 0, sensor_4_data = 0, motor_1_data = 0, motor_1_data = 0;
   char ch;
  for (int i = 0;i <= 5;i++) // starts collecting data
  {
    if (i == 0)//This will be sensor_1 i.e. the sensor which sees forward (left wala) 
    {
      ch = 0;
      Serial.write ("001");
      while (Serial.read() != "REC")
      {
        
      }
      Serial.write ("SD")
       while (ch != 't')
  {
    while (!Serial.available())
    {
    }
    ch = Serial.read();
    if (ch >= '0' && ch <= '9')
    {
      sensor_1_data = sensor_1_data * 10 + (ch - '0');
    }
  }
   ++i;   
    }
     else if (i == 1)//This will be sensor_2 i.e. the sensor which sees left 
    {
      ch = 0;
      Serial.write ("002");
      while (Serial.read() != "REC")
      {
        
      }
      Serial.write ("SD")
       while (ch != 't')
  {
    while (!Serial.available())
    {
    }
    ch = Serial.read();
    if (ch >= '0' && ch <= '9')
    {
      sensor_2_data = sensor_2_data * 10 + (ch - '0');
    }
  }
    ++i;  
    }
       else if (i == 2)//This will be sensor_3 i.e. the sensor which sees left 
    {
      ch = 0;
      Serial.write ("003");
      while (Serial.read() != "REC")
      {
        
      }
      Serial.write ("SD")
       while (ch != 't')
  {
    while (!Serial.available())
    {
    }
    ch = Serial.read();
    if (ch >= '0' && ch <= '9')
    {
      sensor_3_data = sensor_3_data * 10 + (ch - '0');
    }
  }
    ++i;  
    }     
  }
}
void readSensor(){
  // put your main code here, to run repeatedly:
  /* This function defines the movment of motor according to the input received from the sensor module. 
     This is the third time i am writing this comment so bear with me if this explanation is boaring.
     NOw for the forward sensor there are 3 settings
     If the distance is in between object and sensor is between 10cm and 5 cm i.e sensor value is in between 1023 and 511 the sensor is said to be in far position
     If the distance is in between object and sensor is between 5cm and 2 cm i.e sensor value is in between 510 and 240 the sensor is said to be in medium position
     If the distance is in between object and sensor is between 2cm and .5 cm i.e sensor value is in between 239 and 51 the sensor is said to be in zaval position

  */
  if (sensor_value_1 >= 511 || sensor_value_1 <= 1023)
  {
    sensor_1 = far;
  }

  else if  (sensor_value_1 >= 240 || sensor_value_1 <= 510)
  {
    sensor_1 = medium;
  }

  else (sensor_value_1 >= 51 || sensor_value_1 <= 239)
  {
    sensor_1 = zaval;
  }
  //Similarly for the sensor_4 .. If not clear yet these are the two sensors detecting forward direction
  if (sensor_value_4 >= 511 || sensor_value_4 <= 1023)
  {
    sensor_4 = far;
  }

  else if  (sensor_value_4 >= 240 || sensor_value_4 <= 510)
  {
    sensor_4 = medium;
  }

  else (sensor_value_4 >= 51 || sensor_value_4 <= 239)
  {
    sensor_4 = zaval;
  }
  /* Now lets try to pin down the postion of the sensor 2 and sensor 3 . These are used for the detection of left and right turn respectively.
     These sensors ideally will always detect something because the road the robot will follow will be almost be enclosed.
     So in this case, for sensor 2 and sensor 3 we have to detect if there is a free turn.

  */
  if (sensor_value_2 >= 51 || sensor_value_2 <= 511) // need to check this value depending upon the size of vehicle.
  {
    sensor_2 = left_turn_notavailable;
  }

  else (sensor_value_1 >= 512 || sensor_value_1 <= 1023) // valuses are subject to change without further notice.
  {
    sensor_2 = left_turn_available;
  }
  if (sensor_value_3 >= 51 || sensor_value_3 <= 511) // need to check this value depending upon the size of vehicle.
  {
    sensor_3 = right_turn_notavailable;
  }

  else (sensor_value_3 >= 512 || sensor_value_3 <= 1023) // valuses are subject to change without further notice.
  {
    sensor_3 = right_turn_available;
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
  if (sensor_2 == left_turn_notavailable && sensor_3 == right_turn_notavailable)// Checking if the path is straight
  {
    if ( sensor_1 == far && sensor_4 == far)
    {
      //Motor should run at max speed in staraight direction. Code to be written when format for communication is provided.
    }
    else if ( sensor_1 == medium && sensor_4 == medium)
    {
      //Motor should run at medium speed
    }
    else (sensor_1 == zaval && sensor_4 == zaval)
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
  else if ( sensor_1 == far && sensor_4 == far && sensor_2 == left_turn_available && sensor_3 == right_turn_available )
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
  else if (sensor_2 == left_turn_available && sensor_3 == right_turn_available && sensor_1 == medium && sensor_4 == medium)
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
               *  
               *  *****
               *  *
               *  *
               *  *
                ^^
  */
  else if ( sensor_1 == far && sensor_4 == far && sensor_3 == right_turn_available && sensor_2 == left_turn_notavailable )
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
  else if (  sensor_1 == far && sensor_4 == far && sensor_3 == right_turn_notavailable && sensor_2 == left_turn_available )
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
  else if ( sensor_2 == left_turn_notavailable && sensor_3 == right_turn_available && sensor_1 == medium && sensor_4 == medium)
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
  else if ( sensor_2 == left_turn_available && sensor_3 == right_turn_notavailable && sensor_1 == medium && sensor_4 == medium)
  {
    // Simply take a left turn
  }
}
