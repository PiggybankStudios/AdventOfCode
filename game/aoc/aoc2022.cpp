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
u64 Aoc2022_03_GetItemPriority(char itemChar)
{
	if (itemChar >= 'a' && itemChar <= 'z') { return 1 + (itemChar - 'a'); }
	if (itemChar >= 'A' && itemChar <= 'Z') { return 27 + (itemChar - 'A'); }
	return 0;
}
u64 Aoc2022_03_IsItemCharInStr(MyStr_t bagStr, char itemChar)
{
	return FindSubstring(bagStr, NewStr(1, &itemChar));
}
MyStr_t AocSolutionFunc_2022_03(AocSolutionStruct_2022_03_t* data, bool doSolutionB)
{
	AocOpenFile(file, "input_2022_03.txt");
	// AocOpenFile(file, "input_2022_03_ex.txt");
	
	u64 numBagsInGroup = 0;
	MyStr_t groupStrs[3];
	u64 result = 0;
	u64 numGroups = 0;
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
					char itemChar = groupStrs[0].chars[cIndex1];
					bool isItemInBag2 = Aoc2022_03_IsItemCharInStr(groupStrs[1], itemChar);
					bool isItemInBag3 = Aoc2022_03_IsItemCharInStr(groupStrs[2], itemChar);
					if (isItemInBag2 && isItemInBag3)
					{
						result += Aoc2022_03_GetItemPriority(itemChar);
						// PrintLine_D("Group has code %c", itemChar);
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
				
				numGroups++;
				numBagsInGroup = 0;
			}
		}
		else
		{
			Assert(line.length%2 == 0);
			MyStr_t bagFirstHalf = StrSubstring(&line, 0, line.length/2);
			MyStr_t bagSecondHalf = StrSubstring(&line, line.length/2);
			// PrintLine_D("%.*s | %.*s", bagFirstHalf.length, bagFirstHalf.pntr, bagSecondHalf.length, bagSecondHalf.pntr);
			char sharedItemChars[64];
			MyStr_t sharedItemsStr = NewStr(0, &sharedItemChars[0]);
			for (u64 cIndex = 0; cIndex < bagFirstHalf.length; cIndex++)
			{
				char itemChar = bagFirstHalf.chars[cIndex];
				bool foundInSecond = false;
				for (u64 cIndex2 = 0; cIndex2 < bagSecondHalf.length; cIndex2++)
				{
					if (itemChar == bagSecondHalf.chars[cIndex2]) { foundInSecond = true; break; }
				}
				if (foundInSecond)
				{
					if (!Aoc2022_03_IsItemCharInStr(sharedItemsStr, itemChar) &&
						sharedItemsStr.length < ArrayCount(sharedItemChars))
					{
						// PrintLine_D("Bag contains \'%c\' in both compartments", itemChar);
						sharedItemsStr.chars[sharedItemsStr.length] = itemChar;
						sharedItemsStr.length++;
						result += Aoc2022_03_GetItemPriority(itemChar);
					}
				}
			}
		}
	}
	AocCloseFile(file);
	Assert(numBagsInGroup == 0);
	if (doSolutionB) { PrintLine_D("There were %llu groups of 3", numGroups); }
	PrintLine_D("Total priority aggregate is %llu", result);
	
	AocReturnU64(result);
}

// +==============================+
// |            Day 04            |
// +==============================+
MyStr_t AocSolutionFunc_2022_04(AocSolutionStruct_2022_04_t* data, bool doSolutionB)
{
	AocOpenFile(file, "input_2022_04.txt");
	// AocOpenFile(file, "input_2022_04_ex.txt");
	
	u64 result = 0;
	AocLoopFile(file, parser, line)
	{
		u64 commaIndex = 0;
		bool foundComma = FindSubstring(line, ",", &commaIndex);
		Assert(foundComma);
		MyStr_t firstHalfLine = StrSubstring(&line, 0, commaIndex);
		MyStr_t secondHalfLine = StrSubstring(&line, commaIndex+1);
		// PrintLine_D("commaIndex = %llu \"%.*s\" \"%.*s\"", commaIndex, firstHalfLine.length, firstHalfLine.pntr, secondHalfLine.length, secondHalfLine.pntr);
		
		u64 firstHyphenIndex = 0;
		bool foundFirstHyphen = FindSubstring(firstHalfLine, "-", &firstHyphenIndex);
		Assert(foundFirstHyphen);
		u64 secondHyphenIndex = 0;
		bool foundSecondHyphen = FindSubstring(secondHalfLine, "-", &secondHyphenIndex);
		Assert(foundSecondHyphen);
		MyStr_t numberStrs[4];
		numberStrs[0] = StrSubstring(&firstHalfLine, 0, firstHyphenIndex);
		numberStrs[1] = StrSubstring(&firstHalfLine, firstHyphenIndex+1);
		numberStrs[2] = StrSubstring(&secondHalfLine, 0, secondHyphenIndex);
		numberStrs[3] = StrSubstring(&secondHalfLine, secondHyphenIndex+1);
		// PrintLine_D("\"%.*s\" \"%.*s\" \"%.*s\" \"%.*s\"",
		// 	numberStrs[0].length, numberStrs[0].pntr,
		// 	numberStrs[1].length, numberStrs[1].pntr,
		// 	numberStrs[2].length, numberStrs[2].pntr,
		// 	numberStrs[3].length, numberStrs[3].pntr
		// );
		
		u64 min1, max1, min2, max2;
		bool parseNum1 = TryParseU64(numberStrs[0], &min1); Assert(parseNum1);
		bool parseNum2 = TryParseU64(numberStrs[1], &max1); Assert(parseNum2);
		bool parseNum3 = TryParseU64(numberStrs[2], &min2); Assert(parseNum3);
		bool parseNum4 = TryParseU64(numberStrs[3], &max2); Assert(parseNum4);
		// PrintLine_D("%llu, %llu, %llu, %llu", numbers[0], numbers[1], numbers[2], numbers[3]);
		
		if (doSolutionB)
		{
			if ((max1 >= min2 && min1 <= max2))
			{
				PrintLine_D("Overlapping! (%llu-%llu, %llu-%llu)", min1, max1, min2, max2);
				result++;
			}
		}
		else
		{
			if ((min1 >= min2 && max1 <= max2) ||
				(min2 >= min1 && max2 <= max1))
			{
				PrintLine_D("Fully contained! (%llu-%llu, %llu-%llu)", min1, max1, min2, max2);
				result++;
			}
		}
	}
	AocCloseFile(file);
	
	AocReturnU64(result);
}

