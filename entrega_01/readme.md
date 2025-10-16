# Entrega 01 — Blink Interno e Simulação no Tinkercad

Este repositório contém as evidências das atividades de IoT referentes ao Blink interno do Arduino (Parte 1) e à simulação de um blink externo no Tinkercad (Parte 2).

## Parte 1 — Blink com LED Interno (on-board)

Objetivo: Fazer o LED interno do Arduino piscar, mantendo-o aceso por X ms, apagado por Y ms, continuamente.

Passos realizados:

- Instalação e configuração da Arduino IDE.
- Seleção da placa correta (Arduino Uno) e porta serial.
- Upload do código de blink no LED interno (pino LED_BUILTIN, normalmente 13).

Exemplo de código utilizado (referência):

```cpp
// Mantém o LED interno aceso por X ms e apagado por Y ms
// Ajuste os valores de X e Y conforme desejado
void setup() {
	pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
	digitalWrite(LED_BUILTIN, HIGH); // acende
	delay(500); // X ms
	digitalWrite(LED_BUILTIN, LOW);  // apaga
	delay(500); // Y ms
}
```

Evidências a seguir.

### Vídeo (Parte 1)

- Link do vídeo: [INSIRA AQUI]

### Imagens (Parte 1)

- Screenshot da Arduino IDE com o código: [INSIRA AQUI]
- Foto do Arduino conectado com LED aceso: [INSIRA AQUI]

---

## Parte 2 — Simulação de Blink Externo no Tinkercad

Objetivo: Montar no Tinkercad um circuito com Arduino Uno, protoboard, LED off-board e resistor, executando um pisca-pisca de qualquer cadência. Ao iniciar a simulação (Play), o projeto deve rodar sem erros.

Passos realizados:

- Montagem do circuito no Tinkercad (Arduino, protoboard, LED off-board, resistor e fios).
- Definição do pino (ex.: 13 ou 6) como saída: pinMode(PINO, OUTPUT);
- Comando de pisca usando digitalWrite(PINO, HIGH/LOW) e delay.

Tinkercad — Código usado (obtido da simulação):

```cpp
// Exemplo: LED no pino 13 via resistor
const int PINO_LED = 13;

void setup() {
	pinMode(PINO_LED, OUTPUT);
}

void loop() {
	digitalWrite(PINO_LED, HIGH);
	delay(400); // ligado
	digitalWrite(PINO_LED, LOW);
	delay(400); // desligado
}
```

### Link do Projeto no Tinkercad (Parte 2)

- URL: [INSIRA AQUI]

### Vídeo (Parte 2)

- Link do vídeo: [INSIRA AQUI]

### Imagens (Parte 2)

- Screenshot da simulação no Tinkercad com o circuito: [INSIRA AQUI]

---

## Observações

- Subir as screenshots e fotos na pasta `entrega_01/assets/` e referenciá-las aqui quando disponíveis.
- Caso os tempos X e Y sejam alterados, atualizar os comentários no código para manter a documentação coerente.

## Como Executar (referência rápida)

- Parte 1: Abrir a Arduino IDE, selecionar placa e porta, colar o código, compilar e fazer upload.
- Parte 2: Abrir o link do Tinkercad, clicar em Play para iniciar a simulação. Copiar o código gerado e publicá-lo neste repositório.
