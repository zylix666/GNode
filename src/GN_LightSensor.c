#include "GNode.h"

static int openGPIO(int gpio, int direction,int gpioValue)
{
        char buffer[256];
        int fileHandle;
        int fileMode;

        //Export GPIO
        fileHandle = open("/sys/class/gpio/export", O_WRONLY);

        if(ERROR == fileHandle)

        {
               puts("Error: Unable to opening /sys/class/gpio/export");
               return(-1);
        }
        sprintf(buffer, "%d", gpio);
        write(fileHandle, buffer, strlen(buffer));
        close(fileHandle);

        //Direction GPIO
        sprintf(buffer, "/sys/class/gpio/gpio%d/direction", gpio);
        fileHandle = open(buffer, O_WRONLY);
        if(ERROR == fileHandle)
        {
               puts("Unable to open file:");

               puts(buffer);

               return(-1);

        }

        if (direction == GPIO_DIRECTION_OUT)

        {
               // Set out direction
               write(fileHandle, "out", 3);
               fileMode = O_WRONLY;
        }

        else

        {
               // Set in direction
               write(fileHandle, "in", 2);
               fileMode = O_RDONLY;
        }

        close(fileHandle);

       //Open GPIO for Read / Write
        sprintf(buffer, "/sys/class/gpio/gpio%d/value", gpio);

        fileHandle = open(buffer, fileMode);

        if(ERROR == fileHandle)

        {

               puts("Unable to open file:");

               puts(buffer);

               return(-1);

        }

        if(gpioValue ==  0)

        {
               // Set GPIO low status
               write(fileHandle, "0", 1);
        }
        else

        {
               // Set GPIO high status
               write(fileHandle, "1", 1);

        }

        return(fileHandle);  //This file handle will be used in read/write and close operations.

}

static int readAnalogIn(int port)
{
	///sys/bus/iio/devices/iio\:device0/in_voltage0_raw
        int value;
        char buffer[256];
        FILE *fileHandle;

        sprintf(buffer, "/sys/bus/iio/devices/iio\:device0/in_voltage%d_raw", port);

        fileHandle = fopen(buffer, "r+");
        if(NULL == fileHandle)
        {
    	   puts("Unable to open file:");
    	   puts(buffer);
    	   return(-1);
        }
        fscanf(fileHandle, "%d", &value);
        fclose(fileHandle);  //This file handle will be used in read/write and close operations.
        return value;
}

int GN_prepare_light_sensor() {
        int fileHandleGPIO_ANALOG_A1;

        fileHandleGPIO_ANALOG_A1 = openGPIO(GP_ANALOG_IN_A0, GPIO_DIRECTION_OUT,0);
        if(ERROR ==  fileHandleGPIO_ANALOG_A1)
        {
                        puts("Unable to open toggle Proximity port #8");
                        return(-1);
        }

	return 0;
}

int GN_get_light_sensor() {
        int analogValue = 0;
        //float degree = 0;
        analogValue = readAnalogIn(1);
	return analogValue;
}

void GN_release_light_sensor() {
	
}
