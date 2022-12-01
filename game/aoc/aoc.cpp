/*
File:   aoc.cpp
Author: Taylor Robbins
Date:   11\29\2022
Description: 
	** Holds the advent of code solution functions
*/

MemArena_t* aocArena = nullptr;

#include "aoc/aoc_helpers.cpp"

// +--------------------------------------------------------------+
// |                             2022                             |
// +--------------------------------------------------------------+
// +==============================+
// |            Day 01            |
// +==============================+
MyStr_t AocSolutionFunc_2022_01(AocSolutionStruct_2022_01_t* data, bool doSolutionB)
{
	AocOpenFile(file, "input_2022_01.txt");
	
	AocVarArrayU64(counts);
	u64* currentCountPntr = nullptr;
	
	AocLoopFile(file, parser, line)
	{
		if (IsEmptyStr(line))
		{
			// if (currentCountPntr != nullptr) { PrintLine_D("Elf[%llu] has %llu", counts.length-1, *currentCountPntr); }
			currentCountPntr = nullptr;
		}
		else
		{
			if (currentCountPntr == nullptr)
			{
				currentCountPntr = VarArrayAdd(&counts, u64);
				*currentCountPntr = 0;
			}
			u64 lineValue = 0;
			bool parseSuccess = TryParseU64(line, &lineValue);
			Assert(parseSuccess);
			*currentCountPntr += lineValue;
		}
	}
	AocCloseFile(file);
	
	PrintLine_D("There are %llu elves total", counts.length);
	
	if (doSolutionB)
	{
		i64 foundIndices[3] = {-1, -1, -1};
		u64 maxCountsTotal = 0;
		for (u8 pass = 0; pass < ArrayCount(foundIndices); pass++)
		{
			u64 maxCount = 0;
			u64 maxCountIndex = 0;
			VarArrayLoop(&counts, eIndex)
			{
				VarArrayLoopGet(u64, countPntr, &counts, eIndex);
				bool isElfAlreadyFound = false;
				for (u8 fIndex = 0; fIndex < ArrayCount(foundIndices); fIndex++)
				{
					if (foundIndices[fIndex] >= 0 && (u64)foundIndices[fIndex] == eIndex) { isElfAlreadyFound = true; break; }
				}
				
				if (!isElfAlreadyFound && maxCount < *countPntr)
				{
					maxCount = *countPntr;
					maxCountIndex = eIndex;
				}
			}
			
			PrintLine_I("Elf[%llu] has %llu calories", maxCountIndex, maxCount);
			maxCountsTotal += maxCount;
			foundIndices[pass] = maxCountIndex;
		}
		
		AocReturnU64(maxCountsTotal);
	}
	else
	{
		u64 maxCountIndex = 0;
		u64 maxCount = AocFindMaxU64(&counts, &maxCountIndex);
		PrintLine_I("Elf[%llu] has %llu calories", maxCountIndex, maxCount);
		AocReturnU64(maxCount);
	}
}

// +==============================+
// |            Day 02            |
// +==============================+
MyStr_t AocSolutionFunc_2022_02(AocSolutionStruct_2022_02_t* data, bool doSolutionB)
{
	NotifyWrite_W("Solution_2022_02 is unimplemented"); //TODO: Implement me!
	return MyStr_Empty;
}

// +==============================+
// |            Day 03            |
// +==============================+
MyStr_t AocSolutionFunc_2022_03(AocSolutionStruct_2022_03_t* data, bool doSolutionB)
{
	NotifyWrite_W("Solution_2022_03 is unimplemented"); //TODO: Implement me!
	return MyStr_Empty;
}

// +==============================+
// |            Day 04            |
// +==============================+
MyStr_t AocSolutionFunc_2022_04(AocSolutionStruct_2022_04_t* data, bool doSolutionB)
{
	NotifyWrite_W("Solution_2022_04 is unimplemented"); //TODO: Implement me!
	return MyStr_Empty;
}

// +==============================+
// |            Day 05            |
// +==============================+
MyStr_t AocSolutionFunc_2022_05(AocSolutionStruct_2022_05_t* data, bool doSolutionB)
{
	NotifyWrite_W("Solution_2022_05 is unimplemented"); //TODO: Implement me!
	return MyStr_Empty;
}

// +==============================+
// |            Day 06            |
// +==============================+
MyStr_t AocSolutionFunc_2022_06(AocSolutionStruct_2022_06_t* data, bool doSolutionB)
{
	NotifyWrite_W("Solution_2022_06 is unimplemented"); //TODO: Implement me!
	return MyStr_Empty;
}

// +==============================+
// |            Day 07            |
// +==============================+
MyStr_t AocSolutionFunc_2022_07(AocSolutionStruct_2022_07_t* data, bool doSolutionB)
{
	NotifyWrite_W("Solution_2022_07 is unimplemented"); //TODO: Implement me!
	return MyStr_Empty;
}

