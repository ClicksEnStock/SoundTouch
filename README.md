# SoundTouch
==========

EDIF SoundTouch Extension (ClickteamFusion 2.5)

SoundTouch can change the Tempo, Pitch and Playback Rates of audio files.

## Properties

**Speech Enabled**

Checkbox to use settings for a better processing of speech samples.

## Actions

**Change Tempo** 

Change the tempo of a wav file and save it to another wav file.

This action takes 3 arguments:
Input File Name: path of the input wav file.
Output File Name: path of the output wav file.
Tempo value: value to be set on the output wav file. Value is a difference in percents compared to the original tempo (-50 .. +100 %). 

----------

**Change Pitch**

Change the pitch of a wav file and save it to another wav file. 

This action takes 3 arguments:
Input File Name: path of the input wav file.
Output File Name: path of the output wav file.
Pitch value: value to be set on the output wav file. Pitch change is in semi-tones compared to the original pitch (-12 .. +12). 

----------

**Change Playbackrate** 

Change the playback rate of a wav file and save it to another wav file.

This action takes 3 arguments:
Input File Name: path of the input wav file.

## Conditions

**On Error**

Returns true if an error occured.

## Expressions

**Last Error**

Returns the last error encountered. Once read the error is erased and can not be retrieved anymore.
Note that if several errors happened before this string is read, only the last error is provided.

**SoundTouch Version**

Retrieves the current version of the SoundTouch dll used with this extension. It can be useful for debugging reasons or just for configuration management.

## Error Codes

Error Codes provided by Last Error expression

[00] No Error.
Default status.
 
[01] Cannot find sample in the input file.
No sample was found in the input file. Check that the input file is a proper wav sound file.
 
[02] Cannot open the input file.
Cannot open the input file, verify the file name, location and its protection level.

[03] Cannot create and open the output file.
Cannot create and open the output file, verify the file name, location and its protection level.

[04] Cannot change tempo from the input file.
Cannot change tempo, verify the tempo value and that the file is a valid wav file.

[05] Cannot change pitch from the input file.
Cannot change pitch, verify the pitch value and that the file is a valid wav file.

[06] Cannot change playback rate from the input file.
Cannot change playback rate, verify the playback rate value and that the file is a valid wav file.

## License

### SoundTouch License

The SoundTouch library is open-source software and is released under the GNU Lesser General Public License (LGPL) v2.1. The library can be further distributed and used in other applications subject to the LGPL license terms.
