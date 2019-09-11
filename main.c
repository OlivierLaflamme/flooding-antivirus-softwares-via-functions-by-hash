    #include <windows.h>
    #include <assert.h>
    #include <stdio.h>
    #include "md5.h"
     
    typedef bool (__stdcall* IsDebuggerPresentF)(); // the function's typedef
    IsDebuggerPresentF MyIsDebuggerPresent;         // Init func
     
    MD5 md5; // MD5 init
     
    // My function, which will load function by hash
    void *GetProcAddressByMD5(HMODULE hInstance, char *ProcMD5)
    {
        MD5 md5;
        PIMAGE_NT_HEADERS ImageNtHeaders;
        char *FunctionName;
     
        assert(((PIMAGE_DOS_HEADER)hInstance)->e_magic == IMAGE_DOS_SIGNATURE);
     
        ImageNtHeaders = (PIMAGE_NT_HEADERS)((BYTE *)hInstance + ((PIMAGE_DOS_HEADER)hInstance)->e_lfanew);
     
        assert(ImageNtHeaders->Signature == IMAGE_NT_SIGNATURE);
        assert(ImageNtHeaders->OptionalHeader.NumberOfRvaAndSizes > 0);
     
        PIMAGE_EXPORT_DIRECTORY exports = (PIMAGE_EXPORT_DIRECTORY)((BYTE *)hInstance + ImageNtHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);
        PVOID names = (BYTE *)hInstance + exports->AddressOfNames;
     
        for (int i = 0; i < (int)exports->NumberOfNames; i++)
        {
            FunctionName = (char *)((BYTE *)hInstance + ((DWORD *)names)[i]);
     
            if(!strcmp((char *)md5.digestString(FunctionName), ProcMD5))
            {
                return (void *)GetProcAddress(hInstance, FunctionName);
                break;
            }
        }
     
        return 0;
    }
     
    int main()
    {
        MyIsDebuggerPresent = (IsDebuggerPresentF)GetProcAddressByMD5(LoadLibrary("Kernel32.dll"), (char *)"061b4792d0612137b3580832cc6ba7ba"); // load function
     
        if(MyIsDebuggerPresent())
            MessageBox(NULL, "Debugger found!", "Test", MB_OK);
    }
