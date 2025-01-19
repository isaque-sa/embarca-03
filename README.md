# Controlador de LEDs e Buzzer para Raspberry Pi Pico W

Este projeto é uma aplicação simples para controlar LEDs RGB e um buzzer utilizando o Raspberry Pi Pico W. Permite o controle de LEDs e do comportamento do buzzer por meio de comandos de teclado.

---

## Recursos

- **Controle de LEDs RGB**:
  - Ligar LEDs individuais (Vermelho, Verde, Azul).
  - Combinar LEDs para cores adicionais, como branco.
  - Desligar todos os LEDs.

- **Controle do Buzzer**:
  - Emitir um tom sonoro por uma duração específica.

- **Reinicializar o Pico**:
  - Reiniciar a placa em modo de boot USB usando um comando de teclado.

---

## Comandos de Teclado

| Tecla | Ação                          |
|-------|-------------------------------|
| `r`   | Liga o LED Vermelho.          |
| `g`   | Liga o LED Verde.             |
| `b`   | Liga o LED Azul.              |
| `w`   | Liga todos os LEDs (Branco).  |
| `o`   | Desliga todos os LEDs.        |
| `z`   | Ativa o buzzer.               |
| `q`   | Reinicia o Pico no modo USB.  |

---

## Requisitos de Hardware

1. **Raspberry Pi Pico W**.
2. **LEDs RGB** conectados aos seguintes pinos:
   - **Vermelho**: GPIO 13.
   - **Verde**: GPIO 11.
   - **Azul**: GPIO 12.
3. **Buzzer** conectado ao GPIO 21.

---

## Como Funciona

1. **Inicialização**:
   - Os pinos GPIO para os LEDs RGB são configurados como saída.
   - O buzzer é configurado para usar PWM para gerar som.

2. **Controle por Teclado**:
   - O programa lê caracteres da entrada padrão.
   - Baseado no comando, aciona o comportamento correspondente no LED ou no buzzer.

3. **Função de Reinicialização**:
   - O comando `q` reinicia o dispositivo no modo USB.

---

## Pré-requisitos

- **SDK do Pico**: Configure o ambiente conforme o guia oficial do Raspberry Pi.
- **CMake**: Certifique-se de que o CMake está instalado.
- **Comunicação Serial**: Um emulador de terminal (como PuTTY ou minicom) para enviar comandos.

---

## Como Compilar e Executar o Código

1. **Configurar o SDK do Pico**:
   - Siga o guia oficial de configuração do SDK do Pico.

2. **Clonar este repositório**:
   ```bash
   git clone <url-do-repositorio>
   cd <nome-do-repositorio>


## Demonstração do Projeto

### Assista ao vídeo abaixo:

<iframe src="https://vimeo.com/1044007903" width="640" height="360" frameborder="0" allow="autoplay; fullscreen; picture-in-picture" allowfullscreen></iframe>

### Ou clique no link:
[Veja no Vimeo](https://vimeo.com/1044007903)
