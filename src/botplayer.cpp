/**
 * @file botplayer.cpp
 * @brief Implementa os bots para jogos de tabuleiro (Jogo da Velha, Lig 4, Reversi) com algoritmo Minimax.
 */

#include "botplayer.hpp"
#include <climits>
#include <algorithm>
#include <stdexcept>

/**
 * @brief Implementa a lógica Minimax para o Jogo da Velha.
 * @param jogo Estado atual do jogo.
 * @param melhorLinha Referência para armazenar a linha da melhor jogada.
 * @param melhorColuna Referência para armazenar a coluna da melhor jogada.
 * @param jogador ID do jogador atual.
 * @throw std::runtime_error Se o tabuleiro estiver vazio ou inválido.
 */
void JogoDaVelhaBot::minimax(const JogoDaVelha& jogo, int& melhorLinha, int& melhorColuna, int jogador) {
    if (jogo.getLinhas() <= 0 || jogo.getColunas() <= 0) {
        throw std::runtime_error("Tabuleiro vazio ou inválido.");
    }

    int melhorPontuacao = INT_MIN;
    melhorLinha = -1;
    melhorColuna = -1;

    for (int i = 0; i < jogo.getLinhas(); i++) {
        for (int j = 0; j < jogo.getColunas(); j++) {
            if (jogo.get_casa(i, j) == 0) { // Se a casa está vazia
                JogoDaVelha copia = jogo;
                copia.ler_jogada(i, j, jogador);

                int pontuacao = _minimax(copia, 0, false, jogador);
                if (pontuacao > melhorPontuacao) {
                    melhorPontuacao = pontuacao;
                    melhorLinha = i;
                    melhorColuna = j;
                }
            }
        }
    }

    if (melhorLinha == -1 || melhorColuna == -1) {
        throw std::runtime_error("Nenhuma jogada válida encontrada.");
    }
}

/**
 * @brief Função recursiva do algoritmo Minimax para o Jogo da Velha.
 * @param jogo Estado atual do jogo.
 * @param profundidade Nível de profundidade da recursão.
 * @param maximizando Indica se é o turno do jogador maximizador.
 * @param jogador ID do jogador atual.
 * @return Pontuação associada ao estado do jogo.
 */
int JogoDaVelhaBot::_minimax(JogoDaVelha& jogo, int profundidade, bool maximizando, int jogador) {
    if (jogo.testar_condicao_de_vitoria()) {
        return maximizando ? -1 : 1; // Vitória do oponente ou do bot
    }

    // Verifica empate
    bool temEspacosVazios = false;
    for (int i = 0; i < jogo.getLinhas(); i++) {
        for (int j = 0; j < jogo.getColunas(); j++) {
            if (jogo.get_casa(i, j) == 0) {
                temEspacosVazios = true;
                break;
            }
        }
    }
    if (!temEspacosVazios) return 0; // Empate

    int melhorPontuacao = maximizando ? INT_MIN : INT_MAX;
    int outroJogador = (jogador == 1) ? 2 : 1;

    for (int i = 0; i < jogo.getLinhas(); i++) {
        for (int j = 0; j < jogo.getColunas(); j++) {
            if (jogo.get_casa(i, j) == 0) { // Se a casa está vazia
                JogoDaVelha copia = jogo;
                copia.ler_jogada(i, j, maximizando ? jogador : outroJogador);

                int pontuacao = _minimax(copia, profundidade + 1, !maximizando, jogador);
                if (maximizando) {
                    melhorPontuacao = std::max(melhorPontuacao, pontuacao);
                } else {
                    melhorPontuacao = std::min(melhorPontuacao, pontuacao);
                }
            }
        }
    }
    return melhorPontuacao;
}

/**
 * @brief Calcula a próxima jogada ideal para o Jogo da Velha.
 * @param jogoBase Referência para o estado do jogo.
 * @param jogadorAtual ID do jogador atual.
 * @return Par com a linha e coluna da melhor jogada.
 */
std::pair<int, int> JogoDaVelhaBot::calcularProximaJogada(const JogosDeTabuleiro& jogoBase, int jogadorAtual) {
    const JogoDaVelha& jogo = static_cast<const JogoDaVelha&>(jogoBase); 
    int melhorLinha = -1, melhorColuna = -1;
    minimax(jogo, melhorLinha, melhorColuna, jogadorAtual);
    return {melhorLinha, melhorColuna};
}

/**
 * @brief Função para avaliar o tabuleiro no Reversi.
 * @param jogo Estado atual do jogo.
 * @param jogadorAtual ID do jogador atual.
 * @return Pontuação do tabuleiro para o jogador atual.
 */
int ReversiBot::_avaliarTabuleiro(const Reversi& jogo, int jogadorAtual) {
    int oponente = (jogadorAtual == 1) ? 2 : 1;
    int pontuacao = 0;

    int mobilidadeJogador = 0;
    int mobilidadeOponente = 0;

    for (int linha = 0; linha < jogo.getLinhas(); linha++) {
        for (int coluna = 0; coluna < jogo.getColunas(); coluna++) {
            if (jogo.verificar_jogada(linha, coluna, jogadorAtual)) mobilidadeJogador++;
            if (jogo.verificar_jogada(linha, coluna, oponente)) mobilidadeOponente++;
        }
    }
    pontuacao += (mobilidadeJogador - mobilidadeOponente) * 2;

    // Controle de cantos e bordas
    for (int linha = 0; linha < jogo.getLinhas(); linha++) {
        for (int coluna = 0; coluna < jogo.getColunas(); coluna++) {
            int casa = jogo.get_casa(linha, coluna);
            if (casa == jogadorAtual) {
                if ((linha == 0 || linha == jogo.getLinhas() - 1) &&
                    (coluna == 0 || coluna == jogo.getColunas() - 1)) {
                    pontuacao += 20; // Cantos valem mais
                } else if (linha == 0 || linha == jogo.getLinhas() - 1 ||
                           coluna == 0 || coluna == jogo.getColunas() - 1) {
                    pontuacao += 5; // Bordas valem menos que cantos
                } else {
                    pontuacao += 1; // Centros têm valor padrão
                }
            } else if (casa == oponente) {
                if ((linha == 0 || linha == jogo.getLinhas() - 1) &&
                    (coluna == 0 || coluna == jogo.getColunas() - 1)) {
                    pontuacao -= 20; // Penaliza cantos ocupados pelo oponente
                } else if (linha == 0 || linha == jogo.getLinhas() - 1 ||
                           coluna == 0 || coluna == jogo.getColunas() - 1) {
                    pontuacao -= 5; // Penaliza bordas ocupadas pelo oponente
                } else {
                    pontuacao -= 1; // Penaliza centros ocupados pelo oponente
                }
            }
        }
    }

    return pontuacao;
}
