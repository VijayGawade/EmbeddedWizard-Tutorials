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
#include "_ApplicationApplication.h"
#include "_ApplicationBrewingDialog.h"
#include "_ApplicationDeviceClass.h"
#include "_ApplicationSelectionDialog.h"
#include "_CoreGroup.h"
#include "_CoreSystemEvent.h"
#include "_CoreSystemEventHandler.h"
#include "_CoreView.h"
#include "_EffectsFadeInOutTransition.h"
#include "_EffectsTransition.h"
#include "_GraphicsArcPath.h"
#include "_GraphicsPath.h"
#include "_ResourcesBitmap.h"
#include "_ResourcesFont.h"
#include "_ViewsImage.h"
#include "_ViewsLine.h"
#include "_ViewsRectangle.h"
#include "_ViewsStrokePath.h"
#include "_ViewsText.h"
#include "_WidgetSetHorizontalSlider.h"
#include "_WidgetSetHorizontalSliderConfig.h"
#include "_WidgetSetPushButton.h"
#include "_WidgetSetPushButtonConfig.h"
#include "Application.h"
#include "Core.h"
#include "Graphics.h"
#include "Views.h"

/* Compressed strings for the language 'Default'. */
EW_CONST_STRING_PRAGMA static const unsigned int _StringsDefault0[] =
{
  0x00000060, /* ratio 87.50 % */
  0xB8000F00, 0x00060452, 0x244A0010, 0xC0D0C004, 0x150822C0, 0x9028642A, 0x65001520,
  0x4001E000, 0x8A802187, 0x2800AE45, 0x80082002, 0x3C131E25, 0xA2E0029C, 0x004F0014,
  0xC4700138, 0x438782A3, 0x00018400, 0x34802387, 0x7000DE00, 0x4068B1E3, 0x00000000
};

/* Constant values used in this 'C' module only. */
static const XColor _Const0000 = { 0xFF, 0xFF, 0xFF, 0xC8 };
static const XRect _Const0001 = {{ 0, 0 }, { 480, 272 }};
static const XColor _Const0002 = { 0x00, 0x00, 0x00, 0x99 };
static const XRect _Const0003 = {{ 131, 36 }, { 385, 236 }};
static const XRect _Const0004 = {{ 131, 36 }, { 331, 236 }};
static const XPoint _Const0005 = { 100, 100 };
static const XRect _Const0006 = {{ 155, 99 }, { 309, 171 }};
static const XStringRes _Const0007 = { _StringsDefault0, 0x0002 };
static const XColor _Const0008 = { 0xFF, 0xFF, 0xFF, 0x7D };
static const XStringRes _Const0009 = { _StringsDefault0, 0x0009 };
static const XRect _Const000A = {{ 0, 0 }, { 120, 50 }};
static const XStringRes _Const000B = { _StringsDefault0, 0x000F };
static const XRect _Const000C = {{ 0, 120 }, { 90, 147 }};
static const XStringRes _Const000D = { _StringsDefault0, 0x0016 };
static const XRect _Const000E = {{ 390, 120 }, { 479, 147 }};
static const XStringRes _Const000F = { _StringsDefault0, 0x001D };
static const XPoint _Const0010 = { 340, 73 };
static const XPoint _Const0011 = { 140, 73 };
static const XRect _Const0012 = {{ 205, 186 }, { 275, 256 }};
static const XStringRes _Const0013 = { _StringsDefault0, 0x0026 };
static const XRect _Const0014 = {{ 95, 105 }, { 385, 165 }};
static const XRect _Const0015 = {{ 0, 0 }, { 480, 280 }};
static const XColor _Const0016 = { 0x00, 0x00, 0x00, 0xFF };

/* This is an instance of the interface to the underlying device. Through this instance 
   the GUI can communicate with the device. */
EW_DEFINE_AUTOOBJECT( ApplicationDevice, ApplicationDeviceClass )

/* Initializer for the auto object 'Application::Device' */
void ApplicationDevice__Init( ApplicationDeviceClass _this )
{
  EW_UNUSED_ARG( _this );
}

/* Re-Initializer for the auto object 'Application::Device' */
void ApplicationDevice__ReInit( ApplicationDeviceClass _this )
{
  EW_UNUSED_ARG( _this );
}

/* Table with links to derived variants of the auto object : 'Application::Device' */
EW_DEFINE_AUTOOBJECT_VARIANTS( ApplicationDevice )
EW_END_OF_AUTOOBJECT_VARIANTS( ApplicationDevice )

/* Initializer for the class 'Application::DeviceClass' */
void ApplicationDeviceClass__Init( ApplicationDeviceClass _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  TemplatesDeviceClass__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ApplicationDeviceClass );

  /* ... then construct all embedded objects */
  CoreSystemEvent__Init( &_this->BrewingInProgressEvent, &_this->_.XObject, 0 );
  CoreSystemEvent__Init( &_this->BrewingFinishedEvent, &_this->_.XObject, 0 );
  CoreSystemEvent__Init( &_this->BrewingStartedEvent, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ApplicationDeviceClass );
}

