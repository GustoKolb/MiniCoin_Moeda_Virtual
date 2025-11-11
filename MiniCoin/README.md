# MiniCoin_Moeda_Virtual
Trabalho prático de Redes 2. A complementar

Para o websocket usamos o framework Drogon de C++ https://github.com/drogonframework/drogon

Instruções de instalação em https://drogonframework.github.io/drogon-docs/#/ENG/ENG-02-Installation

Para rodar o servidor, use

cmake
make
./miniCoin

Por default, o servidor escuta no port *, *WIP*

Por enquanto, o plano é desenvolver usando o programa CLI drogon_ctl para contruir os controllers, views e models.

Alterações que fiz:

Mudei a classe Currency. Agora ela recebe ou float ou um double aí o seu valor (objeto.number) carrega um long, e você usa getCurrency() para pegar o valor em double.

Criei a classe Message com os enums e o formato geral. Com o construtor tu cria uma espécie de json, e a classe tem métodos para trocar de json para string e vice-versa. Isso é necessário pq o .sendText do drogon só usa string.

BlockChain agora é Singleton. Tem método init para inicializar a Lista e get para instanciar. Tentar dar get sem dar init antes gera aviso. O que fiz foi quando o Servidor recebe um Type::INIT ele cria a lista.

Criei um cliente simples que envia um Type::INIT. Para compilar o cliente e o servidor é make. Para rodar, respectivamente, é make client e make run.

Agora faltava desenvolver melhor as mensagens do cliente e como o servidor vai tratá-las.
