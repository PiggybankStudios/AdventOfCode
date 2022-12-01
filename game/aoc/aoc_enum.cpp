/*
File:   aoc_enum.cpp
Author: Taylor Robbins
Date:   11\30\2022
Description: 
	** Contains the large switch statement that makes it easy to call one of the
	** many AocSolutionFuncs using the AocSolution_t enum
*/

u64 GetAocSolutionStructSize(AocSolution_t solution)
{
	switch (solution)
	{
		case AocSolution_2021_01: return sizeof(AocSolutionStruct_2021_01_t);
		case AocSolution_2021_02: return sizeof(AocSolutionStruct_2021_02_t);
		case AocSolution_2021_03: return sizeof(AocSolutionStruct_2021_03_t);
		case AocSolution_2021_04: return sizeof(AocSolutionStruct_2021_04_t);
		case AocSolution_2021_05: return sizeof(AocSolutionStruct_2021_05_t);
		case AocSolution_2021_06: return sizeof(AocSolutionStruct_2021_06_t);
		case AocSolution_2021_07: return sizeof(AocSolutionStruct_2021_07_t);
		case AocSolution_2021_08: return sizeof(AocSolutionStruct_2021_08_t);
		case AocSolution_2021_09: return sizeof(AocSolutionStruct_2021_09_t);
		case AocSolution_2021_10: return sizeof(AocSolutionStruct_2021_10_t);
		case AocSolution_2021_11: return sizeof(AocSolutionStruct_2021_11_t);
		case AocSolution_2021_12: return sizeof(AocSolutionStruct_2021_12_t);
		case AocSolution_2021_13: return sizeof(AocSolutionStruct_2021_13_t);
		case AocSolution_2021_14: return sizeof(AocSolutionStruct_2021_14_t);
		case AocSolution_2021_15: return sizeof(AocSolutionStruct_2021_15_t);
		case AocSolution_2021_16: return sizeof(AocSolutionStruct_2021_16_t);
		case AocSolution_2021_17: return sizeof(AocSolutionStruct_2021_17_t);
		case AocSolution_2021_18: return sizeof(AocSolutionStruct_2021_18_t);
		case AocSolution_2021_19: return sizeof(AocSolutionStruct_2021_19_t);
		case AocSolution_2021_20: return sizeof(AocSolutionStruct_2021_20_t);
		case AocSolution_2021_21: return sizeof(AocSolutionStruct_2021_21_t);
		case AocSolution_2021_22: return sizeof(AocSolutionStruct_2021_22_t);
		case AocSolution_2021_23: return sizeof(AocSolutionStruct_2021_23_t);
		case AocSolution_2021_24: return sizeof(AocSolutionStruct_2021_24_t);
		case AocSolution_2021_25: return sizeof(AocSolutionStruct_2021_25_t);
		case AocSolution_2022_01: return sizeof(AocSolutionStruct_2022_01_t);
		case AocSolution_2022_02: return sizeof(AocSolutionStruct_2022_02_t);
		case AocSolution_2022_03: return sizeof(AocSolutionStruct_2022_03_t);
		case AocSolution_2022_04: return sizeof(AocSolutionStruct_2022_04_t);
		case AocSolution_2022_05: return sizeof(AocSolutionStruct_2022_05_t);
		case AocSolution_2022_06: return sizeof(AocSolutionStruct_2022_06_t);
		case AocSolution_2022_07: return sizeof(AocSolutionStruct_2022_07_t);
		case AocSolution_2022_08: return sizeof(AocSolutionStruct_2022_08_t);
		case AocSolution_2022_09: return sizeof(AocSolutionStruct_2022_09_t);
		case AocSolution_2022_10: return sizeof(AocSolutionStruct_2022_10_t);
		case AocSolution_2022_11: return sizeof(AocSolutionStruct_2022_11_t);
		case AocSolution_2022_12: return sizeof(AocSolutionStruct_2022_12_t);
		case AocSolution_2022_13: return sizeof(AocSolutionStruct_2022_13_t);
		case AocSolution_2022_14: return sizeof(AocSolutionStruct_2022_14_t);
		case AocSolution_2022_15: return sizeof(AocSolutionStruct_2022_15_t);
		case AocSolution_2022_16: return sizeof(AocSolutionStruct_2022_16_t);
		case AocSolution_2022_17: return sizeof(AocSolutionStruct_2022_17_t);
		case AocSolution_2022_18: return sizeof(AocSolutionStruct_2022_18_t);
		case AocSolution_2022_19: return sizeof(AocSolutionStruct_2022_19_t);
		case AocSolution_2022_20: return sizeof(AocSolutionStruct_2022_20_t);
		case AocSolution_2022_21: return sizeof(AocSolutionStruct_2022_21_t);
		case AocSolution_2022_22: return sizeof(AocSolutionStruct_2022_22_t);
		case AocSolution_2022_23: return sizeof(AocSolutionStruct_2022_23_t);
		case AocSolution_2022_24: return sizeof(AocSolutionStruct_2022_24_t);
		case AocSolution_2022_25: return sizeof(AocSolutionStruct_2022_25_t);
		default: return 0;
	}
}

