#include "Function.h"
void DrawString(SDL_Surface *screen, int x, int y, const char *text, SDL_Surface *charset) {
	int px, py, c;
	SDL_Rect s, d;
	s.w = 8;
	s.h = 8;
	d.w = 8;
	d.h = 8;
	while(*text) {
		c = *text & 255;
		px = (c % 16) * 8;
		py = (c / 16) * 8;
		s.x = px;
		s.y = py;
		d.x = x;
		d.y = y;
		SDL_BlitSurface(charset, &s, screen, &d);
		x += 8;
		text++;
	};
};
void DrawPixel(SDL_Surface *surface, int x, int y, Uint32 color) {
	int bpp = surface->format->BytesPerPixel;
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
	*(Uint32 *)p = color;
};
void DrawLine(SDL_Surface *screen, int x, int y, int l, int dx, int dy, Uint32 color) {
	for(int i = 0; i < l; i++) {
		DrawPixel(screen, x, y, color);
		x += dx;
		y += dy;
		};
	};

// vẽ hcn kích thước 1-k
void DrawRectangle(SDL_Surface *screen, int x, int y, int l, int k,
                   Uint32 outlineColor, Uint32 fillColor) {
	int i;
	DrawLine(screen, x, y, k, 0, 1, outlineColor);
	DrawLine(screen, x + l - 1, y, k, 0, 1, outlineColor);
	DrawLine(screen, x, y, l, 1, 0, outlineColor);
	DrawLine(screen, x, y + k - 1, l, 1, 0, outlineColor);
	for(i = y + 1; i < y + k - 1; i++)
		DrawLine(screen, x + 1, i, l - 2, 1, 0, fillColor);
	};
void DrawPoint(SDL_Surface *screen, int X, int Y, int width, const char *number, SDL_Surface *charset) {
	int length = strlen(number);
	DrawString(screen, (X + width / 2) - length*4, Y + width / 2, number, charset);
}
void DrawBoard(SDL_Surface *screen, int **tab, int size, Uint32 outlineColor, Uint32 fillColor, SDL_Surface *charset) {
	int width = (BOARD_WIDTH / size) - 2;
	int X, Y;
	char number[5];
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			X = BOARD_X + (BOARD_WIDTH / size)*i;
			Y = BOARD_Y + (BOARD_WIDTH / size)*j;
			switch(tab[i][j]){
				case 2:
					DrawRectangle(screen, Y, X, width, width, outlineColor, SDL_MapRGB(screen->format, 168, 208, 216));
					break;
				case 4:
					DrawRectangle(screen, Y, X, width, width, outlineColor, SDL_MapRGB(screen->format, 232, 186, 189));
					break;
				case 8:
					DrawRectangle(screen, Y, X, width, width, outlineColor, SDL_MapRGB(screen->format, 164, 206, 158));
					break;
				case 16:
					DrawRectangle(screen, Y, X, width, width, outlineColor, SDL_MapRGB(screen->format, 243, 223, 126));
					break;
				case 32:
					DrawRectangle(screen, Y, X, width, width, outlineColor, SDL_MapRGB(screen->format, 219, 172, 188));
					break;
				case 64:
					DrawRectangle(screen, Y, X, width, width, outlineColor, SDL_MapRGB(screen->format, 252, 129, 178));
					break;
				case 128:
					DrawRectangle(screen, Y, X, width, width, outlineColor, SDL_MapRGB(screen->format, 228, 89, 65));
					break;
				case 256:
					DrawRectangle(screen, Y, X, width, width, outlineColor, SDL_MapRGB(screen->format, 138, 104, 168));
					break;
				case 512:
					DrawRectangle(screen, Y, X, width, width, outlineColor, SDL_MapRGB(screen->format, 129, 232, 225));
					break;
				case 1024:
					DrawRectangle(screen, Y, X, width, width, outlineColor, SDL_MapRGB(screen->format, 237, 213, 227));
					break;
				case 2048:
					DrawRectangle(screen, Y, X, width, width, outlineColor, SDL_MapRGB(screen->format, 197, 192, 158));
					break;
				default:
					DrawRectangle(screen, Y, X, width, width, outlineColor, SDL_MapRGB(screen->format, 127, 127, 127));
					break;

			}
			if(tab[i][j] == 0) sprintf(number, "");
			else sprintf(number, "%d", tab[i][j]);
			DrawPoint(screen, Y, X, width, number, charset);
		}
	}
}

void DrawScore(SDL_Surface *screen, unsigned int score, SDL_Surface *charset) {
	int X = BOARD_X;
	int Y = BOARD_Y + BOARD_WIDTH + 100;
	int width = 40;
	char number[18];
	sprintf(number, "score: %u", score);
	DrawPoint(screen, Y, X, width, number, charset);
}