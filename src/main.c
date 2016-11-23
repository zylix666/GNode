#include <stdio.h>
#include <string.h>

#include "GNode.h"

int main(int argc, char** argv) {
    //
	// Unit test goes here...
    //

	GN_prepare_light_sensor();

	int i;
        int led_status;

	for (i = 0; i < 10; i++) {
		printf("Light Sensor reads: %d\n", GN_get_light_sensor());
	}

	GN_release_light_sensor();
        led_status = GN_prepare_leds(16, 0);
        if(led_status == -1)
            return -1;
        else{
            led_status = GN_get_led(16);
            printf("LED current status is %d\n", led_status);
            if(led_status == 0)
                   GN_set_led(16,1);
            else
                   GN_set_led(16, 0);
        }
	//Play Servo motor test
	GN_prepare_servo(1, 50000000, 1900000);
	printf("Now raise the door\n");
	GN_enable_servo(1);
      	GN_disable_servo(1);
	//Now turn the Servo back
	GN_prepare_servo(1, 50000000, 2500000);
        printf("Now put down the door\n");
        GN_enable_servo(1);
        GN_disable_servo(1);
    return 0;
}
