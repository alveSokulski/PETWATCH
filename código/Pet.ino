
// Programado por Henrique Finger Zimerman
// Embelezado por Pedro Sokulski
// Invejosos diro que mentira
// - Eh mentira ~ratatusznei


/*Incluindo todas as bibliotecas e coisinhas de um jeito mais bonito*/
#include "all.h"
#include "class.h"
#include "sprites.h"

/*Defines e coisas técnicas do projeto*/
//Modulo RTC DS1307 ligado as portas A4 e A5 do Arduino 
DS1307 rtc(A4, A5);

/*Definindo mais coisas*/
const int buttonPosition[4]={3,4,5,2};
const char saveIntegrity[2]={0,1};
const char save[2]={5,50};
const char timeSaveIntegrity[2]={2,3};
const char timeSave[2]={100,150};
const int daysPerMonth[2][13] = {{-1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
                           {-1, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

/*Taxa de variação das barras*/
const int velPerda=1;
const int perdaFome=2;
const int perdaSede=3;
const int perdaHigiene=1;
const int perdaFelicidade=1;

/*Posicoes das barras na tela*/
#define POSXBARRAS 97
#define BARRAVIDA 6
#define BARRAFOME 19
#define BARRASEDE 32
#define BARRAHIGIENE 45
#define BARRAFELICIDADE 58

enum estado{
  CLOCK,
  GAME,
  MENU,
  GAMEOVER
};

Pet pet; //instancia o objeto pet da classe Pet
MasterClock relogio; //instancia o objeto relogio da classe MasterClock
Animation animation; //instancia o objeto animation da classe Animation
estado GameState=CLOCK; // indica que o estado inicial é o de relógio.

void setup() ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
{
  
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  pinMode(4,INPUT);
  pinMode(5,INPUT);


  //Aciona o relogio
  rtc.halt(false);
  
  //As linhas abaixo setam a data e hora do modulo
  //e podem ser comentada apos a primeira utilizacao
  /*rtc.setDOW(SATURDAY);      //Define o dia da semana
  rtc.setTime(0, 54, 0);     //Define o horario
  rtc.setDate(25, 11, 2017);   //Define o dia, mes e ano*/
  
  //Definicoes do pino SQW/Out
  rtc.setSQWRate(SQW_RATE_1);
  rtc.enableSQW(true);

  relogio.initTime=rtc.getTime();
  
  //Inicia a comunicação I2C com o display OLED
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  
  //Limpa o display
  display.clearDisplay();

  //Mostra as mudanças no display(atualiza a imagem)
  display.display();

  if(digitalRead(5)==0){
    //Verifica a integridade do savo do slot 0
    int slot0=EEPROM.read(saveIntegrity[0]);
    
    //Verifica a integridade do savo do slot 1
    int slot1=EEPROM.read(saveIntegrity[1]);
  
    //se o slot 0 estiver bom, carregar save do slot 0
    if (slot0){
      //carrega o save do slot 0
      readAnything((char*)&pet,sizeof(pet),save[0]);
    }
  
    //se o slot 0 estiver ruim e o 1 bom, carregar save do slot 1
    else if (slot1){
      //carrega o save do slot 1
      readAnything((char*)&pet,sizeof(pet),save[1]);
    }
    //se ambos os slots estiverem corrompidos, criar novo pet 
    else{
        //cria um novo pet
        pet.createPet();
    }
  }
  else{
    pet.createPet();
  }
  int buttonLastState[3]={0};
  int menuItem=0;
  
  while(1){
      
      if(digitalRead(buttonPosition[3])){
        GameState=CLOCK;
        pet.createPet();
      }
      int button[3]={0};
      
      for(int i=0 ; i<3 ; i++)
      {
        int buttonRead=digitalRead(buttonPosition[i]);
        if(buttonRead==1 && buttonLastState[i] == 0)
        {
          button[i]=1;
        }
        buttonLastState[i]=buttonRead;
      }
      
      

      long secondsElapsed = relogio.secondsElapsed();
      pet.calcularParametros(secondsElapsed);

      
      if(GameState==CLOCK)
      {
        
        if(pet.vida>0)
        {          
          if(button[1]==1)
          {
            GameState=GAME;
          }
          Time horas = relogio.returnHours();
          mostrarHoras(horas);
          display.clearDisplay();
          animation.sleep();
        }
        else
        {          
          if(button[1]==1)
          {
            GameState=GAMEOVER;
          }
          display.clearDisplay();
          animation.death();
        }
        Time horas = relogio.returnHours();
        mostrarHoras(horas);
      }
      
      else if(GameState==GAME)
      {
        menuItem=0;
        if(pet.vida<=0)
        {
          GameState=GAMEOVER;
        }
        else if(button[1]==1)
        {
          GameState=MENU;
        }
        display.clearDisplay();
        displayStats();
        animation.idle();        
      }
      
      else if(GameState==MENU) // 0 - comida, 1 - água, 2 - banho, 3 - brincar, 4 - sair
      {
        display.clearDisplay();
        opcoesMenu(menuItem);
        if(button[1]==1)
        {
          if(menuItem==0)
          {
            pet.alimentar();
          }
          else if (menuItem==1)
          {
            pet.hidratar();
          }
          else if(menuItem==2)
          {
            pet.limpar();
          }
          else if(menuItem==3)
          {
            pet.brincar();
          }
          GameState=GAME;
        }
        else if(button[2]==1)
        {
          menuItem++;
          if(menuItem>4)
          {
            menuItem=0;
          }
        }
        else if(button[0]==1)
        {
          menuItem--;
          if(menuItem<0)
          {
            menuItem=4;
          }
        }
      }
      
      else if(GameState==GAMEOVER)
      {
        if(button[1]==1)
        {          
          pet.createPet();
          GameState=GAME;
        }
        display.clearDisplay();
        if(button[1]==0)
        {
          displayIdade();
        }
        escrever("GAME OVER", 9, 2, WHITE, 10, 0);
        animation.death();
      }
      
      display.display();
  }
  
}////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void loop(){;}
