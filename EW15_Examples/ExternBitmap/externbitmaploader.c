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
*   This example implements an extern bitmap loader function which is required
*   by the Mosaic class Resources::ExternBitmap. Within this extern bitmap
*   loader function the content of a bitmap can be filled by any extern image
*   decoder like a JPG or PNG decoder. In order to keep this example as simple
*   as possible, we just demonsrate how to create the bitmap and how to write
*   the content of a bitmap with simple color data.
*   Please feel free to adapt this sample according your needs.
*   Please note, that the usage of Resources::ExternBitmap requires Graphics
*   Engine 2.0 API.
*   This sample is prepared for the 32 bit color format RGBA8888.
*
*******************************************************************************/

#include "ewrte.h"
#include "ewgfx.h"
#include "ewextpxl_RGBA8888.h"


/* This function has the job to create and fill a bitmap with content of an
   extern image file. aName contains the name (or identifier) of the extern file
   that should be loaded. If successful, an initialized bitmap is returned,
   otherwise NULL.
   Please note, that this example does not contain any image decoder - we just
   create a bitmap and fill it with some color data... */
XBitmap* EwLoadExternBitmap( XString aName )
{
  XPoint         size;
  XBitmap*       bitmap;
  XBitmapLock*   lock;
  unsigned char  red;
  unsigned char  green;
  unsigned char  blue;
  unsigned char  alpha;
  unsigned long* ptr;
  int            offset;
  int            x, y;

  /* This intrinsic assumes that the Graphics Engine supports natively the
     32-bit color format RGBA8888. To avoid runtime errors check what format is
     really supported. Please note, the Graphics Engine is determined by the
     selection of the PlatformPackage in the Profile member of your Embedded
     Wizard project. */
  if ( EwGetGraphicsEngineInfo()->FormatOfNativeSurfaces != EW_DRIVER_VARIANT_RGBA8888 )
  {
    EwPrint( "Intrinsic: Incompatible version of the Graphics Engine. The"
             " intrinsic expects the engine to store native surfaces in the"
             " format RGBA8888 with 32-bit per pixel. Please select the right"
             " 'PlatformPackage' in the 'Profile'." );
    return 0;
  }

  /* ==> TODO: Take the given name aName and use it as identifier to access
     your image (e.g. a JPG image within an image directory, an PNG image
     already loaded somewhere in the memory, ... ) */

  /* In our simple example we just use aName to select a color: red, green,
     blue or semitransparent gray if no explicit name has been specified.
     The color is used to fill the bitmap. */
  if      ( aName[0] == 'R' )
  {
    red   = 255;
    green = 0;
    blue  = 0;
    alpha = 255;
  }
  else if ( aName[0] == 'G' )
  {
    red   = 0;
    green = 255;
    blue  = 0;
    alpha = 255;
  }
  else if ( aName[0] == 'B' )
  {
    red   = 0;
    green = 0;
    blue  = 255;
    alpha = 255;
  }
  else
  {
    red   = 128;
    green = 128;
    blue  = 128;
    alpha = 128;
  }

  /* ==> TODO: Access your image and query all necessary data. At least
     we need the width and the height of the image in order to allocate
     the bitmap */

  /* In our simple example, we just use a fixed size */
  size.X = 150;
  size.Y = 100;

  /* Now, create a new empty bitmap with the previously determined size and format */
  bitmap = EwCreateBitmap( EW_PIXEL_FORMAT_NATIVE, size, 0, 1 );

  /* If the creation has failed */
  if ( !bitmap )
    return 0;

  /* Lock the entire bitmap for the write only operation */
  lock = EwLockBitmap( bitmap, 0, EwNewRect( 0, 0, size.X, size.Y ), 0, 1 );

  /* Get the pointer to the bitmap pixel memory */
  ptr    = lock->Pixel1;
  offset = ( lock->Pitch1Y >> 2 ) - size.X;

  /* ==> TODO: Decode your image and copy row by row and pixel by pixel
     from your decoded image into the bitmap. */

  /* Fill the bitmap row by row and column by column */
  for ( y = 0; y < size.Y; y++, ptr += offset )
    for ( x = 0; x < size.X; x++, ptr++ )
    {
      /* The color value for the current pixel */
      unsigned char r = red;
      unsigned char g = green;
      unsigned char b = blue;
      unsigned char a = alpha;

      /* Add a simple grid pattern. In dark gray color. */
      if (( x % 10 == 0 ) || ( y % 10 == 0 ))
      {
        r =  64;
        g =  64;
        b =  64;
        a = 255;
      }

      /* Pre-multiplication of red, green, blue channels by alpha? */
      #ifdef EW_PREMULTIPLY_COLOR_CHANNELS
        if ( EW_PREMULTIPLY_COLOR_CHANNELS && ( a < 255 ))
        {
          r = ( r * ( a + 1 )) >> 8;
          g = ( g * ( a + 1 )) >> 8;
          b = ( b * ( a + 1 )) >> 8;
        }
      #endif

      /* Bring the color channels in the right order and store them in the 
         bitmap's memory. */
      *ptr = EW_SHIFT( r, -EW_COLOR_CHANNEL_BIT_OFFSET_RED   ) |
             EW_SHIFT( g, -EW_COLOR_CHANNEL_BIT_OFFSET_GREEN ) |
             EW_SHIFT( b, -EW_COLOR_CHANNEL_BIT_OFFSET_BLUE  ) |
             EW_SHIFT( a, -EW_COLOR_CHANNEL_BIT_OFFSET_ALPHA );
    }

  /* finally, unlock the bitmap */
  EwUnlockBitmap( lock );

  /* Return the filled bitmap */
  return bitmap;
}

/* pba, msy */