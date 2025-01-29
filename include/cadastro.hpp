#ifndef CADASTRO_HPP
#define CADASTRO_HPP

/**
 * @file cadastro.hpp
 * @brief Declaração das classes e métodos relacionados ao gerenciamento de jogadores e seus cadastros.
 */

#include <iostream>
#include <vector>
#include <string>
#include <fstream> 
#include <memory>
#include <algorithm>

/**
 * @struct Winrate
 * @brief Estrutura para armazenar vitórias e derrotas de um jogador em um jogo específico.
 * @param _vitorias Número de vitórias.
 * @param _derrotas Número de derrotas.
 */
struct Winrate {
    int _vitorias; 
    int _derrotas; 
};

/**
 * @class Jogador
 * @brief Representa um jogador com informações como nome, apelido e desempenho em diferentes jogos.
 */
class Jogador {
private:
    Winrate Velha;   
    Winrate Lig4;    
    Winrate Reversi;
    //adicionar outros jogos aqui.
    std::string _nome;   
    std::string _apelido; 

public:
    // construtor
    Jogador(const std::string& nome = "", const std::string& apelido = "", int vitorias1 = 0, int derrotas1 = 0, int vitorias2 = 0, int derrotas2 = 0, int vitorias3 = 0, int derrotas3 = 0)
        : _nome(nome), _apelido(apelido), 
        Velha{vitorias1, derrotas1}, 
        Lig4{vitorias2, derrotas2}, 
        Reversi{vitorias3, derrotas3}
        //adicionar outros jogos aqui.
        {}

    //destrutor
    ~Jogador() {}

    // métodos de acesso
    std::string getNome() const { return _nome; }
    std::string getApelido() const { return _apelido; }
    const Winrate& getLig4() const { return Lig4; }
    const Winrate& getReversi() const { return Reversi; }
    const Winrate& getVelha() const { return Velha; }
    //possível adicionar outros jogos aqui.
    int getVitorias(const Winrate& jogo) const { return jogo._vitorias; }
    int getDerrotas(const Winrate& jogo) const { return jogo._derrotas; }
    
    void setNome(const std::string& nome) { _nome = nome; }
    void setApelido(const std::string& apelido) { _apelido = apelido; }
    void setVitorias(Winrate& jogo, int vitorias) { jogo._vitorias = vitorias; }
    void setDerrotas(Winrate& jogo, int derrotas) { jogo._derrotas = derrotas; }

    std::string serializar() const;
    static Jogador deserializar(const std::string& linha);
};

/**
 * @class Cadastro
 * @brief Gerencia o cadastro de jogadores, incluindo adição, remoção e persistência de dados.
 */
class Cadastro {
private:
    std::vector<std::unique_ptr<Jogador>> _jogadores; ///< Vetor de ponteiros únicos para os jogadores cadastrados.

public:
    const std::vector<std::unique_ptr<Jogador>>& get_jogadores() const { return _jogadores; }
    void adicionarJogador(const Jogador& alvo);
    void mostrarJogadores() const;
    void import(const std::string& caminho);
    void save(const std::string& caminho);
    void removeJogador(const Jogador& alvo);
    bool check(const Jogador& alvo) const;
};

#endif
