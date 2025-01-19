#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "aciona_led_verde.h"

// update cmakelist

// UART defines
// By default the stdout UART is `uart0`, so we will use the second one
#define UART_ID uart1
#define BAUD_RATE 115200

// Use pins 4 and 5 for UART1
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define UART_TX_PIN 4
#define UART_RX_PIN 5

#define GPIO_LED_GREEN 11
#define GPIO_LED_BLUE 12
#define GPIO_LED_RED 13

void desligar_leds()
{
    gpio_put(GPIO_LED_RED, false);
    gpio_put(GPIO_LED_GREEN, false);
    gpio_put(GPIO_LED_BLUE, false);
}
void ligar_led_branco() {
    gpio_put(GPIO_LED_RED, true);
    gpio_put(GPIO_LED_GREEN, true);
    gpio_put(GPIO_LED_BLUE, true);
}


int main()
{
    stdio_init_all();

    gpio_init(GPIO_LED_RED);
    gpio_init(GPIO_LED_GREEN);
    gpio_init(GPIO_LED_BLUE);
    gpio_set_dir(GPIO_LED_RED, GPIO_OUT);
    gpio_set_dir(GPIO_LED_GREEN, GPIO_OUT);
    gpio_set_dir(GPIO_LED_BLUE, GPIO_OUT);

    // Set up our UART
    uart_init(UART_ID, BAUD_RATE);
    // Set the TX and RX pins by using the function select on the GPIO
    // Set datasheet for more information on function select
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

    // Use some the various UART functions to send out data
    // In a default system, printf will also output via the default UART

    // Send out a string, with CR/LF conversions
    uart_puts(UART_ID, " Hello, UART!\n");

    // For more examples of UART use see https://github.com/raspberrypi/pico-examples/tree/master/uart
    char rx_buffer[64]; // Buffer para armazenar o comando recebido
    int buffer_index = 0;

    while (true)
    {
        while (uart_is_readable(UART_ID))
        {
            char ch = uart_getc(UART_ID); // Lê o próximo caractere
            if (ch == '\n' || ch == '\r')
            {
                // Final do comando recebido
                rx_buffer[buffer_index] = '\0'; // Termina a string
                buffer_index = 0;               // Reinicia o índice do buffer
                

                // Verifica o comando recebido
                if (strcmp(rx_buffer, "off") == 0)
                {
                    desligar_leds();
                    uart_puts(UART_ID, "Comando recebido: OFF\n");
                }
              
                if (strcmp(rx_buffer, "GREEN") == 0)
                {
                    aciona_led_verde();
                    uart_puts(UART_ID, "Comando recebido: GREEN\n");
                }
              
                if (strcmp(rx_buffer, "white") == 0) {
                    ligar_led_branco();
                    uart_puts(UART_ID, "comando recebido: WHITE\n");
                } 

            else
            {
                // Armazena o caractere no buffer se não for o final da linha
                if (buffer_index < sizeof(rx_buffer) - 1)
                {
                    rx_buffer[buffer_index++] = ch;
                }
            }
        }
    }
}