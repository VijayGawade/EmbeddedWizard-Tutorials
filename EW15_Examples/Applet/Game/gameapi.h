/*******************************************************************************
*
* E M B E D D E D   W I Z A R D   P R O J E C T
*
*                                                Copyright (c) TARA Systems GmbH
*                                    written by Paul Banach and Manfred Schweyer
*
********************************************************************************
*
* This software is delivered "as is" and shows the usage of other software 
* components. It is provided as an example software which is intended to be 
* modified and extended according to particular requirements.
* 
* TARA Systems hereby disclaims all warranties and conditions with regard to the
* software, including all implied warranties and conditions of merchantability 
* and non-infringement of any third party IPR or other rights which may result 
* from the use or the inability to use the software.
* 
********************************************************************************
*
* DESCRIPTION:
*   This file demonstrates, how an external application written in 'C' may be
*   integrated into the Embedded Wizard environment as so called Applet.
*
*   This file contains a set of declarations for a simple game. This is the
*   external 'C' application :)
*
* SUBROUTINES:
*   GameInit
*   GameDone
*   GameMove
*   GameAnimate
*   GameUpdate
*
*******************************************************************************/

#ifndef GAME_H
#define GAME_H

#include "ewrte.h"
#include "ewgfx.h"


/* This structure describes an instance of the running game. Buffer points to
   the Index8 bitmap. The both coordinate pairs describes the position of the
   first and the second (the CPU) player. If the bitmap contains some changes
   - Update is != 0. */
typedef struct
{
  XBitmap*          Bitmap;
  XPoint            Size;
  XPoint            Player1;
  XPoint            Player2;
  unsigned long     LastTime;
  int               NeedUpdate;
} XGame;


/* This function should create a new instance of the embedded application.
   This function reserves memory for the new XGame structure, initialize it
   and returns it (if successfull). In this example, also an index8 bitmap is
   created. It will store the content of the application. */
XGame* GameInit( XPoint aSize );


/* This function should release the game instance aGame */
void GameDone( XGame* aGame );


/* The function GameMove() moves the figure of the player 1 by the given
   number of pixels aOffset */
void GameMove( XGame* aGame, XPoint aOffset );


/* This function is called in order to give the game a chance to do some
   background processing. In this case the player 2 is moved. The argment
   aTime contains time as the number of milliseconds. */
void GameAnimate( XGame* aGame, unsigned long aTime );


/* This function forces the game to redaw itself (if needed) and returns a
   value != 0, if an area of the frame buffer needs to be redrawn. */
int GameUpdate( XGame* aGame );


/* The function GameGetBitmap() returns the current bitmap where the visible
   content of the application is stored. */
XBitmap* GameGetBitmap( XGame* aGame );


#endif /* GAME_H */

/* pba */