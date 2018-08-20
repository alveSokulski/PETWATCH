#include "class.h"

/******************************************************************************************************************************/
/*MÉTODOS DE PET*/
/******************************************************************************************************************************/
void Pet::calcularParametros(long elapsedSeconds){

  if(vida>0){
  
    this->age+=elapsedSeconds;
    this->lastIt+=elapsedSeconds;
    if(this->lastIt>=10){
    
      for(int i = 0 ; i < this->lastIt/10 ; i++){
      
          int happyMod;
          if(this->felicidade>=5000){
          
            happyMod=0;
          }
          else if(this->felicidade>=2500)
          {
            happyMod=1;
          }
          else
          {
            happyMod=2;
          }
          int higiMod;
          if(this->higiene>=5000)
          {
            higiMod=0;
          }
          else if(this->higiene>=2500)
          {
            higiMod=1;
          }
          else
          {
            higiMod=2;
          }
          int fomeMod;
          if(this->fome>=5000)
          {
            fomeMod=0;
          }
          else if(this->fome>=2500)
          {
            fomeMod=1;
          }
          else
          {
            fomeMod=2;
          }
          int sedeMod;
          if(this->sede>=5000)
          {
            sedeMod=0;
          }
          else if(this->sede>=2500)
          {
            sedeMod=1;
          }
          else
          {
            sedeMod=2;
          }
          
          this->fome       -= velPerda*(perdaFome);
          this->sede       -= velPerda*(perdaSede);
          this->higiene    -= velPerda*(perdaHigiene);
          this->felicidade -= velPerda*(perdaFelicidade+higiMod);
          this->vida       -= velPerda*happyMod*(fomeMod+sedeMod);
          this->vida       += velPerda*(2-happyMod)*(2-higiMod)*(4-(fomeMod+sedeMod));
          if(this->vida>10000)
          {
            this->vida=10000;
          }
          if(this->fome<0)
          {
            this->fome=0;
          }
          if(this->sede<0)
          {
            this->sede=0;
          }
          if(this->higiene<0)
          {
            this->higiene=0;
          }
          if(this->felicidade<0)
          {
            this->felicidade=0;
          }
      }
    }
  }
  if(elapsedSeconds>0)
  {
    EEPROM.write(0,0);
    storeAnything((char*)this, sizeof(*this), save[0]);
    EEPROM.write(0,1);
    EEPROM.write(1,0);
    storeAnything((char*)this, sizeof(*this), save[1]);
    EEPROM.write(1,1);
    this->lastIt%=10;
  }
}

/******************************************************************************************************************************/
void Pet::alimentar()
{
  this->fome = 10000;
  animation.eat();
}

void Pet::hidratar()
{
  this->sede = 10000;
  animation.drink();
}

void Pet::limpar()
{
  this->higiene = 10000;
  animation.bath();
}

void Pet::brincar()
{
  this->felicidade = 10000;
  animation.play();
}

void Pet::createPet()
{
  this->vida       = 10000;
  this->fome       = 10000;
  this->sede       = 10000;
  this->higiene    = 10000;
  this->felicidade = 10000;
  this->age        = 0;
  this->lastIt     = 0;
}

/******************************************************************************************************************************/
/*MÉTODOS DE MASTERCLOCK*/
/******************************************************************************************************************************/
MasterClock::MasterClock(){

  this->lastIt=millis();
  this->correct=0;
  this->firstIt=1;
  
  int slot0=EEPROM.read(timeSaveIntegrity[0]);
  
  //Verifica a integridade do savo do slot 1
  int slot1=EEPROM.read(timeSaveIntegrity[1]);

  Time lastTime;
  
  if (slot0)
  { 
    readAnything((char*)&lastTime,sizeof(lastTime),timeSave[0]);
  }

  else if (slot1)
  {
    readAnything((char*)&lastTime,sizeof(lastTime),timeSave[1]);
  }
  this->lastTime=lastTime;
}

