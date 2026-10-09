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
#include "_CoreGroup.h"
#include "_CoreTimer.h"
#include "_EffectsEffectTimerClass.h"
#include "_GraphicsCanvas.h"
#include "_ResourcesBitmap.h"
#include "_ResourcesFont.h"
#include "_ResourcesFontSet.h"
#include "_ViewsFrame.h"
#include "_ViewsImage.h"
#include "_ViewsLine.h"
#include "_ViewsRectangle.h"
#include "_ViewsStrokePath.h"
#include "_ViewsText.h"
#include "Core.h"
#include "Effects.h"
#include "Graphics.h"
#include "Resources.h"
#include "Views.h"

/* Constant values used in this 'C' module only. */
static const XColor _Const0000 = { 0xFF, 0xFF, 0xFF, 0xFF };
static const XPoint _Const0001 = { 1, 1 };
static const XPoint _Const0002 = { 0, 0 };
static const XRect _Const0003 = {{ 0, 0 }, { 0, 0 }};

/* Initializer for the class 'Views::Line' */
void ViewsLine__Init( ViewsLine _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  CoreLineView__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ViewsLine );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ViewsLine );

  /* ... and initialize objects, variables, properties, etc. */
  _this->Width2 = 1;
  _this->Width1 = 1;
}

/* Re-Initializer for the class 'Views::Line' */
void ViewsLine__ReInit( ViewsLine _this )
{
  /* At first re-initialize the super class ... */
  CoreLineView__ReInit( &_this->_.Super );
}

/* Finalizer method for the class 'Views::Line' */
void ViewsLine__Done( ViewsLine _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( CoreLineView );

  /* Don't forget to deinitialize the super class ... */
  CoreLineView__Done( &_this->_.Super );
}

/* The method Draw() is invoked automatically if parts of the view should be redrawn 
   on the screen. This can occur when e.g. the view has been moved or the appearance 
   of the view has changed before.
   Draw() is invoked automatically by the framework, you will never need to invoke 
   this method directly. However you can request an invocation of this method by 
   calling the method InvalidateArea() of the views @Owner. Usually this is also 
   unnecessary unless you are developing your own view.
   The passed parameters determine the drawing destination aCanvas and the area 
   to redraw aClip in the coordinate space of the canvas. The parameter aOffset 
   contains the displacement between the origin of the views owner and the origin 
   of the canvas. You will need it to convert views coordinates into these of the 
   canvas.
   The parameter aOpacity contains the opacity descended from this view's @Owner. 
   It lies in range 0 .. 255. If the view implements its own 'Opacity', 'Color', 
   etc. properties, the Draw() method should calculate the resulting real opacity 
   by mixing the values of these properties with the one passed in aOpacity parameter.
   The parameter aBlend contains the blending mode descended from this view's @Owner. 
   It determines, whether the view should be drawn with alpha-blending active or 
   not. If aBlend is false, the outputs of the view should overwrite the corresponding 
   pixel in the drawing destination aCanvas. If aBlend is true, the outputs should 
   be mixed with the pixel already stored in aCanvas. For this purpose all Graphics 
   Engine functions provide a parameter to specify the mode for the respective drawing 
   operation. If the view implements its own 'Blend' property, the Draw() method 
   should calculate the resulting real blend mode by using logical AND operation 
   of the value of the property and the one passed in aBlend parameter. */
void ViewsLine_Draw( ViewsLine _this, GraphicsCanvas aCanvas, XRect aClip, XPoint 
  aOffset, XInt32 aOpacity, XBool aBlend )
{
  XInt32 w1 = _this->Width1;
  XInt32 w2 = _this->Width2;
  XPoint p1 = EwMovePointPos( _this->Super1.Point1, aOffset );
  XPoint p2 = EwMovePointPos( _this->Super1.Point2, aOffset );
  XColor c1;
  XColor c2;

  if ( !EwCompPoint( p1, p2 ))
    return;

  aBlend = (XBool)( aBlend && (( _this->Super2.viewState & CoreViewStateAlphaBlended ) 
  == CoreViewStateAlphaBlended ));
  aOpacity = aOpacity + 1;
  c1 = c2 = _Const0000;

  if ( aOpacity < 256 )
  {
    c1.Alpha = (XUInt8)(( aOpacity * 255 ) >> 8 );
    c2.Alpha = (XUInt8)(( aOpacity * 255 ) >> 8 );
  }

  if (( w1 == 1 ) && ( w2 == 1 ))
    GraphicsCanvas_DrawLine( aCanvas, aClip, p1, p2, c1, c2, aBlend );
  else
    GraphicsCanvas_DrawThickLine( aCanvas, aClip, p1, p2, w1, w2, c1, c2, aBlend );
}

/* The method GetExtent() returns the position and the size of the view relative 
   to the origin of its @Owner. In case of views with a non rectangular shape the 
   method returns the rectangular boundary area enclosing the entire shape. */
XRect ViewsLine_GetExtent( ViewsLine _this )
{
  XInt32 w1 = _this->Width1;
  XInt32 w2 = _this->Width2;
  XPoint p1 = _this->Super1.Point1;
  XPoint p2 = _this->Super1.Point2;
  XFloat fw1;
  XFloat fw2;
  XFloat fp1X;
  XFloat fp1Y;
  XFloat fp2X;
  XFloat fp2Y;
  XFloat dirX;
  XFloat dirY;
  XFloat len;
  XFloat c1x;
  XFloat c1y;
  XFloat c2x;
  XFloat c2y;
  XFloat c3x;
  XFloat c3y;
  XFloat c4x;
  XFloat c4y;
  XFloat left;
  XFloat right;
  XFloat top;
  XFloat bottom;
  XRect r;

  if ((( w1 == 1 ) && ( w2 == 1 )) || !EwCompPoint( p1, p2 ))
    return CoreLineView_GetExtent((CoreLineView)_this );

  fw1 = (XFloat)w1 / 2.0f;
  fw2 = (XFloat)w2 / 2.0f;
  fp1X = (XFloat)p1.X;
  fp1Y = (XFloat)p1.Y;
  fp2X = (XFloat)p2.X;
  fp2Y = (XFloat)p2.Y;
  dirX = fp2X - fp1X;
  dirY = fp2Y - fp1Y;
  len = EwMathSqrt(( dirX * dirX ) + ( dirY * dirY ));
  dirX = dirX / len;
  dirY = dirY / len;
  c1x = fp1X + ( dirY * fw1 );
  c1y = fp1Y - ( dirX * fw1 );
  c2x = fp2X + ( dirY * fw2 );
  c2y = fp2Y - ( dirX * fw2 );
  c3x = fp2X - ( dirY * fw2 );
  c3y = fp2Y + ( dirX * fw2 );
  c4x = fp1X - ( dirY * fw1 );
  c4y = fp1Y + ( dirX * fw1 );
  left = c1x;
  right = c1x;
  top = c1y;
  bottom = c1y;

  if ( c2x < left )
    left = c2x;

  if ( c3x < left )
    left = c3x;

  if ( c4x < left )
    left = c4x;

  if ( c2x > right )
    right = c2x;

  if ( c3x > right )
    right = c3x;

  if ( c4x > right )
    right = c4x;

  if ( c2y < top )
    top = c2y;

  if ( c3y < top )
    top = c3y;

  if ( c4y < top )
    top = c4y;

  if ( c2y > bottom )
    bottom = c2y;

  if ( c3y > bottom )
    bottom = c3y;

  if ( c4y > bottom )
    bottom = c4y;

  r = EwNewRect((XInt32)left, (XInt32)top, (XInt32)right, (XInt32)bottom );
  r.Point2 = EwMovePointPos( r.Point2, _Const0001 );
  return r;
}

/* 'C' function for method : 'Views::Line.observerSlot()' */
void ViewsLine_observerSlot( ViewsLine _this, XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  if (( _this->Super2.Owner != 0 ) && (( _this->Super2.viewState & CoreViewStateVisible ) 
      == CoreViewStateVisible ))
    CoreGroup__InvalidateArea( _this->Super2.Owner, CoreView__GetClipping( _this ));
}

/* 'C' function for method : 'Views::Line.OnSetWidth()' */
void ViewsLine_OnSetWidth( ViewsLine _this, XInt32 value )
{
  if ( value < 1 )
    value = 1;

  if (( value == _this->Width1 ) && ( value == _this->Width2 ))
    return;

  if (( _this->Super2.Owner != 0 ) && (( _this->Super2.viewState & CoreViewStateVisible ) 
      == CoreViewStateVisible ))
    CoreGroup__InvalidateArea( _this->Super2.Owner, CoreView__GetClipping( _this ));

  _this->Width1 = value;
  _this->Width2 = value;

  if (( _this->Super2.Owner != 0 ) && (( _this->Super2.viewState & CoreViewStateVisible ) 
      == CoreViewStateVisible ))
    CoreGroup__InvalidateArea( _this->Super2.Owner, CoreView__GetClipping( _this ));

  if (( value != 1 ) && ( _this->whiteBitmap == 0 ))
  {
    _this->whiteBitmap = EwLoadResource( &ResourcesWhiteBitmapStripe, ResourcesBitmap );

    if ( _this->whiteBitmap->Mutable )
      EwAttachObjObserver( EwNewSlot( _this, ViewsLine_observerSlot ), (XObject)_this->whiteBitmap, 
        0 );
  }

  if (( value == 1 ) && ( _this->whiteBitmap != 0 ))
  {
    if ( _this->whiteBitmap->Mutable )
      EwDetachObjObserver( EwNewSlot( _this, ViewsLine_observerSlot ), (XObject)_this->whiteBitmap, 
        0 );

    _this->whiteBitmap = 0;
  }
}

/* Variants derived from the class : 'Views::Line' */
EW_DEFINE_CLASS_VARIANTS( ViewsLine )
EW_END_OF_CLASS_VARIANTS( ViewsLine )

