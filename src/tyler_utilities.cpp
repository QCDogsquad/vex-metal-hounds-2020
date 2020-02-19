#include <stdio.h>

#include "tyler_utilities.h"

//~ Platform interface

void FreeFileInfo(memory_arena *Arena, file_info File)
{
    FreeMemory(Arena, File.Data, File.Size);
}


//~ Helpers

// NOTE(Tyler): CopyMemory is defined in the windows headers
#if !defined(CopyMemory)
void 
CopyMemory(void *Dest, void *Source, memory_index Size)
{
    u8 *DestU8 = (u8 *)Dest;
    u8 *SourceU8 = (u8 *)Source;
    while(Size--)
    {
        *DestU8++ = *SourceU8++;
    }
}
#endif


//~ Memory arena

void 
InitializeArena(memory_arena *Arena, void *Memory, memory_index Size)
{
    *Arena = {};
    Arena->Memory = (u8 *)Memory;
    Arena->Size = Size;
}

void *
PushMemory(memory_arena *Arena, memory_index Size)
{
    void *Result = 0;
    if((Arena->Used + Size) <= Arena->Size)
    {
        Result = Arena->Memory+Arena->Used;
        Arena->Used += Size;
    }
    return(Result);
}

b32
AddMemory(memory_arena *Arena, memory_index Size)
{
    b32 Result = false;
    if((Arena->Used + Size) <= Arena->Size)
    {
        Arena->Used += Size;
        Result = true;
    }
    return(Result);
}

void
FreeMemory(memory_arena *Arena, void *Memory)
{
    memory_index Size = (rawptr)Memory - (rawptr)Arena->Memory;
    Arena->Used -= Size;
}

//~ Strings

u64 
CStringLength(const char *CString)
{
    u64 Result = 0;
    while(*CString++ != '\0')
    {
        Result++;
    }
    return(Result);
}

string_u8
Su8(u8 *Str, u64 Size)
{
    string_u8 Result = {};
    Result.Size = Size;
    Result.Str = Str;
    
    return(Result);
}

string_u8
Su8(char *CString)
{
    string_u8 Result = {};
    Result.Size = CStringLength(CString);
    Result.Str = (u8 *)CString;
    
    return(Result);
}

string_const_u8
SCu8(string_u8 String)
{
    string_const_u8 Result;
    Result.Str = String.Str;
    Result.Size = String.Size;
    return(Result);
}

string_const_u8
SCu8(const u8 *Str, u64 Size)
{
    string_const_u8 Result = {0};
    Result.Size = Size;
    Result.Str = Str;
    
    return(Result);
}

string_const_u8
SCu8(char *CString)
{
    string_const_u8 Result = {0};
    Result.Size = CStringLength(CString);
    Result.Str = (u8 *)CString;
    printf("SCu8 %s %u\n", Result.Str, Result.Size);
    
    return(Result);
}

string_u8
PushStringU8(memory_arena *Arena, u64 Size)
{
    string_u8 Result;
    Result.Size = Size;
    Result.Str = (u8 *)PushMemory(Arena, Result.Size+1);
    Result.Str[Size] = '\0';
    
    return(Result);
}

string_const_u8
PushStringConstU8(memory_arena *Arena, u64 Size)
{
    string_u8 String;
    String.Size = Size;
    String.Str = (u8 *)PushMemory(Arena, String.Size+1);
    String.Str[Size] = '\0';
    
    string_const_u8 Result = SCu8(String);
    return(Result);
}

string_u8
NewStringU8(memory_arena *Arena, u8 *Str, u64 Size)
{
    string_u8 Result = PushStringU8(Arena, Size+1);
    CopyMemory(Result.Str, Str, Size+1);
    return(Result);
}

void
FreeString(memory_arena *Arena, string_u8 String)
{
    FreeMemory(Arena, String.Str, String.Size);
}

void
FreeStringConst(memory_arena *Arena, string_const_u8 String)
{
    FreeMemory(Arena, (void *)String.Str, String.Size+1);
}

b32
DoStringsMatch(string_const_u8 A, string_const_u8 B)
{
    b32 Result = true;
    if(A.Size == B.Size)
    {
        for(u32 I = 0;
            I < A.Size;
            I++)
        {
            if(A.Str[I] != B.Str[I])
            {
                Result = false;
                break;
            }
        }
    }
    else
    {
        Result = false;
    }
    return(Result);
}
