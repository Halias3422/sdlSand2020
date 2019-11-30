#include "../includes/sand.h"

int			handle_user_input(SDL_Event event, const Uint8 *state,
			t_screen_content ***screen_content)
{
	SDL_Rect	dst = {0, 0, 0, 0};
	int			check = 0;

	if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEMOTION)
	{
		if (SDL_GetMouseState(&dst.x, &dst.y) & SDL_BUTTON(SDL_BUTTON_LEFT) && check++ == 0)
			screen_content[dst.y][dst.x]->filled = 1;
	}
	if (state[SDL_SCANCODE_ESCAPE])
		check = 2;
	return (check);
}

void			update_

void			game_loop(t_sdl *sdl, t_object *object, t_screen_content
				***screen_content)
{
	int			quit = 0;
	const		Uint8	*state;
	SDL_Event	event;
	Uint32		frame_start = 0;
	int			current_frame = 0;
	int			moved = 0;

	while (moved != 2)
	{
		frame_start = SDL_GetTicks();
		state = SDL_GetKeyboardState(NULL);
		if (SDL_PollEvent(&event))
			moved = handle_user_input(event, state, screen_content);
		update_screen_content(screen_content);
		current_frame = SDL_GetTicks() - frame_start;
		if (frame_delay > current_frame)
			SDL_Delay(frame_delay - current_frame);
	}
}
