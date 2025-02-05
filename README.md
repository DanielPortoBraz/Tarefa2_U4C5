# Aprendizado de Temporização e Interrupção no Raspberry Pi Pico W

Este repositório contém duas atividades desenvolvidas para o aprendizado de temporização e interrupção utilizando o Raspberry Pi Pico W, com base no SDK C/C++ oficial da Raspberry Pi.

## Requisitos
- Raspberry Pi Pico W
- SDK C/C++ instalado e configurado
- CMake e ferramentas de compilação compatíveis

## Configuração do Ambiente
Caso ainda não tenha configurado o ambiente de desenvolvimento, siga a documentação oficial:
[Raspberry Pi Pico - Getting Started](https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf)

## Importação do Projeto com a Extensão Raspberry Pi Pico
Se estiver utilizando o Visual Studio Code com a extensão "Raspberry Pi Pico-W", siga os passos abaixo para importar corretamente o projeto:
1. Abra o VS Code e instale a extensão "Raspberry Pi Pico" se ainda não tiver instalado.
2. Na extensão selecione "Import Project" e escolha a versão 2.1.0
4. Coloque o caminho do arquivo no seu ambiente em "Location"
5. Selecione "Import" e aguarde os arquivos serem importados
6. Compile e transfira o código para o Pico seguindo os passos da seção "Como Compilar e Executar" abaixo.
   
**Obs**: Caso não consiga importar o projeto por inteiro, importe cada pasta separadamente.

## Estrutura do Repositório
```
/
├── atividade_1.c  # Simula um semáforo com alternância de LEDs e contagem de veículos
├── atividade_2.c  # Controla LEDs com temporização baseada em eventos de alarme
├── CMakeLists.txt # Arquivo de build do CMake para compilação dos códigos
└── README.md      # Este arquivo explicativo
```

## Atividade 1 - Semáforo Simulado

Este programa simula um semáforo com três LEDs (vermelho, amarelo e verde). A cada 3 segundos, ocorre a transição entre os estados, utilizando um timer periódico. Além disso, o programa conta a quantidade de "carros" aguardando no semáforo enquanto o LED vermelho está aceso.

### Funcionamento:
- O LED vermelho inicia aceso.
- A cada 3 segundos, o próximo LED é ativado, seguindo a sequência: vermelho -> amarelo -> verde.
- Quando o LED verde acende, a contagem de carros é zerada.
- A cada segundo, a variável `cars` é incrementada, simulando a chegada de novos veículos na fila de espera.

### Principais Funções:
- `init_leds()`: Configura os pinos dos LEDs.
- `alternate_led()`: Alterna o LED aceso conforme a ordem definida.
- `repeating_timer_callback()`: Callback chamada a cada 3 segundos para alternar os LEDs e resetar a contagem de carros quando necessário.

## Atividade 2 - Controle de LEDs com Alarme

Este programa permite acionar três LEDs simultaneamente ao pressionar um botão e, após um intervalo programado, desligá-los sequencialmente a cada 3 segundos usando um sistema de alarme.

### Funcionamento:
- O usuário pressiona o botão (configurado com pull-up interno).
- Os três LEDs acendem simultaneamente.
- Três alarmes são programados para desligar cada LED sequencialmente em intervalos de 3 segundos.
- O sistema evita acionamentos repetidos antes que todos os LEDs tenham sido desligados.

### Principais Funções:
- `init_leds()`: Configura os pinos dos LEDs.
- `init_button()`: Configura o botão como entrada com resistor pull-up.
- `turn_off_led_callback()`: Callback acionada pelos alarmes para desligar cada LED em sequência.

## Como Compilar e Executar
1. Clone o repositório:
   ```bash
   git clone <URL_DO_REPOSITORIO>
   cd <NOME_DO_REPOSITORIO>
   ```
2. Crie um diretório de build e compile o código:
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```
3. Conecte o Raspberry Pi Pico W no modo USB Mass Storage (pressione e segure o botão BOOTSEL ao conectá-lo ao PC).
4. Copie o arquivo `.uf2` gerado para o dispositivo.
5. O programa iniciará automaticamente após a transferência.

## Vídeos de teste de execução no Wokwi
Link da playlist: https://www.youtube.com/playlist?list=PLaN_cHSVjBi_pGq5jw-5iki8HIGjD6RPM
---

