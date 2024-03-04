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
 
 
const int PWMLED1=22;//yellow
const int PWMLED2=21;//red
 
int main (void)
{
      wiringPiSetup ();               // wiringPi库初始化
      softPwmCreate (PWMLED1, 0, 100) ;   // 设置yellow为PWM输出 
      softPwmCreate (PWMLED2, 0, 100) ;   // 设置red为PWM输出    
   
    int val = 0;
    int step = 1;
    while(1)
    {
      val+= step ;
      if(val >= 100)
      {
            step = -step;
      }
      if(val <= 0)
      {
            step= -step;
      }
      softPwmWrite(PWMLED1,val); // 输出占空比为val/100的pwm波
      delay(20); // 延时3毫秒
  }
  return 0 ;
}