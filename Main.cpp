//============================================================================
// Name        : F_Proj_First_try.cpp
// Author      : navid
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include "Genio.h"
#include <iostream>
#include  <stdlib.h>
#include <time.h>
#include <math.h>
using namespace std;
int last_speed;
int speed_adder = 0;
int speed_adder_riv = 0;
int high_score = 0;
int score = 0;
int scoret = 0;
TTF_Font* Sans;
#include <string>
#include <cstring>
Mix_Chunk *chick_die_sound = NULL;
Mix_Chunk *ping_die_sound = NULL;
Mix_Chunk *coin_get_sound = NULL;
Mix_Chunk *hop_chick_sound = NULL;
Mix_Chunk *eagle_sound = NULL;
Mix_Chunk *train_sound = NULL;
// Mix_PlayChannel( -1, try_again_sound, 0 )
//	try_again_sound = Mix_LoadWAV("tryagain.wav");
//	Mix_FreeChunk(try_again_sound);
SDL_Color black = { 0, 0, 0 };
SDL_Rect score_rect = { 0, 0, 40, 40 };
SDL_Rect high_score_rect = { 0, 50, 40, 40 };
SDL_Rect coin_rect = { 500, 0, 40, 40 };
G_Rect oghab_rect = { 0, 0, 300, 300 };
double t2, t3, t4, t5;
int speed_y = 1;
int bottom_lane_ind;
const int obj_num_in_lane = 10;
const int train_len = 12;
const int obj_road_num_in_lane = 21 * obj_num_in_lane;
const int car_speed = 3;
const int lane_in_page = 10;
bool on_board = false;
int startMain;
int count_loops;
int coin_gained;
G_Texture* rail_red_img;
G_Texture* park_img;
G_Texture* play_button_img;
G_Texture* street_img;
G_Texture* river_img;
G_Texture* rail_img;
G_Texture* tree_img;
G_Texture* main_char_img;
G_Texture* chick_char_img;
G_Texture* chick_left_img;
G_Texture* chick_right_img;
G_Texture* chick_top_img;
G_Texture* chick_back_img;
G_Texture* chick_dead_img;
G_Texture* ping_left_img;
G_Texture* ping_right_img;
G_Texture* ping_top_img;
G_Texture* ping_back_img;
G_Texture* ping_dead_img;
G_Texture* sock_char_img;
G_Texture* Green_Car_img;
G_Texture* board_img;
G_Texture* leaf_img;
G_Texture* Red_Car_img;
G_Texture* coin_img;
G_Texture* crossy_road_img;
G_Texture* pause_button_img;
G_Texture* oghab_img;
G_Texture* change_char_img;
G_Texture* num_1_img;
G_Texture* num_2_img;
int FPS = 100;
int delay = 1000 / FPS;
int startLoop, endLoop;
double fstartMain;
bool oghab_done = 0;
enum Type {
	TREE, CAR, BOARD, EMPTY, LEAF, TRAIN
};
struct object {
	Type type;
	bool is_null; // = false;
	G_Rect pos;
	G_Texture* texture;
	G_Texture* init_texture;
	int speed;
	bool is_coin = false;
	bool is_init = false;
	bool is_first_train = false;

};
struct character {
	int i;
	int k;
	Type type;
	bool is_null; // = false;
	G_Rect pos;
	G_Texture* texture;
	int speed;

};
character asghar;
enum surface {
	PARK, STREET, RIVER, RAIL
};
enum riv {
	MOVING, STABLE
};

struct lane {
	G_Rect pos;
	object obj[obj_num_in_lane]; // = new object[obj_num_in_lane];
	object obj_road[obj_road_num_in_lane];
	G_Texture* texture;
	surface surf;
	bool left_to_right;
	riv river_obj;

};
lane lanes[lane_in_page + 1];
lane empty_lane;

