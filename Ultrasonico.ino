// --- Configuração dos Pinos ---
const int PINO_TRIG = 21;        // Pino de disparo (Trigger)
const int PINO_ECHO = 22;        // Pino de retorno (Echo)
const int PINO_LED_INTRUSO = 23; // LED indicador

// --- Protótipo da Função ---
float obter_distancia();

void setup() {

  Serial.begin(115200);

  // Configuração dos pinos
  pinMode(PINO_TRIG, OUTPUT);      // Trig envia o pulso
  pinMode(PINO_ECHO, INPUT);       // Echo recebe o pulso
  pinMode(PINO_LED_INTRUSO, OUTPUT);

  // Garante que o Trigger começa desligado
  digitalWrite(PINO_TRIG, LOW);
}

void loop() {

  float dist = obter_distancia();

  Serial.print("Distancia: ");
  Serial.print(dist);
  Serial.println(" cm");

  // --- Ação e decisão ---
  if (dist > 0 && dist < 10) {

    Serial.println("INTRUSO DETECTADO!");
    digitalWrite(PINO_LED_INTRUSO, HIGH);

  } 
  else {

    Serial.println("Ambiente seguro.");
    digitalWrite(PINO_LED_INTRUSO, LOW);

  }

  delay(1000); // Aguarda 3 segundos
}


// --- Função para medir distância ---
float obter_distancia() {

  // Envia pulso de 10 microsegundos
  digitalWrite(PINO_TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(PINO_TRIG, HIGH);
  delayMicroseconds(10);

  digitalWrite(PINO_TRIG, LOW);

  // Mede o tempo do Echo
  long duracao = pulseIn(PINO_ECHO, HIGH, 30000);

  // Calcula distância
  float distancia = (duracao / 2.0) * 0.0343;

  return distancia;
}