// +==============================+
// |            Day 05            |
// +==============================+
MyStr_t AocSolutionFunc_2022_05(AocSolutionStruct_2022_05_t* data, bool doSolutionB)
{
	AocOpenFile(file, "input_2022_05.txt");
	// AocOpenFile(file, "input_2022_05_ex.txt");
	
	#define MAX_NUM_STACKS   10
	#define MAX_STACK_HEIGHT 64
	u64 totalNumCrates = 0;
	u64 maxStackHeight = 0;
	u64 numStacks = 0;
	char stacks[MAX_NUM_STACKS][MAX_STACK_HEIGHT];
	u64 stackHeights[MAX_NUM_STACKS];
	bool foundEndOfStacks = false;
	MyMemSet(stacks, 0x00, sizeof(char) * MAX_NUM_STACKS * MAX_STACK_HEIGHT);
	u64 numMoves = 0;
	
	AocLoopFile(file, parser, line)
	{
		MyStr_t trimmedLine = line;
		TrimWhitespace(&trimmedLine);
		if (!foundEndOfStacks)
		{
			if (StrStartsWith(line, " 1"))
			{
				PrintLine_D("There are %llu stacks with a max height of %llu", numStacks, maxStackHeight);
				
				//Count how high each stack is
				for (u64 sIndex = 0; sIndex < numStacks; sIndex++)
				{
					stackHeights[sIndex] = 0;
					for (u64 hIndex = 0; hIndex < maxStackHeight; hIndex++)
					{
						if (stacks[sIndex][maxStackHeight-1 - hIndex] != '\0') { stackHeights[sIndex]++; }
						else { break; }
					}
				}
				
				//Reverse the order of each stack in memory so we can stack higher than maxStackHeight
				for (u64 sIndex = 0; sIndex < numStacks; sIndex++)
				{
					for (u64 hIndex = 0; hIndex < maxStackHeight/2; hIndex++)
					{
						SWAP_VARIABLES(char, stacks[sIndex][hIndex], stacks[sIndex][maxStackHeight-1 - hIndex]);
					}
				}
				
				PrintLine_D("There are %llu crates total in %llu stacks:", totalNumCrates, numStacks);
				for (u64 sIndex = 0; sIndex < numStacks; sIndex++)
				{
					Print_D("[%llu]: ", stackHeights[sIndex]);
					for (u64 hIndex = 0; hIndex < stackHeights[sIndex]; hIndex++)
					{
						Print_D("%s%c", (hIndex > 0) ? ", " : "", stacks[sIndex][hIndex]);
					}
					WriteLine_D("");
				}
				foundEndOfStacks = true;
			}
			else
			{
				Assert(maxStackHeight+1 < MAX_STACK_HEIGHT);
				for (u64 cIndex = 0; cIndex < line.length; cIndex++)
				{
					char c = line.chars[cIndex];
					if (c == '[' || c == ']' || c == ' ') { continue; }
					Assert((cIndex-1) % 4 == 0);
					u64 column = ((cIndex-1) / 4);
					stacks[column][maxStackHeight] = c;
					totalNumCrates++;
					if (numStacks < column+1) { numStacks = column+1; }
				}
				maxStackHeight++;
			}
		}
		else if (!IsEmptyStr(trimmedLine))
		{
			u64 numLinePieces = 0;
			MyStr_t* linePieces = SplitString(TempArena, trimmedLine, " ", &numLinePieces);
			Assert(numLinePieces == 6);
			u64 numBoxesToMove = 0; bool parsedNumBoxesToMove = TryParseU64(linePieces[1], &numBoxesToMove); Assert(parsedNumBoxesToMove);
			u64 fromStackIndex = 0; bool parsedFromStackIndex = TryParseU64(linePieces[3], &fromStackIndex); Assert(parsedFromStackIndex);
			u64 toStackIndex   = 0; bool parsedToStackIndex   = TryParseU64(linePieces[5], &toStackIndex);   Assert(parsedToStackIndex);
			fromStackIndex--;
			toStackIndex--;
			// PrintLine_D("Moving %llu boxes from stack[%llu] to stack[%llu]", numBoxesToMove, fromStackIndex, toStackIndex);
			numMoves++;
			
			Assert(fromStackIndex != toStackIndex);
			Assert(fromStackIndex < numStacks);
			Assert(toStackIndex < numStacks);
			Assert(numBoxesToMove <= stackHeights[fromStackIndex]);
			Assert(stackHeights[toStackIndex] + numBoxesToMove <= MAX_STACK_HEIGHT);
			if (doSolutionB)
			{
				for (u64 mIndex = 0; mIndex < numBoxesToMove; mIndex++)
				{
					char crate = stacks[fromStackIndex][(stackHeights[fromStackIndex] - numBoxesToMove) + mIndex];
					stacks[toStackIndex][stackHeights[toStackIndex] + mIndex] = crate;
				}
				stackHeights[fromStackIndex] -= numBoxesToMove;
				stackHeights[toStackIndex] += numBoxesToMove;
			}
			else
			{
				for (u64 mIndex = 0; mIndex < numBoxesToMove; mIndex++)
				{
					char crate = stacks[fromStackIndex][stackHeights[fromStackIndex]-1];
					stackHeights[fromStackIndex]--;
					stacks[toStackIndex][stackHeights[toStackIndex]] = crate;
					stackHeights[toStackIndex]++;
				}
			}
		}
	}
	AocCloseFile(file);
	
	PrintLine_D("End Result after %llu moves:", numMoves);
	for (u64 sIndex = 0; sIndex < numStacks; sIndex++)
	{
		Print_D("[%llu]: ", stackHeights[sIndex]);
		for (u64 hIndex = 0; hIndex < stackHeights[sIndex]; hIndex++)
		{
			Print_D("%s%c", (hIndex > 0) ? ", " : "", stacks[sIndex][hIndex]);
		}
		WriteLine_D("");
	}
	
	char* resultBuffer = TempArray(char, numStacks+1);
	for (u64 sIndex = 0; sIndex < numStacks; sIndex++)
	{
		resultBuffer[sIndex] = stacks[sIndex][stackHeights[sIndex]-1];
	}
	resultBuffer[numStacks] = '\0';
	return NewStr(resultBuffer);
}