/* Re-Initializer for the class 'Application::DeviceClass' */
void ApplicationDeviceClass__ReInit( ApplicationDeviceClass _this )
{
  /* At first re-initialize the super class ... */
  TemplatesDeviceClass__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  CoreSystemEvent__ReInit( &_this->BrewingInProgressEvent );
  CoreSystemEvent__ReInit( &_this->BrewingFinishedEvent );
  CoreSystemEvent__ReInit( &_this->BrewingStartedEvent );
}

/* Finalizer method for the class 'Application::DeviceClass' */
void ApplicationDeviceClass__Done( ApplicationDeviceClass _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( TemplatesDeviceClass );

  /* Finalize all embedded objects */
  CoreSystemEvent__Done( &_this->BrewingInProgressEvent );
  CoreSystemEvent__Done( &_this->BrewingFinishedEvent );
  CoreSystemEvent__Done( &_this->BrewingStartedEvent );

  /* Don't forget to deinitialize the super class ... */
  TemplatesDeviceClass__Done( &_this->_.Super );
}

/* This method is intended to be called by the device to notify the GUI application 
   about the progress of the brewing process. */
void ApplicationDeviceClass_TriggerBrewingInProgress( ApplicationDeviceClass _this )
{
  CoreSystemEvent_Trigger( &_this->BrewingInProgressEvent, 0, 0 );
}

/* Wrapper function for the non virtual method : 'Application::DeviceClass.TriggerBrewingInProgress()' */
void ApplicationDeviceClass__TriggerBrewingInProgress( void* _this )
{
  ApplicationDeviceClass_TriggerBrewingInProgress((ApplicationDeviceClass)_this );
}

/* This method is intended to be called by the device to notify the GUI application 
   about the end of the brewing process. */
void ApplicationDeviceClass_TriggerBrewingFinished( ApplicationDeviceClass _this )
{
  CoreSystemEvent_Trigger( &_this->BrewingFinishedEvent, 0, 0 );
}

/* Wrapper function for the non virtual method : 'Application::DeviceClass.TriggerBrewingFinished()' */
void ApplicationDeviceClass__TriggerBrewingFinished( void* _this )
{
  ApplicationDeviceClass_TriggerBrewingFinished((ApplicationDeviceClass)_this );
}

/* This method is intended to be called by the device to notify the GUI application 
   about the start of the brewing process. */
void ApplicationDeviceClass_TriggerBrewingStarted( ApplicationDeviceClass _this )
{
  CoreSystemEvent_Trigger( &_this->BrewingStartedEvent, 0, 0 );
}

/* Wrapper function for the non virtual method : 'Application::DeviceClass.TriggerBrewingStarted()' */
void ApplicationDeviceClass__TriggerBrewingStarted( void* _this )
{
  ApplicationDeviceClass_TriggerBrewingStarted((ApplicationDeviceClass)_this );
}

/* This method implements a device command to query the progress of the brewing 
   process. */
XInt32 ApplicationDeviceClass_GetBrewingProgress( ApplicationDeviceClass _this )
{
  XInt32 progress;

  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );

  progress = 0;
  {
    /* Implement here your C code to query how the brewing process
       progresses in your device. If necessary predeclare the C 
       functions intended to be used here. For example: */
    extern int YourDevice_QueryBrewingProgress( void );

    progress = YourDevice_QueryBrewingProgress();
  }
  return progress;
}

/* Wrapper function for the non virtual method : 'Application::DeviceClass.GetBrewingProgress()' */
XInt32 ApplicationDeviceClass__GetBrewingProgress( void* _this )
{
  return ApplicationDeviceClass_GetBrewingProgress((ApplicationDeviceClass)_this );
}

/* This method implements a device command to start the brewing process. */
void ApplicationDeviceClass_StartBrewing( ApplicationDeviceClass _this, XInt32 aCoffeeStrength )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );

  {
    /* Implement here your C code to start the brewing process in
       the device. If necessary predeclare the C functions intended
       to be used here. For example: */
    extern void YourDevice_StartBrewing( int aStrength );

    YourDevice_StartBrewing( aCoffeeStrength );
  }
}

/* Variants derived from the class : 'Application::DeviceClass' */
EW_DEFINE_CLASS_VARIANTS( ApplicationDeviceClass )
EW_END_OF_CLASS_VARIANTS( ApplicationDeviceClass )

/* Virtual Method Table (VMT) for the class : 'Application::DeviceClass' */
EW_DEFINE_CLASS( ApplicationDeviceClass, TemplatesDeviceClass, BrewingInProgressEvent, 
                 _.VMT, _.VMT, _.VMT, _.VMT, _.VMT, "Application::DeviceClass" )
EW_END_OF_CLASS( ApplicationDeviceClass )

/* This object contains configuration information for a transition between two dialogs 
   (screens). */
EW_DEFINE_AUTOOBJECT( ApplicationFadeInOutCentered, EffectsFadeInOutTransition )

/* Initializer for the auto object 'Application::FadeInOutCentered' */
void ApplicationFadeInOutCentered__Init( EffectsFadeInOutTransition _this )
{
  _this->Duration = 200;
}

