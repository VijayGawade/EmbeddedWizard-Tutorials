/*******************************************************************************
*
* Embedded Wizard - GUI Solutions by TARA Systems
*
*                                                Copyright (c) TARA Systems GmbH
*                                    written by Paul Banach and Manfred Schweyer
*
********************************************************************************
*
* This file was generated automatically by Embedded Wizard tools based on the
* GUI project configuration and resources provided by you.
*
* Please do not modify this file! Any changes will be lost when it is generated
* again by the Embedded Wizard code generation process.
*
* The template of this heading text can be found in the file 'head.ewt' in the
* directory 'Platforms' of your Embedded Wizard installation directory. If you
* wish to adapt this text, please copy 'head.ewt' into your project directory
* and edit only that copy. Please avoid any modifications of the original
* template file.
*
* License, ownership and responsibility:
*
*   - The generated code is based on your project configuration and forms part
*     of your application. The application-specific content of this file
*     (including project-specific classes, resources and UI logic) is owned by
*     you or your licensors. You remain responsible for the overall design,
*     implementation, testing and validation of your application, including any
*     project-specific code and any changes or additions you make to the
*     generated code. TARA Systems GmbH is not responsible for defects or
*     malfunctions caused by such project-specific content or modifications.
*
*   - The use of Embedded Wizard Studio, the Embedded Wizard command line code
*     generator (ChoraC), the Embedded Wizard technology used to generate this
*     file and any Embedded Wizard Platform Packages and Runtime Components
*     required to build and run the generated code is subject to the Embedded
*     Wizard license terms (as published at https://www.embedded-wizard.de/legal),
*     including in particular:
*
*       - Embedded Wizard Terms and Conditions (EWTC)
*       - Embedded Wizard License Agreement (EWLA)
*       - Embedded Wizard Community License (EWCL)
*
*     The specific agreement(s) applicable to you and the applicable warranties
*     and limitations of liability are exclusively governed by these license
*     terms.
*
* Version  : 15.07
* Profile  : Win32
* Platform : Windows.Software.RGBA8888
*
*******************************************************************************/

#include "ewlocale.h"
#include "_CoreKeyPressHandler.h"
#include "_CoreRoot.h"
#include "_CoreSimpleTouchHandler.h"
#include "_CoreTimer.h"
#include "_CoreView.h"
#include "_ResourcesBitmap.h"
#include "_ViewsFrame.h"
#include "_ViewsImage.h"
#include "_WidgetSetHorizontalSlider.h"
#include "_WidgetSetHorizontalSliderConfig.h"
#include "_WidgetSetPushButton.h"
#include "_WidgetSetPushButtonConfig.h"
#include "_WidgetSetWidgetConfig.h"
#include "Core.h"
#include "Graphics.h"
#include "Views.h"
#include "WidgetSet.h"

/* Constant values used in this 'C' module only. */
static const XColor _Const0000 = { 0xFF, 0xFF, 0xFF, 0xFF };
static const XRect _Const0001 = {{ 0, 0 }, { 200, 50 }};
static const XPoint _Const0002 = { 0, 50 };
static const XPoint _Const0003 = { 200, 50 };
static const XPoint _Const0004 = { 200, 0 };
static const XPoint _Const0005 = { 0, 0 };
static const XRect _Const0006 = {{ 0, 0 }, { 0, 0 }};
static const XRect _Const0007 = {{ -8, -8 }, { 9, 9 }};
static const XRect _Const0008 = {{ 0, 0 }, { 150, 50 }};
static const XPoint _Const0009 = { 150, 50 };
static const XPoint _Const000A = { 150, 0 };

/* Initializer for the class 'WidgetSet::HorizontalSliderConfig' */
void WidgetSetHorizontalSliderConfig__Init( WidgetSetHorizontalSliderConfig _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  WidgetSetWidgetConfig__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( WidgetSetHorizontalSliderConfig );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( WidgetSetHorizontalSliderConfig );

  /* ... and initialize objects, variables, properties, etc. */
  _this->ThumbFrameActive = -1;
  _this->ThumbFrameFocused = -1;
  _this->ThumbFrameDisabled = -1;
  _this->ThumbFrameDefault = -1;
  _this->TrackRightTintActive = _Const0000;
  _this->TrackRightTintDefault = _Const0000;
  _this->TrackRightFrameActive = -1;
  _this->TrackRightFrameFocused = -1;
  _this->TrackRightFrameDisabled = -1;
  _this->TrackRightFrameDefault = -1;
  _this->TrackLeftTintActive = _Const0000;
  _this->TrackLeftTintFocused = _Const0000;
  _this->TrackLeftTintDefault = _Const0000;
  _this->TrackLeftFrameActive = -1;
  _this->TrackLeftFrameFocused = -1;
  _this->TrackLeftFrameDisabled = -1;
  _this->TrackLeftFrameDefault = -1;
}

/* Re-Initializer for the class 'WidgetSet::HorizontalSliderConfig' */
void WidgetSetHorizontalSliderConfig__ReInit( WidgetSetHorizontalSliderConfig _this )
{
  /* At first re-initialize the super class ... */
  WidgetSetWidgetConfig__ReInit( &_this->_.Super );
}