void lane_destroyer(lane d) {
	delete d.obj;
}
G_Rect windowPos;
void rect_init(G_Rect& g, int x, int y, int w, int h) {
	g.x = x;
	g.y = y;
	g.w = w;
	g.h = h;

}
void destroy() {
	//Free the sound effects
	//Mix_FreeChunk(scratch);
	Mix_FreeChunk(eagle_sound);
	Mix_FreeChunk(train_sound);
	Mix_FreeChunk(hop_chick_sound);
	Mix_FreeChunk(chick_die_sound);
	Mix_FreeChunk(coin_get_sound);
	//Free the music
	G_DestroyTexture(park_img);
	G_DestroyTexture(street_img);
	G_DestroyTexture(river_img);
	G_DestroyTexture(tree_img);
	G_DestroyTexture(chick_char_img);
	G_DestroyTexture(main_char_img);
	G_DestroyTexture(sock_char_img);
	G_DestroyTexture(Green_Car_img);
	G_DestroyTexture(board_img);
	G_DestroyTexture(leaf_img);
	G_DestroyTexture(Red_Car_img);
	G_DestroyTexture(rail_img);
	G_DestroyTexture(coin_img);
	G_DestroyTexture(crossy_road_img);
	G_DestroyTexture(play_button_img);
	G_DestroyTexture(pause_button_img);
	G_DestroyTexture(oghab_img);

	G_QuitSDL();

}
void load() {
	train_sound = Mix_LoadWAV("./assets/train_sound.wav");
	eagle_sound = Mix_LoadWAV("./assets/eagle.wav");
	hop_chick_sound = Mix_LoadWAV("./assets/hop_chick.wav");
	chick_die_sound = Mix_LoadWAV("./assets/chicken_die.wav");
	ping_die_sound = Mix_LoadWAV("./assets/ping_die.wav");
	coin_get_sound = Mix_LoadWAV("./assets/coin_get.wav");
	Sans = TTF_OpenFont("./assets/arial.ttf", 24);
	num_1_img = G_LoadImage("./assets/num_1.png");
	num_2_img = G_LoadImage("./assets/num_2.png");
	park_img = G_LoadImage("./assets/park.png");
	change_char_img = G_LoadImage("./assets/change_char.png",255,255,255);
	street_img = G_LoadImage("./assets/street.png");
	river_img = G_LoadImage("./assets/river.png");
	tree_img = G_LoadImage("./assets/tree2.png", 255, 255, 255);
	chick_left_img = G_LoadImage("./assets/chick_left.png", 195, 195, 195);
	chick_right_img = G_LoadImage("./assets/chick_right.png", 195, 195, 195);
	chick_top_img = G_LoadImage("./assets/chick_top.png", 195, 195, 195);
	chick_back_img = G_LoadImage("./assets/chick_back.png", 195, 195, 195);
	chick_dead_img = G_LoadImage("./assets/chick_dead.png", 195, 195, 195);
	ping_left_img = G_LoadImage("./assets/ping_left.png", 195, 195, 195);
	ping_right_img = G_LoadImage("./assets/ping_right.png", 195, 195, 195);
	ping_top_img = G_LoadImage("./assets/ping_top.png", 195, 195, 195);
	ping_back_img = G_LoadImage("./assets/ping_back.png", 195, 195, 195);
	ping_dead_img = G_LoadImage("./assets/ping_die.png", 255, 255, 255);
	main_char_img = chick_top_img;
	sock_char_img = G_LoadImage("./assets/yaru.jpg");
	Green_Car_img = G_LoadImage("./assets/Green_Car.png");
	board_img = G_LoadImage("./assets/board.png");
	leaf_img = G_LoadImage("./assets/leaf.jpg");
	Red_Car_img = G_LoadImage("./assets/Red_Car.png");
	rail_img = G_LoadImage("./assets/rail.png");
	rail_red_img = G_LoadImage("./assets/rail_red.png");
	coin_img = G_LoadImage("./assets/coin.png");
	crossy_road_img = G_LoadImage("./assets/crossy_rload.jpg");
	play_button_img = G_LoadImage("./assets/play_button.png");
	pause_button_img = G_LoadImage("./assets/pause_button.jpg",255,255,255);
	oghab_img = G_LoadImage("./assets/eagle.png");

}
enum game_state {
	PLAY, EXITE, LOST, START_MENU, SELECT_CHAR, PAUSE, BARZAKH
};
enum char_name {
	CHICK, ALT
};
char_name charachter_name = CHICK;
int mouseX, mouseY;
void rail_speeder_all();
void oghab_move();
void lost();
void pause();
void draw_resume();
void select_char();
void coin_eat_check();
void car_speeder_all();
void riv_speeder_all();
bool timeer_rail(int speed);
bool timeer_car(int speed);
bool timeer_riv(int speed);
void char_board_opt();
bool is_dead(character c);
void car_speeder_lane(int i);
void go_down();
void go_right();
void go_up();
void go_left();
void obj_speed_optimizer(int i);
game_state state = START_MENU;
void object_initer(int i);
void imaizer(int i);
void speeder();
void make_lane(int i);
bool gone_out(G_Rect g);
void draw();
void initialize();
void play();
void start_menu();
void destroy();
void barzakh();
int main(int argc, char* args[]) {
	startMain = G_GetTicks();
	fstartMain = G_GetTicks();
	srand(time(NULL));
	G_InitSDL();
	rect_init(windowPos, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800,
			800);
	coin_rect.x = windowPos.w - 100;

	G_CreateWindow("Crossy Road", windowPos, 255, 255, 255);

	load();
	initialize();
	while (state != EXITE) {
		startLoop = G_GetTicks();

		G_Update();

		switch (state) {
		case BARZAKH:
			barzakh();
			break;
		case LOST:
			lost();
			break;
		case PAUSE:
			pause();
			break;
		case PLAY:
			play();
			break;
		case START_MENU:
			start_menu();
			break;
		case SELECT_CHAR:
			select_char();
			break;

		}

	}
	cout << endl << coin_gained;
	destroy();
	return 0;
}
void barzakh() {
	draw();
	oghab_move();
	G_Draw(oghab_img, &oghab_rect, false);			//oghab draw
	//oghab gone = true
	//if oghab_done
	if (oghab_done) {
		Mix_PlayChannel(-1, eagle_sound, 0);
		state = LOST;
	} // badan bayad begim oghab biad

}
void lost() {

	score = 0;
	scoret = 0;
	G_Rect play_button_rect = { 60, 400, 60, 60 };
	draw_resume();
	G_Draw(play_button_img, &play_button_rect, false);
	switch (G_Event()) {
	case G_QUIT:
		state = EXITE;
		break;
	case G_MOUSEMOTION:
		mouseX = G_motion.x;
		mouseY = G_motion.y;
		break;
	case G_MOUSEBUTTONDOWN:
	case G_BUTTON_LEFT:
		if ((mouseX >= play_button_rect.x)
				&& (mouseX < play_button_rect.x + play_button_rect.w)
				&& (mouseY > play_button_rect.y)
				&& (mouseY < play_button_rect.y + play_button_rect.h)) {
			initialize();
			state = START_MENU;
		}
		break;
		break;
	}

}
void select_char() {
	G_Rect chick_rect = { 30, 50, 200, 200 };
	G_Rect sock_rect = { 30, 400, 200, 200 };
	G_Draw(chick_top_img, &chick_rect, false);
	G_Draw(ping_top_img, &sock_rect, false);
	switch (G_Event()) {
	case G_QUIT:
		state = EXITE;
		break;
	case G_MOUSEMOTION:
		mouseX = G_motion.x;
		mouseY = G_motion.y;
		break;
	case G_MOUSEBUTTONDOWN:
	case G_BUTTON_LEFT:
		if ((mouseX >= chick_rect.x) && (mouseX < chick_rect.x + chick_rect.w)
				&& (mouseY > chick_rect.y)
				&& (mouseY < chick_rect.y + chick_rect.h)) {
			main_char_img = chick_top_img;
			asghar.texture = chick_top_img;
			charachter_name = CHICK;
			state = START_MENU;
		}
		if ((mouseX >= sock_rect.x) && (mouseX < sock_rect.x + sock_rect.w)
				&& (mouseY > sock_rect.y)
				&& (mouseY < sock_rect.y + sock_rect.h)) {
			main_char_img = ping_top_img;
			asghar.texture = ping_top_img;
			state = START_MENU;
			charachter_name = ALT;
		}
		break;
		break;
	}

}
void start_menu_draw() {

	G_Rect crossy_road_rect = { 30, 300, 500, 300 };
	G_Rect change_char_rect = { 10, 600, 80, 80 };
	G_Draw(crossy_road_img, &crossy_road_rect, false);
	G_Draw(change_char_img, &change_char_rect, false);
	switch (G_Event()) {
	case G_QUIT:
		state = EXITE;
		break;
	case G_MOUSEMOTION:
		mouseX = G_motion.x;
		mouseY = G_motion.y;
		break;
	case G_MOUSEBUTTONDOWN: {
		case G_BUTTON_LEFT:
		{
			if ((mouseX >= change_char_rect.x)
					&& (mouseX < change_char_rect.x + change_char_rect.w)
					&& (mouseY > change_char_rect.y)
					&& (mouseY < change_char_rect.y + change_char_rect.h)) {
				//main_char_img = chick_char_img;   //commented *** *** ***
				state = SELECT_CHAR;
				break;
			}

			state = PLAY;
			break;
		}

	}

	}
	// but down and the crossy road img and change char
}
void pause() {
	G_Rect rect_num={windowPos.w/2-50,windowPos.h/2-50,50,50};
	switch (G_Event()) {
	case G_QUIT:
		state = EXITE;
		break;

	case G_MOUSEBUTTONDOWN: {
		case G_BUTTON_LEFT:
		{
			state = PLAY;
			draw_resume();//added
			G_Draw(num_2_img, &rect_num, false);//added
			G_Update();//added
			G_Delay(1000);
			draw_resume();//added
			G_Draw(num_1_img, &rect_num, false);//added
			G_Update();//added
			G_Delay(1000);
			break;
		}
	}
	}

	draw_resume();
}
void start_menu() {
	endLoop = G_GetTicks() - startLoop;
	if (endLoop < delay) {
		G_Delay(delay - endLoop);
	}
	int end = G_GetTicks();
	count_loops = (end - startMain) / delay;
	speed_y = 0;
	draw();
	start_menu_draw();

}
void play() {
	G_Rect pause_rect = { 10, 600, 80, 80 };
	switch (G_Event()) {
	case G_QUIT:
		state = EXITE;
		break;
	case G_KEYUP:
		switch (G_Keyboard) {
		case GK_UP:
			go_up();
			break;
		case GK_LEFT:
			go_left();
			break;
		case GK_RIGHT:
			go_right();
			break;
		case GK_DOWN:
			go_down();
			break;

			////default break eraseeeeeeeeeeeeeeed; :)
		}
		break;
	case G_MOUSEMOTION:
		mouseX = G_motion.x;
		mouseY = G_motion.y;
		break;
	case G_MOUSEBUTTONDOWN: {
		case G_BUTTON_LEFT:
		{
			if ((mouseX >= pause_rect.x)
					&& (mouseX < pause_rect.x + pause_rect.w)
					&& (mouseY > pause_rect.y)
					&& (mouseY < pause_rect.y + pause_rect.h)) {
				state = PAUSE;
				break;
			}

			break;

		}
	}

		break;
	}

	endLoop = G_GetTicks() - startLoop;
	if (endLoop < delay) {
		G_Delay(delay - endLoop);
	}
	int end = G_GetTicks();
	count_loops = (end - startMain) / delay;
	draw();

}
void initialize() {
	oghab_done = 0;
	oghab_rect.y = 0;
	int ww = windowPos.w / obj_num_in_lane;
	asghar.i = 2;
	asghar.k = 5;

	asghar.texture = main_char_img;
	int hh = windowPos.h / lane_in_page;
	int w = windowPos.w;
	for (int i = 0; i < lane_in_page; ++i) {
		lanes[i].pos= {0,hh*i,w,hh+4}; // 4 is added bcs of the white pblm
		//lanes[i].texture=lane_img;

	}
	for (int i = 0; i < lane_in_page + 1; ++i)
		for (int k = 0; k < obj_num_in_lane; ++k)
			lanes[i].obj[k].type = EMPTY;

	lanes[9].surf = PARK;
	lanes[8].surf = PARK;
	lanes[7].surf = PARK;
	lanes[6].surf = PARK;
	lanes[5].surf = PARK;
	lanes[4].surf = PARK;
	lanes[3].surf = PARK;
	lanes[2].surf = PARK;
	lanes[1].surf = PARK;
	lanes[0].surf = PARK;
	lanes[10].surf = PARK;
	lanes[lane_in_page].pos= {0,-6000,w,hh+4}; // 4 is added bcs of the white pblm
	for (int i = 0; i < lane_in_page + 1; ++i)
		for (int k = 0; k < obj_num_in_lane; ++k)
			lanes[i].obj[k].pos= {k*ww,lanes[i].pos.y,ww,lanes[i].pos.h};
	for (int i = 0; i < lane_in_page + 1; ++i)
		imaizer(i);
//	lanes[lane_in_page].texture = lane_img2;

}
void draw_resume() {
	int hh = windowPos.h / lane_in_page;
	for (int i = 0; i < lane_in_page + 1; ++i) {
		G_Draw(lanes[i].texture, &lanes[i].pos, false);
		switch (lanes[i].surf) {
		case PARK: {

			for (int k = 0; k < obj_num_in_lane; ++k) {
				if (lanes[i].obj[k].type != EMPTY)
					G_Draw(lanes[i].obj[k].texture, &lanes[i].obj[k].pos,
							false);
				if (lanes[i].obj[k].is_coin) {
					G_Draw(coin_img, &lanes[i].obj[k].pos, false);
				}
			}

			break;
		}
		case STREET: {
			//if (!(count_loops % 5))
			//car_speeder_lane(i);
			for (int k = 0; k < obj_road_num_in_lane; ++k) {
				if (lanes[i].obj_road[k].is_coin) {
					G_Draw(coin_img, &lanes[i].obj_road[k].pos, false);
				}

				if (lanes[i].obj_road[k].type != EMPTY)
					G_Draw(lanes[i].obj_road[k].texture,
							&lanes[i].obj_road[k].pos, false);
			}

			break;
		}
		case RAIL: {
			for (int k = 0; k < obj_road_num_in_lane; ++k) {

				if (lanes[i].obj_road[k].type != EMPTY)
					G_Draw(lanes[i].obj_road[k].texture,
							&lanes[i].obj_road[k].pos, false);
			}

			break;

		}
		case RIVER: {
			//if (!(count_loops % 10))
			//if (timeer())
			//car_speeder_lane(i);
			for (int k = 0; k < obj_road_num_in_lane; ++k) {

				if (lanes[i].obj_road[k].type != EMPTY)
					G_Draw(lanes[i].obj_road[k].texture,
							&lanes[i].obj_road[k].pos, false);
			}
			for (int k = 0; k < obj_num_in_lane; ++k) {
				if (lanes[i].obj[k].type != EMPTY)
					G_Draw(lanes[i].obj[k].texture, &lanes[i].obj[k].pos,
							false);
			}

			break;
		}

		}

	}
	G_Draw(asghar.texture, &lanes[asghar.i].obj[asghar.k].pos, false);

}
void draw() {
	char score_str[20];
	char coin_str[20];
	char high_score_str[20];
	sprintf(score_str, "%d", score);
	sprintf(coin_str, "%d", coin_gained);
	sprintf(high_score_str, "%d", high_score);
	SDL_Surface* score_message = TTF_RenderText_Solid(Sans, score_str, black);
	SDL_Surface* coin_message = TTF_RenderText_Solid(Sans, coin_str, black);
	SDL_Surface* high_score_message = TTF_RenderText_Solid(Sans, high_score_str,
			black);
	SDL_Texture* score_texture = SDL_CreateTextureFromSurface(renderer,
			score_message);
	SDL_Texture* coin_texture = SDL_CreateTextureFromSurface(renderer,
			coin_message);
	SDL_Texture* high_score_texture = SDL_CreateTextureFromSurface(renderer,
			high_score_message);
	SDL_RenderCopy(renderer, score_texture, NULL, &score_rect);
	SDL_RenderCopy(renderer, coin_texture, NULL, &coin_rect);
	SDL_RenderCopy(renderer, high_score_texture, NULL, &high_score_rect);

	int hh = windowPos.h / lane_in_page;
	if (state == PLAY) {
		last_speed = speed_y;
		speed_y = ((windowPos.h - lanes[asghar.i].pos.y) / (4 * hh)) + 1;
		//can be deleted ****
		speed_y = 3;
		if (((windowPos.h - lanes[asghar.i].pos.y) / (hh)) < 7)
			speed_y = 2;
		if (((windowPos.h - lanes[asghar.i].pos.y) / (hh)) < 5)
			speed_y = 1;
	}
//can be deleted *******
	//if ((speed_y) > 2)
	cout << speed_y << endl;
	int c = -1;
	speeder();

	for (int i = 0; i < lane_in_page + 1; ++i) {

		if (is_dead(asghar)) {
			switch (charachter_name) {
			case CHICK:
				Mix_PlayChannel(-1, chick_die_sound, 0);
				break;
			case ALT:
				Mix_PlayChannel(-1, ping_die_sound, 0);
				break;

			}
			state = LOST;
			return;
			cout << "salaaam";
		}
		obj_speed_optimizer(i);
		//G_Rect temp_lane=lanes[i].pos;
		//temp_lane.y-=2;
		//temp_lane.h+=4;
		G_Draw(lanes[i].texture, &lanes[i].pos, false);
		switch (lanes[i].surf) {
		case PARK: {

			for (int k = 0; k < obj_num_in_lane; ++k) {
				if (lanes[i].obj[k].type != EMPTY)
					G_Draw(lanes[i].obj[k].texture, &lanes[i].obj[k].pos,
							false);
				if (lanes[i].obj[k].is_coin) {
					G_Draw(coin_img, &lanes[i].obj[k].pos, false);
				}
			}

			break;
		}
		case STREET: {
			//if (!(count_loops % 5))
			//car_speeder_lane(i);
			for (int k = 0; k < obj_road_num_in_lane; ++k) {
				if (lanes[i].obj_road[k].is_coin) {
					G_Draw(coin_img, &lanes[i].obj_road[k].pos, false);
				}
				G_Rect temp = lanes[i].obj_road[k].pos;
				if (lanes[i].left_to_right)
					temp.x += speed_adder - lanes[i].obj_road[k].pos.w/2;
				else
					temp.x -= speed_adder - lanes[i].obj_road[k].pos.w/2;
				//cout << endl << speed_adder;
				if (lanes[i].obj_road[k].type != EMPTY)
					G_Draw(lanes[i].obj_road[k].texture, &temp, false);
			}

			break;
		}
		case RAIL: {
			for (int k = 0; k < obj_road_num_in_lane; ++k) {
				///
				int t = ((obj_road_num_in_lane / obj_num_in_lane) / 2) + 1;
				t *= obj_num_in_lane;
				if (((!lanes[i].left_to_right))
						&& (lanes[i].obj_road[t + 10].is_first_train)) {
					Mix_PlayChannel(-1, train_sound, 0);
					lanes[i].texture = rail_red_img;
				}
				if (((!lanes[i].left_to_right))
						&& (lanes[i].obj_road[t - obj_num_in_lane].is_first_train))
					lanes[i].texture = rail_img;
				t -= obj_num_in_lane;
				if (((lanes[i].left_to_right))
						&& (lanes[i].obj_road[t - 10].is_first_train)) {
					Mix_PlayChannel(-1, train_sound, 0);
					lanes[i].texture = rail_red_img;
				}
				if (((lanes[i].left_to_right))
						&& (lanes[i].obj_road[t + obj_num_in_lane].is_first_train))
					lanes[i].texture = rail_img;
				if (lanes[i].obj_road[k].type != EMPTY)
					G_Draw(lanes[i].obj_road[k].texture,
							&lanes[i].obj_road[k].pos, false);
			}

			break;

		}
		case RIVER: {
			//if (!(count_loops % 10))
			//if (timeer())
			//car_speeder_lane(i);
			for (int k = 0; k < obj_road_num_in_lane; ++k) {
				G_Rect temp = lanes[i].obj_road[k].pos;
				if (lanes[i].left_to_right)
					temp.x += speed_adder_riv;
				else
					temp.x -= speed_adder_riv;
				if (lanes[i].obj_road[k].type != EMPTY)
					G_Draw(lanes[i].obj_road[k].texture,
							&lanes[i].obj_road[k].pos, false);
			}
			for (int k = 0; k < obj_num_in_lane; ++k) {
				if (lanes[i].obj[k].type != EMPTY)
					G_Draw(lanes[i].obj[k].texture, &lanes[i].obj[k].pos,
							false);
			}

			break;
		}

		}
	}
	if (timeer_car(170)) {
		speed_adder = 0;

		car_speeder_all();

	}
	if (timeer_rail(30)) {

		rail_speeder_all();

	}

	if (timeer_riv(260)) {
		speed_adder_riv = 0;
		riv_speeder_all();
	}

	G_Draw(asghar.texture, &lanes[asghar.i].obj[asghar.k].pos, false);
	int bott_ind;
	for (int i = 0; i < lane_in_page + 1; ++i) {
		//if (gone_out(lanes[i].pos)){
		c = i + 1;
		bott_ind = i;
		//speed_y=abs(bott_ind-asghar.i)/3 +1;
		//}
		if (c != -1) {
			if (c == 11)
				c = 0;
			//make new
			if ((lanes[c].pos.y < -600) || (lanes[c].pos.y > windowPos.h)) {
				make_lane(c);
			}

		}

	}
	coin_eat_check();
	G_Rect pause_rect = { 10, 600, 80, 80 };
	G_Draw(pause_button_img, &pause_rect, false);
	SDL_RenderCopy(renderer, score_texture, NULL, &score_rect);
	SDL_RenderCopy(renderer, coin_texture, NULL, &coin_rect);
	SDL_RenderCopy(renderer, high_score_texture, NULL, &high_score_rect);
	SDL_FreeSurface(high_score_message);
	SDL_FreeSurface(score_message);
	SDL_FreeSurface(coin_message);
	SDL_DestroyTexture(score_texture);
	SDL_DestroyTexture(coin_texture);
	SDL_DestroyTexture(high_score_texture);
	if (((lanes[asghar.i].pos.y + 2 * lanes[asghar.i].pos.h) > windowPos.h)) {
		oghab_rect.x = lanes[asghar.i].obj[asghar.k].pos.x - oghab_rect.w / 2;
		state = BARZAKH;
	}

}
bool gone_out(G_Rect g) {
	if ((g.y + g.h) >= (windowPos.h))
		return true;
	return false;
}

