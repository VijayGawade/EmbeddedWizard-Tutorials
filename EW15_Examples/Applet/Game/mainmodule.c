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
* Intrinsics module to load Game into Embedded Wizard for prototyping.
*
\******************************************************************************/

#include "ewrte.h"
#include "ewgfx.h"
#include "gameapi.h"
#include <malloc.h>
#include <string.h>


/* Description of this Embedded Wizard Module */
EW_MODULE
( 
  INTRINSICS_IFC_VERSION,
  L"IntrinsicsModule", 
  L"This is the intrinsics module to load the Game into Embedded Wizard"
)


/* This is the intrinsics-table. This table contains registration-entries for
   intrinsics implemented in this Embedded Wizard module */
EW_DEFINE_INTRINSICS
  EW_INTRINSIC
  (
    L"GameInit",
    L"handle",
    1,
    L"point",
    L"aSize",
    GameInit
  )

  EW_INTRINSIC
  (
    L"GameDone",
    L"void",
    1,
    L"handle",
    L"aGame",
    GameDone
  )

  EW_INTRINSIC
  (
    L"GameMove",
    L"void",
    2,
    L"handle,point",
    L"aGame,aOffset",
    GameMove
  )

  EW_INTRINSIC
  (
    L"GameAnimate",
    L"void",
    2,
    L"handle,uint32",
    L"aGame,aTime",
    GameAnimate
  )

  EW_INTRINSIC
  (
    L"GameUpdate",
    L"bool",
    1,
    L"handle",
    L"aGame",
    GameUpdate
  )

  EW_INTRINSIC
  (
    L"GameGetBitmap",
    L"handle",
    1,
    L"handle",
    L"aGame",
    GameGetBitmap
  )
EW_END_OF_INTRINSICS


/* Declaration of a data structure intended to store a copy of all globally
   existing data members permitting multiple instances of the module to coexist
   simultanously. Since this example uses Graphics Engine, it is important to
   store the pointers to the Graphics Engine module in the context. */
typedef struct
{
  XGraphicsEngineAPI GraphicsEngineAPI;
}
YourContextStruct;


/* At the initialization time of the module, create a data structure to store
   there a copy of global data members. */
EW_ENTRYPOINT void* EwInitModule( void )
{
  YourContextStruct* context;
  
  context = malloc( sizeof( YourContextStruct ));
  memset( context, 0, sizeof( YourContextStruct )); 
  return context; 
}


/* At the de-initialization time of the module, free the data structure used to
   store a copy of global data members. */
EW_ENTRYPOINT void EwDoneModule( void* aContext )
{
  free( aContext );
}


/* After all intrinsic modules are loaded, resolve all references to the Graphics
   Engine API functions */
EW_ENTRYPOINT void EwLinkModule( XModuleContext* aList )
{
  /* This intrinsic module requires access to the Graphics Engine API. Link this
     module with the GRaphics Engine API. */
  EwLinkWithGraphicsEngine( aList );
}


/* Just before Chora interpreter invokes an intrinsic, restore the state of all
   relevant (global) variables from the context data structure. */
EW_ENTRYPOINT void EwIntrinsicsProlog( void* aContext )
{
  YourContextStruct* context = (YourContextStruct*)aContext;

  /* Since this example uses Graphics Engine, it is important to store the
     pointers to the Graphics Engine module in the context. */
  EwGraphicsEngineAPI = context->GraphicsEngineAPI; 
}


/* Just after Chora interpreter invoked an intrinsic, store the state of all
   relevant (global) variables in the context data structure. */
EW_ENTRYPOINT void EwIntrinsicsEpilog( void* aContext )
{
  YourContextStruct* context = (YourContextStruct*)aContext;

  /* Since this example uses Graphics Engine, it is important to store the
     pointers to the Graphics Engine module in the context. */
  context->GraphicsEngineAPI = EwGraphicsEngineAPI;
}


/* pba */