@echo off

rem /******************************************************************************\
rem *
rem * E M B E D D E D   W I Z A R D   P R O J E C T
rem *
rem *                                                Copyright (c) TARA Systems GmbH
rem *                                    written by Paul Banach and Manfred Schweyer
rem *
rem ********************************************************************************
rem *
rem * AVIATION DEMO
rem *
rem ********************************************************************************
rem *
rem * DESCRIPTION:
rem *   This batch file prepares the Aviation Demo to work with a dedicated set of
rem *   bitmap resources, which is created for a certain instrument size.
rem *   For that purpose, the desired bitmap set is copied from the subdirectory
rem *   into the /Res directory.
rem *
rem \******************************************************************************/

set INSTRUMENT_SIZE=140x140

copy .\%INSTRUMENT_SIZE%\*.png .

echo ******************************************************************************
echo *
echo * Embedded Wizard Aviation Demo
echo *   The Aviation Demo is now prepared to use all resources for an instrument
echo *   size of %INSTRUMENT_SIZE% pixel.
echo *
echo ******************************************************************************

pause
