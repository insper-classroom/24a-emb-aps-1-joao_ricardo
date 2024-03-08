// game_functions.c

#include "game_functions.h"

// Definição das constantes de pinos
const int BTN_PIN = 15;
const int BTN2_PIN = 16;
const int BTN3_PIN = 12;
const int BTN4_PIN = 13;
const int BUZZER = 18;

const int LED_G = 28;
const int LED_Y = 27;
const int LED_R = 26;
const int LED_B = 22;

// Definição de variáveis voláteis
volatile bool btn_pressed_flag = false;
volatile bool btn2_pressed_flag = false;
volatile bool btn3_pressed_flag = false;
volatile bool btn4_pressed_flag = false;

volatile bool computador_flag = true;
volatile bool errou_flag = false;

// Implementação das funções
void btn_callback(uint gpio, uint32_t events)
{
    if (gpio == BTN_PIN && !btn_pressed_flag)
    {
        btn_pressed_flag = true;
    }
    if (gpio == BTN2_PIN && !btn2_pressed_flag)
    {
        btn2_pressed_flag = true;
    }
    if (gpio == BTN3_PIN && !btn3_pressed_flag)
    {
        btn3_pressed_flag = true;
    }
    if (gpio == BTN4_PIN && !btn4_pressed_flag)
    {
        btn4_pressed_flag = true;
    }
}

void generate_sound(int buzzer_pin, int frequency, int duration_us)
{
    int period_us = 1000000 / frequency; // Calcula o período em microssegundos
    int half_period_us = period_us / 2;

    for (int i = 0; i < (duration_us / period_us); i++)
    {
        gpio_put(buzzer_pin, 1);
        sleep_us(half_period_us); // Metade do período em alto
        gpio_put(buzzer_pin, 0);
        sleep_us(half_period_us); // Metade do período em baixo
    }
}

void pontuacao(int n, int buzzer_pin)
{
    for (int i = 0; i < n; i++)
    {
        gpio_put(LED_B, 1);
        generate_sound(BUZZER, G4, 500000);
        gpio_put(LED_B, 0);

        sleep_ms(500);
    }
}

void play_theme(int buzzer_pin)
{
    // Sequência de notas e durações (exemplo genérico)
    // Essas notas e durações são apenas para exemplo. Ajuste conforme necessário para a melodia real.
    generate_sound(buzzer_pin, G4, 500000); // G4 por meio segundo
    sleep_ms(100);                          // Pausa entre notas
    generate_sound(buzzer_pin, E4, 500000); // E4 por meio segundo
    sleep_ms(100);
    generate_sound(buzzer_pin, C4, 500000); // C4 por meio segundo
    sleep_ms(100);
    generate_sound(buzzer_pin, G4, 500000); // G4 por meio segundo
    sleep_ms(100);
    // Repita ou modifique estas linhas conforme necessário para sua melodia
}

void play_loss_music(int buzzer_pin)
{
    // Sequência simplificada da música de perda de vida do Mario
    generate_sound(buzzer_pin, E4, 150000); // E4 por 150ms
    sleep_ms(50);                           // Pausa curta entre notas
    generate_sound(buzzer_pin, G3, 150000); // G3 por 150ms
    sleep_ms(50);                           // Pausa
    generate_sound(buzzer_pin, E4, 150000); // E4 novamente por 150ms
    sleep_ms(50);                           // Pausa
    generate_sound(buzzer_pin, C4, 300000); // C4 por 300ms, uma nota mais longa no final
    sleep_ms(500);
}

