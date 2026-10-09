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

#ifndef Application_H
#define Application_H

#ifdef __cplusplus
  extern "C"
  {
#endif

#include "ewrte.h"
#if ( EW_RTE_VERSION >> 16 ) != 15
  #error Wrong version of Embedded Wizard Runtime Environment.
#endif

#include "ewgfx.h"
#if ( EW_GFX_VERSION >> 16 ) != 15
  #error Wrong version of Embedded Wizard Graphics Engine.
#endif

#include "_ApplicationApplication.h"
#include "_ApplicationBrewingDialog.h"
#include "_ApplicationDeviceClass.h"
#include "_ApplicationSelectionDialog.h"

/* This is a font resource used in the application. */
EW_DECLARE_FONT_RES( ApplicationSmallFont )

/* This is a font resource used in the application. */
EW_DECLARE_FONT_RES( ApplicationBigFont )

/* This is a bitmap resource used in the application. */
EW_DECLARE_BITMAP_RES( ApplicationPlayIcon )

/* This is a bitmap resource used in the application. */
EW_DECLARE_BITMAP_RES( ApplicationButtonFace )

/* This is a bitmap resource used in the application. */
EW_DECLARE_BITMAP_RES( ApplicationCup )

/* This is a bitmap resource used in the application. */
EW_DECLARE_BITMAP_RES( ApplicationSliderFront )

/* This is a bitmap resource used in the application. */
EW_DECLARE_BITMAP_RES( ApplicationSliderThumb )

/* This is a bitmap resource used in the application. */
EW_DECLARE_BITMAP_RES( ApplicationSliderBack )

/* This is a bitmap resource used in the application. */
EW_DECLARE_BITMAP_RES( ApplicationBackgroundCup )

/* Forward declaration of the class Effects::FadeInOutTransition */
#ifndef _EffectsFadeInOutTransition_
  EW_DECLARE_CLASS( EffectsFadeInOutTransition )
#define _EffectsFadeInOutTransition_
#endif

/* Forward declaration of the class WidgetSet::HorizontalSliderConfig */
#ifndef _WidgetSetHorizontalSliderConfig_
  EW_DECLARE_CLASS( WidgetSetHorizontalSliderConfig )
#define _WidgetSetHorizontalSliderConfig_
#endif

/* Forward declaration of the class WidgetSet::PushButtonConfig */
#ifndef _WidgetSetPushButtonConfig_
  EW_DECLARE_CLASS( WidgetSetPushButtonConfig )
#define _WidgetSetPushButtonConfig_
#endif

/* This is an instance of the interface to the underlying device. Through this instance 
   the GUI can communicate with the device. */
EW_DECLARE_AUTOOBJECT( ApplicationDevice, ApplicationDeviceClass )

/* This object contains configuration information for a transition between two dialogs 
   (screens). */
EW_DECLARE_AUTOOBJECT( ApplicationFadeInOutCentered, EffectsFadeInOutTransition )

/* This object contains configuration information for a push button widget. */
EW_DECLARE_AUTOOBJECT( ApplicationPushButtonConfig, WidgetSetPushButtonConfig )

/* This object contains configuration information for a slider widget. */
EW_DECLARE_AUTOOBJECT( ApplicationHorizontalSliderConfig, WidgetSetHorizontalSliderConfig )

#ifdef __cplusplus
  }
#endif

#endif /* Application_H */

/* Embedded Wizard */