/* Virtual Method Table (VMT) for the class : 'Views::Line' */
EW_DEFINE_CLASS( ViewsLine, CoreLineView, whiteBitmap, whiteBitmap, Width2, Width2, 
                 Width2, Width2, "Views::Line" )
  CoreLineView_initLayoutContext,
  CoreView_GetRoot,
  ViewsLine_Draw,
  CoreView_GetClipping,
  CoreView_HandleEvent,
  CoreView_CursorHitTest,
  CoreView_AdjustDrawingArea,
  CoreLineView_ArrangeView,
  CoreLineView_MoveView,
  ViewsLine_GetExtent,
  CoreView_ChangeViewState,
EW_END_OF_CLASS( ViewsLine )

/* Initializer for the class 'Views::Rectangle' */
void ViewsRectangle__Init( ViewsRectangle _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  CoreRectView__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ViewsRectangle );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ViewsRectangle );

  /* ... and initialize objects, variables, properties, etc. */
  _this->Color = _Const0000;
}

/* Re-Initializer for the class 'Views::Rectangle' */
void ViewsRectangle__ReInit( ViewsRectangle _this )
{
  /* At first re-initialize the super class ... */
  CoreRectView__ReInit( &_this->_.Super );
}

/* Finalizer method for the class 'Views::Rectangle' */
void ViewsRectangle__Done( ViewsRectangle _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( CoreRectView );

  /* Don't forget to deinitialize the super class ... */
  CoreRectView__Done( &_this->_.Super );
}

/* The method Draw() is invoked automatically if parts of the view should be redrawn 
   on the screen. This can occur when e.g. the view has been moved or the appearance 
   of the view has changed before.
   Draw() is invoked automatically by the framework, you will never need to invoke 
   this method directly. However you can request an invocation of this method by 
   calling the method InvalidateArea() of the views @Owner. Usually this is also 
   unnecessary unless you are developing your own view.
   The passed parameters determine the drawing destination aCanvas and the area 
   to redraw aClip in the coordinate space of the canvas. The parameter aOffset 
   contains the displacement between the origin of the views owner and the origin 
   of the canvas. You will need it to convert views coordinates into these of the 
   canvas.
   The parameter aOpacity contains the opacity descended from this view's @Owner. 
   It lies in range 0 .. 255. If the view implements its own 'Opacity', 'Color', 
   etc. properties, the Draw() method should calculate the resulting real opacity 
   by mixing the values of these properties with the one passed in aOpacity parameter.
   The parameter aBlend contains the blending mode descended from this view's @Owner. 
   It determines, whether the view should be drawn with alpha-blending active or 
   not. If aBlend is false, the outputs of the view should overwrite the corresponding 
   pixel in the drawing destination aCanvas. If aBlend is true, the outputs should 
   be mixed with the pixel already stored in aCanvas. For this purpose all Graphics 
   Engine functions provide a parameter to specify the mode for the respective drawing 
   operation. If the view implements its own 'Blend' property, the Draw() method 
   should calculate the resulting real blend mode by using logical AND operation 
   of the value of the property and the one passed in aBlend parameter. */
void ViewsRectangle_Draw( ViewsRectangle _this, GraphicsCanvas aCanvas, XRect aClip, 
  XPoint aOffset, XInt32 aOpacity, XBool aBlend )
{
  XColor ctl;
  XColor ctr;
  XColor cbl;
  XColor cbr;
  XColor c = _this->Color;

  aBlend = (XBool)( aBlend && (( _this->Super2.viewState & CoreViewStateAlphaBlended ) 
  == CoreViewStateAlphaBlended ));
  aOpacity = aOpacity + 1;
  ctl = ctr = cbl = cbr = c;

  if ( aOpacity < 256 )
  {
    ctl.Alpha = (XUInt8)(( aOpacity * ctl.Alpha ) >> 8 );
    ctr.Alpha = (XUInt8)(( aOpacity * ctr.Alpha ) >> 8 );
    cbl.Alpha = (XUInt8)(( aOpacity * cbl.Alpha ) >> 8 );
    cbr.Alpha = (XUInt8)(( aOpacity * cbr.Alpha ) >> 8 );
  }

  GraphicsCanvas_FillRectangle( aCanvas, aClip, EwMoveRectPos( _this->Super1.Bounds, 
  aOffset ), ctl, ctr, cbr, cbl, aBlend );
}

/* 'C' function for method : 'Views::Rectangle.OnSetColor()' */
void ViewsRectangle_OnSetColor( ViewsRectangle _this, XColor value )
{
  if ( !EwCompColor( value, _this->Color ))
    return;

  _this->Color = value;

  if (( _this->Super2.Owner != 0 ) && (( _this->Super2.viewState & CoreViewStateVisible ) 
      == CoreViewStateVisible ))
    CoreGroup__InvalidateArea( _this->Super2.Owner, _this->Super1.Bounds );
}

/* Variants derived from the class : 'Views::Rectangle' */
EW_DEFINE_CLASS_VARIANTS( ViewsRectangle )
EW_END_OF_CLASS_VARIANTS( ViewsRectangle )

/* Virtual Method Table (VMT) for the class : 'Views::Rectangle' */
EW_DEFINE_CLASS( ViewsRectangle, CoreRectView, _.VMT, _.VMT, _.VMT, _.VMT, _.VMT, 
                 _.VMT, "Views::Rectangle" )
  CoreRectView_initLayoutContext,
  CoreView_GetRoot,
  ViewsRectangle_Draw,
  CoreView_GetClipping,
  CoreView_HandleEvent,
  CoreView_CursorHitTest,
  CoreView_AdjustDrawingArea,
  CoreRectView_ArrangeView,
  CoreRectView_MoveView,
  CoreRectView_GetExtent,
  CoreView_ChangeViewState,
  CoreRectView_OnSetBounds,
EW_END_OF_CLASS( ViewsRectangle )

/* Initializer for the class 'Views::Frame' */
void ViewsFrame__Init( ViewsFrame _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  CoreRectView__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ViewsFrame );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ViewsFrame );

  /* ... and initialize objects, variables, properties, etc. */
  _this->animFrameNumber = -1;
  _this->Color = _Const0000;
  _this->Edges = GraphicsEdgesBottom | GraphicsEdgesInterior | GraphicsEdgesLeft 
  | GraphicsEdgesRight | GraphicsEdgesTop;
}

/* Re-Initializer for the class 'Views::Frame' */
void ViewsFrame__ReInit( ViewsFrame _this )
{
  /* At first re-initialize the super class ... */
  CoreRectView__ReInit( &_this->_.Super );
}

/* Finalizer method for the class 'Views::Frame' */
void ViewsFrame__Done( ViewsFrame _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( CoreRectView );

  /* Don't forget to deinitialize the super class ... */
  CoreRectView__Done( &_this->_.Super );
}

/* The method Draw() is invoked automatically if parts of the view should be redrawn 
   on the screen. This can occur when e.g. the view has been moved or the appearance 
   of the view has changed before.
   Draw() is invoked automatically by the framework, you will never need to invoke 
   this method directly. However you can request an invocation of this method by 
   calling the method InvalidateArea() of the views @Owner. Usually this is also 
   unnecessary unless you are developing your own view.
   The passed parameters determine the drawing destination aCanvas and the area 
   to redraw aClip in the coordinate space of the canvas. The parameter aOffset 
   contains the displacement between the origin of the views owner and the origin 
   of the canvas. You will need it to convert views coordinates into these of the 
   canvas.
   The parameter aOpacity contains the opacity descended from this view's @Owner. 
   It lies in range 0 .. 255. If the view implements its own 'Opacity', 'Color', 
   etc. properties, the Draw() method should calculate the resulting real opacity 
   by mixing the values of these properties with the one passed in aOpacity parameter.
   The parameter aBlend contains the blending mode descended from this view's @Owner. 
   It determines, whether the view should be drawn with alpha-blending active or 
   not. If aBlend is false, the outputs of the view should overwrite the corresponding 
   pixel in the drawing destination aCanvas. If aBlend is true, the outputs should 
   be mixed with the pixel already stored in aCanvas. For this purpose all Graphics 
   Engine functions provide a parameter to specify the mode for the respective drawing 
   operation. If the view implements its own 'Blend' property, the Draw() method 
   should calculate the resulting real blend mode by using logical AND operation 
   of the value of the property and the one passed in aBlend parameter. */
