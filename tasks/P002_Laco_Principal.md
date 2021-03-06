### Laço Principal

O código de um jogo eletrônico tem como característica a presença de um laço
principal, que após a inicialização dos recursos e periféricos necessários à
execução do jogo, fica responsável pela captura das entradas do usuário,
atualização do estado do jogo e pela composição de cada tela.

Usando uma abordagem _top-down_ de desenvolvimento, o primeiro código a
ser escrito é o laço principal, onde cada tarefa a ser realizada é representada
por um _stub_ (uma função sem implementação ou com uma implementação mínima
que permita a compilação). A ideia é que cada uma destas funções seja
implementada por um ou mais _stubs_, particionando cada problema em
partes cada vez menores, até funcionalidades simples e atômicas, que serão
implementadas de fato, eliminando o _stub_. Quando todos os _stubs_ forem
removidos do código, o jogo estará implementado.

### Outputs

Os códigos que implementam o laço principal, com _stubs_. Estes
códigos devem conter, além da referida implementação, a estrutura de diretórios
a ser utilizada e os arquivos e _scripts_ necessários para a construção do jogo
e dos demais artefatos do projeto.
