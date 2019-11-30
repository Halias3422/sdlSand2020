#include "../includes/sand.h"

void					clean_before_exiting(t_sdl *sdl, t_object *object,
						t_screen_content ***screen_content)
{
	int	i = 0;

	SDL_DestroyTexture(object->sand->texture);
	SDL_DestroyRenderer(sdl->renderer);
	SDL_DestroyWindow(sdl->window);
	IMG_Quit();
	SDL_Quit();
	if (screen_content)
	{
		for (int y = 0; y < sdl->window_h; y++)
		{
			for (int x = 0; x < sdl->window_w; x++)
			{
				i++;
				free(screen_content[y][x]);
			}
			free(screen_content[y]);
		}
		printf("i = %d\n", i);
		free(screen_content);
	}
	free(object->sand);
}

void					init_program(t_sdl *sdl, t_object *object)
{
	SDL_DisplayMode		display;


	sdl->window = NULL;
	sdl->renderer = NULL;
	sdl->window_h = -1;
	sdl->window_w = -1;
	SDL_init_window(sdl);
	SDL_init_renderer(sdl);
	SDL_init_img(sdl);

	object->sand = (t_sand*)malloc(sizeof(t_sand));
	object->sand->width = 1;
	object->sand->height = 1;
	object->sand->texture = SDL_load_texture(sdl, sdl->renderer,
			object->sand->texture, "img/sand.png");
	if (SDL_GetDesktopDisplayMode(0, &display) != 0)
		failure_exit_program("Getting display mode", sdl);
	sdl->window_h = display.h;
	sdl->window_w = display.w;
}

void					init_screen_content_struct(t_screen_content ***screen_content,
						t_sdl *sdl)
{
	for (int y = 0; y < sdl->window_h; y++)
	{
		screen_content[y] = (t_screen_content**)malloc(sizeof(t_screen_content*) *
				sdl->window_w);
		for (int x = 0; x < sdl->window_w; x++)
		{
			screen_content[y][x] = (t_screen_content*)malloc(sizeof(t_screen_content));
			screen_content[y][x]->filled = 0;
		}
	}
}

void					init_display(t_sdl *sdl)
{
	SDL_apply_color_to_renderer(black, sdl);
	SDL_render_clear(sdl, sdl->renderer);
	SDL_RenderPresent(sdl->renderer);
}

int						main(void)
{
	t_sdl				sdl;
	t_object			object;
	t_screen_content	***screen_content;


	init_program(&sdl, &object);
	screen_content = (t_screen_content***)malloc(sizeof(t_screen_content**) *
			sdl.window_h);
	init_screen_content_struct(screen_content, &sdl);
	init_display(&sdl);
	game_loop(&sdl, &object, screen_content);

	clean_before_exiting(&sdl, &object, screen_content);
	return (0);
}