// +==============================+
// |            Day 06            |
// +==============================+
bool IsSequenceAllUnique(u64 numChars, char* charPntr)
{
	for (u64 cIndex = 0; cIndex < numChars; cIndex++)
	{
		for (u64 cIndex2 = cIndex+1; cIndex2 < numChars; cIndex2++)
		{
			if (charPntr[cIndex] == charPntr[cIndex2]) { return false; }
		}
	}
	return true;
}
MyStr_t AocSolutionFunc_2022_06(AocSolutionStruct_2022_06_t* data, bool doSolutionB)
{
	AocOpenFile(file, "input_2022_06.txt");
	// AocOpenFile(file, "input_2022_06_ex.txt");
	
	u64 result = 0;
	AocLoopFile(file, parser, line)
	{
		u64 markerLength = (doSolutionB ? 14 : 4);
		for (u64 cIndex = 0; cIndex+markerLength <= line.length; cIndex++)
		{
			if (IsSequenceAllUnique(markerLength, line.chars + cIndex))
			{
				PrintLine_D("Start of %s at %llu/%llu \"%.*s\"", (doSolutionB ? "Message" : "Sequence"), cIndex, line.length, markerLength, &line.chars[cIndex]);
				result = cIndex + markerLength;
				break;
			}
		}
	}
	AocCloseFile(file);
	
	AocReturnU64(result);
}

// +==============================+
// |            Day 07            |
// +==============================+
enum Aoc2022_07_Command_t
{
	Aoc2022_07_Command_Cd = 0,
	Aoc2022_07_Command_Ls,
	Aoc2022_07_Command_Dir,
	Aoc2022_07_Command_NumCommands,
};
const char* GetCommandStr(Aoc2022_07_Command_t enumValue)
{
	switch (enumValue)
	{
		case Aoc2022_07_Command_Cd:  return "Cd";
		case Aoc2022_07_Command_Ls:  return "Ls";
		case Aoc2022_07_Command_Dir: return "Dir";
		default: return "Unknown";
	}
}
struct Aoc2022_07_Directory_t
{
	MyStr_t name;
	VarArray_t children;
	u64 contentsSize;
};
Aoc2022_07_Directory_t* Aoc2022_07_GetDirectory(Aoc2022_07_Directory_t* root, MyStr_t path)
{
	TempPushMark();
	if (StrStartsWith(path, "/")) { path.pntr++; path.length--; }
	u64 numPieces = 0;
	MyStr_t* pieces = SplitString(TempArena, path, "/", &numPieces);
	Aoc2022_07_Directory_t* dir = root;
	for (u64 pIndex = 0; pIndex < numPieces; pIndex++)
	{
		if (IsEmptyStr(pieces[pIndex])) { continue; }
		
		bool foundDir = false;
		for (u64 cIndex = 0; cIndex < dir->children.length; cIndex++)
		{
			Aoc2022_07_Directory_t* child = VarArrayGet(&dir->children, cIndex, Aoc2022_07_Directory_t);
			if (StrEqualsIgnoreCase(child->name, pieces[pIndex]))
			{
				dir = child;
				foundDir = true;
				break;
			}
		}
		
		if (!foundDir)
		{
			if (pieces[pIndex].length == 1) { MyDebugBreak(); }
			
			PrintLine_D("Creating \"%.*s\" in \"%.*s\" for \"%.*s\"",
				pieces[pIndex].length, pieces[pIndex].pntr,
				dir->name.length, dir->name.pntr,
				path.length, path.pntr
			);
			Aoc2022_07_Directory_t* newDir = VarArrayAdd(&dir->children, Aoc2022_07_Directory_t);
			ClearPointer(newDir);
			newDir->name = AllocString(aocArena, &pieces[pIndex]);
			CreateVarArray(&newDir->children, aocArena, sizeof(Aoc2022_07_Directory_t));
			newDir->contentsSize = 0;
			dir = newDir;
		}
	}
	TempPopMark();
	return dir;
}
Aoc2022_07_Command_t Aoc2022_07_GetCommand(MyStr_t str)
{
	for (u64 eIndex = 0; eIndex < Aoc2022_07_Command_NumCommands; eIndex++)
	{
		if (StrEqualsIgnoreCase(NewStr(GetCommandStr((Aoc2022_07_Command_t)eIndex)), str))
		{
			return (Aoc2022_07_Command_t)eIndex;
		}
	}
	return Aoc2022_07_Command_NumCommands;
}
#define AOC_2022_07_NEEDED_SPACE 8381165
u64 Aoc2022_07_WalkDirectories(Aoc2022_07_Directory_t* base, MyStr_t basePath, u64* resultOut, bool doSolutionB)
{
	MyStr_t path = TempPrintStr("%.*s%.*s%s", basePath.length, basePath.pntr, base->name.length, base->name.pntr, (basePath.length == 0 ? "" : "/"));
	PrintLine_D("Walking \"%.*s\" (%llu)", path.length, path.pntr, base->contentsSize);
	u64 dirSize = base->contentsSize;
	VarArrayLoop(&base->children, cIndex)
	{
		VarArrayLoopGet(Aoc2022_07_Directory_t, child, &base->children, cIndex);
		dirSize += Aoc2022_07_WalkDirectories(child, path, resultOut, doSolutionB);
	}
	if (doSolutionB)
	{
		if (dirSize >= AOC_2022_07_NEEDED_SPACE && (*resultOut == 0 || dirSize < *resultOut))
		{
			*resultOut = dirSize;
		}
	}
	else
	{
		if (dirSize <= 100000)
		{
			*resultOut = *resultOut + dirSize;
			PrintLine_D("Adding \"%.*s\" %llu", base->name.length, base->name.pntr, base->contentsSize);
		}
	}
	return dirSize;
}
MyStr_t AocSolutionFunc_2022_07(AocSolutionStruct_2022_07_t* data, bool doSolutionB)
{
	AocOpenFile(file, "input_2022_07.txt");
	// AocOpenFile(file, "input_2022_07_ex.txt");
	
	MyStr_t currentDirStr = MyStr_Empty;
	u64 currentDirSize = 0;
	
	Aoc2022_07_Directory_t parentDir = {};
	CreateVarArray(&parentDir.children, aocArena, sizeof(Aoc2022_07_Directory_t));
	parentDir.name = NewStr("/");
	Aoc2022_07_Directory_t* currentDir = &parentDir;
	
	u64 result = 0;
	AocLoopFile(file, parser, line)
	{
		TempPushMark();
		u64 numPieces = 0;
		MyStr_t* pieces = SplitString(TempArena, line, NewStr(" "), &numPieces);
		if (StrEquals(pieces[0], "$"))
		{
			PrintLine_D("Executing \"%.*s\"", line.length, line.pntr);
			Aoc2022_07_Command_t command = Aoc2022_07_GetCommand(pieces[1]);
			if (command == Aoc2022_07_Command_Cd)
			{
				if (StrEqualsIgnoreCase(pieces[2], ".."))
				{
					u64 lastIndexOfSlash = currentDirStr.length;
					for (u64 cIndex = 0; cIndex < currentDirStr.length; cIndex++)
					{
						if (currentDirStr.chars[cIndex] == '/') { lastIndexOfSlash = cIndex; }
					}
					currentDirStr = StrSubstring(&currentDirStr, 0, lastIndexOfSlash);
				}
				else if (StrEqualsIgnoreCase(pieces[2], "/"))
				{
					currentDirStr = AllocString(aocArena, &pieces[2]);
				}
				else
				{
					currentDirStr = PrintInArenaStr(aocArena, "%.*s%.*s/", currentDirStr.length, currentDirStr.pntr, pieces[2].length, pieces[2].pntr);
				}
				
				// PrintLine_D("In \"%.*s\"", currentDirStr.length, currentDirStr.pntr);
				currentDir = Aoc2022_07_GetDirectory(&parentDir, currentDirStr);
			}
			else if (command == Aoc2022_07_Command_Ls)
			{
				//do nothing
			}
		}
		else
		{
			u64 fileSize = 0;
			bool parsed = TryParseU64(pieces[0], &fileSize);
			if (parsed)
			{
				currentDir->contentsSize += fileSize;
			}
		}
		TempPopMark();
	}
	AocCloseFile(file);
	
	Aoc2022_07_WalkDirectories(&parentDir, MyStr_Empty, &result, doSolutionB);
	
	AocReturnU64(result);
}

