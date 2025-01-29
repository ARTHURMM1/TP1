/**
 * @file partida.cpp
 * @brief Declaração dos métodos da classe Partida.
 */

#include "partida.hpp"
#include <iostream>
#include <memory>
#include <chrono>
#include <thread>
#include <stdexcept>

/**
 * @brief Construtor para criar uma partida com um jogador humano e um bot.
 * @param tipoJogo Tipo do jogo (1 - Jogo da Velha, 2 - Lig4, 3 - Reversi).
 * @param jogador1 Ponteiro para o primeiro jogador humano.
 * @throws std::invalid_argument Se o tipo de jogo for inválido.
 */
Partida::Partida(int tipoJogo, Jogador* jogador1) : jogador1(jogador1), jogador2(nullptr) {
    try {
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
    } catch (const std::exception& e) {
        std::cerr << "Erro ao inicializar a partida: " << e.what() << std::endl;
        throw;
    }
}

/**
 * @brief Construtor para criar uma partida entre dois jogadores humanos.
 * @param tipoJogo Tipo do jogo (1 - Jogo da Velha, 2 - Lig4, 3 - Reversi).
 * @param jogador1 Ponteiro para o primeiro jogador humano.
 * @param jogador2 Ponteiro para o segundo jogador humano.
 * @throws std::invalid_argument Se o tipo de jogo for inválido.
 */
Partida::Partida(int tipoJogo, Jogador* jogador1, Jogador* jogador2) 
    : jogador1(jogador1), jogador2(jogador2), bot1(nullptr), bot2(nullptr) {
    try {
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
    } catch (const std::exception& e) {
        std::cerr << "Erro ao inicializar a partida: " << e.what() << std::endl;
        throw;
    }
}

/**
 * @brief Inicia uma partida com as configurações atuais.
 * @return true se a partida foi concluída com sucesso, false em caso de erro.
 */
