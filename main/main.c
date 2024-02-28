/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


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

const int SEQUENCIA[4] = {1,2,3,4};
const int TAMANHO_SEQ = sizeof(SEQUENCIA)/ sizeof(SEQUENCIA[0]);

volatile bool btn_pressed_flag = false;
volatile bool btn2_pressed_flag = false;
volatile bool btn3_pressed_flag = false;
volatile bool btn4_pressed_flag = false;

volatile bool computador_flag = true;
volatile bool errou_flag = false;

void btn_callback(uint gpio, uint32_t events) {
  if (gpio == BTN_PIN && !btn_pressed_flag) {
    btn_pressed_flag = true;
    gpio_put(LED_B, 1);
  }
  if (gpio == BTN2_PIN && !btn2_pressed_flag) {
    btn2_pressed_flag = true;
    gpio_put(LED_R, 1);
  }
  if (gpio == BTN3_PIN && !btn3_pressed_flag) {
    btn3_pressed_flag = true;
    gpio_put(LED_Y, 1);
  }
  if (gpio == BTN4_PIN && !btn4_pressed_flag) {
    btn4_pressed_flag = true;
    gpio_put(LED_G, 1);
  }
}

void generate_sound(int buzzer_pin, int frequency, int duration_us) {
    int period_us = 1000000 / frequency; // Calcula o período em microssegundos
    int half_period_us = period_us / 2;

    for (int i = 0; i < (duration_us / period_us); i++) {
        gpio_put(buzzer_pin, 1);
        sleep_us(half_period_us); // Metade do período em alto
        gpio_put(buzzer_pin, 0);
        sleep_us(half_period_us); // Metade do período em baixo
    }
}


int main() {
  int SEQJOGADO[4] = {0,0,0,0};

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


    while (true) {

      if(computador_flag){
        printf(" Tamanho sequencia %d \n", TAMANHO_SEQ);
        for(int i = 0; i < TAMANHO_SEQ; i++){
          printf("ValorSequencia %d   " ,SEQUENCIA[i]);
          if(SEQUENCIA[i]==1){
            gpio_put(LED_G, 1);
            generate_sound(BUZZER,349.23, 500000);   
            gpio_put(LED_G, 0);
            printf("GREEN \n");

          }else if(SEQUENCIA[i]==2){
            gpio_put(LED_Y, 1);
            generate_sound(BUZZER,329.63, 500000);
            gpio_put(LED_Y, 0);
            printf("YELLOW \n");

          }else if(SEQUENCIA[i]==3){
            gpio_put(LED_B, 1);
            generate_sound(BUZZER,261.63, 500000);
            gpio_put(LED_B, 0);
            printf("BLUE \n");
            
          }else{
            gpio_put(LED_R, 1);
            generate_sound(BUZZER,293.66, 500000);   
            gpio_put(LED_R, 0);
            printf("RED \n");  
          }
        }
        printf("agora 'e cm vc!");
        computador_flag=false;
      }
      int indice_seq_jogado = 0;
      while(!computador_flag && !errou_flag){
        
        if(btn_pressed_flag){
          generate_sound(BUZZER,261.63, 500000);
          btn_pressed_flag = 0;
          gpio_put(LED_B, 0);
          printf("BLUE \n");
          SEQJOGADO[indice_seq_jogado]=4;
          indice_seq_jogado=indice_seq_jogado+1;
        }
        if(btn2_pressed_flag){
          generate_sound(BUZZER,293.66, 500000);
          btn2_pressed_flag = 0;       
          gpio_put(LED_R, 0);
          printf("RED \n");
          SEQJOGADO[indice_seq_jogado]=3;
          indice_seq_jogado=indice_seq_jogado+1;
        }
        if(btn3_pressed_flag){
          generate_sound(BUZZER,329.63, 500000);
          btn3_pressed_flag = 0;        
          gpio_put(LED_Y, 0);
          printf("YELLOW \n");
          SEQJOGADO[indice_seq_jogado]=2;
          indice_seq_jogado=indice_seq_jogado+1;
        }
        if(btn4_pressed_flag){
          generate_sound(BUZZER,349.23, 500000);
          btn4_pressed_flag = 0;        
          gpio_put(LED_G, 0);
          printf("GREEN \n");
          SEQJOGADO[indice_seq_jogado]=1;
          indice_seq_jogado=indice_seq_jogado+1;
        }
        if (SEQJOGADO[indice_seq_jogado-1] != SEQUENCIA[indice_seq_jogado-1] && SEQJOGADO[indice_seq_jogado-1]!=0  ){
          printf("ERROU \n");
          printf("erru no incide %d \n",indice_seq_jogado);
          errou_flag = true;
        }

        
      }




    }
}

