#include <iostream>
#include <chrono>
#include <ctime>


class Cronometro{

private:
    std::chrono::time_point<std::chrono::system_clock> ini, fim;
    std::chrono::duration<double> tempo_corrido;


public:
    void medir_ini();
    void medir_fim();
    std::chrono::duration<double> get_tempo_corrido();

};


void Cronometro::medir_ini(){
    ini = std::chrono::system_clock::now();
}

void Cronometro::medir_fim(){
    fim = std::chrono::system_clock::now();
}

std::chrono::duration<double> Cronometro::get_tempo_corrido(){
    tempo_corrido = fim - ini;

    return tempo_corrido;
}