/* Re-Initializer for the auto object 'Application::FadeInOutCentered' */
void ApplicationFadeInOutCentered__ReInit( EffectsFadeInOutTransition _this )
{
  EW_UNUSED_ARG( _this );
}

/* Table with links to derived variants of the auto object : 'Application::FadeInOutCentered' */
EW_DEFINE_AUTOOBJECT_VARIANTS( ApplicationFadeInOutCentered )
EW_END_OF_AUTOOBJECT_VARIANTS( ApplicationFadeInOutCentered )

/* This object contains configuration information for a push button widget. */
EW_DEFINE_AUTOOBJECT( ApplicationPushButtonConfig, WidgetSetPushButtonConfig )

/* Initializer for the auto object 'Application::PushButtonConfig' */
void ApplicationPushButtonConfig__Init( WidgetSetPushButtonConfig _this )
{
  WidgetSetPushButtonConfig_OnSetFaceLayout( _this, CoreLayoutAlignToBottom | CoreLayoutAlignToLeft 
  | CoreLayoutAlignToRight | CoreLayoutAlignToTop );
  WidgetSetPushButtonConfig_OnSetFaceFrameActive( _this, 1 );
  WidgetSetPushButtonConfig_OnSetFaceFrameFocused( _this, 0 );
  WidgetSetPushButtonConfig_OnSetFaceFrameDefault( _this, 0 );
  WidgetSetPushButtonConfig_OnSetFaceBitmapActive( _this, EwLoadResource( &ApplicationButtonFace, 
  ResourcesBitmap ));
  WidgetSetPushButtonConfig_OnSetFaceBitmapFocused( _this, EwLoadResource( &ApplicationButtonFace, 
  ResourcesBitmap ));
  WidgetSetPushButtonConfig_OnSetFaceBitmapDefault( _this, EwLoadResource( &ApplicationButtonFace, 
  ResourcesBitmap ));
}

/* Re-Initializer for the auto object 'Application::PushButtonConfig' */
void ApplicationPushButtonConfig__ReInit( WidgetSetPushButtonConfig _this )
{
  EW_UNUSED_ARG( _this );
}

/* Table with links to derived variants of the auto object : 'Application::PushButtonConfig' */
EW_DEFINE_AUTOOBJECT_VARIANTS( ApplicationPushButtonConfig )
EW_END_OF_AUTOOBJECT_VARIANTS( ApplicationPushButtonConfig )

/* This object contains configuration information for a slider widget. */
EW_DEFINE_AUTOOBJECT( ApplicationHorizontalSliderConfig, WidgetSetHorizontalSliderConfig )

/* Initializer for the auto object 'Application::HorizontalSliderConfig' */
void ApplicationHorizontalSliderConfig__Init( WidgetSetHorizontalSliderConfig _this )
{
  WidgetSetHorizontalSliderConfig_OnSetThumbUpdateAtTouch( _this, 1 );
  WidgetSetHorizontalSliderConfig_OnSetThumbMarginRight( _this, 6 );
  WidgetSetHorizontalSliderConfig_OnSetThumbMarginLeft( _this, 6 );
  WidgetSetHorizontalSliderConfig_OnSetThumbFrameActive( _this, 0 );
  WidgetSetHorizontalSliderConfig_OnSetThumbFrameFocused( _this, 0 );
  WidgetSetHorizontalSliderConfig_OnSetThumbFrameDisabled( _this, 0 );
  WidgetSetHorizontalSliderConfig_OnSetThumbFrameDefault( _this, 0 );
  WidgetSetHorizontalSliderConfig_OnSetThumbBitmapActive( _this, EwLoadResource( 
  &ApplicationSliderThumb, ResourcesBitmap ));
  WidgetSetHorizontalSliderConfig_OnSetThumbBitmapFocused( _this, EwLoadResource( 
  &ApplicationSliderThumb, ResourcesBitmap ));
  WidgetSetHorizontalSliderConfig_OnSetThumbBitmapDefault( _this, EwLoadResource( 
  &ApplicationSliderThumb, ResourcesBitmap ));
  WidgetSetHorizontalSliderConfig_OnSetTrackRightTintActive( _this, _Const0000 );
  WidgetSetHorizontalSliderConfig_OnSetTrackRightTintDefault( _this, _Const0000 );
  WidgetSetHorizontalSliderConfig_OnSetTrackRightFrameActive( _this, 0 );
  WidgetSetHorizontalSliderConfig_OnSetTrackRightFrameFocused( _this, 0 );
  WidgetSetHorizontalSliderConfig_OnSetTrackRightFrameDisabled( _this, 0 );
  WidgetSetHorizontalSliderConfig_OnSetTrackRightFrameDefault( _this, 0 );
  WidgetSetHorizontalSliderConfig_OnSetTrackRightBitmapActive( _this, EwLoadResource( 
  &ApplicationSliderBack, ResourcesBitmap ));
  WidgetSetHorizontalSliderConfig_OnSetTrackRightBitmapFocused( _this, EwLoadResource( 
  &ApplicationSliderBack, ResourcesBitmap ));
  WidgetSetHorizontalSliderConfig_OnSetTrackRightBitmapDefault( _this, EwLoadResource( 
  &ApplicationSliderBack, ResourcesBitmap ));
  WidgetSetHorizontalSliderConfig_OnSetTrackLeftTintActive( _this, _Const0000 );
  WidgetSetHorizontalSliderConfig_OnSetTrackLeftTintFocused( _this, _Const0000 );
  WidgetSetHorizontalSliderConfig_OnSetTrackLeftTintDefault( _this, _Const0000 );
  WidgetSetHorizontalSliderConfig_OnSetTrackLeftFrameActive( _this, 0 );
  WidgetSetHorizontalSliderConfig_OnSetTrackLeftFrameFocused( _this, 0 );
  WidgetSetHorizontalSliderConfig_OnSetTrackLeftFrameDisabled( _this, 0 );
  WidgetSetHorizontalSliderConfig_OnSetTrackLeftFrameDefault( _this, 0 );
  WidgetSetHorizontalSliderConfig_OnSetTrackLeftBitmapActive( _this, EwLoadResource( 
  &ApplicationSliderFront, ResourcesBitmap ));
  WidgetSetHorizontalSliderConfig_OnSetTrackLeftBitmapFocused( _this, EwLoadResource( 
  &ApplicationSliderFront, ResourcesBitmap ));
  WidgetSetHorizontalSliderConfig_OnSetTrackLeftBitmapDefault( _this, EwLoadResource( 
  &ApplicationSliderFront, ResourcesBitmap ));
}

