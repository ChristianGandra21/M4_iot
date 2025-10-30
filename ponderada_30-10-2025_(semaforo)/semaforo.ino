// === SEMÁFORO OFFLINE - ATIVIDADE PONDERADA ===
// Autor: Christian Gandra
// Curso: Programação e Eletrônica Básica
// Descrição: Controle de semáforo com ponteiros e temporização

// ==== DEFINIÇÃO DOS PINOS ====
#define LED_VERMELHO 8
#define LED_AMARELO  9
#define LED_VERDE    10

// ==== TEMPOS DE CADA FASE (em milissegundos) ====
const int tempoVermelho = 6000;  // 6 segundos
const int tempoVerde    = 4000;  // 4 segundos
const int tempoAmarelo  = 2000;  // 2 segundos

// ==== ARRAY DE LEDS E PONTEIRO ====
int leds[3] = {LED_VERMELHO, LED_AMARELO, LED_VERDE};
int *ptrLeds = leds;  // ponteiro apontando para o primeiro elemento do array

// ==== FUNÇÕES AUXILIARES ====
void apagarLeds() {
  // percorre o array usando ponteiro e apaga todos os LEDs
  for (int i = 0; i < 3; i++) {
    digitalWrite(*(ptrLeds + i), LOW);
  }
}

void acenderLuz(int indice) {
  apagarLeds();
  digitalWrite(*(ptrLeds + indice), HIGH); // acende o LED indicado
}

void setup() {
  // configuração inicial
  for (int i = 0; i < 3; i++) {
    pinMode(*(ptrLeds + i), OUTPUT);
  }

  // inicia com todos apagados
  apagarLeds();
}

void loop() {
  // Vermelho aceso por 6 segundos
  acenderLuz(0); // *(ptrLeds + 0) → LED_VERMELHO
  delay(tempoVermelho);

  // Verde aceso por 4 segundos
  acenderLuz(2); // *(ptrLeds + 2) → LED_VERDE
  delay(tempoVerde);

  // Amarelo aceso por 2 segundos
  acenderLuz(1); // *(ptrLeds + 1) → LED_AMARELO
  delay(tempoAmarelo);
}
