#include "partida.hpp"
#include <iostream>
#include <memory>
#include <chrono>
#include <thread>

Partida::Partida(int tipoJogo, Jogador* jogador1) : jogador1(jogador1), jogador2(nullptr) {
    // Initialize the appropriate game type and bot
    switch (tipoJogo) {
        case 1:
            jogoAtual.reset(new JogoDaVelha());
            bot1 = new JogoDaVelhaBot();
            break;
        case 2:
            jogoAtual.reset(new Lig4());
            bot1 = new Lig4Bot();
            break;
        case 3:
            jogoAtual.reset(new Reversi());
            bot1 = new ReversiBot();
            break;
        default:
            throw std::invalid_argument("Tipo de jogo inválido");
    }
    bot2 = nullptr;
}

Partida::Partida(int tipoJogo, Jogador* jogador1, Jogador* jogador2) 
    : jogador1(jogador1), jogador2(jogador2), bot1(nullptr), bot2(nullptr) {
    // Initialize the appropriate game type for PvP
    switch (tipoJogo) {
        case 1:
            jogoAtual.reset(new JogoDaVelha());
            break;
        case 2:
            jogoAtual.reset(new Lig4());
            break;
        case 3:
            jogoAtual.reset(new Reversi());
            break;
        default:
            throw std::invalid_argument("Tipo de jogo inválido");
    }
}

bool Partida::iniciarPartida() {
    if (!jogador1) {
        std::cout << "Erro: Jogador 1 não inicializado!" << std::endl;
        return false;
    }

    int jogadorAtual = 1;
    bool jogoEmAndamento = true;

    while (jogoEmAndamento) {
        imprimirTabuleiro(jogadorAtual);
        
        bool jogadaValida = realizarJogada(jogadorAtual);

        if (!jogadaValida) {
            std::cout << "Jogada inválida! Tente novamente." << std::endl;
            continue; // Não alterna o jogador se a jogada for inválida
        }
        if (verificarFimDeJogo()) {
            imprimirTabuleiro(jogadorAtual);
            finalizarPartida();
            jogoEmAndamento = false;
        } else {
            jogadorAtual = (jogadorAtual == 1) ? 2 : 1;
        }
    }

    return true;
}

bool Partida::iniciarPartida(int dificuldade) {
    // Implementação futura para diferentes níveis de dificuldade
    return iniciarPartida();
}

void Partida::imprimirTabuleiro(int jogador_atual) const {
    jogoAtual->imprimir_vetor(jogador_atual);
}

bool Partida::realizarJogada(int jogadorAtual, int linha, int coluna) {

    // Se é um bot jogando
    //if ((jogadorAtual == 2 && !jogador2 && bot1) || (jogadorAtual == 1 && !jogador1 && bot2)) {
    if ((jogadorAtual == 2 && !jogador2) || (jogadorAtual == 1 && !jogador1)) {
        BotPlayer* botAtual = (jogadorAtual == 2) ? bot1 : bot2;
        std::pair<int, int> jogadaBot;
        int botLinha, botColuna;
        bool jogada_achada = false;
        while (!jogada_achada)
        {
            jogadaBot = botAtual->calcularProximaJogada(*jogoAtual, jogadorAtual);
            int botLinha = jogadaBot.first;
            int botColuna = jogadaBot.second;
            jogada_achada = jogoAtual->verificar_jogada(botLinha, botColuna, jogadorAtual);
            if (jogada_achada){
                std::cout << std::endl << "A IA está pensando...\n";
                std::this_thread::sleep_for(std::chrono::seconds(2));
                return jogoAtual->ler_jogada(botLinha, botColuna, jogadorAtual);
            }
        }
        return false;
    }
    
    // Se é um jogador humano
    if (linha == -1 || coluna == -1) {
        std::cout << std::endl <<  "Jogador " << jogadorAtual << ", faça sua jogada:" << std::endl;
        std::cout << "Linha: ";
        std::cin >> linha;
        std::cout << "Coluna: ";
        std::cin >> coluna;
    }
    linha = linha-1;
    coluna = coluna-1;
    if (jogoAtual->verificar_jogada(linha, coluna, jogadorAtual)) {
        return jogoAtual->ler_jogada(linha, coluna, jogadorAtual);
    }
    
    return false;
}

bool Partida::verificarFimDeJogo() const {
    return jogoAtual->testar_condicao_de_vitoria();
}

void Partida::finalizarPartida() {
    // Implementar lógica para atualizar estatísticas dos jogadores
    // e determinar o vencedor
    std::cout << "Jogo finalizado!" << std::endl;
    // Aqui você pode adicionar a lógica para atualizar o winrate dos jogadores
}
