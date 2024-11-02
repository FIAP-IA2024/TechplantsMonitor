// Definindo o pino onde o sensor PIR está conectado
#define pinoPIR 22  // Pino para o sensor PIR

void setup() {
  // Inicializando a comunicação serial
  Serial.begin(115200);

  // Configurando o pino do sensor PIR como entrada
  pinMode(pinoPIR, INPUT);
}

void loop() {
  // Leitura do estado do sensor PIR
  int pirValue = digitalRead(pinoPIR);

  // Verifica se o sensor detectou movimento
  if (pirValue == HIGH) {
    Serial.println("Movimento detectado! Alarme acionado!");
  }

  delay(5000);  // Aguarda 5 segundos antes da próxima leitura
}