#pragma once
#include "Heads.h"

const double fps = 60;

enum KEYS {UP, RIGHT, LEFT, DOWN, S};
int direction = DOWN;
bool start = false;
int Num_Level = NULL;
int Num_Key = NULL;

ALLEGRO_DISPLAY* display = NULL;

ALLEGRO_FONT* font=NULL;
ALLEGRO_FONT* font_small = NULL;
ALLEGRO_FONT* menu_font = NULL;
ALLEGRO_FONT* font_text = NULL;

ALLEGRO_EVENT_QUEUE* event_queue = NULL;
ALLEGRO_TIMER* timer = NULL;
ALLEGRO_TIMER* Timer = NULL;
bool redraw = true;
bool pre_start = true;

struct Time
{
	int millisec=NULL;
	int sec=NULL;
	int min=NULL;
};
Time Score;
Time Record;

struct Point
{
	int x;
	int y;
};

int Main_Menu_width = 0, Main_Menu_height = 0;
const int width = 1600, height = 900;
ALLEGRO_BITMAP* Main_Menu = NULL;
ALLEGRO_BITMAP* button1 = NULL;

struct Unit
{
	ALLEGRO_BITMAP* bit = NULL;
	int x = NULL;
	int y = NULL;
};
Unit _Unit;

struct Elf
{
	ALLEGRO_BITMAP* bit_down = NULL;
	ALLEGRO_BITMAP* bit_right = NULL;
	ALLEGRO_BITMAP* bit_left = NULL;
	ALLEGRO_BITMAP* bit_up = NULL;
	ALLEGRO_BITMAP* bit_death = NULL;
	int x = NULL;
	int y = NULL;
	Point center;
	int health = 300;
	bool death = false;
	int damage = 2;
};
Elf _Elf;
std::vector<Elf> ELVES;
int Max_Elves = NULL;
_int64 Num_Elves = NULL;
int alive = NULL;

struct Baulk
{
	ALLEGRO_BITMAP* bit = NULL;
	bool availability = true;
	int waiting = NULL;
	int x = NULL;
	int y = NULL;
};
Baulk _Baulk;

struct Throll
{
	ALLEGRO_BITMAP* bit = NULL;
	bool availability = true;
	const int damage = 140;
	int waiting_sec = NULL;
	int waiting_millisec = NULL;
	int x=NULL;
	int y=NULL;
};
Throll _Throll;

struct Sham
{
	ALLEGRO_BITMAP* bit_down = NULL;
	ALLEGRO_BITMAP* bit_right = NULL;
	ALLEGRO_BITMAP* bit_left = NULL;
	ALLEGRO_BITMAP* bit_up = NULL;
	ALLEGRO_BITMAP* bit_death = NULL;
	bool availability = true;
	int health = 300;
	int damage = NULL;
	int waiting_sec = NULL;
	int waiting_millisec = NULL;
	int x = NULL;
	int y = NULL;
};
Sham _Sham;

struct Corovan
{
	ALLEGRO_BITMAP* bit = NULL;
	ALLEGRO_BITMAP* bit_rot = NULL;
	int health = NULL;
	int damage = NULL;
	int x = NULL;
	int y = NULL;
	Point center;
	bool stop = false;
};
Corovan Low_Corovan;
Corovan Easy_Corovan;
Corovan Middle_Corovan;
Corovan Hard_Corovan;
Corovan Mad_Corovan;

ALLEGRO_BITMAP* Map1 = NULL;
ALLEGRO_BITMAP* Map2 = NULL;
ALLEGRO_BITMAP* Map3 = NULL;
ALLEGRO_BITMAP* Map4 = NULL;
ALLEGRO_BITMAP* Map5 = NULL;