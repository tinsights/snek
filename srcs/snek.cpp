/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snek.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjegades <tjegades@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 12:49:58 by tjegades          #+#    #+#             */
/*   Updated: 2024/11/29 11:37:25 by tjegades         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "snek.hpp"
int ref_rate = 200000;
#define SNEKLEN 8
enum e_dir {UP, DOWN, LEFT, RIGHT};

typedef struct s_point {
	int x;
	int y;
} t_point;

typedef struct s_snek {
	t_point 		head;
	t_point			tail;
	int				len;
	e_dir			dir;
	deque<e_dir>	moves;
} t_snek;


void drop_food(void) {
	int x = rand() % COLS;
	int y = rand() % LINES;

	if (mvinch(y, x) == ' ')
		mvaddch(y, x, 'o');
	else
		drop_food();
}

void draw(t_snek *snek) {
	snek->moves.push_back(snek->dir);

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
		snek->head.x = COLS - 1;
	else if (snek->head.x >= COLS)
		snek->head.x = 0;
	if (snek->head.y < 0)
		snek->head.y = LINES - 1;
	else if (snek->head.y >= LINES)
		snek->head.y = 0;
	
	int next = mvinch(snek->head.y, snek->head.x);
	if (next == '*') {
		endwin();
		exit(0);
	}
		
	if (next == 'o') {
		drop_food();
		ref_rate *= 0.95;
	}
	else {
		e_dir tail_dir = snek->moves.front();
		switch (tail_dir) {
			case UP:
				snek->tail.y -= 1;
				break;
			case DOWN:
				snek->tail.y += 1;
				break;
			case LEFT:
				snek->tail.x -= 1;
				break;
			case RIGHT:
				snek->tail.x += 1;
				break;
		}
		if (snek->tail.x < 0)
			snek->tail.x = COLS - 1;
		else if (snek->tail.x >= COLS)
			snek->tail.x = 0;
		if (snek->tail.y < 0)
			snek->tail.y = LINES - 1;
		else if (snek->tail.y >= LINES)
			snek->tail.y = 0;
		mvaddch(snek->tail.y, snek->tail.x, ' ');
		snek->moves.pop_front();
	}
	mvaddch(snek->head.y, snek->head.x, '*');
	
}

void handle_input(int ch, t_snek* snek) {
	switch (ch) {
		case KEY_UP:
			if (snek->dir != UP)
				ref_rate *= 1.5; // slower
			else
				ref_rate /= 1.5;
			if (snek->dir != DOWN)
				snek->dir = UP;
			break;
		case KEY_DOWN:
			if (snek->dir != DOWN)
				ref_rate *= 1.5; // slower
			else
				ref_rate /= 1.5;
			if (snek->dir != UP)
				snek->dir = DOWN;
			break;
		case KEY_LEFT:
			if (snek->dir == RIGHT)
				ref_rate *= 1.5; // slower
			else
				ref_rate /= 1.5;
			if (snek->dir != RIGHT)
				snek->dir = LEFT;
			break;
		case KEY_RIGHT:
			if (snek->dir == LEFT)
				ref_rate *= 1.5; // slower
			else
				ref_rate /= 1.5;
			if (snek->dir != LEFT)
				snek->dir = RIGHT;
			break;
		default:
			break;		
	}
}



int main(void) {
	int ch;

	srand(time(NULL)); // for food
	
	initscr();				// Start curses mode
	cbreak();				// disable line buffering, read raw input
	noecho();				// dont echo input to term
	keypad(stdscr, TRUE);	// enable arrow keys
	nodelay(stdscr, TRUE);	// nonblocking getch
	
	t_snek snek = {
		{0, 0},
		{COLS - SNEKLEN, 0},
		SNEKLEN,
		RIGHT,
		deque<e_dir>(SNEKLEN, RIGHT)
		};

	drop_food();
	while (true) {
		ch = getch();
		if (ch == 'q' || ch == 27)
			break;
		handle_input(ch, &snek);
		draw(&snek);
		refresh();
		usleep(ref_rate);
	}
	endwin();
}