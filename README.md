# Carrinho Sumô com Arduino
![Carrinho Sumô](/IMG_20240913_164856.jpg)

## 1. Introdução
O projeto carrinho sumô consiste em uma competição com todas as turmas da Instituição Senac Taboão SP. Os projetos serão apresentados e competirão em uma Arena circular.

### Objetivo do Projeto
O objetivo da competição é propor um desafio para os alunos em um curto periodo de tempo e com poucos recursos para a construção do projeto. Visto queO robô que conseguirá empurrar o oponente para fora da arena vencerá a rodada.

## 2. Tecnologias Utilizadas
- **Placa Controladora**: Arduino  Uno.
- **Sensores**: 1 sensor de proximidade (Ultrassônico HC-SR04), 2 sensores de linha (Sensor TCRT5000).
- **Componentes Eletrônicos**: 4 Motores, 1 Protoboard, 2 baterias (18650 Recarrregável Li-ion 3.7v), 1 PushButton/Chave Táctil, 1 Ponte H l_298N.
- **Linguagem de Programação**: C e C++.

## 3. Estrutura e Funcionamento
### Esquema do Circuito
Um diagrama básico da estrutura elétrica e dos componentes conectados ao Arduino.

### Lógica de Programação
Ao ligar o circuito do Carrinho, ele esperará o 'pulso eletrico' causado com botão instalado na protoboard do circuito Após o acionamento, terá um delay de 20000 milisegundos (ou 20 segundos) de espera para o seu funcionamento. Apartir de seu funcionamento, o sensor ultrassonico entrará em ação rastreando o oponente em um raio de 20 centimetros. Se detectado o oponente em sua frente, o carrinho dará potencia total para seus motores para frente. Se não detectado o oponente, o mesmo entrará em loop girando em seu próprio eixo até a detecção.

### Mecânica do Carrinho
A base do carrinho foi construida a partir de uma placa de aluminio para descarte em serralheria. Seu "raspador" (especie de  escudo na frente do carrinho) foi feito com plastico e suas rodas são de borracha.
## 4. Código Fonte
### Principais Arquivos e Funções


- No arquivo `testando-sensor-ultrasonico.ino` realizamos teste do sensor em funcionamento isolado.
- No arquivo `teste-de-motores_carrinho-sumo.ino` realizamos teste de motores, obtendo a certeza de direção e potência.
- No arquivo `codigo-sumo-gui-atualizado-final.ino` realizamos a contrução do codigo final com todos os recursos e regras da competição.

## 6. Testes e Resultados
### Testes Realizados
Realizados teste de funcionamento em simulação, notamos defeito em reconhecimento dos sensores de linha. Mas logo solucionado com regulação em um de seus senhores localizados na parte traseiro do carrinho.

### Resultados
Ficamos em 2° Lugar na competição! Além de super aprendizado e verdadeira "correria" atrás de conhecimento.

## 7. Conclusão e Aprendizados
### Principais Aprendizados
Aprendemos uma boa noção do que é programar em linguagem C na prática e ajustando funcionalidades que desepenharam estrategias na competição. Aprendemos sobre eletrônica e circuitos.

### Possíveis Melhorias
Percebemos durante a competição que o nosso carrinho de longe era que tinha mais torque, porém perdemos para um oponente que possuia um "raspador" mais arredondado en forma de "C" que levantava as rodas do carrinho fazendo perder tração. Nossa sugestão era o aprimoramento de nosso raspador para a melhor performance.
.

## 8. Como Contribuir
Estou aberto para novas ideias e se possivel novas sugestões de código. Fiquem a vontade para sugerir melhorias!

![Carrinho Sumô](/IMG_20240907_153011.jpg)

### Documentação para mais detalhes
[Documentação e regras para a competição](/Guia_de_Regras_e_Dicas_Robatalha_2024.docx)

