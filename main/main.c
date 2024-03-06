/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdlib.h> // Para rand() e srand()
#include <time.h>   // Para time()
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

const int BTN_PIN = 15;
const int BTN2_PIN = 16;
const int BTN3_PIN = 12;
const int BTN4_PIN = 13;
const int BUZZER = 18;

const int LED_G = 28;
const int LED_Y = 27;
const int LED_R = 26;
const int LED_B = 22;


volatile bool btn_pressed_flag = false;
volatile bool btn2_pressed_flag = false;
volatile bool btn3_pressed_flag = false;
volatile bool btn4_pressed_flag = false;

volatile bool computador_flag = true;
volatile bool errou_flag = false;

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



#define C4  261
#define D4  294
#define E4  329
#define F4  349
#define G4  391
#define A4  440
#define B4  493
#define C5  523
#define G3  196

void pontuacao (int n, int buzzer_pin){
  for (int i = 0; i < n; i++){
    gpio_put(LED_B, 1);
    generate_sound(BUZZER, G4, 500000);
    gpio_put(LED_B, 0);

    sleep_ms(500);
  }
}

void play_theme(int buzzer_pin) {
    // Sequência de notas e durações (exemplo genérico)
    // Essas notas e durações são apenas para exemplo. Ajuste conforme necessário para a melodia real.
    generate_sound(buzzer_pin, G4, 500000); // G4 por meio segundo
    sleep_ms(100); // Pausa entre notas
    generate_sound(buzzer_pin, E4, 500000); // E4 por meio segundo
    sleep_ms(100);
    generate_sound(buzzer_pin, C4, 500000); // C4 por meio segundo
    sleep_ms(100);
    generate_sound(buzzer_pin, G4, 500000); // G4 por meio segundo
    sleep_ms(100);
    // Repita ou modifique estas linhas conforme necessário para sua melodia
}


void play_loss_music(int buzzer_pin) {
    // Sequência simplificada da música de perda de vida do Mario
    generate_sound(buzzer_pin, E4, 150000); // E4 por 150ms
    sleep_ms(50); // Pausa curta entre notas
    generate_sound(buzzer_pin, G3, 150000); // G3 por 150ms
    sleep_ms(50); // Pausa
    generate_sound(buzzer_pin, E4, 150000); // E4 novamente por 150ms
    sleep_ms(50); // Pausa
    generate_sound(buzzer_pin, C4, 300000); // C4 por 300ms, uma nota mais longa no final
    sleep_ms(500);
}


