#include <Wire.h> //for the MEMS sensor
#include <SoftwareSerial.h> //for the bluetooth
SoftwareSerial bl(2,3); //for bluetooth
//Declaring some global variables
const int MPU= 0x68; //for the MEMS sensor
int16_t AcX1, AcY1, AcZ1,Tmp,GyX1,GyY1,GyZ1;
int data;
const int flexPin3=A0; //assigning pins to variables
const int flexPin4=A1;
const int flexPin5=A2;

int gesture1_f3 =0; //gesture 1
int gesture1_f4 =0;
int  gesture1_f5 =0;

int gesture2_f3 =0; //gesture 2
int gesture2_f4=0;
int gesture2_f5=0;

int gesture3_f3 =0; //gesture 3
int gesture3_f4=0;
int gesture3_f5=0;

int gesture4_f3 =0; //gesture 4
int gesture4_f4=0;
int gesture4_f5=0;

int gesture5_f3=0; //gesture 5
int gesture5_f4=0;
int gesture5_f5=0;
//setting the tolerance level/range of input to accept
bool inRange(int ref,int recValue, int range)
{
    return((ref -range <= recValue)&&(ref +range >= recValue) );
}
void setup()  //basic setup of the device
{
  Wire.begin();  //initializing the MPU
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.begin(9600); //for serial communication
    bl.begin(9600); //for Bluetooth with 9600 baud rate
  pinMode(flexPin3,INPUT); //setting the sensor input
  pinMode(flexPin4,INPUT);
  pinMode(flexPin5,INPUT);
}
 
void loop() 
{
  if(bl.available() > 0) //if bluetooth data is available
    {
      if (char(bl.read())=='c') //beginning calibration
      {
      bl.println("Calibration Mode !");
      bl.println("Open your Fingers");
        while(char(bl.read())!= 'q') //storing the values of the gestures
        {
            gesture1_f3=analogRead(flexPin3);
            gesture1_f4=analogRead(flexPin4);
            gesture1_f5=analogRead(flexPin5);
              }
        while(char(bl.read())!= 'r')
        {
          gesture2_f3=analogRead(flexPin3);
          gesture2_f4=analogRead(flexPin4);
            gesture2_f5=analogRead(flexPin5);
        } 
          while(char(bl.read())!= 's')
        {
          gesture3_f3=analogRead(flexPin3);
          gesture3_f4=analogRead(flexPin4);
            gesture3_f5=analogRead(flexPin5);
         } 
          while(char(bl.read())!= 't')
          {
                gesture4_f3=analogRead(flexPin3);
                gesture4_f4=analogRead(flexPin4);
                     gesture4_f5=analogRead(flexPin5);
           }
       while(char(bl.read())!= 'i')
      {
               gesture5_f3=analogRead(flexPin3);
                    gesture5_f4=analogRead(flexPin4);
                    gesture5_f5=analogRead(flexPin5);
     }
      bl.println("Calibration mode Ended ");
      delay(2000);
   }    
 }
if(inRange(gesture1_f3,analogRead(flexPin3),10)&&inRange(gesture1_f4,analogRead(flexPin4),10)&&inRange(gesture1_f5,analogRead(flexPin5),10))
{ //if a particular gesture is made send a selected value
  for( int i = 0; i<=5;i++)
    {
      bl.println("1");
      bl.flush();
      delay(20);
   }
}
else if(inRange(gesture2_f3,analogRead(flexPin3),10)&&inRange(gesture2_f4,analogRead(flexPin4),10)&&inRange(gesture2_f5,analogRead(flexPin5),10))
{
  for( int i = 0; i<=5;i++)
    {
      bl.println("2");
      bl.flush();
     delay(20);
   }
 }
if(inRange(gesture3_f3,analogRead(flexPin3),10)&&inRange(gesture3_f4,analogRead(flexPin4),10)&&inRange(gesture3_f5,analogRead(flexPin5),10))
{
for( int i = 0; i<=5;i++)
    {
      bl.println("3");
      bl.flush();
      delay(20);
    }
}
else if(inRange(gesture4_f3,analogRead(flexPin3),10)&&inRange(gesture4_f4,analogRead(flexPin4),10)&&inRange(gesture4_f5,analogRead(flexPin5),10))
{ 
  for( int i = 0; i<=5;i++)
    {
       bl.println("4");
       bl.flush();
      delay(20);
    }
}   if(inRange(gesture5_f3,analogRead(flexPin3),10)&&inRange(gesture5_f4,analogRead(flexPin4),10)&&inRange(gesture5_f5,analogRead(flexPin5),10))
{ //this gesture activates the MPU sensor
for( int i = 0; i<=5;i++)
    {
      bl.println("5");
      bl.flush();
      delay(20);
      GetMpuValue(MPU);
    sentunity();
    }
   }
}

void GetMpuValue (const int MPU) //getting the MPU value
{
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,14,true);
  AcX1= Wire.read() <<8| Wire.read(); //reads accelerometer
  AcY1= Wire.read() <<8| Wire.read();
  AcZ1= Wire.read() <<8| Wire.read();
  Tmp = Wire.read() <<8| Wire.read(); 
  GyX1= Wire.read() <<8| Wire.read(); //reads gyroscope
  GyY1= Wire.read() <<8| Wire.read();
  GyZ1= Wire.read() <<8| Wire.read();
}
void sentunity() //sending the values to the unity using bluetooth
{
if(bl.available())
    {
        data = bl.read();
       if(data == 'a')
        {
            bl.println(AcX1);
            bl.flush();
            delay(25);
       }
       if(data == 'b')
       {
           bl.println(AcY1);
            bl.flush();
            delay(25);
        }
        if(data == 'd')
        {
            bl.println(AcZ1);
            bl.flush();
            delay(25);
                     }
        if(data == 'e')
        {
            bl.println(GyX1);
            bl.flush();
            delay(25);
        }
        if(data == 'f')
        {
           bl.println(GyY1);
            bl.flush();
            delay(25);
        }
        if(data == 'g')
        {
           bl.println(GyZ1);
            bl.flush();
            delay(25);
 }
 }
} 
