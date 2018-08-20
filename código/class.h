/***************************************************************************************************************************/
class Pet{
  public:
    int vida;
    int fome;
    int sede;
    int higiene;
    int felicidade;
    int age;

    int lastIt;

    void calcularParametros(long elapsedSeconds);
    void alimentar();
    void hidratar();
    void limpar();
    void brincar();    
    void createPet();
};
/***************************************************************************************************************************/
class MasterClock{
    Time lastTime;
    
    int firstIt;
    unsigned long lastIt;
    unsigned long correct;

    void timeStore();
    void timeRestart();
    Time addSecondsToDate(Time indate, long seconds);
    int daysElapsed(Time date0, Time date1);

  public:

    Time returnHours();
    Time initTime;
    MasterClock();
    long secondsElapsed();
    
};
/***************************************************************************************************************************/
class Animation{ //idle=0 , sleep=1, eat=2,  drink=3,  bath=4,  none=5,  death=6
    int estado;
    int frame;
    unsigned long lastIt;
    
  
  public:

    Animation();
    void sleep ();
    void idle  ();
    void none  ();
    void death ();
    void eat   ();
    void drink ();
    void bath  ();
    void play  ();
    
};
/***************************************************************************************************************************/
