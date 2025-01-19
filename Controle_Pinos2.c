#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"

#define GPIO_LED_GREEN 11
#define GPIO_LED_BLUE 12
#define GPIO_LED_RED 13
#define GPIO_BUZZER 21 

// Mapeamento das ações para enviar na UART em escrito
char* MAP_ENTRYS[7] = {
    "ON: RED", "ON: BLUE", "ON: GREEN", "ON: WHITE", "OFF: ALL LEDS", "ON: BUZZER", "ERROR: UNKOWN COMMAND"
};

uint check_entry(){
    uint input;
    //printf("Aguardando entrada...");
    scanf("%d", &input);

    if(input < 7){
        // Manda via UART a mensagem da ação executada e o código referente à ela
        printf("%s\n", MAP_ENTRYS[input - 1]);
        return input;
    
    // Bloco para evitar erros
    } else{
        printf("%s\n", MAP_ENTRYS[6]);
        return 7;
    }
}

void acionar_buzzer() {
    gpio_put(GPIO_BUZZER, 1);  // Liga o buzzer
    sleep_ms(2000);            // Mantenha o buzzer ligado por 2 segundos
    gpio_put(GPIO_BUZZER, 0);  // Desliga o buzzer
}

void desligar_leds(){
    gpio_put(GPIO_LED_RED, false);
    gpio_put(GPIO_LED_GREEN, false);
    gpio_put(GPIO_LED_BLUE, false);
}

void ligar_led_branco(){
    gpio_put(GPIO_LED_RED, true);
    gpio_put(GPIO_LED_GREEN, true);
    gpio_put(GPIO_LED_BLUE, true);
}


int main(){
    stdio_init_all();

    gpio_init(GPIO_LED_RED);
    gpio_init(GPIO_LED_GREEN);
    gpio_init(GPIO_LED_BLUE);
    gpio_set_dir(GPIO_LED_RED, GPIO_OUT);
    gpio_set_dir(GPIO_LED_GREEN, GPIO_OUT);
    gpio_set_dir(GPIO_LED_BLUE, GPIO_OUT);

    gpio_init(GPIO_BUZZER);  // Inicializa o pino do buzzer
    gpio_set_dir(GPIO_BUZZER, GPIO_OUT);  // Configura o buzzer como saída

    while (true){
        uint acao = check_entry();

        switch (acao){
            case 1 :
            desligar_leds();
            gpio_put(GPIO_LED_RED, true);
            break;

            case 2 :
            desligar_leds();
            gpio_put(GPIO_LED_BLUE, true);
            break;

            case 3 :
            desligar_leds();
            gpio_put(GPIO_LED_GREEN, true);
            break;

            case 4 :
            ligar_led_branco();
            break;

            case 5 :
            desligar_leds();
            break;

            case 6 :
            desligar_leds();
            acionar_buzzer();
            break;

            default :
            continue;
        }

        sleep_ms(1000);
    }
}