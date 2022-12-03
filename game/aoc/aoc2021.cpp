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
			// PrintLine_D("%llu -> %llu (+%llu)", prevCompareValue, compareValue, compareValue - prevCompareValue);
			numIncreases++;
		}
		
		prevCompareValue = compareValue;
		prevPrevValue = prevValue;
		prevValue = lineValue;
	}
	AocCloseFile(file);
	PrintLine_D("Out of %llu depth values we increased %llu times", parser.lineIndex, numIncreases);
	
	AocReturnU64(numIncreases);
}

// +==============================+
// |            Day 02            |
// +==============================+
enum Aoc_2021_02_Instruction_t
{
	Aoc_2021_02_Instruction_Up = 0,
	Aoc_2021_02_Instruction_Down,
	Aoc_2021_02_Instruction_Forward,
	Aoc_2021_02_Instruction_NumInstructions,
};
const char* GetAoc_2021_02_InstructionStr(Aoc_2021_02_Instruction_t instruction)
{
	switch (instruction)
	{
		case Aoc_2021_02_Instruction_Up:      return "Up";
		case Aoc_2021_02_Instruction_Down:    return "Down";
		case Aoc_2021_02_Instruction_Forward: return "Forward";
		default: return "Unknown";
	}
}
// const char* ParseAoc_2021_02_InstructionStr(Aoc_2021_02_Instruction_t enumValue)
AocParseEnumFunc(Aoc_2021_02_Instruction, NumInstructions);
MyStr_t AocSolutionFunc_2021_02(AocSolutionStruct_2021_02_t* data, bool doSolutionB)
{
	AocOpenFile(file, "input_2021_02.txt");
	
	u64 numInstructions = 0;
	i32 aim = 0;
	v2i position = Vec2i_Zero;
	AocLoopFile(file, parser, line)
	{
		TempPushMark();
		u64 numPieces = 0;
		MyStr_t* linePieces = SplitString(TempArena, line, " ", &numPieces);
		Assert(numPieces == 2);
		
		MyStr_t instructionStr = linePieces[0];
		Aoc_2021_02_Instruction_t instruction = ParseAoc_2021_02_Instruction(instructionStr);
		Assert(instruction < Aoc_2021_02_Instruction_NumInstructions);
		
		i32 amount = 0;
		bool parseSuccess = TryParseI32(linePieces[1], &amount);
		Assert(parseSuccess);
		
		if (doSolutionB)
		{
			switch (instruction)
			{
				case Aoc_2021_02_Instruction_Up: aim -= amount; break;
				case Aoc_2021_02_Instruction_Down: aim += amount; break;
				case Aoc_2021_02_Instruction_Forward: position.x += amount; position.y += aim * amount; break;
			}
		}
		else
		{
			switch (instruction)
			{
				case Aoc_2021_02_Instruction_Up: position.y -= amount; break;
				case Aoc_2021_02_Instruction_Down: position.y += amount; break;
				case Aoc_2021_02_Instruction_Forward: position.x += amount; break;
			}
		}
		
		numInstructions++;
		TempPopMark();
	}
	AocCloseFile(file);
	PrintLine_D("There are %llu instructions", numInstructions);
	PrintLine_D("Ending position is (%d, %d)", position.x, position.y);
	
	AocReturnI32(position.x * position.y);
}

