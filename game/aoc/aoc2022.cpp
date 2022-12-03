/*
File:   aoc2022.cpp
Author: Taylor Robbins
Date:   11\29\2022
Description: 
	** Holds the advent of code solution functions for 2022
*/

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
	
	PrintLine_D("There are %llu elves total (%llu lines in file)", counts.length, parser.lineIndex);
	
	if (doSolutionB)
	{
		const u64 numElvesToFind = 3;
		i64 foundIndices[numElvesToFind] = {-1, -1, -1};
		u64 maxCountsTotal = 0;
		for (u8 pass = 0; pass < numElvesToFind; pass++)
		{
			u64 maxCount = 0;
			u64 maxCountIndex = 0;
			VarArrayLoop(&counts, eIndex)
			{
				VarArrayLoopGet(u64, countPntr, &counts, eIndex);
				bool isElfAlreadyFound = false;
				for (u8 fIndex = 0; fIndex < numElvesToFind; fIndex++)
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
enum Aoc2022_02_t
{
	Aoc2022_02_Rock = 0,
	Aoc2022_02_Paper,
	Aoc2022_02_Scissors,
	Aoc2022_02_NumOptions,
};
const char* GetAoc2022_02Str(Aoc2022_02_t enumValue)
{
	switch (enumValue)
	{
		case Aoc2022_02_Rock:     return "Rock";
		case Aoc2022_02_Paper:    return "Paper";
		case Aoc2022_02_Scissors: return "Scissors";
		default: return "Unknown";
	}
}
enum Aoc2022_02_Result_t
{
	Aoc2022_02_Result_Lose = -1,
	Aoc2022_02_Result_Draw = 0,
	Aoc2022_02_Result_Win = 1,
	Aoc2022_02_Result_NumOptions,
};
const char* GetAoc2022_02_ResultStr(Aoc2022_02_Result_t enumValue)
{
	switch (enumValue)
	{
		case Aoc2022_02_Result_Lose: return "Lose";
		case Aoc2022_02_Result_Draw: return "Draw";
		case Aoc2022_02_Result_Win:  return "Win";
		default: return "Unknown";
	}
}
Aoc2022_02_t GetAoc2022_02_ForChar(char c)
{
	switch (c)
	{
		case 'A': return Aoc2022_02_Rock;
		case 'B': return Aoc2022_02_Paper;
		case 'C': return Aoc2022_02_Scissors;
		case 'X': return Aoc2022_02_Rock;
		case 'Y': return Aoc2022_02_Paper;
		case 'Z': return Aoc2022_02_Scissors;
		default: return Aoc2022_02_NumOptions;
	}
}
Aoc2022_02_Result_t GetAoc2022_02_ResultForChar(char c)
{
	switch (c)
	{
		case 'X': return Aoc2022_02_Result_Lose;
		case 'Y': return Aoc2022_02_Result_Draw;
		case 'Z': return Aoc2022_02_Result_Win;
		default: return Aoc2022_02_Result_NumOptions;
	}
}
Aoc2022_02_t GetAoc2022_02_Pair(Aoc2022_02_t enumValue, Aoc2022_02_Result_t otherShouldGetResult)
{
	int resultInt = (int)(enumValue) + (int)(otherShouldGetResult);
	if (resultInt < 0) { resultInt += 3; }
	if (resultInt >= 3) { resultInt -= 3; }
	return (Aoc2022_02_t)resultInt;
}
u64 GetAoc2022_02_Score(Aoc2022_02_t enumValue)
{
	switch (enumValue)
	{
		case Aoc2022_02_Rock:     return 1;
		case Aoc2022_02_Paper:    return 2;
		case Aoc2022_02_Scissors: return 3;
		default: return 0;
	}
}
u64 GetAoc2022_02_ResultScore(Aoc2022_02_Result_t result)
{
	switch (result)
	{
		case Aoc2022_02_Result_Lose: return 0;
		case Aoc2022_02_Result_Draw: return 3;
		case Aoc2022_02_Result_Win:  return 6;
		default: return 0;
	}
}
Aoc2022_02_Result_t GetAoc2022_02_ResultForMoves(Aoc2022_02_t yourMove, Aoc2022_02_t opponentMove)
{
	if (yourMove == GetAoc2022_02_Pair(opponentMove, Aoc2022_02_Result_Win))  { return Aoc2022_02_Result_Win;  }
	if (yourMove == GetAoc2022_02_Pair(opponentMove, Aoc2022_02_Result_Draw)) { return Aoc2022_02_Result_Draw; }
	if (yourMove == GetAoc2022_02_Pair(opponentMove, Aoc2022_02_Result_Lose)) { return Aoc2022_02_Result_Lose; }
	return Aoc2022_02_Result_NumOptions;
}
MyStr_t AocSolutionFunc_2022_02(AocSolutionStruct_2022_02_t* data, bool doSolutionB)
{
	AocOpenFile(file, "input_2022_02.txt");
	
	AocVarArrayU64(counts);
	u64* currentCountPntr = nullptr;
	
	u64 numInstructions = 0;
	u64 yourScore = 0;
	AocLoopFile(file, parser, line)
	{
		Assert(line.length == 3);
		Aoc2022_02_t opponentMove = GetAoc2022_02_ForChar(line.chars[0]);
		Aoc2022_02_t yourMove = GetAoc2022_02_ForChar(line.chars[2]);
		
		u64 roundScore = 0;
		
		if (doSolutionB)
		{
			Aoc2022_02_Result_t expectedResult = GetAoc2022_02_ResultForChar(line.chars[2]);
			yourMove = GetAoc2022_02_Pair(opponentMove, expectedResult);
			// PrintLine_D("You need to %s", GetAoc2022_02_ResultStr(expectedResult));
		}
		
		Aoc2022_02_Result_t roundResult = GetAoc2022_02_ResultForMoves(yourMove, opponentMove);
		roundScore += GetAoc2022_02_Score(yourMove);
		roundScore += GetAoc2022_02_ResultScore(roundResult);
		// PrintLine_D("Opponent throws %s. You throw %s. roundScore is %d", GetAoc2022_02Str(opponentMove), GetAoc2022_02Str(yourMove), roundScore);
		
		yourScore += roundScore;
		
		numInstructions++;
	}
	AocCloseFile(file);
	PrintLine_D("Total Rounds: %llu", numInstructions);
	PrintLine_D("Your Score: %llu", yourScore);
	
	AocReturnU64(yourScore);
}

// +==============================+
// |            Day 03            |
// +==============================+
u64 GetItemCode(char item)
{
	if (item >= 'a' && item <= 'z') { return 1 + (item - 'a'); }
	if (item >= 'A' && item <= 'Z') { return 27 + (item - 'A'); }
	return 0;
}
MyStr_t AocSolutionFunc_2022_03(AocSolutionStruct_2022_03_t* data, bool doSolutionB)
{
	AocOpenFile(file, "input_2022_03.txt");
	// AocOpenFile(file, "input_2022_03_ex.txt");
	
	// AocVarArrayU64(counts);
	
	u64 numBagsInGroup = 0;
	MyStr_t groupStrs[3];
	u64 result = 0;
	AocLoopFile(file, parser, line)
	{
		if (doSolutionB)
		{
			// PrintLine_D("Putting in %llu", numBagsInGroup);
			groupStrs[numBagsInGroup] = line;
			numBagsInGroup++;
			
			if (numBagsInGroup >= 3)
			{
				bool foundCode = false;
				for (u64 cIndex1 = 0; cIndex1 < groupStrs[0].length; cIndex1++)
				{
					char item = groupStrs[0].chars[cIndex1];
					bool inBag2 = false;
					for (u64 cIndex2 = 0; cIndex2 < groupStrs[1].length; cIndex2++)
					{
						char itemIn2 = groupStrs[1].chars[cIndex2];
						if (itemIn2 == item) { inBag2 = true; break; }
					}
					bool inBag3 = false;
					for (u64 cIndex3 = 0; cIndex3 < groupStrs[2].length; cIndex3++)
					{
						char itemIn3 = groupStrs[2].chars[cIndex3];
						if (itemIn3 == item) { inBag3 = true; break; }
					}
					if (inBag2 && inBag3)
					{
						result += GetItemCode(item);
						// PrintLine_D("Group has code %c", item);
						foundCode = true;
						break;
					}
				}
				
				if (!foundCode)
				{
					PrintLine_E("Failed to find common item in:\n%.*s\n%.*s\n%.*s",
						groupStrs[0].length, groupStrs[0].pntr,
						groupStrs[1].length, groupStrs[1].pntr,
						groupStrs[2].length, groupStrs[2].pntr
					);
				}
				
				numBagsInGroup = 0;
			}
		}
		else
		{
			Assert(line.length%2 == 0);
			MyStr_t firstCompartmentStr = StrSubstring(&line, 0, line.length/2);
			MyStr_t secondCompartmentStr = StrSubstring(&line, line.length/2);
			PrintLine_D("%.*s | %.*s", firstCompartmentStr.length, firstCompartmentStr.pntr, secondCompartmentStr.length, secondCompartmentStr.pntr);
			u64 numSharedItems = 0;
			char sharedItems[64];
			for (u64 cIndex = 0; cIndex < firstCompartmentStr.length; cIndex++)
			{
				char item = firstCompartmentStr.chars[cIndex];
				bool foundInSecond = false;
				for (u64 cIndex2 = 0; cIndex2 < secondCompartmentStr.length; cIndex2++)
				{
					if (item == secondCompartmentStr.chars[cIndex2]) { foundInSecond = true; break; }
				}
				if (foundInSecond)
				{
					if (numSharedItems < ArrayCount(sharedItems) && !FindSubstring(NewStr(numSharedItems, &sharedItems[0]), NewStr(1, &item)))
					{
						PrintLine_D("Bag contains \'%c\' in both compartments", item);
						sharedItems[numSharedItems] = item;
						numSharedItems++;
						
						result += GetItemCode(item);
					}
				}
			}
		}
	}
	AocCloseFile(file);
	
	AocReturnU64(result);
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
