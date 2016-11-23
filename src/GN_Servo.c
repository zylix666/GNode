#include "GNode.h"

int openPWM(int channel)
{
        char buffer[256];
        int fileHandle;
        int fileMode;

        //Export GPIO
        fileHandle = open("/sys/class/pwm/pwmchip0/export", O_WRONLY);

        if(ERROR == fileHandle)

        {
               puts("Error: Unable to opening /sys/class/gpio/export");
               return(-1);
        }
        sprintf(buffer, "%d", channel);
        write(fileHandle, buffer, strlen(buffer));
        close(fileHandle);
        sleep(1);
        return 0;
}

int enablePWM(int enable,int channel)
{
                char buffer[256];

                int fileHandle;


                //Enable PWM
        sprintf(buffer, "/sys/class/pwm/pwmchip0/pwm%d/enable", channel);
        fileHandle = open(buffer, O_WRONLY);
        if(ERROR == fileHandle)
        {
               puts("Unable to open file:");

               puts(buffer);

               return(-1);

        }

                sprintf(buffer, "%d", enable);
        write(fileHandle, buffer, strlen(buffer));
        return 0;
}

int setPWMPeriod(int period, int channel)
{
       //Open GPIO for Read / Write
                char buffer[256];
                int fileHandle;


                sprintf(buffer, "/sys/class/pwm/pwmchip0/pwm%d/period", channel);

        fileHandle = open(buffer, O_WRONLY);
        if(ERROR == fileHandle)
        {
               puts("Unable to open file:");

               puts(buffer);

               return(-1);
        }
                sprintf(buffer, "%d", period);
        write(fileHandle, buffer, strlen(buffer));

        close(fileHandle);
        return(0);

}

int setPWMDutyCycle(int dutycycle, int channel)
{
       //Open GPIO for Read / Write
                char buffer[256];
                int fileHandle;


                sprintf(buffer, "/sys/class/pwm/pwmchip0/pwm%d/duty_cycle", channel);

        fileHandle = open(buffer, O_WRONLY);
        if(ERROR == fileHandle)
        {
               puts("Unable to open file:");

               puts(buffer);

               return(-1);
        }
                sprintf(buffer, "%d", dutycycle);
        write(fileHandle, buffer, strlen(buffer));
        close(fileHandle);
        return(0);

}

int GN_prepare_servo(int channel, int period, int duty_cycle){
	openPWM(channel);
        setPWMPeriod(period,channel);
	setPWMDutyCycle(duty_cycle,channel);
	enablePWM(0,channel);  //disable first
}

int GN_enable_servo(int channel){
	enablePWM(1, channel);
}

int GN_disable_servo(int channel){
	sleep(1);
	enablePWM(0, channel);
}
