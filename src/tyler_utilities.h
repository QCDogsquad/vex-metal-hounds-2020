#if !defined(TYLER_UTILITIES_H)
#define TYLER_UTILITIES_H

//~ Primitive types

#include <stddef.h>
#include <stdint.h>

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t  s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef s8  b8;
typedef s16 b16;
typedef s32 b32;
typedef s64 b64;

typedef uintptr_t rawptr;

#define U8_MAX  0xff
#define U16_MAX 0xffff
#define U32_MAX 0xffffffff
#define U64_MAX 0xffffffffffffffff

#define S8_MAX  0x7f
#define S16_MAX 0x7fff
#define S32_MAX 0x7fffffff
#define S64_MAX 0x7fffffffffffffff

#define S8_MIN  0x80
#define S16_MIN 0x8000
#define S32_MIN 0x80000000
#define S64_MIN 0x8000000000000000

typedef size_t memory_index;

typedef float  f32;
typedef double f64;

#define internal        static
#define global          static
#define global_constant static const
#define local_persist   static
#define local_constant  static const

//~ Platform interface
struct memory_arena;
struct file_info
{
    memory_index Size;
    void *Data;
};

file_info PlatformReadEntireFile(const char *Path);

void FreeFileInfo(memory_arena *Arena, file_info File);

//~ Helpers
#define ArrayCount(Array) (sizeof(Array)/sizeof(*Array))
#define Kilobytes(Size) (1024*(Size))
#define Megabytes(Size) (1024*Kilobytes(Size))
#define Gigabytes(Size) (1024L*(u64)Megabytes(Size))

#if defined(_MSC_VER)
#define Assert(Expr) do {if (!(Expr)) __debugbreak();} while(0)
#else
#include <assert.h>
#define Assert(Expr) assert(Expr)
#endif

#if !defined(CopyMemory)
void CopyMemory(void *Dest, void *Source, memory_index Size);
#endif

template <typename Type> 
inline Type 
Minimum(Type A, Type B)
{
    Type Result = (A > B) ? B : A;
    return(Result);
}

template <typename Type> 
inline Type 
Maximum(Type A, Type B)
{
    Type Result = (A > B) ? A : B;
    return(Result);
}

//~ Memory arena

struct memory_arena 
{
    u8 *Memory;
    memory_index Used;
    memory_index Size;
    u32 TempCount;
};

struct temporary_memory 
{
    memory_arena *Arena;
    memory_index Size;
};

void InitializeArena(memory_arena *Arena, void *Memory, memory_index Size);

#define PushStruct(Arena, Struct) PushMemory(Arena, sizeof(Struct))
#define PushArray(Arena, Size, Type) (Type *)PushMemory(Arena, Size*sizeof(Type))
void *PushMemory(memory_arena *Arena, memory_index Size);
b32 AddMemory(memory_arena *Arena, memory_index Size);
void FreeMemory(memory_arena *Arena, void *Memory, memory_index Size);

//~ Strings

struct string_u8
{
    u64 Size;
    u8 *Str;
};

struct string_const_u8 
{
    u64 Size;
    const u8 *Str;
};

u64 CStringLength(const char *CString);
string_u8 Su8(u8 *Str, u64 Size);
string_u8 Su8(char *CString);
string_const_u8 SCu8(string_u8 String);
string_const_u8 SCu8(const u8 *Str, u64 Size);
string_const_u8 SCu8(char *CString);
string_u8 PushStringU8(memory_arena *Arena, u64 Size);
string_const_u8 PushStringConstU8(memory_arena *Arena, u64 Size);
string_u8 NewStringU8(memory_arena *Arena, u8 *Str, u64 Size);
void FreeString(memory_arena *Arena, string_u8 String);
void FreeStringConst(memory_arena *Arena, string_const_u8 String);
b32 DoStringsMatch(string_const_u8 A, string_const_u8 B);

#endif //TYLER_UTILITIES_H
