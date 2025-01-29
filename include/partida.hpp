#ifndef PARTIDA_HPP
#define PARTIDA_HPP

#include <memory>
#include "jogos.hpp"
#include "cadastro.hpp"
#include "botplayer.hpp"

class Partida {
public:
    // Constructors
    Partida(int tipoJogo, Jogador* jogador1);  // For PvE
    Partida(int tipoJogo, Jogador* jogador1, Jogador* jogador2);  // For PvP
    
    // Destructor to clean up bot pointers
    ~Partida() {
        delete bot1;
        delete bot2;
    }

    // Game control methods
    bool iniciarPartida();
    bool iniciarPartida(int dificuldade);  // For future difficulty levels
    void imprimirTabuleiro(int jogadorAtual) const;
    bool realizarJogada(int jogadorAtual, int linha = -1, int coluna = -1);
    bool verificarFimDeJogo() const;
    bool verificarJogadasDisponiveis(int jogadorAtual) const;

    // Utility methods
    bool isPvP() const { return jogador2 != nullptr; }
    Jogador* getJogadorAtual(int jogadorNumero) const {
        return jogadorNumero == 1 ? jogador1 : jogador2;
    }

private:
    std::unique_ptr<JogosDeTabuleiro> jogoAtual;
    Jogador* jogador1;
    Jogador* jogador2;
    BotPlayer* bot1;
    BotPlayer* bot2;

    std::pair<int, int> finalizarPartida();
};

#endif
