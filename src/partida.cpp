#include "partida.hpp"
#include <iostream>

Partida::Partida() : jogoAtual(nullptr), jogador1(nullptr), jogador2(nullptr), bot1(nullptr), bot2(nullptr) {}

bool Partida::iniciarPartida(Jogador* j1, Jogador* j2, int tipoJogo, BotPlayer* b1, BotPlayer* b2) {
    jogador1 = j1;
    jogador2 = j2;
    bot1 = b1;
    bot2 = b2;

    switch (tipoJogo) {
        case 1:  // Jogo da Velha
            jogoAtual = std::make_unique<JogoDaVelha>();
            break;
        case 2:  // Reversi
            jogoAtual = std::make_unique<Reversi>();
            break;
        case 3:  // Lig4
            jogoAtual = std::make_unique<Lig4>();
            break;
        default:
            std::cout << "ERRO: Tipo de jogo inválido!" << std::endl;
            return false;
    }

    std::cout << "Partida iniciada entre " << jogador1->getNome()
              << " e " << jogador2->getNome() << "!" << std::endl;
    return true;
}

void Partida::imprimirTabuleiro() const {
    if (jogoAtual) {
        jogoAtual->imprimirTabuleiro();
    } else {
        std::cout << "Nenhuma partida em andamento." << std::endl;
    }
}

bool Partida::realizarJogada(int jogadorAtual, int linha, int coluna) {
    if (!jogoAtual) {
        std::cout << "Nenhuma partida em andamento." << std::endl;
        return false;
    }

    if ((jogadorAtual == 1 && bot1) || (jogadorAtual == 2 && bot2)) {
        // Determina o bot correspondente
        BotPlayer* bot = (jogadorAtual == 1) ? bot1 : bot2;
        auto jogada = bot->calcularProximaJogada(*jogoAtual, jogadorAtual);
        linha = jogada.first;
        coluna = jogada.second;
    }

    if (jogoAtual->fazerJogada(jogadorAtual, linha, coluna)) {
        return true;
    } else {
        std::cout << "Jogada inválida. Tente novamente." << std::endl;
        return false;
    }
}

bool Partida::verificarFimDeJogo() const {
    if (jogoAtual && jogoAtual->verificarFim()) {
        finalizarPartida();
        return true;
    }
    return false;
}

void Partida::finalizarPartida() {
    int vencedor = jogoAtual->determinarVencedor();
    if (vencedor == 0) {
        std::cout << "A partida terminou em empate!" << std::endl;
    } else {
        Jogador* vencedorJogador = (vencedor == 1) ? jogador1 : jogador2;
        std::cout << "O vencedor é " << vencedorJogador->getNome() << "!" << std::endl;
    }
}
