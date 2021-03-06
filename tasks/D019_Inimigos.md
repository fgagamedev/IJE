### Inimigos

#### Regras gerais para inimigos

Antes de detalhar cada tipo de inimigo, é preciso identificar os inimigos
de forma geral, os classificando segundo critérios que permitam analisar sua
diversidade, pontos fortes e fracos, de modo a atingir o correto balanceamento
do jogo.

Devem ser descritos:

1. comportamentos dos inimigos (patrulha, voador, caçador, etc);
2. regras de inteligência artificial e métricas de detecção (campo de
visão, audição, etc);
3. parâmetros de criação/distribuição dos inimigos;
4. parâmetros para derrota do inimigo;
5. regras para recompensas associadas à derrota dos inimigos (itens,
dinheiro, experiência, etc).

#### Inimigos específicos de níveis

Cada nível deve ter um conjunto de inimigos que o populem. Mesmo que boa parte
dos inimigos já tenham sido introduzidos em níveis anteriores, é importante
apresentar novos inimigos a cada nível, evitando que o jogo fique demasiadamente
previsível e cansativo, além de deixar o jogador sempre alerta e com a sensação
de descoberta e exploração.

Para cada nível, deverão ser listados todos os seus inimigos (os novos, os já
descritos anteriormente podem ser apenas referenciados), com descrições e
detalhamentos referentes:

1. à imagem do inimigo;
2. à descrição;
3. aos níveis onde este inimigo aparece;
4. aos padrões de movimentação do inimigo;
5. aos ataques (danos, alcance e efeitos);
6. às reações, dano por contato e morte;
7. às animações de espera;
8. às recompensas associadas à sua derrota.

#### Chefes

Um tipo especial de inimigo é o chefe de nível. Ele é o mais poderoso inimigo
do nível, com maior resistência, capacidade de dano e até mesmo maior
representação visual. A batalha com este chefe deve ser o clímax do nível,
passando ao jogador a sensação de perigo e heroísmo.

É preciso trabalhar bem um chefe de nível, dando a ele personalidade e o
tornando um elemento memorável do jogo. O game designer deve detalhar

1. a descrição e imagem do chefe;
2. a escala de tamanho;
3. os pontos fracos e pontos que podem ser atingidos pelo jogador;
4. as interações com a personagem principal (colisão, estados, etc);
5. os padrões de movimentação;
6. os padrões de ataque (que tendem a se modificar a medida que a
batalha avança): avisos, ataques específicos, danos, efeitos especiais,
reações, animações, etc;
7. a cena de apresentação do chefe;
8. o progresso da batalha e seus diferentes estágios;
9. a imagem do ambiente onde o chefe se encontra;
10. os itens, _power-ups_ e colecionáveis disponíveis neste ambiente;
11. os outros inimigos que podem surgir durante esta batalha;
12. o modo pelo qual o chefe pode ser vencido;
13. a recompensa ganha pela derrota do chefe.

### Outputs

Um capítulo ou seção do GDD, contemplando a descrição dos inimigos, segundo
os critérios apresentados.
