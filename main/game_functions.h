// game_functions.h

#ifndef GAME_FUNCTIONS_H
#define GAME_FUNCTIONS_H

#include "pico/stdlib.h"
#include "hardware/gpio.h"

// Declaração das constantes de pinos
extern const int BTN_PIN;
extern const int BTN2_PIN;
extern const int BTN3_PIN;
extern const int BTN4_PIN;
extern const int BUZZER;

extern const int LED_G;
extern const int LED_Y;
extern const int LED_R;
extern const int LED_B;

// Declaração de variáveis voláteis
extern volatile bool btn_pressed_flag;
extern volatile bool btn2_pressed_flag;
extern volatile bool btn3_pressed_flag;
extern volatile bool btn4_pressed_flag;

extern volatile bool computador_flag;
extern volatile bool errou_flag;

// Declaração das funções
void btn_callback(uint gpio, uint32_t events);
void generate_sound(int buzzer_pin, int frequency, int duration_us);
void pontuacao(int n, int buzzer_pin);
void play_theme(int buzzer_pin);
void play_loss_music(int buzzer_pin);
void play_starwars_theme(int buzzer_pin);

// Definição das frequências das notas musicais
#define C4  261
#define D4  294
#define E4  329
#define F4  349
#define G4  391
#define A4  440
#define B4  493
#define C5  523
#define G3  196
#define a 440
#define aH 880
#define aS 455
#define b 466
#define bH 933
#define cH 523
#define cHS 554
#define dH 587
#define dHS 622
#define eH 659
#define fH 698
#define fHS 740
#define gH 784
#define gHS 830
#define gS 415
#define f 349
#define c 261
#define cS 277
#define d 294
#define g 391


#endif // GAME_FUNCTIONS_H
