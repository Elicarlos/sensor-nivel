# Sistema Alerta de Nível

## Descrição

Este projeto implementa um sistema de alerta de nível para monitorar o nível de um reservatório (por exemplo, uma caixa d'água) utilizando sensores de nível e emitir alertas sonoros e visuais. O sistema é construído utilizando a Placa Bit Doglab e um circuito montado em protoboard, alimentado por 5V da própria placa.

## Funcionalidades

* **Monitoramento de Nível**: Monitora três níveis distintos do reservatório: 100%, 50% e 0%.
* **Alerta Sonoro**: Emite sons distintos quando o nível atinge 100% ou 0%.
* **Indicação Visual**: Utiliza LEDs para indicar o estado do reservatório:
    * LED Verde: Reservatório cheio (100%).
    * LED Azul: Reservatório na metade (50%).
    * LED Vermelho: Reservatório vazio (0%).
* **Debounce de Sensores**: Estabiliza a leitura dos sensores para evitar leituras incorretas.

## Hardware Utilizado

* Placa Bit Dog Lab
* Protoboard
* Resistores (10kΩ e 470Ω)
* CI ULN2003
* Fios para conexão
* Sensores de nível

## Pinagem

```
SENSOR_100: Pino 3
SENSOR_50: Pino 2
SENSOR_0: Pino 4
LEDB (LED Azul): Pino 12
LEDG (LED Verde): Pino 11
LEDR (LED Vermelho): Pino 13
BUZZER_PIN: Pino 21
```

## Especificação do Firmware

* O sistema utiliza lógica condicional para acionar LEDs e buzzer com base nos níveis detectados pelos sensores.
* Link para fluxograma: \[Link para fluxograma]

## Metodologia de Desenvolvimento

1.  **Pesquisa e Referências**: Utilização do repositório BitDogLab e tutorial do YouTube para entender a configuração dos componentes.
2.  **Montagem do Circuito**: Montagem do circuito na protoboard com base no tutorial do YouTube.
3.  **Programação e Testes**: Desenvolvimento e adaptação do código para os sensores de nível, com testes em diferentes níveis de líquido.
4.  **Ajustes Finais**: Ajuste do sistema para garantir estabilidade e confiabilidade.

## Montagem do Circuito

* O circuito utiliza o CI ULN2003 para controlar os LEDs e o buzzer.
* Os sensores de nível são conectados aos pinos 2, 3 e 4 da placa Bit Doglab, com resistores de 10kΩ.
* Os LEDs são conectados ao 5V e controlados pelo ULN2003 com resistores de 470Ω.
* O Buzzer é controlado diretamente pela placa.

## Base Teórica do Circuito

* O circuito envia sinais de 3.3V para a placa Bit Doglab quando os sensores detectam os níveis de 0%, 50% e 100%.
* Os LEDs e o buzzer são acionados de acordo com esses sinais.

## Anexos

* Imagens do circuito montado
* Datasheet do CI ULN2003

## Instalação

* Conecte os sensores de nível aos pinos 2, 3 e 4 da placa Bit Doglab, utilizando resistores de 10kΩ.
* Conecte os LEDs aos pinos 11, 12 e 13 da placa, utilizando resistores de 470Ω e o CI ULN2003.
* Conecte o buzzer ao pino 21 da placa.
* Alimente a placa com 5V.
* Carregue o firmware na placa Bit Doglab.

## Uso

* O sistema monitorará continuamente o nível do reservatório.
* Os LEDs e o buzzer indicarão o nível atual do reservatório.

Espero que este README esteja mais adequado e útil para o seu projeto!
