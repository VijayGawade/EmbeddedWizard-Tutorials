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
*   This file contains the implementation of a simple game. This is the external
*   'C' application :)
*
* SUBROUTINES:
*   GameInit
*   GameDone
*   GameMove
*   GameAnimate
*   GameUpdate
*
*******************************************************************************/

#include "gameapi.h"


/* In this example we uses the Index8 bitmap as off-screen buffer. In order to
   be drawn, such bitmap expsts a color lookup table to convert the index values
   into real colors. */
XColor Colors[] = 
{
  { 0x00, 0x00, 0x00, 0x00 },  /* inxdex #0 */
  { 0xFF, 0x00, 0x00, 0xFF },  /* inxdex #1 */
  { 0x00, 0x88, 0x00, 0xFF },  /* inxdex #2 */
  { 0x88, 0x88, 0x88, 0xFF },  /* inxdex #3 */
};


/* This function should create a new instance of the embedded application.
   This function reserves memory for the new XGame structure, initialize it
   and returns it (if successfull). In this example, also an index8 bitmap is
   created. It will serve as the off-screen bitmap to store the content of
   the application. */
XGame* GameInit( XPoint aSize )
{
  /* Reserve memory for the new game instance */
  XGame*   game   = EwAlloc( sizeof( XGame ));
  XBitmap* bitmap = EwCreateBitmap( EW_PIXEL_FORMAT_INDEX8, aSize, 0, 1 );

  if ( !game || !bitmap )
  {
    if ( game   ) EwFree( game );
    if ( bitmap ) EwFreeBitmap( bitmap );
    return 0;
  }

  /* ... and initialize it */
  game->Bitmap     = bitmap;
  game->Size       = aSize;
  game->Player1    = EwNewPoint( 10, 10 );
  game->Player2    = EwNewPoint( 100, 100 );
  game->LastTime   = 0;
  game->NeedUpdate = 1;

  /* Because the external application uses the Index8 bitmap as off-screen buffer,
     a color lookup table is needed to convert the index values into real colors.
     Load the CLUT now. */
  EwModifyBitmapPalette( bitmap, 0, sizeof( Colors ) / sizeof( *Colors ), Colors );

  /* Return a pointer representing the instance of the just created application */
  return game;
}


/* This function should release the game instance aGame */
void GameDone( XGame* aGame )
{
  if ( aGame )
  {
    EwFreeBitmap( aGame->Bitmap );
    EwFree( aGame );
  }
}


/* The function GameMove() moves the figure of the player 1 by the given
   number of pixels aOffset */
void GameMove( XGame* aGame, XPoint aOffset )
{
  aGame->Player1.X += aOffset.X;
  aGame->Player1.Y += aOffset.Y;

  /* Something has changed. The next the function GameUpdate() is invoked 
     -> redraw the game! */
  aGame->NeedUpdate = 1;
}


/* This function is called in order to give the game a chance to do some
   background processing. In this case the player 1 is moved. The argment
   aTime contains time as the number of milliseconds. */
void GameAnimate( XGame* aGame, unsigned long aTime )
{
  /* Margin for the area where the figures may move */
  int minX = 5;
  int minY = 4;
  int maxX = aGame->Size.X - 5;
  int maxY = aGame->Size.Y - 5;

  /* Ensure the player does not leave the area */
  if ( aGame->Player1.X > maxX ) aGame->Player1.X = maxX;
  if ( aGame->Player1.Y > maxY ) aGame->Player1.Y = maxY;
  if ( aGame->Player1.X < minX ) aGame->Player1.X = minX;
  if ( aGame->Player1.Y < minY ) aGame->Player1.Y = minY;

  /* Calculate the position of the second player - 25 times per second */
  if (( aTime - aGame->LastTime ) > 40 )
  {
    int deltaX = aGame->Player1.X - aGame->Player2.X;
    int deltaY = aGame->Player1.Y - aGame->Player2.Y;

    /* The speed of player 2 depends on the distance between the both
       players */
    if (( deltaX > 0 ) && (( deltaX /= 10 ) == 0 )) deltaX =  1;
    if (( deltaX < 0 ) && (( deltaX /= 10 ) == 0 )) deltaX = -1;
    if (( deltaY > 0 ) && (( deltaY /= 10 ) == 0 )) deltaY =  1;
    if (( deltaY < 0 ) && (( deltaY /= 10 ) == 0 )) deltaY = -1;

    /* The second player should follow the first one */
    aGame->Player2.X += deltaX;
    aGame->Player2.Y += deltaY;

    /* Remember the last time, when the player 2 was moved and force an update */
    aGame->LastTime   = aTime;
    aGame->NeedUpdate = 1;
  }
}


/* This function forces the game to redaw itself (if needed) and returns a
   value != 0, if an area of the frame bitmap needs to be redrawn. */
