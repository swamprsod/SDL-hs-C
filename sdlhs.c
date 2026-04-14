#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>

//preobrazovano via xxd -i /usr/share/fonts/TerminusTTF/ter-u12n.otb > font_termh01234.h
#include "font_termh01234.h"

#include <signal.h> // debug
static int hstrue=1;

void varsigint()
{
hstrue=0;
}

int main() 
{

signal(SIGINT, varsigint);

SDL_Init(SDL_INIT_VIDEO);
TTF_Init();
SDL_Window *hshs = SDL_CreateWindow("hshs", 100, 100, 900, 700, 0);
SDL_Renderer *hshsren=SDL_CreateRenderer(hshs, -1, SDL_RENDERER_ACCELERATED);

SDL_RWops *rw = SDL_RWFromConstMem(ter_u12n_otb, ter_u12n_otb_len);
if (!rw)
{
printf("rw umer\n");
}
TTF_Font *text = TTF_OpenFontRW(rw, 1, 12);
if (!text)
{
printf("font (text) umer tak kak %s\n", TTF_GetError());
}

// x y w h
SDL_Rect hsbtn1={790, 10, 100, 40};
SDL_Rect hsbtn2={790, 60, 100, 40};

SDL_Color white={255,255,255,255};

// hsbtn1
SDL_Surface *srf1 = TTF_RenderUTF8_Blended(text, "cpu model", white);
SDL_Texture *texr1 = SDL_CreateTextureFromSurface(hshsren, srf1);

SDL_Rect texr1_rect=
{
hsbtn1.x+(hsbtn1.w - srf1->w)/2,
hsbtn1.y+(hsbtn1.h - srf1->h)/2,
srf1->w,
srf1->h,
};
SDL_FreeSurface(srf1);

//hsbtn2
SDL_Surface *srf2 = TTF_RenderUTF8_Blended(text, "ram", white);
SDL_Texture *texr2 = SDL_CreateTextureFromSurface(hshsren, srf1);

SDL_Rect texr2_rect=
{
hsbtn2.x+(hsbtn2.w - srf1->w)/2,
hsbtn2.y+(hsbtn2.h - srf1->h)/2,
srf2->w,
srf2->h,
};
SDL_FreeSurface(srf2);
//hsbtn3


SDL_Event evnt;

while (hstrue)
{
// obrabotka klikov
while (SDL_PollEvent(&evnt))
{
if (evnt.type==SDL_MOUSEBUTTONDOWN && evnt.button.button==SDL_BUTTON_LEFT)
{
int x=evnt.button.x;
int y=evnt.button.y;

if (x > hsbtn1.x && x < hsbtn1.x + hsbtn1.w && y > hsbtn1.y && y < hsbtn1.y + hsbtn1.h)
{
system("cat /proc/cpuinfo | grep \"model name\" | head -n 1 | cut -d':' -f2 | sed 's/model name\\s*//'");
}
if (x > hsbtn2.x && x < hsbtn2.x + hsbtn2.w && y > hsbtn2.y && y < hsbtn2.y + hsbtn2.h)
{
printf("2 2 2text from hsbtn2 test!!\n");
}
}
}

SDL_SetRenderDrawColor(hshsren, 172, 172, 172, 255);
SDL_RenderClear(hshsren);

SDL_SetRenderDrawColor(hshsren, 100, 100, 100, 255);
SDL_RenderFillRect(hshsren, &hsbtn1);
SDL_RenderFillRect(hshsren, &hsbtn2);

SDL_SetRenderDrawColor(hshsren, 0,0,0,255);
SDL_RenderDrawRect(hshsren, &hsbtn1);
SDL_RenderDrawRect(hshsren, &hsbtn2);
SDL_RenderCopy(hshsren, texr1, NULL, &texr1_rect);
SDL_RenderCopy(hshsren, texr2, NULL, &texr2_rect);


SDL_RenderPresent(hshsren);
SDL_Delay(16);
}
SDL_DestroyTexture(texr1);
SDL_DestroyTexture(texr2);
TTF_CloseFont(text);
SDL_DestroyRenderer(hshsren);
SDL_DestroyWindow(hshs);
TTF_Quit();
SDL_Quit();
return 0;
}
