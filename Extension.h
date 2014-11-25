
class Extension
{
public:

    LPRDATA rdPtr;
    LPRH    rhPtr;

    Edif::Runtime Runtime;

    static const int MinimumBuild = 251;
    static const int Version = 1;

    static const int OEFLAGS = 0;
    static const int OEPREFS = 0;
    
    static const int WindowProcPriority = 100;

    Extension(LPRDATA rdPtr, LPEDATA edPtr, fpcob cobPtr);
    ~Extension();


    /*  Add any data you want to store in your extension to this class
        (eg. what you'd normally store in rdPtr)

        Unlike rdPtr, you can store real C++ objects with constructors
        and destructors, without having to call them manually or store
        a pointer.
    */

    // int MyVariable;
	HANDLE sndtH;
	int sndVersion;
	static const int ERRORSIZE = 256;
    TCHAR lastError[ERRORSIZE];
	TCHAR errorTemp[ERRORSIZE];
	int sampleRate;
	int channels;
	bool speechEnabled;

    /*  Add your actions, conditions and expressions as real class member
        functions here. The arguments (and return type for expressions) must
        match EXACTLY what you defined in the JSON.

        Remember to link the actions, conditions and expressions to their
        numeric IDs in the class constructor (Extension.cpp)
    */

	bool openFiles(WavInFile **inFile, WavOutFile **outFile, const TCHAR* inFileName, const TCHAR* outFileName);
	void setup(HANDLE h);
	void process(HANDLE h,WavInFile *inFile, WavOutFile *outFile);

    /// Actions

	void ChangeTempo(TCHAR* inFileName,TCHAR* outFileName,float tempo);
	void ChangePitch(TCHAR* inFileName,TCHAR* outFileName,float pitch);
	void ChangePlayBackRate(TCHAR* inFileName,TCHAR* outFileName,float rate);

    /// Conditions

	bool OnError();

    /// Expressions
        
    int GetVersion();
	TCHAR* LastError();

    /* These are called if there's no function linked to an ID */

    void Action(int ID, LPRDATA rdPtr, long param1, long param2);
    long Condition(int ID, LPRDATA rdPtr, long param1, long param2);
    long Expression(int ID, LPRDATA rdPtr, long param);




    /*  These replace the functions like HandleRunObject that used to be
        implemented in Runtime.cpp. They work exactly the same, but they're
        inside the extension class.
    */

    short Handle();
    short Display();

    short Pause();
    short Continue();

    bool Save(HANDLE File);
    bool Load(HANDLE File);

};