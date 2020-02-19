#include <stdlib.h>
#include <stdio.h>

#include "robot_utilities.h"

struct string_to_f64_result 
{
    f64 F64;
    u32 CharsRead;
};
internal string_to_f64_result
StringToF64(u8 *String, u8 *StringEnd)
{
    u8 *Pointer = String;
    
    string_to_f64_result Result = {0};
    f64 DecimalPlace = 0.1;
    b32 ReadPeriod = false; // Read '.'
    b32 Signed = false;
    if(*Pointer == '-')
    {
        Signed = true;
        Pointer++;
    }
    
    while((*Pointer != '\n') &&
          (*Pointer != ',')  && 
          (Pointer < StringEnd))
    {
        if(('0' <= *Pointer) && (*Pointer <= '9'))
        {
            f64 Digit = (f64)(*Pointer-'0');
            if(!ReadPeriod)
            {
                Result.F64*= 10;
                Result.F64 += Digit;
            }
            else
            {
                Result.F64 += DecimalPlace*Digit;
                DecimalPlace /= 10.0;
            }
        }
        else if(*Pointer == '.')
        {
            ReadPeriod = true;
        }
        Pointer++;
        Result.CharsRead++;
    }
    
    if(Signed)
    {
        Result.F64 *= -1.0;
    }
    
    return(Result);
}

path 
ReadPathFromCsv(char *LeftCsvPath, char *RightCsvPath)
{
    path Path = {0};
    
    file_info LeftFile = PlatformReadEntireFile(LeftCsvPath);
    file_info RightFile = PlatformReadEntireFile(RightCsvPath);
    if((LeftFile.Size && LeftFile.Data) &&
       (RightFile.Size && RightFile.Data))
    {
        Path.PointsSize = 100;
        Path.Points = (path_point *)malloc(Path.PointsSize*sizeof(path_point));
        Assert(Path.Points);
        
        if(Path.Points)
        {
            u32 Column = 0;
            path_point Point = {0};
            
            // Process left file
            u8 *FileEnd = ((u8 *)LeftFile.Data+LeftFile.Size);
            u8 *FileStr = (u8 *)LeftFile.Data;
            u8 *Pointer = FileStr;
            
            u32 I = 0;
            while(Pointer <= FileEnd)
            {
                // NOTE(Tyler): MSVC doesn't support ranges 
                // in case statements
                if((('0' <= *Pointer) && (*Pointer <= '9')) ||
                   (*Pointer == '-'))
                {
                    string_to_f64_result F64Result = StringToF64(Pointer, FileEnd);
                    Pointer += F64Result.CharsRead;
                    switch(Column)
                    {
                        case 0:
                        {
                            Point.LeftWheelPos = F64Result.F64;
                        }break;
                        case 1:
                        {
                            Point.LeftWheelVel = F64Result.F64;
                        }break;
                        case 2:
                        {
                            Point.LeftWheelAcc = F64Result.F64;
                        }break;
                        case 3:
                        {
                            Point.Heading = F64Result.F64;
                        }break;
                    }
                    
                }
                else if(*Pointer == ',')
                {
                    Column++;
                    Pointer++;
                }
                
                if((*Pointer == '\n') ||
                   (Pointer == FileEnd))
                {
                    if(Path.PointCount++ >= ((Path.PointsSize*7)/10))
                    {
                        Path.PointsSize *= 2;
                        Path.Points = (path_point *)realloc(Path.Points, Path.PointsSize*sizeof(path_point));
                        //Assert(Path.Points);
                    }
                    Path.Points[Path.PointCount-1] = Point;
                    Point = {0};
                    Column = 0;
                    Pointer++;
                }
            }
            
            
            // Process right file
            FileEnd = ((u8 *)RightFile.Data+RightFile.Size);
            FileStr = (u8 *)RightFile.Data;
            Pointer = FileStr;
            Column = 0;
            u32 Index = 0;
            
            while(Pointer <= FileEnd)
            {
                // NOTE(Tyler): MSVC doesn't support ranges 
                // in case statements
                if((('0' <= *Pointer) && (*Pointer <= '9')) ||
                   (*Pointer == '-'))
                {
                    string_to_f64_result F64Result = StringToF64(Pointer, FileEnd);
                    Pointer += F64Result.CharsRead;
                    switch(Column)
                    {
                        case 0:
                        {
                            Point.RightWheelPos = F64Result.F64;
                        }break;
                        case 1:
                        {
                            Point.RightWheelVel = F64Result.F64;
                        }break;
                        case 2:
                        {
                            Point.RightWheelAcc = F64Result.F64;
                        }break;
                        case 3:
                        {
                            // Heading is identical to the left
                            // side and is therefore already set.
                        }break;
                    }
                    
                }
                else if(*Pointer == ',')
                {
                    Column++;
                    Pointer++;
                }
                if((*Pointer == '\n') ||
                   (Pointer == FileEnd))
                {
                    // NOTE(Tyler): The right and left files should
                    // have the same number of points, so there is
                    // no need to check here
                    Path.Points[Index].RightWheelPos = Point.RightWheelPos;
                    Path.Points[Index].RightWheelVel = Point.RightWheelVel;
                    Path.Points[Index].RightWheelAcc = Point.RightWheelAcc;
                    Index++;
                    Point = {0};
                    Column = 0;
                    Pointer++;
                }
            }
            
        }
        free(LeftFile.Data);
        free(RightFile.Data);
    }
    else
    {
        // TODO(Tyler): Logging
    }
    
    return(Path);
}