/* Finalizer method for the class 'WidgetSet::HorizontalSliderConfig' */
void WidgetSetHorizontalSliderConfig__Done( WidgetSetHorizontalSliderConfig _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( WidgetSetWidgetConfig );

  /* Don't forget to deinitialize the super class ... */
  WidgetSetWidgetConfig__Done( &_this->_.Super );
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetThumbFrameActive()' */
void WidgetSetHorizontalSliderConfig_OnSetThumbFrameActive( WidgetSetHorizontalSliderConfig _this, 
  XInt32 value )
{
  if ( _this->ThumbFrameActive == value )
    return;

  _this->ThumbFrameActive = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetThumbFrameFocused()' */
void WidgetSetHorizontalSliderConfig_OnSetThumbFrameFocused( WidgetSetHorizontalSliderConfig _this, 
  XInt32 value )
{
  if ( _this->ThumbFrameFocused == value )
    return;

  _this->ThumbFrameFocused = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetThumbFrameDisabled()' */
void WidgetSetHorizontalSliderConfig_OnSetThumbFrameDisabled( WidgetSetHorizontalSliderConfig _this, 
  XInt32 value )
{
  if ( _this->ThumbFrameDisabled == value )
    return;

  _this->ThumbFrameDisabled = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetThumbFrameDefault()' */
void WidgetSetHorizontalSliderConfig_OnSetThumbFrameDefault( WidgetSetHorizontalSliderConfig _this, 
  XInt32 value )
{
  if ( _this->ThumbFrameDefault == value )
    return;

  _this->ThumbFrameDefault = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetThumbBitmapActive()' */
void WidgetSetHorizontalSliderConfig_OnSetThumbBitmapActive( WidgetSetHorizontalSliderConfig _this, 
  ResourcesBitmap value )
{
  if ( _this->ThumbBitmapActive == value )
    return;

  _this->ThumbBitmapActive = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetThumbBitmapFocused()' */
void WidgetSetHorizontalSliderConfig_OnSetThumbBitmapFocused( WidgetSetHorizontalSliderConfig _this, 
  ResourcesBitmap value )
{
  if ( _this->ThumbBitmapFocused == value )
    return;

  _this->ThumbBitmapFocused = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetThumbBitmapDefault()' */
void WidgetSetHorizontalSliderConfig_OnSetThumbBitmapDefault( WidgetSetHorizontalSliderConfig _this, 
  ResourcesBitmap value )
{
  if ( _this->ThumbBitmapDefault == value )
    return;

  _this->ThumbBitmapDefault = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetThumbUpdateAtTouch()' */
void WidgetSetHorizontalSliderConfig_OnSetThumbUpdateAtTouch( WidgetSetHorizontalSliderConfig _this, 
  XBool value )
{
  if ( _this->ThumbUpdateAtTouch == value )
    return;

  _this->ThumbUpdateAtTouch = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetThumbMarginRight()' */
void WidgetSetHorizontalSliderConfig_OnSetThumbMarginRight( WidgetSetHorizontalSliderConfig _this, 
  XInt32 value )
{
  if ( _this->ThumbMarginRight == value )
    return;

  _this->ThumbMarginRight = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetThumbMarginLeft()' */
void WidgetSetHorizontalSliderConfig_OnSetThumbMarginLeft( WidgetSetHorizontalSliderConfig _this, 
  XInt32 value )
{
  if ( _this->ThumbMarginLeft == value )
    return;

  _this->ThumbMarginLeft = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetTrackRightTintActive()' */
void WidgetSetHorizontalSliderConfig_OnSetTrackRightTintActive( WidgetSetHorizontalSliderConfig _this, 
  XColor value )
{
  if ( !EwCompColor( _this->TrackRightTintActive, value ))
    return;

  _this->TrackRightTintActive = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetTrackRightTintDefault()' */
void WidgetSetHorizontalSliderConfig_OnSetTrackRightTintDefault( WidgetSetHorizontalSliderConfig _this, 
  XColor value )
{
  if ( !EwCompColor( _this->TrackRightTintDefault, value ))
    return;

  _this->TrackRightTintDefault = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetTrackRightFrameActive()' */
void WidgetSetHorizontalSliderConfig_OnSetTrackRightFrameActive( WidgetSetHorizontalSliderConfig _this, 
  XInt32 value )
{
  if ( _this->TrackRightFrameActive == value )
    return;

  _this->TrackRightFrameActive = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetTrackRightFrameFocused()' */
void WidgetSetHorizontalSliderConfig_OnSetTrackRightFrameFocused( WidgetSetHorizontalSliderConfig _this, 
  XInt32 value )
{
  if ( _this->TrackRightFrameFocused == value )
    return;

  _this->TrackRightFrameFocused = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetTrackRightFrameDisabled()' */
void WidgetSetHorizontalSliderConfig_OnSetTrackRightFrameDisabled( WidgetSetHorizontalSliderConfig _this, 
  XInt32 value )
{
  if ( _this->TrackRightFrameDisabled == value )
    return;

  _this->TrackRightFrameDisabled = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetTrackRightFrameDefault()' */
void WidgetSetHorizontalSliderConfig_OnSetTrackRightFrameDefault( WidgetSetHorizontalSliderConfig _this, 
  XInt32 value )
{
  if ( _this->TrackRightFrameDefault == value )
    return;

  _this->TrackRightFrameDefault = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetTrackRightBitmapActive()' */
void WidgetSetHorizontalSliderConfig_OnSetTrackRightBitmapActive( WidgetSetHorizontalSliderConfig _this, 
  ResourcesBitmap value )
{
  if ( _this->TrackRightBitmapActive == value )
    return;

  _this->TrackRightBitmapActive = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetTrackRightBitmapFocused()' */
void WidgetSetHorizontalSliderConfig_OnSetTrackRightBitmapFocused( WidgetSetHorizontalSliderConfig _this, 
  ResourcesBitmap value )
{
  if ( _this->TrackRightBitmapFocused == value )
    return;

  _this->TrackRightBitmapFocused = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetTrackRightBitmapDefault()' */
void WidgetSetHorizontalSliderConfig_OnSetTrackRightBitmapDefault( WidgetSetHorizontalSliderConfig _this, 
  ResourcesBitmap value )
{
  if ( _this->TrackRightBitmapDefault == value )
    return;

  _this->TrackRightBitmapDefault = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetTrackLeftTintActive()' */
void WidgetSetHorizontalSliderConfig_OnSetTrackLeftTintActive( WidgetSetHorizontalSliderConfig _this, 
  XColor value )
{
  if ( !EwCompColor( _this->TrackLeftTintActive, value ))
    return;

  _this->TrackLeftTintActive = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetTrackLeftTintFocused()' */
void WidgetSetHorizontalSliderConfig_OnSetTrackLeftTintFocused( WidgetSetHorizontalSliderConfig _this, 
  XColor value )
{
  if ( !EwCompColor( _this->TrackLeftTintFocused, value ))
    return;

  _this->TrackLeftTintFocused = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetTrackLeftTintDefault()' */
void WidgetSetHorizontalSliderConfig_OnSetTrackLeftTintDefault( WidgetSetHorizontalSliderConfig _this, 
  XColor value )
{
  if ( !EwCompColor( _this->TrackLeftTintDefault, value ))
    return;

  _this->TrackLeftTintDefault = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetTrackLeftFrameActive()' */
void WidgetSetHorizontalSliderConfig_OnSetTrackLeftFrameActive( WidgetSetHorizontalSliderConfig _this, 
  XInt32 value )
{
  if ( _this->TrackLeftFrameActive == value )
    return;

  _this->TrackLeftFrameActive = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetTrackLeftFrameFocused()' */
void WidgetSetHorizontalSliderConfig_OnSetTrackLeftFrameFocused( WidgetSetHorizontalSliderConfig _this, 
  XInt32 value )
{
  if ( _this->TrackLeftFrameFocused == value )
    return;

  _this->TrackLeftFrameFocused = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetTrackLeftFrameDisabled()' */
void WidgetSetHorizontalSliderConfig_OnSetTrackLeftFrameDisabled( WidgetSetHorizontalSliderConfig _this, 
  XInt32 value )
{
  if ( _this->TrackLeftFrameDisabled == value )
    return;

  _this->TrackLeftFrameDisabled = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetTrackLeftFrameDefault()' */
void WidgetSetHorizontalSliderConfig_OnSetTrackLeftFrameDefault( WidgetSetHorizontalSliderConfig _this, 
  XInt32 value )
{
  if ( _this->TrackLeftFrameDefault == value )
    return;

  _this->TrackLeftFrameDefault = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetTrackLeftBitmapActive()' */
void WidgetSetHorizontalSliderConfig_OnSetTrackLeftBitmapActive( WidgetSetHorizontalSliderConfig _this, 
  ResourcesBitmap value )
{
  if ( _this->TrackLeftBitmapActive == value )
    return;

  _this->TrackLeftBitmapActive = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetTrackLeftBitmapFocused()' */
void WidgetSetHorizontalSliderConfig_OnSetTrackLeftBitmapFocused( WidgetSetHorizontalSliderConfig _this, 
  ResourcesBitmap value )
{
  if ( _this->TrackLeftBitmapFocused == value )
    return;

  _this->TrackLeftBitmapFocused = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetTrackLeftBitmapDefault()' */
void WidgetSetHorizontalSliderConfig_OnSetTrackLeftBitmapDefault( WidgetSetHorizontalSliderConfig _this, 
  ResourcesBitmap value )
{
  if ( _this->TrackLeftBitmapDefault == value )
    return;

  _this->TrackLeftBitmapDefault = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* Variants derived from the class : 'WidgetSet::HorizontalSliderConfig' */
EW_DEFINE_CLASS_VARIANTS( WidgetSetHorizontalSliderConfig )
EW_END_OF_CLASS_VARIANTS( WidgetSetHorizontalSliderConfig )

/* Virtual Method Table (VMT) for the class : 'WidgetSet::HorizontalSliderConfig' */
EW_DEFINE_CLASS( WidgetSetHorizontalSliderConfig, WidgetSetWidgetConfig, ThumbBitmapActive, 
                 ThumbBitmapActive, ThumbFrameActive, ThumbFrameActive, ThumbFrameActive, 
                 ThumbFrameActive, "WidgetSet::HorizontalSliderConfig" )
EW_END_OF_CLASS( WidgetSetHorizontalSliderConfig )

/* Initializer for the class 'WidgetSet::PushButtonConfig' */
void WidgetSetPushButtonConfig__Init( WidgetSetPushButtonConfig _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  WidgetSetWidgetConfig__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( WidgetSetPushButtonConfig );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( WidgetSetPushButtonConfig );

  /* ... and initialize objects, variables, properties, etc. */
  _this->FaceLayout = CoreLayoutAlignToBottom | CoreLayoutAlignToLeft | CoreLayoutAlignToRight 
  | CoreLayoutAlignToTop | CoreLayoutResizeHorz | CoreLayoutResizeVert;
  _this->FaceFrameActive = -1;
  _this->FaceFrameFocused = -1;
  _this->FaceFrameDefault = -1;
}

/* Re-Initializer for the class 'WidgetSet::PushButtonConfig' */
void WidgetSetPushButtonConfig__ReInit( WidgetSetPushButtonConfig _this )
{
  /* At first re-initialize the super class ... */
  WidgetSetWidgetConfig__ReInit( &_this->_.Super );
}

/* Finalizer method for the class 'WidgetSet::PushButtonConfig' */
void WidgetSetPushButtonConfig__Done( WidgetSetPushButtonConfig _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( WidgetSetWidgetConfig );

  /* Don't forget to deinitialize the super class ... */
  WidgetSetWidgetConfig__Done( &_this->_.Super );
}

/* 'C' function for method : 'WidgetSet::PushButtonConfig.OnSetFaceLayout()' */
void WidgetSetPushButtonConfig_OnSetFaceLayout( WidgetSetPushButtonConfig _this, 
  XSet value )
{
  if ( _this->FaceLayout == value )
    return;

  _this->FaceLayout = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::PushButtonConfig.OnSetFaceFrameActive()' */
void WidgetSetPushButtonConfig_OnSetFaceFrameActive( WidgetSetPushButtonConfig _this, 
  XInt32 value )
{
  if ( _this->FaceFrameActive == value )
    return;

  _this->FaceFrameActive = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::PushButtonConfig.OnSetFaceFrameFocused()' */
void WidgetSetPushButtonConfig_OnSetFaceFrameFocused( WidgetSetPushButtonConfig _this, 
  XInt32 value )
{
  if ( _this->FaceFrameFocused == value )
    return;

  _this->FaceFrameFocused = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::PushButtonConfig.OnSetFaceFrameDefault()' */
void WidgetSetPushButtonConfig_OnSetFaceFrameDefault( WidgetSetPushButtonConfig _this, 
  XInt32 value )
{
  if ( _this->FaceFrameDefault == value )
    return;

  _this->FaceFrameDefault = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::PushButtonConfig.OnSetFaceBitmapActive()' */
void WidgetSetPushButtonConfig_OnSetFaceBitmapActive( WidgetSetPushButtonConfig _this, 
  ResourcesBitmap value )
{
  if ( _this->FaceBitmapActive == value )
    return;

  _this->FaceBitmapActive = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::PushButtonConfig.OnSetFaceBitmapFocused()' */
void WidgetSetPushButtonConfig_OnSetFaceBitmapFocused( WidgetSetPushButtonConfig _this, 
  ResourcesBitmap value )
{
  if ( _this->FaceBitmapFocused == value )
    return;

  _this->FaceBitmapFocused = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::PushButtonConfig.OnSetFaceBitmapDefault()' */
void WidgetSetPushButtonConfig_OnSetFaceBitmapDefault( WidgetSetPushButtonConfig _this, 
  ResourcesBitmap value )
{
  if ( _this->FaceBitmapDefault == value )
    return;

  _this->FaceBitmapDefault = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* Variants derived from the class : 'WidgetSet::PushButtonConfig' */
EW_DEFINE_CLASS_VARIANTS( WidgetSetPushButtonConfig )
EW_END_OF_CLASS_VARIANTS( WidgetSetPushButtonConfig )

/* Virtual Method Table (VMT) for the class : 'WidgetSet::PushButtonConfig' */
EW_DEFINE_CLASS( WidgetSetPushButtonConfig, WidgetSetWidgetConfig, FaceBitmapActive, 
                 FaceBitmapActive, FaceLayout, FaceLayout, FaceLayout, FaceLayout, 
                 "WidgetSet::PushButtonConfig" )
EW_END_OF_CLASS( WidgetSetPushButtonConfig )

/* Initializer for the class 'WidgetSet::WidgetConfig' */
void WidgetSetWidgetConfig__Init( WidgetSetWidgetConfig _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  XObject__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( WidgetSetWidgetConfig );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( WidgetSetWidgetConfig );
}

/* Re-Initializer for the class 'WidgetSet::WidgetConfig' */
void WidgetSetWidgetConfig__ReInit( WidgetSetWidgetConfig _this )
{
  /* At first re-initialize the super class ... */
  XObject__ReInit( &_this->_.Super );
}

/* Finalizer method for the class 'WidgetSet::WidgetConfig' */
void WidgetSetWidgetConfig__Done( WidgetSetWidgetConfig _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( XObject );

  /* Don't forget to deinitialize the super class ... */
  XObject__Done( &_this->_.Super );
}

/* 'C' function for method : 'WidgetSet::WidgetConfig.onInvalidate()' */
void WidgetSetWidgetConfig_onInvalidate( WidgetSetWidgetConfig _this, XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  EwNotifyObjObservers((XObject)_this, 0 );
}

/* Variants derived from the class : 'WidgetSet::WidgetConfig' */
EW_DEFINE_CLASS_VARIANTS( WidgetSetWidgetConfig )
EW_END_OF_CLASS_VARIANTS( WidgetSetWidgetConfig )

/* Virtual Method Table (VMT) for the class : 'WidgetSet::WidgetConfig' */
EW_DEFINE_CLASS( WidgetSetWidgetConfig, XObject, _.VMT, _.VMT, _.VMT, _.VMT, _.VMT, 
                 _.VMT, "WidgetSet::WidgetConfig" )
EW_END_OF_CLASS( WidgetSetWidgetConfig )

/* Initializer for the class 'WidgetSet::HorizontalSlider' */
void WidgetSetHorizontalSlider__Init( WidgetSetHorizontalSlider _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  CoreGroup__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( WidgetSetHorizontalSlider );

  /* ... then construct all embedded objects */
  CoreTimer__Init( &_this->RepetitionTimer, &_this->_.XObject, 0 );
  CoreKeyPressHandler__Init( &_this->KeyHandlerLeft, &_this->_.XObject, 0 );
  CoreKeyPressHandler__Init( &_this->KeyHandlerRight, &_this->_.XObject, 0 );
  CoreSimpleTouchHandler__Init( &_this->TouchHandler, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( WidgetSetHorizontalSlider );

  /* ... and initialize objects, variables, properties, etc. */
  CoreRectView__OnSetBounds( _this, _Const0001 );
  CoreTimer_OnSetPeriod( &_this->RepetitionTimer, 0 );
  CoreTimer_OnSetBegin( &_this->RepetitionTimer, 50 );
  _this->KeyHandlerLeft.Filter = CoreKeyCodeLeft;
  _this->KeyHandlerRight.Filter = CoreKeyCodeRight;
  CoreView_OnSetLayout((CoreView)&_this->TouchHandler, CoreLayoutAlignToBottom | 
  CoreLayoutAlignToLeft | CoreLayoutAlignToRight | CoreLayoutAlignToTop | CoreLayoutResizeHorz 
  | CoreLayoutResizeVert );
  CoreQuadView_OnSetPoint4((CoreQuadView)&_this->TouchHandler, _Const0002 );
  CoreQuadView_OnSetPoint3((CoreQuadView)&_this->TouchHandler, _Const0003 );
  CoreQuadView_OnSetPoint2((CoreQuadView)&_this->TouchHandler, _Const0004 );
  CoreQuadView_OnSetPoint1((CoreQuadView)&_this->TouchHandler, _Const0005 );
  CoreSimpleTouchHandler_OnSetRetargetOffset( &_this->TouchHandler, 16 );
  CoreSimpleTouchHandler_OnSetMaxStrikeCount( &_this->TouchHandler, 100 );
  _this->CurrentValue = 50;
  CoreGroup_Add((CoreGroup)_this, ((CoreView)&_this->TouchHandler ), 0 );
  _this->RepetitionTimer.OnTrigger = EwNewSlot( _this, WidgetSetHorizontalSlider_onRepetitionTimer );
  _this->KeyHandlerLeft.OnRelease = EwNewSlot( _this, WidgetSetHorizontalSlider_onReleaseKey );
  _this->KeyHandlerLeft.OnPress = EwNewSlot( _this, WidgetSetHorizontalSlider_onPressKey );
  _this->KeyHandlerRight.OnRelease = EwNewSlot( _this, WidgetSetHorizontalSlider_onReleaseKey );
  _this->KeyHandlerRight.OnPress = EwNewSlot( _this, WidgetSetHorizontalSlider_onPressKey );
  _this->TouchHandler.OnDrag = EwNewSlot( _this, WidgetSetHorizontalSlider_onDragTouch );
  _this->TouchHandler.OnRelease = EwNewSlot( _this, WidgetSetHorizontalSlider_onReleaseTouch );
  _this->TouchHandler.OnPress = EwNewSlot( _this, WidgetSetHorizontalSlider_onPressTouch );
}

/* Re-Initializer for the class 'WidgetSet::HorizontalSlider' */
void WidgetSetHorizontalSlider__ReInit( WidgetSetHorizontalSlider _this )
{
  /* At first re-initialize the super class ... */
  CoreGroup__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  CoreTimer__ReInit( &_this->RepetitionTimer );
  CoreKeyPressHandler__ReInit( &_this->KeyHandlerLeft );
  CoreKeyPressHandler__ReInit( &_this->KeyHandlerRight );
  CoreSimpleTouchHandler__ReInit( &_this->TouchHandler );
}

/* Finalizer method for the class 'WidgetSet::HorizontalSlider' */
void WidgetSetHorizontalSlider__Done( WidgetSetHorizontalSlider _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( CoreGroup );

  /* Finalize all embedded objects */
  CoreTimer__Done( &_this->RepetitionTimer );
  CoreKeyPressHandler__Done( &_this->KeyHandlerLeft );
  CoreKeyPressHandler__Done( &_this->KeyHandlerRight );
  CoreSimpleTouchHandler__Done( &_this->TouchHandler );

  /* Don't forget to deinitialize the super class ... */
  CoreGroup__Done( &_this->_.Super );
}

/* 'C' function for method : 'WidgetSet::HorizontalSlider.OnSetBounds()' */
void WidgetSetHorizontalSlider_OnSetBounds( WidgetSetHorizontalSlider _this, XRect 
  value )
{
  if ( _this->Appearance != 0 )
  {
    XPoint cs = EwGetRectSize( value );
    XPoint ns = cs;
    XPoint delta;

    if ( ns.X < 0 )
      ns.X = 0;

    if ( ns.Y < 0 )
      ns.Y = 0;

    delta = EwMovePointNeg( ns, cs );

    if ( delta.X != 0 )
    {
      XBool alignToLeft = (( _this->Super3.Layout & CoreLayoutAlignToLeft ) == CoreLayoutAlignToLeft );
      XBool alignToRight = (( _this->Super3.Layout & CoreLayoutAlignToRight ) == 
        CoreLayoutAlignToRight );

      if ( alignToLeft && !alignToRight )
        value.Point2.X = ( value.Point2.X + delta.X );
      else
        if ( !alignToLeft && alignToRight )
          value.Point1.X = ( value.Point1.X - delta.X );
        else
        {
          value.Point1.X = ( value.Point1.X - ( delta.X / 2 ));
          value.Point2.X = ( value.Point1.X + ns.X );
        }
    }

    if ( delta.Y != 0 )
    {
      XBool alignToTop = (( _this->Super3.Layout & CoreLayoutAlignToTop ) == CoreLayoutAlignToTop );
      XBool alignToBottom = (( _this->Super3.Layout & CoreLayoutAlignToBottom ) 
        == CoreLayoutAlignToBottom );

      if ( alignToTop && !alignToBottom )
        value.Point2.Y = ( value.Point2.Y + delta.Y );
      else
        if ( !alignToTop && alignToBottom )
          value.Point1.Y = ( value.Point1.Y - delta.Y );
        else
        {
          value.Point1.Y = ( value.Point1.Y - ( delta.Y / 2 ));
          value.Point2.Y = ( value.Point1.Y + ns.Y );
        }
    }
  }

  CoreGroup_OnSetBounds((CoreGroup)_this, value );
}

/* The method UpdateViewState() is invoked automatically after the state of the 
   component has been changed. This method can be overridden and filled with logic 
   to ensure the visual aspect of the component does reflect its current state. 
   For example, the 'enabled' state of the component can affect its colors (disabled 
   components may appear pale). In this case the logic of the method should modify 
   the respective color properties accordingly to the current 'enabled' state. 
   The current state of the component is passed as a set in the parameter aState. 
   It reflects the very basic component state like its visibility or the ability 
   to react to user inputs. Beside this common state, the method can also involve 
   any other variables used in the component as long as they reflect its current 
   state. For example, the toggle switch component can take in account its toggle 
   state 'on' or 'off' and change accordingly the location of the slider, etc.
   Usually, this method will be invoked automatically by the framework. Optionally 
   you can request its invocation by using the method @InvalidateViewState(). */
void WidgetSetHorizontalSlider_UpdateViewState( WidgetSetHorizontalSlider _this, 
  XSet aState )
{
  XBool needsFrame2;
  XBool needsFrame3;
  XBool needsImage;
  XRect area;
  XChar isState;
  XInt32 marginLeft;
  XInt32 marginRight;
  XInt32 minPos;
  XInt32 maxPos;
  XInt32 newThumbPos;
  XRect r;

  CoreGroup_UpdateViewState((CoreGroup)_this, aState );
  needsFrame2 = (XBool)(( _this->Appearance != 0 ) && ((( _this->Appearance->TrackLeftBitmapDefault 
  != 0 ) || ( _this->Appearance->TrackLeftBitmapFocused != 0 )) || ( _this->Appearance->TrackLeftBitmapActive 
  != 0 )));
  needsFrame3 = (XBool)(( _this->Appearance != 0 ) && ((( _this->Appearance->TrackRightBitmapDefault 
  != 0 ) || ( _this->Appearance->TrackRightBitmapFocused != 0 )) || ( _this->Appearance->TrackRightBitmapActive 
  != 0 )));
  needsImage = (XBool)(( _this->Appearance != 0 ) && ((( _this->Appearance->ThumbBitmapDefault 
  != 0 ) || ( _this->Appearance->ThumbBitmapFocused != 0 )) || ( _this->Appearance->ThumbBitmapActive 
  != 0 )));
  area = EwGetRectORect( _this->Super2.Bounds );

  if ( needsFrame2 && !( _this->frameView2 != 0 ))
  {
    _this->frameView2 = EwNewObject( ViewsFrame, 0 );
    CoreGroup_Add((CoreGroup)_this, ((CoreView)_this->frameView2 ), 0 );
  }
  else
    if ( !needsFrame2 && ( _this->frameView2 != 0 ))
    {
      CoreGroup_Remove((CoreGroup)_this, ((CoreView)_this->frameView2 ));
      _this->frameView2 = 0;
    }

  if ( needsFrame3 && !( _this->frameView3 != 0 ))
  {
    _this->frameView3 = EwNewObject( ViewsFrame, 0 );
    CoreGroup_Add((CoreGroup)_this, ((CoreView)_this->frameView3 ), 0 );
  }
  else
    if ( !needsFrame3 && ( _this->frameView3 != 0 ))
    {
      CoreGroup_Remove((CoreGroup)_this, ((CoreView)_this->frameView3 ));
      _this->frameView3 = 0;
    }

  if ( needsImage && !( _this->imageView != 0 ))
  {
    _this->imageView = EwNewObject( ViewsImage, 0 );
    CoreGroup_Add((CoreGroup)_this, ((CoreView)_this->imageView ), 0 );
  }
  else
    if ( !needsImage && ( _this->imageView != 0 ))
    {
      CoreGroup_Remove((CoreGroup)_this, ((CoreView)_this->imageView ));
      _this->imageView = 0;
    }

  if ( !(( aState & CoreViewStateEnabled ) == CoreViewStateEnabled ))
    isState = 'D';
  else
    if (( _this->touchActive || _this->KeyHandlerRight.Down ) || _this->KeyHandlerLeft.Down )
      isState = 'A';
    else
      if ((( aState & CoreViewStateFocused ) == CoreViewStateFocused ))
        isState = 'F';
      else
        isState = 'E';

  _this->prevState = isState;

  if ( _this->frameView2 != 0 )
    switch ( isState )
    {
      case 'D' :
      case 'A' :
      case 'F' :
      break;

      default :; 
    }

  if ( _this->frameView3 != 0 )
    switch ( isState )
    {
      case 'D' :
      case 'A' :
      case 'F' :
      break;

      default :; 
    }

  if ( _this->imageView != 0 )
    switch ( isState )
    {
      case 'D' :
      case 'A' :
      case 'F' :
      break;

      default :; 
    }

  if ( _this->frameView2 != 0 )
  {
    ResourcesBitmap bitmap;
    XInt32 frameNo;
    XColor tint;

    switch ( isState )
    {
      case 'D' :
      {
        bitmap = 0;
        frameNo = _this->Appearance->TrackLeftFrameDisabled;
      }
      break;

      case 'A' :
      {
        bitmap = _this->Appearance->TrackLeftBitmapActive;
        frameNo = _this->Appearance->TrackLeftFrameActive;
      }
      break;

      case 'F' :
      {
        bitmap = _this->Appearance->TrackLeftBitmapFocused;
        frameNo = _this->Appearance->TrackLeftFrameFocused;
      }
      break;

      default : 
      {
        bitmap = _this->Appearance->TrackLeftBitmapDefault;
        frameNo = _this->Appearance->TrackLeftFrameDefault;
      }
    }

    switch ( isState )
    {
      case 'D' :
        tint = _Const0000;
      break;

      case 'A' :
        tint = _this->Appearance->TrackLeftTintActive;
      break;

      case 'F' :
        tint = _this->Appearance->TrackLeftTintFocused;
      break;

      default : 
        tint = _this->Appearance->TrackLeftTintDefault;
    }

    ViewsFrame_OnSetAnimated( _this->frameView2, (XBool)( frameNo < 0 ));
    ViewsFrame_OnSetColor( _this->frameView2, tint );

    if ( frameNo < 0 )
      frameNo = 0;

    ViewsFrame_OnSetFrameNumber( _this->frameView2, frameNo );
    ViewsFrame_OnSetBitmap( _this->frameView2, bitmap );
    ViewsFrame_OnSetEdges( _this->frameView2, GraphicsEdgesBottom | GraphicsEdgesInterior 
    | GraphicsEdgesLeft | GraphicsEdgesTop );
    CoreView_OnSetStackingPriority((CoreView)_this->frameView2, 54 );
  }

  if ( _this->frameView3 != 0 )
  {
    ResourcesBitmap bitmap;
    XInt32 frameNo;
    XColor tint;

    switch ( isState )
    {
      case 'D' :
      {
        bitmap = 0;
        frameNo = _this->Appearance->TrackRightFrameDisabled;
      }
      break;

      case 'A' :
      {
        bitmap = _this->Appearance->TrackRightBitmapActive;
        frameNo = _this->Appearance->TrackRightFrameActive;
      }
      break;

      case 'F' :
      {
        bitmap = _this->Appearance->TrackRightBitmapFocused;
        frameNo = _this->Appearance->TrackRightFrameFocused;
      }
      break;

      default : 
      {
        bitmap = _this->Appearance->TrackRightBitmapDefault;
        frameNo = _this->Appearance->TrackRightFrameDefault;
      }
    }

    switch ( isState )
    {
      case 'A' :
        tint = _this->Appearance->TrackRightTintActive;
      break;

      case 'D' :
      case 'F' :
        tint = _Const0000;
      break;

      default : 
        tint = _this->Appearance->TrackRightTintDefault;
    }

    ViewsFrame_OnSetAnimated( _this->frameView3, (XBool)( frameNo < 0 ));
    ViewsFrame_OnSetColor( _this->frameView3, tint );

    if ( frameNo < 0 )
      frameNo = 0;

    ViewsFrame_OnSetFrameNumber( _this->frameView3, frameNo );
    ViewsFrame_OnSetBitmap( _this->frameView3, bitmap );
    ViewsFrame_OnSetEdges( _this->frameView3, GraphicsEdgesBottom | GraphicsEdgesInterior 
    | GraphicsEdgesRight | GraphicsEdgesTop );
    CoreView_OnSetStackingPriority((CoreView)_this->frameView3, 35 );
  }

  if ( _this->imageView != 0 )
  {
    ResourcesBitmap bitmap;
    XInt32 frameNo;

    switch ( isState )
    {
      case 'D' :
      {
        bitmap = 0;
        frameNo = _this->Appearance->ThumbFrameDisabled;
      }
      break;

      case 'A' :
      {
        bitmap = _this->Appearance->ThumbBitmapActive;
        frameNo = _this->Appearance->ThumbFrameActive;
      }
      break;

      case 'F' :
      {
        bitmap = _this->Appearance->ThumbBitmapFocused;
        frameNo = _this->Appearance->ThumbFrameFocused;
      }
      break;

      default : 
      {
        bitmap = _this->Appearance->ThumbBitmapDefault;
        frameNo = _this->Appearance->ThumbFrameDefault;
      }
    }

    switch ( isState )
    {
      case 'D' :
      case 'A' :
      case 'F' :
      break;

      default :; 
    }

    ViewsImage_OnSetAnimated( _this->imageView, (XBool)( frameNo < 0 ));
    ViewsImage_OnSetColor( _this->imageView, _Const0000 );

    if ( frameNo < 0 )
      frameNo = 0;

    ViewsImage_OnSetFrameNumber( _this->imageView, frameNo );
    ViewsImage_OnSetBitmap( _this->imageView, bitmap );
    CoreView_OnSetStackingPriority((CoreView)_this->imageView, 74 );
  }

  marginLeft = (( _this->Appearance != 0 )? _this->Appearance->ThumbMarginLeft : 
  0 );
  marginRight = (( _this->Appearance != 0 )? _this->Appearance->ThumbMarginRight 
  : 0 );

  if (( _this->imageView != 0 ) && ( _this->imageView->Bitmap != 0 ))
  {
    XInt32 width = _this->imageView->Bitmap->FrameSize.X;
    marginLeft += ( width / 2 );
    marginRight += ( width - ( width / 2 ));
  }

  minPos = marginLeft;
  maxPos = EwGetRectW( area ) - marginRight;
  newThumbPos = (XInt32)(((XFloat)WidgetSetHorizontalSlider_OnGetCurrentValue( _this ) 
  * (XFloat)( maxPos - minPos )) / 100.0f ) + minPos;

  if ( newThumbPos < marginLeft )
    newThumbPos = marginLeft;

  if ( newThumbPos > ( EwGetRectW( area ) - marginRight ))
    newThumbPos = EwGetRectW( area ) - marginRight;

  if (( _this->frameView2 != 0 ) && ( _this->frameView2->Bitmap != 0 ))
  {
    XPoint s = _this->frameView2->Bitmap->FrameSize;
    XInt32 x2 = EwGetRectW( area );
    XInt32 x = newThumbPos;

    if ( x > x2 )
      x = x2;

    CoreRectView__OnSetBounds( _this->frameView2, EwNewRect( 0, ( EwGetRectH( area ) 
    / 2 ) - ( s.Y / 2 ), x, (( EwGetRectH( area ) / 2 ) - ( s.Y / 2 )) + s.Y ));
    ViewsFrame_OnSetNoEdgesLimit( _this->frameView2, EwSetPointX( _this->frameView2->NoEdgesLimit, 
    x2 - ( s.X / 3 )));
    ViewsFrame_OnSetVisible( _this->frameView2, 1 );
  }

  if (( _this->frameView3 != 0 ) && ( _this->frameView3->Bitmap != 0 ))
  {
    XPoint s = _this->frameView3->Bitmap->FrameSize;
    XInt32 x2 = EwGetRectW( area );
    XInt32 x = newThumbPos;

    if ( x < 0 )
      x = 0;

    CoreRectView__OnSetBounds( _this->frameView3, EwNewRect( x, ( EwGetRectH( area ) 
    / 2 ) - ( s.Y / 2 ), x2, (( EwGetRectH( area ) / 2 ) - ( s.Y / 2 )) + s.Y ));
    ViewsFrame_OnSetNoEdgesLimit( _this->frameView3, EwSetPointX( _this->frameView3->NoEdgesLimit, 
    x2 - ( s.X / 3 )));
    ViewsFrame_OnSetVisible( _this->frameView3, 1 );
  }

  if (( _this->imageView != 0 ) && ( _this->imageView->Bitmap != 0 ))
  {
    XRect thumbArea = EwNewRect2Point( _Const0005, _this->imageView->Bitmap->FrameSize );
    CoreRectView__OnSetBounds( _this->imageView, EwMoveRectPos( EwMoveRectNeg( thumbArea, 
    EwGetRectCenter( thumbArea )), EwNewPoint( newThumbPos, EwGetRectH( area ) / 
    2 )));
  }

  r = _Const0006;

  if ( _this->imageView != 0 )
    r = EwUnionRect( r, _this->imageView->Super1.Bounds );

  CoreGroup_ExtendClipping((CoreGroup)_this, EwGetInt32Max( 2, -r.Point1.X, 0 ), 
  EwGetInt32Max( 2, r.Point2.X - area.Point2.X, 0 ), EwGetInt32Max( 2, -r.Point1.Y, 
  0 ), EwGetInt32Max( 2, r.Point2.Y - area.Point2.Y, 0 ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSlider.onConfigChanged()' */
void WidgetSetHorizontalSlider_onConfigChanged( WidgetSetHorizontalSlider _this, 
  XObject sender )
{
  XEnum oldKeyCodeRight;
  XEnum oldKeyCodeLeft;

  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  oldKeyCodeRight = _this->KeyHandlerRight.Filter;
  oldKeyCodeLeft = _this->KeyHandlerLeft.Filter;
  _this->KeyHandlerRight.Filter = CoreKeyCodeRight;
  _this->KeyHandlerLeft.Filter = CoreKeyCodeLeft;

  if (((( oldKeyCodeRight == CoreKeyCodeNoKey ) || ( oldKeyCodeLeft == CoreKeyCodeNoKey )) 
      && ( _this->KeyHandlerRight.Filter != CoreKeyCodeNoKey )) && ( _this->KeyHandlerLeft.Filter 
      != CoreKeyCodeNoKey ))
    CoreView__ChangeViewState( _this, CoreViewStateFocusable, 0 );

  if ((( oldKeyCodeRight != CoreKeyCodeNoKey ) && ( oldKeyCodeLeft != CoreKeyCodeNoKey )) 
      && (( _this->KeyHandlerRight.Filter == CoreKeyCodeNoKey ) || ( _this->KeyHandlerLeft.Filter 
      == CoreKeyCodeNoKey )))
    CoreView__ChangeViewState( _this, 0, CoreViewStateFocusable );

  CoreTimer_OnSetBegin( &_this->RepetitionTimer, 0 );
  CoreTimer_OnSetPeriod( &_this->RepetitionTimer, 0 );

  if ( _this->Appearance != 0 )
    CoreRectView__OnSetBounds( _this, _this->Super2.Bounds );

  CoreGroup_InvalidateViewState((CoreGroup)_this );
}

/* 'C' function for method : 'WidgetSet::HorizontalSlider.onRepetitionTimer()' */
void WidgetSetHorizontalSlider_onRepetitionTimer( WidgetSetHorizontalSlider _this, 
  XObject sender )
{
  XInt32 oldValue;
  XInt32 newValue;
  XInt32 delta;

  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  oldValue = WidgetSetHorizontalSlider_OnGetCurrentValue( _this );
  newValue = oldValue;
  delta = 1;

  if ( _this->KeyHandlerLeft.Down )
    delta = -1;

  if ( oldValue < 0 )
  {
    newValue = -newValue;
    delta = -delta;
  }

  if ( delta > 0 )
    newValue = ( newValue + delta ) - (( newValue + delta ) % delta );

  if ( delta < 0 )
  {
    if (( newValue % -delta ) != 0 )
      newValue = ( newValue - delta ) - ( newValue % -delta );

    newValue = newValue + delta;
  }

  if ( oldValue < 0 )
    newValue = -newValue;

  WidgetSetHorizontalSlider_OnSetCurrentValue( _this, newValue );

  if ( oldValue == WidgetSetHorizontalSlider_OnGetCurrentValue( _this ))
    return;
}

/* 'C' function for method : 'WidgetSet::HorizontalSlider.onReleaseKey()' */
void WidgetSetHorizontalSlider_onReleaseKey( WidgetSetHorizontalSlider _this, XObject 
  sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  CoreSimpleTouchHandler_OnSetEnabled( &_this->TouchHandler, 1 );
  CoreGroup_InvalidateViewState((CoreGroup)_this );
  CoreTimer_OnSetEnabled( &_this->RepetitionTimer, 0 );
}

/* 'C' function for method : 'WidgetSet::HorizontalSlider.onPressKey()' */
void WidgetSetHorizontalSlider_onPressKey( WidgetSetHorizontalSlider _this, XObject 
  sender )
{
  XInt32 oldValue;
  XInt32 newValue;
  XInt32 delta;

  CoreSimpleTouchHandler_OnSetEnabled( &_this->TouchHandler, 0 );
  CoreGroup_InvalidateViewState((CoreGroup)_this );
  CoreTimer_OnSetEnabled( &_this->RepetitionTimer, 1 );
  oldValue = WidgetSetHorizontalSlider_OnGetCurrentValue( _this );
  newValue = oldValue;
  delta = 1;

  if ( sender == ((XObject)&_this->KeyHandlerLeft ))
    delta = -1;

  if ( oldValue < 0 )
  {
    newValue = -newValue;
    delta = -delta;
  }

  if ( delta > 0 )
    newValue = ( newValue + delta ) - (( newValue + delta ) % delta );

  if ( delta < 0 )
  {
    if (( newValue % -delta ) != 0 )
      newValue = ( newValue - delta ) - ( newValue % -delta );

    newValue = newValue + delta;
  }

  if ( oldValue < 0 )
    newValue = -newValue;

  WidgetSetHorizontalSlider_OnSetCurrentValue( _this, newValue );

  if ( oldValue == WidgetSetHorizontalSlider_OnGetCurrentValue( _this ))
    return;
}

/* 'C' function for method : 'WidgetSet::HorizontalSlider.onDragTouch()' */
void WidgetSetHorizontalSlider_onDragTouch( WidgetSetHorizontalSlider _this, XObject 
  sender )
{
  XInt32 marginLeft;
  XInt32 marginRight;
  XPoint delta;
  XInt32 minPos;
  XInt32 maxPos;
  XInt32 oldValue;
  XInt32 newValue;

  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  if ( !_this->touchActive )
    return;

  marginLeft = 0;
  marginRight = 0;

  if ( _this->Appearance != 0 )
  {
    marginLeft = _this->Appearance->ThumbMarginLeft;
    marginRight = _this->Appearance->ThumbMarginRight;
  }

  delta = EwMovePointNeg( _this->TouchHandler.CurrentPos, _this->TouchHandler.HittingPos );
  minPos = marginLeft;
  maxPos = EwGetRectW( _this->Super2.Bounds ) - marginRight;
  oldValue = WidgetSetHorizontalSlider_OnGetCurrentValue( _this );
  newValue = oldValue;

  if (( _this->imageView != 0 ) && ( _this->imageView->Bitmap != 0 ))
    maxPos = maxPos - EwGetRectW( _this->imageView->Super1.Bounds );

  if ( maxPos > minPos )
    newValue = (XInt32)(((XFloat)delta.X * 100.0f ) / (XFloat)( maxPos - minPos )) 
    + _this->touchStartValue;

  WidgetSetHorizontalSlider_OnSetCurrentValue( _this, newValue );

  if ( oldValue == WidgetSetHorizontalSlider_OnGetCurrentValue( _this ))
    return;
}

/* 'C' function for method : 'WidgetSet::HorizontalSlider.onReleaseTouch()' */
void WidgetSetHorizontalSlider_onReleaseTouch( WidgetSetHorizontalSlider _this, 
  XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  if ( !_this->touchActive )
    return;

  _this->touchActive = 0;
  _this->KeyHandlerRight.Enabled = 1;
  _this->KeyHandlerLeft.Enabled = 1;
  CoreGroup_InvalidateViewState((CoreGroup)_this );
}

/* 'C' function for method : 'WidgetSet::HorizontalSlider.onPressTouch()' */
void WidgetSetHorizontalSlider_onPressTouch( WidgetSetHorizontalSlider _this, XObject 
  sender )
{
  XRect touchArea;
  XBool adjustAtTouch;
  XBool hasThumb;
  XBool insideThumb;

  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  touchArea = EwMoveRectPos( _Const0007, _this->TouchHandler.CurrentPos );
  adjustAtTouch = (XBool)(( _this->Appearance != 0 ) && _this->Appearance->ThumbUpdateAtTouch );
  hasThumb = 0;
  insideThumb = 0;

  if (( _this->imageView != 0 ) && ( _this->imageView->Bitmap != 0 ))
  {
    hasThumb = 1;
    insideThumb = (XBool)!EwIsRectEmpty( EwIntersectRect( _this->imageView->Super1.Bounds, 
    touchArea ));
  }

  if (( hasThumb && !insideThumb ) && !adjustAtTouch )
  {
    CoreRoot root = CoreView__GetRoot( _this );
    CoreSimpleTouchHandler_OnSetEnabled( &_this->TouchHandler, 0 );
    CoreRoot_RetargetCursor( root, ((CoreView)root ), 0, ((CoreView)_this ));
    CoreSimpleTouchHandler_OnSetEnabled( &_this->TouchHandler, 1 );
    return;
  }

  _this->touchActive = 1;
  _this->KeyHandlerRight.Enabled = 0;
  _this->KeyHandlerLeft.Enabled = 0;
  CoreGroup_InvalidateViewState((CoreGroup)_this );
  _this->touchStartValue = WidgetSetHorizontalSlider_OnGetCurrentValue( _this );

  if ( adjustAtTouch && !insideThumb )
  {
    XInt32 marginLeft = 0;
    XInt32 marginRight = 0;
    XInt32 thumbWidth = 0;
    XInt32 hitPos;
    XInt32 minPos;
    XInt32 maxPos;
    XInt32 oldValue;
    XInt32 newValue;

    if ( _this->Appearance != 0 )
    {
      marginLeft = _this->Appearance->ThumbMarginLeft;
      marginRight = _this->Appearance->ThumbMarginRight;
    }

    if (( _this->imageView != 0 ) && ( _this->imageView->Bitmap != 0 ))
      thumbWidth = EwGetRectW( _this->imageView->Super1.Bounds );

    hitPos = _this->TouchHandler.HittingPos.X - ( thumbWidth / 2 );
    minPos = marginLeft;
    maxPos = ( EwGetRectW( _this->Super2.Bounds ) - marginRight ) - thumbWidth;
    oldValue = WidgetSetHorizontalSlider_OnGetCurrentValue( _this );
    newValue = oldValue;

    if ( maxPos > minPos )
      newValue = (XInt32)(((XFloat)( hitPos - minPos ) * 100.0f ) / (XFloat)( maxPos 
      - minPos ));

    WidgetSetHorizontalSlider_OnSetCurrentValue( _this, newValue );

    if ( oldValue == WidgetSetHorizontalSlider_OnGetCurrentValue( _this ))
      return;

    _this->touchStartValue = WidgetSetHorizontalSlider_OnGetCurrentValue( _this );
  }
}

/* 'C' function for method : 'WidgetSet::HorizontalSlider.OnGetCurrentValue()' */
XInt32 WidgetSetHorizontalSlider_OnGetCurrentValue( WidgetSetHorizontalSlider _this )
{
  XInt32 value = _this->CurrentValue;

  if ( value < 0 )
    value = 0;

  if ( value > 100 )
    value = 100;

  return value;
}

/* 'C' function for method : 'WidgetSet::HorizontalSlider.OnSetCurrentValue()' */
void WidgetSetHorizontalSlider_OnSetCurrentValue( WidgetSetHorizontalSlider _this, 
  XInt32 value )
{
  if ( _this->CurrentValue == value )
    return;

  _this->CurrentValue = value;
  CoreGroup_InvalidateViewState((CoreGroup)_this );
}

/* 'C' function for method : 'WidgetSet::HorizontalSlider.OnSetAppearance()' */
void WidgetSetHorizontalSlider_OnSetAppearance( WidgetSetHorizontalSlider _this, 
  WidgetSetHorizontalSliderConfig value )
{
  if ( _this->Appearance == value )
    return;

  if ( _this->Appearance != 0 )
    EwDetachObjObserver( EwNewSlot( _this, WidgetSetHorizontalSlider_onConfigChanged ), 
      (XObject)_this->Appearance, 0 );

  _this->Appearance = value;

  if ( value != 0 )
    EwAttachObjObserver( EwNewSlot( _this, WidgetSetHorizontalSlider_onConfigChanged ), 
      (XObject)value, 0 );

  EwPostSignal( EwNewSlot( _this, WidgetSetHorizontalSlider_onConfigChanged ), ((XObject)_this ));
}

/* Variants derived from the class : 'WidgetSet::HorizontalSlider' */
EW_DEFINE_CLASS_VARIANTS( WidgetSetHorizontalSlider )
EW_END_OF_CLASS_VARIANTS( WidgetSetHorizontalSlider )

/* Virtual Method Table (VMT) for the class : 'WidgetSet::HorizontalSlider' */
EW_DEFINE_CLASS( WidgetSetHorizontalSlider, CoreGroup, RepetitionTimer, imageView, 
                 touchStartValue, touchStartValue, touchStartValue, touchStartValue, 
                 "WidgetSet::HorizontalSlider" )
  CoreRectView_initLayoutContext,
  CoreView_GetRoot,
  CoreGroup_Draw,
  CoreGroup_GetClipping,
  CoreView_HandleEvent,
  CoreGroup_CursorHitTest,
  CoreGroup_AdjustDrawingArea,
  CoreRectView_ArrangeView,
  CoreRectView_MoveView,
  CoreRectView_GetExtent,
  CoreGroup_ChangeViewState,
  WidgetSetHorizontalSlider_OnSetBounds,
  CoreGroup_OnSetFocus,
  CoreGroup_OnSetOpacity,
  CoreGroup_IsCurrentDialog,
  CoreGroup_IsActiveDialog,
  CoreGroup_DispatchEvent,
  CoreGroup_BroadcastEvent,
  WidgetSetHorizontalSlider_UpdateViewState,
  CoreGroup_InvalidateArea,
EW_END_OF_CLASS( WidgetSetHorizontalSlider )

/* Initializer for the class 'WidgetSet::PushButton' */
void WidgetSetPushButton__Init( WidgetSetPushButton _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  CoreGroup__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( WidgetSetPushButton );

  /* ... then construct all embedded objects */
  CoreTimer__Init( &_this->FlashTimer, &_this->_.XObject, 0 );
  CoreKeyPressHandler__Init( &_this->KeyHandler, &_this->_.XObject, 0 );
  CoreSimpleTouchHandler__Init( &_this->TouchHandler, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( WidgetSetPushButton );

  /* ... and initialize objects, variables, properties, etc. */
  CoreRectView__OnSetBounds( _this, _Const0008 );
  CoreTimer_OnSetPeriod( &_this->FlashTimer, 0 );
  CoreTimer_OnSetBegin( &_this->FlashTimer, 50 );
  _this->KeyHandler.Filter = CoreKeyCodeEnter;
  CoreView_OnSetLayout((CoreView)&_this->TouchHandler, CoreLayoutAlignToBottom | 
  CoreLayoutAlignToLeft | CoreLayoutAlignToRight | CoreLayoutAlignToTop | CoreLayoutResizeHorz 
  | CoreLayoutResizeVert );
  CoreQuadView_OnSetPoint4((CoreQuadView)&_this->TouchHandler, _Const0002 );
  CoreQuadView_OnSetPoint3((CoreQuadView)&_this->TouchHandler, _Const0009 );
  CoreQuadView_OnSetPoint2((CoreQuadView)&_this->TouchHandler, _Const000A );
  CoreQuadView_OnSetPoint1((CoreQuadView)&_this->TouchHandler, _Const0005 );
  CoreSimpleTouchHandler_OnSetRetargetOffset( &_this->TouchHandler, 16 );
  CoreSimpleTouchHandler_OnSetMaxStrikeCount( &_this->TouchHandler, 100 );
  CoreGroup_Add((CoreGroup)_this, ((CoreView)&_this->TouchHandler ), 0 );
  _this->FlashTimer.OnTrigger = EwNewSlot( _this, WidgetSetPushButton_onFlashTimer );
  _this->KeyHandler.OnRelease = EwNewSlot( _this, WidgetSetPushButton_onReleaseKey );
  _this->KeyHandler.OnPress = EwNewSlot( _this, WidgetSetPushButton_onPressKey );
  _this->TouchHandler.OnLeave = EwNewSlot( _this, WidgetSetPushButton_onLeaveTouch );
  _this->TouchHandler.OnEnter = EwNewSlot( _this, WidgetSetPushButton_onEnterTouch );
  _this->TouchHandler.OnRelease = EwNewSlot( _this, WidgetSetPushButton_onReleaseTouch );
  _this->TouchHandler.OnPress = EwNewSlot( _this, WidgetSetPushButton_onPressTouch );
}

/* Re-Initializer for the class 'WidgetSet::PushButton' */
void WidgetSetPushButton__ReInit( WidgetSetPushButton _this )
{
  /* At first re-initialize the super class ... */
  CoreGroup__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  CoreTimer__ReInit( &_this->FlashTimer );
  CoreKeyPressHandler__ReInit( &_this->KeyHandler );
  CoreSimpleTouchHandler__ReInit( &_this->TouchHandler );
}

/* Finalizer method for the class 'WidgetSet::PushButton' */
void WidgetSetPushButton__Done( WidgetSetPushButton _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( CoreGroup );

  /* Finalize all embedded objects */
  CoreTimer__Done( &_this->FlashTimer );
  CoreKeyPressHandler__Done( &_this->KeyHandler );
  CoreSimpleTouchHandler__Done( &_this->TouchHandler );

  /* Don't forget to deinitialize the super class ... */
  CoreGroup__Done( &_this->_.Super );
}

/* 'C' function for method : 'WidgetSet::PushButton.OnSetBounds()' */
void WidgetSetPushButton_OnSetBounds( WidgetSetPushButton _this, XRect value )
{
  if ( _this->Appearance != 0 )
  {
    XPoint cs = EwGetRectSize( value );
    XPoint ns = cs;
    XPoint delta;

    if ( ns.X < 0 )
      ns.X = 0;

    if ( ns.Y < 0 )
      ns.Y = 0;

    delta = EwMovePointNeg( ns, cs );

    if ( delta.X != 0 )
    {
      XBool alignToLeft = (( _this->Super3.Layout & CoreLayoutAlignToLeft ) == CoreLayoutAlignToLeft );
      XBool alignToRight = (( _this->Super3.Layout & CoreLayoutAlignToRight ) == 
        CoreLayoutAlignToRight );

      if ( alignToLeft && !alignToRight )
        value.Point2.X = ( value.Point2.X + delta.X );
      else
        if ( !alignToLeft && alignToRight )
          value.Point1.X = ( value.Point1.X - delta.X );
        else
        {
          value.Point1.X = ( value.Point1.X - ( delta.X / 2 ));
          value.Point2.X = ( value.Point1.X + ns.X );
        }
    }

    if ( delta.Y != 0 )
    {
      XBool alignToTop = (( _this->Super3.Layout & CoreLayoutAlignToTop ) == CoreLayoutAlignToTop );
      XBool alignToBottom = (( _this->Super3.Layout & CoreLayoutAlignToBottom ) 
        == CoreLayoutAlignToBottom );

      if ( alignToTop && !alignToBottom )
        value.Point2.Y = ( value.Point2.Y + delta.Y );
      else
        if ( !alignToTop && alignToBottom )
          value.Point1.Y = ( value.Point1.Y - delta.Y );
        else
        {
          value.Point1.Y = ( value.Point1.Y - ( delta.Y / 2 ));
          value.Point2.Y = ( value.Point1.Y + ns.Y );
        }
    }
  }

  CoreGroup_OnSetBounds((CoreGroup)_this, value );
}

/* The method UpdateViewState() is invoked automatically after the state of the 
   component has been changed. This method can be overridden and filled with logic 
   to ensure the visual aspect of the component does reflect its current state. 
   For example, the 'enabled' state of the component can affect its colors (disabled 
   components may appear pale). In this case the logic of the method should modify 
   the respective color properties accordingly to the current 'enabled' state. 
   The current state of the component is passed as a set in the parameter aState. 
   It reflects the very basic component state like its visibility or the ability 
   to react to user inputs. Beside this common state, the method can also involve 
   any other variables used in the component as long as they reflect its current 
   state. For example, the toggle switch component can take in account its toggle 
   state 'on' or 'off' and change accordingly the location of the slider, etc.
   Usually, this method will be invoked automatically by the framework. Optionally 
   you can request its invocation by using the method @InvalidateViewState(). */
void WidgetSetPushButton_UpdateViewState( WidgetSetPushButton _this, XSet aState )
{
  XBool needsFrame;
  XBool needsImage;
  XRect area;
  XChar isState;

  CoreGroup_UpdateViewState((CoreGroup)_this, aState );
  needsFrame = (XBool)(( _this->Appearance != 0 ) && ((( _this->Appearance->FaceBitmapDefault 
  != 0 ) || ( _this->Appearance->FaceBitmapFocused != 0 )) || ( _this->Appearance->FaceBitmapActive 
  != 0 )));
  needsImage = _this->Icon != 0;
  area = EwGetRectORect( _this->Super2.Bounds );

  if ( needsFrame && !( _this->frameView != 0 ))
  {
    _this->frameView = EwNewObject( ViewsFrame, 0 );
    CoreGroup_Add((CoreGroup)_this, ((CoreView)_this->frameView ), 0 );
  }
  else
    if ( !needsFrame && ( _this->frameView != 0 ))
    {
      CoreGroup_Remove((CoreGroup)_this, ((CoreView)_this->frameView ));
      _this->frameView = 0;
    }

  if ( needsImage && !( _this->imageView != 0 ))
  {
    _this->imageView = EwNewObject( ViewsImage, 0 );
    CoreGroup_Add((CoreGroup)_this, ((CoreView)_this->imageView ), 0 );
  }
  else
    if ( !needsImage && ( _this->imageView != 0 ))
    {
      CoreGroup_Remove((CoreGroup)_this, ((CoreView)_this->imageView ));
      _this->imageView = 0;
    }

  if ( !(( aState & CoreViewStateEnabled ) == CoreViewStateEnabled ))
    isState = 'D';
  else
    if ((( _this->TouchHandler.Down && _this->TouchHandler.Inside ) || _this->KeyHandler.Down ) 
        || _this->FlashTimer.Enabled )
      isState = 'A';
    else
      if ((( aState & CoreViewStateFocused ) == CoreViewStateFocused ))
        isState = 'F';
      else
        isState = 'E';

  _this->prevState = isState;

  if (( _this->frameView != 0 ) || (( _this->imageView != 0 ) && ( _this->Appearance 
      != 0 )))
    switch ( isState )
    {
      case 'D' :
      case 'A' :
      case 'F' :
      break;

      default :; 
    }

  if ( _this->frameView != 0 )
  {
    ResourcesBitmap bitmap;
    XInt32 frameNo;
    XSet layout = _this->Appearance->FaceLayout;
    XRect r = EwNewRect( area.Point1.X, area.Point1.Y, area.Point2.X, area.Point2.Y );

    switch ( isState )
    {
      case 'D' :
      {
        bitmap = 0;
        frameNo = -1;
      }
      break;

      case 'A' :
      {
        bitmap = _this->Appearance->FaceBitmapActive;
        frameNo = _this->Appearance->FaceFrameActive;
      }
      break;

      case 'F' :
      {
        bitmap = _this->Appearance->FaceBitmapFocused;
        frameNo = _this->Appearance->FaceFrameFocused;
      }
      break;

      default : 
      {
        bitmap = _this->Appearance->FaceBitmapDefault;
        frameNo = _this->Appearance->FaceFrameDefault;
      }
    }

    switch ( isState )
    {
      case 'D' :
      case 'A' :
      case 'F' :
      break;

      default :; 
    }

    ViewsFrame_OnSetAnimated( _this->frameView, (XBool)( frameNo < 0 ));
    ViewsFrame_OnSetColor( _this->frameView, _Const0000 );

    if ( frameNo < 0 )
      frameNo = 0;

    if (( bitmap != 0 ) && !(( layout & CoreLayoutResizeHorz ) == CoreLayoutResizeHorz ))
    {
      XBool alignToLeft = (( layout & CoreLayoutAlignToLeft ) == CoreLayoutAlignToLeft );
      XBool alignToRight = (( layout & CoreLayoutAlignToRight ) == CoreLayoutAlignToRight );
      XInt32 w = bitmap->FrameSize.X;

      if ( alignToLeft && !alignToRight )
        r.Point2.X = ( r.Point1.X + w );
      else
        if ( !alignToLeft && alignToRight )
          r.Point1.X = ( r.Point2.X - w );
        else
        {
          r.Point1.X = ( r.Point1.X + (( EwGetRectW( r ) / 2 ) - ( w / 2 )));
          r.Point2.X = ( r.Point1.X + w );
        }
    }

    if (( bitmap != 0 ) && !(( layout & CoreLayoutResizeVert ) == CoreLayoutResizeVert ))
    {
      XBool alignToTop = (( layout & CoreLayoutAlignToTop ) == CoreLayoutAlignToTop );
      XBool alignToBottom = (( layout & CoreLayoutAlignToBottom ) == CoreLayoutAlignToBottom );
      XInt32 h = bitmap->FrameSize.Y;

      if ( alignToTop && !alignToBottom )
        r.Point2.Y = ( r.Point1.Y + h );
      else
        if ( !alignToTop && alignToBottom )
          r.Point1.Y = ( r.Point2.Y - h );
        else
        {
          r.Point1.Y = ( r.Point1.Y + (( EwGetRectH( r ) / 2 ) - ( h / 2 )));
          r.Point2.Y = ( r.Point1.Y + h );
        }
    }

    ViewsFrame_OnSetFrameNumber( _this->frameView, frameNo );
    ViewsFrame_OnSetBitmap( _this->frameView, bitmap );
    CoreRectView__OnSetBounds( _this->frameView, r );
    CoreView_OnSetStackingPriority((CoreView)_this->frameView, 16 );
  }

  if (( _this->imageView != 0 ) && ( _this->Appearance != 0 ))
  {
    switch ( isState )
    {
      case 'D' :
      case 'A' :
      case 'F' :
      break;

      default :; 
    }

    switch ( isState )
    {
      case 'D' :
      case 'A' :
      case 'F' :
      break;

      default :; 
    }

    ViewsImage_OnSetAnimated( _this->imageView, 1 );
    CoreRectView__OnSetBounds( _this->imageView, EwNewRect( area.Point1.X, area.Point1.Y, 
    area.Point2.X, area.Point2.Y ));
    ViewsImage_OnSetAlignment( _this->imageView, ViewsImageAlignmentAlignHorzCenter 
    | ViewsImageAlignmentAlignVertCenter );
    ViewsImage_OnSetBitmap( _this->imageView, _this->Icon );
    ViewsImage_OnSetFrameNumber( _this->imageView, 0 );
    ViewsImage_OnSetColor( _this->imageView, _Const0000 );
    CoreView_OnSetStackingPriority((CoreView)_this->imageView, 59 );
  }
  else
    if ( _this->imageView != 0 )
    {
      switch ( isState )
      {
        case 'D' :
        case 'A' :
        case 'F' :
        break;

        default :; 
      }

      CoreRectView__OnSetBounds( _this->imageView, area );
      ViewsImage_OnSetAlignment( _this->imageView, ViewsImageAlignmentAlignHorzCenter 
      | ViewsImageAlignmentAlignVertCenter );
      ViewsImage_OnSetBitmap( _this->imageView, _this->Icon );
      ViewsImage_OnSetFrameNumber( _this->imageView, -1 );
      ViewsImage_OnSetColor( _this->imageView, _Const0000 );
    }

  CoreGroup_ExtendClipping((CoreGroup)_this, 0, 0, 0, 0 );
}

/* 'C' function for method : 'WidgetSet::PushButton.onConfigChanged()' */
void WidgetSetPushButton_onConfigChanged( WidgetSetPushButton _this, XObject sender )
{
  XEnum oldKeyCode;

  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  oldKeyCode = _this->KeyHandler.Filter;
  _this->KeyHandler.Filter = CoreKeyCodeEnter;

  if (( oldKeyCode == CoreKeyCodeNoKey ) && ( _this->KeyHandler.Filter != CoreKeyCodeNoKey ))
    CoreView__ChangeViewState( _this, CoreViewStateFocusable, 0 );

  if (( oldKeyCode != CoreKeyCodeNoKey ) && ( _this->KeyHandler.Filter == CoreKeyCodeNoKey ))
    CoreView__ChangeViewState( _this, 0, CoreViewStateFocusable );

  if ( _this->Appearance != 0 )
    CoreRectView__OnSetBounds( _this, _this->Super2.Bounds );

  CoreGroup_InvalidateViewState((CoreGroup)_this );
}

/* 'C' function for method : 'WidgetSet::PushButton.onFlashTimer()' */
void WidgetSetPushButton_onFlashTimer( WidgetSetPushButton _this, XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  CoreGroup_InvalidateViewState((CoreGroup)_this );
  EwPostSignal( _this->OnActivate, ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::PushButton.onReleaseKey()' */
void WidgetSetPushButton_onReleaseKey( WidgetSetPushButton _this, XObject sender )
{
  XInt32 pressFeedbackDuration;

  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  pressFeedbackDuration = 0;

  if ( _this->Appearance != 0 )
    pressFeedbackDuration = 50;

  CoreSimpleTouchHandler_OnSetEnabled( &_this->TouchHandler, 1 );
  CoreGroup_InvalidateViewState((CoreGroup)_this );

  if ((XInt32)( _this->KeyHandler.Time - _this->onPressKeyTime ) >= pressFeedbackDuration )
    EwPostSignal( _this->OnActivate, ((XObject)_this ));
  else
  {
    CoreTimer_OnSetBegin( &_this->FlashTimer, pressFeedbackDuration - (XInt32)( 
    _this->KeyHandler.Time - _this->onPressKeyTime ));
    CoreTimer_OnSetEnabled( &_this->FlashTimer, 1 );
  }
}

/* 'C' function for method : 'WidgetSet::PushButton.onPressKey()' */
void WidgetSetPushButton_onPressKey( WidgetSetPushButton _this, XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  CoreSimpleTouchHandler_OnSetEnabled( &_this->TouchHandler, 0 );
  CoreGroup_InvalidateViewState((CoreGroup)_this );

  if ( _this->FlashTimer.Enabled )
  {
    EwPostSignal( _this->OnActivate, ((XObject)_this ));
    CoreTimer_OnSetEnabled( &_this->FlashTimer, 0 );
  }

  _this->onPressKeyTime = _this->KeyHandler.Time;
}

/* 'C' function for method : 'WidgetSet::PushButton.onLeaveTouch()' */
void WidgetSetPushButton_onLeaveTouch( WidgetSetPushButton _this, XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  CoreGroup_InvalidateViewState((CoreGroup)_this );
}

/* 'C' function for method : 'WidgetSet::PushButton.onEnterTouch()' */
void WidgetSetPushButton_onEnterTouch( WidgetSetPushButton _this, XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  CoreGroup_InvalidateViewState((CoreGroup)_this );
}

/* 'C' function for method : 'WidgetSet::PushButton.onReleaseTouch()' */
void WidgetSetPushButton_onReleaseTouch( WidgetSetPushButton _this, XObject sender )
{
  XInt32 pressFeedbackDuration;

  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  pressFeedbackDuration = 0;

  if ( _this->Appearance != 0 )
    pressFeedbackDuration = 50;

  _this->KeyHandler.Enabled = 1;

  if ( !_this->TouchHandler.Inside )
    return;

  if ( _this->TouchHandler.AutoDeflected )
    return;

  if ( _this->TouchHandler.HoldPeriod >= pressFeedbackDuration )
    EwPostSignal( _this->OnActivate, ((XObject)_this ));
  else
  {
    CoreTimer_OnSetBegin( &_this->FlashTimer, pressFeedbackDuration - _this->TouchHandler.HoldPeriod );
    CoreTimer_OnSetEnabled( &_this->FlashTimer, 1 );
  }
}

/* 'C' function for method : 'WidgetSet::PushButton.onPressTouch()' */
void WidgetSetPushButton_onPressTouch( WidgetSetPushButton _this, XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  _this->KeyHandler.Enabled = 0;

  if ( _this->FlashTimer.Enabled )
  {
    EwPostSignal( _this->OnActivate, ((XObject)_this ));
    CoreTimer_OnSetEnabled( &_this->FlashTimer, 0 );
  }
}

/* 'C' function for method : 'WidgetSet::PushButton.OnSetIcon()' */
void WidgetSetPushButton_OnSetIcon( WidgetSetPushButton _this, ResourcesBitmap value )
{
  if ( _this->Icon == value )
    return;

  _this->Icon = value;
  CoreGroup_InvalidateViewState((CoreGroup)_this );
}

/* 'C' function for method : 'WidgetSet::PushButton.OnSetLabel()' */
void WidgetSetPushButton_OnSetLabel( WidgetSetPushButton _this, XString value )
{
  if ( !EwCompString( _this->Label, value ))
    return;

  _this->Label = EwShareString( value );
  CoreGroup_InvalidateViewState((CoreGroup)_this );
}

/* 'C' function for method : 'WidgetSet::PushButton.OnSetAppearance()' */
void WidgetSetPushButton_OnSetAppearance( WidgetSetPushButton _this, WidgetSetPushButtonConfig 
  value )
{
  if ( _this->Appearance == value )
    return;

  if ( _this->Appearance != 0 )
    EwDetachObjObserver( EwNewSlot( _this, WidgetSetPushButton_onConfigChanged ), 
      (XObject)_this->Appearance, 0 );

  _this->Appearance = value;

  if ( value != 0 )
    EwAttachObjObserver( EwNewSlot( _this, WidgetSetPushButton_onConfigChanged ), 
      (XObject)value, 0 );

  EwPostSignal( EwNewSlot( _this, WidgetSetPushButton_onConfigChanged ), ((XObject)_this ));
}

/* Variants derived from the class : 'WidgetSet::PushButton' */
EW_DEFINE_CLASS_VARIANTS( WidgetSetPushButton )
EW_END_OF_CLASS_VARIANTS( WidgetSetPushButton )

/* Virtual Method Table (VMT) for the class : 'WidgetSet::PushButton' */
EW_DEFINE_CLASS( WidgetSetPushButton, CoreGroup, FlashTimer, imageView, OnActivate, 
                 Label, Label, onPressKeyTime, "WidgetSet::PushButton" )
  CoreRectView_initLayoutContext,
  CoreView_GetRoot,
  CoreGroup_Draw,
  CoreGroup_GetClipping,
  CoreView_HandleEvent,
  CoreGroup_CursorHitTest,
  CoreGroup_AdjustDrawingArea,
  CoreRectView_ArrangeView,
  CoreRectView_MoveView,
  CoreRectView_GetExtent,
  CoreGroup_ChangeViewState,
  WidgetSetPushButton_OnSetBounds,
  CoreGroup_OnSetFocus,
  CoreGroup_OnSetOpacity,
  CoreGroup_IsCurrentDialog,
  CoreGroup_IsActiveDialog,
  CoreGroup_DispatchEvent,
  CoreGroup_BroadcastEvent,
  WidgetSetPushButton_UpdateViewState,
  CoreGroup_InvalidateArea,
EW_END_OF_CLASS( WidgetSetPushButton )

/* Embedded Wizard */
