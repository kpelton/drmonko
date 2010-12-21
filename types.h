#ifndef TYPES_H
#define TYPES_H
namespace player_types
{
  
	enum p_type
	{
		PLAYER1,
		PLAYER2,
		INTERNET_CLIENT,
		INTERNET_SERVER,
		INTERNET_SERVER_CLIENT,
		INTERNET_CLIENT_SERVER
    	};

	enum tetris_key
	{
		LEFT,
		RIGHT,
		ROTATE,
		DOWN,
		EXIT,
		CHAT,
		NONE
	};

	static const int p1_keys[] = 
		{
			SDLK_LEFT,
			SDLK_RIGHT,
			SDLK_UP,
			SDLK_DOWN,
			SDLK_ESCAPE,
			SDLK_z
		};

	static const int p2_keys[] = 
		{
			SDLK_a,
			SDLK_d,
			SDLK_w,
			SDLK_s,
			SDLK_ESCAPE,
			SDLK_z
		};

};
#endif
