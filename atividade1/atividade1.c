#include <stdio.h> // Biblioteca de entrada e saída padrão
#include "pico/stdlib.h" // BIblioteca padrão do SDK Pico
#include "hardware/timer.h" // Biblioteca com funções de temporização e interrupção

// Pinos dos leds
const uint8_t leds_pins[] = {11, 12, 13};

// Acessa a posição do led no vetor
volatile uint8_t led = 0;

// Conta a quantidade de carros esperando no semáforo
volatile uint8_t cars = 0;

// Inicialização dos leds. Todos, exceto o vermelho, são desligados
void init_leds(){

  for (int i = 0; i < 3; i++){
    gpio_init(leds_pins[i]);
    gpio_set_dir(leds_pins[i], GPIO_OUT);

    if(i == 0){
      gpio_put(leds_pins[i], 1);
      led++;
    }  

    else 
      gpio_put(leds_pins[i], 0);
  }
}

// Alterna o led que será aceso com base na variável "led"
void alternate_led(){

  for(int i = 0; i < 3; i++){

    if (i == led)
      gpio_put(leds_pins[i], 1);

    else 
      gpio_put(leds_pins[i], 0);
  }
}

// Protótipo da callback para a temporização periódica
bool repeating_timer_callback(struct repeating_timer *t);


int main() {
  stdio_init_all(); // Inicia a comunicação serial
  init_leds();

  struct repeating_timer timer; // Variável para armazenar informações de tempo

  // Ativa a função de temporização periódica para cada 3000 ms (3 segundos)
  add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

  while (1){
      printf("Carros na espera: %d\n", cars); // Informa a quantidade de carros no semáforo
      cars++; // Simula a chegada de um novo carro
      sleep_ms(1000); // Faz uma pausa de 1 segundo
    }
}

// Função callback de temporização periódica
bool repeating_timer_callback(struct repeating_timer *t){

  if(led == 3) // Se o ciclo tiver encerrado, reinicia a posição do led no vetor
    led = 0;
  
  else if (led == 2) // Se o led verde ficar aceso, reinicia a quantidade de carros
    cars = 0;

  // Troca o led aceso
  alternate_led();

  // Atualiza a posição para o próximo led no vetor
  led++;

  // Retorna true para chamar outras vezes a função
  return true;
}