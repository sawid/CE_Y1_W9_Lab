#include<stdio.h>
#include<windows.h>
#include<time.h>
#include<conio.h>
int starX[20] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
int starY[20] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
int score = 0;
int randStarX(int j)
{
	int i;
	srand(time(NULL) + j);
	i = rand()%100;
	while (i < 10 || i > 70)
	{
		i = rand() % 100;
	}
	return i;
}
int randStarY(int j)
{
	int i;
	srand(time(NULL) + j);
	i = rand() % 10;
	while (i < 2 || i > 5)
	{
		i = rand() % 10;
	}
	return i;
}
char cursor(int x, int y) {
	HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
	char buf[2]; COORD c = { x,y }; DWORD num_read;
	if (
		!ReadConsoleOutputCharacter(hStd, (LPTSTR)buf, 1, c, (LPDWORD)&num_read))

		return '\0';
	else
		return buf[0];

}
void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void draw_ship(int x, int y)
{
	gotoxy(x, y); printf(" <-0-> ");
}
void draw_star(int x, int y)
{
	gotoxy(x, y); printf("*");
}
void draw_bullet(int x, int y)
{
	gotoxy(x, y); printf("^");
}
void clear_bullet(int x, int y)
{
	gotoxy(x, y); printf(" ");
}
void show_score(int score) {
	gotoxy(70, 0); printf("Score is %d",score);
}
int main()
{
	char ch = '.';
	int x = 38, y = 20;
	int bx, by, i;
	int bullet = 0;
	draw_ship(x, y);
	do {
		show_score(score);
		for (int i = 0; i < 20; i++)
		{
			if (starX[i] == 0 && starY[i] == 0)
			{
				int tx = randStarX(i), ty = randStarY(i);
				for (int j = 0; j < 20; j++)
				{
					if (tx == starX[j] && ty == starY[j])
					{
						tx = randStarX(j), ty = randStarY(j);
						j = 0;
					}
				}
				starX[i] = tx;
				starY[i] = ty;
				draw_star(starX[i], starY[i]);
			}
		}
		if (_kbhit()) {
			ch = _getch();
			if (ch == 'a') { draw_ship(--x, y); }
			if (ch == 's') { draw_ship(++x, y); }
			if (bullet != 1 && ch == ' ') { bullet = 1; bx = x + 3; by = y - 1; }
			fflush(stdin);
		}
		if (bullet == 1) {

			clear_bullet(bx, by);
			if (by == 2) { bullet = 0; }
			else {
				if (cursor(bx, by - 1) == '*')
				{
					Beep(2223, 1);
					score++;
					bullet = 0;
					for (int i = 0; i < 20; i++)
					{
						if (starX[i] == bx && starY[i] == by - 1)
						{
							clear_bullet(bx,by - 1);
							starX[i] = 0;
							starY[i] = 0;
						}
					}
				}
				else
				{
					draw_bullet(bx, --by);
				}
			}

		}
		 
		Sleep(100);
	} while (ch != 'x');
	return 0;
}