void ViewsFrame_Draw( ViewsFrame _this, GraphicsCanvas aCanvas, XRect aClip, XPoint 
  aOffset, XInt32 aOpacity, XBool aBlend )
{
  XInt32 frameNr = _this->FrameNumber;
  XColor ctl;
  XColor ctr;
  XColor cbr;
  XColor cbl;
  XColor c;
  XInt32 opacity;
  XSet edges;
  XRect r;
  XPoint sd;

  if ( _this->animFrameNumber >= 0 )
    frameNr = _this->animFrameNumber;

  if (( _this->Bitmap == 0 ) || ( frameNr >= _this->Bitmap->NoOfFrames ))
    return;

  ResourcesBitmap__Update( _this->Bitmap );
  c = _this->Color;
  opacity = ((( aOpacity + 1 ) * 255 ) >> 8 ) + 1;
  edges = _this->Edges;
  r = EwMoveRectPos( _this->Super1.Bounds, aOffset );
  sd = EwMovePointNeg( EwGetRectSize( r ), _this->NoEdgesLimit );
  aBlend = (XBool)( aBlend && (( _this->Super2.viewState & CoreViewStateAlphaBlended ) 
  == CoreViewStateAlphaBlended ));
  ctl = ctr = cbl = cbr = c;

  if ( opacity < 256 )
  {
    ctl.Alpha = (XUInt8)(( ctl.Alpha * opacity ) >> 8 );
    ctr.Alpha = (XUInt8)(( ctr.Alpha * opacity ) >> 8 );
    cbr.Alpha = (XUInt8)(( cbr.Alpha * opacity ) >> 8 );
    cbl.Alpha = (XUInt8)(( cbl.Alpha * opacity ) >> 8 );
  }

  if ((( _this->NoEdgesLimit.X > 0 ) && ( sd.X > 0 )) && !(( edges & ( GraphicsEdgesLeft 
      | GraphicsEdgesRight )) == ( GraphicsEdgesLeft | GraphicsEdgesRight )))
  {
    XInt32 d = ( _this->Bitmap->FrameSize.X / 3 ) - sd.X;

    if ((( edges & GraphicsEdgesLeft ) == GraphicsEdgesLeft ))
    {
      if ( aClip.Point2.X > r.Point2.X )
        aClip.Point2.X = r.Point2.X;

      if ( d > 0 )
        r.Point2.X = ( r.Point2.X + d );

      edges = edges | GraphicsEdgesRight;
    }
    else
      if ((( edges & GraphicsEdgesRight ) == GraphicsEdgesRight ))
      {
        if ( aClip.Point1.X < r.Point1.X )
          aClip.Point1.X = r.Point1.X;

        if ( d > 0 )
          r.Point1.X = ( r.Point1.X - d );

        edges = edges | GraphicsEdgesLeft;
      }
      else
      {
        if ( aClip.Point1.X < r.Point1.X )
          aClip.Point1.X = r.Point1.X;

        if ( aClip.Point2.X > r.Point2.X )
          aClip.Point2.X = r.Point2.X;

        if ( d > 0 )
        {
          r.Point1.X = ( r.Point1.X - ( d / 2 ));
          r.Point2.X = (( r.Point2.X + d ) - ( d / 2 ));
        }

        edges = edges | ( GraphicsEdgesLeft | GraphicsEdgesRight );
      }
  }

  if ((( _this->NoEdgesLimit.Y > 0 ) && ( sd.Y > 0 )) && !(( edges & ( GraphicsEdgesBottom 
      | GraphicsEdgesTop )) == ( GraphicsEdgesBottom | GraphicsEdgesTop )))
  {
    XInt32 d = ( _this->Bitmap->FrameSize.Y / 3 ) - sd.Y;

    if ((( edges & GraphicsEdgesTop ) == GraphicsEdgesTop ))
    {
      if ( aClip.Point2.Y > r.Point2.Y )
        aClip.Point2.Y = r.Point2.Y;

      if ( d > 0 )
        r.Point2.Y = ( r.Point2.Y + d );

      edges = edges | GraphicsEdgesBottom;
    }
    else
      if ((( edges & GraphicsEdgesBottom ) == GraphicsEdgesBottom ))
      {
        if ( aClip.Point1.Y < r.Point1.Y )
          aClip.Point1.Y = r.Point1.Y;

        if ( d > 0 )
          r.Point1.Y = ( r.Point1.Y - d );

        edges = edges | GraphicsEdgesTop;
      }
      else
      {
        if ( aClip.Point1.Y < r.Point1.Y )
          aClip.Point1.Y = r.Point1.Y;

        if ( aClip.Point2.Y > r.Point2.Y )
          aClip.Point2.Y = r.Point2.Y;

        if ( d > 0 )
        {
          r.Point1.Y = ( r.Point1.Y - ( d / 2 ));
          r.Point2.Y = (( r.Point2.Y + d ) - ( d / 2 ));
        }

        edges = edges | ( GraphicsEdgesBottom | GraphicsEdgesTop );
      }
  }

  GraphicsCanvas_DrawBitmapFrame( aCanvas, aClip, _this->Bitmap, frameNr, r, edges, 
  ctl, ctr, cbr, cbl, aBlend );
}

/* 'C' function for method : 'Views::Frame.observerSlot()' */
void ViewsFrame_observerSlot( ViewsFrame _this, XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  if (( _this->Super2.Owner != 0 ) && (( _this->Super2.viewState & CoreViewStateVisible ) 
      == CoreViewStateVisible ))
    CoreGroup__InvalidateArea( _this->Super2.Owner, _this->Super1.Bounds );
}

/* 'C' function for method : 'Views::Frame.timerSlot()' */
void ViewsFrame_timerSlot( ViewsFrame _this, XObject sender )
{
  XInt32 frameNr;
  XInt32 period;

  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  frameNr = _this->animFrameNumber;
  period = 0;

  if ( _this->Bitmap != 0 )
    period = _this->Bitmap->NoOfFrames * _this->Bitmap->FrameDelay;

  if ((( _this->timer != 0 ) && ( _this->animFrameNumber < 0 )) && ( period > 0 ))
    _this->startTime = _this->timer->Time - ( _this->FrameNumber * _this->Bitmap->FrameDelay );

  if (( _this->timer != 0 ) && ( period > 0 ))
  {
    XInt32 time = (XInt32)( _this->timer->Time - _this->startTime );
    frameNr = time / _this->Bitmap->FrameDelay;

    if ( time >= period )
    {
      frameNr = frameNr % _this->Bitmap->NoOfFrames;
      _this->startTime = _this->timer->Time - ( time % period );
    }
  }

  if ((( frameNr != _this->animFrameNumber ) && ( _this->Super2.Owner != 0 )) && 
      (( _this->Super2.viewState & CoreViewStateVisible ) == CoreViewStateVisible ))
    CoreGroup__InvalidateArea( _this->Super2.Owner, _this->Super1.Bounds );

  _this->animFrameNumber = frameNr;

  if (( period == 0 ) && ( _this->timer != 0 ))
  {
    EwDetachObjObserver( EwNewSlot( _this, ViewsFrame_timerSlot ), (XObject)_this->timer, 
      0 );
    _this->timer = 0;
  }
}

/* 'C' function for method : 'Views::Frame.OnSetColor()' */
void ViewsFrame_OnSetColor( ViewsFrame _this, XColor value )
{
  if ( !EwCompColor( value, _this->Color ))
    return;

  _this->Color = value;

  if (( _this->Super2.Owner != 0 ) && (( _this->Super2.viewState & CoreViewStateVisible ) 
      == CoreViewStateVisible ))
    CoreGroup__InvalidateArea( _this->Super2.Owner, _this->Super1.Bounds );
}

/* 'C' function for method : 'Views::Frame.OnSetAnimated()' */
void ViewsFrame_OnSetAnimated( ViewsFrame _this, XBool value )
{
  if ( _this->Animated == value )
    return;

  _this->Animated = value;
  _this->animFrameNumber = -1;

  if ( !value && ( _this->timer != 0 ))
  {
    EwDetachObjObserver( EwNewSlot( _this, ViewsFrame_timerSlot ), (XObject)_this->timer, 
      0 );
    _this->timer = 0;
  }

  if ( value )
  {
    _this->timer = ((CoreTimer)EwGetAutoObject( &EffectsEffectTimer, EffectsEffectTimerClass ));
    EwAttachObjObserver( EwNewSlot( _this, ViewsFrame_timerSlot ), (XObject)_this->timer, 
      0 );
    EwPostSignal( EwNewSlot( _this, ViewsFrame_timerSlot ), ((XObject)_this ));
  }

  if (( _this->Super2.Owner != 0 ) && (( _this->Super2.viewState & CoreViewStateVisible ) 
      == CoreViewStateVisible ))
    CoreGroup__InvalidateArea( _this->Super2.Owner, _this->Super1.Bounds );
}

/* 'C' function for method : 'Views::Frame.OnSetEdges()' */
void ViewsFrame_OnSetEdges( ViewsFrame _this, XSet value )
{
  if ( value == _this->Edges )
    return;

  _this->Edges = value;

  if (( _this->Super2.Owner != 0 ) && (( _this->Super2.viewState & CoreViewStateVisible ) 
      == CoreViewStateVisible ))
    CoreGroup__InvalidateArea( _this->Super2.Owner, _this->Super1.Bounds );
}

/* 'C' function for method : 'Views::Frame.OnSetFrameNumber()' */
void ViewsFrame_OnSetFrameNumber( ViewsFrame _this, XInt32 value )
{
  if ( value < 0 )
    value = 0;

  if (( value == _this->FrameNumber ) && ( _this->animFrameNumber == -1 ))
    return;

  _this->FrameNumber = value;

  if ( _this->timer == 0 )
    _this->animFrameNumber = -1;

  if (( _this->Super2.Owner != 0 ) && (( _this->Super2.viewState & CoreViewStateVisible ) 
      == CoreViewStateVisible ))
    CoreGroup__InvalidateArea( _this->Super2.Owner, _this->Super1.Bounds );
}

/* 'C' function for method : 'Views::Frame.OnSetBitmap()' */
void ViewsFrame_OnSetBitmap( ViewsFrame _this, ResourcesBitmap value )
{
  if ( value == _this->Bitmap )
    return;

  if (( _this->Bitmap != 0 ) && _this->Bitmap->Mutable )
    EwDetachObjObserver( EwNewSlot( _this, ViewsFrame_observerSlot ), (XObject)_this->Bitmap, 
      0 );

  _this->Bitmap = value;
  _this->animFrameNumber = -1;

  if (( value != 0 ) && value->Mutable )
    EwAttachObjObserver( EwNewSlot( _this, ViewsFrame_observerSlot ), (XObject)value, 
      0 );

  if ( _this->Animated )
  {
    ViewsFrame_OnSetAnimated( _this, 0 );
    ViewsFrame_OnSetAnimated( _this, 1 );
  }

  if (( _this->Super2.Owner != 0 ) && (( _this->Super2.viewState & CoreViewStateVisible ) 
      == CoreViewStateVisible ))
    CoreGroup__InvalidateArea( _this->Super2.Owner, _this->Super1.Bounds );
}

/* 'C' function for method : 'Views::Frame.OnSetVisible()' */
void ViewsFrame_OnSetVisible( ViewsFrame _this, XBool value )
{
  if ( value )
    CoreView__ChangeViewState( _this, CoreViewStateVisible, 0 );
  else
    CoreView__ChangeViewState( _this, 0, CoreViewStateVisible );
}

