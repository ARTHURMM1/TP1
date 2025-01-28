#ifndef CADASTRO_HPP
#define CADASTRO_HPP

#include <iostream>
#include <vector>
#include <string>
#include <fstream> 
#include <memory>
#include <algorithm>

struct Winrate {
    int _vitorias;
    int _derrotas;

};

class Jogador {
private:
    Winrate Velha;  // Primeiro membro
    Winrate Lig4;   // Segundo membro
    Winrate Reversi; // Terceiro membro
    std::string _nome;
    std::string _apelido;
    //adicionar outros jogos

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

    // serializar o jogador como string para salvar em arquivo
    std::string serializar() const;

    //deserializar uma string para criar um jogador
    static Jogador deserializar(const std::string& linha);
};


class Cadastro {
private:
    std::vector<std::unique_ptr<Jogador>> _jogadores;

public:

    const std::vector<std::unique_ptr<Jogador>>& get_jogadores() const {
    return _jogadores; }

    //adiciona um jogador ao vetor de cadastro
    void adicionarJogador(const Jogador& alvo);

    //mostra o vetor de cadastros
    void mostrarJogadores() const;

    //importa de um arquivo .txt todos os cadastros
    void import(const std::string& caminho) ;

    //salva e atualiza os dados de cadastro em um .txt
    void save(const std::string& caminho) ;

    //remove o jogador alvo do vetor de cadastros
    void removeJogador(const Jogador& alvo) ;

    //verifica se o jogador alvo está no vetor de cadastros, retorna 0 ou 1.
    bool check(const Jogador& alvo) const ;

};

#endif
