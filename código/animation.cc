#include"animation.h"

/******************************************************************************************************************************/
/*MÉTODOS DE ANIMATION*/
/******************************************************************************************************************************/
Animation::Animation()
{
  this->estado=8;
  this->lastIt=0;
  this->frame=0;
}

void Animation::sleep () //idle=0 , sleep=1, eat=2,  drink=3,  bath=4,  none=5,  death=6
{
  if(this->estado==1)
  {
    if(millis()-this->lastIt >= 500)
    {
      lastIt=millis();
      if(this->frame==1)
      {
        this->frame=2;
      }
      else if(this->frame==2)
      {
        this->frame=1;
      }
    }
    if(this->frame==1)
    {
      display.drawBitmap(36,30,dormindo1,56,32,WHITE);
    }
    else if(this->frame==2)
    {
      display.drawBitmap(36,30,dormindo2,56,32,WHITE);
    }
  }
  else
  {
    this->estado=1;
    this->lastIt=millis();
    this->frame=1;
    display.drawBitmap(36,30,dormindo1,56,32,WHITE);
  } 
}

/*****************************************************************************************************************************/
void Animation::idle  ()
{
  if(this->estado==0)
  {
    if(millis()-this->lastIt >= 500)
    {
      lastIt=millis();
      if(this->frame==1)
      {
        this->frame=2;
      }
      else if(this->frame==2)
      {
        this->frame=3;
      }
      else if(this->frame==3)
      {
        this->frame=4;
      }
      else if(this->frame==4)
      {
        this->frame=1;
      }
    }
    if(this->frame==1)
    {
      display.drawBitmap(20,0,idle1,64,64,WHITE);
    }
    else if(this->frame==2)
    {
      display.drawBitmap(20,0,idle2,64,64,WHITE);
    }
    else if(this->frame==3)
    {
      display.drawBitmap(20,0,idle3,64,64,WHITE);
    }
    else if(this->frame==4)
    {
      display.drawBitmap(20,0,idle2,64,64,WHITE);
    }
  }
  else
  {
    this->estado=0;
    this->lastIt=millis();
    this->frame=1;
    display.drawBitmap(20,0,idle1,64,64,WHITE);
  } 
}
void Animation::none  ()
{
   this->estado=5;
}
void Animation::death (){;}

void Animation::eat   ()
{
  display.clearDisplay();
  display.drawBitmap(32 , 8 , alimento1 , 64 , 48 , WHITE);
  display.display();
  delay(500);
  display.clearDisplay();  
  display.drawBitmap(32 , 8 , alimento2 , 64 , 48 , WHITE);
  display.display();
  delay(500);
  display.clearDisplay();
  display.drawBitmap(32 , 8 , alimento3 , 64 , 48 , WHITE);
  display.display();
  delay(500);
  display.clearDisplay();
  display.drawBitmap(32 , 8 , alimento4 , 64 , 48 , WHITE);
  display.display();
  delay(500);
  display.clearDisplay();    
}

/******************************************************************************************************************************/
void Animation::drink ()
{
  display.clearDisplay();
  display.drawBitmap(32 , 8 , bebida1 , 64 , 48 , WHITE);
  display.display();
  delay(500);
  display.clearDisplay();
  display.drawBitmap(32 , 8 , bebida2 , 64 , 48 , WHITE);
  display.display();
  delay(500);
  display.clearDisplay();
  display.drawBitmap(32 , 8 , bebida2 , 64 , 48 , WHITE);
  display.display();
  delay(500);
  display.clearDisplay();
  display.drawBitmap(32 , 8 , bebida2 , 64 , 48 , WHITE);
  display.display();
  delay(500);
  display.clearDisplay();
}

/******************************************************************************************************************************/
void Animation::play ()
{
  display.clearDisplay();
  display.drawBitmap(32 , 8 , brincando1 , 64 , 64 , WHITE);
  display.display();
  delay(500);
  display.clearDisplay();
  display.drawBitmap(32 , 8 , brincando2 , 64 , 64 , WHITE);
  display.display();
  delay(500);
  display.clearDisplay();
  display.drawBitmap(32 , 8 , brincando3 , 64 , 64 , WHITE);
  display.display();
  delay(500);
  display.clearDisplay();
  display.drawBitmap(32 , 8 , brincando4 , 64 , 64 , WHITE);
  display.display();
  delay(500);
  display.clearDisplay();
}

/*****************************************************************************************************************************/
void Animation::bath  ()
{
  display.clearDisplay();
  display.drawBitmap(36 , 0 , banho1 , 56 , 64 , WHITE);
  display.display();
  delay(500);
  display.clearDisplay();
  display.drawBitmap(36 , 0 , banho2 , 56 , 64 , WHITE);
  display.display();
  delay(500);
  display.clearDisplay();
  display.drawBitmap(36 , 0 , banho1 , 56 , 64 , WHITE);
  display.display();
  delay(500);
  display.clearDisplay();
  display.drawBitmap(36 , 0 , banho2 , 56 , 64 , WHITE);
  display.display();
  delay(500);
  display.clearDisplay();
}
/******************************************************************************************************************************/
