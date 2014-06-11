#include "jogador.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

char* encrypt(char* password) {
	int i = 0;
	for(i = 0; i < strlen(password); i++) {
		password[i] -= 57;		
	}
	return password;
}

char* decrypt(char* password) {
  int i = 0;
  for(i = 0; i < strlen(password); i++) {
    password[i] += 57;    
  }
  return password;
}


Player requireLogin(){

  char login[8];
  char password[8];
  char auxPassword[8];

  Player player;
  char ch;
  bool logged = false;
  system("clear");
  while(!logged) {
    system("clear");
    printf("Digite <L> para Login ou <C> para Cadastro: ");
    scanf("%c", &ch);
    fflush(stdout);
    switch(ch) {
      case 'L':
        system("clear");
        printf("Login: ");
        scanf("%s", &login);
        printf("\nPassword: ");
        scanf("%s", &password);
        if(logIn(login, password) == 1) {
          logged = true;
          return getPlayer(login);
        }
        system("clear");
        printf("\nLogin ou senha invalidos!\n");
        system("read -p \"Pressione qualquer tecla para continuar...\" ");
        system("clear");
      break;
      case 'C':
        system("clear");
        printf("Login: ");
        scanf("%s", &player.login);
        printf("\nSenha: ");
        scanf("%s", &player.password);
        printf("\nConfirme sua senha: ");
        scanf("%s", &auxPassword);
        printf("\nNome: ");
        scanf("%s", &player.name);
        printf("\nIdade: ");
        scanf("%d", &player.age);
        if(strcmp(player.password, auxPassword) == 0) {
          if (existsPlayer(player.login) == -1) {
            player.bestScore = 0;
            player.wins = 0;
            savePlayerToDatabase(player);
            system("clear");
            printf("Jogador cadastrado com sucesso!\n");
            logged = true;
            system("read -p \"Pressione <enter> para jogar...\" ");
            system("clear");
            return player;
          } 
          else {
            system("clear");
            printf("Ja existe um jogador com esse login!\n");
            system("read -p \"Pressione <enter> para continuar1...\" ");
            system("clear");
          }
        }
        else {
          printf("As senhas digitadas sao diferentes!\n");
          
          system("read -p \"Pressione <enter> para continuar2...\" ");
          system("clear");
        } 
      break;
      default:
        printf("Opcao invalida!\n");
        system("read -p \"Pressione <enter> para continuar2...\" ");
        system("clear");
        fflush(stdout);
    }
  }
}

int logIn(char* login, char* password) {
  char buf[255];
  char loginDB[8];
  char passwordDB[8];
  char* auxPasswordDB;

  char auxLogin[8];
  char auxPassword[8];
  strcpy(auxLogin, login);
  strcpy(auxPassword, password);
  FILE* players_database;
  players_database = fopen("players_database.txt", "r");   
  if (players_database == NULL) {    
      printf("Error! The file could not be opened.\n");    
      exit(1);               
  }
  fgets(buf, 255, players_database);
  while(!feof(players_database)) {
    strcpy(loginDB, strtok(buf, ", "));
    auxPasswordDB = strtok(NULL, ", ");
    auxPasswordDB = decrypt(auxPasswordDB);
    strcpy(passwordDB, auxPasswordDB);
    if(strcmp(auxLogin, loginDB) == 0) {
      if(strcmp(auxPassword, passwordDB) == 0){
        fclose(players_database);
        return 1;
      }
    }
    fgets(buf, 255, players_database);
  }
  fclose(players_database);
  return -1;  
} 

int existsPlayer(char* login) {
  char buf[255];
  char auxLogin[8];
  strcpy(auxLogin, login);
  char loginDB[255];

  FILE* players_database;       
  players_database = fopen ("players_database.txt", "r");   
  if (players_database == NULL) {    
      printf("Error! The file could not be opened.\n");    
      exit(1);               
  }
  fgets(buf, 255, players_database);
  while(!feof(players_database)) {
    strcpy(loginDB, strtok(buf, ", "));
    if(strcmp(auxLogin, loginDB) == 0) {
      fclose(players_database);
      return 1;
    }
    fgets(buf, 255, players_database);
  }
  fclose(players_database);
  return -1;
}


Player getPlayer(char* login) {
  Player player;
  char buf[255];
  char auxLogin[8];
  strcpy(auxLogin, login);
  char auxLoginDB[8];
  char password[8];
  char name[8];
  int age;
  int bestScore;
  int wins;
  FILE* players_database;       
  players_database = fopen ("players_database.txt", "r");   
  if (players_database == NULL) {    
      printf("Error! The file could not be opened.\n");    
      exit(1);               
  }
  fgets(buf, 255, players_database);
  while(!feof(players_database)) {
    strcpy(auxLoginDB, strtok(buf, ", "));
    strcpy(password, strtok(NULL, ", "));
    strcpy(name, strtok(NULL, ", "));
    age = atoi(strtok(NULL, ", "));
    bestScore = atoi(strtok(NULL, ", "));
    wins = atoi(strtok(NULL, ", "));
    printf("%s   %s\n",auxLogin, auxLoginDB);
    if(strcmp(auxLogin, auxLoginDB) == 0) {
      printf("vivo2\n");
      strcpy(player.login, auxLogin);
      strcpy(player.password, password);
      strcpy(player.name, name);
      player.age = age;
      player.bestScore = bestScore;
      player.wins = wins;
      fclose(players_database);
      return player;
    }
  }
  fclose(players_database);
  return player;
}

void savePlayerToDatabase (Player player) {
	FILE* players_database;       
   	players_database = fopen ("players_database.txt", "a");   
   	if (players_database == NULL) {    
        printf("Error! The file could not be opened.\n");    
        exit(1);               
  	}
  	fprintf(players_database, "%s, %s, %s, %d, %d, %d\n", player.login, encrypt(player.password), player.name, player.age, player.bestScore, player.wins); 
   	fclose(players_database);
}

void saveScore (Player player) {
  char buf[255];
  char login[8];
  char password[8];
  char name[8];
  int age;
  int bestScore;
  int wins;
  FILE* players_database;
  FILE* temp; 
  fclose(players_database);      
  players_database = fopen ("players_database.txt", "r");   
  if (players_database == NULL) {    
      printf("Error! The file could not be opened.\n");    
      exit(1);               
  }

  temp = fopen("temp.txt", "w");   
  if (players_database == NULL) {    
      printf("Error! The temp file could not be opened.\n");    
      exit(1);               
  }
  fgets(buf, 255, players_database);
  while(!feof(players_database)) {
    strcpy(login, strtok(buf, ", "));
    strcpy(password, strtok(NULL, ", "));
    strcpy(name, strtok(NULL, ", "));
    age = atoi(strtok(NULL, ", "));
    bestScore = atoi(strtok(NULL, ", "));
    wins = atoi(strtok(NULL, ", "));
    
    if(strcmp(player.login, login) == 0) {
      if(player.currentDefenses > bestScore);
        player.bestScore = player.currentDefenses; 
      player.wins++;
    }
    fprintf(temp, "%s, %s, %s, %d, %d, %d\n", player.login, player.password, player.name, player.age, player.bestScore, player.wins);
    fgets(buf, 255, players_database);
  }
  fclose(players_database);
  remove("players_database.txt");
    //renomeia o arquivo temporario
  rename("temp.txt", "players_database");

  //fclose(players_database);
}

