#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "pico/cyw43_arch.h"

// Define GPIO para os LEDs de saída
#define GPIO_RED_LED 13
#define GPIO_GREEN_LED 11
#define GPIO_BLUE_LED 12

// Define GPIO para os buzzers
#define BUZZER_A 21
#define BUZZER_B 10

// Define tempo para T01, T02 e T03
#define T01_TIME 1000000
#define T02_TIME 150
#define T03_TIME 2000000

// Temporizador 01
static bool T01(bool IN, uint64_t time_us){
    static uint64_t prev_time;
    static uint64_t curr_time;
    static bool set_value;

    if(!IN){
        curr_time = time_us_64();
        prev_time = curr_time;
        set_value = false;
    }else{
        curr_time = time_us_64();
        if(curr_time - prev_time >= time_us)
            set_value = true;
    }
    return set_value;
}

// Temporizador 02
static bool T02(bool IN, uint64_t time_us){
    static uint64_t prev_time;
    static uint64_t curr_time;
    static bool set_value;

    if(!IN){
        curr_time = time_us_64();
        prev_time = curr_time;
        set_value = false;
    }else{
        curr_time = time_us_64();
        if(curr_time - prev_time >= time_us)
            set_value = true;
    }
    return set_value;
}

// Temporizador 03
static bool T03(bool IN, uint64_t time_us){
    static uint64_t prev_time;
    static uint64_t curr_time;
    static bool set_value;

    if(!IN){
        curr_time = time_us_64();
        prev_time = curr_time;
        set_value = false;
    }else{
        curr_time = time_us_64();
        if(curr_time - prev_time >= time_us)
            set_value = true;
    }
    return set_value;
}

// Geracao do sinal para os buzzers
static bool song_gen(bool * IN_T, uint64_t T_Time, bool (*Timer)(bool,uint64_t)){
    static bool song_out = 0;

    if(!*IN_T && !Timer(*IN_T,T_Time))
        *IN_T = 1;

    if(Timer(*IN_T,T_Time) && !song_out)
        song_out = 1;
    else if(Timer(*IN_T,T_Time) && song_out)
        song_out = 0;

    if(Timer(*IN_T,T_Time))
        *IN_T = 0;
  
    return song_out;
}

// Funcao principal
int main() {
    bool IN1_T = 0, IN2_T = 0, IN3_T = 0;
    char character_press;

    stdio_init_all();

    // Inicializa os LEDs
    gpio_init(GPIO_RED_LED);
    gpio_set_dir(GPIO_RED_LED, GPIO_OUT);
    gpio_init(GPIO_GREEN_LED);
    gpio_set_dir(GPIO_GREEN_LED, GPIO_OUT);
    gpio_init(GPIO_BLUE_LED);
    gpio_set_dir(GPIO_BLUE_LED, GPIO_OUT);

    // Inicializa os buzzers
    gpio_init(BUZZER_A);
    gpio_set_dir(BUZZER_A, GPIO_OUT);
    gpio_init(BUZZER_B);
    gpio_set_dir(BUZZER_B, GPIO_OUT);

    while (true) {
        // Leitura do teclado stdio
        if(!IN1_T && !T01(IN1_T,T01_TIME))
        IN1_T = 1;

        if(T01(IN1_T,T01_TIME)){
            character_press = getchar();
            printf("\nTecla pressionada: %c\n", character_press);
        }

        if(T01(IN1_T,T01_TIME))
          IN1_T = 0;

        // Avaliacao de caractere para o RED_LED
        if (character_press=='A' || character_press=='a')
        {
            gpio_put_masked(0x3800,0x2000);
            gpio_put(BUZZER_A,false);
            gpio_put(BUZZER_B,false);
            IN3_T = 0;
        }

        // Avaliacao de caractere para o GREEN_LED
        if (character_press=='B' || character_press=='b')
        {
            gpio_put_masked(0x3800,0x800);
            gpio_put(BUZZER_A,false);
            gpio_put(BUZZER_B,false);
            IN3_T = 0;
        }

        // Avaliacao de caractere para o BLUE_LED
        if (character_press=='C' || character_press=='c')
        {
            gpio_put_masked(0x3800,0x1000);
            gpio_put(BUZZER_A,false);
            gpio_put(BUZZER_B,false);
            IN3_T = 0;
        }

        // Avaliacao de caractere para o RGB_LED
        if (character_press=='D' || character_press=='d')
        {
            gpio_put_masked(0x3800,0x3800);
            gpio_put(BUZZER_A,false);
            gpio_put(BUZZER_B,false);
            IN3_T = 0;
        }

        // Avaliacao de caractere para os buzzers
        if (character_press=='#')
        {
          if(!IN3_T && !T03(IN3_T,T03_TIME))
            IN3_T = 1;
          
          if(!T03(IN3_T,T03_TIME)){
            gpio_put_masked(0x3800,0x0);
            gpio_put(BUZZER_A, song_gen(& IN2_T,T02_TIME,T02));
            gpio_put(BUZZER_B, song_gen(& IN2_T,T02_TIME,T02));
          }else{
            gpio_put(BUZZER_A,false);
            gpio_put(BUZZER_B,false);
          }
        }

        // Avaliacao de caractere para desligar tudo
        if (character_press=='*')
        {
            gpio_put_masked(0x3800,0x0);
            gpio_put(BUZZER_A,false);
            gpio_put(BUZZER_B,false);
            IN3_T = 0;
        }
    }
    return 0;
}
