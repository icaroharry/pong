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

char* encrypt(char* password);

char* decrypt(char* password);

Player requireLogin();

Player getPlayer(char* login);

int logIn(char* login, char* password);

int existsPlayer(char* login);

void savePlayerToDatabase(Player player);