/* Re-Initializer for the auto object 'Application::HorizontalSliderConfig' */
void ApplicationHorizontalSliderConfig__ReInit( WidgetSetHorizontalSliderConfig _this )
{
  EW_UNUSED_ARG( _this );
}

/* Table with links to derived variants of the auto object : 'Application::HorizontalSliderConfig' */
EW_DEFINE_AUTOOBJECT_VARIANTS( ApplicationHorizontalSliderConfig )
EW_END_OF_AUTOOBJECT_VARIANTS( ApplicationHorizontalSliderConfig )

/* Include a file containing the font resource : 'Application::SmallFont' */
#include "_ApplicationSmallFont.h"

/* Table with links to derived variants of the font resource : 'Application::SmallFont' */
EW_RES_WITHOUT_VARIANTS( ApplicationSmallFont )

/* Include a file containing the font resource : 'Application::BigFont' */
#include "_ApplicationBigFont.h"

/* Table with links to derived variants of the font resource : 'Application::BigFont' */
EW_RES_WITHOUT_VARIANTS( ApplicationBigFont )

/* Include a file containing the bitmap resource : 'Application::PlayIcon' */
#include "_ApplicationPlayIcon.h"

/* Table with links to derived variants of the bitmap resource : 'Application::PlayIcon' */
EW_RES_WITHOUT_VARIANTS( ApplicationPlayIcon )

/* Include a file containing the bitmap resource : 'Application::ButtonFace' */
#include "_ApplicationButtonFace.h"

/* Table with links to derived variants of the bitmap resource : 'Application::ButtonFace' */
EW_RES_WITHOUT_VARIANTS( ApplicationButtonFace )

/* Include a file containing the bitmap resource : 'Application::Cup' */
#include "_ApplicationCup.h"

/* Table with links to derived variants of the bitmap resource : 'Application::Cup' */
EW_RES_WITHOUT_VARIANTS( ApplicationCup )

