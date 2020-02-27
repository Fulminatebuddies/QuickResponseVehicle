String sensor_1_data;
String sensor_2_data;
void setup() {
  Serial.begin(19200);
  pinMode (13, OUTPUT);
  pinMode (12, OUTPUT);
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  // this is the first test run for protocol
  //lets say this is the moiment you want the data to arrive
  //IC 1 STARTS
  digitalWrite (13, LOW); //801
  digitalWrite(13, HIGH);
  delay(10);
  //now the interpt has been set. the data should start coming
  if (Serial.available() > 0)
    sensor_1_data = Serial.readStringUntil('t');
  Serial.print(sensor_1_data);
  Serial.println(" IC 1");
  serialFlush();
  //IC 1 ENDS

  //IC 2 STARTS
  digitalWrite (12, LOW); //102
  digitalWrite(12, HIGH);
  delay(10);
  //now the interpt has been set. the data should start coming
  if (Serial.available() > 0)
    sensor_2_data = Serial.readStringUntil('t');
  Serial.print(sensor_2_data);
  Serial.println(" IC 2");
  serialFlush();
  //IC 2 ENDS
}

void serialFlush() {
  while (Serial.available() > 0) {
    char t = Serial.read();
  }
  sensor_1_data = "0";
  sensor_2_data = "0";
}
