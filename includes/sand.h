#ifndef SAND_H
# define SAND_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>

typedef struct		s_object
{
	SDL_Texture		*sand;
}					t_object;

typedef struct		s_pixel
{
	int				filled;
}					t_pixel;

typedef struct		s_sdl
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	int				window_h;
	int				window_w;
	struct s_object	*object;
}					t_sdl;

//	MAIN_C

void			clean_before_exiting(t_sdl *sdl, t_pixel ***pixel);

//	SDL_FUNCTIONS_C

void			failure_exit_program(char *error, t_sdl *sdl);
void			SDL_init_window(t_sdl *sdl);
void			SDL_init_renderer(t_sdl *sdl);
void			SDL_apply_color_to_renderer(SDL_Color rgba, t_sdl *sdl);
void			SDL_init_img(t_sdl *sdl);
SDL_Texture		*SDL_load_texture(t_sdl *sdl, SDL_Renderer *renderer,
				SDL_Texture *texture, char *path);
void			SDL_render_clear(t_sdl *sdl, SDL_Renderer *renderer);
void			SDL_render_copy(t_sdl *sdl, SDL_Renderer *renderer,
				SDL_Texture *texture, SDL_Rect *src, SDL_Rect *dest);
void			SDL_render_target(t_sdl *sdl, SDL_Renderer *renderer,
				SDL_Texture *texture);

#endif
