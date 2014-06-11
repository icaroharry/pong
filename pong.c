#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <math.h>
#include <allegro5/allegro_primitives.h>
#include "jogador.h"
#include <string.h>

const float FPS = 60;
const int screenWidth = 640*2;
const int screenHeight = 480;

const int barWidth = 20;
const int barHeight = 100;

const int ballSize = 15;





int main(int argc, char** argv) {
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_EVENT_QUEUE *eventQueue = NULL;
	ALLEGRO_EVENT_QUEUE *eventQueue2 = NULL;		 

    Player player;
    Player computer;
    player = requireLogin();	
    player.currentScore = 0;
    player.currentDefenses = 0;
    player.wins;
    computer.currentDefenses = 0;
    computer.currentScore = 0;
    int currentPlayer = 0;
    bool finished = false;

	ALLEGRO_BITMAP *barOne = NULL;
	int barOneY = (int)(screenHeight / 2 - barHeight / 2);	
	int barOneX = 10;

	ALLEGRO_BITMAP *barTwo = NULL;
	int barTwoY = (int)(screenHeight / 2 - barHeight / 2);					
	int barTwoX = screenWidth - 30;

	ALLEGRO_BITMAP *ball = NULL;
    int ballX = barTwoX - ballSize - 1;
	int ballY = barTwoY;
	int ballDx = -5, ballDy = 5;
	int ballDxDy = 10;

	enum myKeys {
		KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_W, KEY_S, KEY_A, KEY_D
	};

	bool key[8] = {false, false, false, false, false, false, false, false};
	bool restart = false;
	bool redraw = true;
	bool exit = false;

	// Initialize Allegro
	if(!al_init()) {
		fprintf(stderr, "Error initializing Allegro!\n");
		return -1;
	}

	// Install the keyboard.
	if(!al_install_keyboard()) {
		fprintf(stderr, "Error installing keyboard!\n");
		return -1;
	}

	// Create the timer.
	timer = al_create_timer(1.0 / FPS);
	if(!timer) {
		fprintf(stderr, "Failed to create timer!\n");
		return -1;
	}

	// Create the display.
	display = al_create_display(screenWidth, screenHeight);
	if(!display) {
		fprintf(stderr, "Could not create display!\n");
		return -1;
	}

	// Create Pong Paddle One
	barOne = al_create_bitmap(barWidth, barHeight);
	if(!barOne) {
		fprintf(stderr, "Failed to create Pong Paddle One!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}

	// Set color of Pong Paddle One
	al_set_target_bitmap(barOne);
	al_clear_to_color(al_map_rgb(255,255,255));
	al_set_target_bitmap(al_get_backbuffer(display));

	// Create Pong Paddle Two
	barTwo = al_create_bitmap(barWidth, barHeight);
	if(!barTwo) {
		fprintf(stderr, "Failed to create Pong Paddle Two!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}

	// Set the color of Pong Paddle Two
	al_set_target_bitmap(barTwo);
	al_clear_to_color(al_map_rgb(255,255,255));
	al_set_target_bitmap(al_get_backbuffer(display));

	// Create the Ball
	ball = al_create_bitmap(ballSize, ballSize);
	if(!ball) {
		fprintf(stderr, "Failed to create ball!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}

	// Set the color of the ball.
	al_set_target_bitmap(ball);
	al_clear_to_color(al_map_rgb(255, 255, 255));
	al_set_target_bitmap(al_get_backbuffer(display));

	eventQueue = al_create_event_queue();
	if(!eventQueue) {
		fprintf(stderr, "Error creating event queue!\n");
		al_destroy_bitmap(barOne);
		al_destroy_bitmap(barTwo);
		al_destroy_bitmap(ball);
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}

	eventQueue2 = al_create_event_queue();
	if(!eventQueue2) {
		fprintf(stderr, "Error creating event queue!\n");
		al_destroy_bitmap(barOne);
		al_destroy_bitmap(barTwo);
		al_destroy_bitmap(ball);
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}
	al_register_event_source(eventQueue, al_get_display_event_source(display));
	al_register_event_source(eventQueue, al_get_timer_event_source(timer));
	al_register_event_source(eventQueue, al_get_keyboard_event_source());

	al_register_event_source(eventQueue2, al_get_keyboard_event_source());

	char text[100];
	char text2[100];
	al_init_font_addon();
    al_init_ttf_addon();

    ALLEGRO_FONT *size_32 = al_load_font("arial.ttf", 32, 1);

	al_clear_to_color(al_map_rgb(0,0,0));
	al_flip_display();

	al_start_timer(timer);


	// Contexto do jogo
	while(!exit) {
		redraw = true;
		ALLEGRO_EVENT ev;
		ALLEGRO_EVENT ev2;
		al_wait_for_event(eventQueue, &ev);

		if(ev.type == ALLEGRO_EVENT_TIMER) {
			
			//Tecla para cima pressionada
			if(key[KEY_UP] && barOneY >= 5) {
				barOneY -= 5;
				//barTwoY -= 5;
			}

			//Tecla para baixo pressionada
			if(key[KEY_DOWN] && barOneY <= screenHeight - barHeight - 5) {
				barOneY += 5;
				//barTwoY += 5;
			}

			//Movimenta bola em relação ao eixo Y.
			if(ballY < 0 || ballY > screenHeight - ballSize) {
				ballDy = -ballDy;
			}

			//Bola bateu na barra da esquerda
			if((ballX <= barOneX + barWidth) && (ballY + ballSize >= barOneY && ballY <= (barOneY + barHeight)) && restart == false) {
				player.currentDefenses++;
				ballDy = (int)((barOneY + (barHeight / 2)) - (ballY + (ballSize / 2)))/10;
				ballDy = -ballDy; 
				ballDx = (ballDxDy - abs(ballDy));
				ballDxDy++;
			}

			//Bola bateu na barra direita
			if((ballX >= barTwoX - ballSize) && (ballY >= barTwoY && ballY <= (barTwoY + barHeight)) && restart == false) {
				computer.currentDefenses++;
				ballDy = (int)((barTwoY + (barHeight / 2)) - (ballY + (ballSize / 2)))/10;
				ballDy = -ballDy; 
				ballDx = -(ballDxDy - abs(ballDy));
				ballDxDy++;
			}


			//I.A
			if(ballDx < 0 && (barTwoY > 0 && barTwoY + barHeight < screenHeight)) {
				barTwoY = ballDy;
			}

			/*if(ballDx > 0 && (ballY < barTwoY + (int)barHeight/2)){
				barTwoY += ballDy;
			}*/
			//if(ballDx > 0 && ballY > (barTwoY))
				//barTwoY -=ballDy;

			//Computador pontuou
			if((ballX < 0) && (ballY < barOneY || ballY > (barOneY + barHeight))) {
				computer.currentScore++;
				if(computer.currentScore == 1) {
					finished = true;
				};
				currentPlayer = 1; //indica onde a bola deve começar. 
				restart = true;

				ballX = barOneX + barWidth;
				ballY = barOneY + (int)(barHeight / 2) + 1;
				ballDy = 5;
				ballDx = 0;	
			} 

			//Jogador pontuou
			if((ballX > screenWidth) && (ballY < barTwoY || ballY > (barTwoY + barHeight))) {
				player.currentScore++;	
				if(player.currentScore == 1) {
					finished = true;
				};
				currentPlayer = 2;
				restart = true;

				ballX = barTwoX - ballSize;
				ballY = barTwoY + (int)(barHeight / 2) + 1;
				ballDy = 5;
				ballDx = 0;	
			}

				//Movimenta bola.
				ballX += ballDx;
				ballY += ballDy; 

		}

		//Pressionou ESC
		else if(ev.type == ALLEGRO_KEY_ESCAPE) {
			break;
		}

		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch(ev.keyboard.keycode) {
				//Pressionou seta para cima. Marca flag para movimentar
				case ALLEGRO_KEY_UP:
					key[KEY_UP] = true;
					break;
				//Pressionou seta para baixo. Marca flag para movimentar
				case ALLEGRO_KEY_DOWN:
					key[KEY_DOWN] = true;
					break;
			}
		}

		else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch(ev.keyboard.keycode) {
				//Soltou a seta para cima. Marca flag para parar
				case ALLEGRO_KEY_UP:
					key[KEY_UP] = false;
					break;
				//Soltou a seta para cima. Marca flag para parar
				case ALLEGRO_KEY_DOWN:
					key[KEY_DOWN] = false;
					break;
				//Pressionou ESC. Sai do jogo 
				case ALLEGRO_KEY_ESCAPE:
					exit = true;
					break;
				//Pressionou espaço. Saca se o flag restar == true
				case ALLEGRO_KEY_SPACE:
					if(restart == true) {
						//Player 2 pontou, bola deve voltar para Player 1
						if(currentPlayer == 1 && (ballX <= barOneX + barWidth) && (ballY + ballSize >= barOneY && ballY <= (barOneY + barHeight))) {
							restart = false;
							ballDxDy = 10;
							ballDy = 5;
						}
						//Player 1 pontuou, bola deve voltar para Player 2
						if (currentPlayer == 2 && (ballX >= barTwoX - ballSize) && (ballY >= barTwoY && ballY <= (barTwoY + barHeight))) {
							restart = false;
							ballDxDy = 10;
							al_rest(0.002);
							ballDx = 5;
						}
					}
				break;
			}
		}
		//Fechou a tela. Sai do jogo
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}

		//Terminou ciclo do while. Redesenha a tela
		if(redraw && al_is_event_queue_empty(eventQueue)) {
			redraw = false;
			sprintf(text, "X: %d, Y: %d, Dx: %d, Dy: %d", ballX, ballY, ballDx, ballDy);
			sprintf(text2, "Player 1: %d                                      Player 2: %d", player.currentScore, computer.currentScore);
			al_clear_to_color(al_map_rgb(0,0,0));
			al_draw_text(size_32, al_map_rgb(128, 200, 30), 10, 10, 0, text2);
			
			//Se jogo terminou, exibe mensagem e fecha janela.
			if(finished) {
				if(currentPlayer == 1) {
					sprintf(text2, "Computador venceu! %d rebatidas. Esc para sair", computer.currentDefenses);
					al_draw_text(size_32, al_map_rgb(128, 200, 30), 200, 300, 0, text2);
					//al_flip_display();
					ballDx = 0;
					ballDy = 0;
				}
				if(currentPlayer == 2) {
					sprintf(text2, "Player 1 venceu! %d rebatidas. Esc para sair", player.currentDefenses);
					al_draw_text(size_32, al_map_rgb(128, 200, 30), 200, 300, 0, text2);					
					al_flip_display();
					saveScore(player);
					ballDx = 0;
					ballDy = 0;
				}
			}
			al_draw_bitmap(barOne, 10, barOneY, 0);
			al_draw_bitmap(barTwo, screenWidth-30, barTwoY, 0);

			al_draw_bitmap(ball, ballX, ballY, 0);	

			al_flip_display();
		}
	}

	al_destroy_bitmap(barOne);
	al_destroy_bitmap(barTwo);
	al_destroy_bitmap(ball);
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(eventQueue);

	return 0;
}