/* Initializer for the class 'Application::BrewingDialog' */
void ApplicationBrewingDialog__Init( ApplicationBrewingDialog _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  CoreGroup__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ApplicationBrewingDialog );

  /* ... then construct all embedded objects */
  GraphicsArcPath__Init( &_this->ArcPath, &_this->_.XObject, 0 );
  ViewsRectangle__Init( &_this->Background, &_this->_.XObject, 0 );
  ViewsImage__Init( &_this->CupImage, &_this->_.XObject, 0 );
  ViewsStrokePath__Init( &_this->StrokePath, &_this->_.XObject, 0 );
  ViewsText__Init( &_this->ProgressText, &_this->_.XObject, 0 );
  CoreSystemEventHandler__Init( &_this->SystemEventHandler, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ApplicationBrewingDialog );

  /* ... and initialize objects, variables, properties, etc. */
  CoreRectView__OnSetBounds( _this, _Const0001 );
  GraphicsArcPath_OnSetEndAngle( &_this->ArcPath, -90.0f );
  GraphicsArcPath_OnSetStartAngle( &_this->ArcPath, -90.0f );
  GraphicsArcPath_OnSetRadius( &_this->ArcPath, 67.0f );
  GraphicsArcPath_OnSetStyle( &_this->ArcPath, GraphicsArcStyleArc );
  CoreRectView__OnSetBounds( &_this->Background, _Const0001 );
  ViewsRectangle_OnSetColor( &_this->Background, _Const0002 );
  CoreRectView__OnSetBounds( &_this->CupImage, _Const0003 );
  CoreRectView__OnSetBounds( &_this->StrokePath, _Const0004 );
  ViewsStrokePath_OnSetOffset( &_this->StrokePath, _Const0005 );
  ViewsStrokePath_OnSetEndCap( &_this->StrokePath, GraphicsPathCapRound );
  ViewsStrokePath_OnSetStartCap( &_this->StrokePath, GraphicsPathCapRound );
  ViewsStrokePath_OnSetWidth( &_this->StrokePath, 14.0f );
  CoreRectView__OnSetBounds( &_this->ProgressText, _Const0006 );
  ViewsText_OnSetAlignment( &_this->ProgressText, ViewsTextAlignmentAlignHorzCenter 
  | ViewsTextAlignmentAlignVertCenter );
  ViewsText_OnSetString( &_this->ProgressText, EwLoadString( &_Const0007 ));
  ViewsText_OnSetColor( &_this->ProgressText, _Const0008 );
  CoreGroup_Add((CoreGroup)_this, ((CoreView)&_this->Background ), 0 );
  CoreGroup_Add((CoreGroup)_this, ((CoreView)&_this->CupImage ), 0 );
  CoreGroup_Add((CoreGroup)_this, ((CoreView)&_this->StrokePath ), 0 );
  CoreGroup_Add((CoreGroup)_this, ((CoreView)&_this->ProgressText ), 0 );
  ViewsImage_OnSetBitmap( &_this->CupImage, EwLoadResource( &ApplicationCup, ResourcesBitmap ));
  ViewsStrokePath_OnSetPath( &_this->StrokePath, ((GraphicsPath)&_this->ArcPath ));
  ViewsText_OnSetFont( &_this->ProgressText, EwLoadResource( &ApplicationBigFont, 
  ResourcesFont ));
  _this->SystemEventHandler.OnEvent = EwNewSlot( _this, ApplicationBrewingDialog_onBrewingProgress );
  CoreSystemEventHandler_OnSetEvent( &_this->SystemEventHandler, &EwGetAutoObject( 
  &ApplicationDevice, ApplicationDeviceClass )->BrewingInProgressEvent );
}

/* Re-Initializer for the class 'Application::BrewingDialog' */
void ApplicationBrewingDialog__ReInit( ApplicationBrewingDialog _this )
{
  /* At first re-initialize the super class ... */
  CoreGroup__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  GraphicsArcPath__ReInit( &_this->ArcPath );
  ViewsRectangle__ReInit( &_this->Background );
  ViewsImage__ReInit( &_this->CupImage );
  ViewsStrokePath__ReInit( &_this->StrokePath );
  ViewsText__ReInit( &_this->ProgressText );
  CoreSystemEventHandler__ReInit( &_this->SystemEventHandler );
}

/* Finalizer method for the class 'Application::BrewingDialog' */
void ApplicationBrewingDialog__Done( ApplicationBrewingDialog _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( CoreGroup );

  /* Finalize all embedded objects */
  GraphicsArcPath__Done( &_this->ArcPath );
  ViewsRectangle__Done( &_this->Background );
  ViewsImage__Done( &_this->CupImage );
  ViewsStrokePath__Done( &_this->StrokePath );
  ViewsText__Done( &_this->ProgressText );
  CoreSystemEventHandler__Done( &_this->SystemEventHandler );

  /* Don't forget to deinitialize the super class ... */
  CoreGroup__Done( &_this->_.Super );
}

/* This slot method is executed when the associated property observer 'BrewingProgressObserver' 
   is notified. */
void ApplicationBrewingDialog_onBrewingProgress( ApplicationBrewingDialog _this, 
  XObject sender )
{
  XInt32 progress;

  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  progress = ApplicationDeviceClass_GetBrewingProgress( EwGetAutoObject( &ApplicationDevice, 
  ApplicationDeviceClass ));
  ViewsText_OnSetString( &_this->ProgressText, EwConcatString( EwNewStringInt( progress, 
  0, 10 ), EwLoadString( &_Const0009 )));
  GraphicsArcPath_OnSetEndAngle( &_this->ArcPath, ( 3.6f * (XFloat)progress ) - 
  90.0f );
}

/* Variants derived from the class : 'Application::BrewingDialog' */
EW_DEFINE_CLASS_VARIANTS( ApplicationBrewingDialog )
EW_END_OF_CLASS_VARIANTS( ApplicationBrewingDialog )

/* Virtual Method Table (VMT) for the class : 'Application::BrewingDialog' */
EW_DEFINE_CLASS( ApplicationBrewingDialog, CoreGroup, ArcPath, _.VMT, _.VMT, _.VMT, 
                 _.VMT, _.VMT, "Application::BrewingDialog" )
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
  CoreGroup_OnSetBounds,
  CoreGroup_OnSetFocus,
  CoreGroup_OnSetOpacity,
  CoreGroup_IsCurrentDialog,
  CoreGroup_IsActiveDialog,
  CoreGroup_DispatchEvent,
  CoreGroup_BroadcastEvent,
  CoreGroup_UpdateViewState,
  CoreGroup_InvalidateArea,
EW_END_OF_CLASS( ApplicationBrewingDialog )