/* 'C' function for method : 'Views::Frame.OnSetNoEdgesLimit()' */
void ViewsFrame_OnSetNoEdgesLimit( ViewsFrame _this, XPoint value )
{
  if ( value.X < 0 )
    value.X = 0;

  if ( value.Y < 0 )
    value.Y = 0;

  if ( !EwCompPoint( value, _this->NoEdgesLimit ))
    return;

  _this->NoEdgesLimit = value;

  if ((( _this->Super2.Owner != 0 ) && (( _this->Super2.viewState & CoreViewStateVisible ) 
      == CoreViewStateVisible )) && !(( _this->Edges & ( GraphicsEdgesBottom | GraphicsEdgesLeft 
      | GraphicsEdgesRight | GraphicsEdgesTop )) == ( GraphicsEdgesBottom | GraphicsEdgesLeft 
      | GraphicsEdgesRight | GraphicsEdgesTop )))
    CoreGroup__InvalidateArea( _this->Super2.Owner, _this->Super1.Bounds );
}

/* Variants derived from the class : 'Views::Frame' */
EW_DEFINE_CLASS_VARIANTS( ViewsFrame )
EW_END_OF_CLASS_VARIANTS( ViewsFrame )

/* Virtual Method Table (VMT) for the class : 'Views::Frame' */
EW_DEFINE_CLASS( ViewsFrame, CoreRectView, timer, timer, animFrameNumber, animFrameNumber, 
                 animFrameNumber, animFrameNumber, "Views::Frame" )
  CoreRectView_initLayoutContext,
  CoreView_GetRoot,
  ViewsFrame_Draw,
  CoreView_GetClipping,
  CoreView_HandleEvent,
  CoreView_CursorHitTest,
  CoreView_AdjustDrawingArea,
  CoreRectView_ArrangeView,
  CoreRectView_MoveView,
  CoreRectView_GetExtent,
  CoreView_ChangeViewState,
  CoreRectView_OnSetBounds,
EW_END_OF_CLASS( ViewsFrame )

/* Initializer for the class 'Views::Image' */
void ViewsImage__Init( ViewsImage _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  CoreRectView__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ViewsImage );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ViewsImage );

  /* ... and initialize objects, variables, properties, etc. */
  _this->Color = _Const0000;
  _this->Alignment = ViewsImageAlignmentAlignHorzCenter | ViewsImageAlignmentAlignVertCenter;
}

/* Re-Initializer for the class 'Views::Image' */
void ViewsImage__ReInit( ViewsImage _this )
{
  /* At first re-initialize the super class ... */
  CoreRectView__ReInit( &_this->_.Super );
}

/* Finalizer method for the class 'Views::Image' */
void ViewsImage__Done( ViewsImage _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( CoreRectView );

  /* Don't forget to deinitialize the super class ... */
  CoreRectView__Done( &_this->_.Super );
}

/* The method Draw() is invoked automatically if parts of the view should be redrawn 
   on the screen. This can occur when e.g. the view has been moved or the appearance 
   of the view has changed before.
   Draw() is invoked automatically by the framework, you will never need to invoke 
   this method directly. However you can request an invocation of this method by 
   calling the method InvalidateArea() of the views @Owner. Usually this is also 
   unnecessary unless you are developing your own view.
   The passed parameters determine the drawing destination aCanvas and the area 
   to redraw aClip in the coordinate space of the canvas. The parameter aOffset 
   contains the displacement between the origin of the views owner and the origin 
   of the canvas. You will need it to convert views coordinates into these of the 
   canvas.
   The parameter aOpacity contains the opacity descended from this view's @Owner. 
   It lies in range 0 .. 255. If the view implements its own 'Opacity', 'Color', 
   etc. properties, the Draw() method should calculate the resulting real opacity 
   by mixing the values of these properties with the one passed in aOpacity parameter.
   The parameter aBlend contains the blending mode descended from this view's @Owner. 
   It determines, whether the view should be drawn with alpha-blending active or 
   not. If aBlend is false, the outputs of the view should overwrite the corresponding 
   pixel in the drawing destination aCanvas. If aBlend is true, the outputs should 
   be mixed with the pixel already stored in aCanvas. For this purpose all Graphics 
   Engine functions provide a parameter to specify the mode for the respective drawing 
   operation. If the view implements its own 'Blend' property, the Draw() method 
   should calculate the resulting real blend mode by using logical AND operation 
   of the value of the property and the one passed in aBlend parameter. */
void ViewsImage_Draw( ViewsImage _this, GraphicsCanvas aCanvas, XRect aClip, XPoint 
  aOffset, XInt32 aOpacity, XBool aBlend )
{
  XInt32 frameNr = _this->FrameNumber;
  XRect area;
  XPoint size;
  XColor ctl;
  XColor ctr;
  XColor cbr;
  XColor cbl;
  XColor c;
  XInt32 opacity;

  if ( _this->animFrameNumber >= 0 )
    frameNr = _this->animFrameNumber;

  if (( _this->Bitmap == 0 ) || ( frameNr >= _this->Bitmap->NoOfFrames ))
    return;

  ResourcesBitmap__Update( _this->Bitmap );
  area = ViewsImage_GetContentArea( _this );
  size = _this->Bitmap->FrameSize;

  if ( EwIsRectEmpty( area ))
    return;

  c = _this->Color;
  opacity = ((( aOpacity + 1 ) * 255 ) >> 8 ) + 1;
  aBlend = (XBool)( aBlend && (( _this->Super2.viewState & CoreViewStateAlphaBlended ) 
  == CoreViewStateAlphaBlended ));
  ctl = ctr = cbl = cbr = c;

  if ( opacity < 256 )
  {
    ctl.Alpha = (XUInt8)(( ctl.Alpha * opacity ) >> 8 );
    ctr.Alpha = (XUInt8)(( ctr.Alpha * opacity ) >> 8 );
    cbr.Alpha = (XUInt8)(( cbr.Alpha * opacity ) >> 8 );
    cbl.Alpha = (XUInt8)(( cbl.Alpha * opacity ) >> 8 );
  }

  if ( !EwCompPoint( EwGetRectSize( area ), size ))
    GraphicsCanvas_CopyBitmap( aCanvas, aClip, _this->Bitmap, frameNr, EwMoveRectPos( 
    _this->Super1.Bounds, aOffset ), EwMovePointNeg( _this->Super1.Bounds.Point1, 
    area.Point1 ), ctl, ctr, cbr, cbl, aBlend );
  else
    GraphicsCanvas_ScaleBitmap( aCanvas, aClip, _this->Bitmap, frameNr, EwMoveRectPos( 
    area, aOffset ), EwNewRect2Point( _Const0002, size ), ctl, ctr, cbr, cbl, aBlend, 
    1 );
}

/* 'C' function for method : 'Views::Image.observerSlot()' */
void ViewsImage_observerSlot( ViewsImage _this, XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  if (( _this->Super2.Owner != 0 ) && (( _this->Super2.viewState & CoreViewStateVisible ) 
      == CoreViewStateVisible ))
    CoreGroup__InvalidateArea( _this->Super2.Owner, _this->Super1.Bounds );
}

/* 'C' function for method : 'Views::Image.timerSlot()' */
void ViewsImage_timerSlot( ViewsImage _this, XObject sender )
{
  XInt32 frameNr;
  XInt32 period;

  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  frameNr = _this->animFrameNumber;
  period = 0;

  if ( _this->Bitmap != 0 )
    period = _this->Bitmap->NoOfFrames * _this->Bitmap->FrameDelay;

  if ((( _this->timer != 0 ) && ( _this->animFrameNumber < 0 )) && ( period > 0 ))
    _this->startTime = _this->timer->Time - ( _this->FrameNumber * _this->Bitmap->FrameDelay );

  if (( _this->timer != 0 ) && ( period > 0 ))
  {
    XInt32 time = (XInt32)( _this->timer->Time - _this->startTime );
    frameNr = time / _this->Bitmap->FrameDelay;

    if ( time >= period )
    {
      frameNr = frameNr % _this->Bitmap->NoOfFrames;
      _this->startTime = _this->timer->Time - ( time % period );
    }
  }

  if ((( frameNr != _this->animFrameNumber ) && ( _this->Super2.Owner != 0 )) && 
      (( _this->Super2.viewState & CoreViewStateVisible ) == CoreViewStateVisible ))
    CoreGroup__InvalidateArea( _this->Super2.Owner, _this->Super1.Bounds );

  _this->animFrameNumber = frameNr;

  if (( period == 0 ) && ( _this->timer != 0 ))
  {
    EwDetachObjObserver( EwNewSlot( _this, ViewsImage_timerSlot ), (XObject)_this->timer, 
      0 );
    _this->timer = 0;
  }
}

/* 'C' function for method : 'Views::Image.OnSetColor()' */
void ViewsImage_OnSetColor( ViewsImage _this, XColor value )
{
  if ( !EwCompColor( value, _this->Color ))
    return;

  _this->Color = value;

  if (( _this->Super2.Owner != 0 ) && (( _this->Super2.viewState & CoreViewStateVisible ) 
      == CoreViewStateVisible ))
    CoreGroup__InvalidateArea( _this->Super2.Owner, _this->Super1.Bounds );
}

/* 'C' function for method : 'Views::Image.OnSetAnimated()' */
void ViewsImage_OnSetAnimated( ViewsImage _this, XBool value )
{
  if ( _this->Animated == value )
    return;

  _this->Animated = value;
  _this->animFrameNumber = -1;

  if ( !value && ( _this->timer != 0 ))
  {
    EwDetachObjObserver( EwNewSlot( _this, ViewsImage_timerSlot ), (XObject)_this->timer, 
      0 );
    _this->timer = 0;
  }

  if ( value )
  {
    _this->timer = ((CoreTimer)EwGetAutoObject( &EffectsEffectTimer, EffectsEffectTimerClass ));
    EwAttachObjObserver( EwNewSlot( _this, ViewsImage_timerSlot ), (XObject)_this->timer, 
      0 );
    EwPostSignal( EwNewSlot( _this, ViewsImage_timerSlot ), ((XObject)_this ));
  }

  if (( _this->Super2.Owner != 0 ) && (( _this->Super2.viewState & CoreViewStateVisible ) 
      == CoreViewStateVisible ))
    CoreGroup__InvalidateArea( _this->Super2.Owner, _this->Super1.Bounds );
}

