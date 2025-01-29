/**
 * @file botplayer.cpp
 * @brief Declaração dos métodos da classe BotPlayer.
*/

#include "botplayer.hpp"
#include <climits>
#include <algorithm>

// --- Implementação do Jogo da Velha Bot ---

/**
 * @brief Calcula a melhor jogada para o Jogo da Velha utilizando o algoritmo Minimax.
 * @param jogo Estado atual do jogo.
 * @param melhorLinha Referência para armazenar a linha da melhor jogada.
 * @param melhorColuna Referência para armazenar a coluna da melhor jogada.
 * @param jogador ID do jogador atual.
 */
void JogoDaVelhaBot::minimax(const JogoDaVelha& jogo, int& melhorLinha, int& melhorColuna, int jogador) {
    int melhorPontuacao = INT_MIN;

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
}

/**
 * @brief Implementação recursiva do algoritmo Minimax para o Jogo da Velha.
 * @param jogo Estado atual do jogo.
 * @param profundidade Nível de profundidade da árvore de decisão.
 * @param maximizando Indica se é a vez do jogador maximizar ou minimizar a pontuação.
 * @param jogador ID do jogador atual.
 * @return Valor da melhor jogada possível.
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

std::pair<int, int> JogoDaVelhaBot::calcularProximaJogada(const JogosDeTabuleiro& jogoBase, int jogadorAtual) {
    const JogoDaVelha& jogo = static_cast<const JogoDaVelha&>(jogoBase); 
    int melhorLinha = -1, melhorColuna = -1;
    minimax(jogo, melhorLinha, melhorColuna, jogadorAtual);
    return {melhorLinha, melhorColuna};
}


std::pair<int, int> Lig4Bot::calcularProximaJogada(const JogosDeTabuleiro& jogoBase, int jogadorAtual) {
    const Lig4& jogo = static_cast<const Lig4&>(jogoBase);
    std::vector<int> colunasValidas;

    for (int coluna = 0; coluna < jogo.getColunas(); ++coluna) {
        if (jogo.verificar_jogada(0, coluna, jogadorAtual)) {
            colunasValidas.push_back(coluna);
        }
    }

    if (colunasValidas.empty()) {
        std::cerr << "Erro: Nenhuma jogada válida disponível para o bot.\n";
        return {-1, -1};  // Retorna valores inválidos para indicar erro
    }

    int melhorColuna = -1;
    int melhorPontuacao = INT_MIN;

    for (int coluna : colunasValidas) {
        Lig4 copia = jogo;
        copia.ler_jogada(0, coluna, jogadorAtual);
        int pontuacao = minimax(copia, 3, false, jogadorAtual);

        if (pontuacao > melhorPontuacao) {
            melhorPontuacao = pontuacao;
            melhorColuna = coluna;
        }
    }

    if (melhorColuna == -1) {
        melhorColuna = colunasValidas[rand() % colunasValidas.size()];  // Escolhe uma aleatória
    }

    return {0, melhorColuna};  // Retorna a coluna escolhida
}



bool Lig4Bot::tabuleiroCheio(const Lig4& jogo) {
    // Check top row for empty spaces
    for (int coluna = 0; coluna < jogo.getColunas(); ++coluna) {
        if (jogo.get_casa(0, coluna) == 0) {
            return false;
        }
    }
    return true;
}

int Lig4Bot::minimax(Lig4& jogo, int profundidade, bool maximizando, int jogadorAtual) {
    // Verifica se o jogo acabou
    if (jogo.testar_condicao_de_vitoria()) {
        return maximizando ? -100 : 100; // Se for nossa vez e encontramos um tabuleiro vencedor, o oponente venceu
    }

    if (tabuleiroCheio(jogo) || profundidade == 0) {
        return 0; // Empate ou profundidade máxima atingida
    }

    int melhorPontuacao = maximizando ? INT_MIN : INT_MAX;
    int proximoJogador = maximizando ? jogadorAtual : (jogadorAtual == 1 ? 2 : 1);

    for (int coluna = 0; coluna < jogo.getColunas(); ++coluna) {
        if (jogo.verificar_jogada(0, coluna, proximoJogador)) {
            Lig4 copia = jogo;
            copia.ler_jogada(0, coluna, proximoJogador);

            int pontuacao = minimax(copia, profundidade - 1, !maximizando, jogadorAtual);

            if (maximizando) {
                melhorPontuacao = std::max(melhorPontuacao, pontuacao);
            } else {
                melhorPontuacao = std::min(melhorPontuacao, pontuacao);
            }
        }
    }

    return melhorPontuacao;
}

// --- Implementação Atualizada do Reversi Bot ---

std::pair<int, int> ReversiBot::calcularProximaJogada(const JogosDeTabuleiro& jogoBase, int jogadorAtual) {
    const Reversi& jogo = static_cast<const Reversi&>(jogoBase);
    std::vector<std::pair<int, int>> jogadasValidas;
    
    // Coletar todas as jogadas válidas primeiro
    for (int linha = 0; linha < jogo.getLinhas(); linha++) {
        for (int coluna = 0; coluna < jogo.getColunas(); coluna++) {
            if (jogo.verificar_jogada(linha, coluna, jogadorAtual)) {
                jogadasValidas.emplace_back(linha, coluna);
            }
        }
    }
    
    // Se não houver jogadas válidas, retornar (-1, -1)
    if (jogadasValidas.empty()) {
        return {-1, -1};
    }

    int melhorPontuacao = INT_MIN;
    std::pair<int, int> melhorJogada = jogadasValidas[0];

    // Avaliar apenas as jogadas válidas
    for (const auto& jogada : jogadasValidas) {
        Reversi copia = jogo;
        copia.ler_jogada(jogada.first, jogada.second, jogadorAtual);
        
        int pontuacao = _minimax(copia, 0, false, jogadorAtual);
        
        if (pontuacao > melhorPontuacao) {
            melhorPontuacao = pontuacao;
            melhorJogada = jogada;
        }
    }

    return melhorJogada;
}

int ReversiBot::_minimax(Reversi& jogo, int profundidade, bool maximizando, int jogadorAtual) {
    if (jogo.testar_condicao_de_vitoria() || profundidade >= 4) { 
        return _avaliarTabuleiro(jogo, jogadorAtual);
    }

    int melhorPontuacao = maximizando ? INT_MIN : INT_MAX;
    int jogador = maximizando ? jogadorAtual : (jogadorAtual == 1 ? 2 : 1);

    // Iterar sobre todas as jogadas válidas
    for (int linha = 0; linha < jogo.getLinhas(); linha++) {
        for (int coluna = 0; coluna < jogo.getColunas(); coluna++) {
            if (jogo.verificar_jogada(linha, coluna, jogador)) {
                jogo.ler_jogada(linha, coluna, jogador);

                // Chamada recursiva para Minimax
                int pontuacao = _minimax(jogo, profundidade + 1, !maximizando, jogadorAtual);

                //jogo.desfazer_jogada(linha, coluna);

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

// Método para avaliar o tabuleiro
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