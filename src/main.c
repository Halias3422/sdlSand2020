#include "sand.h"

void			clean_before_exiting(t_sdl *sdl, t_pixel ***pixel)
{
	SDL_DestroyRenderer(sdl->renderer);
	SDL_DestroyWindow(sdl->window);
	SDL_DestroyTexture(sdl->object->sand);
	free (sdl->object);
	free(sdl);
	IMG_Quit();
	SDL_Quit();
	if (pixel)
	{
		for (int y = 0; y < 1080; y++)
		{
			for (int x = 0; x < 1920; x++)
				free(pixel[y][x]);
			free(pixel[y]);
		}
		free(pixel);
	}
}

void			init_pixel_tab(t_pixel ***pixel)
{
	for (int y = 0; y < 1080; y++)
	{
		pixel[y] = (t_pixel**)malloc(sizeof(t_pixel*) * 1920);
		for (int x = 0; x < 1920; x++)
		{
			pixel[y][x] = (t_pixel*)malloc(sizeof(t_pixel));
			pixel[y][x]->filled = 0;
		}
	}
}

void			update_sand_on_screen(t_sdl *sdl, t_pixel ***pixel)
{
	SDL_Rect	dst = {0, 0, 2, 2};

	srand(time(NULL));
	SDL_render_clear(sdl, sdl->renderer);
	printf("je rentre\n");
	for (int y = 0; y < 1000; y++)
	{
		for (int x = 0; x < 1920; x++)
		{
			if (y < 500 && pixel[y][x]->filled == 1 && pixel[y + 2][x]->filled == 0)
			{
				pixel[y][x]->filled = 0;
				if (pixel[y + 3][x]->filled == 0 && pixel[y + 4][x]->filled == 0)
					pixel[y + 4][x] ->filled = 2;
				else if (pixel[y + 3][x]->filled == 0)
					pixel[y + 3][x]->filled = 2;
				else
					pixel[y + 2][x]->filled = 2;
				dst.x = x;
				dst.y = y;
			}
			else if (x > 0 && x < 1079 && y < 500 && pixel[y][x]->filled == 1 && pixel[y + 2][x]->filled == 1 && (pixel[y + 2][x - 2]->filled == 0 || pixel[y + 2][x + 2]->filled == 0))
			{
				if (pixel[y + 2][x - 2]->filled == 0 && pixel[y + 2][x + 2] == 0)
				{
					int	random = rand() % 2;
					if (random == 0)
						pixel[y + 2][x - 2]->filled = 2;
					else
						pixel[y + 2][x + 2]->filled = 2;
				}
				else if (pixel[y + 2][x - 2]->filled == 0)
					pixel[y + 2][x - 2]->filled = 2;
				else if (pixel[y + 2][x + 2]->filled == 0)
					pixel[y + 2][x + 2]->filled = 2;
				pixel[y][x]->filled = 0;
			}
			if (pixel[y][x]->filled == 1 || pixel[y][x] ->filled== 2)
			{
				dst.x = x;
				dst.y = y;
				SDL_render_copy(sdl, sdl->renderer, sdl->object->sand, NULL, &dst);
			}
		}
	}
	printf("je sors\n");
	for (int y = 0; y < 1080; y++)
	{
		for (int x = 0; x < 1920; x++)
		{
			if (y < 1080 && pixel[y][x]->filled == 2)
			{
				pixel[y][x]->filled = 1;
			}
		}
	}
	SDL_RenderPresent(sdl->renderer);
}

int				main(void)
{
	t_sdl		*sdl;
	SDL_DisplayMode	display;
	SDL_Color	black = {0, 0, 0, 255};
	const		Uint8 *state;
	SDL_Event	event;
	int			quit = 0;
	SDL_Rect	dst = {0, 0, 1, 1};
	t_pixel		***pixel;

	sdl = (t_sdl*)malloc(sizeof(t_sdl));
	sdl->object = (t_object*)malloc(sizeof(t_object));
	SDL_init_window(sdl);
	SDL_init_renderer(sdl);
	SDL_init_img(sdl);
	sdl->object->sand = SDL_load_texture(sdl, sdl->renderer, sdl->object->sand, "img/sand.png");
	if (SDL_GetDesktopDisplayMode(0, &display) != 0)
		failure_exit_program("Getting display mode", sdl);
	sdl->window_h = display.h;
	sdl->window_w = display.w;
	pixel = (t_pixel***)malloc(sizeof(t_pixel**) * 1080);
	init_pixel_tab(pixel);
	SDL_apply_color_to_renderer(black, sdl);
	SDL_render_clear(sdl, sdl->renderer);
	SDL_RenderPresent(sdl->renderer);
	while (quit != 1)
	{
		state = SDL_GetKeyboardState(NULL);
		if (SDL_PollEvent(&event) && (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEMOTION))
		{
			if (SDL_GetMouseState(&dst.x, &dst.y) & SDL_BUTTON(SDL_BUTTON_LEFT))
				pixel[dst.y][dst.x]->filled = 1;
		}
		if (state[SDL_SCANCODE_ESCAPE])
			quit = 1;
		update_sand_on_screen(sdl, pixel);
		SDL_Delay(1);
	}
	clean_before_exiting(sdl, pixel);
}
