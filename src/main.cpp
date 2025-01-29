#include <iostream>
#include <stdlib.h>
#include <string>
#include "cadastro.hpp"
#include "jogos.hpp"
#include "partida.hpp"
#include <algorithm>

void mostrarMenu() {
    std::cout << "\n=== Menu de Comandos ===" << std::endl;
    std::cout << "CJ - Cadastrar novo jogador" << std::endl;
    std::cout << "RJ - Remover jogador" << std::endl;
    std::cout << "LJ - Listar jogadores" << std::endl;
    std::cout << "PJ - Procurar jogador" << std::endl;
    std::cout << "NP - Nova partida" << std::endl;
    std::cout << "F  - Finalizar programa" << std::endl;
    std::cout << "H  - Ajuda (mostra este menu)" << std::endl;
    std::cout << "=====================" << std::endl;
}

void cadastrarJogador(Cadastro& jogadores) {
    std::string nome, apelido;
    std::cout << "Digite o nome do jogador: ";
    std::cin.ignore();
    std::getline(std::cin, nome);
    std::cout << "Digite o apelido do jogador: ";
    std::getline(std::cin, apelido);
    
    Jogador novoJogador(nome, apelido);
    
    if (!jogadores.check(novoJogador)) {
        jogadores.adicionarJogador(novoJogador);
        jogadores.save("./include/cadastro.txt");
    } else {
        std::cout << "ERRO: Jogador já cadastrado!" << std::endl;
    }
}

void removerJogador(Cadastro& jogadores) {
    std::string apelido;
    std::cout << "Digite o apelido do jogador a ser removido: ";
    std::cin.ignore();
    std::getline(std::cin, apelido);
    
    Jogador alvo("", apelido);
    jogadores.removeJogador(alvo);
    jogadores.save("./include/cadastro.txt");
}

void procurarJogador(const Cadastro& jogadores) {
    std::string apelido;
    std::cout << "Digite o apelido do jogador: ";
    std::cin.ignore();
    std::getline(std::cin, apelido);
    
    Jogador alvo("", apelido);
    if (jogadores.check(alvo)) {
        std::cout << "Jogador encontrado!" << std::endl;
    } else {
        std::cout << "Jogador não encontrado." << std::endl;
    }
}

void iniciarNovaPartida(Cadastro& jogadores) {
    std::string apelido1, apelido2;
    int tipoJogo;
    bool vsBot = false;
    
    std::cout << "=== Tipos de Jogo ===" << std::endl;
    std::cout << "1 - Jogo da Velha" << std::endl;
    std::cout << "2 - Lig4" << std::endl;
    std::cout << "3 - Reversi" << std::endl;
    std::cout << "Escolha o tipo de jogo: ";
    std::cin >> tipoJogo;
    
    if (tipoJogo < 1 || tipoJogo > 3) {
        std::cout << "Tipo de jogo inválido!" << std::endl;
        return;
    }
    
    std::cout << "Jogar contra BOT? (1-Sim, 0-Não): ";
    std::cin >> vsBot;
    
    std::cout << "Digite o apelido do Jogador 1: ";
    std::cin.ignore();
    std::getline(std::cin, apelido1);
    
    Jogador jogador1("", apelido1);
    if (!jogadores.check(jogador1)) {
        std::cout << "Jogador 1 não encontrado!" << std::endl;
        return;
    }
    
    if (!vsBot) {
        std::cout << "Digite o apelido do Jogador 2: ";
        std::getline(std::cin, apelido2);
        
        Jogador jogador2("", apelido2);
        if (!jogadores.check(jogador2)) {
            std::cout << "Jogador 2 não encontrado!" << std::endl;
            return;
        }
        
        Partida partida(tipoJogo, &jogador1, &jogador2);
        partida.iniciarPartida();
    } else {
        Partida partida(tipoJogo, &jogador1);
        partida.iniciarPartida();
    }
    
    // Após a partida, salva as atualizações do cadastro
    jogadores.save("./include/cadastro.txt");
}

int main() {
    Cadastro jogadores;
    jogadores.import("./include/cadastro.txt");
    
    std::vector<std::string> commands = {"CJ", "RJ", "LJ", "PJ", "NP", "F", "H"};
    std::string inputComando;
    
    std::cout << "Bem-vindo ao Sistema de Jogos!" << std::endl;
    mostrarMenu();
    
    while (true) {
        std::cout << "\nDigite um comando: ";
        std::cin >> inputComando;
        
        // Converte o comando para maiúsculas
        std::transform(inputComando.begin(), inputComando.end(), inputComando.begin(), ::toupper);
        
        auto it = std::find(commands.begin(), commands.end(), inputComando);
        
        if (it == commands.end()) {
            std::cout << "Comando inválido! Digite 'H' para ver os comandos disponíveis." << std::endl;
            continue;
        }
        
        int indexComando = std::distance(commands.begin(), it);
        
        switch(indexComando) {
            case 0: // CJ
                cadastrarJogador(jogadores);
                break;
            case 1: // RJ
                removerJogador(jogadores);
                break;
            case 2: // LJ
                jogadores.mostrarJogadores();
                break;
            case 3: // PJ
                procurarJogador(jogadores);
                break;
            case 4: // NP
                iniciarNovaPartida(jogadores);
                break;
            case 5: // F
                std::cout << "Programa finalizado." << std::endl;
                return 0;
            case 6: // H
                mostrarMenu();
                break;
            default:
                std::cout << "Erro inesperado!" << std::endl;
                return 1;
        }
    }
    
    return 0;
}