// +==============================+
// |            Day 08            |
// +==============================+
MyStr_t AocSolutionFunc_2022_08(AocSolutionStruct_2022_08_t* data, bool doSolutionB)
{
	NotifyWrite_W("Solution_2022_08 is unimplemented"); //TODO: Implement me!
	return MyStr_Empty;
}

// +==============================+
// |            Day 09            |
// +==============================+
MyStr_t AocSolutionFunc_2022_09(AocSolutionStruct_2022_09_t* data, bool doSolutionB)
{
	NotifyWrite_W("Solution_2022_09 is unimplemented"); //TODO: Implement me!
	return MyStr_Empty;
}

// +==============================+
// |            Day 10            |
// +==============================+
MyStr_t AocSolutionFunc_2022_10(AocSolutionStruct_2022_10_t* data, bool doSolutionB)
{
	NotifyWrite_W("Solution_2022_10 is unimplemented"); //TODO: Implement me!
	return MyStr_Empty;
}

// +==============================+
// |            Day 11            |
// +==============================+
MyStr_t AocSolutionFunc_2022_11(AocSolutionStruct_2022_11_t* data, bool doSolutionB)
{
	NotifyWrite_W("Solution_2022_11 is unimplemented"); //TODO: Implement me!
	return MyStr_Empty;
}

// +==============================+
// |            Day 12            |
// +==============================+
MyStr_t AocSolutionFunc_2022_12(AocSolutionStruct_2022_12_t* data, bool doSolutionB)
{
	NotifyWrite_W("Solution_2022_12 is unimplemented"); //TODO: Implement me!
	return MyStr_Empty;
}

// +==============================+
// |            Day 13            |
// +==============================+
MyStr_t AocSolutionFunc_2022_13(AocSolutionStruct_2022_13_t* data, bool doSolutionB)
{
	NotifyWrite_W("Solution_2022_13 is unimplemented"); //TODO: Implement me!
	return MyStr_Empty;
}

// +==============================+
// |            Day 14            |
// +==============================+
MyStr_t AocSolutionFunc_2022_14(AocSolutionStruct_2022_14_t* data, bool doSolutionB)
{
	NotifyWrite_W("Solution_2022_14 is unimplemented"); //TODO: Implement me!
	return MyStr_Empty;
}

// +==============================+
// |            Day 15            |
// +==============================+
MyStr_t AocSolutionFunc_2022_15(AocSolutionStruct_2022_15_t* data, bool doSolutionB)
{
	NotifyWrite_W("Solution_2022_15 is unimplemented"); //TODO: Implement me!
	return MyStr_Empty;
}

// +==============================+
// |            Day 16            |
// +==============================+
MyStr_t AocSolutionFunc_2022_16(AocSolutionStruct_2022_16_t* data, bool doSolutionB)
{
	NotifyWrite_W("Solution_2022_16 is unimplemented"); //TODO: Implement me!
	return MyStr_Empty;
}

// +==============================+
// |            Day 17            |
// +==============================+
MyStr_t AocSolutionFunc_2022_17(AocSolutionStruct_2022_17_t* data, bool doSolutionB)
{
	NotifyWrite_W("Solution_2022_17 is unimplemented"); //TODO: Implement me!
	return MyStr_Empty;
}

// +==============================+
// |            Day 18            |
// +==============================+
MyStr_t AocSolutionFunc_2022_18(AocSolutionStruct_2022_18_t* data, bool doSolutionB)
{
	NotifyWrite_W("Solution_2022_18 is unimplemented"); //TODO: Implement me!
	return MyStr_Empty;
}

// +==============================+
// |            Day 19            |
// +==============================+
MyStr_t AocSolutionFunc_2022_19(AocSolutionStruct_2022_19_t* data, bool doSolutionB)
{
	NotifyWrite_W("Solution_2022_19 is unimplemented"); //TODO: Implement me!
	return MyStr_Empty;
}

// +==============================+
// |            Day 20            |
// +==============================+
MyStr_t AocSolutionFunc_2022_20(AocSolutionStruct_2022_20_t* data, bool doSolutionB)
{
	NotifyWrite_W("Solution_2022_20 is unimplemented"); //TODO: Implement me!
	return MyStr_Empty;
}

// +==============================+
// |            Day 21            |
// +==============================+
MyStr_t AocSolutionFunc_2022_21(AocSolutionStruct_2022_21_t* data, bool doSolutionB)
{
	NotifyWrite_W("Solution_2022_21 is unimplemented"); //TODO: Implement me!
	return MyStr_Empty;
}

// +==============================+
// |            Day 22            |
// +==============================+
MyStr_t AocSolutionFunc_2022_22(AocSolutionStruct_2022_22_t* data, bool doSolutionB)
{
	NotifyWrite_W("Solution_2022_22 is unimplemented"); //TODO: Implement me!
	return MyStr_Empty;
}

// +==============================+
// |            Day 23            |
// +==============================+
MyStr_t AocSolutionFunc_2022_23(AocSolutionStruct_2022_23_t* data, bool doSolutionB)
{
	NotifyWrite_W("Solution_2022_23 is unimplemented"); //TODO: Implement me!
	return MyStr_Empty;
}

