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

#ifndef _EffectsFadeInOutTransition_H
#define _EffectsFadeInOutTransition_H

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

#include "_EffectsTransition.h"

/* Forward declaration of the class Effects::FadeInOutTransition */
#ifndef _EffectsFadeInOutTransition_
  EW_DECLARE_CLASS( EffectsFadeInOutTransition )
#define _EffectsFadeInOutTransition_
#endif

/* Forward declaration of the class Effects::Fader */
#ifndef _EffectsFader_
  EW_DECLARE_CLASS( EffectsFader )
#define _EffectsFader_
#endif


/* The class Effects::FadeInOutTransition provides functionality for the fade-in/out 
   operation affecting the opacity of a given GUI component. When using the transition 
   for the fade-in operation, the GUI component is automatically arranged to appear 
   (per default centered) within the area of its owner component. This transition 
   is thus ideal wherever one GUI component should smoothly appear or disappear 
   in context of another component.
   Per default when the component is displayed, it is aligned in the center of its 
   owner. This can be modified by using the property @Alignment. Furthermore, with 
   the four properties @MarginLeft, @MarginRight, @MarginTop and @MarginBottom the 
   area to align the component within its owner can be limited.
   How long the transition should take is determined in the property @Duration, 
   which is per default 500 ms. With the property @Buffered you can configure, whether 
   the transition should additionally enable the buffering mode for the affected 
   GUI component while it perform the animation. */
EW_DEFINE_FIELDS( EffectsFadeInOutTransition, EffectsTransition )
  EW_PROPERTY( Duration,        XInt32 )
EW_END_OF_FIELDS( EffectsFadeInOutTransition )

/* Virtual Method Table (VMT) for the class : 'Effects::FadeInOutTransition' */
EW_DEFINE_METHODS( EffectsFadeInOutTransition, EffectsTransition )
  EW_METHOD( CreatePresentFader, EffectsFader )( EffectsFadeInOutTransition _this )
  EW_METHOD( CreateDismissFader, EffectsFader )( EffectsFadeInOutTransition _this )
  EW_METHOD( CreateRestoreFader, EffectsFader )( EffectsFadeInOutTransition _this )
  EW_METHOD( CreateOverlayFader, EffectsFader )( EffectsFadeInOutTransition _this )
EW_END_OF_METHODS( EffectsFadeInOutTransition )

/* The method CreatePresentFader() creates an object of one of the classes descending 
   from Effects::Fader and configures it with parameters according to the desired 
   fade-in (present) transition. Finally the prepared fader object is returned to 
   the caller. Typically, the created fader is used to show (to present) a GUI component 
   when the user navigates to it. The method has to be overridden and implemented 
   in derived classes. The actual implementation does nothing and returns 'null'. */
EffectsFader EffectsFadeInOutTransition_CreatePresentFader( EffectsFadeInOutTransition _this );

/* The method CreateDismissFader() creates an object of one of the classes descending 
   from Effects::Fader and configures it with parameters according to the desired 
   fade-out (dismiss) transition. Finally the prepared fader object is returned 
   to the caller. Typically, the created fader is used to hide (to dismiss) a GUI 
   component when the user leaves it while he/she navigates in the GUI system. The 
   method has to be overridden and implemented in derived classes. The actual implementation 
   does nothing and returns 'null'. */
EffectsFader EffectsFadeInOutTransition_CreateDismissFader( EffectsFadeInOutTransition _this );

/* The method CreateRestoreFader() creates an object of one of the classes descending 
   from Effects::Fader and configures it with parameters according to the desired 
   fade-in (restore) transition. Finally the prepared fader object is returned to 
   the caller. Typically, the created fader is used to show (to restore the original 
   visible state) of a GUI component, which has been obscured (overlaid) by other 
   GUI components during the user navigates in the GUI system. The method has to 
   be overridden and implemented in derived classes. The actual implementation of 
   this method redirects the operation to the method @CreatePresentFader(). */
EffectsFader EffectsFadeInOutTransition_CreateRestoreFader( EffectsFadeInOutTransition _this );

/* The method CreateOverlayFader() creates an object of one of the classes descending 
   from Effects::Fader and configures it with parameters according to the desired 
   fade-out (overlay) transition. Finally the prepared fader object is returned 
   to the caller. Typically, the created fader is used to temporarily hide (to overlay) 
   a GUI component when the user navigates a deeper level in the GUI system. The 
   method has to be overridden and implemented in derived classes. The actual implementation 
   of this method redirects the operation to the method @CreateDismissFader(). */
EffectsFader EffectsFadeInOutTransition_CreateOverlayFader( EffectsFadeInOutTransition _this );

/* 'C' function for method : 'Effects::FadeInOutTransition.onInitializeIn()' */
void EffectsFadeInOutTransition_onInitializeIn( EffectsFadeInOutTransition _this, 
  XObject sender );

#ifdef __cplusplus
  }
#endif

#endif /* _EffectsFadeInOutTransition_H */

/* Embedded Wizard */
