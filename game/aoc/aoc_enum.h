/*
File:   aoc_enum.h
Author: Taylor Robbins
Date:   11\30\2022
*/

#ifndef _AOC_ENUM_H
#define _AOC_ENUM_H

enum AocSolution_t
{
	AocSolution_2021_01 = 0,
	AocSolution_2021_02,
	AocSolution_2021_03,
	AocSolution_2021_04,
	AocSolution_2021_05,
	AocSolution_2021_06,
	AocSolution_2021_07,
	AocSolution_2021_08,
	AocSolution_2021_09,
	AocSolution_2021_10,
	AocSolution_2021_11,
	AocSolution_2021_12,
	AocSolution_2021_13,
	AocSolution_2021_14,
	AocSolution_2021_15,
	AocSolution_2021_16,
	AocSolution_2021_17,
	AocSolution_2021_18,
	AocSolution_2021_19,
	AocSolution_2021_20,
	AocSolution_2021_21,
	AocSolution_2021_22,
	AocSolution_2021_23,
	AocSolution_2021_24,
	AocSolution_2021_25,
	
	AocSolution_2022_01,
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
	AocSolution_First = AocSolution_2021_01,
};

const char* GetAocSolutionStr(AocSolution_t solution)
{
	switch (solution)
	{
		case AocSolution_2021_01: return "2021_01";
		case AocSolution_2021_02: return "2021_02";
		case AocSolution_2021_03: return "2021_03";
		case AocSolution_2021_04: return "2021_04";
		case AocSolution_2021_05: return "2021_05";
		case AocSolution_2021_06: return "2021_06";
		case AocSolution_2021_07: return "2021_07";
		case AocSolution_2021_08: return "2021_08";
		case AocSolution_2021_09: return "2021_09";
		case AocSolution_2021_10: return "2021_10";
		case AocSolution_2021_11: return "2021_11";
		case AocSolution_2021_12: return "2021_12";
		case AocSolution_2021_13: return "2021_13";
		case AocSolution_2021_14: return "2021_14";
		case AocSolution_2021_15: return "2021_15";
		case AocSolution_2021_16: return "2021_16";
		case AocSolution_2021_17: return "2021_17";
		case AocSolution_2021_18: return "2021_18";
		case AocSolution_2021_19: return "2021_19";
		case AocSolution_2021_20: return "2021_20";
		case AocSolution_2021_21: return "2021_21";
		case AocSolution_2021_22: return "2021_22";
		case AocSolution_2021_23: return "2021_23";
		case AocSolution_2021_24: return "2021_24";
		case AocSolution_2021_25: return "2021_25";
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
		case AocSolution_2021_01: return "2021 Day 01";
		case AocSolution_2021_02: return "2021 Day 02";
		case AocSolution_2021_03: return "2021 Day 03";
		case AocSolution_2021_04: return "2021 Day 04";
		case AocSolution_2021_05: return "2021 Day 05";
		case AocSolution_2021_06: return "2021 Day 06";
		case AocSolution_2021_07: return "2021 Day 07";
		case AocSolution_2021_08: return "2021 Day 08";
		case AocSolution_2021_09: return "2021 Day 09";
		case AocSolution_2021_10: return "2021 Day 10";
		case AocSolution_2021_11: return "2021 Day 11";
		case AocSolution_2021_12: return "2021 Day 12";
		case AocSolution_2021_13: return "2021 Day 13";
		case AocSolution_2021_14: return "2021 Day 14";
		case AocSolution_2021_15: return "2021 Day 15";
		case AocSolution_2021_16: return "2021 Day 16";
		case AocSolution_2021_17: return "2021 Day 17";
		case AocSolution_2021_18: return "2021 Day 18";
		case AocSolution_2021_19: return "2021 Day 19";
		case AocSolution_2021_20: return "2021 Day 20";
		case AocSolution_2021_21: return "2021 Day 21";
		case AocSolution_2021_22: return "2021 Day 22";
		case AocSolution_2021_23: return "2021 Day 23";
		case AocSolution_2021_24: return "2021 Day 24";
		case AocSolution_2021_25: return "2021 Day 25";
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
	if (solution >= AocSolution_2021_01 && solution <= AocSolution_2021_25) { return 2021; }
	if (solution >= AocSolution_2022_01 && solution <= AocSolution_2022_25) { return 2022; }
	return 0;
}
u64 GetAocSolutionDay(AocSolution_t solution) //0-indexed
{
	if (solution >= AocSolution_2021_01 && solution <= AocSolution_2021_25) { return (solution - AocSolution_2021_01); }
	if (solution >= AocSolution_2022_01 && solution <= AocSolution_2022_25) { return (solution - AocSolution_2022_01); }
	return 0;
}

#endif //  _AOC_ENUM_H
