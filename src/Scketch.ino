// Importa a biblioteca DHT
#include <DHT.h>

// Definindo o pino onde o sensor DHT22 está conectado
#define pinoDHT 12       // Pino para o DHT22

// Definindo o tipo de sensor DHT
#define tipoDHT DHT22
DHT dht(pinoDHT, tipoDHT);

void setup() {
  // Inicializando a comunicação serial
  Serial.begin(115200);

  // Inicializando o sensor DHT22
  dht.begin();
}

void loop() {
  // Leitura da umidade e temperatura
  float umidade = dht.readHumidity();
  float temperatura = dht.readTemperature();

  // Verifica se a leitura falhou
  if (isnan(umidade) || isnan(temperatura)) {
    Serial.println("Falha ao ler o DHT!");
    return;
  }

  // Exibição dos valores no Serial Monitor
  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println(" °C");

  Serial.print("Umidade: ");
  Serial.print(umidade);
  Serial.println(" %");

  delay(5000);  // Aguarda 5 segundos antes da próxima leitura
}
