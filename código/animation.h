#pragma once

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
