/*
File:   aoc.h
Author: Taylor Robbins
Date:   11\29\2022
*/

#ifndef _AOC_H
#define _AOC_H

enum AocSolution_t
{
	AocSolution_2022_01 = 0,
	AocSolution_2022_02,
	AocSolution_2022_03,
	AocSolution_2022_04,
	AocSolution_2022_05,
	AocSolution_2022_06,
	AocSolution_2022_07,
	AocSolution_2022_08,
	AocSolution_2022_09,
	AocSolution_2022_10,
	AocSolution_2022_11,
	AocSolution_2022_12,
	AocSolution_2022_13,
	AocSolution_2022_14,
	AocSolution_2022_15,
	AocSolution_2022_16,
	AocSolution_2022_17,
	AocSolution_2022_18,
	AocSolution_2022_19,
	AocSolution_2022_20,
	AocSolution_2022_21,
	AocSolution_2022_22,
	AocSolution_2022_23,
	AocSolution_2022_24,
	AocSolution_2022_25,
	AocSolution_NumSolutions,
	AocSolution_First = AocSolution_2022_01,
};
const char* GetAocSolutionStr(AocSolution_t solution)
{
	switch (solution)
	{
		case AocSolution_2022_01: return "2022_01";
		case AocSolution_2022_02: return "2022_02";
		case AocSolution_2022_03: return "2022_03";
		case AocSolution_2022_04: return "2022_04";
		case AocSolution_2022_05: return "2022_05";
		case AocSolution_2022_06: return "2022_06";
		case AocSolution_2022_07: return "2022_07";
		case AocSolution_2022_08: return "2022_08";
		case AocSolution_2022_09: return "2022_09";
		case AocSolution_2022_10: return "2022_10";
		case AocSolution_2022_11: return "2022_11";
		case AocSolution_2022_12: return "2022_12";
		case AocSolution_2022_13: return "2022_13";
		case AocSolution_2022_14: return "2022_14";
		case AocSolution_2022_15: return "2022_15";
		case AocSolution_2022_16: return "2022_16";
		case AocSolution_2022_17: return "2022_17";
		case AocSolution_2022_18: return "2022_18";
		case AocSolution_2022_19: return "2022_19";
		case AocSolution_2022_20: return "2022_20";
		case AocSolution_2022_21: return "2022_21";
		case AocSolution_2022_22: return "2022_22";
		case AocSolution_2022_23: return "2022_23";
		case AocSolution_2022_24: return "2022_24";
		case AocSolution_2022_25: return "2022_25";
		default: return "Unknown";
	}
}
const char* GetAocSolutionDisplayStr(AocSolution_t solution)
{
	switch (solution)
	{
		case AocSolution_2022_01: return "2022 Day 01";
		case AocSolution_2022_02: return "2022 Day 02";
		case AocSolution_2022_03: return "2022 Day 03";
		case AocSolution_2022_04: return "2022 Day 04";
		case AocSolution_2022_05: return "2022 Day 05";
		case AocSolution_2022_06: return "2022 Day 06";
		case AocSolution_2022_07: return "2022 Day 07";
		case AocSolution_2022_08: return "2022 Day 08";
		case AocSolution_2022_09: return "2022 Day 09";
		case AocSolution_2022_10: return "2022 Day 10";
		case AocSolution_2022_11: return "2022 Day 11";
		case AocSolution_2022_12: return "2022 Day 12";
		case AocSolution_2022_13: return "2022 Day 13";
		case AocSolution_2022_14: return "2022 Day 14";
		case AocSolution_2022_15: return "2022 Day 15";
		case AocSolution_2022_16: return "2022 Day 16";
		case AocSolution_2022_17: return "2022 Day 17";
		case AocSolution_2022_18: return "2022 Day 18";
		case AocSolution_2022_19: return "2022 Day 19";
		case AocSolution_2022_20: return "2022 Day 20";
		case AocSolution_2022_21: return "2022 Day 21";
		case AocSolution_2022_22: return "2022 Day 22";
		case AocSolution_2022_23: return "2022 Day 23";
		case AocSolution_2022_24: return "2022 Day 24";
		case AocSolution_2022_25: return "2022 Day 25";
		default: return "Unknown";
	}
}
u64 GetAocSolutionYear(AocSolution_t solution)
{
	if (solution >= AocSolution_2022_01 && solution <= AocSolution_2022_25) { return 2022; }
	return 0;
}
u64 GetAocSolutionDay(AocSolution_t solution) //0-indexed
{
	if (solution >= AocSolution_2022_01 && solution <= AocSolution_2022_25) { return (solution - AocSolution_2022_01); }
	return 0;
}

// +--------------------------------------------------------------+
// |                             2022                             |
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