void play_starwars_theme(int buzzer_pin)
{
    // Primeira seção
    generate_sound(buzzer_pin, a, 500000);
    generate_sound(buzzer_pin, a, 500000);
    generate_sound(buzzer_pin, f, 350000);
    generate_sound(buzzer_pin, cH, 150000);
    generate_sound(buzzer_pin, a, 500000);
    // generate_sound(buzzer_pin, f, 350000);
    // generate_sound(buzzer_pin, cH, 150000);
    // generate_sound(buzzer_pin, a, 100000);
    // sleep_ms(500);

    // // Segunda seção
    // generate_sound(buzzer_pin, eH, 500000);
    // generate_sound(buzzer_pin, eH, 500000);
    // generate_sound(buzzer_pin, eH, 500000);
    // generate_sound(buzzer_pin, fH, 350000);
    // generate_sound(buzzer_pin, cH, 150000);
    // generate_sound(buzzer_pin, gS, 500000);
    // generate_sound(buzzer_pin, f, 350000);
    // generate_sound(buzzer_pin, cH, 150000);
    // generate_sound(buzzer_pin, a, 1000000);
    // sleep_ms(500);

    // // Terceira seção
    // generate_sound(buzzer_pin, aH, 500000);
    // generate_sound(buzzer_pin, a, 350000);
    // generate_sound(buzzer_pin, a, 150000);
    // generate_sound(buzzer_pin, aH, 500000);
    // generate_sound(buzzer_pin, gHS, 250000);
    // generate_sound(buzzer_pin, gH, 250000);
    // generate_sound(buzzer_pin, fHS, 125000);
    // generate_sound(buzzer_pin, fH, 125000);
    // generate_sound(buzzer_pin, fHS, 250000);
    // sleep_ms(120);

    // generate_sound(buzzer_pin, aS, 250000);
    // generate_sound(buzzer_pin, dHS, 500000);
    // generate_sound(buzzer_pin, dH, 250000);
    // generate_sound(buzzer_pin, cHS, 250000);
    // generate_sound(buzzer_pin, cH, 125000);
    // generate_sound(buzzer_pin, b, 125000);
    // generate_sound(buzzer_pin, cH, 250000);
    // sleep_ms(120);

    // // Quarta seção
    // generate_sound(buzzer_pin, f, 125000);
    // generate_sound(buzzer_pin, gS, 500000);
    // generate_sound(buzzer_pin, f, 375000);
    // generate_sound(buzzer_pin, a, 125000);
    // generate_sound(buzzer_pin, cH, 500000);
    // generate_sound(buzzer_pin, a, 375000);
    // generate_sound(buzzer_pin, cH, 125000);
    // generate_sound(buzzer_pin, eH, 1000000);
    // sleep_ms(250);

    // generate_sound(buzzer_pin, a, 500000);
    // generate_sound(buzzer_pin, a, 500000);
    // generate_sound(buzzer_pin, f, 350000);
    // generate_sound(buzzer_pin, cH, 150000);
    // generate_sound(buzzer_pin, a, 500000);
    // generate_sound(buzzer_pin, f, 350000);
    // generate_sound(buzzer_pin, cH, 150000);
    // generate_sound(buzzer_pin, a, 1000000);
    // sleep_ms(500);

    // // Sexta seção (Variação das seções anteriores)
    // generate_sound(buzzer_pin, eH, 500000);
    // generate_sound(buzzer_pin, eH, 500000);
    // generate_sound(buzzer_pin, eH, 500000);
    // generate_sound(buzzer_pin, fH, 350000);
    // generate_sound(buzzer_pin, cH, 150000);
    // generate_sound(buzzer_pin, gS, 500000);
    // generate_sound(buzzer_pin, f, 350000);
    // generate_sound(buzzer_pin, cH, 150000);
    // generate_sound(buzzer_pin, a, 1000000);
    // sleep_ms(500);

    // // Repete a terceira seção para concluir
    // generate_sound(buzzer_pin, aH, 500000);
    // generate_sound(buzzer_pin, a, 350000);
    // generate_sound(buzzer_pin, a, 150000);
    // generate_sound(buzzer_pin, aH, 500000);
    // generate_sound(buzzer_pin, gHS, 250000);
    // generate_sound(buzzer_pin, gH, 250000);
    // generate_sound(buzzer_pin, fHS, 125000);
    // generate_sound(buzzer_pin, fH, 125000);
    // generate_sound(buzzer_pin, fHS, 250000);
    // sleep_ms(250);

    // generate_sound(buzzer_pin, aS, 250000);
    // generate_sound(buzzer_pin, dHS, 500000);
    // generate_sound(buzzer_pin, dH, 250000);
    // generate_sound(buzzer_pin, cHS, 250000);
    // generate_sound(buzzer_pin, cH, 125000);
    // generate_sound(buzzer_pin, b, 125000);
    // generate_sound(buzzer_pin, cH, 250000);
    // sleep_ms(250);

    // // Finaliza com uma repetição de partes chave para encerrar a música
    // generate_sound(buzzer_pin, f, 250000);
    // generate_sound(buzzer_pin, gS, 500000);
    // generate_sound(buzzer_pin, f, 375000);
    // generate_sound(buzzer_pin, cH, 125000);
    // generate_sound(buzzer_pin, a, 500000);
    // generate_sound(buzzer_pin, f, 375000);
    // generate_sound(buzzer_pin, c, 125000);
    // generate_sound(buzzer_pin, a, 1000000);
    // sleep_ms(250);
}
