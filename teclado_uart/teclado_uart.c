#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"

// Mapeamento das ações para enviar na UART em escrito
char* MAP_ENTRYS[7] = {
    "ON: RED", "ON: BLUE", "ON: GREEN", "ON: WHITE", "OFF: ALL LEDS", "ON: BUFFER", "ERROR: UNKOWN COMMAND"
};

uint check_entry(){
    uint input;
    printf("Aguardando entrada...");
    scanf("%d", &input);
    printf("\n");

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