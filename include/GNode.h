#include <stdlib.h>

#include <stdio.h>

#include <fcntl.h>

#include <unistd.h>

#include <string.h>

#define _OK_ (0)
#define _NG_ (-1)
#define ERROR (-1)

#define GPIO_DIRECTION_OUT      (0)
#define GPIO_DIRECTION_IN       (1)
#define GP_ANALOG_IN_A0         (37) // Thermal sensor
#define GP_ANALOG_IN_A1         (36) // Light sensor

#define GP_PWM_3                (4) // PWM3  is PWM output
#define GP_PWM_1                (1) // PWM3  is PWM output


int GN_prepare_light_sensor();
int GN_get_light_sensor();
void GN_release_light_sensor();
int GN_prepare_thermistor();
float GN_get_thermistor();
void GN_release_thermistor();
int GN_prepare_leds(int gpio, int direction);
int GN_get_led(int gpio);
int GN_set_led(int gpio, int gpioValue);
void GN_release_led(int gpio);

int GN_prepare_servo(int channel, int period, int duty_cycle);
int GN_enable_servo(int channel);
int GN_disable_servo(int channel);