/* Include a file containing the bitmap resource : 'Application::SliderFront' */
#include "_ApplicationSliderFront.h"

/* Table with links to derived variants of the bitmap resource : 'Application::SliderFront' */
EW_RES_WITHOUT_VARIANTS( ApplicationSliderFront )

/* Include a file containing the bitmap resource : 'Application::SliderThumb' */
#include "_ApplicationSliderThumb.h"

/* Table with links to derived variants of the bitmap resource : 'Application::SliderThumb' */
EW_RES_WITHOUT_VARIANTS( ApplicationSliderThumb )

/* Include a file containing the bitmap resource : 'Application::SliderBack' */
#include "_ApplicationSliderBack.h"

/* Table with links to derived variants of the bitmap resource : 'Application::SliderBack' */
EW_RES_WITHOUT_VARIANTS( ApplicationSliderBack )

/* Include a file containing the bitmap resource : 'Application::BackgroundCup' */
#include "_ApplicationBackgroundCup.h"

/* Table with links to derived variants of the bitmap resource : 'Application::BackgroundCup' */
EW_RES_WITHOUT_VARIANTS( ApplicationBackgroundCup )

/* Initializer for the class 'Application::SelectionDialog' */
void ApplicationSelectionDialog__Init( ApplicationSelectionDialog _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  CoreGroup__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ApplicationSelectionDialog );

  /* ... then construct all embedded objects */
  ViewsImage__Init( &_this->BackgroundImage, &_this->_.XObject, 0 );
  ViewsText__Init( &_this->Caption, &_this->_.XObject, 0 );
  ViewsText__Init( &_this->Weak, &_this->_.XObject, 0 );
  ViewsText__Init( &_this->Strong, &_this->_.XObject, 0 );
  ViewsLine__Init( &_this->Line, &_this->_.XObject, 0 );
  WidgetSetPushButton__Init( &_this->PushButton, &_this->_.XObject, 0 );
  WidgetSetHorizontalSlider__Init( &_this->HorizontalSlider, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ApplicationSelectionDialog );

  /* ... and initialize objects, variables, properties, etc. */
  CoreRectView__OnSetBounds( _this, _Const0001 );
  CoreRectView__OnSetBounds( &_this->BackgroundImage, _Const0001 );
  CoreRectView__OnSetBounds( &_this->Caption, _Const000A );
  ViewsText_OnSetString( &_this->Caption, EwLoadString( &_Const000B ));
  CoreRectView__OnSetBounds( &_this->Weak, _Const000C );
  ViewsText_OnSetAlignment( &_this->Weak, ViewsTextAlignmentAlignHorzCenter | ViewsTextAlignmentAlignVertCenter );
  ViewsText_OnSetString( &_this->Weak, EwLoadString( &_Const000D ));
  CoreRectView__OnSetBounds( &_this->Strong, _Const000E );
  ViewsText_OnSetAlignment( &_this->Strong, ViewsTextAlignmentAlignHorzCenter | 
  ViewsTextAlignmentAlignVertCenter );
  ViewsText_OnSetString( &_this->Strong, EwLoadString( &_Const000F ));
  CoreLineView_OnSetPoint2((CoreLineView)&_this->Line, _Const0010 );
  CoreLineView_OnSetPoint1((CoreLineView)&_this->Line, _Const0011 );
  ViewsLine_OnSetWidth( &_this->Line, 2 );
  CoreRectView__OnSetBounds( &_this->PushButton, _Const0012 );
  WidgetSetPushButton_OnSetLabel( &_this->PushButton, EwLoadString( &_Const0013 ));
  CoreRectView__OnSetBounds( &_this->HorizontalSlider, _Const0014 );
  CoreGroup_Add((CoreGroup)_this, ((CoreView)&_this->BackgroundImage ), 0 );
  CoreGroup_Add((CoreGroup)_this, ((CoreView)&_this->Caption ), 0 );
  CoreGroup_Add((CoreGroup)_this, ((CoreView)&_this->Weak ), 0 );
  CoreGroup_Add((CoreGroup)_this, ((CoreView)&_this->Strong ), 0 );
  CoreGroup_Add((CoreGroup)_this, ((CoreView)&_this->Line ), 0 );
  CoreGroup_Add((CoreGroup)_this, ((CoreView)&_this->PushButton ), 0 );
  CoreGroup_Add((CoreGroup)_this, ((CoreView)&_this->HorizontalSlider ), 0 );
  ViewsImage_OnSetBitmap( &_this->BackgroundImage, EwLoadResource( &ApplicationBackgroundCup, 
  ResourcesBitmap ));
  ViewsText_OnSetFont( &_this->Caption, EwLoadResource( &ApplicationSmallFont, ResourcesFont ));
  ViewsText_OnSetFont( &_this->Weak, EwLoadResource( &ApplicationSmallFont, ResourcesFont ));
  ViewsText_OnSetFont( &_this->Strong, EwLoadResource( &ApplicationSmallFont, ResourcesFont ));
  _this->PushButton.OnActivate = EwNewSlot( _this, ApplicationSelectionDialog_onPushButton );
  WidgetSetPushButton_OnSetIcon( &_this->PushButton, EwLoadResource( &ApplicationPlayIcon, 
  ResourcesBitmap ));
  WidgetSetPushButton_OnSetAppearance( &_this->PushButton, EwGetAutoObject( &ApplicationPushButtonConfig, 
  WidgetSetPushButtonConfig ));
  WidgetSetHorizontalSlider_OnSetAppearance( &_this->HorizontalSlider, EwGetAutoObject( 
  &ApplicationHorizontalSliderConfig, WidgetSetHorizontalSliderConfig ));
}

