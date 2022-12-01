/*
File:   aoc2021.cpp
Author: Taylor Robbins
Date:   12\01\2022
Description: 
	** Holds the advent of code solution functions for 2021
*/

// +==============================+
// |            Day 01            |
// +==============================+
MyStr_t AocSolutionFunc_2021_01(AocSolutionStruct_2021_01_t* data, bool doSolutionB)
{
	AocOpenFile(file, "input_2021_01.txt");
	
	u64 numIncreases = 0;
	u64 prevCompareValue = 0;
	u64 prevValue = 0;
	u64 prevPrevValue = 0;
	AocLoopFile(file, parser, line)
	{
		u64 lineValue = 0;
		bool parseSuccess = TryParseU64(line, &lineValue);
		Assert(parseSuccess);
		
		u64 compareValue = (doSolutionB ? (lineValue + prevValue + prevPrevValue) : lineValue);
		prevCompareValue = (doSolutionB ? prevCompareValue : prevValue);
		
		// PrintLine_D("Line[%llu]: %llu", parser.lineIndex-1, lineValue);
		if (parser.lineIndex > (doSolutionB ? 3 : 1) && compareValue > prevCompareValue)
		{
			PrintLine_D("%llu -> %llu (+%llu)", prevCompareValue, compareValue, compareValue - prevCompareValue);
			numIncreases++;
		}
		
		prevCompareValue = compareValue;
		prevPrevValue = prevValue;
		prevValue = lineValue;
	}
	AocCloseFile(file);
	
	AocReturnU64(numIncreases);
}

// +==============================+
// |            Day 02            |
// +==============================+
MyStr_t AocSolutionFunc_2021_02(AocSolutionStruct_2021_02_t* data, bool doSolutionB)
{
	NotifyWrite_W("Solution_2021_02 is unimplemented"); //TODO: Implement me!
	return MyStr_Empty;
}

// +==============================+
// |            Day 03            |
// +==============================+
MyStr_t AocSolutionFunc_2021_03(AocSolutionStruct_2021_03_t* data, bool doSolutionB)
{
	NotifyWrite_W("Solution_2021_03 is unimplemented"); //TODO: Implement me!
	return MyStr_Empty;
}

// +==============================+
// |            Day 04            |
// +==============================+
MyStr_t AocSolutionFunc_2021_04(AocSolutionStruct_2021_04_t* data, bool doSolutionB)
{
	NotifyWrite_W("Solution_2021_04 is unimplemented"); //TODO: Implement me!
	return MyStr_Empty;
}

// +==============================+
// |            Day 05            |
// +==============================+
MyStr_t AocSolutionFunc_2021_05(AocSolutionStruct_2021_05_t* data, bool doSolutionB)
{
	NotifyWrite_W("Solution_2021_05 is unimplemented"); //TODO: Implement me!
	return MyStr_Empty;
}

// +==============================+
// |            Day 06            |
// +==============================+
MyStr_t AocSolutionFunc_2021_06(AocSolutionStruct_2021_06_t* data, bool doSolutionB)
{
	NotifyWrite_W("Solution_2021_06 is unimplemented"); //TODO: Implement me!
	return MyStr_Empty;
}

// +==============================+
// |            Day 07            |
// +==============================+
MyStr_t AocSolutionFunc_2021_07(AocSolutionStruct_2021_07_t* data, bool doSolutionB)
{
	NotifyWrite_W("Solution_2021_07 is unimplemented"); //TODO: Implement me!
	return MyStr_Empty;
}

// +==============================+
// |            Day 08            |
// +==============================+
MyStr_t AocSolutionFunc_2021_08(AocSolutionStruct_2021_08_t* data, bool doSolutionB)
{
	NotifyWrite_W("Solution_2021_08 is unimplemented"); //TODO: Implement me!
	return MyStr_Empty;
}

// +==============================+
// |            Day 09            |
// +==============================+
MyStr_t AocSolutionFunc_2021_09(AocSolutionStruct_2021_09_t* data, bool doSolutionB)
{
	NotifyWrite_W("Solution_2021_09 is unimplemented"); //TODO: Implement me!
	return MyStr_Empty;
}

// +==============================+
// |            Day 10            |
// +==============================+
MyStr_t AocSolutionFunc_2021_10(AocSolutionStruct_2021_10_t* data, bool doSolutionB)
{
	NotifyWrite_W("Solution_2021_10 is unimplemented"); //TODO: Implement me!
	return MyStr_Empty;
}

// +==============================+
// |            Day 11            |
// +==============================+
MyStr_t AocSolutionFunc_2021_11(AocSolutionStruct_2021_11_t* data, bool doSolutionB)
{
	NotifyWrite_W("Solution_2021_11 is unimplemented"); //TODO: Implement me!
	return MyStr_Empty;
}

