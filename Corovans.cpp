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
	_Elf.bit_death = al_load_bitmap("Bits/Elf_death.PNG");
	al_convert_mask_to_alpha(_Elf.bit_left, al_map_rgb(66, 93, 41));
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
	al_draw_textf(font_small, al_map_rgb(0, 0, 0), 1520, 70, ALLEGRO_ALIGN_RIGHT, "S - spawn elves-criminals");
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
	al_draw_bitmap(Low_Corovan.bit, 0, 400, 0);
	al_flip_display();
	al_start_timer(timer);
}

void key_3()//третий уровень
{
	al_draw_bitmap(Map3, 0, 0, 0);
	al_draw_bitmap(Low_Corovan.bit, 0, 400, 0);
	al_flip_display();
}

void key_4()//четвертый уровень
{
	al_draw_bitmap(Map4, 0, 0, 0);
	al_draw_bitmap(Low_Corovan.bit, 0, 400, 0);
	al_flip_display();
}

void key_5()//пятый уровень
{
	al_draw_bitmap(Map5, 0, 0, 0);
	al_draw_bitmap(Low_Corovan.bit, 0, 400, 0);
	al_flip_display();
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
			case ALLEGRO_KEY_DOWN: direction = DOWN; spawn(); break;
			case ALLEGRO_KEY_UP: direction = UP; spawn(); break;
			case ALLEGRO_KEY_RIGHT: direction = RIGHT; spawn(); break;
			case ALLEGRO_KEY_LEFT: direction = LEFT; spawn(); break;
			case ALLEGRO_KEY_S: elves(); break;
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
			}
			
		}
		if (pre_start && al_is_event_queue_empty(event_queue))
		{
			pre_start = false;
			switch (Num_Key)
			{
			case 1:
				key_1(); break;
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
