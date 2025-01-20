#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "pico/bootrom.h"

#define LED_GREEN 11
#define LED_BLUE 12
#define LED_RED 13
#define BUZZER 21

void setup() {
    gpio_init(LED_GREEN);
    gpio_set_dir(LED_GREEN, GPIO_OUT);
    gpio_init(LED_BLUE);
    gpio_set_dir(LED_BLUE, GPIO_OUT);
    gpio_init(LED_RED);
    gpio_set_dir(LED_RED, GPIO_OUT);

    gpio_set_function(BUZZER, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(BUZZER);
    pwm_set_wrap(slice_num, 255);
    pwm_set_clkdiv(slice_num, 2.0f); // Ajuste a frequência do PWM
    pwm_set_gpio_level(BUZZER, 0);
    pwm_set_enabled(slice_num, true);
}


void control_leds(char key) {
    static char last_key = 0;

    if (key != last_key) {
        switch (key) {
            case 'r':
                gpio_put(LED_RED, 1);
                gpio_put(LED_GREEN, 0);
                gpio_put(LED_BLUE, 0);
                printf("Red\n");
                break;
            case 'g':
                gpio_put(LED_RED, 0);
                gpio_put(LED_GREEN, 1);
                gpio_put(LED_BLUE, 0);
                printf("Green\n");
                break;
            case 'b':
                gpio_put(LED_RED, 0);
                gpio_put(LED_GREEN, 0);
                gpio_put(LED_BLUE, 1);
                printf("Blue\n");
                break;
            case 'w':
                gpio_put(LED_RED, 1);
                gpio_put(LED_GREEN, 1);
                gpio_put(LED_BLUE, 1);
                printf("White\n");
                break;

            case 'o':
                gpio_put(LED_RED, 0);
                gpio_put(LED_GREEN, 0);
                gpio_put(LED_BLUE, 0);
                printf("Off\n");
                break;
            case 'q':
                printf("Reboot\n");
                reset_usb_boot(0, 0);
                break;
            case 'z':
                gpio_put(LED_RED, 0);
                gpio_put(LED_GREEN, 0);
                gpio_put(LED_BLUE, 0);
                printf("Buzzer\n");
                pwm_set_gpio_level(BUZZER, 192); 
                sleep_ms(2000);
                pwm_set_gpio_level(BUZZER, 0);
                break;  
            default:
                break;
        }
        last_key = key;
    }
}

int main()
{
    stdio_init_all();
    setup();

    while (true) {
        char key = getchar_timeout_us(1000);
        if (key != PICO_ERROR_TIMEOUT) {
            control_leds(key);
        }
    }
}