/* 'C' function for method : 'Views::Image.OnSetAlignment()' */
void ViewsImage_OnSetAlignment( ViewsImage _this, XSet value )
{
  if ( value == _this->Alignment )
    return;

  _this->Alignment = value;

  if (( _this->Super2.Owner != 0 ) && (( _this->Super2.viewState & CoreViewStateVisible ) 
      == CoreViewStateVisible ))
    CoreGroup__InvalidateArea( _this->Super2.Owner, _this->Super1.Bounds );
}

/* 'C' function for method : 'Views::Image.OnSetFrameNumber()' */
void ViewsImage_OnSetFrameNumber( ViewsImage _this, XInt32 value )
{
  if ( value < 0 )
    value = 0;

  if (( value == _this->FrameNumber ) && ( _this->animFrameNumber == -1 ))
    return;

  _this->FrameNumber = value;

  if ( _this->timer == 0 )
    _this->animFrameNumber = -1;

  if (( _this->Super2.Owner != 0 ) && (( _this->Super2.viewState & CoreViewStateVisible ) 
      == CoreViewStateVisible ))
    CoreGroup__InvalidateArea( _this->Super2.Owner, _this->Super1.Bounds );
}

/* 'C' function for method : 'Views::Image.OnSetBitmap()' */
void ViewsImage_OnSetBitmap( ViewsImage _this, ResourcesBitmap value )
{
  if ( value == _this->Bitmap )
    return;

  if (( _this->Bitmap != 0 ) && _this->Bitmap->Mutable )
    EwDetachObjObserver( EwNewSlot( _this, ViewsImage_observerSlot ), (XObject)_this->Bitmap, 
      0 );

  _this->Bitmap = value;
  _this->animFrameNumber = -1;

  if (( value != 0 ) && value->Mutable )
    EwAttachObjObserver( EwNewSlot( _this, ViewsImage_observerSlot ), (XObject)value, 
      0 );

  if ( _this->Animated )
  {
    ViewsImage_OnSetAnimated( _this, 0 );
    ViewsImage_OnSetAnimated( _this, 1 );
  }

  if (( _this->Super2.Owner != 0 ) && (( _this->Super2.viewState & CoreViewStateVisible ) 
      == CoreViewStateVisible ))
    CoreGroup__InvalidateArea( _this->Super2.Owner, _this->Super1.Bounds );
}

/* The method GetContentArea() returns the position and the size of an area where 
   the view will show the bitmap. This area is expressed in coordinates relative 
   to the top-left corner of the view's @Owner. The method takes in account all 
   properties which do affect the position and the alignment of the bitmap, e.g. 
   @Alignment or @ScrollOffset. */
XRect ViewsImage_GetContentArea( ViewsImage _this )
{
  XSet align;
  XPoint size;
  XRect bounds;
  XInt32 width;
  XInt32 height;
  XRect rd;
  XRect rs;

  if ( _this->Bitmap == 0 )
    return _Const0003;

  align = _this->Alignment;
  size = _this->Bitmap->FrameSize;
  bounds = _this->Super1.Bounds;
  width = EwGetRectW( bounds );
  height = EwGetRectH( bounds );

  if (( size.X == 0 ) || ( size.Y == 0 ))
    return _Const0003;

  rd = EwNewRect( 0, 0, width, height );
  rs = rd;

  if ((( align & ViewsImageAlignmentScaleToFill ) == ViewsImageAlignmentScaleToFill ))
  {
    XInt32 scaleX = (( EwGetRectW( rd ) << 16 ) + ( size.X / 2 )) / size.X;
    XInt32 scaleY = (( EwGetRectH( rd ) << 16 ) + ( size.Y / 2 )) / size.Y;
    XInt32 scale = scaleX;

    if ( scaleY > scale )
      scale = scaleY;

    rs = EwSetRectW( rs, (( size.X * scale ) + 32768 ) >> 16 );
    rs = EwSetRectH( rs, (( size.Y * scale ) + 32768 ) >> 16 );
  }
  else
    if ((( align & ViewsImageAlignmentScaleToFit ) == ViewsImageAlignmentScaleToFit ))
    {
      XInt32 scaleX = (( EwGetRectW( rd ) << 16 ) + ( size.X / 2 )) / size.X;
      XInt32 scaleY = (( EwGetRectH( rd ) << 16 ) + ( size.Y / 2 )) / size.Y;
      XInt32 scale = scaleX;

      if ( scaleY < scale )
        scale = scaleY;

      rs = EwSetRectW( rs, (( size.X * scale ) + 32768 ) >> 16 );
      rs = EwSetRectH( rs, (( size.Y * scale ) + 32768 ) >> 16 );
    }
    else
      if ( !(( align & ViewsImageAlignmentStretchToFill ) == ViewsImageAlignmentStretchToFill ))
        rs = EwSetRectSize( rs, size );

  if ( EwGetRectW( rs ) != EwGetRectW( rd ))
  {
    if ((( align & ViewsImageAlignmentAlignHorzRight ) == ViewsImageAlignmentAlignHorzRight ))
      rs = EwSetRectX( rs, rd.Point2.X - EwGetRectW( rs ));
    else
      if ((( align & ViewsImageAlignmentAlignHorzCenter ) == ViewsImageAlignmentAlignHorzCenter ))
        rs = EwSetRectX( rs, ( rd.Point1.X + ( EwGetRectW( rd ) / 2 )) - ( EwGetRectW( 
        rs ) / 2 ));
  }

  if ( EwGetRectH( rs ) != EwGetRectH( rd ))
  {
    if ((( align & ViewsImageAlignmentAlignVertBottom ) == ViewsImageAlignmentAlignVertBottom ))
      rs = EwSetRectY( rs, rd.Point2.Y - EwGetRectH( rs ));
    else
      if ((( align & ViewsImageAlignmentAlignVertCenter ) == ViewsImageAlignmentAlignVertCenter ))
        rs = EwSetRectY( rs, ( rd.Point1.Y + ( EwGetRectH( rd ) / 2 )) - ( EwGetRectH( 
        rs ) / 2 ));
  }

  rs = EwMoveRectPos( rs, bounds.Point1 );
  return rs;
}

/* Variants derived from the class : 'Views::Image' */
EW_DEFINE_CLASS_VARIANTS( ViewsImage )
EW_END_OF_CLASS_VARIANTS( ViewsImage )

/* Virtual Method Table (VMT) for the class : 'Views::Image' */
EW_DEFINE_CLASS( ViewsImage, CoreRectView, timer, timer, startTime, startTime, startTime, 
                 startTime, "Views::Image" )
  CoreRectView_initLayoutContext,
  CoreView_GetRoot,
  ViewsImage_Draw,
  CoreView_GetClipping,
  CoreView_HandleEvent,
  CoreView_CursorHitTest,
  CoreView_AdjustDrawingArea,
  CoreRectView_ArrangeView,
  CoreRectView_MoveView,
  CoreRectView_GetExtent,
  CoreView_ChangeViewState,
  CoreRectView_OnSetBounds,
EW_END_OF_CLASS( ViewsImage )

/* Initializer for the class 'Views::Text' */
void ViewsText__Init( ViewsText _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  CoreRectView__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ViewsText );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ViewsText );

  /* ... and initialize objects, variables, properties, etc. */
  _this->Alignment = ViewsTextAlignmentAlignHorzCenter | ViewsTextAlignmentAlignVertCenter;
  _this->Color = _Const0000;
}

/* Re-Initializer for the class 'Views::Text' */
void ViewsText__ReInit( ViewsText _this )
{
  /* At first re-initialize the super class ... */
  CoreRectView__ReInit( &_this->_.Super );
}

/* Finalizer method for the class 'Views::Text' */
void ViewsText__Done( ViewsText _this )
{
  /* Call the user defined destructor of the class */
  ViewsText_Done( _this );

  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( CoreRectView );

  /* Don't forget to deinitialize the super class ... */
  CoreRectView__Done( &_this->_.Super );
}

/* 'C' function for method : 'Views::Text.Done()' */
void ViewsText_Done( ViewsText _this )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );
}

/* The method Draw() is invoked automatically if parts of the view should be redrawn 
   on the screen. This can occur when e.g. the view has been moved or the appearance 
   of the view has changed before.
   Draw() is invoked automatically by the framework, you will never need to invoke 
   this method directly. However you can request an invocation of this method by 
   calling the method InvalidateArea() of the views @Owner. Usually this is also 
   unnecessary unless you are developing your own view.
   The passed parameters determine the drawing destination aCanvas and the area 
   to redraw aClip in the coordinate space of the canvas. The parameter aOffset 
   contains the displacement between the origin of the views owner and the origin 
   of the canvas. You will need it to convert views coordinates into these of the 
   canvas.
   The parameter aOpacity contains the opacity descended from this view's @Owner. 
   It lies in range 0 .. 255. If the view implements its own 'Opacity', 'Color', 
   etc. properties, the Draw() method should calculate the resulting real opacity 
   by mixing the values of these properties with the one passed in aOpacity parameter.
   The parameter aBlend contains the blending mode descended from this view's @Owner. 
   It determines, whether the view should be drawn with alpha-blending active or 
   not. If aBlend is false, the outputs of the view should overwrite the corresponding 
   pixel in the drawing destination aCanvas. If aBlend is true, the outputs should 
   be mixed with the pixel already stored in aCanvas. For this purpose all Graphics 
   Engine functions provide a parameter to specify the mode for the respective drawing 
   operation. If the view implements its own 'Blend' property, the Draw() method 
   should calculate the resulting real blend mode by using logical AND operation 
   of the value of the property and the one passed in aBlend parameter. */
