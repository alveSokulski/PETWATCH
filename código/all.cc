#include "sprites.h"
#include "all.h"
#include "class.h"

/*Funções do projeto em arquivo separado para desencavalar o arquivo principal*/

/*****************************************************************************************************************************/
void escrever(char stringue[], short int tamanho ,short int tamanhoFonte, short int cor, short int posX, short int posY){
  
  /*Imprime uma string no Display OLED*/
  
  display.setTextSize(tamanhoFonte);
  display.setTextColor(cor);
  display.setCursor(posX,posY);
  for(int i=0;i<tamanho;i++){
  
    display.write(stringue[i]);
  
  }
  
}

/******************************************************************************************************************************/
char intToChar (int a){ // Função que converte um algarismo int para char
  return (a >= 0 && a <= 9)? (a + '0'): '\0';
}

/******************************************************************************************************************************/
void displayBarras(){
  
  /*Imprime as barras de estado do bichinho no Display*/
  
  display.drawBitmap(POSXBARRAS,0,statBar,16,64,WHITE);
  
  short int vida=1+pet.vida/500;
  display.fillRect(POSXBARRAS+9, BARRAVIDA, vida, 2, WHITE);
  
  short int fome=1+pet.fome/500;
  display.fillRect(POSXBARRAS+9, BARRAFOME, fome, 2, WHITE);
  
  short int sede=1+pet.sede/500;
  display.fillRect(POSXBARRAS+9, BARRASEDE, sede, 2, WHITE);
  
  short int higiene=1+pet.higiene/500;
  display.fillRect(POSXBARRAS+9, BARRAHIGIENE, higiene, 2, WHITE);
  
  short int felicidade=1+pet.felicidade/500;
  display.fillRect(POSXBARRAS+9, BARRAFELICIDADE, felicidade, 2, WHITE);
  
}

/******************************************************************************************************************************/
void displayIdade(){
  
  /*Imprime no Display OLED a idade do bichinho em dias*/
  
  char idadeDisplay[]="idade:XXXX dias";
  unsigned long idade= pet.age/(86400);
  char s_idade[4]={'\0'};
  for(int i=3;i>=0;i--){
    
      idadeDisplay[i+6]=intToChar(idade%10);
      idade/=10;
    
  }
  escrever(idadeDisplay, 15, 1, WHITE, 0, 55);
  
}

/******************************************************************************************************************************/
void displayStats(){
  
  /*Imprime os estados do bichinho no Display OLED*/
  
  displayBarras();
  displayIdade();
  
}

/******************************************************************************************************************************/
void storeAnything(char * thing, int tam, int pos){
  
  /*Guarda algo na EEPROM*/
  
  for (int i=0;i<tam;i++){
    
    EEPROM.write(i+pos,0x00);
    EEPROM.write(i+pos,thing[i]);
    
  }
  
}

/******************************************************************************************************************************/
void readAnything(char * thing, int tam, int pos){
  
  /*Puxa algo da EEPROM*/
  
  for (int i=0;i<tam;i++){
    
    char * adress = thing + i;
    *adress=EEPROM.read(pos+i);
    
  }
  
}

/******************************************************************************************************************************/
void opcoesMenu(int opcao){ 
  
  /*Gerencia as opções do menu*/

  switch(opcao){
    case 0:/*Comida*/
      escrever("comida", 6, 2, WHITE, 0, 32);
      break;
    case 1:/*Água*/
      escrever("agua", 4, 2, WHITE, 0, 32);
      break;
    case 2:/*Banho*/
      escrever("banho", 5, 2, WHITE, 0, 32);
      break;
    case 3:/*Brincar*/
      escrever("brincar", 7, 2, WHITE, 0, 32);
      break;
    case 4:/*Sair*/
      escrever("sair", 4, 2, WHITE, 0, 32);
      break;
  }
  
}

/******************************************************************************************************************************/
void mostrarHoras(Time horas){
  
  /*Imprime as horas no Display OLED*/
  
  char hora[]="XX:XX";
  char data[]="YY/YY/YY";

  hora[0]= intToChar(horas.hour/10);
  hora[1]= intToChar(horas.hour%10);

  hora[3]= intToChar(horas.min/10);
  hora[4]= intToChar(horas.min%10);

  data[0]= intToChar(horas.date/10);
  data[1]= intToChar(horas.date%10);

  data[3]= intToChar(horas.mon/10);
  data[4]= intToChar(horas.mon%10);

  data[6]= intToChar((horas.year/10)%10);
  data[7]= intToChar(horas.year%10);
  
  escrever(hora, 5 , 2 , WHITE , 4, 0);
  escrever(data, 8 , 1 , WHITE, 74, 4);
  
}

/******************************************************************************************************************************/
