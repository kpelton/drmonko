\
#include "board.h"
#include <iostream>
#include <time.h>
#include <stdio.h>
#include <GL/glut.h>
#include "GLobject.h"
#include "sdlWindow.h"
#include "types.h"

using namespace std;
using namespace player_types;
using namespace piece_types;
enum types{
	NONE,
	O,
	I,
	L,
	J,
	S,
	Z,
	T
};

void board::handleKeyPress(player_types::tetris_key key)
{

	switch ( key )
	{	
	case DOWN:	
		if(isPossible(newPiece.x,newPiece.y+1,newPiece.type,newPiece.rotation))
			newPiece.y +=1;

		break;
	case ROTATE:
		rotatePiece();
		break;
	case LEFT:
		if(isPossible(newPiece.x-1,newPiece.y,newPiece.type,newPiece.rotation))
			newPiece.x -=1;
		break;
	case RIGHT:
		if(isPossible(newPiece.x+1,newPiece.y,newPiece.type,newPiece.rotation))
			newPiece.x +=1;
		break;
	case EXIT:
		exit(0);
		break;

	default:
		break;
	}

} 

void board::rotatePiece()
{
	int rot = newPiece.rotation;

	if(rot <3 ) 
		rot++;
	else
		rot=0;

	
	if(isPossible(newPiece.x,newPiece.y,newPiece.type,rot))
		newPiece.rotation = rot;
	
}

void board::addToBoard(Uint8 aboard[ROWWIDTH][COLUMNLENGTH])
{
	int type = newPiece.type;
	int rot = newPiece.rotation;
	int pX = newPiece.x;
	int pY = newPiece.y;

	

	for(int i=pY-abs(piecesInitialPosition[type][rot][1]),i2=0; i<pY-abs(piecesInitialPosition[type][rot][1])+5; i++,i2++)
	{
		for(int j=(pX-abs(piecesInitialPosition[type][rot][0])),j2=0; j<pX-abs(piecesInitialPosition[type][rot][0])+5; j++,j2++)
		{
			if(pieces[type][rot][i2][j2] != 0 )
				aboard[j][i] = type+1;
			
		}
	}

}

bool board::isDone()

{
  
	for(int i =0; i<ROWWIDTH; i++)
		if(gameboard[i][1] != 0)
			return true;

	//check to see if new piece will hit
	if(!isPossible(newPiece.x,newPiece.y,newPiece.type,newPiece.rotation))
	  return true;

	return false;
		

}

bool board::isPossible(int pX, int pY, int type, int rot)
{ 

	for(int i=pY-abs(piecesInitialPosition[type][rot][1]),i2=0; i<pY-abs(piecesInitialPosition[type][rot][1])+5; i++,i2++)
	{
		for(int j=(pX-abs(piecesInitialPosition[type][rot][0])),j2=0; j<pX-abs(piecesInitialPosition[type][rot][0])+5; j++,j2++)
		{
			if(pieces[type][rot][i2][j2] != 0 && ( i >=COLUMNLENGTH  || i<0 || j>=ROWWIDTH || j<0))
				return 0;

			if(pieces[type][rot][i2][j2] != 0 && gameboard[j][i] != 0)
				return 0;
					
			
		}
	}



	return true;

}
board::board(const int width, const int height,const int lstart)
{
	int lend;
	const int LINEWIDTH=2;

	blocksize = ((height)/(1.0*COLUMNLENGTH));
	this->height = height;
	this->width = width;
	this->lstart = lstart;

	lend =  lstart + (blocksize * ROWWIDTH) +LINEWIDTH;

	tbackground = new background(width,height,lstart,lend);
       
	
	loadTextures();
        clearBoard();
}
board::board()
{
	blocksize = ((height)/COLUMNLENGTH);
	loadTextures();
	clearBoard();
}

void board::clearBoard()
{
	ready = true;
	Uint32 now;
	for(int i = 0; i<ROWWIDTH;i++)
	{
		for (int j=0; j<COLUMNLENGTH; j++)
		{
			gameboard[i][j] =0;
		}
	}
	interval = 1000;
	newBlock();	
	level  = 1;
	score = 0;
	lines = 0;
	lineslevel=0;
	tbackground->setLevel(1);
	now = SDL_GetTicks();	
	start = now+interval;
}

