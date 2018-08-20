#pragma once

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