/* Re-Initializer for the class 'Application::SelectionDialog' */
void ApplicationSelectionDialog__ReInit( ApplicationSelectionDialog _this )
{
  /* At first re-initialize the super class ... */
  CoreGroup__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  ViewsImage__ReInit( &_this->BackgroundImage );
  ViewsText__ReInit( &_this->Caption );
  ViewsText__ReInit( &_this->Weak );
  ViewsText__ReInit( &_this->Strong );
  ViewsLine__ReInit( &_this->Line );
  WidgetSetPushButton__ReInit( &_this->PushButton );
  WidgetSetHorizontalSlider__ReInit( &_this->HorizontalSlider );
}

/* Finalizer method for the class 'Application::SelectionDialog' */
void ApplicationSelectionDialog__Done( ApplicationSelectionDialog _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( CoreGroup );

  /* Finalize all embedded objects */
  ViewsImage__Done( &_this->BackgroundImage );
  ViewsText__Done( &_this->Caption );
  ViewsText__Done( &_this->Weak );
  ViewsText__Done( &_this->Strong );
  ViewsLine__Done( &_this->Line );
  WidgetSetPushButton__Done( &_this->PushButton );
  WidgetSetHorizontalSlider__Done( &_this->HorizontalSlider );

  /* Don't forget to deinitialize the super class ... */
  CoreGroup__Done( &_this->_.Super );
}

/* 'C' function for method : 'Application::SelectionDialog.onPushButton()' */
void ApplicationSelectionDialog_onPushButton( ApplicationSelectionDialog _this, 
  XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  if ( CoreGroup__IsCurrentDialog( _this ))
    ApplicationDeviceClass_StartBrewing( EwGetAutoObject( &ApplicationDevice, ApplicationDeviceClass ), 
    WidgetSetHorizontalSlider_OnGetCurrentValue( &_this->HorizontalSlider ));
}

/* Variants derived from the class : 'Application::SelectionDialog' */
EW_DEFINE_CLASS_VARIANTS( ApplicationSelectionDialog )
EW_END_OF_CLASS_VARIANTS( ApplicationSelectionDialog )

/* Virtual Method Table (VMT) for the class : 'Application::SelectionDialog' */
EW_DEFINE_CLASS( ApplicationSelectionDialog, CoreGroup, BackgroundImage, _.VMT, 
                 _.VMT, _.VMT, _.VMT, _.VMT, "Application::SelectionDialog" )
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
  CoreGroup_OnSetBounds,
  CoreGroup_OnSetFocus,
  CoreGroup_OnSetOpacity,
  CoreGroup_IsCurrentDialog,
  CoreGroup_IsActiveDialog,
  CoreGroup_DispatchEvent,
  CoreGroup_BroadcastEvent,
  CoreGroup_UpdateViewState,
  CoreGroup_InvalidateArea,
EW_END_OF_CLASS( ApplicationSelectionDialog )

/* Initializer for the class 'Application::Application' */
void ApplicationApplication__Init( ApplicationApplication _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  CoreRoot__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ApplicationApplication );

  /* ... then construct all embedded objects */
  CoreSystemEventHandler__Init( &_this->BrewingFinishedEvent, &_this->_.XObject, 0 );
  CoreSystemEventHandler__Init( &_this->BrewingStartedEvent, &_this->_.XObject, 0 );
  ViewsRectangle__Init( &_this->Background, &_this->_.XObject, 0 );
  ApplicationBrewingDialog__Init( &_this->BrewingDialog, &_this->_.XObject, 0 );
  ApplicationSelectionDialog__Init( &_this->SelectionDialog, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ApplicationApplication );

  /* ... and initialize objects, variables, properties, etc. */
  CoreRectView__OnSetBounds( _this, _Const0001 );
  CoreRectView__OnSetBounds( &_this->Background, _Const0015 );
  ViewsRectangle_OnSetColor( &_this->Background, _Const0016 );
  CoreRectView__OnSetBounds( &_this->BrewingDialog, _Const0001 );
  CoreGroup_OnSetVisible((CoreGroup)&_this->BrewingDialog, 0 );
  CoreRectView__OnSetBounds( &_this->SelectionDialog, _Const0001 );
  CoreGroup_OnSetVisible((CoreGroup)&_this->SelectionDialog, 0 );
  CoreGroup_Add((CoreGroup)_this, ((CoreView)&_this->Background ), 0 );
  CoreGroup_Add((CoreGroup)_this, ((CoreView)&_this->BrewingDialog ), 0 );
  CoreGroup_Add((CoreGroup)_this, ((CoreView)&_this->SelectionDialog ), 0 );
  _this->BrewingFinishedEvent.OnEvent = EwNewSlot( _this, ApplicationApplication_onBrewingFinished );
  CoreSystemEventHandler_OnSetEvent( &_this->BrewingFinishedEvent, &EwGetAutoObject( 
  &ApplicationDevice, ApplicationDeviceClass )->BrewingFinishedEvent );
  _this->BrewingStartedEvent.OnEvent = EwNewSlot( _this, ApplicationApplication_onBrewingStarted );
  CoreSystemEventHandler_OnSetEvent( &_this->BrewingStartedEvent, &EwGetAutoObject( 
  &ApplicationDevice, ApplicationDeviceClass )->BrewingStartedEvent );

  /* Call the user defined constructor */
  ApplicationApplication_Init( _this, aArg );
}

