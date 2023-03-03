#include "../include/setup.h"
#include "SEGGER_RTT_printf.c"
int debug = 1;

// Basic Variables
int ready = 0;

// Semaphores
K_SEM_DEFINE(move_to_pos_sem, 0, 1);
K_SEM_DEFINE(fill_glass_sem, 0, 1);
K_SEM_DEFINE(drink_sem, 0, 1);
K_SEM_DEFINE(cocktail_sem, 0, 1);

// Queue
K_QUEUE_DEFINE(position_q);
K_QUEUE_DEFINE(amount_q);

// GPIOS
const struct gpio_dt_spec dir_hor_spec = GPIO_DT_SPEC_GET(DT_NODELABEL(dir_hor), gpios);
const struct gpio_dt_spec step_hor_spec = GPIO_DT_SPEC_GET(DT_NODELABEL(step_hor), gpios);
const struct gpio_dt_spec dir_ver_spec = GPIO_DT_SPEC_GET(DT_NODELABEL(dir_ver), gpios);
const struct gpio_dt_spec step_ver_spec = GPIO_DT_SPEC_GET(DT_NODELABEL(step_ver), gpios);

const struct gpio_dt_spec limit_sw_hor0_spec = GPIO_DT_SPEC_GET(DT_NODELABEL(limit_sw_hor0), gpios);
const struct gpio_dt_spec limit_sw_ver0_spec = GPIO_DT_SPEC_GET(DT_NODELABEL(limit_sw_ver0), gpios);


// Status LEDs
const struct gpio_dt_spec green = GPIO_DT_SPEC_GET(DT_NODELABEL(green_led_4), gpios);
const struct gpio_dt_spec red = GPIO_DT_SPEC_GET(DT_NODELABEL(red_led_5), gpios);
const struct gpio_dt_spec blue = GPIO_DT_SPEC_GET(DT_NODELABEL(blue_led_6), gpios);

void setup(void){

    gpio_pin_configure_dt(&dir_hor_spec, GPIO_OUTPUT_INACTIVE);
    gpio_pin_configure_dt(&step_hor_spec, GPIO_OUTPUT_INACTIVE);
    gpio_pin_configure_dt(&dir_ver_spec, GPIO_OUTPUT_INACTIVE);
    gpio_pin_configure_dt(&step_ver_spec, GPIO_OUTPUT_INACTIVE);

    gpio_pin_configure_dt(&limit_sw_hor0_spec, GPIO_INPUT);
    gpio_pin_configure_dt(&limit_sw_ver0_spec, GPIO_INPUT);

    gpio_pin_configure_dt(&green, GPIO_OUTPUT_INACTIVE);    
    gpio_pin_configure_dt(&red, GPIO_OUTPUT_INACTIVE);
    gpio_pin_configure_dt(&blue, GPIO_OUTPUT_INACTIVE);

}

void set_status_led(int status){    

    gpio_pin_set_dt(&green, 0);
    gpio_pin_set_dt(&red, 0);
    gpio_pin_set_dt(&blue, 0);

    switch (status){
        case STATUS_OK:
            gpio_pin_set_dt(&green, 1);
            break;

        case STATUS_ERROR:
            gpio_pin_set_dt(&red, 1);
            break;

        case STATUS_BLOCKED:
            gpio_pin_set_dt(&blue, 1);
            break;

        default:
            break;
    }
}