board::~board()
{
	delete tbackground;
	
}
bool board::loadTextures()
{

	string file = "block.bmp";
	GLobject::loadTextureFile(file.c_str(),&blocktexture);
	return true; 
}


int board::timerCb()
{
	Uint32 now;
	int lines = 0;
	now = SDL_GetTicks();
	if ( start >= now ) {
		return lines;
	}
	start = now+interval;

	 if(!isPossible(newPiece.x, newPiece.y+1,newPiece.type, newPiece.rotation))
	{ 
		//add to board since we can no longer go down
		addToBoard(gameboard);
		lines = checkLines();
		newPiece.newPiece(0,0,ROWWIDTH/2);
		if (isDone()){
		  clearBoard();
		return -1; //for mplayer to start new game
		}
       
	}
	
	else
	{
		// move piece one line down
		newPiece.y+=1;	    
		
	}
	return lines;
}
bool board::render(){

	tbackground->render();
	//drawPiece();
	drawBlocks();
	drawNextPiece();
	drawScore();


	
	return true;
}
void board::drawString(string str,int height ) const
{
		int lend = lstart + (blocksize * ROWWIDTH) +1;
		void * font = GLUT_BITMAP_HELVETICA_12;
		glColor3f(0.0, 1.0, 0.0); // Green
		GLobject::drawString(str,font,lend+blocksize,height);
}
void board::drawScore()
{  
	char cscore[50];
	string s = "Score:";

	sprintf(cscore,"%i",score);
	s += cscore;
	this->drawString(s, height *.75);

	s = "Level:";
	sprintf(cscore,"%i",level);
	s += cscore;
	
	this->drawString(s,(height *.75)-25);

	s = "Lines:";
	sprintf(cscore,"%i",lines);
	s += cscore;
	
	this->drawString(s,(height *.75)-50);
	
	
}

void board::newBlock()
{

	newPiece.firstPiece(1);

}
void board::addLines(const int num) //for multiplayer
{
	int hole = rand()%ROWWIDTH;
	//shift  up the board by num
	for (int k = num; k<COLUMNLENGTH; k++)  
	{  
		for (int z = 0; z < ROWWIDTH; z++)  
		{  
			gameboard[z][k-num] = gameboard[z][k];   
		}  
	}

	//replace num lines with dummy blocks except for the hole
	for (int k = COLUMNLENGTH-1; k>COLUMNLENGTH-1-num; k--)  
	{  
		for (int z = 0; z < ROWWIDTH; z++)  
		{  
			if(z == hole)
				gameboard[z][k] =0;
			else
				gameboard[z][k] =9; 
		}  

	}


}
int board::checkLines()
{
	int blocks = 0;
	int clines = 0;
	for (int j=0; j<COLUMNLENGTH; j++)
	{
		blocks=0;
		for(int i = 0; i<ROWWIDTH;i++)
		{
			if(gameboard[i][j] != 0 && gameboard[i][j] != 10 )
				blocks++;
			else 
				break;
		}
		if(blocks == ROWWIDTH)
		{
			lines++;
			lineslevel++;
			clines++;	
		    	for(int i = 0; i<ROWWIDTH;i++)
			{
				gameboard[i][j] = -1;
			}   
			for (int k = j; k > 0; k--)  
			{  
				for (int z = 0; z < ROWWIDTH; z++)  
				{  
					gameboard[z][k] = gameboard[z][k-1];  
				}  
			}
		}
			
	}
	if(clines >0){

		switch (clines)
		{
		case 1: 
			score += 100;
			break;
	
		case 2:
			score += 300;
			break;
		case 3 :
			score += 500;
			break;
		case 4:
			score += 1000;
			break;
		
		default:
			break;
		}
	}

	if(lineslevel >= 10 && level <10){
		jumpLevel();
	}

	return clines;
}


