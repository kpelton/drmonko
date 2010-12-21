#include "sdlWindow.h"
#include <GL/glut.h>

#define TICK_INTERVAL 500

const char * sdlWindow::musicFile = "song.wav";

sdlWindow::sdlWindow()
{
	initWindow();
	scene = new GLscene(SCREEN_WIDTH,SCREEN_HEIGHT);
    	done = false;
	this->fullscreen = false;
}
sdlWindow::sdlWindow(int argc, char **argv)
{
	this->fullscreen = false;
	for(int i = 0; i<argc; i++)
		{
			if(strcmp(argv[i],"-f") == 0)
				this->fullscreen = true;
			//put in width height
			
			
		}
	    
	initWindow();
	scene = new GLscene(SCREEN_WIDTH,SCREEN_HEIGHT,argc,argv);
    	done = false;
}

void sdlWindow::initGL()
{
	/* Set the background black */
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

    /* Depth buffer setup */
    glClearDepth( 1.0f );

    /* Enables Depth Testing */
    glEnable( GL_DEPTH_TEST );

    /* The Type Of Depth Test To Do */
    glDepthFunc( GL_LEQUAL );

    /* Really Nice Perspective Calculations */
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

	
}

void sdlWindow::initWindow()
{
	
	isActive = true;
	Mix_Chunk *sound = NULL;
	int channel;
  /* initialize SDL */
    if ( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 )
	{
	    fprintf( stderr, "Video initialization failed: %s\n",
		     SDL_GetError( ) );
	    exit(1);
	}


    /* Fetch the video info */
    videoInfo = SDL_GetVideoInfo( );

    if ( !videoInfo )
	{
	    fprintf( stderr, "Video query failed: %s\n",
		     SDL_GetError( ) );
	    exit(1);
	}
     
    /* the flags to pass to SDL_SetVideoMode */
     videoFlags = SDL_OPENGL;          /* Enable OpenGL in SDL */
    videoFlags |= SDL_GL_DOUBLEBUFFER; /* Enable double buffering */
    videoFlags |= SDL_HWPALETTE;       /* Store the palette in hardware */
    videoFlags |= SDL_RESIZABLE;
    if (fullscreen)    
	    videoFlags |= SDL_FULLSCREEN;       /* Enable window resizing */


    /* This checks to see if surfaces can be stored in memory */
    if ( videoInfo->hw_available )
	videoFlags |= SDL_HWSURFACE;
    else
	videoFlags |= SDL_SWSURFACE;

    /* This checks if hardware blits can be done */
    if ( videoInfo->blit_hw )
	videoFlags |= SDL_HWACCEL;

    /* Sets up OpenGL double buffering */
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

    /* get a SDL surface */
    surface = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP,
				videoFlags );

    
    /* Verify there is a surface */
    if ( !surface )
	{
	    fprintf( stderr,  "Video mode set failed: %s\n", SDL_GetError( ) );
	    exit(1);
	}

    /* initialize OpenGL */
    initGL( );
     if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
     {
	 exit(-1);
     }
     sound = Mix_LoadWAV(musicFile);

     channel = Mix_PlayChannel(-1, sound, -1);
      if(channel == -1) {
	  fprintf(stderr, "Unable to play WAV file: %s\n", Mix_GetError());
      }

    
    SDL_EnableKeyRepeat(200, SDL_DEFAULT_REPEAT_INTERVAL);
    resizeWindow( SCREEN_WIDTH, SCREEN_HEIGHT );
    /* resize the initial window */
    //resizeWindow( SCREEN_WIDTH, SCREEN_HEIGHT );

	    
 
	
}
bool sdlWindow::resizeWindow(const  int width, const int height )
{
    /* Height / width ration */
     GLfloat ratio;

    /* Protect against a divide by zero */
   

    ratio = ( GLfloat )width / ( GLfloat )height;

    /* Setup our viewport. */
    
    glViewport(0,0 ,( GLsizei )width, height);

    /* change to the projection matrix and set our viewing volume. */
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );
    //gluPerspective(45.0,width/height,1.0,500.0f);
    /* Set our perspective */
    glOrtho (0,SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, 1);

    /* Make sure we're chaning the model view and not the projection */
    glMatrixMode( GL_MODELVIEW );

    /* Reset The View */
    glLoadIdentity( );

    return true;
}



void sdlWindow::renderLoop()
{

 
	
	  

	while ( !done )
	{
		/* handle the events in the queue */
	  if( SDL_PollEvent( &event ) )
		{
			switch( event.type )
			{
			case SDL_ACTIVEEVENT:
				/* Something's happend with our focus
				 * If we lost focus or we are iconified, we
				 * shouldn't draw the screen
				 */
			  scene->renderScene(NULL);
				if ( event.active.gain == 0 )
					isActive = false;
				else
				    isActive = true;
			    break;			    
			case SDL_VIDEORESIZE:
			    /* handle resize event */
			    surface = SDL_SetVideoMode( event.resize.w,
							event.resize.h,
							16, videoFlags );
			        
			    if ( !surface )
				{
				    fprintf( stderr, "Could not get a surface after resize: %s\n", SDL_GetError( ) );
				   exit( 1 );
				}
			    resizeWindow( event.resize.w, event.resize.h );
			    break;
			case SDL_KEYDOWN:
			
			  scene->renderScene(&event);
			
			  break;
			  
			case SDL_USEREVENT:
			
			  scene->renderScene(&event);
				break;


			case SDL_QUIT:
				/* handle quit requests */
				done = true;
				break;
			default:
			    				
				break;
			}
		
			
		
		}

	  scene->renderScene(NULL);
	  SDL_Delay(2);
	}
 
 }