void make_lane(int i) {
	int next_i = i + 1;
	if (next_i == 11)
		next_i = 0;

	for (int k = 0; k < obj_num_in_lane; ++k) {
		lanes[i].obj[k].type = EMPTY;
		lanes[i].obj[k].is_coin = false;

	}
	for (int k = 0; k < obj_road_num_in_lane; ++k) {
		lanes[i].obj_road[k].type = EMPTY;
		lanes[i].obj_road[k].is_coin = false;
		lanes[i].obj_road[k].is_first_train = false;

	}
	int hh = windowPos.h / lane_in_page;
	lanes[i].pos.y = -hh + last_speed - 1; ///maybe 2 is needed
	hh = lanes[next_i].pos.y - lanes[i].pos.y + last_speed + 1;
	//hh+=last_speed+2;
	lanes[i].pos.h=hh;
	//lanes[i].pos.y-=2;
	int rand1 = rand() % 3 + 1;
	int rand2;
	switch (rand1) {
	case 1:
		lanes[i].surf = PARK;
		break;
	case 2:
		lanes[i].surf = STREET;
		rand2 = rand() % 4 + 1;
		if (rand2 == 1)
			lanes[i].surf = RAIL;
		break;
	case 3:
		lanes[i].surf = RIVER;
		break;
	}
	imaizer(i);
	object_initer(i);

}
void speeder() {
//speed everything down
	for (int i = 0; i < lane_in_page + 1; ++i) {
		lanes[i].pos.y += speed_y;
	}

}
void imaizer(int i) {
	if (lanes[i].surf == PARK)
		lanes[i].texture = park_img;
	if (lanes[i].surf == STREET)
		lanes[i].texture = street_img;
	if (lanes[i].surf == RIVER)
		lanes[i].texture = river_img;
	if (lanes[i].surf == RAIL)
		lanes[i].texture = rail_img;

}
void object_initer(int i) {
// needs some work
	int last = i + 1;
	if (i == 10)
		last = 0;
	int ww = windowPos.w / obj_num_in_lane;
	for (int k = 0; k < obj_num_in_lane; ++k)
		lanes[i].obj[k].pos= {k*ww,lanes[i].pos.y,ww,lanes[i].pos.h};
	switch (lanes[i].surf) {
	case PARK:
		srand(time(NULL));
		for (int k = 0; k < obj_num_in_lane; ++k) {
			int rand1 = rand() % 10 + abs(5 - k);
			if ((lanes[last].surf == RIVER) && (lanes[last].river_obj == STABLE)
					&& (lanes[last].obj[k].type == LEAF)) {
				rand1 = 5; //this is for avoiding the weird tree after LEAF

			}
			if (rand1 > 9) {
				lanes[i].obj[k].type = TREE;
				lanes[i].obj[k].is_null = false;
				lanes[i].obj[k].speed = 0;
				lanes[i].obj[k].pos= {k*ww,lanes[i].pos.y,ww,lanes[i].pos.h};
				lanes[i].obj[k].texture = tree_img;
			}
			if (lanes[i].obj[k].type == EMPTY) {
				int rand_coin = rand() % 10 + 1;
				if (rand_coin < 2)
					lanes[i].obj[k].is_coin = true;
				;
			}

		}

		break;
	case STREET: {
		int t = (obj_road_num_in_lane / obj_num_in_lane) / 2;
		t *= obj_num_in_lane;
		srand(time(NULL));
		int rand1 = rand() % 2 + 1;
		int rand2;
		for (int k = 0; k < obj_road_num_in_lane; ++k)
			lanes[i].obj_road[k].pos= {k*ww-(10*windowPos.w),lanes[i].pos.y,ww,lanes[i].pos.h};
		switch (rand1) {
		case 1:

			lanes[i].left_to_right = true;
			for (int k = 0; k < obj_num_in_lane * 10; ++k) { //*** zarb shodan 2 bekhatere 5 tayi boodaneshe
				//srand(time(NULL));

				rand2 = rand() % 10 + 1;
				if ((k != 0) && (lanes[i].obj_road[k - 1].type == CAR))
					rand2 = 3;

				if (rand2 < 2) {
					lanes[i].obj_road[k].type = CAR;
					lanes[i].obj_road[k].is_null = false;
					lanes[i].obj_road[k].speed = car_speed;
					//lanes[i].obj_road[k].pos= {k*ww-(2*windowPos.w),lanes[i].pos.y,ww,lanes[i].pos.h};
					lanes[i].obj_road[k].texture = Green_Car_img;
				}
			}
			break;
		case 2:
			lanes[i].left_to_right = false;
			for (int k = obj_num_in_lane * 11; k < obj_num_in_lane * 21; ++k) { //*** zarb shodan 2 bekhatere 5 tayi boodaneshe
				//srand(time(NULL));

				rand2 = rand() % 10 + 1;
				if ((lanes[i].obj_road[k - 1].type == CAR))
					rand2 = 3; //this will not let 2 cars right after each other
				if (rand2 < 2) {
					lanes[i].obj_road[k].type = CAR;
					lanes[i].obj_road[k].is_null = false;
					lanes[i].obj_road[k].speed = (-1) * car_speed;
					//lanes[i].obj_road[k].pos= {k*ww-(2*windowPos.w),lanes[i].pos.y,ww,lanes[i].pos.h};
					lanes[i].obj_road[k].texture = Green_Car_img;
				}

			}
			break;
		}
		for (int k = obj_num_in_lane * 10; k < obj_num_in_lane * 11; ++k) {

			int rand_coin = rand() % 10 + 1;
			if (rand_coin < 2)
				lanes[i].obj_road[k].is_coin = true;
		}

	}
		///putt

		//manfi goxari kon akharesh
		break;
	case RAIL: {
		int t = (obj_road_num_in_lane / obj_num_in_lane) / 2;
		t *= obj_num_in_lane;
		int rand1 = rand() % 2 + 1;
		int train_start;
		for (int k = 0; k < obj_road_num_in_lane; ++k)
			lanes[i].obj_road[k].pos= {k*ww-(10*windowPos.w),lanes[i].pos.y,ww,lanes[i].pos.h};
		switch (rand1) {
		case 1:
			lanes[i].left_to_right = true;
			//for (int k = 0; k < obj_num_in_lane * 10; ++k) { //*** zarb shodan 2 bekhatere 5 tayi boodaneshe
			//srand(time(NULL));

			train_start = (rand() % (t - train_len - 10));			//////
			lanes[i].obj_road[train_start + train_len].is_first_train = true;
			for (int k = train_start; k < train_start + train_len; ++k) {
				lanes[i].obj_road[k].type = CAR;
				lanes[i].obj_road[k].is_null = false;
				lanes[i].obj_road[k].speed = car_speed;
				//lanes[i].obj_road[k].pos= {k*ww-(2*windowPos.w),lanes[i].pos.y,ww,lanes[i].pos.h};
				lanes[i].obj_road[k].texture = Red_Car_img;
			}
			//}
			break;
		case 2:
			lanes[i].left_to_right = false;
			train_start = 10 + (rand() % (t - train_len - 10));
			train_start += t + obj_num_in_lane;
			lanes[i].obj_road[train_start].is_first_train = true;
			for (int k = train_start; k < train_start + train_len; ++k) {
				lanes[i].obj_road[k].type = CAR;
				lanes[i].obj_road[k].is_null = false;
				lanes[i].obj_road[k].speed = car_speed;
				//lanes[i].obj_road[k].pos= {k*ww-(2*windowPos.w),lanes[i].pos.y,ww,lanes[i].pos.h};
				lanes[i].obj_road[k].texture = Red_Car_img;
			}
			break;
		}
		break;
	}
	case RIVER:
		srand(time(NULL));
		int rand0 = rand() % 4 + 1;
		if ((lanes[last].surf == RIVER) && (lanes[last].river_obj == STABLE))

			rand0 = 2; //this is for making sure not 2 leafs come right after each other

		if (rand0 < 3) { //jtdytfchgfhgchg      ***CHANGE WHEN STABLE MADE******
			lanes[i].river_obj = MOVING;
			int rand1 = rand() % 2 + 1;
			if ((lanes[last].surf == RIVER) && (lanes[last].river_obj == MOVING) //***
					&& (lanes[last].left_to_right))
				rand1 = 2;      //THESE LINE ARE FOR AVOIDING TWO BOARDS ONE WAY
			if ((lanes[last].surf == RIVER) && (lanes[last].river_obj == MOVING)
					&& (!lanes[last].left_to_right))                       //***
				rand1 = 1;
			int rand2;
			int wood_counter_in_row = 0;
			for (int k = 0; k < obj_road_num_in_lane; ++k)
				lanes[i].obj_road[k].pos= {k*ww-(10*windowPos.w),lanes[i].pos.y,ww,lanes[i].pos.h};
			switch (rand1) {
			case 1:
				lanes[i].left_to_right = true;
				wood_counter_in_row = 0;
				for (int k = 0; k < obj_num_in_lane * 10; ++k) { //*** zarb shodan 2 bekhatere 5 tayi boodaneshe
					//srand(time(NULL));
					rand2 = rand() % 7 + 1;
					if ((k == (obj_num_in_lane * 10) - 1)
							&& (wood_counter_in_row == 0))
						rand2 = 5;
					if (wood_counter_in_row > 3)
						rand2 = 5;
					if (wood_counter_in_row == 1)
						rand2 = 0;
					if (rand2 < 5) {
						wood_counter_in_row++;
						lanes[i].obj_road[k].type = BOARD;
						lanes[i].obj_road[k].is_null = false;
						lanes[i].obj_road[k].speed = car_speed;
						//lanes[i].obj_road[k].pos= {k*ww-(2*windowPos.w),lanes[i].pos.y,ww,lanes[i].pos.h};
						lanes[i].obj_road[k].texture = board_img;
					} else
						wood_counter_in_row = 0;
				}
				break;
			case 2:
				lanes[i].left_to_right = false;
				wood_counter_in_row = 0;
				for (int k = obj_num_in_lane * 11; k < obj_num_in_lane * 21;
						++k) { //*** zarb shodan 2 bekhatere 5 tayi boodaneshe
					//srand(time(NULL));

					rand2 = rand() % 7 + 1;
					if (wood_counter_in_row > 3)
						rand2 = 5;
					if (wood_counter_in_row == 1)
						rand2 = 0;
					if (rand2 < 5) {
						wood_counter_in_row++;
						lanes[i].obj_road[k].type = BOARD;
						lanes[i].obj_road[k].is_null = false;
						lanes[i].obj_road[k].speed = (-1) * car_speed;
						//lanes[i].obj_road[k].pos= {k*ww-(2*windowPos.w),lanes[i].pos.y,ww,lanes[i].pos.h};
						lanes[i].obj_road[k].texture = board_img;
					} else
						wood_counter_in_row = 0;

				}
				break;
			}

			//manfi goxari kon akharesh
			break;

		} else {
			static bool last_n_use_tree;
			lanes[i].river_obj = STABLE;
			srand(time(NULL));
			bool is_there_any_leaf = 0;
			while (!is_there_any_leaf) {
				for (int k = 0; k < obj_num_in_lane; ++k) {
					int rand1 = rand() % 10 + 1;
					/*if ((lanes[last].surf == RIVER)
					 && (lanes[last].obj[k].type == LEAF)) {
					 lanes[i].obj[k].type = LEAF;            //this was used for the leafs
					 lanes[i].obj[k].is_null = false;
					 lanes[i].obj[k].speed = 0;
					 lanes[i].obj[k].pos= {k*ww,lanes[i].pos.y,ww,lanes[i].pos.h};
					 lanes[i].obj[k].texture = leaf_img;
					 continue;

					 }*/
					if (last_n_use_tree) {
						rand1 = 0;
						last_n_use_tree = false;
					}
					if (rand1 < 6) {
						if (lanes[last].obj[k].type == TREE) {
							last_n_use_tree = true;

						} else {
							is_there_any_leaf = true;
							lanes[i].obj[k].type = LEAF;
							lanes[i].obj[k].is_null = false;
							lanes[i].obj[k].speed = 0;
							lanes[i].obj[k].pos= {k*ww,lanes[i].pos.y,ww,lanes[i].pos.h};
							lanes[i].obj[k].texture = leaf_img;
						}
					}

				}
			}

		}
		break;
	}
}