MyStr_t AocSolutionFunc(AocSolution_t solution, u64 dataSize, void* dataPntr, bool doSolutionB)
{
	Assert(dataSize == GetAocSolutionStructSize(solution));
	NotNull(dataPntr);
	NotNull(aocArena);
	switch (solution)
	{
		case AocSolution_2021_01: return AocSolutionFunc_2021_01((AocSolutionStruct_2021_01_t*)dataPntr, doSolutionB); break;
		case AocSolution_2021_02: return AocSolutionFunc_2021_02((AocSolutionStruct_2021_02_t*)dataPntr, doSolutionB); break;
		case AocSolution_2021_03: return AocSolutionFunc_2021_03((AocSolutionStruct_2021_03_t*)dataPntr, doSolutionB); break;
		case AocSolution_2021_04: return AocSolutionFunc_2021_04((AocSolutionStruct_2021_04_t*)dataPntr, doSolutionB); break;
		case AocSolution_2021_05: return AocSolutionFunc_2021_05((AocSolutionStruct_2021_05_t*)dataPntr, doSolutionB); break;
		case AocSolution_2021_06: return AocSolutionFunc_2021_06((AocSolutionStruct_2021_06_t*)dataPntr, doSolutionB); break;
		case AocSolution_2021_07: return AocSolutionFunc_2021_07((AocSolutionStruct_2021_07_t*)dataPntr, doSolutionB); break;
		case AocSolution_2021_08: return AocSolutionFunc_2021_08((AocSolutionStruct_2021_08_t*)dataPntr, doSolutionB); break;
		case AocSolution_2021_09: return AocSolutionFunc_2021_09((AocSolutionStruct_2021_09_t*)dataPntr, doSolutionB); break;
		case AocSolution_2021_10: return AocSolutionFunc_2021_10((AocSolutionStruct_2021_10_t*)dataPntr, doSolutionB); break;
		case AocSolution_2021_11: return AocSolutionFunc_2021_11((AocSolutionStruct_2021_11_t*)dataPntr, doSolutionB); break;
		case AocSolution_2021_12: return AocSolutionFunc_2021_12((AocSolutionStruct_2021_12_t*)dataPntr, doSolutionB); break;
		case AocSolution_2021_13: return AocSolutionFunc_2021_13((AocSolutionStruct_2021_13_t*)dataPntr, doSolutionB); break;
		case AocSolution_2021_14: return AocSolutionFunc_2021_14((AocSolutionStruct_2021_14_t*)dataPntr, doSolutionB); break;
		case AocSolution_2021_15: return AocSolutionFunc_2021_15((AocSolutionStruct_2021_15_t*)dataPntr, doSolutionB); break;
		case AocSolution_2021_16: return AocSolutionFunc_2021_16((AocSolutionStruct_2021_16_t*)dataPntr, doSolutionB); break;
		case AocSolution_2021_17: return AocSolutionFunc_2021_17((AocSolutionStruct_2021_17_t*)dataPntr, doSolutionB); break;
		case AocSolution_2021_18: return AocSolutionFunc_2021_18((AocSolutionStruct_2021_18_t*)dataPntr, doSolutionB); break;
		case AocSolution_2021_19: return AocSolutionFunc_2021_19((AocSolutionStruct_2021_19_t*)dataPntr, doSolutionB); break;
		case AocSolution_2021_20: return AocSolutionFunc_2021_20((AocSolutionStruct_2021_20_t*)dataPntr, doSolutionB); break;
		case AocSolution_2021_21: return AocSolutionFunc_2021_21((AocSolutionStruct_2021_21_t*)dataPntr, doSolutionB); break;
		case AocSolution_2021_22: return AocSolutionFunc_2021_22((AocSolutionStruct_2021_22_t*)dataPntr, doSolutionB); break;
		case AocSolution_2021_23: return AocSolutionFunc_2021_23((AocSolutionStruct_2021_23_t*)dataPntr, doSolutionB); break;
		case AocSolution_2021_24: return AocSolutionFunc_2021_24((AocSolutionStruct_2021_24_t*)dataPntr, doSolutionB); break;
		case AocSolution_2021_25: return AocSolutionFunc_2021_25((AocSolutionStruct_2021_25_t*)dataPntr, doSolutionB); break;
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
