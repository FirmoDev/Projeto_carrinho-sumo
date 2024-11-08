//////////////////////////////////////
//Codigo feito por Guilherme Sousa  //
//Data 07/08/2024                   //
//projeto carrinho sumo arduino 2.0 //   
//////////////////////////////////////

#include <Ultrasonic.h>
//definindo variaveis 

  //Motores (4 motores)

  #define ET 1 //Motor esquerdo para carrinho andar para tras
  #define EF 2 //motor esquerdo para carrinho andar para frente
  #define DT 3 //Motor direito para carrinho andar para tras
  #define DF 4 //Motor direito para carrinho andar para tras
  //#define VE 7 //Velocidade do motor esquerdo
  //#define VD 9 //Velocidade do motor direito

  //Ultrassonico 1
  #define trig 10 //entrada trig entrada de dados
  #define echo 11//saida echo saida de dados

  //Sensores de linha
  #define s1 A4 //sensor da frente do carrinho
  #define s2 A3 //sensor de tras do carrinho

  #define branco  0
  #define preto  1

  //Definição dos pinos para o botão de ativação e led embutido
  #define botao_pin 6
  #define led_embu 13

  //Tempo inicial para começo de combate 20 segundos = 20000 mili
  #define delay_inicial 20000 

  //Variaveis para controlar os modos de detecção e combate
  bool modoEspera = false;
  bool combateOn = false;
  unsigned long timeStart;
  unsigned long correndoMillis;

  //Variaveis para gerenciar o estado do botao com debouncing
  bool ultEstadoBotao = HIGH; //ultimo estado do botao
  bool botaoAtual = HIGH; //estado do botao atual
  unsigned long ultMudancaBotao = 0;//Ultima vez que o botao foi alterado
  unsigned long atrasoDebouncing = 50; //atraso para debouncing
  

void setup() {
  //configuração inicial dos pinos para ser executado somente uma vez
  pinMode(ET, OUTPUT);
  pinMode(EF, OUTPUT);
  pinMode(DT, OUTPUT);
  pinMode(DF, OUTPUT);
  //pinMode(VE, OUTPUT); //controla a velocidade dos motores A da Ponte H
  //pinMode(VD, OUTPUT); //controla a velocidade dos motores B da ponte H

  //configuração dos pinos do sensor ultrassonico
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  //configuração dos sensores de linha
  pinMode(s1, INPUT);//sensor frente
  pinMode(s2, INPUT);//sensor tras

  //configuração do botão e led embutido
  pinMode(botao_pin, INPUT_PULLUP);
  pinMode(led_embu, OUTPUT);

  //inicialização do led embutido
  digitalWrite(led_embu, LOW);//inicialmente apagado


}
/*void controle(){
  //se o sensor da frente achar a borda e não o carrinho
  if(digitalRead(s1) == 0 && digitalRead()){

  }
}
*/
void loop() {
  //leitura do botao com debouncing
  int lendo = digitalRead(botao_pin);

  if(lendo != ultEstadoBotao ){
    ultEstadoBotao = millis();//reseta o tempo de debounce

  }

  if((millis() - ultEstadoBotao ) > atrasoDebouncing){
    if(lendo != botaoAtual){
      botaoAtual = lendo;

      //alterna o estado de combate se o botao foi pressionado
      if(botaoAtual == LOW){
        combateOn = !combateOn;

        if(combateOn){
          //inicia a contagem de 20 segundos
          timeStart = millis();
          modoEspera = true; //entra no modo procura depois dos 20 segundos
          digitalWrite(led_embu, HIGH);//acende o led embutido para indicar o inicio

        }
        
      }

    }

  }

  ultEstadoBotao = lendo;

  //modo de combate
  if(combateOn && modoEspera){
    //verifica se já passou o tempo de espera de 20 segundos
    correndoMillis = millis();

    if(correndoMillis - timeStart >= delay_inicial){
      //desliga o led embutido e entra em modo combate 
      digitalWrite(led_embu, LOW);

      //envia o pulso ultrassonico
      digitalWrite(trig, LOW);
      delayMicroseconds(2);
      digitalWrite(trig, HIGH);
      delayMicroseconds(10);
      digitalWrite(trig, LOW);

      //mede o tempo de retorno do eco
      long duration = pulseIn(echo, HIGH);

      //calcula a distancia e cm
      long distance = duration * 0.034/2;

      //se a distancia for menor ou igual a 20 cm, o robo deve avançar
      if(distance > 20 && digitalRead(s1) == 0 && digitalRead(s2) == 0){
        //procurando oponente, indo para frente nessas primeiras 4 linhas
        //após isso, ele vai virar a direita, ir reto e virar a direita até achar o oponente
        
        digitalWrite(ET, HIGH);
        digitalWrite(EF, LOW);
        digitalWrite(DT, LOW);
        digitalWrite(DF, HIGH);
        //analogWrite(VE, 200); //velocidade media para detectar
        //analogWrite(VD, 200);//velocidade media para detectar
        delay(300);
        digitalWrite(ET, HIGH);
        digitalWrite(EF, LOW);
        digitalWrite(DT, LOW);
        digitalWrite(DF, LOW);
        //analogWrite(VE, 200); //velocidade maxima dos motores A da ponte H
        //analogWrite(VD, 200);//velocidade maxima dos motores B da ponte H
        delay(300);
        


      }

      //se caso encontrar algo na sua frente
      if(distance < 20 && distance > 0 && digitalRead(s1) == 0 && digitalRead(s2) == 0){
        while(digitalRead(s1) == 0) { //prende na condição até o sensor encontrar a borda da arena "branca"
        
        digitalWrite(ET, HIGH);//motor esquerdo para dar ré no carrinho
        digitalWrite(EF, LOW);//motor esquerdo para ir para frente (LIGADO)
        digitalWrite(DT, LOW);//motor direito para dar ré no carrinho
        digitalWrite(DF, HIGH);//motor direito para ir para frente (LIGADO)
        //analogWrite(VE, 255);//velocidade maxima do motor
        //analogWrite(VD, 255);//velocidade maxima do motor é para acabar com esse jão...
        }

      }
      //se caso encontre a borda e não o oponente
      if(digitalRead(s1) == 1 && digitalRead(s2) == 0){
        //sensor da frente encontrou a borda
        //quero que ele de meia volta e ative o modoEspera
        digitalWrite(ET, LOW);//motor esquerdo para dar ré no carrinho (LIGADO)
        digitalWrite(EF, HIGH);//motor esquerdo para ir para frente
        digitalWrite(DT, HIGH);//motor direito para dar ré no carrinho (LIGADO)
        digitalWrite(DF, LOW);//motor direito para ir para frente 
        delay(700);
        /*digitalWrite(ET, LOW);//motor esquerdo para dar ré no carrinho
        digitalWrite(EF, HIGH);//motor esquerdo para ir para frente
        digitalWrite(DT, HIGH);//motor direito para dar ré no carrinho quero que deixe ligado para ver se ele vira mais rapido, na teoria funcionaria como um 4x4
        digitalWrite(DF, LOW);//motor direito para ir para frente 
        delay(300);
        */

      }
    }
    delay(50);//para evitar leituras rapidas
  }

}

  /*void paraMotores(){
    digitalWrite(ET, LOW);
    digitalWrite(EF, LOW);
    digitalWrite(DT, LOW);
    digitalWrite(DF, LOW);
    analogWrite(VE, 0);
    analogWrite(VD, 0);




  }*/
