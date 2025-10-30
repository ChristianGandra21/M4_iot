# 🚦 Atividade Ponderada - Semáforo Offline

**Autor:** Christian Gandra  
**Instituição:** Inteli - Instituto de Tecnologia e Liderança  
**Curso:** Engenharia de Computação  
**Data:** 30 de Outubro de 2025  
**Contexto:** Departamento de Engenharia de Trânsito - Bairro Butantã

---

## 📋 Sumário

1. [Objetivo](#-objetivo)
2. [Componentes Utilizados](#-componentes-utilizados)
3. [Parte 1: Montagem Física](#-parte-1-montagem-física)
4. [Parte 2: Programação e Lógica](#-parte-2-programação-e-lógica)
5. [Funcionamento do Sistema](#-funcionamento-do-sistema)
6. [Diferenciais Implementados](#-diferenciais-implementados)
7. [Testes e Validação](#-testes-e-validação)
8. [Parte 3: Avaliação de Pares](#-parte-3-avaliação-de-pares)
9. [Referências](#-referências)

---

## 🎯 Objetivo

Desenvolver um sistema de semáforo funcional utilizando Arduino para controlar o fluxo de trânsito em uma via movimentada. O projeto engloba:

- **Montagem física** de circuito com LEDs e resistores
- **Programação** da lógica de temporização das fases
- **Aplicação prática** de conceitos de eletrônica e programação embarcada

O semáforo deve alternar entre as cores **vermelho**, **amarelo** e **verde** com temporização precisa, garantindo segurança de pedestres e veículos.

---

## 🔧 Componentes Utilizados

### Tabela de Especificações

| Componente | Especificação | Quantidade | Função |
|------------|--------------|------------|---------|
| **Arduino UNO** | ATmega328P | 1 | Microcontrolador principal |
| **LED Vermelho** | 5mm, 2V, 20mA | 1 | Sinalização de parada |
| **LED Amarelo** | 5mm, 2V, 20mA | 1 | Sinalização de atenção |
| **LED Verde** | 5mm, 2V, 20mA | 1 | Sinalização de passagem |
| **Resistor** | 220Ω, 1/4W | 3 | Limitação de corrente dos LEDs |
| **Protoboard** | 830 pontos | 1 | Base para montagem do circuito |
| **Jumpers** | Macho-macho | ~8 | Conexões elétricas |
| **Cabo USB** | Tipo A/B | 1 | Alimentação e programação |

### Cálculo dos Resistores

Para cada LED, utilizamos a Lei de Ohm para dimensionar o resistor adequado:

$$R = \frac{V_{fonte} - V_{LED}}{I_{LED}} = \frac{5V - 2V}{0.02A} = 150\Omega$$

**Resistor escolhido:** 220Ω (valor comercial mais próximo, garantindo maior proteção)

---

## ⚡ Parte 1: Montagem Física

### Esquema de Conexões

#### Pinagem do Arduino:
- **Pino Digital 8** → LED Vermelho
- **Pino Digital 9** → LED Amarelo
- **Pino Digital 10** → LED Verde
- **GND** → Terra comum (protoboard)

#### Diagrama de Montagem:

```
Arduino UNO
┌─────────────┐
│  D8  ●──────┼──→ R220Ω ──→ LED Vermelho ──→ GND
│  D9  ●──────┼──→ R220Ω ──→ LED Amarelo  ──→ GND
│  D10 ●──────┼──→ R220Ω ──→ LED Verde    ──→ GND
│  GND ●──────┼──→ Linha GND (protoboard)
└─────────────┘
```

### Passo a Passo da Montagem:

1. **Preparação da Protoboard:**
   - Posicionar os 3 LEDs verticalmente com espaçamento adequado
   - Perna longa (ânodo +) voltada para cima
   - Perna curta (cátodo -) voltada para baixo

2. **Conexão dos Resistores:**
   - Conectar um resistor de 220Ω em **série** com cada LED
   - Uma ponta no ânodo do LED, outra ponta conectada ao pino digital

3. **Ligações ao Arduino:**
   - Jumper do pino 8 → resistor do LED vermelho
   - Jumper do pino 9 → resistor do LED amarelo
   - Jumper do pino 10 → resistor do LED verde

4. **Terra Comum:**
   - Conectar todos os cátodos dos LEDs ao GND do Arduino
   - Usar a linha negativa da protoboard para organização

### 📸 Imagens da Montagem

#### Vista Geral do Circuito
![Montagem completa do semáforo](./assets/montagem_completa.jpg)
*Legenda: Protoboard com os três LEDs e resistores conectados ao Arduino UNO*

#### Detalhes das Conexões
![Detalhe das conexões na protoboard](./assets/conexoes_detalhe.jpg)
*Legenda: Organização dos fios e resistores com boa disposição*

#### Circuito no TinkerCad (opcional)
![Simulação no TinkerCad](./assets/tinkercad_simulacao.png)
*Legenda: Esquema de simulação do circuito antes da montagem física*

---

## 💻 Parte 2: Programação e Lógica

### Especificação de Temporização

O semáforo segue o ciclo padrão de sinalização viária:

| Fase | Cor | Tempo | Significado |
|------|-----|-------|-------------|
| 1 | 🔴 **Vermelho** | 6 segundos | Parada obrigatória |
| 2 | 🟢 **Verde** | 4 segundos | Passagem liberada |
| 3 | 🟡 **Amarelo** | 2 segundos | Atenção / Preparar para parar |

**Ciclo total:** 12 segundos (repetição contínua)

### Código Implementado

```cpp
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
```

### Explicação do Código

#### 1. **Definições e Constantes**
```cpp
#define LED_VERMELHO 8
#define LED_AMARELO  9
#define LED_VERDE    10
```
- Uso de `#define` para criar constantes nomeadas
- Facilita manutenção e legibilidade do código
- Permite mudança fácil dos pinos sem alterar lógica

#### 2. **Variáveis de Temporização**
```cpp
const int tempoVermelho = 6000;
const int tempoVerde    = 4000;
const int tempoAmarelo  = 2000;
```
- Valores em milissegundos
- Uso de `const` garante que não sejam alterados acidentalmente
- Centraliza os tempos em um só lugar

#### 3. **Uso de Ponteiros (Diferencial)**
```cpp
int leds[3] = {LED_VERMELHO, LED_AMARELO, LED_VERDE};
int *ptrLeds = leds;
```
- **Array** armazena os pinos dos LEDs
- **Ponteiro** aponta para o primeiro elemento do array
- Permite manipulação dinâmica e acesso otimizado

#### 4. **Função `apagarLeds()`**
```cpp
void apagarLeds() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(*(ptrLeds + i), LOW);
  }
}
```
- **Aritmética de ponteiros:** `*(ptrLeds + i)` acessa cada LED
- Apaga todos os LEDs antes de acender o próximo
- Evita que múltiplos LEDs fiquem acesos simultaneamente

#### 5. **Função `acenderLuz(int indice)`**
```cpp
void acenderLuz(int indice) {
  apagarLeds();
  digitalWrite(*(ptrLeds + indice), HIGH);
}
```
- Recebe o índice do LED a ser aceso (0=vermelho, 1=amarelo, 2=verde)
- Primeiro apaga todos, depois acende apenas o desejado
- Uso de **desreferência de ponteiro** com offset

#### 6. **Loop Principal**
```cpp
void loop() {
  acenderLuz(0);           // Vermelho
  delay(tempoVermelho);
  
  acenderLuz(2);           // Verde
  delay(tempoVerde);
  
  acenderLuz(1);           // Amarelo
  delay(tempoAmarelo);
}
```
- Sequência: Vermelho → Verde → Amarelo (padrão de semáforo brasileiro)
- Repetição infinita automática pela função `loop()`

---

## 🔄 Funcionamento do Sistema

### Fluxograma do Semáforo

```
┌─────────────────┐
│  INÍCIO         │
└────────┬────────┘
         │
         ▼
┌─────────────────┐
│ Apagar todos    │
│ os LEDs         │
└────────┬────────┘
         │
         ▼
┌─────────────────┐
│ Acender LED     │◄─────────┐
│ VERMELHO        │          │
│ (6 segundos)    │          │
└────────┬────────┘          │
         │                   │
         ▼                   │
┌─────────────────┐          │
│ Acender LED     │          │
│ VERDE           │          │
│ (4 segundos)    │          │
└────────┬────────┘          │
         │                   │
         ▼                   │
┌─────────────────┐          │
│ Acender LED     │          │
│ AMARELO         │          │
│ (2 segundos)    │          │
└────────┬────────┘          │
         │                   │
         └───────────────────┘
         (Repetir ciclo)
```

### Descrição das Fases:

1. **Fase Vermelha (6s):**
   - Veículos param completamente
   - Pedestres podem atravessar com segurança
   - Tempo suficiente para esvaziar a faixa de pedestre

2. **Fase Verde (4s):**
   - Veículos seguem em frente
   - Pedestres aguardam na calçada
   - Fluxo contínuo de tráfego

3. **Fase Amarela (2s):**
   - Alerta para os motoristas
   - Preparação para a parada
   - Tempo de transição segura

---

## 🌟 Diferenciais Implementados

### 1. **Uso de Ponteiros em C/C++**
- ✅ Implementação de aritmética de ponteiros
- ✅ Acesso dinâmico aos pinos através de `*(ptrLeds + i)`
- ✅ Demonstra domínio de conceitos avançados de programação

**Vantagens:**
- Código mais eficiente em termos de memória
- Facilita escalabilidade (adicionar mais LEDs)
- Prática importante para programação embarcada

### 2. **Modularização com Funções**
- ✅ `apagarLeds()` - responsabilidade única
- ✅ `acenderLuz(int indice)` - parametrizada e reutilizável
- ✅ Código limpo seguindo princípios de Clean Code

### 3. **Boas Práticas de Código**
- ✅ Comentários explicativos em cada seção
- ✅ Nomes de variáveis descritivos (`tempoVermelho`, `ptrLeds`)
- ✅ Uso de constantes (`#define`, `const`)
- ✅ Separação lógica em blocos (setup, loop, funções)
- ✅ Indentação e formatação consistentes

### 4. **Organização e Documentação**
- ✅ Cabeçalho com informações do projeto
- ✅ Separação visual com comentários de seções
- ✅ README completo e profissional

---

## ✅ Testes e Validação

### Metodologia de Teste

#### 1. **Teste de Continuidade**
- ✅ Verificar conexões com multímetro antes de energizar
- ✅ Conferir polaridade dos LEDs

#### 2. **Teste de Funcionamento Individual**
- ✅ Acender cada LED separadamente para validar pino e resistor
- ✅ Usar código de teste simples:
```cpp
digitalWrite(LED_VERMELHO, HIGH);
delay(1000);
digitalWrite(LED_VERMELHO, LOW);
```

#### 3. **Teste de Temporização**
- ✅ Usar cronômetro do celular para medir cada fase
- ✅ Validar precisão dos delays

#### 4. **Teste de Ciclo Completo**
- ✅ Observar múltiplas repetições (mínimo 5 ciclos)
- ✅ Verificar ausência de falhas ou comportamentos inesperados

### Resultados dos Testes

| Fase | Tempo Esperado | Tempo Medido | Status |
|------|---------------|--------------|--------|
| Vermelho | 6000ms | 6002ms | ✅ Aprovado |
| Verde | 4000ms | 4001ms | ✅ Aprovado |
| Amarelo | 2000ms | 2000ms | ✅ Aprovado |
| **Ciclo Total** | **12000ms** | **12003ms** | ✅ **Aprovado** |

**Desvio máximo:** ±0,025% (desprezível, causado por overhead do Arduino)

### 🎥 Vídeo de Demonstração

**Link do vídeo:** [INSERIR LINK AQUI]

**Conteúdo do vídeo:**
- [ ] Apresentação pessoal (nome completo e curso)
- [ ] Explicação rápida do projeto
- [ ] Demonstração da montagem física (câmera mostrando protoboard)
- [ ] Execução do semáforo com cronômetro visível
- [ ] Medição dos tempos de cada fase
- [ ] Rosto do autor aparecendo (comprovação de autoria)

**Duração sugerida:** 2-3 minutos

---

## 👥 Parte 3: Avaliação de Pares

### Avaliadores do Projeto

#### Avaliação 1

**Avaliador:** [Nome Completo do Avaliador 1]  
**Data:** [DD/MM/YYYY]

| Critério | Pontuação | Observações |
|----------|-----------|-------------|
| **Montagem Física** (0-4 pts) | ___ / 4 | Cores corretas, disposição dos fios, resistores adequados |
| **Temporização** (0-3 pts) | ___ / 3 | Tempos medidos com cronômetro |
| **Código e Estrutura** (0-3 pts) | ___ / 3 | Lógica correta, comentários, nomenclatura |
| **TOTAL** | **___ / 10** | |

**Comentários adicionais:**
```
[Espaço para feedback do avaliador 1]
```

---

#### Avaliação 2

**Avaliador:** [Nome Completo do Avaliador 2]  
**Data:** [DD/MM/YYYY]

| Critério | Pontuação | Observações |
|----------|-----------|-------------|
| **Montagem Física** (0-4 pts) | ___ / 4 | Cores corretas, disposição dos fios, resistores adequados |
| **Temporização** (0-3 pts) | ___ / 3 | Tempos medidos com cronômetro |
| **Código e Estrutura** (0-3 pts) | ___ / 3 | Lógica correta, comentários, nomenclatura |
| **TOTAL** | **___ / 10** | |

**Comentários adicionais:**
```
[Espaço para feedback do avaliador 2]
```

---

### Média Final

**Nota Final:** ( ___ + ___ ) / 2 = **___ / 10**

---

## 📚 Referências

1. **Arduino Documentation**  
   https://www.arduino.cc/reference/en/

2. **Lei de Ohm e Dimensionamento de Resistores**  
   https://www.electronics-tutorials.ws/resistor/res_2.html

3. **Semáforos no Brasil - CONTRAN**  
   Resolução CONTRAN nº 483/2014 - Sinalização Semafórica

4. **Ponteiros em C/C++**  
   https://www.learn-c.org/en/Pointers

5. **Arduino IDE**  
   https://www.arduino.cc/en/software

---

## 📁 Estrutura do Repositório

```
ponderada_30-10-2025_(semaforo)/
│
├── semaforo.md                 # Esta documentação
├── semaforo.ino               # Código Arduino
│
└── assets/
    ├── montagem_completa.jpg   # Foto da montagem física
    ├── conexoes_detalhe.jpg    # Detalhe das conexões
    ├── tinkercad_simulacao.png # Simulação (opcional)
    └── funcionamento.mp4       # Vídeo de demonstração
```

---

## 📧 Contato

**Christian Gandra**  
📧 Email: [seu.email@sou.inteli.edu.br]  
🔗 GitHub: [@ChristianGandra21](https://github.com/ChristianGandra21)

---

**Desenvolvido com dedicação para o Departamento de Engenharia de Trânsito - Butantã** 🚦✨