// +==============================+
// |            Day 08            |
// +==============================+
MyStr_t AocSolutionFunc_2022_08(AocSolutionStruct_2022_08_t* data, bool doSolutionB)
{
	AocOpenFile(file, "input_2022_08.txt");
	// AocOpenFile(file, "input_2022_08_ex.txt");
	
	#define MAX_NUM_COLUMNS 100
	#define MAX_NUM_ROWS 100
	u64 numColumns = 0;
	u64 numRows = 0;
	u64 treeHeights[MAX_NUM_COLUMNS][MAX_NUM_ROWS];
	
	u64 result = 0;
	AocLoopFile(file, parser, line)
	{
		if (numColumns == 0) { numColumns = line.length; }
		for (u64 cIndex = 0; cIndex < line.length; cIndex++)
		{
			treeHeights[cIndex][numRows] = (u64)(line.chars[cIndex] - '0');
		}
		numRows++;
	}
	AocCloseFile(file);
	
	if (doSolutionB)
	{
		i64 foundTreeViewValue = -1;
		v2i foundTreePos = NewVec2i(-1, -1);
		
		for (u64 yIndex = 0; yIndex < numRows; yIndex++)
		{
			for (u64 xIndex = 0; xIndex < numColumns; xIndex++)
			{
				u64 treeHeight = treeHeights[xIndex][yIndex];
				u64 maxTreeLeft = 0;
				u64 maxTreeRight = 0;
				u64 maxTreeUp = 0;
				u64 maxTreeDown = 0;
				u64 numTreesLeft = 0;
				u64 numTreesRight = 0;
				u64 numTreesUp = 0;
				u64 numTreesDown = 0;
				for (u64 offset = 1; offset < MaxU64(numRows, numColumns); offset++)
				{
					v2i treeLeftPos = NewVec2i((i32)xIndex - (i32)offset, (i32)yIndex);
					v2i treeRightPos = NewVec2i((i32)xIndex + (i32)offset, (i32)yIndex);
					v2i treeUpPos = NewVec2i((i32)xIndex, (i32)yIndex - (i32)offset);
					v2i treeDownPos = NewVec2i((i32)xIndex, (i32)yIndex + (i32)offset);
					if (treeLeftPos.x >= 0          && maxTreeLeft  < treeHeight) { numTreesLeft++;  }
					if (treeRightPos.x < numColumns && maxTreeRight < treeHeight) { numTreesRight++; }
					if (treeUpPos.y >= 0            && maxTreeUp    < treeHeight) { numTreesUp++;    }
					if (treeDownPos.y < numRows     && maxTreeDown  < treeHeight) { numTreesDown++;  }
					if (treeLeftPos.x >= 0)          { maxTreeLeft  = MaxU64(maxTreeLeft,  treeHeights[treeLeftPos.x][treeLeftPos.y]);   }
					if (treeRightPos.x < numColumns) { maxTreeRight = MaxU64(maxTreeRight, treeHeights[treeRightPos.x][treeRightPos.y]); }
					if (treeUpPos.y >= 0)            { maxTreeUp    = MaxU64(maxTreeUp,    treeHeights[treeUpPos.x][treeUpPos.y]);       }
					if (treeDownPos.y < numRows)     { maxTreeDown  = MaxU64(maxTreeDown,  treeHeights[treeDownPos.x][treeDownPos.y]);   }
				}
				
				u64 viewValue = numTreesLeft * numTreesRight * numTreesUp * numTreesDown;
				if (foundTreeViewValue < 0 || viewValue > (u64)foundTreeViewValue)
				{
					PrintLine_D("(%llu, %llu) with height %llu has view %llu (%llu left %llu right %llu up %llu down)", xIndex, yIndex, treeHeight, viewValue, numTreesLeft, numTreesRight, numTreesUp, numTreesDown);
					foundTreeViewValue = (i64)viewValue;
					foundTreePos = NewVec2i((i32)xIndex, (i32)yIndex);
				}
			}
		}
		
		PrintLine_D("They should build their tree at (%d, %d) with %llu trees visible", foundTreePos.x, foundTreePos.y, foundTreeViewValue);
		result = (u64)foundTreeViewValue;
	}
	else
	{
		char treeIsVisible[MAX_NUM_COLUMNS][MAX_NUM_ROWS];
		MyMemSet(&treeIsVisible[0][0], 0x00, sizeof(char) * MAX_NUM_COLUMNS * MAX_NUM_ROWS);
		
		// for (u64 yIndex = 0; yIndex < numRows; yIndex++)
		// {
		// 	for (u64 xIndex = 0; xIndex < numColumns; xIndex++)
		// 	{
		// 		Print_D("%llu ", treeHeights[xIndex][yIndex]);
		// 	}
		// 	WriteLine_D("");
		// }
		
		for (u64 majorIndex = 0; majorIndex < MaxU64(numColumns, numRows); majorIndex++)
		{
			i64 leftMaxFound = -1;
			i64 rightMaxFound = -1;
			i64 topMaxFound = -1;
			i64 bottomMaxFound = -1;
			for (u64 minorIndex = 0; minorIndex < MaxU64(numColumns, numRows); minorIndex++)
			{
				if (majorIndex < numRows && minorIndex < numColumns)
				{
					u64 nextLeftHeight = treeHeights[minorIndex][majorIndex];
					u64 nextRightHeight = treeHeights[numColumns-1 - minorIndex][majorIndex];
					// PrintLine_D("L at (%llu, %llu) at %d and R at (%llu, %llu) at %d", minorIndex, majorIndex, leftMaxFound, numColumns-1 - minorIndex, majorIndex, rightMaxFound);
					if (leftMaxFound < 0 || nextLeftHeight > (u64)leftMaxFound)
					{
						leftMaxFound = (i64)nextLeftHeight;
						if (treeIsVisible[minorIndex][majorIndex] == '\0') { result++; treeIsVisible[minorIndex][majorIndex] = 'L'; /*PrintLine_D("L +1=%llu", result);*/ }
					}
					if (rightMaxFound < 0 || nextRightHeight > (u64)rightMaxFound)
					{
						rightMaxFound = (i64)nextRightHeight;
						if (treeIsVisible[numColumns-1 - minorIndex][majorIndex] == '\0') { result++; treeIsVisible[numColumns-1 - minorIndex][majorIndex] = 'R'; /*PrintLine_D("R +1=%llu", result);*/ }
					}
				}
				if (majorIndex < numColumns && minorIndex < numRows)
				{
					u64 nextTopHeight = treeHeights[majorIndex][minorIndex];
					u64 nextBottomHeight = treeHeights[majorIndex][numRows-1 - minorIndex];
					// PrintLine_D("T at (%llu, %llu) at %d and B at (%llu, %llu) at %d", majorIndex, minorIndex, topMaxFound, majorIndex, numRows-1 - minorIndex, bottomMaxFound);
					if (topMaxFound < 0 || nextTopHeight > (u64)topMaxFound)
					{
						topMaxFound = (i64)nextTopHeight;
						if (treeIsVisible[majorIndex][minorIndex] == '\0') { result++; treeIsVisible[majorIndex][minorIndex] = 'T'; /*PrintLine_D("T +1=%llu", result);*/ }
					}
					if (bottomMaxFound < 0 || nextBottomHeight > (u64)bottomMaxFound)
					{
						bottomMaxFound = (i64)nextBottomHeight;
						if (treeIsVisible[majorIndex][numRows-1 - minorIndex] == '\0') { result++; treeIsVisible[majorIndex][numRows-1 - minorIndex] = 'B'; /*PrintLine_D("B +1=%llu", result);*/ }
					}
				}
			}
		}
				
		// PrintLine_D("(%llu, %llu)", numColumns, numRows);
		// for (u64 yIndex = 0; yIndex < numRows; yIndex++)
		// {
		// 	for (u64 xIndex = 0; xIndex < numColumns; xIndex++)
		// 	{
		// 		Print_D("%c", treeIsVisible[xIndex][yIndex] ? treeIsVisible[xIndex][yIndex] : '.');
		// 	}
		// 	WriteLine_D("");
		// }
	}
	
	AocReturnU64(result);
}

