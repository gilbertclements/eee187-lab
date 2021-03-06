/*    
 *robot code for Arduino 
 *wheel radius 3.25cm
 *axel length 22cm on center
 *EEE187 Lab activity 3
 *follow black tape line on ground 
 *if black line is in the middle, then go straight 
 *if black line is to the left, then turn left 
 *if black line is to the right, then turn right 
 *if black line is to the left edge, then rotate left 
 *if black line is to the right edge, then rotate right 
 *if all black, then stop 
 *if all white, then reverse
 */ 

#include <NewPing.h>
const float referenceVolts = 5.0; // the default reference on a 5-volt board
const int batteryPin = 5;         // battery is connected to analog pin A5

//right side
#define Right_Motor_DirFW  2   //IN3 pin on driver   green wire 
#define Right_PWM_pin      3   //ENA pin on driver   black wire
#define Right_Motor_DirBW  4   //IN4 pin on driver   purple wire
//left side
#define Left_Motor_DirFW   5   //IN1 pin on driver   white wire
#define Left_PWM_pin       6   //ENB pin on driver   red wire
#define Left_Motor_DirBW   7   //IN2 pin on driver   yellow wire
//define trigger and echo for distance 
#define TRIGGER_PIN  8   // Arduino pin 8 tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     9   // Arduino pin ~9 tied to echo pin on the ultrasonic sensor.

//set SPEED of wheels PWM = 225*(motor_voltage/battery_voltage) 
int SPEED, val;
float volts;

#define SPEED   255*5/9  //motor in   SPEED
#define MAX_DISTANCE 400 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

/*Ground Sensors from left to right */
#define GroundSensor_0 A0
#define GroundSensor_1 A1
#define GroundSensor_2 A2
#define GroundSensor_3 A3
#define GroundSensor_4 A4

char sensor[5];
 /*read sensor value string, 1 stands for black, 0 starnds for white, i.e 10000 means the first sensor(from left) detect black line, other 4 sensors detected white ground */
String read_sensor_values()
{   int sensorvalue=32;
  sensor[0]=digitalRead(GroundSensor_0);
  sensor[1]=digitalRead(GroundSensor_1);
  sensor[2]=digitalRead(GroundSensor_2);
  sensor[3]=digitalRead(GroundSensor_3);
  sensor[4]=digitalRead(GroundSensor_4);
  sensorvalue +=sensor[0]*16+sensor[1]*8+sensor[2]*4+sensor[3]*2+sensor[4];
 
  String senstr= String(sensorvalue,BIN);
  Serial.println(senstr);
  return senstr.substring(1,6);
}

void move_forward(void)  //Forward
{
  digitalWrite(Right_Motor_DirFW,HIGH);
  digitalWrite(Right_Motor_DirBW,LOW);
  digitalWrite(Left_Motor_DirFW, HIGH);
  digitalWrite(Left_Motor_DirBW, LOW);
}
void move_counter_clockwise(void)  //rotate left
{
  digitalWrite(Right_Motor_DirFW,HIGH);
  digitalWrite(Right_Motor_DirBW,LOW);
  digitalWrite(Left_Motor_DirFW, LOW);
  digitalWrite(Left_Motor_DirBW, HIGH);
}
void move_clockwise(void)  //rotate right
{
  digitalWrite(Right_Motor_DirFW,LOW);
  digitalWrite(Right_Motor_DirBW,HIGH);
  digitalWrite(Left_Motor_DirFW, HIGH);
  digitalWrite(Left_Motor_DirBW, LOW);
}
void move_backward(void)  //Reverse
{
  digitalWrite(Right_Motor_DirFW,LOW);
  digitalWrite(Right_Motor_DirBW,HIGH);
  digitalWrite(Left_Motor_DirFW, LOW);
  digitalWrite(Left_Motor_DirBW, HIGH);
}
void all_stop()    //Stop
{
  digitalWrite(Right_Motor_DirFW,LOW);
  digitalWrite(Right_Motor_DirBW,LOW);
  digitalWrite(Left_Motor_DirFW, LOW);
  digitalWrite(Left_Motor_DirBW, LOW);
}
/*set motor SPEED */
void set_SPEED(int SPEED_L,int SPEED_R)
{
  analogWrite(Left_PWM_pin,SPEED_L); 
  analogWrite(Right_PWM_pin,SPEED_R);
  }