/* Re-Initializer for the class 'Application::Application' */
void ApplicationApplication__ReInit( ApplicationApplication _this )
{
  /* At first re-initialize the super class ... */
  CoreRoot__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  CoreSystemEventHandler__ReInit( &_this->BrewingFinishedEvent );
  CoreSystemEventHandler__ReInit( &_this->BrewingStartedEvent );
  ViewsRectangle__ReInit( &_this->Background );
  ApplicationBrewingDialog__ReInit( &_this->BrewingDialog );
  ApplicationSelectionDialog__ReInit( &_this->SelectionDialog );
}

/* Finalizer method for the class 'Application::Application' */
void ApplicationApplication__Done( ApplicationApplication _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( CoreRoot );

  /* Finalize all embedded objects */
  CoreSystemEventHandler__Done( &_this->BrewingFinishedEvent );
  CoreSystemEventHandler__Done( &_this->BrewingStartedEvent );
  ViewsRectangle__Done( &_this->Background );
  ApplicationBrewingDialog__Done( &_this->BrewingDialog );
  ApplicationSelectionDialog__Done( &_this->SelectionDialog );

  /* Don't forget to deinitialize the super class ... */
  CoreRoot__Done( &_this->_.Super );
}

/* The method Init() is invoked automatically after the component has been created. 
   This method can be overridden and filled with logic containing additional initialization 
   statements. */
void ApplicationApplication_Init( ApplicationApplication _this, XHandle aArg )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( aArg );

  CoreGroup_PresentDialog((CoreGroup)_this, ((CoreGroup)&_this->SelectionDialog ), 
  0, 0, 0, 0, 0, 0, EwNullSlot, EwNullSlot, 0 );
}

/* This slot method is executed when the associated event handler 'BrewingFinishedEvent' 
   is triggered. */
void ApplicationApplication_onBrewingFinished( ApplicationApplication _this, XObject 
  sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  CoreGroup_DismissDialog((CoreGroup)_this, ((CoreGroup)&_this->BrewingDialog ), 
  0, 0, 0, EwNullSlot, EwNullSlot, 0 );
}

/* This slot method is executed when the associated event handler 'BrewingStartedEvent' 
   is triggered. */
void ApplicationApplication_onBrewingStarted( ApplicationApplication _this, XObject 
  sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  CoreGroup_PresentDialog((CoreGroup)_this, ((CoreGroup)&_this->BrewingDialog ), 
  ((EffectsTransition)EwGetAutoObject( &ApplicationFadeInOutCentered, EffectsFadeInOutTransition )), 
  ((EffectsTransition)EwGetAutoObject( &ApplicationFadeInOutCentered, EffectsFadeInOutTransition )), 
  0, 0, 0, 0, EwNullSlot, EwNullSlot, 0 );
}

/* Variants derived from the class : 'Application::Application' */
EW_DEFINE_CLASS_VARIANTS( ApplicationApplication )
EW_END_OF_CLASS_VARIANTS( ApplicationApplication )

/* Virtual Method Table (VMT) for the class : 'Application::Application' */
EW_DEFINE_CLASS( ApplicationApplication, CoreRoot, BrewingFinishedEvent, _.VMT, 
                 _.VMT, _.VMT, _.VMT, _.VMT, "Application::Application" )
  CoreRectView_initLayoutContext,
  CoreRoot_GetRoot,
  CoreRoot_Draw,
  CoreGroup_GetClipping,
  CoreView_HandleEvent,
  CoreGroup_CursorHitTest,
  CoreGroup_AdjustDrawingArea,
  CoreRectView_ArrangeView,
  CoreRectView_MoveView,
  CoreRectView_GetExtent,
  CoreRoot_ChangeViewState,
  CoreGroup_OnSetBounds,
  CoreRoot_OnSetFocus,
  CoreRoot_OnSetOpacity,
  CoreRoot_IsCurrentDialog,
  CoreRoot_IsActiveDialog,
  CoreRoot_DispatchEvent,
  CoreRoot_BroadcastEvent,
  CoreGroup_UpdateViewState,
  CoreRoot_InvalidateArea,
EW_END_OF_CLASS( ApplicationApplication )

/* Embedded Wizard */
