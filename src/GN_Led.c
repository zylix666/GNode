#include "GNode.h"
#include <stdlib.h>

#include <stdio.h>

#include <fcntl.h>

#include <unistd.h>

#include <string.h>

int GN_prepare_leds(int gpio, int direction) {
        char buffer[256];
        int fileHandle;
        int fileMode;

        //Export GPIO
        fileHandle = open("/sys/class/gpio/export", O_WRONLY);

        if(_NG_ == fileHandle)

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

        return(fileHandle);  //This file handle will be used in read/write and close operations.
}

int GN_get_led(int gpio) {
        ///sys/bus/iio/devices/iio\:device0/in_voltage0_raw
        int value;
        char buffer[256];
        FILE *fileHandle;

        sprintf(buffer, "/sys/class/gpio/gpio%d/value", gpio);

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

int GN_set_led(int gpio, int gpioValue) {
        char buffer[256];
        int fileHandle;
       //Open GPIO for Read / Write
        sprintf(buffer, "/sys/class/gpio/gpio%d/value", gpio);

        fileHandle = open(buffer, O_WRONLY);

        if(ERROR == fileHandle)

        {

               puts("Unable to open file:");

               puts(buffer);

               return ERROR;

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

    return _OK_;
}

void GN_release_led(int gpio) {
        char buffer[256];
        int fileHandle;
        fileHandle = open("/sys/class/gpio/unexport", O_WRONLY);
        if(ERROR == fileHandle)
        {
               puts("Unable to open file:");
               puts(buffer);
               return(-1);
        }
        sprintf(buffer, "%d", gpio);
        write(fileHandle, buffer, strlen(buffer));
        close(fileHandle);
        return(0);

}

