// Importa a biblioteca DHT
#include <DHT.h>

// Definição dos pinos dos sensores e atuadores
#define PINO_PIR 22       // Pino para o sensor PIR
#define PINO_DHT 12       // Pino para o DHT22
#define PINO_LDR 14       // Pino para o LDR (sensor de intensidade da luz solar)
#define TRIG_PIN 17       // Pino GPIO conectado ao Trig do HC-SR04
#define ECHO_PIN 16       // Pino GPIO conectado ao Echo do HC-SR04
#define PINO_RELE 32      // Pino de controle para ativação do relé

// Definição do tipo de sensor DHT
#define TIPO_DHT DHT22
DHT dht(PINO_DHT, TIPO_DHT);

// --- Variáveis e Parâmetros ---
const int ALTURA_RESERVATORIO = 400;    // Altura do reservatório em centímetros
const int NIVEL_MAXIMO = 400000;        // Nível máximo do reservatório em litros
const int NIVEL_MINIMO = 10000;         // Nível mínimo do reservatório em litros

// Limiares para controle
const float UMIDADE_MINIMA = 40.0;      // Umidade mínima em porcentagem
const float TEMPERATURA_MAXIMA = 30.0;  // Temperatura máxima em Celsius
const int LIMIAR_LDR = 3000;            // Limiar para o valor do LDR (ajuste conforme necessário)

// Variáveis globais
float umidade = 0.0;
float temperatura = 0.0;
int valorLDR = 0;
int nivel = 0;

void setup() {
  // Inicialização da comunicação serial
  Serial.begin(115200);

  // Configuração dos pinos dos sensores
  pinMode(PINO_PIR, INPUT);
  pinMode(PINO_LDR, INPUT);

  // Inicialização do sensor DHT22
  dht.begin();

  // Configuração dos pinos do HC-SR04
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Configuração do pino do relé
  pinMode(PINO_RELE, OUTPUT);
  digitalWrite(PINO_RELE, LOW); // Garante que o relé esteja desligado no início
}

void loop() {
  lerSensorPIR();
  lerSensorDHT22();
  lerSensorLDR();
  lerNivelAgua();
  controlarIrrigacao();
  delay(5000);  // Aguarda 5 segundos antes da próxima leitura
}

// --- Funções Auxiliares ---

void lerSensorPIR() {
  int pirValue = digitalRead(PINO_PIR);

  if (pirValue == HIGH) {
    Serial.println("Movimento detectado! Alarme acionado!");
  }
}

void lerSensorDHT22() {
  umidade = dht.readHumidity();
  temperatura = dht.readTemperature();

  if (isnan(umidade) || isnan(temperatura)) {
    Serial.println("Falha ao ler o DHT!");
  } else {
    Serial.print("Temperatura: ");
    Serial.print(temperatura);
    Serial.println(" °C");

    Serial.print("Umidade: ");
    Serial.print(umidade);
    Serial.println(" %");

    if (umidade < UMIDADE_MINIMA) {
      Serial.println("ALERTA: Umidade baixa! Condições secas podem prejudicar as plantas.");
    }

    if (temperatura > TEMPERATURA_MAXIMA) {
      Serial.println("ALERTA: Temperatura alta! Condições de calor extremo detectadas.");
    }
  }
}

void lerSensorLDR() {
  valorLDR = analogRead(PINO_LDR);

  Serial.print("Luminosidade (LDR): ");
  Serial.println(valorLDR);
}

void lerNivelAgua() {
  unsigned long duracao;
  unsigned int distancia;

  // Envia um pulso de 10us para o Trig
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Calcula o tempo de duração do pulso de retorno no Echo
  duracao = pulseIn(ECHO_PIN, HIGH, 30000);  // Timeout de 30ms

  // Calcula a distância em centímetros
  distancia = duracao * 0.034 / 2;

  // Verifica se a distância está dentro do esperado
  if (distancia <= 0 || distancia > ALTURA_RESERVATORIO) {
    Serial.println("Leitura do nível de água fora de alcance");
  } else {
    // Calcula o nível atual do reservatório
    nivel = (ALTURA_RESERVATORIO - distancia) * (NIVEL_MAXIMO / ALTURA_RESERVATORIO);
    nivel = constrain(nivel, 0, NIVEL_MAXIMO);

    Serial.print("Nível da Água: ");
    Serial.print(nivel);
    Serial.print(" / ");
    Serial.print(NIVEL_MAXIMO);
    Serial.println(" Litros");

    exibirEstadoReservatorio(distancia);

    if (nivel <= NIVEL_MINIMO) {
      Serial.println("ALERTA: Nível de água abaixo do mínimo necessário para irrigação.");
    }
  }
}

void exibirEstadoReservatorio(int distancia) {
  if (distancia <= 39) {
    Serial.println("Reservatório em estado ÓTIMO - Nível de água acima de 90%");
  } else if (distancia <= 100) {
    Serial.println("Reservatório em estado BOM - Nível de água entre 75% e 90%");
  } else if (distancia <= 200) {
    Serial.println("Reservatório em estado NORMAL - Nível de água entre 50% e 74%");
  } else if (distancia <= 300) {
    Serial.println("Reservatório em estado de RISCO - Nível de água entre 25% e 49%");
  } else if (distancia <= 398) {
    Serial.println("Reservatório em estado MÍNIMO - Nível de água abaixo de 25%");
  } else {
    Serial.println("ALERTA CRÍTICO: Reservatório quase vazio! Ação imediata necessária!");
  }
}

void controlarIrrigacao() {
  bool condicoesIrrigacao = ((umidade < UMIDADE_MINIMA) || (temperatura > TEMPERATURA_MAXIMA)) &&
                            (valorLDR < LIMIAR_LDR) &&
                            (nivel > NIVEL_MINIMO);

  if (condicoesIrrigacao) {
    digitalWrite(PINO_RELE, HIGH); // Liga o relé
    Serial.println("Irrigação LIGADA");
  } else {
    digitalWrite(PINO_RELE, LOW); // Desliga o relé
    Serial.println("Irrigação DESLIGADA");
  }
}