// +==============================+
// |            Day 24            |
// +==============================+
MyStr_t AocSolutionFunc_2022_24(AocSolutionStruct_2022_24_t* data, bool doSolutionB)
{
	NotifyWrite_W("Solution_2022_24 is unimplemented"); //TODO: Implement me!
	return MyStr_Empty;
}

// +==============================+
// |            Day 25            |
// +==============================+
MyStr_t AocSolutionFunc_2022_25(AocSolutionStruct_2022_25_t* data, bool doSolutionB)
{
	NotifyWrite_W("Solution_2022_25 is unimplemented"); //TODO: Implement me!
	return MyStr_Empty;
}

// +--------------------------------------------------------------+
// |                           Generic                            |
// +--------------------------------------------------------------+
MyStr_t AocSolutionFunc(AocSolution_t solution, u64 dataSize, void* dataPntr, bool doSolutionB)
{
	Assert(dataSize == GetAocSolutionStructSize(solution));
	NotNull(dataPntr);
	NotNull(aocArena);
	switch (solution)
	{
		case AocSolution_2022_01: return AocSolutionFunc_2022_01((AocSolutionStruct_2022_01_t*)dataPntr, doSolutionB); break;
		case AocSolution_2022_02: return AocSolutionFunc_2022_02((AocSolutionStruct_2022_02_t*)dataPntr, doSolutionB); break;
		case AocSolution_2022_03: return AocSolutionFunc_2022_03((AocSolutionStruct_2022_03_t*)dataPntr, doSolutionB); break;
		case AocSolution_2022_04: return AocSolutionFunc_2022_04((AocSolutionStruct_2022_04_t*)dataPntr, doSolutionB); break;
		case AocSolution_2022_05: return AocSolutionFunc_2022_05((AocSolutionStruct_2022_05_t*)dataPntr, doSolutionB); break;
		case AocSolution_2022_06: return AocSolutionFunc_2022_06((AocSolutionStruct_2022_06_t*)dataPntr, doSolutionB); break;
		case AocSolution_2022_07: return AocSolutionFunc_2022_07((AocSolutionStruct_2022_07_t*)dataPntr, doSolutionB); break;
		case AocSolution_2022_08: return AocSolutionFunc_2022_08((AocSolutionStruct_2022_08_t*)dataPntr, doSolutionB); break;
		case AocSolution_2022_09: return AocSolutionFunc_2022_09((AocSolutionStruct_2022_09_t*)dataPntr, doSolutionB); break;
		case AocSolution_2022_10: return AocSolutionFunc_2022_10((AocSolutionStruct_2022_10_t*)dataPntr, doSolutionB); break;
		case AocSolution_2022_11: return AocSolutionFunc_2022_11((AocSolutionStruct_2022_11_t*)dataPntr, doSolutionB); break;
		case AocSolution_2022_12: return AocSolutionFunc_2022_12((AocSolutionStruct_2022_12_t*)dataPntr, doSolutionB); break;
		case AocSolution_2022_13: return AocSolutionFunc_2022_13((AocSolutionStruct_2022_13_t*)dataPntr, doSolutionB); break;
		case AocSolution_2022_14: return AocSolutionFunc_2022_14((AocSolutionStruct_2022_14_t*)dataPntr, doSolutionB); break;
		case AocSolution_2022_15: return AocSolutionFunc_2022_15((AocSolutionStruct_2022_15_t*)dataPntr, doSolutionB); break;
		case AocSolution_2022_16: return AocSolutionFunc_2022_16((AocSolutionStruct_2022_16_t*)dataPntr, doSolutionB); break;
		case AocSolution_2022_17: return AocSolutionFunc_2022_17((AocSolutionStruct_2022_17_t*)dataPntr, doSolutionB); break;
		case AocSolution_2022_18: return AocSolutionFunc_2022_18((AocSolutionStruct_2022_18_t*)dataPntr, doSolutionB); break;
		case AocSolution_2022_19: return AocSolutionFunc_2022_19((AocSolutionStruct_2022_19_t*)dataPntr, doSolutionB); break;
		case AocSolution_2022_20: return AocSolutionFunc_2022_20((AocSolutionStruct_2022_20_t*)dataPntr, doSolutionB); break;
		case AocSolution_2022_21: return AocSolutionFunc_2022_21((AocSolutionStruct_2022_21_t*)dataPntr, doSolutionB); break;
		case AocSolution_2022_22: return AocSolutionFunc_2022_22((AocSolutionStruct_2022_22_t*)dataPntr, doSolutionB); break;
		case AocSolution_2022_23: return AocSolutionFunc_2022_23((AocSolutionStruct_2022_23_t*)dataPntr, doSolutionB); break;
		case AocSolution_2022_24: return AocSolutionFunc_2022_24((AocSolutionStruct_2022_24_t*)dataPntr, doSolutionB); break;
		case AocSolution_2022_25: return AocSolutionFunc_2022_25((AocSolutionStruct_2022_25_t*)dataPntr, doSolutionB); break;
		default: Assert(false); return MyStr_Empty; break;
	}
}