// +==============================+
// |            Day 09            |
// +==============================+
MyStr_t AocSolutionFunc_2022_09(AocSolutionStruct_2022_09_t* data, bool doSolutionB)
{
	AocOpenFile(file, "input_2022_09.txt");
	// AocOpenFile(file, "input_2022_09_ex.txt");
	
	#define AOC2022_09_GRID_WIDTH 1000
	#define AOC2022_09_GRID_HEIGHT 1000
	bool visited[AOC2022_09_GRID_WIDTH][AOC2022_09_GRID_HEIGHT];
	MyMemSet(&visited[0][0], 0x00, sizeof(bool) * AOC2022_09_GRID_WIDTH * AOC2022_09_GRID_HEIGHT);
	
	u64 numTails = (doSolutionB ? 9 : 1);
	u64 lastTail = (numTails - 1);
	#define AOC2022_09_MAX_NUM_TAILS 9
	v2i headPos = NewVec2i((i32)AOC2022_09_GRID_WIDTH/2, (i32)AOC2022_09_GRID_HEIGHT/2);
	v2i tailPos[AOC2022_09_MAX_NUM_TAILS];
	for (u64 tIndex = 0; tIndex < numTails; tIndex++)
	{
		tailPos[tIndex] = headPos;
	}
	visited[tailPos[lastTail].x][tailPos[lastTail].y] = true;
	reci visitedRec = NewReci(tailPos[lastTail].x, tailPos[lastTail].y, 1, 1);
	u64 result = 1;
	AocLoopFile(file, parser, line)
	{
		u64 spaceIndex = 0;
		FindSubstring(line, " ", &spaceIndex);
		MyStr_t dirStr = StrSubstring(&line, 0, spaceIndex);
		MyStr_t amountStr = StrSubstring(&line, spaceIndex+1);
		Dir2_t dir = Dir2_None;
		if (StrEqualsIgnoreCase(dirStr, "R")) { dir = Dir2_Right; }
		else if (StrEqualsIgnoreCase(dirStr, "L")) { dir = Dir2_Left; }
		else if (StrEqualsIgnoreCase(dirStr, "U")) { dir = Dir2_Up; }
		else if (StrEqualsIgnoreCase(dirStr, "D")) { dir = Dir2_Down; }
		v2i dirVec = ToVec2i(dir);
		u64 amount = 0;
		TryParseU64(amountStr, &amount);
		
		// PrintLine_D("Moving %s %llu", GetDir2String(dir), amount);
		for (u64 aIndex = 0; aIndex < amount; aIndex++)
		{
			headPos += dirVec;
			for (u64 tIndex = 0; tIndex < numTails; tIndex++)
			{
				v2i nextPos = (tIndex == 0) ? headPos : tailPos[tIndex-1];
				if (nextPos.x >= tailPos[tIndex].x + 2)
				{
					tailPos[tIndex].x++;
					if (nextPos.y != tailPos[tIndex].y) { tailPos[tIndex].y += SignOfI32(nextPos.y - tailPos[tIndex].y); }
				}
				else if (nextPos.x <= tailPos[tIndex].x - 2)
				{
					tailPos[tIndex].x--;
					if (nextPos.y != tailPos[tIndex].y) { tailPos[tIndex].y += SignOfI32(nextPos.y - tailPos[tIndex].y); }
				}
				else if (nextPos.y >= tailPos[tIndex].y + 2)
				{
					tailPos[tIndex].y++;
					if (nextPos.x != tailPos[tIndex].x) { tailPos[tIndex].x += SignOfI32(nextPos.x - tailPos[tIndex].x); }
				}
				else if (nextPos.y <= tailPos[tIndex].y - 2)
				{
					tailPos[tIndex].y--;
					if (nextPos.x != tailPos[tIndex].x) { tailPos[tIndex].x += SignOfI32(nextPos.x - tailPos[tIndex].x); }
				}
				Assert(tailPos[tIndex].x >= 0 && tailPos[tIndex].y >= 0);
				Assert(tailPos[tIndex].x < AOC2022_09_GRID_WIDTH && tailPos[tIndex].y < AOC2022_09_GRID_HEIGHT);
				if (tIndex == lastTail && !visited[tailPos[tIndex].x][tailPos[tIndex].y])
				{
					visited[tailPos[tIndex].x][tailPos[tIndex].y] = true;
					visitedRec = ReciExpandToVec2i(visitedRec, tailPos[tIndex]);
					result++;
				}
			}
		}
	}
	AocCloseFile(file);
	
	PrintLine_D("Covered an area %dx%d at offset (%d, %d)", visitedRec.width, visitedRec.height, visitedRec.x, visitedRec.y);
	#if 0
	for (u64 yIndex = visitedRec.y; yIndex < visitedRec.y + visitedRec.height; yIndex++)
	{
		for (u64 xIndex = visitedRec.x; xIndex < visitedRec.x + visitedRec.width; xIndex++)
		{
			bool visitedValue = visited[xIndex][yIndex];
			Print_D("%s", visitedValue ? "#" : ".");
		}
		WriteLine_D("");
	}
	#endif
	
	AocReturnU64(result);
}

