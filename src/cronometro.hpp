#include <chrono>

class Cronometro {

private:
    std::chrono::time_point<std::chrono::system_clock> ini, fim;
    std::chrono::duration<double> tempo_corrido;

public:
    void medir_ini();
    void medir_fim();
    std::chrono::duration<double> get_tempo_corrido();
};


inline void Cronometro::medir_ini(){
    this->ini = std::chrono::system_clock::now();
}

inline void Cronometro::medir_fim(){
    this->fim = std::chrono::system_clock::now();
}

inline std::chrono::duration<double> Cronometro::get_tempo_corrido(){
    this->tempo_corrido = this->fim - this->ini;

    return tempo_corrido;
}