bool Partida::iniciarPartida() {
    if (!jogador1) {
        std::cerr << "Erro: Jogador 1 não inicializado!" << std::endl;
        return false;
    }

    int jogadorAtual = 1;
    bool jogoEmAndamento = true;
    int passesConsecutivos = 0;

    try {
        while (jogoEmAndamento) {
            imprimirTabuleiro(jogadorAtual);

            if (!verificarJogadasDisponiveis(jogadorAtual)) {
                std::cout << "Jogador " << jogadorAtual << " não tem jogadas válidas. Passando a vez..." << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(2));

                passesConsecutivos++;
                if (passesConsecutivos >= 2) {
                    std::cout << "Nenhum jogador tem jogadas válidas. Fim de jogo!" << std::endl;
                    finalizarPartida();
                    return true;
                }

                jogadorAtual = (jogadorAtual == 1) ? 2 : 1;
                continue;
            }

            passesConsecutivos = 0;
            bool jogadaValida = realizarJogada(jogadorAtual);

            if (!jogadaValida) {
                std::cout << "Jogada inválida! Tente novamente." << std::endl;
                continue;
            }

            if (verificarFimDeJogo()) {
                imprimirTabuleiro(jogadorAtual);
                std::pair<int, int> vencedor_e_jogo = finalizarPartida(); //primeiro é o jogador vencedor e o segundo o jogo
                std::cout << vencedor_e_jogo.first << ' ' << vencedor_e_jogo.second;
                switch (vencedor_e_jogo.second)
                {
                case 1:
                    if (vencedor_e_jogo.first == 1)
                    {
                        jogador1->setVitorias(jogador1->getReversi(),jogador1->getReversi()._vitorias + 1);
                        if (jogador2)
                        {
                            jogador2->setDerrotas(jogador2->getReversi(),jogador2->getReversi()._derrotas + 1);
                        }
                    }
                    if (vencedor_e_jogo.first == 2)
                    {
                        jogador1->setDerrotas(jogador1->getReversi(),jogador1->getReversi()._derrotas + 1);
                        if (jogador2)
                        {
                            jogador2->setVitorias(jogador2->getReversi(),jogador2->getReversi()._vitorias + 1);
                        }

                    }
                case 2: // Jogo: Velha
                    if (vencedor_e_jogo.first == 1)
                    {
                        jogador1->setVitorias(jogador1->getVelha(), jogador1->getVelha()._vitorias + 1);
                        if (jogador2)
                        {
                            jogador2->setDerrotas(jogador2->getVelha(), jogador2->getVelha()._derrotas + 1);
                        }
                    }
                    if (vencedor_e_jogo.first == 2)
                    {
                        jogador1->setDerrotas(jogador1->getVelha(), jogador1->getVelha()._derrotas + 1);
                        if (jogador2)
                        {
                            jogador2->setVitorias(jogador2->getVelha(), jogador2->getVelha()._vitorias + 1);
                        }
                    }
                    break;

                case 3: // Jogo: Lig4
                    if (vencedor_e_jogo.first == 1)
                    {
                        jogador1->setVitorias(jogador1->getLig4(), jogador1->getLig4()._vitorias + 1);
                        if (jogador2)
                        {
                            jogador2->setDerrotas(jogador2->getLig4(), jogador2->getLig4()._derrotas + 1);
                        }
                    }
                    if (vencedor_e_jogo.first == 2)
                    {
                        jogador1->setDerrotas(jogador1->getLig4(), jogador1->getLig4()._derrotas + 1);
                        if (jogador2)
                        {
                            jogador2->setVitorias(jogador2->getLig4(), jogador2->getLig4()._vitorias + 1);
                        }
                    }
                    break;
                
                default:
                    std::cout << "Jogo inválido ou não reconhecido!" << std::endl;
                    break;
                }
                jogoEmAndamento = false;
            }else 
            {
                jogadorAtual = (jogadorAtual == 1) ? 2 : 1;
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Erro durante a partida: " << e.what() << std::endl;
        return false;
    }
    return true;
}

/**
 * @brief Sobrecarga para iniciar uma partida com dificuldade específica.
 * @param dificuldade Nível de dificuldade para bots (não implementado).
 * @return true se a partida foi concluída com sucesso, false em caso de erro.
 */
bool Partida::iniciarPartida(int dificuldade) {
    // Implementação futura para diferentes níveis de dificuldade
    return iniciarPartida();
}

/**
 * @brief Imprime o tabuleiro atual no console.
 * @param jogador_atual Indica qual jogador está jogando.
 */
void Partida::imprimirTabuleiro(int jogador_atual) const {
    jogoAtual->imprimir_vetor(jogador_atual);
}

/**
 * @brief Realiza a jogada de um jogador ou bot.
 * @param jogadorAtual Indica o jogador que fará a jogada.
 * @param linha Linha escolhida para a jogada (opcional para bots).
 * @param coluna Coluna escolhida para a jogada (opcional para bots).
 * @return true se a jogada foi válida, false caso contrário.
 */
bool Partida::realizarJogada(int jogadorAtual, int linha, int coluna) { 
    try {
        // Verifica se o jogador atual é um bot
        if ((jogadorAtual == 2 && !jogador2) || (jogadorAtual == 1 && !jogador1)) {
            BotPlayer* botAtual = (jogadorAtual == 2) ? bot1 : bot2;
            std::pair<int, int> jogadaBot;
            bool jogada_achada = false;
            int tentativas = 0;
            const int maxTentativas = 100; // Limite para evitar loop infinito

            while (!jogada_achada && tentativas < maxTentativas) {
                jogadaBot = botAtual->calcularProximaJogada(*jogoAtual, jogadorAtual);
                int botLinha = jogadaBot.first;
                int botColuna = jogadaBot.second;
                jogada_achada = jogoAtual->verificar_jogada(botLinha, botColuna, jogadorAtual);
                tentativas++;
                
                if (jogada_achada) {
                    std::cout << "\nA IA está pensando...\n";
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                    return jogoAtual->ler_jogada(botLinha, botColuna, jogadorAtual);
                }
            }

            if (!jogada_achada) {
                std::cerr << "Erro: O bot não encontrou uma jogada válida após " << maxTentativas << " tentativas.\n";
            }
            return false;
        }

        // Entrada do jogador humano
        bool jogada_valida = false;
        while (!jogada_valida) {
            if (linha == -1 || coluna == -1) {
                std::cout << "\nJogador " << jogadorAtual << ", faça sua jogada:";

                if (auto* lig4 = dynamic_cast<Lig4*>(jogoAtual.get())) {
                    std::cout << "Coluna: ";
                    std::cin >> coluna;
                    linha = -1; // Para Lig4, a linha é determinada automaticamente
                } else {
                    std::cout << "Linha: ";
                    std::cin >> linha;
                    std::cout << "\nColuna: ";
                    std::cin >> coluna;
                }
            }

            linha -= 1;
            coluna -= 1;

            jogada_valida = jogoAtual->verificar_jogada(linha, coluna, jogadorAtual);
            if (!jogada_valida) {
                std::cout << "Jogada inválida! Tente novamente.\n";
                linha = -1; // Reseta para forçar nova entrada
                coluna = -1;
            }
        }

        return jogoAtual->ler_jogada(linha, coluna, jogadorAtual);

    } catch (const std::exception& e) {
        std::cerr << "Erro ao realizar jogada: " << e.what() << std::endl;
    }

    return false;
}


/**
 * @brief Verifica se o jogador atual tem jogadas disponíveis.
 * @param jogadorAtual Indica o jogador que está verificando as jogadas.
 * @return true se há jogadas disponíveis, false caso contrário.
 */
bool Partida::verificarJogadasDisponiveis(int jogadorAtual) const {
    try {
        if (auto* reversi = dynamic_cast<Reversi*>(jogoAtual.get())) {
            auto jogadas = reversi->atualizar_jogadas_validas(jogadorAtual);
            for (const auto& linha : jogadas) {
                for (bool jogada : linha) {
                    if (jogada) return true;
                }
            }
            return false;
        }

        if (auto* lig4 = dynamic_cast<Lig4*>(jogoAtual.get())) {
            for (int coluna = 0; coluna < lig4->getColunas(); coluna++) {
                if (lig4->verificar_jogada(0, coluna, jogadorAtual)) {
                    return true;
                }
            }
            return false;
        }

        if (auto* velha = dynamic_cast<JogoDaVelha*>(jogoAtual.get())) {
            for (int i = 0; i < velha->getLinhas(); i++) {
                for (int j = 0; j < velha->getColunas(); j++) {
                    if (velha->verificar_jogada(i, j, jogadorAtual)) {
                        return true;
                    }
                }
            }
            return false;
        }

    } catch (const std::exception& e) {
        std::cerr << "Erro ao verificar jogadas disponíveis: " << e.what() << std::endl;
    }

    return false;
}

/**
 * @brief Verifica se as condições de fim de jogo foram atingidas.
 * @return true se o jogo terminou, false caso contrário.
 */
bool Partida::verificarFimDeJogo() const {
    return jogoAtual->testar_condicao_de_vitoria();
}

/**
 * @brief Finaliza a partida e exibe o resultado.
 */
std::pair<int, int> Partida::finalizarPartida() {
    std::cout << "Jogo finalizado!" << std::endl;
    std::pair<int, int> vencedor_e_jogo;
    if (auto* reversi = dynamic_cast<Reversi*>(jogoAtual.get())) {
        vencedor_e_jogo.first = reversi->anunciar_vencedor();
        vencedor_e_jogo.second = 1;
    }
    else if (auto* velha = dynamic_cast<JogoDaVelha*>(jogoAtual.get()))
    {
        vencedor_e_jogo.first = velha->anunciar_vencedor();
        vencedor_e_jogo.second = 2;
    }
    else if (auto* lig4 = dynamic_cast<Lig4*>(jogoAtual.get()))
    {
        vencedor_e_jogo.first = lig4->anunciar_vencedor();
        vencedor_e_jogo.second = 3;
    }
    return vencedor_e_jogo;
}
