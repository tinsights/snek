/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snek.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjegades <tjegades@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 12:49:58 by tjegades          #+#    #+#             */
/*   Updated: 2024/11/28 14:52:43 by tjegades         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "snek.h"

enum dir {UP, DOWN, LEFT, RIGHT};

typedef struct s_snek {
	int x;
	int y;
	int len;
	int dir;
} t_snek;

void draw(t_snek *snek) {
	mvaddch(snek->y, snek->x, '*');
}

void handle_input(int ch, t_snek* snek) {

	switch (ch) {
		case KEY_UP:
			snek->y -= 1;
			break;
		case KEY_DOWN:
			snek->y += 1;
			break;
		case KEY_LEFT:
			snek->x -= 1;
			break;
		case KEY_RIGHT:
			snek->x += 1;
			break;
		default:
			break;		
	}
	if (snek->x < 0)
		snek->x = 0;
	if (snek->y < 0)
		snek->y = 0;
	draw(snek);
}

int main(void) {
	int ch;

	t_snek snek = {0, 0, 5, RIGHT};

	initscr();				// Start curses mode
	cbreak();				// disable line buffering, read raw input
	noecho();				// dont echo input to term
	keypad(stdscr, TRUE);	// enable arrow keys
	// nodelay(stdscr, TRUE);	// nonblocking getch

	while (true) {
		ch = getch();
		if (ch == 'q' || ch == 27)
			break;
		handle_input(ch, &snek);
		// usleep(10000);
		refresh();
	}
	endwin();
}