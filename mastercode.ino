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
}

void loop() {
  // put your main code here, to run repeatedly:
/* This is the third time i am writing this comment so bear with me if this explanation is boaring.
 * NOw for the forward sensor there are 3 settings
 * If the distance is in between object and sensor is between 10cm and 5 cm i.e sensor value is in between 1023 and 511 the sensor is said to be in far position 
 * If the distance is in between object and sensor is between 5cm and 2 cm i.e sensor value is in between 510 and 240 the sensor is said to be in medium position 
 * If the distance is in between object and sensor is between 10cm and 5 cm i.e sensor value is in between 239 and 51 the sensor is said to be in zaval position
 * 
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
 * these sensors ideally will always detect something because the road the robot will follow will almost be enclosed
 * So in this case, for sensor 2 and sensor 3 we have to detect if there is a free turn.
 * 
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
// now lets explore conditions where the bot has to make decisions 
//First lets start with staright condition
//Depending upon the condition of sensor lets decide the speed of motor.
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
//Now what if the path has a left turn 
//UNtil the path detects a left turn the above straight path loop will go on 
else if ( sensor_2 == left_turn_available && sensor_3 == right_turn_notavailable)
{

}
}