int GameUpdate( XGame* aGame )
{
  XBitmapLock*   lock;
  unsigned char* pixel;
  unsigned char* tmp;
  int            ofs;
  int            x, y;

  /* No update needed */
  if ( !aGame->NeedUpdate )
    return 0;

  /* No destination bitmap */
  if ( !aGame->Bitmap )
    return 0;

  /* Within this function we access the pixel memory of the Index8 off-screen 
     bitmap. In this manner the external application does feel like it had
     an own frame buffer. Within this 'buffer', the application can draw what
     it want */

  /* For the update get the pointer to the pixel memory of the bitmap */
  lock = EwLockBitmap( aGame->Bitmap, 0, 
                       EwNewRect( 0, 0, aGame->Size.X, aGame->Size.Y ), 0, 1 );

  /* Could obtain direct access to the bitmap? */
  if ( !lock )
    return 0;

  /* Start address for the first top-left pixel of the bitmap and an offset
     between the end of one row and the start of the next following row */
  pixel = lock->Pixel1;
  ofs   = lock->Pitch1Y - aGame->Size.X;

  /* Fill the index8 bitmap with the background color #0. Additionally draw
     a 8 pixel large grid with color #3 */
  for ( tmp = pixel, y = 0; y < aGame->Size.Y; y++, tmp += ofs )
    for ( x = 0; x < aGame->Size.X; x++ )
      *tmp++ = ( !( x % 8 ) && !( y % 8 ))? 3 : 0;

  /* Now, get the pointer to the pixel where the first player should appear. */
  tmp = pixel + ( aGame->Player1.Y * lock->Pitch1Y ) + aGame->Player1.X;

  /* 'tmp' refers the pixel in the center of the player's figure. Adjust the
     pointer so that it refers the upper pixel in the first row */
  tmp -= lock->Pitch1Y * 2;

  /* Display the first player as a 7 x 7 pixel large diamond in color #1. */
  tmp[ 0 ] = 1;
  tmp += lock->Pitch1Y;
  tmp[-1 ] = tmp[ 0 ] = tmp[ 1 ] = 1;
  tmp += lock->Pitch1Y;
  tmp[-2 ] = tmp[-1 ] = tmp[ 0 ] = tmp[ 1 ] = tmp[ 2 ] = 1;
  tmp += lock->Pitch1Y;
  tmp[-3 ] = tmp[-2 ] = tmp[-1 ] = tmp[ 0 ] = tmp[ 1 ] = tmp[ 2 ] = tmp[ 3 ] = 1;
  tmp += lock->Pitch1Y;
  tmp[-2 ] = tmp[-1 ] = tmp[ 0 ] = tmp[ 1 ] = tmp[ 2 ] = 1;
  tmp += lock->Pitch1Y;
  tmp[-1 ] = tmp[ 0 ] = tmp[ 1 ] = 1;
  tmp += lock->Pitch1Y;
  tmp[ 0 ] = 1;

  /* Then, get the pointer to the pixel where the second player should appear. */
  tmp = pixel + ( aGame->Player2.Y * lock->Pitch1Y ) + aGame->Player2.X;

  /* Again, 'tmp' refers the pixel in the center of the player's figure. Adjust
     the pointer so that it refers the upper pixel in the first row */
  tmp -= lock->Pitch1Y * 2;

  /* Display the second player as a 7 x 7 pixel large diamond in color #2. */
  tmp[ 0 ] = 2;
  tmp += lock->Pitch1Y;
  tmp[-1 ] = tmp[ 0 ] = tmp[ 1 ] = 2;
  tmp += lock->Pitch1Y;
  tmp[-2 ] = tmp[-1 ] = tmp[ 0 ] = tmp[ 1 ] = tmp[ 2 ] = 2;
  tmp += lock->Pitch1Y;
  tmp[-3 ] = tmp[-2 ] = tmp[-1 ] = tmp[ 0 ] = tmp[ 1 ] = tmp[ 2 ] = tmp[ 3 ] = 2;
  tmp += lock->Pitch1Y;
  tmp[-2 ] = tmp[-1 ] = tmp[ 0 ] = tmp[ 1 ] = tmp[ 2 ] = 2;
  tmp += lock->Pitch1Y;
  tmp[-1 ] = tmp[ 0 ] = tmp[ 1 ] = 2;
  tmp += lock->Pitch1Y;
  tmp[ 0 ] = 2;

  /* Release the pixel memory */
  EwUnlockBitmap( lock );

  /* Clear the update request and inform the EmWi environment, ... */
  aGame->NeedUpdate = 0;

  /* ... that there are some modifications performed on the off-screen bitmap 
     -> Screen update is required */
  return 1;
}


/* The function GameGetBitmap() returns the current bitmap where the visible
   content of the application is stored. */
XBitmap* GameGetBitmap( XGame* aGame )
{
  return aGame->Bitmap;
}


/* pba */