// +==============================+
// |            Day 10            |
// +==============================+
#define CRT_WIDTH 40
#define CRT_HEIGHT 6
void RunCycle(bool doSolutionB, i64* result, char* crtDisplay, u64* cycle, i64 xReg)
{
	if (doSolutionB)
	{
		v2i crtPos = NewVec2i((i32)(((*cycle) - 1) % CRT_WIDTH), (i32)(((*cycle) - 1) / CRT_WIDTH));
		char* crtChar = &crtDisplay[(crtPos.y * CRT_WIDTH) + crtPos.x];
		bool isPixelFilled = ((xReg-1) <= crtPos.x && (xReg-1) > crtPos.x - 3);
		// PrintLine_D("Pos (%d, %d) is %s", crtPos.x, crtPos.y, isPixelFilled ? "Filled" : "Empty");
		*crtChar = (isPixelFilled ? '#' : '.');
	}
	else
	{
		if ((*cycle) >= 20 && ((*cycle) - 20) % 40 == 0)
		{
			PrintLine_I("Measuring: %lld + (%llu * %lld) or %lld = %lld", *result, xReg, *cycle, (*cycle) * xReg, (*result) + ((*cycle) * xReg));
			*result += ((*cycle) * xReg);
		}
	}
	*cycle += 1;
}
MyStr_t AocSolutionFunc_2022_10(AocSolutionStruct_2022_10_t* data, bool doSolutionB)
{
	AocOpenFile(file, "input_2022_10.txt");
	// AocOpenFile(file, "input_2022_10_ex.txt");
	
	char crtDisplay[CRT_WIDTH * CRT_HEIGHT];
	MyMemSet(&crtDisplay[0], '-', sizeof(char) * CRT_WIDTH * CRT_HEIGHT);
	
	i64 result = 0;
	u64 cycle = 1;
	i64 xReg = 1;
	AocLoopFile(file, parser, line)
	{
		if (StrStartsWith(line, "addx "))
		{
			i64 addValue = 0;
			TryParseI64(StrSubstring(&line, 5), &addValue);
			// PrintLine_D("%lld+%lld [%llu, %llu] -> %lld", xReg, addValue, cycle, cycle+2, xReg + addValue);
			RunCycle(doSolutionB, &result, &crtDisplay[0], &cycle, xReg);
			RunCycle(doSolutionB, &result, &crtDisplay[0], &cycle, xReg);
			xReg += addValue;
		}
		else if (StrStartsWith(line, "noop"))
		{
			// PrintLine_D("Noop on cycle %llu", cycle);
			RunCycle(doSolutionB, &result, &crtDisplay[0], &cycle, xReg);
		}
		else { PrintLine_E("Invalid line \"%.*s\"", line.length, line.pntr); }
	}
	AocCloseFile(file);
	
	if (doSolutionB)
	{
		PrintLine_D("Ended on cycle %llu:", cycle);
		for (u64 yIndex = 0; yIndex < CRT_HEIGHT; yIndex++)
		{
			for (u64 xIndex = 0; xIndex < CRT_WIDTH; xIndex++)
			{
				Print_D("%c", crtDisplay[(yIndex * CRT_WIDTH) + xIndex]);
			}
			WriteLine_D("");
		}
	}
	
	AocReturnU64(result);
}