void ViewsText_Draw( ViewsText _this, GraphicsCanvas aCanvas, XRect aClip, XPoint 
  aOffset, XInt32 aOpacity, XBool aBlend )
{
  XSet align;
  ResourcesFont font;
  XRect rd;
  XColor ctl;
  XColor ctr;
  XColor cbr;
  XColor cbl;
  XColor col;
  XInt32 opacity;
  XInt32 noOfRows;
  XRect area;
  XPoint ofs;
  XInt32 leading;
  XInt32 rowHeight;
  XInt32 clipY1;
  XInt32 clipY2;
  XInt32 areaW;
  XInt32 y;
  XInt32 i;
  XInt32 c;

  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( aBlend );

  if ( !EwCompString( _this->flowString, 0 ) || ( _this->usedFont == 0 ))
    return;

  align = _this->Alignment;
  font = _this->usedFont;
  rd = EwMoveRectPos( _this->Super1.Bounds, aOffset );
  col = _this->Color;
  opacity = ((( aOpacity + 1 ) * 255 ) >> 8 ) + 1;
  noOfRows = EwGetStringChar( _this->flowString, 0 );
  area = EwMoveRectPos( ViewsText_GetContentArea( _this ), aOffset );
  ofs = EwNewPoint( rd.Point1.X - area.Point1.X, ( rd.Point1.Y - area.Point1.Y ) 
  - font->Ascent );

  if ( noOfRows < 1 )
    return;

  ctl = ctr = cbl = cbr = col;

  if ( opacity < 256 )
  {
    ctl.Alpha = (XUInt8)(( ctl.Alpha * opacity ) >> 8 );
    ctr.Alpha = (XUInt8)(( ctr.Alpha * opacity ) >> 8 );
    cbr.Alpha = (XUInt8)(( cbr.Alpha * opacity ) >> 8 );
    cbl.Alpha = (XUInt8)(( cbl.Alpha * opacity ) >> 8 );
  }

  if ((( align & ViewsTextAlignmentAlignHorzAuto ) == ViewsTextAlignmentAlignHorzAuto ))
  {
    if ( ViewsText_IsBaseDirectionRTL( _this ))
      align = ( align & ~ViewsTextAlignmentAlignHorzAuto ) | ViewsTextAlignmentAlignHorzRight;
    else
      align = ( align & ~ViewsTextAlignmentAlignHorzAuto ) | ViewsTextAlignmentAlignHorzLeft;
  }

  if (( noOfRows == 1 ) && !(( align & ViewsTextAlignmentAlignHorzJustified ) == 
      ViewsTextAlignmentAlignHorzJustified ))
  {
    GraphicsCanvas_DrawText( aCanvas, aClip, font, _this->flowString, 2, EwGetStringChar( 
    _this->flowString, 1 ) - 1, rd, ofs, 0, ViewsOrientationNormal, ctl, ctr, cbr, 
    cbl, 1 );
    return;
  }

  leading = font->Leading;
  rowHeight = ( font->Ascent + font->Descent ) + leading;
  clipY1 = aClip.Point1.Y - area.Point1.Y;
  clipY2 = aClip.Point2.Y - area.Point1.Y;
  areaW = EwGetRectW( area );
  y = 0;
  i = 1;
  c = EwGetStringChar( _this->flowString, 1 );

  while ((( y + rowHeight ) < clipY1 ) && ( c > 0 ))
  {
    i = i + c;
    y = y + rowHeight;
    c = EwGetStringChar( _this->flowString, i );
  }

  while (( y < clipY2 ) && ( c > 0 ))
  {
    XPoint ofs2 = EwMovePointNeg( ofs, EwNewPoint( 0, y ));
    XInt32 rw = 0;
    XBool justified = 0;

    if ((((( align & ViewsTextAlignmentAlignHorzJustified ) == ViewsTextAlignmentAlignHorzJustified ) 
        && ( EwGetStringChar( _this->flowString, ( i + c ) - 1 ) != 0x000A )) && 
        ( EwGetStringChar( _this->flowString, i + 1 ) != 0x000A )) && ( EwGetStringChar( 
        _this->flowString, i + c ) != 0x0000 ))
      justified = 1;

    if ( justified && !!( align & ( ViewsTextAlignmentAlignHorzCenter | ViewsTextAlignmentAlignHorzRight )))
    {
      XInt32 rowEnd = i + c;
      XInt32 blank1 = EwStringFindChar( _this->flowString, 0x0020, i + 1 );
      XInt32 blank2 = EwStringFindChar( _this->flowString, 0x00A0, i + 1 );

      if ((( blank1 < 0 ) || ( blank1 >= rowEnd )) && (( blank2 < 0 ) || ( blank2 
          >= rowEnd )))
        justified = 0;
    }

    if ( justified )
      rw = areaW;
    else
      if ((( align & ViewsTextAlignmentAlignHorzRight ) == ViewsTextAlignmentAlignHorzRight ))
        ofs2.X = (( ofs2.X - areaW ) + ResourcesFont_GetTextAdvance( font, _this->flowString, 
        i + 1, c - 1 ));
      else
        if ((( align & ViewsTextAlignmentAlignHorzCenter ) == ViewsTextAlignmentAlignHorzCenter ))
          ofs2.X = (( ofs2.X - ( areaW / 2 )) + ( ResourcesFont_GetTextAdvance( 
          font, _this->flowString, i + 1, c - 1 ) / 2 ));

    GraphicsCanvas_DrawText( aCanvas, aClip, font, _this->flowString, i + 1, c - 
    1, rd, ofs2, rw, ViewsOrientationNormal, ctl, ctr, cbr, cbl, 1 );
    i = i + c;
    y = y + rowHeight;
    c = EwGetStringChar( _this->flowString, i );
  }
}

/* The method GetClipping() returns the clipping area of the view as rectangle relative 
   to the origin of the view's @Owner. With the returned clipping area the view 
   limits its own visibility. Contents belonging to the view and lying outside this 
   area will not be displayed - they are clipped during the screen update process.
   Per default the clipping area corresponds to the boundary area of the view (see 
   also @GetExtent()). Derived views can override GetClipping() and enlarge the 
   area so the view can display additional contents (e.g. shadows or decoration) 
   outside of its original boundary area. */
XRect ViewsText_GetClipping( ViewsText _this )
{
  XRect r = CoreView_GetClipping((CoreView)_this );

  return r;
}

/* 'C' function for method : 'Views::Text.OnSetBounds()' */
void ViewsText_OnSetBounds( ViewsText _this, XRect value )
{
  if ( !EwCompRect( value, _this->Super1.Bounds ))
    return;

  if (((( _this->usedFont != _this->Font ) && _this->reparsed ) && EwCompPoint( 
      EwGetRectSize( _this->Super1.Bounds ), EwGetRectSize( value ))) && !(( _this->Super2.viewState 
      & CoreViewStateUpdatingLayout ) == CoreViewStateUpdatingLayout ))
  {
    _this->flowString = 0;
    _this->reparsed = 0;
    EwPostSignal( EwNewSlot( _this, ViewsText_preReparseSlot ), ((XObject)_this ));
  }

  CoreRectView_OnSetBounds((CoreRectView)_this, value );
  EwPostSignal( EwNewSlot( _this, ViewsText_preOnUpdateSlot ), ((XObject)_this ));
  EwIdleSignal( EwNewSlot( _this, ViewsText_onOverflowTest ), ((XObject)_this ));
}

/* 'C' function for method : 'Views::Text.preOnUpdateSlot()' */
void ViewsText_preOnUpdateSlot( ViewsText _this, XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );
  EW_UNUSED_ARG( sender );
}

/* 'C' function for method : 'Views::Text.preReparseSlot()' */
void ViewsText_preReparseSlot( ViewsText _this, XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  EwPostSignal( EwNewSlot( _this, ViewsText_reparseSlot ), ((XObject)_this ));
}

/* 'C' function for method : 'Views::Text.onOverflowTest()' */
void ViewsText_onOverflowTest( ViewsText _this, XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );
  EW_UNUSED_ARG( sender );
}

/* 'C' function for method : 'Views::Text.onUpdateFont()' */
void ViewsText_onUpdateFont( ViewsText _this, XObject sender )
{
  ResourcesFontSet fontSet;

  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  fontSet = EwCastObject( _this->Font, ResourcesFontSet );

  if ( fontSet != 0 )
    _this->usedFont = ResourcesFontSet_GetAnyFont( fontSet );

  _this->flowString = 0;
  _this->reparsed = 0;
  EwPostSignal( EwNewSlot( _this, ViewsText_preReparseSlot ), ((XObject)_this ));
}

/* 'C' function for method : 'Views::Text.reparseSlot()' */
void ViewsText_reparseSlot( ViewsText _this, XObject sender )
{
  XInt32 width;
  XInt32 height;
  ResourcesFont font;
  ResourcesFontSet fontSet;
  XBool shrink;

  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  if ( _this->reparsed )
    return;

  width = EwGetRectW( _this->Super1.Bounds );
  height = EwGetRectH( _this->Super1.Bounds );
  font = _this->usedFont;
  fontSet = EwCastObject( _this->Font, ResourcesFontSet );
  shrink = 0;

  do
  {
    if ((( font != 0 ) && !!!font->Ascent ) && !!!font->Descent )
      font = 0;

    _this->reparsed = 1;

    if (( EwCompString( _this->String, 0 ) != 0 ) && ( font != 0 ))
    {
      XInt32 length = EwGetStringLength( _this->String );
      _this->flowString = EwShareString( ResourcesFont_ParseFlowString( font, _this->String, 
      0, -1, length, 0 ));
    }
    else
      _this->flowString = 0;

    _this->textSize = _Const0002;

    if (( fontSet != 0 ) && !EwIsStringEmpty( _this->flowString ))
    {
      XPoint size = EwGetRectSize( ViewsText_GetContentArea( _this ));

      if (( size.X > width ) || ( size.Y > height ))
      {
        ResourcesFont smallerFont = ResourcesFontSet_GetSmallerFont( fontSet, _this->usedFont );

        if ( !( smallerFont != 0 ) || ( smallerFont == _this->usedFont ))
          break;

        _this->usedFont = smallerFont;
        font = _this->usedFont;
        shrink = 1;
      }
      else
        if ( !shrink )
        {
          ResourcesFont largerFont = ResourcesFontSet_GetLargerFont( fontSet, _this->usedFont );

          if ( !( largerFont != 0 ) || ( largerFont == _this->usedFont ))
            break;

          _this->usedFont = largerFont;
          font = _this->usedFont;
        }
        else
          break;
    }
  }
  while (( fontSet != 0 ) && !EwIsStringEmpty( _this->flowString ));

  if (( _this->Super2.Owner != 0 ) && (( _this->Super2.viewState & CoreViewStateVisible ) 
      == CoreViewStateVisible ))
    CoreGroup__InvalidateArea( _this->Super2.Owner, _this->Super1.Bounds );

  EwPostSignal( EwNewSlot( _this, ViewsText_preOnUpdateSlot ), ((XObject)_this ));
  EwIdleSignal( EwNewSlot( _this, ViewsText_onOverflowTest ), ((XObject)_this ));
}

