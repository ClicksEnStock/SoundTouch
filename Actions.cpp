
#include "Common.h"

bool Extension::openFiles(WavInFile **inFile, WavOutFile **outFile, const TCHAR* inFileName, const TCHAR* outFileName)
{
	bool success=false;
	bool fileOpened=false;
    int bits;
	int lg;
	LPSTR ps;
	UINT codePage = CP_ACP;
	lg = WideCharToMultiByte(codePage, 0, inFileName, -1, NULL, 0, NULL, NULL);
	ps = (LPSTR)malloc(lg*sizeof(char));
	WideCharToMultiByte(codePage, 0, inFileName, -1, ps, lg, NULL, NULL);
	try
	{
		*inFile = new WavInFile(ps);
		fileOpened=true;
	}
	catch (const runtime_error &e) 
    {
		_snwprintf_s(lastError, _countof(lastError),_countof(lastError),ErrorS[openIn]);
	}
    
    // ... open output file with same sound parameters
	if(inFile!=NULL && fileOpened)
	{
		bits = (int)(*inFile)->getNumBits();
		sampleRate = (int)(*inFile)->getSampleRate();
		channels = (int)(*inFile)->getNumChannels();
		if (outFileName)
		{
			lg = WideCharToMultiByte(codePage, 0, outFileName, -1, NULL, 0, NULL, NULL);
			ps = (LPSTR)malloc(lg*sizeof(char));
			WideCharToMultiByte(codePage, 0, outFileName, -1, ps, lg, NULL, NULL);
			try
			{
				*outFile = new WavOutFile(ps, sampleRate, bits, channels);
				success=true;
			}
			catch (const runtime_error &e) 
			{
				_snwprintf_s(lastError, _countof(lastError),_countof(lastError),ErrorS[openOut]);
			}
		}
		else
		{
			*outFile = NULL;
			success = false;
		}
	}
	else
	{
		success = false;
	}
	free(ps);
	return success;
}

// Setup according to input file sound format 
void Extension::setup(HANDLE h)
{
    soundtouch_setSampleRate(h,sampleRate);
    soundtouch_setChannels(h,channels);

    soundtouch_setSetting(h,SETTING_USE_QUICKSEEK, 0); //params->quick);
    soundtouch_setSetting(h,SETTING_USE_AA_FILTER, 0); //!(params->noAntiAlias));

	if (speechEnabled)
    {
        // use settings for speech processing
        soundtouch_setSetting(h,SETTING_SEQUENCE_MS, 40);
        soundtouch_setSetting(h,SETTING_SEEKWINDOW_MS, 15);
        soundtouch_setSetting(h,SETTING_OVERLAP_MS, 8);
    }
}

void Extension::process(HANDLE h,WavInFile *inFile, WavOutFile *outFile)
{
	int nSamples;
    int buffSizeSamples;
    float sampleBuffer[BUFF_SIZE];

    if ((inFile == NULL) || (outFile == NULL)) return;  // nothing to do.

    buffSizeSamples = BUFF_SIZE / channels;
	// Process samples read from the input file
    while (inFile->eof() == 0)
    {
        int num;

        // Read a chunk of samples from the input file
        num = inFile->read(sampleBuffer, BUFF_SIZE);
        nSamples = num / channels;
		
		if(nSamples<=0)
		{
			_snwprintf_s(lastError, _countof(lastError),ERRORSIZE,ErrorS[noSamples]);
		}
		
        // Feed the samples into SoundTouch processor
		soundtouch_putSamples(h,sampleBuffer, nSamples);

        // Read ready samples from SoundTouch processor & write them output file.
        // NOTES:
        // - 'receiveSamples' doesn't necessarily return any samples at all
        //   during some rounds!
        // - On the other hand, during some round 'receiveSamples' may have more
        //   ready samples than would fit into 'sampleBuffer', and for this reason 
        //   the 'receiveSamples' call is iterated for as many times as it
        //   outputs samples.
        do 
        {
            nSamples = soundtouch_receiveSamples(h,sampleBuffer, buffSizeSamples);
            outFile->write(sampleBuffer, nSamples * channels);
        } while (nSamples != 0);
    }

    // Now the input file is processed, yet 'flush' few last samples that are
    // hiding in the SoundTouch's internal processing pipeline.
    soundtouch_flush(h);
    do 
    {
        nSamples = soundtouch_receiveSamples(h,sampleBuffer, buffSizeSamples);
        outFile->write(sampleBuffer, nSamples * channels);
    } while (nSamples != 0);
}

void Extension::ChangeTempo(TCHAR* inFileName,TCHAR* outFileName,float tempo)
{
	try
	{
		 WavInFile *inFile;
		 WavOutFile *outFile;

		 sndtH = soundtouch_createInstance();
		 // Open input & output files
		 if(openFiles(&inFile, &outFile, inFileName, outFileName))
		 {
			// Setup for processing the sound
			setup(sndtH);
			soundtouch_setTempoChange(sndtH,tempo);
    
			 // Process the sound
			process(sndtH,inFile,outFile);
       
			delete inFile;
			inFile=NULL;
			delete outFile;
			outFile=NULL;
			soundtouch_destroyInstance(sndtH);
		 }
	}
	catch (const runtime_error &e) 
    {
        // An exception occurred during processing
        _snwprintf_s(lastError, _countof(lastError),_countof(lastError),ErrorS[tempoErr]);
    }
}

void Extension::ChangePitch(TCHAR* inFileName,TCHAR* outFileName,float pitch)
{
	try
	{
		WavInFile *inFile;
		WavOutFile *outFile;
		sndtH = soundtouch_createInstance();
		// Open input & output files
		if(openFiles(&inFile, &outFile, inFileName, outFileName))
		{
			// Setup for processing the sound
			setup(sndtH);
			soundtouch_setPitchSemiTones(sndtH,pitch);
    
			// Process the sound
			process(sndtH,inFile,outFile);

			delete inFile;
			inFile=NULL;
			delete outFile;
			outFile=NULL;
			soundtouch_destroyInstance(sndtH);
		}
	}
	catch (const runtime_error &e) 
    {
        // An exception occurred during processing
        _snwprintf_s(lastError, _countof(lastError),_countof(lastError),ErrorS[pitchErr]);
    }
}

void Extension::ChangePlayBackRate(TCHAR* inFileName,TCHAR* outFileName,float rate)
{
	try
	{
		 WavInFile *inFile;
		 WavOutFile *outFile;

		 sndtH = soundtouch_createInstance();
		 // Open input & output files
		 if(openFiles(&inFile, &outFile, inFileName, outFileName))
		 {
			 // Setup for processing the sound
			 setup(sndtH);
			 soundtouch_setRateChange(sndtH,rate);
    
			 // Process the sound
			 process(sndtH,inFile,outFile);

			 delete inFile;
			 inFile=NULL;
			 delete outFile;
			 outFile=NULL;
			 soundtouch_destroyInstance(sndtH);
		 }
	}
	catch (const runtime_error &e) 
    {
        // An exception occurred during processing
        _snwprintf_s(lastError, _countof(lastError),_countof(lastError),ErrorS[rateErr]);
    }
}



