#ifndef __ALL_H
#define __ALL_H

#include <Wire.h>
#include <EEPROM.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DS1307.h>
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

#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 

#define OLED_RESET 6
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif



/*Funcoes do projeto*/
/*Obrigado, Finger*/
void escrever(char stringue[], short int tamanho ,short int tamanhoFonte, short int cor, short int posX, short int posY);
char intToChar(int a);
void displayStats();
void displayBarras();
void displayIdade();
void storeAnything(char * thing, int tam, int pos);
void readAnything(char * thing, int tam, int pos);
void opcoesMenu(int opcao);
void mostrarHoras();

#endif /*__ALL_H*/