int main()
{
  int TAMANHO_SEQ = 0;
  int SEQUENCIA[100];


  stdio_init_all();

  gpio_init(BTN_PIN);
  gpio_set_dir(BTN_PIN, GPIO_IN);
  gpio_pull_up(BTN_PIN);

  gpio_init(BTN2_PIN);
  gpio_set_dir(BTN2_PIN, GPIO_IN);
  gpio_pull_up(BTN2_PIN);

  gpio_init(BTN3_PIN);
  gpio_set_dir(BTN3_PIN, GPIO_IN);
  gpio_pull_up(BTN3_PIN);

  gpio_init(BTN4_PIN);
  gpio_set_dir(BTN4_PIN, GPIO_IN);
  gpio_pull_up(BTN4_PIN);

  gpio_init(BUZZER);
  gpio_set_dir(BUZZER, GPIO_OUT);

  gpio_init(LED_G);
  gpio_set_dir(LED_G, GPIO_OUT);

  gpio_init(LED_Y);
  gpio_set_dir(LED_Y, GPIO_OUT);

  gpio_init(LED_R);
  gpio_set_dir(LED_R, GPIO_OUT);

  gpio_init(LED_B);
  gpio_set_dir(LED_B, GPIO_OUT);

  gpio_set_irq_enabled_with_callback(BTN_PIN, GPIO_IRQ_EDGE_FALL, true, &btn_callback);
  gpio_set_irq_enabled_with_callback(BTN2_PIN, GPIO_IRQ_EDGE_FALL, true, &btn_callback);
  gpio_set_irq_enabled_with_callback(BTN3_PIN, GPIO_IRQ_EDGE_FALL, true, &btn_callback);
  gpio_set_irq_enabled_with_callback(BTN4_PIN, GPIO_IRQ_EDGE_FALL, true, &btn_callback);


  while(!btn_pressed_flag && !btn2_pressed_flag &&!btn3_pressed_flag && !btn4_pressed_flag){
    sleep_ms(1000);
  }

  btn_pressed_flag = 0;
  btn2_pressed_flag = 0;
  btn3_pressed_flag = 0;
  btn4_pressed_flag = 0;
  
  play_theme(BUZZER);
  srand(to_us_since_boot(get_absolute_time()));

  while (true)
  {

    if (computador_flag)
    {
      int novo_numero = rand() % 4 + 1; // Gera um número aleatório entre 1 e 4
      SEQUENCIA[TAMANHO_SEQ] = novo_numero; // Adiciona o novo número à sequência
      TAMANHO_SEQ++;
      printf(" Tamanho sequencia %d \n", TAMANHO_SEQ);
      for (int i = 0; i < TAMANHO_SEQ; i++)
      {
        printf("ValorSequencia %d   ", SEQUENCIA[i]);
        if (SEQUENCIA[i] == 1)
        {
          gpio_put(LED_G, 1);
          generate_sound(BUZZER, 349.23, 500000);
          sleep_ms(1000);
          gpio_put(LED_G, 0);
          printf("GREEN \n");
        }
        else if (SEQUENCIA[i] == 2)
        {
          gpio_put(LED_Y, 1);
          generate_sound(BUZZER, 329.63, 500000);
          sleep_ms(1000);
          gpio_put(LED_Y, 0);
          printf("YELLOW \n");
        }
        else if (SEQUENCIA[i] == 3)
        {
          gpio_put(LED_B, 1);
          generate_sound(BUZZER, 261.63, 500000);
          sleep_ms(1000);
          gpio_put(LED_B, 0);
          printf("BLUE \n");
        }
        else
        {
          gpio_put(LED_R, 1);
          generate_sound(BUZZER, 293.66, 500000);
          sleep_ms(1000);
          gpio_put(LED_R, 0);
          printf("RED \n");
        }
      }
      printf("agora e cm vc! \n");
      computador_flag = false;
    }
    int indice_seq_jogado = 0;
    int valor_clicado = 0;
    while (!computador_flag && !errou_flag)
    {

      if (btn_pressed_flag)
      {gpio_put(LED_B, 1);
        printf("BLUE \n");
        generate_sound(BUZZER, 293.66, 500000);
        sleep_ms(1000);
        btn_pressed_flag = 0;
        gpio_put(LED_B, 0);
        indice_seq_jogado = indice_seq_jogado + 1;
        valor_clicado = 3;

      }
      if (btn2_pressed_flag)
      {
        gpio_put(LED_R, 1);
        printf("RED \n");
        generate_sound(BUZZER, 261.63, 500000);
        sleep_ms(1000);
        btn2_pressed_flag = 0;
        gpio_put(LED_R, 0);
        indice_seq_jogado = indice_seq_jogado + 1;
        valor_clicado = 4;
        
      }
      if (btn3_pressed_flag)
      {
        gpio_put(LED_Y, 1);
        printf("YELLOW \n");
        generate_sound(BUZZER, 329.63, 500000);
        sleep_ms(1000);
        btn3_pressed_flag = 0;
        gpio_put(LED_Y, 0);
        indice_seq_jogado = indice_seq_jogado + 1;
        valor_clicado = 2;
      }
      if (btn4_pressed_flag)
      {
        gpio_put(LED_G, 1);
        printf("GREEN \n");
        generate_sound(BUZZER, 349.23, 500000);
        sleep_ms(1000);
        btn4_pressed_flag = 0;
        gpio_put(LED_G, 0);
        indice_seq_jogado = indice_seq_jogado + 1;
        valor_clicado = 1;
      }
      if (SEQUENCIA[indice_seq_jogado-1] != valor_clicado && valor_clicado !=0)
      {
        printf("ERROU \n");
        printf("erru no indice %d \n", indice_seq_jogado);
        play_loss_music(BUZZER);
        pontuacao (TAMANHO_SEQ-1, BUZZER);
        errou_flag = true;

      }if(SEQUENCIA[indice_seq_jogado-1] == valor_clicado && indice_seq_jogado==TAMANHO_SEQ){
        computador_flag=true;
        valor_clicado=0;
        sleep_ms(1000);
      }
      else if(SEQUENCIA[indice_seq_jogado-1] == valor_clicado){
        valor_clicado=0;
      }

    }
  }
}