// +==============================+
// |            Day 03            |
// +==============================+
MyStr_t AocSolutionFunc_2021_03(AocSolutionStruct_2021_03_t* data, bool doSolutionB)
{
	AocOpenFile(file, "input_2021_03.txt");
	// AocOpenFile(file, "input_2021_03_ex.txt");
	
	VarArray_t oxygenCandidateStrs;
	CreateVarArray(&oxygenCandidateStrs, aocArena, sizeof(MyStr_t));
	VarArray_t co2CandidateStrs;
	CreateVarArray(&co2CandidateStrs, aocArena, sizeof(MyStr_t));
	
	#define MAX_NUM_BITS 12
	u64 bitOneCounts[MAX_NUM_BITS];
	ClearArray(bitOneCounts);
	u64 numBits = 0;
	u64 numEntries = 0;
	AocLoopFile(file, parser, line)
	{
		MyStr_t* newOxygenCandidateStr = VarArrayAdd(&oxygenCandidateStrs, MyStr_t);
		*newOxygenCandidateStr = line;
		MyStr_t* newCo2CandidateStr = VarArrayAdd(&co2CandidateStrs, MyStr_t);
		*newCo2CandidateStr = line;
		if (numBits == 0) { numBits = line.length; }
		else { Assert(line.length == numBits); }
		for (u64 bIndex = 0; bIndex < numBits; bIndex++)
		{
			if (line.chars[bIndex] == '1') { bitOneCounts[bIndex]++; }
		}
		numEntries++;
	}
	
	if (doSolutionB)
	{
		u64 oxygenBitOneCounts[MAX_NUM_BITS];
		u64 co2BitOneCounts[MAX_NUM_BITS];
		MyMemCopy(&oxygenBitOneCounts[0], &bitOneCounts[0], sizeof(u64) * MAX_NUM_BITS);
		MyMemCopy(&co2BitOneCounts[0], &bitOneCounts[0], sizeof(u64) * MAX_NUM_BITS);
		
		for (u64 bIndex = 0; bIndex < numBits; bIndex++)
		{
			PrintLine_I("There are now %llu/%llu 1's in column[%llu] for oxygen", oxygenBitOneCounts[bIndex], oxygenCandidateStrs.length, bIndex);
			PrintLine_I("There are now %llu/%llu 1's in column[%llu] for CO2", co2BitOneCounts[bIndex], co2CandidateStrs.length, bIndex);
			char oxygenExpectedChar = ((oxygenBitOneCounts[bIndex] >= (oxygenCandidateStrs.length - oxygenBitOneCounts[bIndex])) ? '1' : '0');
			char co2ExpectedChar = ((co2BitOneCounts[bIndex] >= (co2CandidateStrs.length - co2BitOneCounts[bIndex])) ? '0' : '1');
			if (oxygenCandidateStrs.length > 1)
			{
				for (u64 sIndex = 0; sIndex < oxygenCandidateStrs.length; )
				{
					MyStr_t* candidateStr = VarArrayGet(&oxygenCandidateStrs, sIndex, MyStr_t);
					if (candidateStr->chars[bIndex] != oxygenExpectedChar)
					{
						for (u64 bIndex2 = 0; bIndex2 < numBits; bIndex2++)
						{
							if (candidateStr->chars[bIndex2] == '1') { Assert(oxygenBitOneCounts[bIndex2] > 0); oxygenBitOneCounts[bIndex2]--; }
						}
						VarArrayRemove(&oxygenCandidateStrs, sIndex, MyStr_t);
						//don't increment sIndex
					}
					else { sIndex++; }
				}
			}
			if (co2CandidateStrs.length > 1)
			{
				for (u64 sIndex = 0; sIndex < co2CandidateStrs.length; )
				{
					MyStr_t* candidateStr = VarArrayGet(&co2CandidateStrs, sIndex, MyStr_t);
					if (candidateStr->chars[bIndex] != co2ExpectedChar)
					{
						for (u64 bIndex2 = 0; bIndex2 < numBits; bIndex2++)
						{
							if (candidateStr->chars[bIndex2] == '1') { Assert(co2BitOneCounts[bIndex2] > 0); co2BitOneCounts[bIndex2]--; }
						}
						VarArrayRemove(&co2CandidateStrs, sIndex, MyStr_t);
						//don't increment sIndex
					}
					else { sIndex++; }
				}
			}
			
			PrintLine_D("Weeded down to %llu and %llu candidates after bit[%llu] (filtered for %c and %c)", oxygenCandidateStrs.length, co2CandidateStrs.length, bIndex, oxygenExpectedChar, co2ExpectedChar);
		}
		
		Assert(oxygenCandidateStrs.length == 1);
		Assert(co2CandidateStrs.length == 1);
		MyStr_t oxygenGeneratorRatingBinStr = *VarArrayGetHard(&oxygenCandidateStrs, 0, MyStr_t);
		MyStr_t co2ScrubberRatingBinStr = *VarArrayGetHard(&co2CandidateStrs, 0, MyStr_t);
		
		u64 oxygenGeneratorRating = 0;
		bool parseSuccess = TryParseU64(TempPrintStr("0b%.*s", oxygenGeneratorRatingBinStr.length, oxygenGeneratorRatingBinStr.pntr), &oxygenGeneratorRating);
		Assert(parseSuccess);
		u64 co2ScrubberRating = 0;
		parseSuccess = TryParseU64(TempPrintStr("0b%.*s", co2ScrubberRatingBinStr.length, co2ScrubberRatingBinStr.pntr), &co2ScrubberRating);
		Assert(parseSuccess);
		
		PrintLine_D("Oxygen Generator Rating: %llu (0b%.*s)", oxygenGeneratorRating, oxygenGeneratorRatingBinStr.length, oxygenGeneratorRatingBinStr.pntr);
		PrintLine_D("CO2 Scrubber Rating: %llu (0b%.*s)", co2ScrubberRating, co2ScrubberRatingBinStr.length, co2ScrubberRatingBinStr.pntr);
		
		AocCloseFile(file);
		AocReturnU64(oxygenGeneratorRating * co2ScrubberRating);
	}
	else
	{
		AocCloseFile(file);
		
		char gammaRateBinChars[2+MAX_NUM_BITS];
		char epsilonRateBinChars[2+MAX_NUM_BITS];
		gammaRateBinChars[0] = '0'; gammaRateBinChars[1] = 'b';
		epsilonRateBinChars[0] = '0'; epsilonRateBinChars[1] = 'b';
		for (u64 bIndex = 0; bIndex < numBits; bIndex++)
		{
			gammaRateBinChars[2+bIndex] = ((bitOneCounts[bIndex] >= numEntries/2) ? '1' : '0');
			epsilonRateBinChars[2+bIndex] = ((bitOneCounts[bIndex] >= numEntries/2) ? '0' : '1');
			PrintLine_D("Bit[%llu]: %llu/%llu (Gamma:%c Epsiolon:%c)", bIndex, bitOneCounts[bIndex], numEntries, gammaRateBinChars[2+bIndex], epsilonRateBinChars[2+bIndex]);
		}
		u64 gammaRate = 0;
		u64 epsilonRate = 0;
		bool parseSuccess = TryParseU64(NewStr(2+numBits, &gammaRateBinChars[0]), &gammaRate);
		Assert(parseSuccess);
		parseSuccess = TryParseU64(NewStr(2+numBits, &epsilonRateBinChars[0]), &epsilonRate);
		Assert(parseSuccess);
		PrintLine_D("Gamma Rate: %llu", gammaRate);
		PrintLine_D("Epsilon Rate: %llu", epsilonRate);
		
		AocReturnU64(gammaRate * epsilonRate);
	}
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
