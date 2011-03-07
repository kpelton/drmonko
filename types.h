#ifndef TYPES_H
#define TYPES_H
namespace player_types
{
  
	enum p_type
	{
		INTERNET_CLIENT,
		INTERNET_SERVER
    	};

	enum key
	{
		LEFT,
		RIGHT,
		ROTATE,
		DOWN,
		EXIT,
		SELECT,
		NONE
	};

	static const int p1_keys[] = 
		{
			SDLK_LEFT,
			SDLK_RIGHT,
			SDLK_UP,
			SDLK_DOWN,
			SDLK_ESCAPE,
			SDLK_RETURN
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
