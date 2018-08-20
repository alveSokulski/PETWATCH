#include"pet.h"

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