void board::jumpLevel()
{
	tbackground->setLevel(level+1);
	lineslevel = 0;
	level++;
	interval-=100;
	cout <<"Level #" <<level <<endl;

}
void board::drawNextPiece()
{
	int type = newPiece.ntype;
	int rotation = newPiece.nrotation;
	int x = 0;
	int y = 0;
	int lend = lstart + (blocksize * ROWWIDTH) +1;
	int  wstart=(width * .78);
	int  hstart=(height * .25);			      	
	
	if(type == 1)
		rotation = 1;

	glEnable( GL_TEXTURE_2D );
	glBindTexture( GL_TEXTURE_2D, blocktexture );

	hstart = (blocksize) *(y) ; //y coordinate where to start

	for(int i=0; i<5;i++)
	{		
		
		wstart = (lend) +((blocksize) * ( x));
						
		for (int j=0; j<5; j++)
		{
			if(pieces[type][rotation][i][j] != 0)
			{
				doColor(type+1);
				drawBlock(wstart,hstart,blocksize);
			}
			wstart += blocksize;	
		}
		hstart += blocksize;
	}
	glDisable( GL_TEXTURE_2D );
}
void board::drawPiece()
{
	int type = newPiece.type;
	int rotation = newPiece.rotation;
	float x = newPiece.x -abs(piecesInitialPosition[type][newPiece.rotation][0]);
	float  y = newPiece.y -abs(piecesInitialPosition[type][newPiece.rotation][1]);

	float wstart=(lstart);
	float hstart=0;			      

	hstart = (blocksize) *(y) ; //y coordinate where to start
	
	glEnable( GL_TEXTURE_2D );
	glBindTexture( GL_TEXTURE_2D, blocktexture );


	for(int i=0; i<5;i++)
	{		
		wstart = lstart  +((blocksize) * ( x));
		for (int j=0; j<5; j++)
		{
			if(pieces[type][rotation][i][j] != 0)
			{
				doColor(type+1);
				drawBlock(wstart,hstart,blocksize);
			}
			wstart += blocksize;	
		}
		hstart += blocksize;
	}
	glDisable( GL_TEXTURE_2D );
}

void board::doColor(int type){

	float r=255;
	float  g=255;
	float  b=255;
	float a=0.2;
	
	switch (type)
	{
	case O:
		r=255;
		g=255;
		b=0;
		break;
	case L:
		r=1;
		g=.64;
		b=0;
		break;

	case I:
		r=0;
		g=255;
		b=255;
		break;
	
	case J:
		r=0;
		g=0;
		b=255;
		break;

	case S:
		r=0;
		g=255;
		b=0;
		break;

	case Z:
		r=1;
		g=0;
		b=0;
		break;
	
	case T:
		r=.62;
		g=.12;
		b=.94;
		break;


	default:
		break;

	}
		
	glColor4f(r,g,b,a);


}

void board::drawBlock(const float wstart, const float hstart, const float  size) const
{
  glBegin(GL_QUADS); // Start drawing a quad primitive 
  glTexCoord2i( 0, 0 );   glVertex2f(wstart, hstart);
  glTexCoord2i( 1, 0 );   glVertex2f(wstart+size, hstart);
  glTexCoord2i( 1, 1 );   glVertex2f(wstart+size, hstart+size);
  glTexCoord2i( 0, 1 );	glVertex2f(wstart, hstart+size);
  glEnd();  

}
void board::drawBlocks(){

	float  hstart=0;			 
	float wstart=lstart;
	glEnable( GL_TEXTURE_2D );
	glBindTexture( GL_TEXTURE_2D, blocktexture );
	
	for(int i = 0; i<ROWWIDTH;i++)
	{	
		hstart = height;
		
		for (int j=COLUMNLENGTH; j>0; j--)
		{
			if(gameboard[i][j] > 0)
			{
				doColor(gameboard[i][j]);
				drawBlock(wstart,hstart,blocksize);
						
			}
			hstart -=blocksize;//blocksize +(blocksize - blocksize);
		}
		
		wstart +=blocksize;
	}
	glDisable( GL_TEXTURE_2D );
}

