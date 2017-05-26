# Azo


Repositório para o desenvolvimento do jogo _Azo_ na matéria de Introdução à Jogos Eletrônicos, Universidade de Brasília.


### Envolvidos no Projeto

* Allan Jefrey (Desenvolvedor - UnB FGA);
* Hugo Alves (Desenvolvedor - UnB FGA);
* Roger Lenke (Desenvolvedor - UnB FGA);
* Murilo Oliveira (Músico - UnB Darcy Ribeiro);
* Marina Rebello (Designer - UnB Darcy Ribeiro);
* Thainá Ferreira (Designer - UnB Darcy Ribeiro).


### Introdução e Objetivos

Azo é um jogo onde o jogador deve controlar três diferentes personagens em diferentes épocas, para corrigir a distorção nas linhas temporais!


### História

No ano de 2097, uma filósofa humana e um cientista de uma raça alienígena discutem para saber quem veio primeiro: o ovo, ou a galinha. Sem chegar num consenso, ambos acordam em projetar uma máquina do tempo para que possam verificar por si mesmos. Infelizmente, os cálculos para a concepção da máquina estavam errados, o que causou uma explosão na máquina do tempo e distorceu as linhas temporais! Agora, três diferentes heróis serão escolhidos para coletar os fragmentos da máquina e corrigir o tempo, ou o universo estará condenado para sempre.

### Características

* Gênero: Runner/Plataforma.
* Quantidade de jogadores: Single-player.
* Quantidade de níveis: Quatro.
* Personagens: Cinco personagens, sendo três jogáveis.

### Aspectos fundamentais e diferencial

O aspecto primordial que guia o jogo é a coleta dos fragmentos da máquina do tempo dentro de cada fase (fendas). O diferencial de _Azo_ para com outros runners é que a corrida é baseada no ritmo das músicas de cada fase, sendo estas músicas produzidas de acordo com a temática de cada personagem.

### Personagens

* Uma filósofa humana, que acredita que o ovo veio antes da galinha.
* Um alien cientista, que defende que a galinha veio antes do ovo.
* Um forasteiro do velho oeste, que resolve ajudar a filósofa e o cientista por dinheiro.
* Uma universitária, que gasta toda a mesada em doces, moda e jogos, e vai ajudá-los por diversão.
* Um ninja ciborgue ultrapassado, que vai atrás dos fragmentos para conseguir uma atualização de hardware prometida pelo cientista.

### Objetos

Os objetos presentes no jogo são:
* Obstáculos de pulo.
* Obstáculos para abaixar/deslizar.
* Plataformas comuns.
* Buracos.
* Espinhos.
* Fragmentos da máquina do tempo, que são coletáveis.
* Itens de poder, que também são coletáveis.

### Estrutura

* O menu inicial é composto pelas opções:
  * Novo jogo.
  * Continuar.
  * Informações.
  * Habilitar/Desabilitar som.
* Ao iniciar o jogo, _cutscenes_ que explicam a história.
* Após as _cutscenes_ é iniciada a primeira fase do jogo, com o primeiro personagem.
* As fases são formadas por conjuntos dos objetos descritos, de maneira que estes estão organizados para que o jogador se movimente de acordo com o ritmo da música tema da fase.
* A cada fase completada, um fragmento da máquina do tempo é recolhido, o que permite ao jogador avançar na história.
* A cada fase completada, uma nova fase de um novo personagem é disponibilizada. Essa dinâmica se repete até que o jogador termine o jogo.
* Na fase final, o jogador precisa controlar todos os personagens para levar o fragmento através da última fenda temporal.
* Após o término do jogo, todas as fases ficam disponíveis no modo arcade, de maneira que o jogador pode utilizar qualquer personagem em qualquer fase.

### Controles

O jogador pode:
* Saltar obstáculos.
* Deslizar por baixo de obstáculos.
* Ativar a habilidade especial.

### Produto final

Será entregue como produto final:
* Três fases completas, onde o _running_ é feito no ritmo da melodia tema da fase, com condição de vitória e de derrota.
* Três personagens jogáveis.
* Um poder especial para cada personagem jogável.
* Um menu inicial.
* Cutscenes que explicam a história após o início de um novo jogo.
* Cutscenes referentes a cada personagem jogável.
* Custcenes de entrada na fase final.

### Cronograma
#### Entrega dos dias 31/05 e 01/06 (30%)

* Sprites dos personagens.
* Elementos visuais iniciais de cada fase.
* Engine.
* Menu parcialmente implementado.
* Possibilidade de habilitar ou desabilitar o som.
* Colisão.

#### Entrega dos dias 21/06 e 23/06 (70%)

* Sprites de todas as fases.
* Sprites de todos os personagens.
* Arte do menu.
* Uma fase completamente jogável, com melodia e ritmada.

#### Entrega do dia 07/06 (100%)

* Todas as cutscenes que explicam a história e os personagens.
* Todas as fases concluídas.
* Menu completamente implementado.
