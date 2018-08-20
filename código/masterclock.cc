#include"masterclock.h"


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
