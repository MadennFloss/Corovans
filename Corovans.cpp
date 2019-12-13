#pragma once


#include "Heads.h"
#include "Variables.h"


int al_display()//инициализация дисплея
{
	if (!al_init())
	{
		std::cerr << "could not initialize allegro!\n";
		return -1;
	}

	display = al_create_display(1600, 900);
	if (!display)
	{
		std::cerr << "could not initialize display!\n";
		return -2;
	}
}

void init()
{

	al_init_font_addon(); //инициализация шрифтов //
	al_init_ttf_addon();// шрифт //
	al_init_image_addon();//установка картинок
	//al_init_primitives_addon();//инициализация примитива
	al_install_keyboard();// установка клавиатуры
	Timer = al_create_timer(1.0 / fps);
	timer = al_create_timer(1.0 / fps);//установка таймеров (Первый для перерисовки вне игрового процесса, второй для игрового процесса)
	event_queue = al_create_event_queue();//показывает программе ,что используем очередь 
}

void load()//загрузка
{
	//шрифты
	font = al_load_ttf_font("18408.ttf", 40, 0);
	font_small = al_load_ttf_font("18408.ttf", 30, 0);
	font_text = al_load_ttf_font("18408.ttf", 24, 0);
	menu_font = al_load_ttf_font("18407.ttf", 70, 0);
	
	//кнопка
	button1 = al_load_bitmap("Bits/Button_1.PNG");

	//главное меню - фон
	Main_Menu = al_load_bitmap("Bits/Main_Menu.PNG");
	if (!Main_Menu) {
		al_show_native_message_box(display, "Error", "Error", "Failed to load image!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(display);
	}
	Main_Menu_width = al_get_bitmap_width(Main_Menu);
	Main_Menu_height = al_get_bitmap_height(Main_Menu);
	//карты уровней
	Map1 = al_load_bitmap("Maps/Map1.PNG");
	Map2 = al_load_bitmap("Maps/Map2.PNG");
	Map3 = al_load_bitmap("Maps/Map3.PNG");
	Map4 = al_load_bitmap("Maps/Map4.PNG");
	Map5 = al_load_bitmap("Maps/Map5.PNG");

	//юниты
	Low_Corovan.bit = al_load_bitmap("Bits/Low_Corovan.PNG");
	al_convert_mask_to_alpha(Low_Corovan.bit, al_map_rgb(106, 76, 48));
	Easy_Corovan.bit = al_load_bitmap("Bits/Easy_Corovan.PNG");
	al_convert_mask_to_alpha(Easy_Corovan.bit, al_map_rgb(106, 76, 48));
	Easy_Corovan.bit_rot = al_load_bitmap("Bits/Easy_Corovan_rot.PNG");
	al_convert_mask_to_alpha(Easy_Corovan.bit_rot, al_map_rgb(106, 76, 48));
	Middle_Corovan.bit = al_load_bitmap("Bits/Middle_Corovan.PNG");
	al_convert_mask_to_alpha(Middle_Corovan.bit, al_map_rgb(106, 76, 48));
	Middle_Corovan.bit_rot = al_load_bitmap("Bits/Middle_Corovan_rot.PNG");
	al_convert_mask_to_alpha(Middle_Corovan.bit_rot, al_map_rgb(106, 76, 48));
	Hard_Corovan.bit = al_load_bitmap("Bits/Hard_Corovan.PNG");
	al_convert_mask_to_alpha(Hard_Corovan.bit, al_map_rgb(106, 76, 48));
	Hard_Corovan.bit_rot = al_load_bitmap("Bits/Hard_Corovan_rot.PNG");
	al_convert_mask_to_alpha(Hard_Corovan.bit_rot, al_map_rgb(106, 76, 48));
	Mad_Corovan.bit = al_load_bitmap("Bits/Mad_Corovan.PNG");
	al_convert_mask_to_alpha(Mad_Corovan.bit, al_map_rgb(106, 76, 48));
	Mad_Corovan.bit_rot = al_load_bitmap("Bits/Mad_Corovan_rot.PNG");
	al_convert_mask_to_alpha(Mad_Corovan.bit_rot, al_map_rgb(106, 76, 48));

	_Unit.bit = al_load_bitmap("Bits/Unit.PNG");
	al_convert_mask_to_alpha(_Unit.bit, al_map_rgb(97, 68, 4));

	_Elf.bit_up = al_load_bitmap("Bits/Elf_up.PNG");
	al_convert_mask_to_alpha(_Elf.bit_up, al_map_rgb(66, 93, 41));
	_Elf.bit_down = al_load_bitmap("Bits/Elf_down.PNG");
	al_convert_mask_to_alpha(_Elf.bit_down, al_map_rgb(66, 93, 41));
	_Elf.bit_right = al_load_bitmap("Bits/Elf_right.PNG");
	al_convert_mask_to_alpha(_Elf.bit_right, al_map_rgb(66, 93, 41));
	_Elf.bit_left = al_load_bitmap("Bits/Elf_left.PNG");
	al_convert_mask_to_alpha(_Elf.bit_left, al_map_rgb(66, 93, 41));

	_Sham.bit_up = al_load_bitmap("Bits/Sham_up.PNG");
	al_convert_mask_to_alpha(_Sham.bit_up, al_map_rgb(66, 93, 41));
	_Sham.bit_down = al_load_bitmap("Bits/Sham_down.PNG");
	al_convert_mask_to_alpha(_Sham.bit_down, al_map_rgb(66, 93, 41));
	_Sham.bit_right = al_load_bitmap("Bits/Sham_right.PNG");
	al_convert_mask_to_alpha(_Sham.bit_right, al_map_rgb(66, 93, 41));
	_Sham.bit_left = al_load_bitmap("Bits/Sham_left.PNG");
	al_convert_mask_to_alpha(_Sham.bit_left, al_map_rgb(66, 93, 41));


	_Baulk.bit = al_load_bitmap("Bits/Baulk.PNG");
	al_convert_mask_to_alpha(_Baulk.bit, al_map_rgb(110, 80, 52));
	_Throll.bit = al_load_bitmap("Bits/Throll.PNG");
	al_convert_mask_to_alpha(_Throll.bit, al_map_rgb(191, 123, 199));
}

void start_menu()//отображение стартового меню
{
	al_draw_bitmap(Main_Menu, Main_Menu_width / 2 - Main_Menu_width / 2, Main_Menu_height / 2 - Main_Menu_height / 2, 0);
	al_draw_textf(menu_font, al_map_rgb(0, 20, 30), 680, 150, 0, "Corovans");
	al_draw_bitmap(button1, 660, 250, 0);
	al_draw_textf(font, al_map_rgb(0, 0, 0), 720, 280, 0, "G - Game");
	al_draw_bitmap(button1, 660, 450, 0);
	al_draw_textf(font, al_map_rgb(0, 0, 0), 700, 480, 0, "R - Records");
	al_draw_textf(font_small, al_map_rgb(0, 0, 0), 800, 680, ALLEGRO_ALIGN_CENTER, "Press X to close game (No, please, no)");
	al_draw_textf(font_small, al_map_rgb(0, 0, 0), 800, 800, ALLEGRO_ALIGN_CENTER, "Maxim Vasilev's game for course project");
	al_flip_display();
}

void spawn()//перемещение юнита
{
	switch (direction)
	{
	case DOWN:
		_Unit.y += 20;
		break;
	case UP:
		_Unit.y -= 20;
		break;
	case RIGHT:
		_Unit.x += 20;
		break;
	case LEFT:
		_Unit.x -= 20;
		break;
	}
	al_draw_bitmap(_Unit.bit, _Unit.x, _Unit.y, 0);
	al_flip_display();
}

void check_move(Corovan &_Corovan, std::vector<Elf> &_Elf)//проверка на столкновения
{
	for (int i = Max_Elves - 1; i > Num_Elves; --i)
	{
		if (!_Elf[i].death)
		{
			//Столкновение в левой-верхней части каравана
			if ((_Corovan.y <= (_Elf[i].y + al_get_bitmap_height(_Elf[i].bit_down))) &&
				(_Elf[i].x <= (_Corovan.x + al_get_bitmap_width(_Corovan.bit)/2) &&
				(_Elf[i].y <= (_Corovan.y + al_get_bitmap_height(_Corovan.bit)/2)) &&
				(_Corovan.x <= (_Elf[i].x + al_get_bitmap_width(_Elf[i].bit_right)))))
			{
				_Corovan.health -= _Elf[i].damage;
				_Elf[i].health -= _Corovan.damage;
				_Elf[i].x -= 20;
				_Elf[i].y -= 20;
				al_draw_bitmap(_Elf[i].bit_down, _Elf[i].x, _Elf[i].y, 0);
			}
			//Столкновение в правой-верхней части каравана
			if ((_Corovan.y <= (_Elf[i].y + al_get_bitmap_height(_Elf[i].bit_down))) &&
				(_Elf[i].x <= (_Corovan.x + al_get_bitmap_width(_Corovan.bit))) &&
				(_Elf[i].y <= (_Corovan.y + al_get_bitmap_height(_Corovan.bit) / 2)) &&
				((_Corovan.x + al_get_bitmap_width(_Corovan.bit) / 2) <= (_Elf[i].x + al_get_bitmap_width(_Elf[i].bit_right) / 2)))
			{
				_Corovan.health -= _Elf[i].damage;
				_Elf[i].health -= _Corovan.damage;
				_Elf[i].x += 20;
				_Elf[i].y -= 20;
				al_draw_bitmap(_Elf[i].bit_down, _Elf[i].x, _Elf[i].y, 0);
			}
			//Столкновение в правой-нижней части каравана
			if (((_Corovan.y + al_get_bitmap_height(_Corovan.bit) / 2) <= (_Elf[i].y + al_get_bitmap_height(_Elf[i].bit_down))) &&
				(_Elf[i].x <= (_Corovan.x + al_get_bitmap_width(_Corovan.bit))) &&
				(_Elf[i].y <= (_Corovan.y + al_get_bitmap_height(_Corovan.bit))) &&
				((_Corovan.x + al_get_bitmap_width(_Corovan.bit) / 2) <= (_Elf[i].x + al_get_bitmap_width(_Elf[i].bit_right) / 2)))
			{
				_Corovan.health -= _Elf[i].damage;
				_Elf[i].health -= _Corovan.damage;
				_Elf[i].x += 20;
				_Elf[i].y += 20;
				al_draw_bitmap(_Elf[i].bit_up, _Elf[i].x, _Elf[i].y, 0);
			}
			//Столкновение в левой-нижней части каравана
			if (((_Corovan.y + al_get_bitmap_height(_Corovan.bit) / 2) <= (_Elf[i].y + al_get_bitmap_height(_Elf[i].bit_down))) &&
				(_Elf[i].x <= (_Corovan.x + al_get_bitmap_width(_Corovan.bit)/2)) &&
				(_Elf[i].y <= (_Corovan.y + al_get_bitmap_height(_Corovan.bit))) &&
				(_Corovan.x <= (_Elf[i].x + al_get_bitmap_width(_Elf[i].bit_right))))
			{
				_Corovan.health -= _Elf[i].damage;
				_Elf[i].health -= _Corovan.damage;
				_Elf[i].x -= 10;
				_Elf[i].y += 10;
				al_draw_bitmap(_Elf[i].bit_up, _Elf[i].x, _Elf[i].y, 0);
			}
			if (_Elf[i].health <= 0)
			{
				_Elf[i].death = true;
				--alive;
			}
		}
	}
	if (!_Baulk.availability)//проверка столкновения каравана с бревном
	{
		if ((_Baulk.y <= (_Corovan.y + al_get_bitmap_height(_Corovan.bit))) &&
			((_Baulk.x + al_get_bitmap_width(_Baulk.bit)) >= _Corovan.x) &&
			((_Baulk.y + al_get_bitmap_height(_Baulk.bit)) >= _Corovan.y) &&
			(_Baulk.x < (_Corovan.x + al_get_bitmap_width(_Corovan.bit))))
		{
			if (!_Corovan.stop)
			{
				_Corovan.stop = true;
				_Baulk.waiting = Score.sec + 5;
			}
		}
	}
	if (!_Throll.availability)//проверка на столкновение с троллем
	{
		if ((_Throll.y <= (_Corovan.y + al_get_bitmap_height(_Corovan.bit))) &&
			((_Throll.x + al_get_bitmap_width(_Throll.bit)) >= _Corovan.x) &&
			((_Throll.y + al_get_bitmap_height(_Throll.bit)) >= _Corovan.y) &&
			(_Throll.x < (_Corovan.x + al_get_bitmap_width(_Corovan.bit))))
		{
			if (!_Corovan.stop)
			{
				_Corovan.stop = true;
				_Throll.waiting_sec = Score.sec + 2;
				_Throll.waiting_millisec = Score.millisec;
			}
		}
	}
	if ((Score.sec == _Throll.waiting_sec) && (Score.millisec == _Throll.waiting_millisec))//определить случайно, получит ли караван урон или нет
	{
		double _P = Score.millisec / 100.;
		std::cout << _P;
			if (_P < 0.5)
			{
				_Corovan.health -= _Throll.damage;
			}
	}
	//проверка на столкновение с обманщиком
	if (!_Sham.availability)
	{
		if ((_Sham.y <= (_Corovan.y + al_get_bitmap_height(_Corovan.bit))) &&
			((_Sham.x + al_get_bitmap_width(_Sham.bit_left)) >= _Corovan.x) &&
			((_Sham.y + al_get_bitmap_height(_Sham.bit_up)) >= _Corovan.y) &&
			(_Sham.x < (_Corovan.x + al_get_bitmap_width(_Corovan.bit))))
		{
			if (_Sham.waiting_sec == -1)
			{
				_Sham.waiting_sec = Score.sec + 4;
				_Sham.waiting_millisec = Score.millisec;
				_Corovan.damage++;
			}
			if (Score.sec == _Sham.waiting_sec && Score.millisec == _Sham.waiting_millisec)
			{
				_Corovan.damage = _Corovan.damage / 2;
				_Sham.damage = 2 + _Corovan.damage;
			}
			if ((Score.sec > _Sham.waiting_sec) && (_Sham.waiting_sec != -1))
			{
				_Sham.health -= _Corovan.damage;
				_Corovan.health -= _Sham.damage;
			}
		}
	}
}

void key_1()//первый уровень
{
	al_draw_bitmap(Map1, 0, 0, 0);
	for (int i = Max_Elves-1; i > Num_Elves; --i)
	{
		al_draw_bitmap(ELVES[i].bit_up, ELVES[i].x, ELVES[i].y, 0);
	}
	al_draw_bitmap(_Unit.bit, _Unit.x, _Unit.y, 0);
	al_draw_textf(font_small, al_map_rgb(0, 0, 0), 130, 30, 0, "Elves: %i", Num_Elves+1);
	al_draw_textf(font, al_map_rgb(0, 0, 0), 800, 30, ALLEGRO_ALIGN_CENTER, "Press Enter to start Game");
	al_draw_textf(font_small, al_map_rgb(0, 0, 0), 1520, 30, ALLEGRO_ALIGN_RIGHT, "Use pointers for moving spawner");
	al_draw_textf(font_small, al_map_rgb(0, 0, 0), 1520, 70, ALLEGRO_ALIGN_RIGHT, "S - spawn elves-criminals to heist Corovan");
	al_flip_display();
}

void first_level()//Первый уровень - маршруты
{
	al_draw_bitmap(Map1, 0, 0, 0);
	++Low_Corovan.x;
	al_draw_bitmap(Low_Corovan.bit, Low_Corovan.x, Low_Corovan.y, 0);
	if (Low_Corovan.health >= 0)
	{
		check_move(Low_Corovan, ELVES);
		for (int i = Max_Elves - 1; i > Num_Elves; --i)
		{
			if (!ELVES[i].death)
			{
				if (((ELVES[i].x + al_get_bitmap_width(ELVES[i].bit_right)) - (Low_Corovan.x + (al_get_bitmap_width(Low_Corovan.bit) / 2)) < 0))
				{
					ELVES[i].x += 2;
					al_draw_bitmap(ELVES[i].bit_right, ELVES[i].x, ELVES[i].y, 0);
				}
				if ((ELVES[i].x - (Low_Corovan.x + (al_get_bitmap_width(Low_Corovan.bit) / 2)) > 0))
				{
					ELVES[i].x -= 2;
					al_draw_bitmap(ELVES[i].bit_left, ELVES[i].x, ELVES[i].y, 0);

				}
				if (((ELVES[i].y + al_get_bitmap_height(ELVES[i].bit_down)) - (Low_Corovan.y + al_get_bitmap_height(Low_Corovan.bit) / 2)) < 0)
				{
					ELVES[i].y += 2;
					al_draw_bitmap(ELVES[i].bit_down, ELVES[i].x, ELVES[i].y, 0);
				}
				if ((ELVES[i].y - (Low_Corovan.y + al_get_bitmap_height(Low_Corovan.bit) / 2)) > 0)
				{
					ELVES[i].y -= 2;
					al_draw_bitmap(ELVES[i].bit_up, ELVES[i].x, ELVES[i].y, 0);
				}
				if (ELVES[i].health <= 0) ELVES[i].death = true;
			}
			else
			{
				al_draw_bitmap(ELVES[i].bit_down, ELVES[i].x, ELVES[i].y, 0);
			}
		}
		++Score.millisec;
		if (Score.millisec == 100)
		{
			++Score.sec;
			Score.millisec = 0;
		}
		if (Score.sec == 60)
		{
			++Score.min;
			Score.sec = 0;
		}
		al_draw_textf(font_small, al_map_rgb(0, 0, 0), 30, 70, 0, "Living elves-criminals: %i", alive);
		al_draw_textf(font_small, al_map_rgb(0, 0, 0), 30, 100, 0, "Corovan's health: %i", Low_Corovan.health);
		al_draw_textf(font_small, al_map_rgb(0, 0, 0), 30, 150, 0, "Time: %i:%i:%i", Score.min, Score.sec, Score.millisec);
	}
	else
	{
		if ((Record.min == 0) && (Record.sec == 0) && (Record.millisec == 0))Record = Score;
			if (Record.min > Score.min) Record = Score;
			if (Record.min == Score.min)
			{
				if (Record.sec > Score.sec) Record = Score;
				if (Record.sec == Score.sec)
				{
					if (Record.millisec > Score.millisec) Record = Score;
				}
			}
		al_stop_timer(timer);
		al_draw_textf(font, al_map_rgb(0, 0, 0), 800, 400, ALLEGRO_ALIGN_CENTER, "You Win!");
		al_draw_textf(font_small, al_map_rgb(0, 0, 0), 800, 440, ALLEGRO_ALIGN_CENTER, "Press ESC to back main menu");
	}
	al_draw_bitmap(_Unit.bit, _Unit.x, _Unit.y, 0);
	al_flip_display();
	if (Low_Corovan.x == 1450 || alive==0)
	{
		al_stop_timer(timer);
		al_draw_textf(font, al_map_rgb(0, 0, 0), 800, 400, ALLEGRO_ALIGN_CENTER, "Game Over");
		al_draw_textf(font_small, al_map_rgb(0, 0, 0), 800, 440, ALLEGRO_ALIGN_CENTER, "Press ESC to back main menu");
		al_flip_display();
	}
}

void key_2()//второй уровень
{
	al_draw_bitmap(Map2, 0, 0, 0);
	al_draw_bitmap(_Baulk.bit, _Baulk.x, _Baulk.y, 0);
	for (int i = Max_Elves - 1; i > Num_Elves; --i)
	{
		al_draw_bitmap(ELVES[i].bit_up, ELVES[i].x, ELVES[i].y, 0);
	}
	al_draw_bitmap(_Unit.bit, _Unit.x, _Unit.y, 0);
	al_draw_textf(font_small, al_map_rgb(0, 0, 0), 130, 30, 0, "Elves: %i", Num_Elves + 1);
	al_draw_textf(font, al_map_rgb(0, 0, 0), 800, 30, ALLEGRO_ALIGN_CENTER, "Press Enter to start Game");
	al_draw_textf(font_small, al_map_rgb(0, 0, 0), 1520, 30, ALLEGRO_ALIGN_RIGHT, "Use pointers for moving spawner");
	al_draw_textf(font_small, al_map_rgb(0, 0, 0), 1520, 70, ALLEGRO_ALIGN_RIGHT, "S - spawn elves-criminals");
	al_draw_textf(font_small, al_map_rgb(0, 0, 0), 1520, 100, ALLEGRO_ALIGN_RIGHT, "B - spawn baulk to stop Corovan for 5 sec");
	al_flip_display();
}

//второй уровень - маршруты
void second_level()
{
	al_draw_bitmap(Map2, 0, 0, 0);
	if (!_Baulk.availability)
	{
		al_draw_bitmap(_Baulk.bit, _Baulk.x, _Baulk.y, 0);
	}
	if (!Easy_Corovan.stop)
	{
		if (Easy_Corovan.x < 950)
		{
			al_draw_bitmap(Easy_Corovan.bit, Easy_Corovan.x, Easy_Corovan.y, 0);
			++Easy_Corovan.x;
		}
		else
		{
			al_draw_bitmap(Easy_Corovan.bit_rot, Easy_Corovan.x, Easy_Corovan.y, 0);
			++Easy_Corovan.y;
		}
	}
	else
	{
		if (Score.sec - _Baulk.waiting >= 0)
		{
			Easy_Corovan.stop = false;
			_Baulk.availability = true;
			al_draw_bitmap(_Baulk.bit, _Baulk.x + 1600, _Baulk.y, 0);
		}
		if (Easy_Corovan.x < 950)
		{
			al_draw_bitmap(Easy_Corovan.bit, Easy_Corovan.x, Easy_Corovan.y, 0);
		}
		else
		{
			al_draw_bitmap(Easy_Corovan.bit_rot, Easy_Corovan.x, Easy_Corovan.y, 0);
		}
	}
	if (Easy_Corovan.health >= 0)
	{
		check_move(Easy_Corovan, ELVES);
		for (int i = Max_Elves - 1; i > Num_Elves; --i)
		{
			if (!ELVES[i].death)
			{
				if (((ELVES[i].x + al_get_bitmap_width(ELVES[i].bit_right)) - (Easy_Corovan.x + (al_get_bitmap_width(Easy_Corovan.bit) / 2)) < 0))
				{
					ELVES[i].x += 2;
					al_draw_bitmap(ELVES[i].bit_right, ELVES[i].x, ELVES[i].y, 0);
				}
				if ((ELVES[i].x - (Easy_Corovan.x + (al_get_bitmap_width(Easy_Corovan.bit) / 2)) > 0))
				{
					ELVES[i].x -= 2;
					al_draw_bitmap(ELVES[i].bit_left, ELVES[i].x, ELVES[i].y, 0);
				}
				if (((ELVES[i].y + al_get_bitmap_height(ELVES[i].bit_down)) - (Easy_Corovan.y + al_get_bitmap_height(Easy_Corovan.bit) / 2)) < 0)
				{
					ELVES[i].y += 2;
					al_draw_bitmap(ELVES[i].bit_down, ELVES[i].x, ELVES[i].y, 0);
				}
				if ((ELVES[i].y - (Easy_Corovan.y + al_get_bitmap_height(Easy_Corovan.bit) / 2)) > 0)
				{
					ELVES[i].y -= 2;
					al_draw_bitmap(ELVES[i].bit_up, ELVES[i].x, ELVES[i].y, 0);
				}
				if (ELVES[i].health <= 0) ELVES[i].death = true;
			}
			else
			{
				al_draw_bitmap(ELVES[i].bit_down, ELVES[i].x, ELVES[i].y, 0);
			}
		}
		++Score.millisec;
		if (Score.millisec == 100)
		{
			++Score.sec;
			Score.millisec = 0;
		}
		if (Score.sec == 60)
		{
			++Score.min;
			Score.sec = 0;
		}
		al_draw_textf(font_small, al_map_rgb(0, 0, 0), 30, 70, 0, "Living elves-criminals: %i", alive);
		al_draw_textf(font_small, al_map_rgb(0, 0, 0), 30, 100, 0, "Corovan's health: %i", Easy_Corovan.health);
		al_draw_textf(font_small, al_map_rgb(0, 0, 0), 30, 150, 0, "Time: %i:%i:%i", Score.min, Score.sec, Score.millisec);
	}
	else
	{
		if ((Record.min == 0) && (Record.sec == 0) && (Record.millisec == 0))Record = Score;
		if (Record.min > Score.min) Record = Score;
		if (Record.min == Score.min)
		{
			if (Record.sec > Score.sec) Record = Score;
			if (Record.sec == Score.sec)
			{
				if (Record.millisec > Score.millisec) Record = Score;
			}
		}
		al_stop_timer(timer);
		al_draw_textf(font, al_map_rgb(0, 0, 0), 800, 400, ALLEGRO_ALIGN_CENTER, "You Win!");
		al_draw_textf(font_small, al_map_rgb(0, 0, 0), 800, 440, ALLEGRO_ALIGN_CENTER, "Press ESC to back main menu");
	}
	al_draw_bitmap(_Unit.bit, _Unit.x, _Unit.y, 0);
	al_flip_display();
	if (Easy_Corovan.y == 750 || alive == 0)
	{
		al_stop_timer(timer);
		al_draw_textf(font, al_map_rgb(0, 0, 0), 800, 400, ALLEGRO_ALIGN_CENTER, "Game Over");
		al_draw_textf(font_small, al_map_rgb(0, 0, 0), 800, 440, ALLEGRO_ALIGN_CENTER, "Press ESC to back main menu");
		al_flip_display();
	}
}

void key_3()//третий уровень
{
	al_draw_bitmap(Map3, 0, 0, 0);
	al_draw_bitmap(_Baulk.bit, _Baulk.x, _Baulk.y, 0);
	for (int i = Max_Elves - 1; i > Num_Elves; --i)
	{
		al_draw_bitmap(ELVES[i].bit_up, ELVES[i].x, ELVES[i].y, 0);
	}
	al_draw_bitmap(_Throll.bit, _Throll.x, _Throll.y, 0);
	al_draw_bitmap(_Unit.bit, _Unit.x, _Unit.y, 0);
	al_draw_textf(font_small, al_map_rgb(0, 0, 0), 130, 30, 0, "Elves: %i", Num_Elves + 1);
	al_draw_textf(font, al_map_rgb(0, 0, 0), 760, 30, ALLEGRO_ALIGN_CENTER, "Press Enter to start Game");
	al_draw_textf(font_small, al_map_rgb(0, 0, 0), 1520, 30, ALLEGRO_ALIGN_RIGHT, "Use pointers for moving spawner");
	al_draw_textf(font_small, al_map_rgb(0, 0, 0), 1520, 70, ALLEGRO_ALIGN_RIGHT, "S - spawn elves-criminals");
	al_draw_textf(font_small, al_map_rgb(0, 0, 0), 1520, 100, ALLEGRO_ALIGN_RIGHT, "B - spawn Baulk");
	al_draw_textf(font_small, al_map_rgb(0, 0, 0), 1520, 130, ALLEGRO_ALIGN_RIGHT, "T - spawn Throll");
	al_draw_textf(font_text, al_map_rgb(0, 0, 0), 1520, 150, ALLEGRO_ALIGN_RIGHT, "Throll can stop Corovan for 2 second.");
	al_draw_textf(font_text, al_map_rgb(0, 0, 0), 1520, 170, ALLEGRO_ALIGN_RIGHT, "If Corovan had solve Throll's riddle");
	al_draw_textf(font_text, al_map_rgb(0, 0, 0), 1520, 190, ALLEGRO_ALIGN_RIGHT, "it can move forvard, else one get damage by Throll");
	al_flip_display();
}

//третий уровень - маршруты
void third_level()
{
	al_draw_bitmap(Map3, 0, 0, 0);
	if (!_Baulk.availability)
	{
		al_draw_bitmap(_Baulk.bit, _Baulk.x, _Baulk.y, 0);
	}
	if (!Middle_Corovan.stop)
	{
		if (Middle_Corovan.x < 465)
		{
			al_draw_bitmap(Middle_Corovan.bit, Middle_Corovan.x, Middle_Corovan.y, 0);
			++Middle_Corovan.x;
		}
		else if (Middle_Corovan.x==465)
		{
			al_draw_bitmap(Middle_Corovan.bit_rot, Middle_Corovan.x, Middle_Corovan.y, 0);
			++Middle_Corovan.y;
		}
		if (Middle_Corovan.x < 950 && Middle_Corovan.y == 750)
		{
			al_draw_bitmap(Middle_Corovan.bit, Middle_Corovan.x, Middle_Corovan.y, 0);
			++Middle_Corovan.x;
		}
		else if (Middle_Corovan.x==950)
		{
			al_draw_bitmap(Middle_Corovan.bit_rot, Middle_Corovan.x, Middle_Corovan.y, 0);
			--Middle_Corovan.y;
		}
	}
	else
	{
		if ((Score.sec - _Baulk.waiting) == 0)
		{
			Middle_Corovan.stop = false;
			_Baulk.availability = true;
			al_draw_bitmap(_Baulk.bit, _Baulk.x + 1600, _Baulk.y, 0);
		}
			if ((Score.sec - _Throll.waiting_sec) == 0)
			{
				Middle_Corovan.stop = false;
				_Throll.availability = true;
				al_draw_bitmap(_Throll.bit, _Throll.x + 1600, _Throll.y, 0);
			}
		if (Middle_Corovan.x < 465)
			al_draw_bitmap(Middle_Corovan.bit, Middle_Corovan.x, Middle_Corovan.y, 0);
		else if (Middle_Corovan.x == 465)
			al_draw_bitmap(Middle_Corovan.bit_rot, Middle_Corovan.x, Middle_Corovan.y, 0);
		if (Middle_Corovan.x < 950 && Middle_Corovan.y == 750)
			al_draw_bitmap(Middle_Corovan.bit, Middle_Corovan.x, Middle_Corovan.y, 0);
		else if (Middle_Corovan.x == 950)
			al_draw_bitmap(Middle_Corovan.bit_rot, Middle_Corovan.x, Middle_Corovan.y, 0);
	}
	if (Middle_Corovan.health >= 0)
	{
		check_move(Middle_Corovan, ELVES);
		for (int i = Max_Elves - 1; i > Num_Elves; --i)
		{
			if (!ELVES[i].death)
			{
				if (((ELVES[i].x + al_get_bitmap_width(ELVES[i].bit_right)) - (Middle_Corovan.x + (al_get_bitmap_width(Middle_Corovan.bit) / 2)) < 0))
				{
					ELVES[i].x += 2;
					al_draw_bitmap(ELVES[i].bit_right, ELVES[i].x, ELVES[i].y, 0);
				}
				if ((ELVES[i].x - (Middle_Corovan.x + (al_get_bitmap_width(Middle_Corovan.bit) / 2)) > 0))
				{
					ELVES[i].x -= 2;
					al_draw_bitmap(ELVES[i].bit_left, ELVES[i].x, ELVES[i].y, 0);
				}
				if (((ELVES[i].y + al_get_bitmap_height(ELVES[i].bit_down)) - (Middle_Corovan.y + al_get_bitmap_height(Middle_Corovan.bit) / 2)) < 0)
				{
					ELVES[i].y += 2;
					al_draw_bitmap(ELVES[i].bit_down, ELVES[i].x, ELVES[i].y, 0);
				}
				if ((ELVES[i].y - (Middle_Corovan.y + al_get_bitmap_height(Middle_Corovan.bit) / 2)) > 0)
				{
					ELVES[i].y -= 2;
					al_draw_bitmap(ELVES[i].bit_up, ELVES[i].x, ELVES[i].y, 0);
				}
				if (ELVES[i].health <= 0) ELVES[i].death = true;
			}
			else
			{
				al_draw_bitmap(ELVES[i].bit_down, ELVES[i].x, ELVES[i].y, 0);
			}
		}
		if (!_Throll.availability)
		{
			al_draw_bitmap(_Throll.bit, _Throll.x, _Throll.y, 0);
		}
		++Score.millisec;
		if (Score.millisec == 100)
		{
			++Score.sec;
			Score.millisec = 0;
		}
		if (Score.sec == 60)
		{
			++Score.min;
			Score.sec = 0;
		}
		al_draw_textf(font_small, al_map_rgb(0, 0, 0), 30, 70, 0, "Living elves-criminals: %i", alive);
		al_draw_textf(font_small, al_map_rgb(0, 0, 0), 30, 100, 0, "Corovan's health: %i", Middle_Corovan.health);
		al_draw_textf(font_small, al_map_rgb(0, 0, 0), 30, 150, 0, "Time: %i:%i:%i", Score.min, Score.sec, Score.millisec);
	}
	else
	{
		if ((Record.min == 0) && (Record.sec == 0) && (Record.millisec == 0))Record = Score;
		if (Record.min > Score.min) Record = Score;
		if (Record.min == Score.min)
		{
			if (Record.sec > Score.sec) Record = Score;
			if (Record.sec == Score.sec)
			{
				if (Record.millisec > Score.millisec) Record = Score;
			}
		}
		al_stop_timer(timer);
		al_draw_textf(font, al_map_rgb(0, 0, 0), 800, 400, ALLEGRO_ALIGN_CENTER, "You Win!");
		al_draw_textf(font_small, al_map_rgb(0, 0, 0), 800, 440, ALLEGRO_ALIGN_CENTER, "Press ESC to back main menu");
	}
	al_draw_bitmap(_Unit.bit, _Unit.x, _Unit.y, 0);
	al_flip_display();
	if (Middle_Corovan.y == 0 || alive == 0)
	{
		al_stop_timer(timer);
		al_draw_textf(font, al_map_rgb(0, 0, 0), 800, 400, ALLEGRO_ALIGN_CENTER, "Game Over");
		al_draw_textf(font_small, al_map_rgb(0, 0, 0), 800, 440, ALLEGRO_ALIGN_CENTER, "Press ESC to back main menu");
		al_flip_display();
	}
}

void key_4()//четвертый уровень
{
	al_draw_bitmap(Map4, 0, 0, 0);
	al_draw_bitmap(_Baulk.bit, _Baulk.x, _Baulk.y, 0);
	al_draw_bitmap(_Sham.bit_up, _Sham.x, _Sham.y, 0);
	for (int i = Max_Elves - 1; i > Num_Elves; --i)
	{
		al_draw_bitmap(ELVES[i].bit_up, ELVES[i].x, ELVES[i].y, 0);
	}
	al_draw_bitmap(_Throll.bit, _Throll.x, _Throll.y, 0);
	al_draw_bitmap(_Unit.bit, _Unit.x, _Unit.y, 0);
	al_draw_textf(font_small, al_map_rgb(0, 0, 0), 130, 30, 0, "Elves: %i", Num_Elves + 1);
	al_draw_textf(font, al_map_rgb(0, 0, 0), 760, 30, ALLEGRO_ALIGN_CENTER, "Press Enter to start Game");
	al_draw_textf(font_small, al_map_rgb(0, 0, 0), 1520, 30, ALLEGRO_ALIGN_RIGHT, "Use pointers for moving spawner");
	al_draw_textf(font_small, al_map_rgb(0, 0, 0), 1520, 70, ALLEGRO_ALIGN_RIGHT, "S - spawn elves-criminals");
	al_draw_textf(font_small, al_map_rgb(0, 0, 0), 1520, 100, ALLEGRO_ALIGN_RIGHT, "B - spawn Baulk");
	al_draw_textf(font_small, al_map_rgb(0, 0, 0), 1520, 130, ALLEGRO_ALIGN_RIGHT, "T - spawn Throll");
	al_draw_textf(font_small, al_map_rgb(0, 0, 0), 1520, 160, ALLEGRO_ALIGN_RIGHT, "J - spawn Sham");
	al_draw_textf(font_text, al_map_rgb(0, 0, 0), 1520, 190, ALLEGRO_ALIGN_RIGHT, "Sham attacks elves, pretending to be guarding,");
	al_draw_textf(font_text, al_map_rgb(0, 0, 0), 1520, 210, ALLEGRO_ALIGN_RIGHT, "after which, having bowed half of the Corovan to");
	al_draw_textf(font_text, al_map_rgb(0, 0, 0), 1520, 230, ALLEGRO_ALIGN_RIGHT, "his side, he attacks it.");
	al_flip_display();
}

//четвертый уровень - маршруты
void four_level()
{
	al_draw_bitmap(Map4, 0, 0, 0);
	if (!_Baulk.availability)
	{
		al_draw_bitmap(_Baulk.bit, _Baulk.x, _Baulk.y, 0);
	}
	if (!Hard_Corovan.stop)
	{
		if ((Hard_Corovan.y > 450) && (Hard_Corovan.x==50))
		{
			al_draw_bitmap(Hard_Corovan.bit_rot, Hard_Corovan.x, Hard_Corovan.y, 0);
			--Hard_Corovan.y;
		}
		else if ((Hard_Corovan.y == 450) && (Hard_Corovan.x < 450))
		{
			al_draw_bitmap(Hard_Corovan.bit, Hard_Corovan.x, Hard_Corovan.y, 0);
			++Hard_Corovan.x;
		}
		if ((Hard_Corovan.x == 450) && (Hard_Corovan.y > 100))
		{
			al_draw_bitmap(Hard_Corovan.bit_rot, Hard_Corovan.x, Hard_Corovan.y, 0);
			--Hard_Corovan.y;
		}
		else if ((Hard_Corovan.y == 100) && (Hard_Corovan.x < 950))
		{
			al_draw_bitmap(Hard_Corovan.bit, Hard_Corovan.x, Hard_Corovan.y, 0);
			++Hard_Corovan.x;
		}
		if ((Hard_Corovan.x == 950) && (Hard_Corovan.y < 700))
		{
			al_draw_bitmap(Hard_Corovan.bit_rot, Hard_Corovan.x, Hard_Corovan.y, 0);
			++Hard_Corovan.y;
		}
		if ((Hard_Corovan.y == 700) && (950 <= Hard_Corovan.x))
		{
			al_draw_bitmap(Hard_Corovan.bit, Hard_Corovan.x, Hard_Corovan.y, 0);
			++Hard_Corovan.x;
		}
	}
	else
	{
		if ((Score.sec - _Baulk.waiting) == 0)
		{
			Hard_Corovan.stop = false;
			_Baulk.availability = true;
			al_draw_bitmap(_Baulk.bit, _Baulk.x + 1600, _Baulk.y, 0);
		}
		if ((Score.sec - _Throll.waiting_sec) == 0)
		{
			Hard_Corovan.stop = false;
			_Throll.availability = true;
			al_draw_bitmap(_Throll.bit, _Throll.x + 1600, _Throll.y, 0);
		}
		if ((Hard_Corovan.y > 450) && (Hard_Corovan.x == 50))
			al_draw_bitmap(Hard_Corovan.bit_rot, Hard_Corovan.x, Hard_Corovan.y, 0);
		else if ((Hard_Corovan.y == 450) && (Hard_Corovan.x < 450))
			al_draw_bitmap(Hard_Corovan.bit, Hard_Corovan.x, Hard_Corovan.y, 0);
		if ((Hard_Corovan.x == 450) && (Hard_Corovan.y > 100))
			al_draw_bitmap(Hard_Corovan.bit_rot, Hard_Corovan.x, Hard_Corovan.y, 0);
		else if ((Hard_Corovan.y == 100) && (Hard_Corovan.x < 950))
			al_draw_bitmap(Hard_Corovan.bit, Hard_Corovan.x, Hard_Corovan.y, 0);
		if ((Hard_Corovan.x == 950) && (Hard_Corovan.y < 700))
			al_draw_bitmap(Hard_Corovan.bit_rot, Hard_Corovan.x, Hard_Corovan.y, 0);
		else if ((Hard_Corovan.y == 700) && (950 <= Hard_Corovan.x))
			al_draw_bitmap(Hard_Corovan.bit, Hard_Corovan.x, Hard_Corovan.y, 0);
	}
	if (Hard_Corovan.health >= 0)
	{
		check_move(Hard_Corovan, ELVES);
		for (int i = Max_Elves - 1; i > Num_Elves; --i)
		{
			if (!ELVES[i].death)
			{
				if (((ELVES[i].x + al_get_bitmap_width(ELVES[i].bit_right)) - (Hard_Corovan.x + (al_get_bitmap_width(Hard_Corovan.bit) / 2)) < 0))
				{
					ELVES[i].x += 2;
					al_draw_bitmap(ELVES[i].bit_right, ELVES[i].x, ELVES[i].y, 0);
				}
				if ((ELVES[i].x - (Hard_Corovan.x + (al_get_bitmap_width(Hard_Corovan.bit) / 2)) > 0))
				{
					ELVES[i].x -= 2;
					al_draw_bitmap(ELVES[i].bit_left, ELVES[i].x, ELVES[i].y, 0);
				}
				if (((ELVES[i].y + al_get_bitmap_height(ELVES[i].bit_down)) - (Hard_Corovan.y + al_get_bitmap_height(Hard_Corovan.bit) / 2)) < 0)
				{
					ELVES[i].y += 2;
					al_draw_bitmap(ELVES[i].bit_down, ELVES[i].x, ELVES[i].y, 0);
				}
				if ((ELVES[i].y - (Hard_Corovan.y + al_get_bitmap_height(Hard_Corovan.bit) / 2)) > 0)
				{
					ELVES[i].y -= 2;
					al_draw_bitmap(ELVES[i].bit_up, ELVES[i].x, ELVES[i].y, 0);
				}
				if (ELVES[i].health <= 0) ELVES[i].death = true;
			}
			else
			{
				al_draw_bitmap(ELVES[i].bit_down, ELVES[i].x, ELVES[i].y, 0);
			}
		}
		if (!_Sham.availability)
		{
			if (((_Sham.x + al_get_bitmap_width(_Sham.bit_right)) - (Hard_Corovan.x + (al_get_bitmap_width(Hard_Corovan.bit) / 2)) < 0))
			{
				_Sham.x += 2;
				al_draw_bitmap(_Sham.bit_right, _Sham.x, _Sham.y, 0);
			}
			if ((_Sham.x - (Hard_Corovan.x + (al_get_bitmap_width(Hard_Corovan.bit) / 2)) > 0))
			{
				_Sham.x -= 2;
				al_draw_bitmap(_Sham.bit_left, _Sham.x, _Sham.y, 0);
			}
			if (((_Sham.y + al_get_bitmap_height(_Sham.bit_down)) - (Hard_Corovan.y + al_get_bitmap_height(Hard_Corovan.bit) / 2)) < 0)
			{
				_Sham.y += 2;
				al_draw_bitmap(_Sham.bit_down, _Sham.x, _Sham.y, 0);
			}
			if ((_Sham.y - (Hard_Corovan.y + al_get_bitmap_height(Hard_Corovan.bit) / 2)) > 0)
			{
				_Sham.y -= 2;
				al_draw_bitmap(_Sham.bit_up, _Sham.x, _Sham.y, 0);
			}
			if (_Sham.health <= 0) _Sham.availability = true;
		}
		else
		{
			al_draw_bitmap(_Sham.bit_down, _Sham.x, _Sham.y, 0);
		}
		if (!_Throll.availability)
		{
			al_draw_bitmap(_Throll.bit, _Throll.x, _Throll.y, 0);
		}
		++Score.millisec;
		if (Score.millisec == 100)
		{
			++Score.sec;
			Score.millisec = 0;
		}
		if (Score.sec == 60)
		{
			++Score.min;
			Score.sec = 0;
		}
		al_draw_textf(font_small, al_map_rgb(0, 0, 0), 30, 70, 0, "Living elves-criminals: %i", alive);
		al_draw_textf(font_small, al_map_rgb(0, 0, 0), 30, 100, 0, "Corovan's health: %i", Hard_Corovan.health);
		al_draw_textf(font_small, al_map_rgb(0, 0, 0), 30, 150, 0, "Time: %i:%i:%i", Score.min, Score.sec, Score.millisec);
	}
	else
	{
		if ((Record.min == 0) && (Record.sec == 0) && (Record.millisec == 0))Record = Score;
		if (Record.min > Score.min) Record = Score;
		if (Record.min == Score.min)
		{
			if (Record.sec > Score.sec) Record = Score;
			if (Record.sec == Score.sec)
			{
				if (Record.millisec > Score.millisec) Record = Score;
			}
		}
		al_stop_timer(timer);
		al_draw_textf(font, al_map_rgb(0, 0, 0), 800, 400, ALLEGRO_ALIGN_CENTER, "You Win!");
		al_draw_textf(font_small, al_map_rgb(0, 0, 0), 800, 440, ALLEGRO_ALIGN_CENTER, "Press ESC to back main menu");
	}
	al_draw_bitmap(_Unit.bit, _Unit.x, _Unit.y, 0);
	al_flip_display();
	if (Hard_Corovan.y == 0 || alive == 0)
	{
		al_stop_timer(timer);
		al_draw_textf(font, al_map_rgb(0, 0, 0), 800, 400, ALLEGRO_ALIGN_CENTER, "Game Over");
		al_draw_textf(font_small, al_map_rgb(0, 0, 0), 800, 440, ALLEGRO_ALIGN_CENTER, "Press ESC to back main menu");
		al_flip_display();
	}
}

void key_5()//пятый уровень
{
	al_draw_bitmap(Map5, 0, 0, 0);
	al_draw_bitmap(_Baulk.bit, _Baulk.x, _Baulk.y, 0);
	al_draw_bitmap(_Sham.bit_up, _Sham.x, _Sham.y, 0);
	for (int i = Max_Elves - 1; i > Num_Elves; --i)
	{
		al_draw_bitmap(ELVES[i].bit_up, ELVES[i].x, ELVES[i].y, 0);
	}
	al_draw_bitmap(_Throll.bit, _Throll.x, _Throll.y, 0);
	al_draw_bitmap(_Unit.bit, _Unit.x, _Unit.y, 0);
	al_draw_textf(font_small, al_map_rgb(0, 0, 0), 130, 30, 0, "Elves: %i", Num_Elves + 1);
	al_draw_textf(font, al_map_rgb(0, 0, 0), 760, 30, ALLEGRO_ALIGN_CENTER, "Press Enter to start Game");
	al_draw_textf(font_small, al_map_rgb(0, 0, 0), 1520, 100, ALLEGRO_ALIGN_RIGHT, "Well, I think, you know, what to do");
	al_draw_textf(font_text, al_map_rgb(0, 0, 0), 1520, 130, ALLEGRO_ALIGN_RIGHT, "(I hope, you did not miss the previous levels");
	al_flip_display();
}

//пятый уровень - маршруты
void fifth_level()
{
	al_draw_bitmap(Map5, 0, 0, 0);
	if (!_Baulk.availability)
	{
		al_draw_bitmap(_Baulk.bit, _Baulk.x, _Baulk.y, 0);
	}
	if (!Mad_Corovan.stop)
	{
		if (Mad_Corovan.x < 300 && Mad_Corovan.y == 400)
		{
			al_draw_bitmap(Mad_Corovan.bit, Mad_Corovan.x, Mad_Corovan.y, 0);
			++Mad_Corovan.x;
		}
		if (Mad_Corovan.y > 100 && Mad_Corovan.x == 300)
		{
			al_draw_bitmap(Mad_Corovan.bit_rot, Mad_Corovan.x, Mad_Corovan.y, 0);
			--Mad_Corovan.y;
		}
		if (Mad_Corovan.x < 650 && Mad_Corovan.y == 100)
		{
			al_draw_bitmap(Mad_Corovan.bit, Mad_Corovan.x, Mad_Corovan.y, 0);
			++Mad_Corovan.x;
		}
		if (Mad_Corovan.y < 700 && Mad_Corovan.x == 650)
		{
			al_draw_bitmap(Mad_Corovan.bit_rot, Mad_Corovan.x, Mad_Corovan.y, 0);
			++Mad_Corovan.y;
		}
		if (Mad_Corovan.x < 1000 && Mad_Corovan.y == 700)
		{
			al_draw_bitmap(Mad_Corovan.bit, Mad_Corovan.x, Mad_Corovan.y, 0);
			++Mad_Corovan.x;
		}
		if (Mad_Corovan.y > 200 && Mad_Corovan.x == 1000)
		{
			al_draw_bitmap(Mad_Corovan.bit_rot, Mad_Corovan.x, Mad_Corovan.y, 0);
			--Mad_Corovan.y;
		}
		if ((1000 <= Mad_Corovan.x) && (Mad_Corovan.x) < 1350 && (Mad_Corovan.y == 200))
		{
			al_draw_bitmap(Mad_Corovan.bit, Mad_Corovan.x, Mad_Corovan.y, 0);
			++Mad_Corovan.x;
		}
		if (Mad_Corovan.y < 600 && Mad_Corovan.x == 1350)
		{
			al_draw_bitmap(Mad_Corovan.bit_rot, Mad_Corovan.x, Mad_Corovan.y, 0);
			++Mad_Corovan.y;
		}
		if (1350 <= Mad_Corovan.x && Mad_Corovan.y == 600)
		{
			al_draw_bitmap(Mad_Corovan.bit, Mad_Corovan.x, Mad_Corovan.y, 0);
			++Mad_Corovan.x;
		}
	}
	else
	{	
		if ((Score.sec - _Baulk.waiting) == 0)
		{
			Mad_Corovan.stop = false;
			_Baulk.availability = true;
			al_draw_bitmap(_Baulk.bit, _Baulk.x + 1600, _Baulk.y, 0);
		}
		if ((Score.sec - _Throll.waiting_sec) == 0)
		{
			Mad_Corovan.stop = false;
			_Throll.availability = true;
			al_draw_bitmap(_Throll.bit, _Throll.x + 1600, _Throll.y, 0);
		}
		if (Mad_Corovan.x < 300 && Mad_Corovan.y == 400)
			al_draw_bitmap(Mad_Corovan.bit, Mad_Corovan.x, Mad_Corovan.y, 0);
		if (Mad_Corovan.y > 100 && Mad_Corovan.x == 300)
			al_draw_bitmap(Mad_Corovan.bit_rot, Mad_Corovan.x, Mad_Corovan.y, 0);
		if (Mad_Corovan.x < 650 && Mad_Corovan.y == 100)
			al_draw_bitmap(Mad_Corovan.bit, Mad_Corovan.x, Mad_Corovan.y, 0);
		if (Mad_Corovan.y < 700 && Mad_Corovan.x == 650)
			al_draw_bitmap(Mad_Corovan.bit_rot, Mad_Corovan.x, Mad_Corovan.y, 0);
		if (Mad_Corovan.x < 1000 && Mad_Corovan.y == 700)
			al_draw_bitmap(Mad_Corovan.bit, Mad_Corovan.x, Mad_Corovan.y, 0);
		if (Mad_Corovan.y > 200 && Mad_Corovan.x == 1000)
			al_draw_bitmap(Mad_Corovan.bit_rot, Mad_Corovan.x, Mad_Corovan.y, 0);
		if ((1000 <= Mad_Corovan.x) && (Mad_Corovan.x) < 1350 && (Mad_Corovan.y == 200))
			al_draw_bitmap(Mad_Corovan.bit, Mad_Corovan.x, Mad_Corovan.y, 0);
		if (Mad_Corovan.y < 600 && Mad_Corovan.x == 1350)
			al_draw_bitmap(Mad_Corovan.bit_rot, Mad_Corovan.x, Mad_Corovan.y, 0);
		if (1350 <= Mad_Corovan.x && Mad_Corovan.y == 600)
			al_draw_bitmap(Mad_Corovan.bit, Mad_Corovan.x, Mad_Corovan.y, 0);
	}
	if (Mad_Corovan.health >= 0)
	{
		check_move(Mad_Corovan, ELVES);
		for (int i = Max_Elves - 1; i > Num_Elves; --i)
		{
			if (!ELVES[i].death)
			{
				if (((ELVES[i].x + al_get_bitmap_width(ELVES[i].bit_right)) - (Mad_Corovan.x + (al_get_bitmap_width(Mad_Corovan.bit) / 2)) < 0))
				{
					ELVES[i].x += 2;
					al_draw_bitmap(ELVES[i].bit_right, ELVES[i].x, ELVES[i].y, 0);
				}
				if ((ELVES[i].x - (Mad_Corovan.x + (al_get_bitmap_width(Mad_Corovan.bit) / 2)) > 0))
				{
					ELVES[i].x -= 2;
					al_draw_bitmap(ELVES[i].bit_left, ELVES[i].x, ELVES[i].y, 0);
				}
				if (((ELVES[i].y + al_get_bitmap_height(ELVES[i].bit_down)) - (Mad_Corovan.y + al_get_bitmap_height(Mad_Corovan.bit) / 2)) < 0)
				{
					ELVES[i].y += 2;
					al_draw_bitmap(ELVES[i].bit_down, ELVES[i].x, ELVES[i].y, 0);
				}
				if ((ELVES[i].y - (Mad_Corovan.y + al_get_bitmap_height(Mad_Corovan.bit) / 2)) > 0)
				{
					ELVES[i].y -= 2;
					al_draw_bitmap(ELVES[i].bit_up, ELVES[i].x, ELVES[i].y, 0);
				}
				if (ELVES[i].health <= 0) ELVES[i].death = true;
			}
			else
			{
				al_draw_bitmap(ELVES[i].bit_down, ELVES[i].x, ELVES[i].y, 0);
			}
		}
		if (!_Sham.availability)
		{
			if (((_Sham.x + al_get_bitmap_width(_Sham.bit_right)) - (Mad_Corovan.x + (al_get_bitmap_width(Mad_Corovan.bit) / 2)) < 0))
			{
				_Sham.x += 2;
				al_draw_bitmap(_Sham.bit_right, _Sham.x, _Sham.y, 0);
			}
			if ((_Sham.x - (Mad_Corovan.x + (al_get_bitmap_width(Mad_Corovan.bit) / 2)) > 0))
			{
				_Sham.x -= 2;
				al_draw_bitmap(_Sham.bit_left, _Sham.x, _Sham.y, 0);
			}
			if (((_Sham.y + al_get_bitmap_height(_Sham.bit_down)) - (Mad_Corovan.y + al_get_bitmap_height(Mad_Corovan.bit) / 2)) < 0)
			{
				_Sham.y += 2;
				al_draw_bitmap(_Sham.bit_down, _Sham.x, _Sham.y, 0);
			}
			if ((_Sham.y - (Mad_Corovan.y + al_get_bitmap_height(Mad_Corovan.bit) / 2)) > 0)
			{
				_Sham.y -= 2;
				al_draw_bitmap(_Sham.bit_up, _Sham.x, _Sham.y, 0);
			}
			if (_Sham.health <= 0) _Sham.availability = true;
		}
		else
		{
			al_draw_bitmap(_Sham.bit_down, _Sham.x, _Sham.y, 0);
		}
		if (!_Throll.availability)
		{
			al_draw_bitmap(_Throll.bit, _Throll.x, _Throll.y, 0);
		}
		++Score.millisec;
		if (Score.millisec == 100)
		{
			++Score.sec;
			Score.millisec = 0;
		}
		if (Score.sec == 60)
		{
			++Score.min;
			Score.sec = 0;
		}
		al_draw_textf(font_small, al_map_rgb(0, 0, 0), 30, 70, 0, "Living elves-criminals: %i", alive);
		al_draw_textf(font_small, al_map_rgb(0, 0, 0), 30, 100, 0, "Corovan's health: %i", Mad_Corovan.health);
		al_draw_textf(font_small, al_map_rgb(0, 0, 0), 30, 150, 0, "Time: %i:%i:%i", Score.min, Score.sec, Score.millisec);
	}
	else
	{
		if ((Record.min == 0) && (Record.sec == 0) && (Record.millisec == 0))Record = Score;
		if (Record.min > Score.min) Record = Score;
		if (Record.min == Score.min)
		{
			if (Record.sec > Score.sec) Record = Score;
			if (Record.sec == Score.sec)
			{
				if (Record.millisec > Score.millisec) Record = Score;
			}
		}
		al_stop_timer(timer);
		al_draw_textf(font, al_map_rgb(0, 0, 0), 800, 400, ALLEGRO_ALIGN_CENTER, "Good boy!");
		al_draw_textf(font_small, al_map_rgb(0, 0, 0), 800, 440, ALLEGRO_ALIGN_CENTER, "Press ESC to back main menu");
	}
	al_draw_bitmap(_Unit.bit, _Unit.x, _Unit.y, 0);
	al_flip_display();
	if (Mad_Corovan.x == 1450 || alive == 0)
	{
		al_stop_timer(timer);
		al_draw_textf(font, al_map_rgb(0, 0, 0), 800, 400, ALLEGRO_ALIGN_CENTER, "Looser!");
		al_draw_textf(font_small, al_map_rgb(0, 0, 0), 800, 440, ALLEGRO_ALIGN_CENTER, "Press ESC to back main menu");
		al_flip_display();
	}
}

void elves()//спаун эльфов-разбойников
{
	if (Num_Elves >=0)
	{
		ELVES[Num_Elves].x = _Unit.x;
		ELVES[Num_Elves].y = _Unit.y;
		al_draw_bitmap(ELVES[Num_Elves].bit_up, ELVES[Num_Elves].x, ELVES[Num_Elves].y, 0);
		al_flip_display();
		--Num_Elves;
	}
	else
	{
		al_draw_textf(font_small, al_map_rgb(0, 0, 0), 50, 50, 0, "Empty");
		al_flip_display();
		al_rest(1);
	}
}

//спаун бревна
void key_B()
{
	if (_Baulk.availability)
	{
		_Baulk.x = _Unit.x-al_get_bitmap_width(_Baulk.bit)/2;
		_Baulk.y = _Unit.y - al_get_bitmap_height(_Baulk.bit)/2;
		al_draw_bitmap(_Baulk.bit, _Baulk.x, _Baulk.y, 0);
		al_flip_display();
		_Baulk.availability = false;
	}
	else
	{
		al_draw_textf(font_small, al_map_rgb(0, 0, 0), 50, 50, 0, "Empty");
		al_flip_display();
		al_rest(1);
	}
}

//спаун тролля
void key_T()
{
	if (_Throll.availability)
	{
		_Throll.x = _Unit.x - al_get_bitmap_width(_Throll.bit) / 2;
		_Throll.y = _Unit.y - al_get_bitmap_height(_Throll.bit) / 2;
		al_draw_bitmap(_Throll.bit, _Throll.x, _Throll.y, 0);
		al_flip_display();
		_Throll.availability = false;
	}
	else
	{
		al_draw_textf(font_small, al_map_rgb(0, 0, 0), 50, 50, 0, "Empty");
		al_flip_display();
		al_rest(1);
	}
}

//спаун обманщика
void key_J()
{
	if (_Sham.availability)
	{
		_Sham.x = _Unit.x - al_get_bitmap_width(_Sham.bit_up) / 2;
		_Sham.y = _Unit.y - al_get_bitmap_height(_Sham.bit_up) / 2;
		al_draw_bitmap(_Sham.bit_up, _Sham.x, _Sham.y, 0);
		al_flip_display();
		_Sham.availability = false;
	}
	else
	{
		al_draw_textf(font_small, al_map_rgb(0, 0, 0), 50, 50, 0, "Empty");
		al_flip_display();
		al_rest(1);
	}
}

void key_G()//начало игры
{
	al_draw_bitmap(button1, 1170, 100, 0);
	al_draw_textf(font, al_map_rgb(0, 0, 0), 1230, 130, 0, "1 - Baby");
	al_draw_bitmap(button1, 1170, 250, 0);
	al_draw_textf(font, al_map_rgb(0, 0, 0), 1230, 280, 0, "2 - Easy");
	al_draw_bitmap(button1, 1170, 400, 0);
	al_draw_textf(font, al_map_rgb(0, 0, 0), 1210, 430, 0, "3 - Middle");
	al_draw_bitmap(button1, 1170, 550, 0);
	al_draw_textf(font, al_map_rgb(0, 0, 0), 1230, 580, 0, "4 - Hard");
	al_draw_bitmap(button1, 1170, 700, 0);
	al_draw_textf(font, al_map_rgb(0, 0, 0), 1210, 730, 0, "5 - Madness");
	al_flip_display();
}

void key_R()
{
	al_draw_bitmap(button1, 130, 400, 0);
	al_draw_textf(font, al_map_rgb(0, 0, 0), 170, 430, 0, "%i:%i:%i", Record.min, Record.sec, Record.millisec);
	al_flip_display();
}

int main()
{
	al_display();
	init();
	load();
	start_menu();
	//считывание событий
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_timer_event_source(Timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_start_timer(Timer);//начало таймера
	bool out = false;//флаг для выхода из цикла
	while (!out)//пока не выйдет из игры
	{
		ALLEGRO_EVENT event;//любое событие
		al_wait_for_event(event_queue, &event);//ожидать событие
		if (event.type == ALLEGRO_EVENT_KEY_DOWN)//событие - нажатая клавиша
		{
			switch (event.keyboard.keycode)
			{
			case ALLEGRO_KEY_G:key_G(); break;
			case ALLEGRO_KEY_R:key_R(); break;
			case ALLEGRO_KEY_1:
			{
				Low_Corovan.x = 0;
				Low_Corovan.y = 400;
				Low_Corovan.center.x = al_get_bitmap_width(Low_Corovan.bit);
				Low_Corovan.center.y = al_get_bitmap_height(Low_Corovan.bit);
				_Unit.x = 800;
				_Unit.y = 450;
				_Elf.center.x = al_get_bitmap_width(_Elf.bit_up);
				_Elf.center.y = al_get_bitmap_height(_Elf.bit_up);
				Max_Elves = 6;
				alive = 6;
				Num_Elves = 5;
				ELVES.resize(Max_Elves);
				_Elf.death = false;
				_Elf.health = 300;
				Low_Corovan.health = 700;
				Low_Corovan.damage = 5;
				for (int i = 0; i < Max_Elves; i++)
				{
					ELVES[i] = _Elf;
				}
				Num_Level = 1;
				Num_Key = 1;
				Score.millisec = 0;
				Score.sec = 0;
				Score.min = 0;
				pre_start = true;
				al_start_timer(Timer);
				break;
			}
			case ALLEGRO_KEY_2:
			{
				Easy_Corovan.x = 0;
				Easy_Corovan.y = 400;
				Easy_Corovan.center.x = al_get_bitmap_width(Easy_Corovan.bit);
				Easy_Corovan.center.y = al_get_bitmap_height(Easy_Corovan.bit);
				_Unit.x = 800;
				_Unit.y = 450;
				_Elf.center.x = al_get_bitmap_width(_Elf.bit_up);
				_Elf.center.y = al_get_bitmap_height(_Elf.bit_up);
				Max_Elves = 6;
				alive = 6;
				Num_Elves = 5;
				ELVES.resize(Max_Elves);
				_Elf.death = false;
				_Elf.health = 300;
				_Baulk.availability = true;
				_Baulk.x = 1700;
				_Baulk.y = 0;
				Easy_Corovan.health = 700;
				Easy_Corovan.damage = 5;
				Easy_Corovan.stop = false;
				_Baulk.waiting = 0;
				for (int i = 0; i < Max_Elves; i++)
				{
					ELVES[i] = _Elf;
				}
				Num_Level = 2;
				Num_Key = 2;
				Score.millisec = 0;
				Score.sec = 0;
				Score.min = 0;
				pre_start = true;
				al_start_timer(Timer);
				break;
			}
			case ALLEGRO_KEY_3:
			{
				Middle_Corovan.x = 0;
				Middle_Corovan.y = 400;
				Middle_Corovan.center.x = al_get_bitmap_width(Middle_Corovan.bit);
				Middle_Corovan.center.y = al_get_bitmap_height(Middle_Corovan.bit);
				_Unit.x = 800;
				_Unit.y = 450;
				_Elf.center.x = al_get_bitmap_width(_Elf.bit_up);
				_Elf.center.y = al_get_bitmap_height(_Elf.bit_up);
				Max_Elves = 6;
				alive = 6;
				Num_Elves = 5;
				ELVES.resize(Max_Elves);
				_Elf.death = false;
				_Elf.health = 300;
				_Baulk.availability = true;
				_Baulk.x = 1700;
				_Baulk.y = 0;
				_Throll.availability = true;
				_Throll.x = 1700;
				_Throll.y = 0;
				Middle_Corovan.health = 900;
				Middle_Corovan.damage = 5;
				Middle_Corovan.stop = false;
				_Baulk.waiting = 0;
				_Throll.waiting_sec = -1;
				_Throll.waiting_millisec = -1;
				for (int i = 0; i < Max_Elves; i++)
				{
					ELVES[i] = _Elf;
				}
				Num_Level = 3;
				Num_Key = 3;
				Score.millisec = 0;
				Score.sec = 0;
				Score.min = 0;
				pre_start = true;
				al_start_timer(Timer);
				break;
			}
			case ALLEGRO_KEY_4:
			{
				Hard_Corovan.x = 50;
				Hard_Corovan.y = 750;
				Hard_Corovan.center.x = al_get_bitmap_width(Hard_Corovan.bit)/2;
				Hard_Corovan.center.y = al_get_bitmap_height(Hard_Corovan.bit)/2;
				_Unit.x = 800;
				_Unit.y = 450;
				_Elf.center.x = al_get_bitmap_width(_Elf.bit_up);
				_Elf.center.y = al_get_bitmap_height(_Elf.bit_up);
				Max_Elves = 2;
				alive = 2;
				Num_Elves = 1;
				ELVES.resize(Max_Elves);
				_Elf.death = false;
				_Elf.health = 300;
				_Baulk.availability = true;
				_Baulk.x = 1700;
				_Baulk.y = 0;
				_Throll.availability = true;
				_Throll.x = 1700;
				_Throll.y = 0;
				_Sham.availability = true;
				_Sham.x = 1700;
				_Sham.y = 0;
				_Sham.health = 300;
				Hard_Corovan.health = 1000;
				Hard_Corovan.damage = 5;
				Hard_Corovan.stop = false;
				_Baulk.waiting = 0;
				_Throll.waiting_sec = -1;
				_Throll.waiting_millisec = -1;
				_Sham.waiting_sec = -1;
				for (int i = 0; i < Max_Elves; i++)
				{
					ELVES[i] = _Elf;
				}
				Num_Level = 4;
				Num_Key = 4;
				Score.millisec = 0;
				Score.sec = 0;
				Score.min = 0;
				pre_start = true;
				al_start_timer(Timer);
				break;
			}
			case ALLEGRO_KEY_5:
			{
				Mad_Corovan.x = 0;
				Mad_Corovan.y = 400;
				_Unit.x = 800;
				_Unit.y = 450;
				_Elf.center.x = al_get_bitmap_width(_Elf.bit_up);
				_Elf.center.y = al_get_bitmap_height(_Elf.bit_up);
				Max_Elves = 6;
				alive = 6;
				Num_Elves = 5;
				ELVES.resize(Max_Elves);
				_Elf.death = false;
				_Elf.health = 300;
				_Baulk.availability = true;
				_Baulk.x = 1700;
				_Baulk.y = 0;
				_Throll.availability = true;
				_Throll.x = 1700;
				_Throll.y = 0;
				_Sham.availability = true;
				_Sham.x = 1700;
				_Sham.y = 0;
				_Sham.health = 300;
				Mad_Corovan.health = 1900;
				Mad_Corovan.damage = 6;
				Mad_Corovan.stop = false;
				_Baulk.waiting = 0;
				_Throll.waiting_sec = -1;
				_Throll.waiting_millisec = -1;
				_Sham.waiting_sec = -1;
				for (int i = 0; i < Max_Elves; i++)
				{
					ELVES[i] = _Elf;
				}
				Num_Level = 5;
				Num_Key = 5;
				Score.millisec = 0;
				Score.sec = 0;
				Score.min = 0;
				pre_start = true;
				al_start_timer(Timer);
				break;
			}
			case ALLEGRO_KEY_DOWN: direction = DOWN; spawn(); break;
			case ALLEGRO_KEY_UP: direction = UP; spawn(); break;
			case ALLEGRO_KEY_RIGHT: direction = RIGHT; spawn(); break;
			case ALLEGRO_KEY_LEFT: direction = LEFT; spawn(); break;
			case ALLEGRO_KEY_S: elves(); break;
			case ALLEGRO_KEY_B: key_B(); break;
			case ALLEGRO_KEY_T: key_T(); break;
			case ALLEGRO_KEY_J: key_J(); break;
			case ALLEGRO_KEY_ENTER:
			{
				al_stop_timer(Timer);
				al_start_timer(timer);
				break;
			}
			case ALLEGRO_KEY_ESCAPE:
			{
				start_menu();
				break;
			}
			case ALLEGRO_KEY_X: out = true; break;
			}
		}

		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)//событие - закрытие дисплея
		{
			out = true;
		}

		if (event.type == ALLEGRO_EVENT_TIMER)//событие - таймер
		{
			if (event.timer.source == timer)
			{
				redraw = true;
			}
			if (event.timer.source == Timer)
			{
				pre_start = true;
			}
		}
		if (redraw && al_is_event_queue_empty(event_queue))//произошедшее событие
		{
			redraw = false;
			switch (Num_Level)
			{
			case 1://Первый уровень
				first_level(); break;
			case 2:
				second_level(); break;
			case 3:
				third_level(); break;
			case 4:
				four_level(); break;
			case 5:
				fifth_level(); break;
			}
		}
		if (pre_start && al_is_event_queue_empty(event_queue))
		{
			pre_start = false;
			switch (Num_Key)
			{
			case 1:
				key_1(); break;
			case 2:
				key_2(); break;
			case 3:
				key_3(); break;
			case 4:
				key_4(); break;
			case 5:
				key_5(); break;
			}
		}
	}

	//очищение
	al_destroy_bitmap(Low_Corovan.bit);
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

	return 0;
};
