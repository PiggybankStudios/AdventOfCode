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
enum Command_t
{
	Command_Cd = 0,
	Command_Ls,
	Command_Dir,
	Command_NumCommands,
};
const char* GetCommandStr(Command_t enumValue)
{
	switch (enumValue)
	{
		case Command_Cd:  return "Cd";
		case Command_Ls:  return "Ls";
		case Command_Dir: return "Dir";
		default: return "Unknown";
	}
}
struct Directory_t
{
	MyStr_t name;
	VarArray_t children;
	u64 contentsSize;
};
Directory_t* GetDirectory(Directory_t* root, MyStr_t path)
{
	TempPushMark();
	if (StrStartsWith(path, "/")) { path.pntr++; path.length--; }
	u64 numPieces = 0;
	MyStr_t* pieces = SplitString(TempArena, path, "/", &numPieces);
	Directory_t* dir = root;
	for (u64 pIndex = 0; pIndex < numPieces; pIndex++)
	{
		if (IsEmptyStr(pieces[pIndex])) { continue; }
		
		bool foundDir = false;
		for (u64 cIndex = 0; cIndex < dir->children.length; cIndex++)
		{
			Directory_t* child = VarArrayGet(&dir->children, cIndex, Directory_t);
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
			Directory_t* newDir = VarArrayAdd(&dir->children, Directory_t);
			ClearPointer(newDir);
			newDir->name = AllocString(aocArena, &pieces[pIndex]);
			CreateVarArray(&newDir->children, aocArena, sizeof(Directory_t));
			newDir->contentsSize = 0;
			dir = newDir;
		}
	}
	TempPopMark();
	return dir;
}
Command_t GetCommand(MyStr_t str)
{
	for (u64 eIndex = 0; eIndex < Command_NumCommands; eIndex++)
	{
		if (StrEqualsIgnoreCase(NewStr(GetCommandStr((Command_t)eIndex)), str))
		{
			return (Command_t)eIndex;
		}
	}
	return Command_NumCommands;
}
#define NEEDED_SPACE 8381165
u64 WalkDirectories(Directory_t* base, MyStr_t basePath, u64* resultOut, bool doSolutionB)
{
	MyStr_t path = TempPrintStr("%.*s%.*s%s", basePath.length, basePath.pntr, base->name.length, base->name.pntr, (basePath.length == 0 ? "" : "/"));
	PrintLine_D("Walking \"%.*s\" (%llu)", path.length, path.pntr, base->contentsSize);
	u64 dirSize = base->contentsSize;
	VarArrayLoop(&base->children, cIndex)
	{
		VarArrayLoopGet(Directory_t, child, &base->children, cIndex);
		dirSize += WalkDirectories(child, path, resultOut, doSolutionB);
	}
	if (doSolutionB)
	{
		if (dirSize >= NEEDED_SPACE && (*resultOut == 0 || dirSize < *resultOut))
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
	
	Directory_t parentDir = {};
	CreateVarArray(&parentDir.children, aocArena, sizeof(Directory_t));
	parentDir.name = NewStr("/");
	Directory_t* currentDir = &parentDir;
	
	u64 result = 0;
	AocLoopFile(file, parser, line)
	{
		TempPushMark();
		u64 numPieces = 0;
		MyStr_t* pieces = SplitString(TempArena, line, NewStr(" "), &numPieces);
		if (StrEquals(pieces[0], "$"))
		{
			PrintLine_D("Executing \"%.*s\"", line.length, line.pntr);
			Command_t command = GetCommand(pieces[1]);
			if (command == Command_Cd)
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
				currentDir = GetDirectory(&parentDir, currentDirStr);
			}
			else if (command == Command_Ls)
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
	
	WalkDirectories(&parentDir, MyStr_Empty, &result, doSolutionB);
	
	AocReturnU64(result);
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
