#ifndef SAND_H
# define SAND_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>

# define black (SDL_Color){0, 0, 0, 255}
# define FPS 60
# define frame_delay (1000 / FPS)

typedef struct		s_sand
{
	SDL_Texture		*texture;
	int				width;
	int				height;
}					t_sand;

typedef struct		s_object
{
	struct s_sand	*sand;
}					t_object;

typedef struct		s_screen_content
{
	int				filled;
}					t_screen_content;

typedef struct		s_sdl
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	int				window_h;
	int				window_w;
}					t_sdl;

//	MAIN_C


//	GAME_LOOP_C

void			game_loop(t_sdl *sdl, t_object *object, t_screen_content
				***screen_content);
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