// +==============================+
// |            Day 11            |
// +==============================+
#define MAX_NUM_MONKEYS 8
#define MAX_NUM_ITEMS   200 
#define OP_VALUE_OLD    0

struct Item_t
{
	u64 id;
	u64 worryLevel;
};
enum OpType_t
{
	OpType_Add = 0,
	OpType_Subtract,
	OpType_Multiply,
	OpType_NumTypes,
};
const char* GetOpTypeStr(OpType_t enumValue)
{
	switch (enumValue)
	{
		case OpType_Add:      return "Add";
		case OpType_Subtract: return "Subtract";
		case OpType_Multiply: return "Multiply";
		default: return "Unknown";
	}
}
const char GetOpTypeChar(OpType_t enumValue)
{
	switch (enumValue)
	{
		case OpType_Add:      return '+';
		case OpType_Subtract: return '-';
		case OpType_Multiply: return '*';
		default: return '?';
	}
}
OpType_t GetOpTypeByChar(char c)
{
	for (u64 oIndex = 0; oIndex < OpType_NumTypes; oIndex++)
	{
		OpType_t opType = (OpType_t)oIndex;
		if (c == GetOpTypeChar(opType)) { return opType; }
	}
	return OpType_NumTypes;
}
struct Monkey_t
{
	u64 id;
	
	u64 numInspections;
	
	OpType_t opType;
	u64 opValue;
	
	u64 testDivisor;
	u64 testTrueTarget;
	u64 testFalseTarget;
	