// +==============================+
// |            Day 12            |
// +==============================+
MyStr_t AocSolutionFunc_2021_12(AocSolutionStruct_2021_12_t* data, bool doSolutionB)
{
	NotifyWrite_W("Solution_2021_12 is unimplemented"); //TODO: Implement me!
	return MyStr_Empty;
}

// +==============================+
// |            Day 13            |
// +==============================+
MyStr_t AocSolutionFunc_2021_13(AocSolutionStruct_2021_13_t* data, bool doSolutionB)
{
	NotifyWrite_W("Solution_2021_13 is unimplemented"); //TODO: Implement me!
	return MyStr_Empty;
}

// +==============================+
// |            Day 14            |
// +==============================+
MyStr_t AocSolutionFunc_2021_14(AocSolutionStruct_2021_14_t* data, bool doSolutionB)
{
	NotifyWrite_W("Solution_2021_14 is unimplemented"); //TODO: Implement me!
	return MyStr_Empty;
}

// +==============================+
// |            Day 15            |
// +==============================+
MyStr_t AocSolutionFunc_2021_15(AocSolutionStruct_2021_15_t* data, bool doSolutionB)
{
	NotifyWrite_W("Solution_2021_15 is unimplemented"); //TODO: Implement me!
	return MyStr_Empty;
}

// +==============================+
// |            Day 16            |
// +==============================+
MyStr_t AocSolutionFunc_2021_16(AocSolutionStruct_2021_16_t* data, bool doSolutionB)
{
	NotifyWrite_W("Solution_2021_16 is unimplemented"); //TODO: Implement me!
	return MyStr_Empty;
}

// +==============================+
// |            Day 17            |
// +==============================+
MyStr_t AocSolutionFunc_2021_17(AocSolutionStruct_2021_17_t* data, bool doSolutionB)
{
	NotifyWrite_W("Solution_2021_17 is unimplemented"); //TODO: Implement me!
	return MyStr_Empty;
}

// +==============================+
// |            Day 18            |
// +==============================+
MyStr_t AocSolutionFunc_2021_18(AocSolutionStruct_2021_18_t* data, bool doSolutionB)
{
	NotifyWrite_W("Solution_2021_18 is unimplemented"); //TODO: Implement me!
	return MyStr_Empty;
}

// +==============================+
// |            Day 19            |
// +==============================+
MyStr_t AocSolutionFunc_2021_19(AocSolutionStruct_2021_19_t* data, bool doSolutionB)
{
	NotifyWrite_W("Solution_2021_19 is unimplemented"); //TODO: Implement me!
	return MyStr_Empty;
}

// +==============================+
// |            Day 20            |
// +==============================+
MyStr_t AocSolutionFunc_2021_20(AocSolutionStruct_2021_20_t* data, bool doSolutionB)
{
	NotifyWrite_W("Solution_2021_20 is unimplemented"); //TODO: Implement me!
	return MyStr_Empty;
}

// +==============================+
// |            Day 21            |
// +==============================+
MyStr_t AocSolutionFunc_2021_21(AocSolutionStruct_2021_21_t* data, bool doSolutionB)
{
	NotifyWrite_W("Solution_2021_21 is unimplemented"); //TODO: Implement me!
	return MyStr_Empty;
}

// +==============================+
// |            Day 22            |
// +==============================+
MyStr_t AocSolutionFunc_2021_22(AocSolutionStruct_2021_22_t* data, bool doSolutionB)
{
	NotifyWrite_W("Solution_2021_22 is unimplemented"); //TODO: Implement me!
	return MyStr_Empty;
}

// +==============================+
// |            Day 23            |
// +==============================+
MyStr_t AocSolutionFunc_2021_23(AocSolutionStruct_2021_23_t* data, bool doSolutionB)
{
	NotifyWrite_W("Solution_2021_23 is unimplemented"); //TODO: Implement me!
	return MyStr_Empty;
}

// +==============================+
// |            Day 24            |
// +==============================+
MyStr_t AocSolutionFunc_2021_24(AocSolutionStruct_2021_24_t* data, bool doSolutionB)
{
	NotifyWrite_W("Solution_2021_24 is unimplemented"); //TODO: Implement me!
	return MyStr_Empty;
}

// +==============================+
// |            Day 25            |
// +==============================+
MyStr_t AocSolutionFunc_2021_25(AocSolutionStruct_2021_25_t* data, bool doSolutionB)
{
	NotifyWrite_W("Solution_2021_25 is unimplemented"); //TODO: Implement me!
	return MyStr_Empty;
}