/* 'C' function for method : 'Views::Text.OnSetAlignment()' */
void ViewsText_OnSetAlignment( ViewsText _this, XSet value )
{
  if ( value == _this->Alignment )
    return;

  _this->Alignment = value;

  if (( _this->Super2.Owner != 0 ) && (( _this->Super2.viewState & CoreViewStateVisible ) 
      == CoreViewStateVisible ))
    CoreGroup__InvalidateArea( _this->Super2.Owner, _this->Super1.Bounds );

  if ( _this->usedFont != _this->Font )
  {
    _this->flowString = 0;
    _this->reparsed = 0;
    EwPostSignal( EwNewSlot( _this, ViewsText_preReparseSlot ), ((XObject)_this ));
  }

  if ( _this->reparsed )
    EwPostSignal( EwNewSlot( _this, ViewsText_preOnUpdateSlot ), ((XObject)_this ));
}

/* 'C' function for method : 'Views::Text.OnSetString()' */
void ViewsText_OnSetString( ViewsText _this, XString value )
{
  if ( !EwCompString( value, _this->String ))
    return;

  _this->String = EwShareString( value );
  _this->flowString = 0;
  _this->reparsed = 0;
  EwPostSignal( EwNewSlot( _this, ViewsText_preReparseSlot ), ((XObject)_this ));
}

/* 'C' function for method : 'Views::Text.OnSetFont()' */
void ViewsText_OnSetFont( ViewsText _this, ResourcesFont value )
{
  ResourcesFontSet fontSet;

  if ( value == _this->Font )
    return;

  if (( _this->Font != 0 ) && _this->Font->Mutable )
    EwDetachObjObserver( EwNewSlot( _this, ViewsText_onUpdateFont ), (XObject)_this->Font, 
      0 );

  _this->Font = value;
  fontSet = EwCastObject( value, ResourcesFontSet );
  _this->usedFont = (( fontSet != 0 )? ResourcesFontSet_GetAnyFont( fontSet ) : 
  value );

  if (( value != 0 ) && value->Mutable )
    EwAttachObjObserver( EwNewSlot( _this, ViewsText_onUpdateFont ), (XObject)_this->Font, 
      0 );

  _this->flowString = 0;
  _this->reparsed = 0;
  EwPostSignal( EwNewSlot( _this, ViewsText_preReparseSlot ), ((XObject)_this ));
}

/* 'C' function for method : 'Views::Text.OnSetColor()' */
void ViewsText_OnSetColor( ViewsText _this, XColor value )
{
  if ( !EwCompColor( value, _this->Color ))
    return;

  _this->Color = value;

  if (( _this->Super2.Owner != 0 ) && (( _this->Super2.viewState & CoreViewStateVisible ) 
      == CoreViewStateVisible ))
    CoreGroup__InvalidateArea( _this->Super2.Owner, _this->Super1.Bounds );
}

/* The method IsBaseDirectionRTL() returns 'true' if the text specified in @String 
   starts with an RTL (right-to-left) character. This implies the base direction 
   of the entire text paragraph. If the text starts with an LTR (left-to-right) 
   sign or the property @EnableBidiText is 'false', this method returns 'false'. */
XBool ViewsText_IsBaseDirectionRTL( ViewsText _this )
{
  if ( !_this->reparsed )
    EwSignal( EwNewSlot( _this, ViewsText_reparseSlot ), ((XObject)_this ));

  return 0;
}

/* The method GetContentArea() returns the position and the size of an area where 
   the view will show the text. This area is expressed in coordinates relative to 
   the top-left corner of the view's @Owner. The method takes in account all properties 
   which do affect the position and the alignment of the text, e.g. @Alignment, 
   @Orientation, @ScrollOffset, @WrapText, etc. */
XRect ViewsText_GetContentArea( ViewsText _this )
{
  XInt32 leading;
  XInt32 rh;
  XSet align;
  XRect bounds;
  XInt32 width;
  XInt32 height;
  XRect rd;
  XRect rs;

  if ( !EwCompString( _this->String, 0 ) || ( _this->usedFont == 0 ))
    return _Const0003;

  if ( !_this->reparsed )
    EwSignal( EwNewSlot( _this, ViewsText_reparseSlot ), ((XObject)_this ));

  if ( !EwCompString( _this->flowString, 0 ))
    return _Const0003;

  leading = _this->usedFont->Leading;
  rh = ( _this->usedFont->Ascent + _this->usedFont->Descent ) + _this->usedFont->Leading;

  if ( !EwCompPoint( _this->textSize, _Const0002 ))
    _this->textSize.X = ResourcesFont_GetFlowTextAdvance( _this->usedFont, _this->flowString );

  _this->textSize.Y = (( EwGetStringChar( _this->flowString, 0 ) * rh ) - leading );
  align = _this->Alignment;
  bounds = _this->Super1.Bounds;
  width = EwGetRectW( bounds );
  height = EwGetRectH( bounds );
  rd = EwNewRect( 0, 0, width, height );
  rs = EwNewRect2Point( rd.Point1, EwMovePointPos( rd.Point1, _this->textSize ));

  if ((( align & ViewsTextAlignmentAlignHorzAuto ) == ViewsTextAlignmentAlignHorzAuto ))
  {
    if ( ViewsText_IsBaseDirectionRTL( _this ))
      align = ( align & ~ViewsTextAlignmentAlignHorzAuto ) | ViewsTextAlignmentAlignHorzRight;
    else
      align = ( align & ~ViewsTextAlignmentAlignHorzAuto ) | ViewsTextAlignmentAlignHorzLeft;
  }

  if ((( align & ViewsTextAlignmentAlignHorzJustified ) == ViewsTextAlignmentAlignHorzJustified ))
  {
    XInt32 maxWidth;
    maxWidth = width;

    if ( maxWidth < 0 )
      maxWidth = 0;

    if ( maxWidth > EwGetRectW( rs ))
      rs = EwSetRectW( rs, maxWidth );
  }

  if (( !!( align & ( ViewsTextAlignmentAlignVertCenter | ViewsTextAlignmentAlignVertCenterBaseline )) 
      && !!( align & ( ViewsTextAlignmentAlignVertBottom | ViewsTextAlignmentAlignVertTop ))) 
      && ( EwGetRectH( rs ) > EwGetRectH( rd )))
    align &= ~( ViewsTextAlignmentAlignVertCenter | ViewsTextAlignmentAlignVertCenterBaseline );

  if ( !!( align & ( ViewsTextAlignmentAlignVertCenter | ViewsTextAlignmentAlignVertCenterBaseline )))
    align &= ~( ViewsTextAlignmentAlignVertBottom | ViewsTextAlignmentAlignVertTop );

  if (((( align & ViewsTextAlignmentAlignHorzCenter ) == ViewsTextAlignmentAlignHorzCenter ) 
      && !!( align & ( ViewsTextAlignmentAlignHorzLeft | ViewsTextAlignmentAlignHorzRight ))) 
      && ( EwGetRectW( rs ) > EwGetRectW( rd )))
    align &= ~ViewsTextAlignmentAlignHorzCenter;

  if ((( align & ViewsTextAlignmentAlignHorzCenter ) == ViewsTextAlignmentAlignHorzCenter ))
    align &= ~( ViewsTextAlignmentAlignHorzLeft | ViewsTextAlignmentAlignHorzRight );

  if ( EwGetRectW( rs ) != EwGetRectW( rd ))
  {
    if ((( align & ViewsTextAlignmentAlignHorzRight ) == ViewsTextAlignmentAlignHorzRight ))
      rs = EwSetRectX( rs, rd.Point2.X - EwGetRectW( rs ));
    else
      if ((( align & ViewsTextAlignmentAlignHorzCenter ) == ViewsTextAlignmentAlignHorzCenter ))
        rs = EwSetRectX( rs, ( rd.Point1.X + ( EwGetRectW( rd ) / 2 )) - ( EwGetRectW( 
        rs ) / 2 ));
  }

  if ( EwGetRectH( rs ) != EwGetRectH( rd ))
  {
    if ((( align & ViewsTextAlignmentAlignVertBottom ) == ViewsTextAlignmentAlignVertBottom ))
      rs = EwSetRectY( rs, rd.Point2.Y - EwGetRectH( rs ));
    else
      if ((( align & ViewsTextAlignmentAlignVertCenterBaseline ) == ViewsTextAlignmentAlignVertCenterBaseline ))
        rs = EwSetRectY( rs, (( rd.Point1.Y + ( EwGetRectH( rd ) / 2 )) - ( EwGetRectH( 
        rs ) / 2 )) + (( _this->usedFont->Descent - _this->usedFont->Ascent ) / 
        2 ));
      else
        if ((( align & ViewsTextAlignmentAlignVertCenter ) == ViewsTextAlignmentAlignVertCenter ))
          rs = EwSetRectY( rs, ( rd.Point1.Y + ( EwGetRectH( rd ) / 2 )) - ( EwGetRectH( 
          rs ) / 2 ));
  }

  rs = EwMoveRectPos( rs, bounds.Point1 );
  return rs;
}

