// Definição dos pinos do sensor
int trigPin = 11;
int echoPin = 10;

// Variável para armazenar a distância
long duracao;
int distancia;

void setup() {
  // Iniciar a comunicação serial
  Serial.begin(9600);
  
  // Definir pinos como saída e entrada
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // Enviar pulso ultrassônico
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Medir o tempo do eco
  duracao = pulseIn(echoPin, HIGH);
  
  // Calcular a distância em cm
  distancia = duracao * 0.034 / 2;
  
  // Exibir a distância no monitor serial
  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.println(" cm");

  delay(500);
}
