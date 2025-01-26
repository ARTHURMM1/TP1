#ifndef PARTIDA_HPP
#define PARTIDA_HPP

#include <memory>
#include "jogos.hpp"
#include "cadastro.hpp"
#include "botplayer.hpp"

class Partida {
public:
    Partida();

    // Inicializa a partida com dois jogadores e o tipo de jogo
    bool iniciarPartida(Jogador* jogador1, Jogador* jogador2, int tipoJogo, 
                        BotPlayer* bot1 = nullptr, BotPlayer* bot2 = nullptr);

    // Imprime o estado atual do tabuleiro
    void imprimirTabuleiro() const;

    // Realiza uma jogada para o jogador atual
    bool realizarJogada(int jogadorAtual, int linha = -1, int coluna = -1);

    // Verifica se o jogo terminou
    bool verificarFimDeJogo() const;

private:
    std::unique_ptr<JogosDeTabuleiro> jogoAtual;
    Jogador* jogador1;
    Jogador* jogador2;
    BotPlayer* bot1;
    BotPlayer* bot2;

    // Determina o vencedor ou se houve empate
    void finalizarPartida();
};

#endif