	u64 numItems;
	Item_t items[MAX_NUM_ITEMS];
};
void PrintMonkeyStates(u64 numMonkeys, Monkey_t* monkeys)
{
	for (u64 mIndex = 0; mIndex < numMonkeys; mIndex++)
	{
		Monkey_t* monkey = &monkeys[mIndex];
		Print_D("Monkey %llu: [%llu] { ", monkey->id, monkey->numItems);
		for (u64 iIndex = 0; iIndex < monkey->numItems; iIndex++)
		{
			Item_t* item = &monkey->items[iIndex];
			Print_D("%s%llu(%c)", iIndex > 0 ? ", " : "", item->worryLevel, (char)('A' + item->id));
		}
		WriteLine_D(" }");
	}
}
void SimulateMonkeys(bool doSolutionB, bool debugOutput, u64 allDivisorsMult, u64 numMonkeys, Monkey_t* monkeys)
{
	for (u64 mIndex = 0; mIndex < numMonkeys; mIndex++)
	{
		Monkey_t* monkey = &monkeys[mIndex];
		if (debugOutput) { PrintLine_D("Simulating Monkey %llu", monkey->id); }
		for (u64 iIndex = 0; monkey->numItems > 0; iIndex++)
		{
			Item_t* item = &monkey->items[iIndex];
			if (debugOutput) { PrintLine_D("  Looking at item %c at %llu worry", (char)('A' + item->id), item->worryLevel); }
			u64 opValue = monkey->opValue;
			if (opValue == OP_VALUE_OLD) { opValue = item->worryLevel; }
			switch (monkey->opType)
			{
				case OpType_Add:      item->worryLevel += opValue; if (debugOutput) { PrintLine_D("    Adding %llu", opValue);         } break;
				case OpType_Subtract: item->worryLevel -= opValue; if (debugOutput) { PrintLine_D("    Subtracting %llu", opValue);    } break;
				case OpType_Multiply: item->worryLevel *= opValue; if (debugOutput) { PrintLine_D("    Multiplying by %llu", opValue); } break;
			}
			item->worryLevel = (item->worryLevel % allDivisorsMult);
			if (debugOutput) { PrintLine_D("    Worry is now %llu", item->worryLevel); }
			if (!doSolutionB)
			{
				item->worryLevel = (u64)FloorR64i((r64)item->worryLevel / 3);
				item->worryLevel = (item->worryLevel % allDivisorsMult);
				if (debugOutput) { PrintLine_D("    Dropped to %llu", item->worryLevel); }
			}
			
			Monkey_t* targetMonkey = nullptr;
			if ((item->worryLevel % monkey->testDivisor) == 0)
			{
				Assert(monkey->testTrueTarget < numMonkeys);
				Assert(monkey->testTrueTarget != monkey->id);
				targetMonkey = &monkeys[monkey->testTrueTarget];
				if (debugOutput) { PrintLine_D("    Throwing to monkey %llu because %llu IS divisable by %llu", monkey->testTrueTarget, item->worryLevel, monkey->testDivisor); }
			}
			else
			{
				Assert(monkey->testFalseTarget < numMonkeys);
				Assert(monkey->testFalseTarget != monkey->id);
				targetMonkey = &monkeys[monkey->testFalseTarget];
				if (debugOutput) { PrintLine_D("    Throwing to monkey %llu because %llu IS NOT divisable by %llu", monkey->testFalseTarget, item->worryLevel, monkey->testDivisor); }
			}
			
			Assert(targetMonkey->numItems < MAX_NUM_ITEMS);
			Item_t* targetSlot = &targetMonkey->items[targetMonkey->numItems];
			MyMemCopy(targetSlot, item, sizeof(Item_t));
			targetMonkey->numItems++;
			monkey->numItems--;
			
			monkey->numInspections++;
		}
	}
}
MyStr_t AocSolutionFunc_2022_11(AocSolutionStruct_2022_11_t* data, bool doSolutionB)
{
	AocOpenFile(file, "input_2022_11.txt");
	// AocOpenFile(file, "input_2022_11_ex.txt");
	
	u64 numMonkeys = 0;
	Monkey_t monkeys[MAX_NUM_MONKEYS];
	
	Monkey_t* currentMonkey = nullptr;
	u64 nextItemId = 1;
	u64 allDivisorsMult = 1;
	AocLoopFile(file, parser, line)
	{
		TrimWhitespace(&line);
		if (IsEmptyStr(line)) { continue; }
		
		if (StrStartsWith(line, "Monkey"))
		{
			Assert(numMonkeys < MAX_NUM_MONKEYS);
			currentMonkey = &monkeys[numMonkeys];
			ClearPointer(currentMonkey);
			currentMonkey->id = numMonkeys;
			numMonkeys++;
		}
		else if (StrStartsWith(line, "Starting items: "))
		{
			NotNull(currentMonkey);
			MyStr_t itemsStr = StrSubstring(&line, 16);
			TempPushMark();
			u64 numPieces = 0;
			MyStr_t* pieces = SplitString(TempArena, itemsStr, ",", &numPieces);
			for (u64 pIndex = 0; pIndex < numPieces; pIndex++)
			{
				Assert(currentMonkey->numItems < MAX_NUM_ITEMS);
				Item_t* newItem = &currentMonkey->items[currentMonkey->numItems];
				ClearPointer(newItem);
				newItem->id = nextItemId;
				nextItemId++;
				bool parseSuccess = TryParseU64(pieces[pIndex], &newItem->worryLevel);
				Assert(parseSuccess);
				currentMonkey->numItems++;
			}
			TempPopMark();
		}
		else if (StrStartsWith(line, "Operation: new = old "))
		{
			NotNull(currentMonkey);
			
			char opTypeChar = line.chars[21];
			currentMonkey->opType = GetOpTypeByChar(opTypeChar);
			
			MyStr_t opValueStr = StrSubstring(&line, 23);
			if (StrEqualsIgnoreCase(opValueStr, "old"))
			{
				currentMonkey->opValue = OP_VALUE_OLD;
			}
			else
			{
				bool parseSuccess = TryParseU64(opValueStr, &currentMonkey->opValue);
				Assert(parseSuccess);
			}
		}
		else if (StrStartsWith(line, "Test: divisible by "))
		{
			NotNull(currentMonkey);
			MyStr_t divisorStr = StrSubstring(&line, 19);
			bool parseSuccess = TryParseU64(divisorStr, &currentMonkey->testDivisor);
			Assert(parseSuccess);
			allDivisorsMult *= currentMonkey->testDivisor;
		}
		else if (StrStartsWith(line, "If true: throw to monkey "))
		{
			NotNull(currentMonkey);
			MyStr_t targetNumStr = StrSubstring(&line, 25);
			bool parseSuccess = TryParseU64(targetNumStr, &currentMonkey->testTrueTarget);
			Assert(parseSuccess);
		}
		else if (StrStartsWith(line, "If false: throw to monkey "))
		{
			NotNull(currentMonkey);
			MyStr_t targetNumStr = StrSubstring(&line, 26);
			bool parseSuccess = TryParseU64(targetNumStr, &currentMonkey->testFalseTarget);
			Assert(parseSuccess);
		}
		else { PrintLine_E("Unhandled line \"%.*s\"", line.length, line.pntr); }
	}
	AocCloseFile(file);
	
	PrintLine_I("Found %llu monkeys", numMonkeys);
	for (u64 mIndex = 0; mIndex < numMonkeys; mIndex++)
	{
		Monkey_t* monkey = &monkeys[mIndex];
		PrintLine_D("Monkey[%llu] has %llu items and does %s %llu on inspection and checks %llu divisor and throws to %llu or %llu",
			monkey->id,
			monkey->numItems,
			GetOpTypeStr(monkey->opType),
			monkey->opValue,
			monkey->testDivisor,
			monkey->testTrueTarget,
			monkey->testFalseTarget
		);
	}
	
	PrintMonkeyStates(numMonkeys, monkeys);
	u64 numRounds = (doSolutionB ? 10000 : 20);
	if (KeyDownRaw(Key_Shift)) { numRounds = 1; } //TODO: Remove me!
	PrintLine_N("Simulating %llu rounds...", numRounds);
	for (u64 rIndex = 0; rIndex < numRounds; rIndex++)
	{
		if (rIndex > 0 && ((rIndex+1) % 500) == 0) { PrintLine_D("Round %llu...", rIndex+1); }
		SimulateMonkeys(doSolutionB, KeyDownRaw(Key_Control), allDivisorsMult, numMonkeys, monkeys);
	}
	PrintMonkeyStates(numMonkeys, monkeys);
	
	u64 maxInspections1 = 0;
	u64 maxInspections2 = 0;
	for (u64 mIndex = 0; mIndex < numMonkeys; mIndex++)
	{
		Monkey_t* monkey = &monkeys[mIndex];
		PrintLine_D("Monkey[%llu] has inspected %llu items", monkey->id, monkey->numInspections);
		if (monkey->numInspections > maxInspections1)
		{
			maxInspections2 = maxInspections1;
			maxInspections1 = monkey->numInspections;
		}
		else if (monkey->numInspections > maxInspections2)
		{
			maxInspections2 = monkey->numInspections;
		}
	}
	u64 monkeyBusiness = maxInspections1 * maxInspections2;
	PrintLine_D("Max two are %llu and %llu making %llu monkey business", maxInspections1, maxInspections2, monkeyBusiness);
	
	AocReturnU64(monkeyBusiness);
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
