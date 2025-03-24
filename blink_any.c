#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"

#define SENSOR_100 3
#define SENSOR_50 2
#define SENSOR_0 4

#define LEDB 12
#define LEDG 11
#define LEDR 13

#define BUZZER_PIN 21
#define BUZZER_FREQUENCIA_AGUDA 1000
#define BUZZER_FREQUENCIA_GRAVE 100

void pwm_init_buzzer(uint pin, uint frequencia) {
    // Configura o pino de saída do PWM
    gpio_set_function(pin, GPIO_FUNC_PWM);

    // Obtém o slice de PWM associado ao pino
    uint slice_num = pwm_gpio_to_slice_num(pin);

    // Configura o PWM com a frequência desejada
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, (float)clock_get_hz(clk_sys) / (frequencia * 4096)); // Divisor de clock

    pwm_init(slice_num, &config, true);

    // Inicia o PWM no nível baixo
    pwm_set_gpio_level(pin, 0);
}

void beep(uint pin, uint duration_ms, uint frequencia) {
    // Obtém o slice do PWM associado ao pino
    uint slice_num = pwm_gpio_to_slice_num(pin);

    pwm_set_gpio_level(pin, 2048);

    // Temporização
    sleep_ms(duration_ms);

    pwm_set_gpio_level(pin, 0);

    // Pausa entre os bips
    sleep_ms(100);
}

int debounce_sensor(uint pin){
    int estado = gpio_get(pin);
    sleep_ms(50);

    if (gpio_get(pin) == estado) {
        return estado;
    } else {
        return gpio_get(pin);
    }
}

void alerta_caixa_vazia(uint pin){
    for (int i = 0; i < 3; i++) {
        beep(pin, 100, BUZZER_FREQUENCIA_GRAVE);
    }
}

void alerta_caixa_cheia(uint pin){
    beep(pin, 500, BUZZER_FREQUENCIA_AGUDA);
}

int main() {
    stdio_init_all();

    // Inicia o PWM no pino do BUZZER
    pwm_init_buzzer(BUZZER_PIN, 500);

    gpio_init(SENSOR_0);
    gpio_set_dir(SENSOR_0, GPIO_IN);
    gpio_pull_down(SENSOR_0);

    gpio_init(SENSOR_50);
    gpio_set_dir(SENSOR_50, GPIO_IN);
    gpio_pull_down(SENSOR_50);

    gpio_init(SENSOR_100);
    gpio_set_dir(SENSOR_100, GPIO_IN);
    gpio_pull_down(SENSOR_100);

    gpio_init(LEDR);
    gpio_set_dir(LEDR, GPIO_OUT);
    gpio_put(LEDR, false);

    gpio_init(LEDB);
    gpio_set_dir(LEDB, GPIO_OUT);
    gpio_put(LEDB, false);

    gpio_init(LEDG);
    gpio_set_dir(LEDG, GPIO_OUT);
    gpio_put(LEDG, false);

    while (true) {
        // int estado_0 = gpio_get(SENSOR_0);
        // int estado_50 = gpio_get(SENSOR_50);
        // int estado_100 = gpio_get(SENSOR_100);

        int estado_0 = debounce_sensor(SENSOR_0);
        int estado_50 = debounce_sensor(SENSOR_50);
        int estado_100 = debounce_sensor(SENSOR_100);

        printf("Sensor 100: %d | Sensor 50: %d | Sensor 0: %d\n", estado_100, estado_50, estado_0);

        gpio_put(LEDR, false);
        gpio_put(LEDB, false);
        gpio_put(LEDG, false);

        if (estado_100) {
            printf("Caixa cheia\n");
            gpio_put(LEDG, true);
            alerta_caixa_cheia(BUZZER_PIN);
        } else if (estado_50) {
            printf("Caixa está na metade\n");
            gpio_put(LEDB, true);
        } else if (estado_0) {
            printf("Caixa vazia\n");
            gpio_put(LEDR, true);
            alerta_caixa_vazia(BUZZER_PIN);
        }

        sleep_ms(500);
    }
    return 0;
}