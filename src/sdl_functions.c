#include "../includes/sand.h"

void			failure_exit_program(char *error, t_sdl *sdl)
{
	fprintf(stderr, "ERROR %s (%s)\n", error, SDL_GetError());
	if (!sdl)
		exit(EXIT_FAILURE);
	clean_before_exiting(sdl, NULL);
	exit(EXIT_FAILURE);
}

void			SDL_init_window(t_sdl *sdl)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
			failure_exit_program("Initialization SDL WINDOW", sdl);
	if ((sdl->window = SDL_CreateWindow("SUCH AMAZING TETRIS, SUCH WOW",
				SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920, 1080,
				SDL_WINDOW_SHOWN)) == NULL)
		failure_exit_program("Creating sdl->window", sdl);
}

void			SDL_init_renderer(t_sdl *sdl)
{
	if ((sdl->renderer = SDL_CreateRenderer(sdl->window, -1,
					SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE)) == NULL)
		failure_exit_program("Creating Window Renderer", sdl);
}

void			SDL_apply_color_to_renderer(SDL_Color rgba, t_sdl *sdl)
{
	if ((SDL_SetRenderDrawColor(sdl->renderer, rgba.r, rgba.g, rgba.b, rgba.a))
			!= 0)
		failure_exit_program("Rendering Color", sdl);
}

void			SDL_init_img(t_sdl *sdl)
{
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
		failure_exit_program("Initializing IMAGES", sdl);
}

SDL_Texture		*SDL_load_texture(t_sdl *sdl, SDL_Renderer *renderer,
				SDL_Texture *texture, char *path)
{
	if ((texture = IMG_LoadTexture(renderer, path)) == NULL)
		failure_exit_program("Loading Image on Texture", sdl);
	return (texture);
}

void			SDL_render_clear(t_sdl *sdl, SDL_Renderer *renderer)
{
	if ((SDL_RenderClear(renderer)) != 0)
		failure_exit_program("Clearing Render With Color", sdl);
}

void			SDL_render_copy(t_sdl *sdl, SDL_Renderer *renderer,
				SDL_Texture *texture, SDL_Rect *src, SDL_Rect *dest)
{
	if (SDL_RenderCopy(renderer, texture, src, dest) != 0)
		failure_exit_program("Rendering Copy Of Texture", sdl);
}

void			SDL_render_target(t_sdl *sdl, SDL_Renderer *renderer,
				SDL_Texture *texture)
{
	if (SDL_SetRenderTarget(renderer, texture) != 0)
		failure_exit_program("Setting Texture as Render Target", sdl);
}
