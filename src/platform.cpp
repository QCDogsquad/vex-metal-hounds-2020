
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h> 
#include <string.h>

#include "tyler_utilities.h"

//~ Platform interface
file_info PlatformReadEntireFile(const char *Path)
{
    file_info Result = {};
    FILE *File = fopen(Path, "rb");
    if(File)
    {
        fseek(File, 0, SEEK_END);
        memory_index Size = ftell(File);
        fseek(File, 0, SEEK_SET);
        
        if(Size)
        {
            void *Memory = malloc(Size);
            if(Memory)
            {
                Result.Size = Size;
                Result.Data = Memory;
                fread(Result.Data, 1, Result.Size, File);
            }
            else
            {
                // TODO(Tyler): Logging
            }
        }
        else
        {
            // TODO(Tyler): Logging
        }
        
        fclose(File);
    }
    else
    {
        // TODO(Tyler): Logging
    }
    return(Result);
}