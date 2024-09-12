//Este arquivo será utilizado para a formação do codigo em C
//O carrinho terá sensores ultrasonico e sensores de linha

// Definindo os pinos da ponte H (Motores)
int IN1 = 2;  // Pino do Arduino conectado ao IN1 da ponte H (Motor 1)
int IN2 = 3;  // Pino do Arduino conectado ao IN2 da ponte H (Motor 1)
int IN3 = 4;  // Pino do Arduino conectado ao IN3 da ponte H (Motor 2)
int IN4 = 5;  // Pino do Arduino conectado ao IN4 da ponte H (Motor 2)

// Definindo os pinos do sensor ultrassônico
const int trigPin = 10;  // Pino TRIG do sensor ultrassônico
const int echoPin = 11;  // Pino ECHO do sensor ultrassônico

// Definindo os pinos dos sensores de linha
const int lineSensorRear = 8;  // Sensor de linha traseiro
const int lineSensorFront = 9; // Sensor de linha dianteiro

// Variáveis para armazenar o tempo e a distância do ultrassônico
long duration;
int distance;

// Variáveis para armazenar leituras dos sensores de linha
int rearSensorState;
int frontSensorState;

void setup() {
  // Configurando os pinos dos motores como saída
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Configurando os pinos do sensor ultrassônico
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Configurando os pinos dos sensores de linha como entrada
  pinMode(lineSensorRear, INPUT);
  pinMode(lineSensorFront, INPUT);

  // Inicializando a comunicação serial para monitoramento (opcional)
  Serial.begin(9600);

  // Delay inicial de 5 segundos antes de começar
  delay(5000);
}

void loop() {
  // Medindo a distância usando o sensor ultrassônico
  distance = getDistance();

  // Lendo o estado dos sensores de linha
  rearSensorState = digitalRead(lineSensorRear);
  frontSensorState = digitalRead(lineSensorFront);

  // Exibindo a distância medida e o estado dos sensores no monitor serial (opcional)
  Serial.print("Distancia: ");
  Serial.print(distance);
  Serial.println(" cm");

  Serial.print("Sensor de linha traseiro: ");
  Serial.println(rearSensorState);
  
  Serial.print("Sensor de linha dianteiro: ");
  Serial.println(frontSensorState);

  // Se o ultrassônico detectar um oponente a 20 cm ou menos
  if (distance <= 25) {
    // Continuar avançando se o oponente estiver à frente e a borda preta ainda não foi detectada
    if (frontSensorState == HIGH) {
      moveForward();
    } 
    // Se o sensor de linha dianteiro detectar a borda preta, mover para trás e procurar o próximo oponente
    else if (frontSensorState == LOW) {
      moveBackward();  // Andar para trás ao detectar a borda preta
      delay(1000);     // Duração do movimento para trás (ajustável)

      // Após andar para trás, procurar o próximo oponente
      stopMotors();    // Parar os motores
      searchOpponent();
    }
  } 
  // Caso o sensor traseiro detecte a borda preta
  else if (rearSensorState == LOW) {
    // Andar para frente buscando oponente
    moveForward();
  } 
  // Se o sensor traseiro não detectar a borda preta e não houver oponente
  else {
    stopMotors();  // Parar os motores
  }

  delay(100);  // Pequeno atraso para evitar leituras repetitivas muito rápidas
}

// Função para calcular a distância com base no tempo de retorno do sinal ultrassônico
int getDistance() {
  // Limpar o pino TRIG
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Enviar um pulso de 10 microssegundos no TRIG
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Ler o tempo de retorno no pino ECHO
  duration = pulseIn(echoPin, HIGH);

  // Calcular a distância (tempo x velocidade do som: 340 m/s)
  // A fórmula é (tempo * 0.034) / 2
  int dist = duration * 0.034 / 2;

  return dist;
}

// Função para acionar os motores e mover para frente
void moveForward() {
  digitalWrite(IN1, HIGH);  // Motor 1 gira para frente
  digitalWrite(IN2, LOW);   // Direção do Motor 1

  digitalWrite(IN3, HIGH);  // Motor 2 gira para frente
  digitalWrite(IN4, LOW);   // Direção do Motor 2
}

// Função para acionar os motores e mover para trás
void moveBackward() {
  digitalWrite(IN1, LOW);   // Motor 1 gira para trás
  digitalWrite(IN2, HIGH);  // Direção do Motor 1

  digitalWrite(IN3, LOW);   // Motor 2 gira para trás
  digitalWrite(IN4, HIGH);  // Direção do Motor 2
}

// Função para parar os motores
void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

// Função para procurar o próximo oponente
void searchOpponent() {
  // A lógica de procurar o oponente pode ser uma rotação em busca de um novo oponente
  // Exemplo: girar até encontrar um novo oponente (simples rotação)
  digitalWrite(IN1, HIGH);  // Motor 1 gira para frente
  digitalWrite(IN2, LOW);   // Direção do Motor 1

  digitalWrite(IN3, LOW);   // Motor 2 gira para trás
  digitalWrite(IN4, HIGH);  // Direção do Motor 2
  
  delay(1500);  // Tempo de rotação (ajustável)
  
  stopMotors();  // Parar após a rotação
}
