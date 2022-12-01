/*
File:   aoc.h
Author: Taylor Robbins
Date:   11\29\2022
*/

#ifndef _AOC_H
#define _AOC_H

// +--------------------------------------------------------------+
// |                          Structures                          |
// +--------------------------------------------------------------+
struct AocSolutionStruct_2022_01_t { u8 stub; };
struct AocSolutionStruct_2022_02_t { u8 stub; };
struct AocSolutionStruct_2022_03_t { u8 stub; };
struct AocSolutionStruct_2022_04_t { u8 stub; };
struct AocSolutionStruct_2022_05_t { u8 stub; };
struct AocSolutionStruct_2022_06_t { u8 stub; };
struct AocSolutionStruct_2022_07_t { u8 stub; };
struct AocSolutionStruct_2022_08_t { u8 stub; };
struct AocSolutionStruct_2022_09_t { u8 stub; };
struct AocSolutionStruct_2022_10_t { u8 stub; };
struct AocSolutionStruct_2022_11_t { u8 stub; };
struct AocSolutionStruct_2022_12_t { u8 stub; };
struct AocSolutionStruct_2022_13_t { u8 stub; };
struct AocSolutionStruct_2022_14_t { u8 stub; };
struct AocSolutionStruct_2022_15_t { u8 stub; };
struct AocSolutionStruct_2022_16_t { u8 stub; };
struct AocSolutionStruct_2022_17_t { u8 stub; };
struct AocSolutionStruct_2022_18_t { u8 stub; };
struct AocSolutionStruct_2022_19_t { u8 stub; };
struct AocSolutionStruct_2022_20_t { u8 stub; };
struct AocSolutionStruct_2022_21_t { u8 stub; };
struct AocSolutionStruct_2022_22_t { u8 stub; };
struct AocSolutionStruct_2022_23_t { u8 stub; };
struct AocSolutionStruct_2022_24_t { u8 stub; };
struct AocSolutionStruct_2022_25_t { u8 stub; };

u64 GetAocSolutionStructSize(AocSolution_t solution)
{
	switch (solution)
	{
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

#endif //  _AOC_H
