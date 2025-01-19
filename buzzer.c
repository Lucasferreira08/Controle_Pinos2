#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"

// UART defines
#define UART_ID uart1
#define BAUD_RATE 115200

// Define pinos para UART1
#define UART_TX_PIN 4
#define UART_RX_PIN 5

#define GPIO_LED_GREEN 11
#define GPIO_LED_BLUE 12
#define GPIO_LED_RED 13
#define GPIO_BUZZER 21 // Definir o pino do buzzer

void desligar_leds() {
    gpio_put(GPIO_LED_RED, false);
    gpio_put(GPIO_LED_GREEN, false);
    gpio_put(GPIO_LED_BLUE, false);
}

void acionar_buzzer() {
    gpio_put(GPIO_BUZZER, 1);  // Liga o buzzer
    sleep_ms(2000);            // Mantenha o buzzer ligado por 2 segundos
    gpio_put(GPIO_BUZZER, 0);  // Desliga o buzzer
}

int main() {
    stdio_init_all();

    gpio_init(GPIO_LED_RED);
    gpio_init(GPIO_LED_GREEN);
    gpio_init(GPIO_LED_BLUE);
    gpio_init(GPIO_BUZZER);  // Inicializa o pino do buzzer
    gpio_set_dir(GPIO_LED_RED, GPIO_OUT);
    gpio_set_dir(GPIO_LED_GREEN, GPIO_OUT);
    gpio_set_dir(GPIO_LED_BLUE, GPIO_OUT);
    gpio_set_dir(GPIO_BUZZER, GPIO_OUT);  // Configura o buzzer como saída

    // Configuração da UART
    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

    // Mensagem inicial na UART
    uart_puts(UART_ID, "Hello, UART!\n");

    // Buffer para armazenar o comando recebido
    char rx_buffer[64];
    int buffer_index = 0;

    while (true) {
        while (uart_is_readable(UART_ID)) {
            char ch = uart_getc(UART_ID); // Lê o próximo caractere
            if (ch == '\n' || ch == '\r') {
                // Final do comando recebido
                rx_buffer[buffer_index] = '\0'; // Termina a string
                buffer_index = 0;               // Reinicia o índice do buffer

                // Verifica o comando recebido
                if (strcmp(rx_buffer, "off") == 0) {
                    desligar_leds();
                    uart_puts(UART_ID, "Comando recebido: OFF\n");
                }
                else if (strcmp(rx_buffer, "buzz") == 0) {
                    acionar_buzzer();
                    uart_puts(UART_ID, "Comando recebido: BUZZ\n");
                }
            } else {
                // Armazena o caractere no buffer se não for o final da linha
                if (buffer_index < sizeof(rx_buffer) - 1) {
                    rx_buffer[buffer_index++] = ch;
                }
            }
        }
    }
}
