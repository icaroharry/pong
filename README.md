#Pong

## Informações

> 
- Compilado no gcc (GCC) 4.8.2 20131212 (Red Hat 4.8.2-7);
- Testado no sistema operacional Fedora 20;
- Não funciona no Windows.



##Ferramentas utilizadas

>- [Allegro 5](www.allegro.cc "Allegro 5")
- [Sublime Text 3](www.sublimetext.com/3 "Sublime Text 3")







## Instruções de compilação

Com todos o arquivos no mesmo diretório, abra o terminal e digite:

``` bash
gcc -c pong.c

gcc pong.o -o pong $(pkg-config --libs allegro-5.0 allegro_image-5.0 allegro_font-5.0 allegro_ttf-5.0 allegro_primitives-5.0) jogador.p

./pong
```




## Instruções de jogo
> 1. Na tela inicial digite L para Login ou C para cadastro e pressione ENTER;
2. Para cadastrar, digite seu login, senha, nome e idade;
	- Não podem existir logins iguais na base de dados;
	- Você deve confirmar a senha digitada;
	- O número máximo de caracteres para o login e a senha é 8;
    - Para o nome digite apenas o primeiro nome, sem espaços.
3. Para fazer login digite seu login e senha;
4. Após a verificação do login, o jogo será iniciado.
###Comandos
  - Controle com as setas para cima e para baixo (UP and DOWN);
  - Para sacar, pressione espaço.
  
  
  
## Módulo ["jogador.h"](https://github.com/icaroharry/pong/jogador.h)
> Struct que define um jogador.
currentScore e currentDefenses são variáveis auxiliares para armazenar a pontuação do jogador durante o jogo.


``` c
typedef struct Player {
	char login[8];
    char password[8];
    char name[100];
    int age;
    int bestScore;
    int wins;
    int currentScore;
    int currentDefenses;
} Player;
```

> Função que criptografa a senha, alterando os caracteres pelo seu código ascii.

``` c
char* encrypt(char* password);
```

> Função que descriptografa a senha, alterando os caracteres pelo seu código ascii original.

``` c
char* decrypt(char* password);
```

  
  
  










