// Importa a biblioteca DHT
#include <DHT.h>

// Definição dos pinos dos sensores
#define pinoPIR 22       // Pino para o sensor PIR
#define pinoDHT 12       // Pino para o DHT22
#define pinoLDR 14       // Pino para o LDR (sensor de intensidade da luz solar)

// Definição do tipo de sensor DHT
#define tipoDHT DHT22
DHT dht(pinoDHT, tipoDHT);

void setup() {
  // Inicialização da comunicação serial
  Serial.begin(115200);

  // Configuração dos pinos dos sensores
  pinMode(pinoPIR, INPUT);
  pinMode(pinoLDR, INPUT);

  // Inicialização do sensor DHT22
  dht.begin();
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

  // --- Delay antes da próxima leitura ---
  delay(5000);  // Aguarda 5 segundos antes da próxima leitura
}