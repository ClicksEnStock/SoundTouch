#pragma once

// #define TGFEXT       // TGF2, MMF2, MMF2 Dev
   #define MMFEXT       // MMF2, MMF2 Dev
// #define PROEXT       // MMF2 Dev only

#include    "Edif.h"
#include	"Resource.h"
#include	"SoundTouchDLL.h"
#include    "WavFile.h"

#define BUFF_SIZE           2048
#define SETTING_USE_AA_FILTER       0
#define SETTING_AA_FILTER_LENGTH    1
#define SETTING_USE_QUICKSEEK       2
#define SETTING_SEQUENCE_MS         3
#define SETTING_SEEKWINDOW_MS       4
#define SETTING_OVERLAP_MS          5
#define SETTING_NOMINAL_INPUT_SEQUENCE		6
#define SETTING_NOMINAL_OUTPUT_SEQUENCE		7

enum ErrorN
{
	noError,
	noSamples,
	openIn,
	openOut,
	tempoErr,
	pitchErr,
	rateErr
};

static TCHAR* ErrorS[100] = {
	_T("[00] No Error"),
	_T("[01] Cannot find sample in the input file."),
	_T("[02] Cannot open the input file."),
	_T("[03] Cannot create and open the output file."),
	_T("[04] Cannot change tempo from the input file."),
	_T("[05] Cannot change pitch from the input file."),
	_T("[06] Cannot change playback rate from the input file.")
};

// edPtr : Used at edittime and saved in the MFA/CCN/EXE files

struct EDITDATA
{
	// Header - required
	extHeader		eHeader;
	bool			speechEnabled;
	// Object's data
//	short			swidth;
//	short			sheight;

};

#include "Extension.h"
