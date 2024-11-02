// Importa a biblioteca DHT
#include <DHT.h>

// Definição dos pinos dos sensores e atuadores
#define pinoPIR 22       // Pino para o sensor PIR
#define pinoDHT 12       // Pino para o DHT22
#define pinoLDR 14       // Pino para o LDR (sensor de intensidade da luz solar)
#define trigPin 17       // Pino GPIO conectado ao Trig do HC-SR04
#define echoPin 16       // Pino GPIO conectado ao Echo do HC-SR04
#define pinoRele 32      // Pino de controle para ativação do relé

// Definição do tipo de sensor DHT
#define tipoDHT DHT22
DHT dht(pinoDHT, tipoDHT);

// --- Variáveis e Parâmetros ---
const int alturaReservatorio = 400;  // Altura do reservatório em centímetros
const int nivelMaximo = 400000;      // Nível máximo do reservatório em litros
const int nivelMinimo = 10000;       // Nível mínimo do reservatório em litros

// Limiares para controle
const float umidadeMinima = 40.0;    // Umidade mínima em porcentagem
const float temperaturaMaxima = 30.0; // Temperatura máxima em Celsius
const int limiarLDR = 3000;          // Limiar para o valor do LDR (ajuste conforme necessário)

void setup() {
  // Inicialização da comunicação serial
  Serial.begin(115200);

  // Configuração dos pinos dos sensores
  pinMode(pinoPIR, INPUT);
  pinMode(pinoLDR, INPUT);

  // Inicialização do sensor DHT22
  dht.begin();

  // Configuração dos pinos do HC-SR04
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Configuração do pino do relé
  pinMode(pinoRele, OUTPUT);
  digitalWrite(pinoRele, LOW); // Garante que o relé esteja desligado no início
}

void loop() {
  // --- Leitura do Sensor PIR ---
  int pirValue = digitalRead(pinoPIR);

  // Verifica se o sensor PIR detectou movimento
  if (pirValue == HIGH) {
    Serial.println("Movimento detectado! Alarme acionado!");
  }

  // --- Leitura do Sensor DHT22 ---
  float umidade = dht.readHumidity();
  float temperatura = dht.readTemperature();

  // Verifica se a leitura do DHT falhou
  if (isnan(umidade) || isnan(temperatura)) {
    Serial.println("Falha ao ler o DHT!");
  } else {
    // Exibição dos valores de temperatura e umidade
    Serial.print("Temperatura: ");
    Serial.print(temperatura);
    Serial.println(" °C");

    Serial.print("Umidade: ");
    Serial.print(umidade);
    Serial.println(" %");
  }

  // --- Leitura do Sensor LDR ---
  int valorLDR = analogRead(pinoLDR);

  // Exibição do valor da luminosidade
  Serial.print("Luminosidade (LDR): ");
  Serial.println(valorLDR);

  // --- Leitura do Nível de Água com o HC-SR04 ---
  unsigned long duracao;
  unsigned int distancia;

  // Envia um pulso de 10us para o Trig
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Calcula o tempo de duração do pulso de retorno no Echo
  duracao = pulseIn(echoPin, HIGH, 30000);  // Timeout de 30ms

  // Calcula a distância em centímetros
  distancia = duracao * 0.034 / 2;

  int nivel = 0;  // Variável para armazenar o nível calculado

  // Verifica se a distância está dentro do esperado
  if (distancia <= 0 || distancia > alturaReservatorio) {
    Serial.println("Leitura do nível de água fora de alcance");
  } else {
    // Calcula o nível atual do reservatório
    nivel = (alturaReservatorio - distancia) * (nivelMaximo / alturaReservatorio);
    nivel = constrain(nivel, 0, nivelMaximo);

    // Exibe o nível da água
    Serial.print("Nível da Água: ");
    Serial.print(nivel);
    Serial.print(" / ");
    Serial.print(nivelMaximo);
    Serial.println(" Litros");

    // Mensagens sobre o estado do reservatório
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
      Serial.println("Reservatório em estado CRÍTICO - Ação imediata necessária!");
    }
  }

  // --- Controle do Relé (Irrigação) ---
  if (((umidade < umidadeMinima) || (temperatura > temperaturaMaxima)) && (valorLDR < limiarLDR) && (nivel > nivelMinimo)) {
    digitalWrite(pinoRele, HIGH); // Liga o relé
    Serial.println("Irrigação LIGADA");
  } else {
    digitalWrite(pinoRele, LOW); // Desliga o relé
    Serial.println("Irrigação DESLIGADA");
  }

  // --- Delay antes da próxima leitura ---
  delay(5000);  // Aguarda 5 segundos antes da próxima leitura
}