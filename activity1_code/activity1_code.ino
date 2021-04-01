/*    
 *robot code for Arduino 
 *wheele radius 3.25cm
 *axel length 22cm on center
 *EEE187 Lab activity 1 ROBOT CAR MOVE FORWARD, BACKWARD, LEFT, RIGHT
 */

//left side
#define Left_PWM_pin         6   //ENB pin on driver     red wire
#define Left_Motor_DirPin1   7   //IN1 pin on driver     yellow wire
#define Left_Motor_DirPin2   2   //IN2 pin on driver     white wire
//right side
#define right_PWM_pin        5   //ENA pin on driver   black wire
#define Right_Motor_DirPin1  3   //IN3 pin on driver   purple wire
#define Right_Motor_DirPin2  4   //IN4 pin on driver   green wire

//set speed of wheeles PWM = 225*(motor_voltage/battery_voltage) 
int speed = 255*(6/8);

/*define motor control*/
void move_forward(void)  //forward
{
  digitalWrite(Right_Motor_DirPin1, HIGH);
  digitalWrite(Right_Motor_DirPin2,LOW);
  digitalWrite(Left_Motor_DirPin1,HIGH);
  digitalWrite(Left_Motor_DirPin2,LOW);
  analogWrite(Left_PWM_pin,speed);
  analogWrite(right_PWM_pin,speed);
}
void move_backward(int t=0)  //backward
{
  digitalWrite(Right_Motor_DirPin1, LOW);
  digitalWrite(Right_Motor_DirPin2,HIGH);
  digitalWrite(Left_Motor_DirPin1,LOW);
  digitalWrite(Left_Motor_DirPin2,HIGH);
  analogWrite(Left_PWM_pin,speed);
  analogWrite(right_PWM_pin,speed);
  delay(t);
}
void move_counter_clockwise(int t=0)  //rotate counter clockwise <<<<
{
  digitalWrite(Right_Motor_DirPin1, HIGH);
  digitalWrite(Right_Motor_DirPin2,LOW);
  digitalWrite(Left_Motor_DirPin1,LOW);
  digitalWrite(Left_Motor_DirPin2,HIGH);
  analogWrite(Left_PWM_pin,speed);
  analogWrite(right_PWM_pin,speed);
  delay(t);
}
void move_clockwise(int t=0)  //rotate clockwise >>>>
{
  digitalWrite(Right_Motor_DirPin1, LOW);
  digitalWrite(Right_Motor_DirPin2,HIGH);
  digitalWrite(Left_Motor_DirPin1,HIGH);
  digitalWrite(Left_Motor_DirPin2,LOW);
  analogWrite(Left_PWM_pin,speed);
  analogWrite(right_PWM_pin,speed);
  delay(t);
}
void move_left_fw(int t=0)  //turning left forward<<
{
  digitalWrite(Right_Motor_DirPin1, LOW);
  digitalWrite(Right_Motor_DirPin2,HIGH);
  digitalWrite(Left_Motor_DirPin1,HIGH);
  digitalWrite(Left_Motor_DirPin2,LOW);
  analogWrite(Left_PWM_pin,speed);
  analogWrite(right_PWM_pin,0);
  delay(t);
}
void move_right_fw(int t=0)  //turning right forward>>
{
  digitalWrite(Right_Motor_DirPin1, HIGH);
  digitalWrite(Right_Motor_DirPin2,LOW);
  digitalWrite(Left_Motor_DirPin1,LOW);
  digitalWrite(Left_Motor_DirPin2,HIGH);
  analogWrite(Left_PWM_pin,0);
  analogWrite(right_PWM_pin,speed);
  delay(t);
}
void move_left_bk(int t=0)  //turning left back<<
{
  digitalWrite(Right_Motor_DirPin1, HIGH);
  digitalWrite(Right_Motor_DirPin2,LOW);
  digitalWrite(Left_Motor_DirPin1,LOW);
  digitalWrite(Left_Motor_DirPin2,HIGH);
  analogWrite(Left_PWM_pin,speed);
  analogWrite(right_PWM_pin,0);
  delay(t);
}
void move_right_bk(int t=0)  //turning right back>>
{
  digitalWrite(Right_Motor_DirPin1, LOW);
  digitalWrite(Right_Motor_DirPin2,HIGH);
  digitalWrite(Left_Motor_DirPin1,HIGH);
  digitalWrite(Left_Motor_DirPin2,LOW);
  analogWrite(Left_PWM_pin,0);
  analogWrite(right_PWM_pin,speed);
  delay(t);
}
void all_stop()    //dont move
{
  digitalWrite(Right_Motor_DirPin1, LOW);
  digitalWrite(Right_Motor_DirPin2,LOW);
  digitalWrite(Left_Motor_DirPin1,LOW);
  digitalWrite(Left_Motor_DirPin2,LOW);
}
/* set motor speed */
void set_Motorspeed(int speed_L,int speed_R)
{
  analogWrite(Left_PWM_pin,speed_L); 
  analogWrite(right_PWM_pin,speed_R);   
}

// initialize Pins
void init_GPIO()
{
	pinMode(Right_Motor_DirPin1, OUTPUT); 
	pinMode(Right_Motor_DirPin2, OUTPUT); 
	pinMode(Left_PWM_pin, OUTPUT);  
 
	pinMode(Left_Motor_DirPin1, OUTPUT);
  pinMode(Left_Motor_DirPin2, OUTPUT); 
  pinMode(right_PWM_pin, OUTPUT); 
	all_stop();
}

void setup()
{
	init_GPIO();
	move_forward();//forward
  delay(2000);
  
  all_stop();//Stop
  delay(2000);
  
  move_backward();//backward
  delay(2000);
  
  all_stop();//Stop
  delay(2000);
  
  move_counter_clockwise();//rotate counter clockwise
  delay(2000);

  move_clockwise();//rotate clockwise
  delay(2000);

  all_stop();//Stop
  delay(2000);

  move_left_fw();//turning left forward
  delay(2000);
  
  move_right_fw();//truning right forward
  delay(2000);

  move_left_bk();  //turning left back<<
  delay(2000);
  
  move_right_bk();  //turning right back>>
  delay(2000);

  all_stop();//Stop

}
void loop(){
}