/* Variants derived from the class : 'Views::Text' */
EW_DEFINE_CLASS_VARIANTS( ViewsText )
EW_END_OF_CLASS_VARIANTS( ViewsText )

/* Virtual Method Table (VMT) for the class : 'Views::Text' */
EW_DEFINE_CLASS( ViewsText, CoreRectView, usedFont, usedFont, flowString, flowString, 
                 flowString, textSize, "Views::Text" )
  CoreRectView_initLayoutContext,
  CoreView_GetRoot,
  ViewsText_Draw,
  ViewsText_GetClipping,
  CoreView_HandleEvent,
  CoreView_CursorHitTest,
  CoreView_AdjustDrawingArea,
  CoreRectView_ArrangeView,
  CoreRectView_MoveView,
  CoreRectView_GetExtent,
  CoreView_ChangeViewState,
  ViewsText_OnSetBounds,
EW_END_OF_CLASS( ViewsText )

/* Initializer for the class 'Views::StrokePath' */
void ViewsStrokePath__Init( ViewsStrokePath _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  CoreRectView__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ViewsStrokePath );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ViewsStrokePath );

  /* ... and initialize objects, variables, properties, etc. */
  _this->EndCap = GraphicsPathCapFlat;
  _this->StartCap = GraphicsPathCapFlat;
  _this->Width = 1.0f;
}

/* Re-Initializer for the class 'Views::StrokePath' */
void ViewsStrokePath__ReInit( ViewsStrokePath _this )
{
  /* At first re-initialize the super class ... */
  CoreRectView__ReInit( &_this->_.Super );
}

/* Finalizer method for the class 'Views::StrokePath' */
void ViewsStrokePath__Done( ViewsStrokePath _this )
{
  /* Call the user defined destructor of the class */
  ViewsStrokePath_Done( _this );

  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( CoreRectView );

  /* Don't forget to deinitialize the super class ... */
  CoreRectView__Done( &_this->_.Super );
}

/* 'C' function for method : 'Views::StrokePath.Done()' */
void ViewsStrokePath_Done( ViewsStrokePath _this )
{
  ViewsStrokePath_destroyBuffer( _this );
}

/* The method Draw() is invoked automatically if parts of the view should be redrawn 
   on the screen. This can occur when e.g. the view has been moved or the appearance 
   of the view has changed before.
   Draw() is invoked automatically by the framework, you will never need to invoke 
   this method directly. However you can request an invocation of this method by 
   calling the method InvalidateArea() of the views @Owner. Usually this is also 
   unnecessary unless you are developing your own view.
   The passed parameters determine the drawing destination aCanvas and the area 
   to redraw aClip in the coordinate space of the canvas. The parameter aOffset 
   contains the displacement between the origin of the views owner and the origin 
   of the canvas. You will need it to convert views coordinates into these of the 
   canvas.
   The parameter aOpacity contains the opacity descended from this view's @Owner. 
   It lies in range 0 .. 255. If the view implements its own 'Opacity', 'Color', 
   etc. properties, the Draw() method should calculate the resulting real opacity 
   by mixing the values of these properties with the one passed in aOpacity parameter.
   The parameter aBlend contains the blending mode descended from this view's @Owner. 
   It determines, whether the view should be drawn with alpha-blending active or 
   not. If aBlend is false, the outputs of the view should overwrite the corresponding 
   pixel in the drawing destination aCanvas. If aBlend is true, the outputs should 
   be mixed with the pixel already stored in aCanvas. For this purpose all Graphics 
   Engine functions provide a parameter to specify the mode for the respective drawing 
   operation. If the view implements its own 'Blend' property, the Draw() method 
   should calculate the resulting real blend mode by using logical AND operation 
   of the value of the property and the one passed in aBlend parameter. */
void ViewsStrokePath_Draw( ViewsStrokePath _this, GraphicsCanvas aCanvas, XRect 
  aClip, XPoint aOffset, XInt32 aOpacity, XBool aBlend )
{
  XColor ctl;
  XColor ctr;
  XColor cbl;
  XColor cbr;

  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( aBlend );

  if ( _this->Path == 0 )
    return;

  aOpacity = aOpacity + 1;
  ctl = ctr = cbl = cbr = _Const0000;

  if ( aOpacity < 256 )
  {
    ctl.Alpha = (XUInt8)(( aOpacity * 255 ) >> 8 );
    ctr.Alpha = (XUInt8)(( aOpacity * 255 ) >> 8 );
    cbl.Alpha = (XUInt8)(( aOpacity * 255 ) >> 8 );
    cbr.Alpha = (XUInt8)(( aOpacity * 255 ) >> 8 );
  }

  GraphicsCanvas_StrokePath( aCanvas, aClip, _this->Path, EwMoveRectPos( _this->Super1.Bounds, 
  aOffset ), 0, _this->Offset, _this->Width, _this->StartCap, _this->EndCap, GraphicsPathJoinBevel, 
  3.0f, ctl, ctr, cbr, cbl, 1, 1 );
}

/* 'C' function for method : 'Views::StrokePath.destroyBuffer()' */
void ViewsStrokePath_destroyBuffer( ViewsStrokePath _this )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );

  return;
}

/* 'C' function for method : 'Views::StrokePath.updatePath()' */
void ViewsStrokePath_updatePath( ViewsStrokePath _this, XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  if (( _this->Super2.Owner != 0 ) && (( _this->Super2.viewState & CoreViewStateVisible ) 
      == CoreViewStateVisible ))
    CoreGroup__InvalidateArea( _this->Super2.Owner, _this->Super1.Bounds );
}

/* 'C' function for method : 'Views::StrokePath.OnSetOffset()' */
void ViewsStrokePath_OnSetOffset( ViewsStrokePath _this, XPoint value )
{
  if ( !EwCompPoint( value, _this->Offset ))
    return;

  _this->Offset = value;

  if ((( _this->Super2.Owner != 0 ) && (( _this->Super2.viewState & CoreViewStateVisible ) 
      == CoreViewStateVisible )) && ( _this->Path != 0 ))
    CoreGroup__InvalidateArea( _this->Super2.Owner, _this->Super1.Bounds );
}

/* 'C' function for method : 'Views::StrokePath.OnSetEndCap()' */
void ViewsStrokePath_OnSetEndCap( ViewsStrokePath _this, XEnum value )
{
  if ( value == _this->EndCap )
    return;

  _this->EndCap = value;

  if ((( _this->Super2.Owner != 0 ) && (( _this->Super2.viewState & CoreViewStateVisible ) 
      == CoreViewStateVisible )) && ( _this->Path != 0 ))
    CoreGroup__InvalidateArea( _this->Super2.Owner, _this->Super1.Bounds );
}

/* 'C' function for method : 'Views::StrokePath.OnSetStartCap()' */
void ViewsStrokePath_OnSetStartCap( ViewsStrokePath _this, XEnum value )
{
  if ( value == _this->StartCap )
    return;

  _this->StartCap = value;

  if ((( _this->Super2.Owner != 0 ) && (( _this->Super2.viewState & CoreViewStateVisible ) 
      == CoreViewStateVisible )) && ( _this->Path != 0 ))
    CoreGroup__InvalidateArea( _this->Super2.Owner, _this->Super1.Bounds );
}

/* 'C' function for method : 'Views::StrokePath.OnSetWidth()' */
void ViewsStrokePath_OnSetWidth( ViewsStrokePath _this, XFloat value )
{
  if ( value < 0.0f )
    value = 0.0f;

  if ( value == _this->Width )
    return;

  _this->Width = value;

  if ((( _this->Super2.Owner != 0 ) && (( _this->Super2.viewState & CoreViewStateVisible ) 
      == CoreViewStateVisible )) && ( _this->Path != 0 ))
    CoreGroup__InvalidateArea( _this->Super2.Owner, _this->Super1.Bounds );
}

/* 'C' function for method : 'Views::StrokePath.OnSetPath()' */
void ViewsStrokePath_OnSetPath( ViewsStrokePath _this, GraphicsPath value )
{
  if ( value == _this->Path )
    return;

  if ( _this->Path != 0 )
    EwDetachObjObserver( EwNewSlot( _this, ViewsStrokePath_updatePath ), (XObject)_this->Path, 
      0 );

  _this->Path = value;

  if ( _this->Path != 0 )
    EwAttachObjObserver( EwNewSlot( _this, ViewsStrokePath_updatePath ), (XObject)_this->Path, 
      0 );

  if (( _this->Super2.Owner != 0 ) && (( _this->Super2.viewState & CoreViewStateVisible ) 
      == CoreViewStateVisible ))
    CoreGroup__InvalidateArea( _this->Super2.Owner, _this->Super1.Bounds );
}

/* Variants derived from the class : 'Views::StrokePath' */
EW_DEFINE_CLASS_VARIANTS( ViewsStrokePath )
EW_END_OF_CLASS_VARIANTS( ViewsStrokePath )

/* Virtual Method Table (VMT) for the class : 'Views::StrokePath' */
EW_DEFINE_CLASS( ViewsStrokePath, CoreRectView, Path, Path, Offset, Offset, Offset, 
                 Offset, "Views::StrokePath" )
  CoreRectView_initLayoutContext,
  CoreView_GetRoot,
  ViewsStrokePath_Draw,
  CoreView_GetClipping,
  CoreView_HandleEvent,
  CoreView_CursorHitTest,
  CoreView_AdjustDrawingArea,
  CoreRectView_ArrangeView,
  CoreRectView_MoveView,
  CoreRectView_GetExtent,
  CoreView_ChangeViewState,
  CoreRectView_OnSetBounds,
EW_END_OF_CLASS( ViewsStrokePath )

/* Embedded Wizard */