void setup()
{
 Serial.begin(115200); // 

 pinMode(Left_PWM_pin,      OUTPUT); //left motor PWM pin
 pinMode(Right_PWM_pin,     OUTPUT); //rignt motor PWM  pin
 pinMode(Right_Motor_DirFW, OUTPUT); //left motor direction pin1
 pinMode(Right_Motor_DirBW, OUTPUT); //left motor direction pin2
 pinMode(Left_Motor_DirFW,  OUTPUT); //right motor direction Pin 1
 pinMode(Left_Motor_DirBW,  OUTPUT);  //right motor direction Pin 2

  /*line follow sensors */
 pinMode(GroundSensor_0,INPUT);
 pinMode(GroundSensor_1,INPUT);
 pinMode(GroundSensor_2,INPUT);
 pinMode(GroundSensor_3,INPUT);
 pinMode(GroundSensor_4,INPUT); 
 Serial.begin(9600);
}

void auto_tracking(){
 String sensorval= read_sensor_values();
 //Serial.println(sensorval);
 if (sensorval=="00100" or sensorval=="01110" or sensorval=="11100" or sensorval=="11110" or sensorval=="01010" or sensorval=="10011" )
 {  //if black line is in the middle, then go straight 
    move_forward(); //straight
    set_SPEED(SPEED,SPEED);
    Serial.print(F(" straight \n")); // 
    delay(100);
    all_stop();
    }
    
 if (sensorval=="01100" or sensorval=="11101" or sensorval=="01000")
 {  //if black line is to the left, then turn left    
    move_counter_clockwise();  //Turn left
    set_SPEED(0,SPEED);
    Serial.print(F(" left \n")); // 
    delay(100);
    all_stop();
    }
    
 if (sensorval=="00110" or sensorval=="00010" or  sensorval=="00111" or sensorval=="10111" or sensorval=="10110" or sensorval=="01101")
 {  //if black line is to the right, then turn right  
    move_clockwise();  //Turn right
    set_SPEED(SPEED,0);
    Serial.print(F(" right \n")); // 
    delay(100);
    all_stop();
    }

 if (sonar.ping_cm() < 15 or sensorval=="00000" or sensorval=="10000" or sensorval=="11000" or sensorval=="11010" or sensorval=="11001" or sensorval=="10100" or sensorval=="10010")
 {  //if black line is to the left, then rotate left    
    move_counter_clockwise();  //Turn left
    set_SPEED(SPEED,SPEED);
    Serial.print(F(" left \n")); // 
    delay(200);
    all_stop();
    }
    
 if (sonar.ping_cm() < 15 or sensorval=="11111" or sensorval=="10001" or sensorval=="00001" or sensorval=="00011" or sensorval=="00101" or sensorval=="01001" or sensorval=="01011" or sensorval=="10101" or sensorval=="11011" or sensorval=="01111")
 {  //if black line is to the right, then rotate right  
    move_clockwise();  //Turn right
    set_SPEED(SPEED,SPEED);
    Serial.print(F(" right \n")); // 
    delay(100);
    all_stop();
    }  
    
 if (sonar.ping_cm() < 15 )
 { //if obstacle less than 15 cm, then stop
    all_stop();
    delay(100);
    all_stop();
    }  
 }

void loop(){
  delay(50);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  Serial.print("Ping: ");
  Serial.print(sonar.ping_cm()); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");
  auto_tracking();
}