/******************************************************************************************************************************/
Time MasterClock::returnHours(){

  return this->lastTime;

}

/******************************************************************************************************************************/
Time MasterClock::addSecondsToDate(Time indate, long seconds){

  seconds=indate.sec+seconds;

  if(seconds>=60)
  {
    indate.min+=seconds/60;    
  }
  indate.sec=seconds%60;

  if(indate.min>=60)
  {

    indate.hour+=indate.min/60;
    indate.min%=60;
  }
  if(indate.hour>=24)
  {

    indate.date+=indate.hour/24;
    indate.hour%=24;
  }
  int BiYear=0;
  if(indate.year%4==0)
  {
    BiYear=1;
  }
  while(indate.date>daysPerMonth[BiYear][indate.mon])
  {
    indate.date-=daysPerMonth[BiYear][indate.mon];
    indate.mon+=1;
    if(indate.mon>=13)
    {
      indate.mon=1;
      indate.year+=1;
    }
    if(indate.year%4==0)
    {
      BiYear=1;
    }
    else
    {
      BiYear=0;
    }
  }
  return indate;
}

/******************************************************************************************************************************/
int MasterClock::daysElapsed(Time date0, Time date1)
{
  int BiYear=0;
  if(date0.year%4==0)
  {
    BiYear=1;
  }
  int dayCount=0;
  while(date0.date != date1.date || date0.mon != date1.mon || date0.year != date1.year)
  {
    date0.date++;
    dayCount++;
    if(date0.date>daysPerMonth[BiYear][date0.mon])
    {
      date0.date=1;
      date0.mon++;
    }
    if(date0.mon>=13)
    {
      date0.mon=1;
      date0.year+=1;
    }
    if(date0.year%4==0)
    {
      BiYear=1;
    }
    else
    {
      BiYear=0;
    }
    if(dayCount>1000)
      break;
  }
  return dayCount;
}

/*****************************************************************************************************************************/
long MasterClock::secondsElapsed()
{
  long elapsedSeconds=0;
  
  Time lastTime = this->lastTime;

  if(this-> firstIt==1)
  {
    Time initTime = this->initTime;
    int daysElapsed = this->daysElapsed(lastTime,initTime);
    elapsedSeconds = daysElapsed * 86400;

    int daySecondsInit, daySecondsLast;
    daySecondsInit = 3600 * initTime.hour + 60 * initTime.min + initTime.sec;
    daySecondsLast = 3600 * lastTime.hour + 60 * lastTime.min + lastTime.sec;
    elapsedSeconds = elapsedSeconds + (daySecondsInit - daySecondsLast);
    
  }
  
  if(millis()<this->lastIt)
  {
    this->lastIt=4294967295-this->lastIt;
  }
  if (millis()+this->correct-this->lastIt>=1000)
  {
    elapsedSeconds+=(millis()+this->correct-this->lastIt)/1000;
    this->correct=(millis()+this->correct-this->lastIt)%1000;
    lastIt=millis();
  }  
  
  
  if(elapsedSeconds>0 && firstIt==1)
  {
    this->lastTime=initTime;
    this->timeStore();
  }
  if(elapsedSeconds>0 && firstIt==0)
  {
    this->lastTime=addSecondsToDate(this->lastTime,elapsedSeconds);
    this->timeStore();
  }
  this->firstIt = 0;
  
  
  return elapsedSeconds;
}

/*****************************************************************************************************************************/
void MasterClock::timeStore()
{
  Time lastTime=this->lastTime;
  EEPROM.write(timeSaveIntegrity[0],0);
  storeAnything((char*)&lastTime, sizeof(lastTime), timeSave[0]);
  EEPROM.write(timeSaveIntegrity[0],1);
  EEPROM.write(timeSaveIntegrity[1],0);
  storeAnything((char*)&lastTime, sizeof(lastTime), timeSave[1]);
  EEPROM.write(timeSaveIntegrity[1],1);

}

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