void obj_speed_optimizer(int i) {
//inja check if tree if road and ...
	switch (lanes[i].surf) {
	case PARK:
		for (int k = 0; k < obj_num_in_lane; ++k)
			lanes[i].obj[k].pos.y = lanes[i].pos.y;
		break;
	case STREET:
		for (int k = 0; k < obj_road_num_in_lane; ++k) {
			lanes[i].obj_road[k].pos.y = lanes[i].pos.y;
			lanes[i].obj[k].pos.y = lanes[i].pos.y;
		}
		break;
	case RIVER:
		for (int k = 0; k < obj_road_num_in_lane; ++k) {
			lanes[i].obj_road[k].pos.y = lanes[i].pos.y;
			lanes[i].obj[k].pos.y = lanes[i].pos.y;
		}
		break;
	case RAIL:
		for (int k = 0; k < obj_road_num_in_lane; ++k) {
			lanes[i].obj_road[k].pos.y = lanes[i].pos.y;
			lanes[i].obj[k].pos.y = lanes[i].pos.y;
		}
		break;

	}
}
void go_up() {
	switch (charachter_name) {
	case CHICK:
		asghar.texture = chick_top_img;
		break;
	case ALT:
		asghar.texture = ping_top_img;
		break;
	}
	scoret++;
	if (score < scoret)
		score++;
	if (score > high_score)
		high_score = score;
	int ii = (asghar.i) - 1;
	if (ii < 0)
		ii = 10;
	lane lane1 = lanes[ii];
	bool move = true;
	switch (lane1.surf) {
//case PARK:
	default:
		switch (lane1.obj[(asghar.k)].type) {
		case TREE:
			move = false;
			break;
		}
		if (move) {
			Mix_PlayChannel(-1, hop_chick_sound, 0);
			if (asghar.i > 0)
				asghar.i--;
			else
				asghar.i = 10;

		}
		break;
	}

}
void go_left() {
	switch (charachter_name) {
	case CHICK:
		asghar.texture = chick_left_img;
		break;
	case ALT:
		asghar.texture = ping_left_img;
		break;
	}
	lane lane1 = lanes[(asghar.i)];
	bool move = true;
	switch (lane1.surf) {
	case PARK:
	case STREET: {
		if (asghar.k == 0)
			move = false;

		break;
	}
//case PARK:

	}
	switch (lane1.obj[(asghar.k) - 1].type) {
	case TREE:
		move = false;
		break;
	}
	if (move) {
		Mix_PlayChannel(-1, hop_chick_sound, 0);
		asghar.k--;
	}

}
void go_down() {
	switch (charachter_name) {
	case CHICK:
		asghar.texture = chick_back_img;
		break;
	case ALT:
		asghar.texture = ping_back_img;
		break;

	}
	scoret--;
	int ii = (asghar.i) + 1;
	if (ii > 10)
		ii = 0;
	lane lane1 = lanes[ii];
	bool move = true;
	switch (lane1.surf) {
//case PARK:
	default:
		switch (lane1.obj[(asghar.k)].type) {
		case TREE:
			move = false;
			break;
		}
		if (move) {
			Mix_PlayChannel(-1, hop_chick_sound, 0);
			if (asghar.i < 10)
				asghar.i++;
			else
				asghar.i = 0;

		}
		break;
	}

}
void go_right() {
	switch (charachter_name) {
	case CHICK:
		asghar.texture = chick_right_img;
		break;
	case ALT:
		asghar.texture = ping_right_img;
		break;
	}
	lane lane1 = lanes[(asghar.i)];
	bool move = true;
	switch (lane1.surf) {
	case PARK:
	case STREET: {
		if (asghar.k == 9)
			move = false;

		break;
	}
//case PARK:

	}
	switch (lane1.obj[(asghar.k) + 1].type) {
	case TREE:
		move = false;
		break;
	}
	if (move) {
		Mix_PlayChannel(-1, hop_chick_sound, 0);
		asghar.k++;
	}

}
void car_speeder_lane(int i) {
	if (lanes[i].left_to_right) {

		for (int k = obj_road_num_in_lane - 1; k > 0; --k) {

			lanes[i].obj_road[k].texture = lanes[i].obj_road[k - 1].texture; //fasfasfa
			lanes[i].obj_road[k].type = lanes[i].obj_road[k - 1].type; //fasfasfa
			lanes[i].obj_road[k].is_first_train =
					lanes[i].obj_road[k - 1].is_first_train;
		}
		lanes[i].obj_road[0].texture = NULL; //fasfasfa
		lanes[i].obj_road[0].type = EMPTY; //fasfasfa

	}

	else {

		for (int k = 0; k < obj_road_num_in_lane - 1; ++k) {

			lanes[i].obj_road[k].texture = lanes[i].obj_road[k + 1].texture; //fasfasfa
			lanes[i].obj_road[k].type = lanes[i].obj_road[k + 1].type; //fasfasfa
			lanes[i].obj_road[k].is_first_train =
					lanes[i].obj_road[k + 1].is_first_train; //fasfasfa
		}
		lanes[i].obj_road[obj_road_num_in_lane - 1].texture = NULL; //fasfasfa
		lanes[i].obj_road[obj_road_num_in_lane - 1].type = EMPTY; //fasfasfa
	}
	if (on_board && (asghar.i == i)) {
		if (lanes[asghar.i].left_to_right)
			asghar.k++;

		if (!(lanes[asghar.i].left_to_right))
			asghar.k--;

	}

}
bool is_dead(character c) {

	on_board = false;
	int t = (obj_road_num_in_lane / obj_num_in_lane) / 2;
	t *= obj_num_in_lane;
	if ((lanes[c.i].surf == STREET)) {
		if (lanes[c.i].obj_road[c.k + t].type == CAR) {
			cout << "asfsffa";
			switch (charachter_name) {
			case CHICK:
				asghar.texture = chick_dead_img;
				break;
			case ALT:
				asghar.texture = ping_dead_img;
				break;
			}
			return true;

		}

	}
	if ((lanes[c.i].surf == RAIL)) {
		if (lanes[c.i].obj_road[c.k + t].type == CAR) {
			switch (charachter_name) {
			case CHICK:
				asghar.texture = chick_dead_img;
				break;
			case ALT:
				asghar.texture = ping_dead_img;
				break;
			}
			cout << "asfsffa";
			return true;

		}

	}
	if ((lanes[c.i].surf == RIVER)) {
		if ((lanes[c.i].river_obj == MOVING)
				&& (lanes[c.i].obj_road[c.k + t].type == EMPTY)) {
			return true;
		}
		if (((lanes[c.i].river_obj == STABLE)
				&& (lanes[c.i].obj[c.k].type != LEAF)))
			return true;
		if (lanes[c.i].obj_road[c.k + t].type == BOARD)
			on_board = true;
	}
	return false;

}
void char_board_opt() {
	if (lanes[asghar.i].surf == RIVER) {
		if ((lanes[asghar.i].river_obj == MOVING)
				&& (lanes[asghar.i].obj_road[asghar.k].type == BOARD)) {
			if (lanes[asghar.i].left_to_right)
				asghar.k += 1;
			else
				asghar.k -= 1;
		}
	}

}
bool timeer_car(int speed) {
	t2 = G_GetTicks();
	int ww = windowPos.w / obj_num_in_lane;
	if ((abs(t2 - t3)) < speed)
		speed_adder = abs(t2 - t3) * ww / speed;
	;
	if ((abs(t2 - t3)) >= speed) {
		t3 = G_GetTicks();
		return true;
	}
	/*double dd;
	 dd = (t2 - fstartMain);
	 cout << dd << endl; //fmod(dd, 5.123) << endl;
	 if (((fmod(dd, 5.1)) > 0.5) && (fmod(dd, 5.1) < 1.0))
	 return true;*/
	return false;

}
bool timeer_riv(int speed) {

	t2 = G_GetTicks();
	int ww = windowPos.w / obj_num_in_lane;
	if ((abs(t2 - t4)) < speed)
		speed_adder_riv = abs(t2 - t4) * ww / speed;
	;
	if ((abs(t2 - t4)) >= speed) {
		t4 = G_GetTicks();
		return true;
	}
	/*double dd;
	 dd = (t2 - fstartMain);
	 cout << dd << endl; //fmod(dd, 5.123) << endl;
	 if (((fmod(dd, 5.1)) > 0.5) && (fmod(dd, 5.1) < 1.0))
	 return true;*/
	return false;

}
bool timeer_rail(int speed) {

	t2 = G_GetTicks();
	int ww = windowPos.w / obj_num_in_lane;
	;
	if ((abs(t2 - t5)) >= speed) {
		t5 = G_GetTicks();
		return true;
	}
	/*double dd;
	 dd = (t2 - fstartMain);
	 cout << dd << endl; //fmod(dd, 5.123) << endl;
	 if (((fmod(dd, 5.1)) > 0.5) && (fmod(dd, 5.1) < 1.0))
	 return true;*/
	return false;

}
void riv_speeder_all() {
	for (int i = 0; i < lane_in_page + 1; ++i) {
		if ((lanes[i].surf == RIVER) && (lanes[i].river_obj == MOVING)) {
			if (lanes[i].left_to_right) {

				for (int k = obj_road_num_in_lane - 1; k > 0; --k) {

					lanes[i].obj_road[k].texture =
							lanes[i].obj_road[k - 1].texture; //fasfasfa
					lanes[i].obj_road[k].type = lanes[i].obj_road[k - 1].type; //fasfasfa
				}
				lanes[i].obj_road[0].texture = NULL; //fasfasfa
				lanes[i].obj_road[0].type = EMPTY; //fasfasfa

			}

			else {

				for (int k = 0; k < obj_road_num_in_lane - 1; ++k) {

					lanes[i].obj_road[k].texture =
							lanes[i].obj_road[k + 1].texture; //fasfasfa
					lanes[i].obj_road[k].type = lanes[i].obj_road[k + 1].type; //fasfasfa
				}
				lanes[i].obj_road[obj_road_num_in_lane - 1].texture = NULL; //fasfasfa
				lanes[i].obj_road[obj_road_num_in_lane - 1].type = EMPTY; //fasfasfa
			}
			if (on_board && (asghar.i == i)) {
				if (lanes[asghar.i].left_to_right)
					asghar.k++;
				if (!(lanes[asghar.i].left_to_right))
					asghar.k--;

			}
			if (((asghar.k) < 0) || (asghar.k > 9))
				state = LOST;

		}
	}

}
void car_speeder_all() {
	for (int i = 0; i < lane_in_page + 1; ++i) {
		if ((lanes[i].surf == STREET)) {
			if (lanes[i].left_to_right) {

				for (int k = obj_road_num_in_lane - 1; k > 0; --k) {

					lanes[i].obj_road[k].texture =
							lanes[i].obj_road[k - 1].texture; //fasfasfa
					lanes[i].obj_road[k].type = lanes[i].obj_road[k - 1].type; //fasfasfa
					lanes[i].obj_road[k].is_first_train = lanes[i].obj_road[k
							- 1].is_first_train;
				}
				lanes[i].obj_road[0].texture = NULL; //fasfasfa
				lanes[i].obj_road[0].type = EMPTY; //fasfasfa

			}

			else {

				for (int k = 0; k < obj_road_num_in_lane - 1; ++k) {

					lanes[i].obj_road[k].texture =
							lanes[i].obj_road[k + 1].texture; //fasfasfa
					lanes[i].obj_road[k].type = lanes[i].obj_road[k + 1].type; //fasfasfa
					lanes[i].obj_road[k].is_first_train = lanes[i].obj_road[k
							+ 1].is_first_train;
				}
				lanes[i].obj_road[obj_road_num_in_lane - 1].texture = NULL; //fasfasfa
				lanes[i].obj_road[obj_road_num_in_lane - 1].type = EMPTY; //fasfasfa
			}
		}
	}

}
void rail_speeder_all() {
	for (int i = 0; i < lane_in_page + 1; ++i) {
		if ((lanes[i].surf == RAIL)) {
			if (lanes[i].left_to_right) {

				for (int k = obj_road_num_in_lane - 1; k > 0; --k) {

					lanes[i].obj_road[k].texture =
							lanes[i].obj_road[k - 1].texture; //fasfasfa
					lanes[i].obj_road[k].type = lanes[i].obj_road[k - 1].type; //fasfasfa
					lanes[i].obj_road[k].is_first_train = lanes[i].obj_road[k
							- 1].is_first_train;
				}
				lanes[i].obj_road[0].texture = NULL; //fasfasfa
				lanes[i].obj_road[0].type = EMPTY; //fasfasfa

			}

			else {

				for (int k = 0; k < obj_road_num_in_lane - 1; ++k) {

					lanes[i].obj_road[k].texture =
							lanes[i].obj_road[k + 1].texture; //fasfasfa
					lanes[i].obj_road[k].type = lanes[i].obj_road[k + 1].type; //fasfasfa
					lanes[i].obj_road[k].is_first_train = lanes[i].obj_road[k
							+ 1].is_first_train;
				}
				lanes[i].obj_road[obj_road_num_in_lane - 1].texture = NULL; //fasfasfa
				lanes[i].obj_road[obj_road_num_in_lane - 1].type = EMPTY; //fasfasfa
			}
		}
	}

}

void coin_eat_check() {
	int t = (obj_road_num_in_lane / obj_num_in_lane) / 2;
	t *= obj_num_in_lane;
	switch (lanes[asghar.i].surf) {
	case PARK:
		if (lanes[asghar.i].obj[asghar.k].is_coin) {
			lanes[asghar.i].obj[asghar.k].is_coin = false;
			coin_gained++;
			Mix_PlayChannel(-1, coin_get_sound, 0);
		}
		break;
	case STREET: {
		if (lanes[asghar.i].obj_road[asghar.k + t].is_coin) {
			lanes[asghar.i].obj_road[asghar.k + t].is_coin = false;
			coin_gained++;
			Mix_PlayChannel(-1, coin_get_sound, 0);
		}
		break;
	}
	}
}
void oghab_move() {
	if (oghab_rect.y > windowPos.h)
		oghab_done = true;
	oghab_rect.y += 10;

}


