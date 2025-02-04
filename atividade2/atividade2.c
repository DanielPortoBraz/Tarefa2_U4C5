#include "pico/stdlib.h" // Biblioteca padrão do SDK Pico
#include "pico/time.h" // Biblioteca com funções de temporização e interrupção


// Pino do botão
#define BUTTON_PIN 5

// Pinos dos leds: azul, vermelho e verde
const uint8_t leds_pins[] = {11, 12, 13};

// Conta a quantidade de chamadas do alarme
volatile uint8_t alarms = 0;

// Guarda o estado de pressionamento do botão. Inicialmente como falso
volatile bool button_on = false;

// Inicializa os leds e os desliga
void init_leds(){

  for (int i = 0; i < 3; i++){
    gpio_init(leds_pins[i]);
    gpio_set_dir(leds_pins[i], GPIO_OUT);
    gpio_put(leds_pins[i], 0);
  }
}

// Inicializa o botão com um resistor pull-up
void init_button(){
  gpio_init(BUTTON_PIN);
  gpio_set_dir(BUTTON_PIN, GPIO_IN);
  gpio_pull_up(BUTTON_PIN);
}

// Função callback para o alarme
int64_t turn_off_led_callback(alarm_id_t id, void *user_data){
  
  // Desliga o led baseado na ordem do alarme
  gpio_put(leds_pins[alarms], 0);

  // Contabiliza um alarme
  alarms++;

  if (alarms == 3){ // Se o contador de alarme chegar a 3, é reiniciado o contador
    alarms = 0;
    button_on = false; // Atualiza o estado do botão para permitir outro pressionamento
  }

  return 0;
}


int main() {
  stdio_init_all(); // Inicializa a comunicação serial (não utilizada nesse código)
  init_leds();
  init_button();

  while(1){
    
    // Se o botão for pressionado (estiver em LOW) e não tiver sido solicitado antes do fim da callback
    if(!gpio_get(BUTTON_PIN) && !button_on){
      sleep_ms(50); // Atraso de 50 ms para debounce

      if(!gpio_get(BUTTON_PIN)){ // Verifica novamente para não ter efeito bounce

        for(int i = 0; i < 3; i++)
          gpio_put(leds_pins[i], 1);

        // Atualiza o pressionamento do botão para que não hajam tentativas antes dos alarmes termninarem
        button_on = true;

        // Aciona 3 alarmes consecutivos de 3 segundos para desligar cada led
        for (int i = 1; i < 4; i++)
          add_alarm_in_ms(i * 3000, turn_off_led_callback, NULL, false);

      }
    }
    sleep_ms(20); // Intervaldo de 20 ms para menor uso da CPU
  }
}



