# Azo

Repositório para a matéria de Técnicas de Programação, Universidade de Brasília-FGA, para refatoração do projeto _Azo_, que foi desenvolvido na matéria de Introdução à Jogos Eletrônicos, Universidade de Brasília.


### Envolvidos no Projeto
#### Refatoração
* Miguel Alves (Desenvolvedor - UnB FGA);
* Kamila Costa (Desenvolvedor - UnB FGA);
* Igor Aragão (Desenvolvedor - UnB FGA);
* Lucas Vitor (Desenvolvedor - UnB FGA);
* Samuel Borges (Desenvolvedor - UnB FGA);
* Lude Ribeiro (Desenvolvedor - UnB FGA);
* Eduardo Lima (Desenvolvedor - UnB FGA);
* Nathalia Lorena (Desenvolvedor - UnB FGA);

#### Projeto Original
* Allan Jefrey (Desenvolvedor - UnB FGA);
* Hugo Alves (Desenvolvedor - UnB FGA);
* Roger Lenke (Desenvolvedor - UnB FGA);
* Murilo Oliveira (Músico - UnB Darcy Ribeiro);
* Marina Rebello (Designer - UnB Darcy Ribeiro);
* Thainá Ferreira (Designer - UnB Darcy Ribeiro).

### Introdução e Objetivos

Aplicar sobre o projeto _Azo_ as Técnicas de Programação aprendidas no decorrer da matéria Técnicas de Programação. Evoluir o código e arquitetura visando melhorar a qualidade do código e aplicar os conhecimentos adiquiridos.

"Azo é um jogo onde o jogador deve controlar três diferentes personagens em diferentes épocas, para corrigir a distorção nas linhas temporais!"

### História

No ano de 2097, uma filósofa humana e um cientista de uma raça alienígena discutem para saber quem veio primeiro: o ovo, ou a galinha. Sem chegar num consenso, ambos acordam em projetar uma máquina do tempo para que possam verificar por si mesmos. Infelizmente, os cálculos para a concepção da máquina estavam errados, o que causou uma explosão na máquina do tempo e distorceu as linhas temporais! Agora, três diferentes heróis serão escolhidos para coletar os fragmentos da máquina e corrigir o tempo, ou o universo estará condenado para sempre.

### Características

* Gênero: Runner/Plataforma.
* Quantidade de jogadores: Single-player.
* Quantidade de níveis: 1.
* Personagens: 1.

### Objetos

Os objetos presentes no jogo são:
* Obstáculos de pulo.
* Obstáculos para abaixar/deslizar.
* Plataformas comuns.
* Espinhos.
* Fragmentos da máquina do tempo, que são coletáveis.

### Controles

O jogador pode:
* Saltar obstáculos (tecla 'w').
* Deslizar por baixo de obstáculos (tecla 's').
* Selecionar opções nos menus (tecla 'seta para direita' e 'seta para esquerda').
* Ativar as opções selecionadas (tecla enter).

### Dependências

Para executar o jogo com sucesso é necessário possuir instaladas tais dependências:
* CMake 3.5.1
* SDL 2
* SDL_image 2
* SDL_ttf 2
* SDL_mixer 2

### Como executar

No terminal do sistema operacional (Linux), utilize os comandos na pasta do clone do projeto:
```
$ mkdir build
```
```
$ cd build
```
```
$ cmake ..
```
```
$ make
```
```
$ ./Azo
```

Também é possível criar um instalador .deb para o projeto com os seguintes comandos:
```
$ mkdir build
```
```
$ cd build
```
```
$ cmake ..
```
```
$ make package
```

O instalador estará localizado na pasta build.
