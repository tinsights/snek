/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snek.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjegades <tjegades@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 12:49:58 by tjegades          #+#    #+#             */
/*   Updated: 2024/11/28 15:35:23 by tjegades         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "snek.hpp"

enum dir {UP, DOWN, LEFT, RIGHT};

typedef struct s_point {
	int x;
	int y;
} t_point;

typedef struct s_snek {
	t_point head;
	int len;
	int dir;
} t_snek;

void draw(t_snek *snek) {
	switch (snek->dir) {
		case UP:
			snek->head.y -= 1;
			break;
		case DOWN:
			snek->head.y += 1;
			break;
		case LEFT:
			snek->head.x -= 1;
			break;
		case RIGHT:
			snek->head.x += 1;
			break;
	}
	if (snek->head.x < 0)
		snek->head.x = 0;
	if (snek->head.y < 0)
		snek->head.y = 0;
	
	mvaddch(snek->head.y, snek->head.x, '*');
}

void handle_input(int ch, t_snek* snek) {

	switch (ch) {
		case KEY_UP:
			if (snek->dir != DOWN)
				snek->dir = UP;
			break;
		case KEY_DOWN:
			if (snek->dir != UP)
				snek->dir = DOWN;
			break;
		case KEY_LEFT:
			if (snek->dir != RIGHT)
				snek->dir = LEFT;
			break;
		case KEY_RIGHT:
			if (snek->dir != LEFT)
				snek->dir = RIGHT;
			break;
		default:
			break;		
	}
}

int main(void) {
	int ch;

	t_snek snek = {{0, 0}, 5, RIGHT};

	initscr();				// Start curses mode
	cbreak();				// disable line buffering, read raw input
	noecho();				// dont echo input to term
	keypad(stdscr, TRUE);	// enable arrow keys
	nodelay(stdscr, TRUE);	// nonblocking getch

	while (true) {
		ch = getch();
		if (ch == 'q' || ch == 27)
			break;
		handle_input(ch, &snek);
		draw(&snek);
		refresh();
		usleep(500000);
	}
	endwin();
}