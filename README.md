**##Pong**
## Informações

> 
- Compilado no gcc (GCC) 4.8.2 20131212 (Red Hat 4.8.2-7);
- Testado no sistema operacional Fedora 20;
- Não funciona no Windows.


## Instruções de compilaçãoCom todos o arquivos no mesmo diretório, abra o terminal e digite:
``` shell
gcc -c pong.c

gcc pong.o -o pong $(pkg-config --libs allegro-5.0 allegro_image-5.0 allegro_font-5.0 allegro_ttf-5.0 allegro_primitives-5.0) jogador.p

./pong
```

## Instruções de jogo1. Na tela inicial digite L para Login ou C para cadastro e pressione <Enter>;
2. Para cadastrar, digite seu login, senha, nome e idade;
	- Não podem existir logins iguais na base de dados;
	- Você deve confirmar a senha digitada;
	- O número máximo de caracteres para o login e a senha é 8;
    - Para o nome digite apenas o primeiro nome, sem espaços.
3. Para fazer login 







