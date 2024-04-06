#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

 

 int TDS_SENSOR_PIN = A1;
  int sensor_in = A2;
 
float calibration_value = 25.34 - 0.7;
int phval = 0; 
unsigned long int avgval; 
int buffer_arr[10],temp;
 
float ph_act;
// for the OLED display
 

 
void setup() 
{
  Wire.begin();
 Serial.begin(9600);
   
}
void loop() {
  
 for(int i=0;i<10;i++) 
 { 
 buffer_arr[i]=analogRead(A0);
 delay(30);
 }
 for(int i=0;i<9;i++)
 {
 for(int j=i+1;j<10;j++)
 {
 if(buffer_arr[i]>buffer_arr[j])
 {
 temp=buffer_arr[i];
 buffer_arr[i]=buffer_arr[j];
 buffer_arr[j]=temp;
 }
 }
 }
 avgval=0;
 for(int i=2;i<8;i++)
 avgval+=buffer_arr[i];
 float volt=(float)avgval*5.0/1024/6; 
  ph_act = -5.70 * volt + calibration_value;
//  Serial.print(ph_act);
 delay(500);


//  int sensorValue = analogRead(sensor_in); // read the input on analog pin A0
//  float turb = sensorValue * (5.0 / 1024.0); // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V)
//  // print out the value you read
//  Serial.println(turb);
//  delay(1000);
 int sensorValue = analogRead(TDS_SENSOR_PIN);

  // Convert analog value to TDS using a calibration factor
  float tdsValue = map(sensorValue, 0, 1023, 0, 5000); // Adjust the mapping based on your sensor's characteristics

  // Print the TDS value to the Serial Monitor
// Serial.print("TDS Value: ");
//  Serial.println(tdsValue);

  delay(500);
  
  int turbValue = analogRead(sensor_in); // read the input on analog pin A0
  float turb = turbValue * (5.0 / 1024.0); // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V)
  // print out the value you read
//  Serial.println(turb);
//  delay(500);
 
// Serial.println("pH Val: ");
 

 if(ph_act>=6 && ph_act<=8 && tdsValue>=50 && tdsValue<=1200)
 {
  Serial.println("this water can be portable");
}
else
{
   Serial.println("this water can be portable");
}
}
