// Definindo os pinos da ponte H (Motores)
int IN1 = 2;  // Pino do Arduino conectado ao IN1 da ponte H (Motor 1)
int IN2 = 3;  // Pino do Arduino conectado ao IN2 da ponte H (Motor 1)
int IN3 = 4;  // Pino do Arduino conectado ao IN3 da ponte H (Motor 2)
int IN4 = 5;  // Pino do Arduino conectado ao IN4 da ponte H (Motor 2)

// Definindo os pinos do sensor ultrassônico
const int trigPin = 10;  // Pino TRIG do sensor ultrassônico
const int echoPin = 11;  // Pino ECHO do sensor ultrassônico

// Definindo o pino do sensor de linha dianteiro
const int lineSensorFront = A3; // Sensor de linha dianteiro

// Variáveis para armazenar o tempo e a distância do ultrassônico
long duration;
int distance;

// Variável para armazenar a leitura do sensor de linha dianteiro
int frontSensorState;

bool searchingOpponent = false;  // Variável para indicar se está no modo de busca

void setup() {
  // Configurando os pinos dos motores como saída
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Configurando os pinos do sensor ultrassônico
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Configurando o pino do sensor de linha como entrada
  pinMode(lineSensorFront, INPUT);

  // Inicializando a comunicação serial para monitoramento (opcional)
  Serial.begin(9600);

  // Delay inicial de 5 segundos antes de começar
  delay(20000);
}

void loop() {
  // Medindo a distância usando o sensor ultrassônico
  distance = getDistance();

  // Lendo o estado do sensor de linha dianteiro
  frontSensorState = digitalRead(lineSensorFront);

  // Exibindo a distância medida e o estado do sensor no monitor serial (opcional)
  Serial.print("Distancia: ");
  Serial.print(distance);
  Serial.println(" cm");

  Serial.print("Sensor de linha dianteiro: ");
  Serial.println(frontSensorState);

  // Se o ultrassônico detectar um oponente a 20 cm ou menos
  if (distance <= 25) {
    searchingOpponent = false;  // Sai do modo de busca

    // Continuar avançando se o oponente estiver à frente e a borda branca ainda não foi detectada
    if (frontSensorState == HIGH) {
      moveForward();  // Continuar empurrando o oponente
    } 
    // Se o sensor de linha dianteiro detectar a borda branca, mover para trás e procurar o próximo oponente
    else if (frontSensorState == LOW) {
      moveBackward();  // Andar para trás ao detectar a borda branca
      delay(500);     // Duração do movimento para trás (ajustável)

      // Após andar para trás, girar para continuar procurando o próximo oponente
      turn180();
    }
  } 
  // Caso não haja oponente à frente, continuar no modo de busca
  else {
    if (searchingOpponent) {
      // Se encontrar a borda branca durante a busca, recuar e continuar a varredura
      if (frontSensorState == LOW) {
        moveBackward();  // Recuar ao encontrar a borda branca
        delay(500);     // Ajustável para determinar o quanto recua
        turn180();       // Virar 180 graus para continuar a busca
      } else {
        moveForward();   // Continuar andando para frente procurando oponente
      }
    } else {
      searchingOpponent = true;
      moveForward();  // Iniciar a busca ao não encontrar oponente
    }
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

// Função para fazer o carrinho virar 180 graus
void turn180() {
  // Girar os motores para fazer o carrinho virar 180 graus
  digitalWrite(IN1, LOW);   // Motor 1 gira para trás
  digitalWrite(IN2, HIGH);  // Direção do Motor 1

  digitalWrite(IN3, HIGH);  // Motor 2 gira para frente
  digitalWrite(IN4, LOW);   // Direção do Motor 2
  
  delay(900);  // Tempo ajustável para girar 180 graus
  
  stopMotors();  // Parar após a rotação
}

// Função para fazer uma rotação de 90 graus (não usada nesse exemplo, mas mantida para ajuste futuro)
void turn90() {
  // Girar os motores para fazer o carrinho virar 90 graus
  digitalWrite(IN1, LOW);   // Motor 1 gira para trás
  digitalWrite(IN2, HIGH);  // Direção do Motor 1

  digitalWrite(IN3, HIGH);  // Motor 2 gira para frente
  digitalWrite(IN4, LOW);   // Direção do Motor 2
  
  delay(450);  // Tempo ajustável para girar 90 graus
  
  stopMotors();  // Parar após a rotação
}
