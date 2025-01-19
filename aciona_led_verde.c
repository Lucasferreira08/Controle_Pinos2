#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "aciona_led_verde.h"

#define GPIO_LED_VERDE 11

// Constante que define o tempo de acionamento do LED VERDE
#define TEMPO_ACIONAMENTO_LED 1000

void setup_led_verde() {
    gpio_init(GPIO_LED_VERDE);
    gpio_set_dir(GPIO_LED_VERDE, GPIO_OUT);
}

void aciona_led_verde() {
    // Chama função de inicialização da GPIO
    setup_led_verde();

    gpio_put(GPIO_LED_VERDE, 1); 
    desligar_leds();
    sleep_ms(TEMPO_ACIONAMENTO_LED);          // Aguarda pelo tempo especificado
}
