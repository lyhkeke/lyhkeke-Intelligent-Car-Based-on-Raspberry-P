#include <wiringPi.h>
#include <softTone.h>
#include <softPwm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <time.h>
#include <arpa/inet.h> 

const int LEDpin1 = 22;
const int LEDpin2 = 21;
const int PWMA = 1;
const int AIN1 = 3;
const int AIN2 = 2;
const int PWMB = 4;
const int BIN1 = 6;
const int BIN2 = 5;

void led()
{
     
      int i;
      for(i=0;i<5;i++)
      {
            
            digitalWrite(LEDpin1,HIGH);
            delay(600);
            digitalWrite(LEDpin1,LOW);
            digitalWrite(LEDpin2,HIGH);
            delay(600);
            digitalWrite(LEDpin2,LOW);
      }
      
}
void forward()//前进
{
      softPwmWrite(PWMA,50);
      digitalWrite(AIN1,HIGH);
      softPwmWrite(PWMB,50);
      digitalWrite(BIN1,HIGH);
      delay(600);
      softPwmWrite(PWMA,0);
      digitalWrite(AIN1,LOW);
      softPwmWrite(PWMB,0);
      digitalWrite(BIN1,LOW);
      delay(600);
}
void retreat()// 后退
{
      softPwmWrite(PWMA,50);
      digitalWrite(AIN2,HIGH);
      softPwmWrite(PWMB,50);
      digitalWrite(BIN2,HIGH);
      delay(200);
      softPwmWrite(PWMA,0);
      digitalWrite(AIN2,LOW);
      softPwmWrite(PWMB,0);
      digitalWrite(BIN2,LOW);
      delay(600);
}
void left()// 原地左拐
{
      softPwmWrite(PWMA,50);
      digitalWrite(AIN2,HIGH);
      softPwmWrite(PWMB,50);
      digitalWrite(BIN1,HIGH);
      delay(100);
      softPwmWrite(PWMA,0);
      digitalWrite(AIN2,LOW);
      softPwmWrite(PWMB,0);
      digitalWrite(BIN1,LOW);
      delay(600);
}
void right()// 原地右拐
{
      softPwmWrite(PWMA,50);
      digitalWrite(AIN1,HIGH);
      softPwmWrite(PWMB,50);
      digitalWrite(BIN2,HIGH);
      delay(100);
      softPwmWrite(PWMA,0);
      digitalWrite(AIN1,LOW);
      softPwmWrite(PWMB,0);
      digitalWrite(BIN2,LOW);
      delay(600);
}
void w_left()// 左拐
{
      softPwmWrite(PWMA,50);
      digitalWrite(AIN1,HIGH);
      softPwmWrite(PWMB,100);
      digitalWrite(BIN1,HIGH);
      delay(1500);
      softPwmWrite(PWMA,0);
      digitalWrite(AIN1,LOW);
      softPwmWrite(PWMB,0);
      digitalWrite(BIN1,LOW);
      delay(600);
}
void w_right()// 右拐
{
      softPwmWrite(PWMA,100);
      digitalWrite(AIN1,HIGH);
      softPwmWrite(PWMB,50);
      digitalWrite(BIN1,HIGH);
      delay(1500);
      softPwmWrite(PWMA,0);
      digitalWrite(AIN1,LOW);
      softPwmWrite(PWMB,0);
      digitalWrite(BIN1,LOW);
      delay(600);
}
int main()
{
      //检测端口是否有故障
      if(-1==wiringPiSetup())
      {
   
            printf("etup error\n");
            exit(-1);
      }
      //注册中断处理函数
      
      //配置端口
      pinMode(LEDpin1,OUTPUT);   
      pinMode(LEDpin2,OUTPUT);   
      pinMode(PWMA,OUTPUT); 
      pinMode(AIN1,OUTPUT); 
      pinMode(AIN2,OUTPUT); 
      pinMode(PWMB,OUTPUT); 
      pinMode(BIN1,OUTPUT); 
      pinMode(BIN2,OUTPUT); 
      softPwmCreate(PWMA,0,100);
      softPwmCreate(PWMB,0,100);
      //led();
      /*
      forward();//前进
      retreat();//后退
      left();// 左拐
      right();// 右拐
      */
      char mv;
      (void)mv;
      while(1)
      {
            //避障
            if((digitalRead (27)==LOW)&&(digitalRead (26)==HIGH))
            {
                  right();
                  printf("right\n");
            }
            if((digitalRead (27)==HIGH)&&(digitalRead (26)==LOW))
            {
                  left();
                  printf("left\n");
            }
            if((digitalRead (27)==LOW)&&(digitalRead (26)==LOW))
            {
                  printf("retreat\n");
                  retreat();
            }
            if((digitalRead (27)==HIGH)&&(digitalRead (26)==HIGH))
            {
                  printf("forward\n");
                  forward();
            }
            delay(500)；
      }
      //end
      printf("---------OVER-----------\n");
      return 0;   
}
