/*
File:   game_debug_commands.cpp
Author: Taylor Robbins
Date:   06\17\2022
Description: 
	** Holds the GameHandleDebugCommand function which is where the game is
	** able to try processing a debug command input to the console.
	** See pig_debug_commands.cpp for engine level debug commands
*/

const char* GameDebugCommandInfoStrs[] = {
	//"command", "description", "arg1", "arg2", ... "\n",
	"test", "Serves as a dedicated spot to place temporary test code", "\n",
	"aoc", "Runs a specific Advent of Code solution", "[solution]", "\n",
};
DebugCommandInfoList_t GameGetDebugCommandInfoList() //pre-declared in game_main.h
{
	return CreateDebugCommandInfoList(GameDebugCommandInfoStrs, ArrayCount(GameDebugCommandInfoStrs));
}

//Pre-declared in game_main.h
bool GameHandleDebugCommand(MyStr_t command, u64 numArguments, MyStr_t* arguments, MyStr_t fullInputStr)
{
	UNUSED(fullInputStr);
	bool isValidCommand = true;
	
	// +==============================+
	// |             test             |
	// +==============================+
	if (StrCompareIgnoreCase(command, "test") == 0)
	{
		WriteLine_D("Nothing to test right now");
	}
	
	// +==============================+
	// |        aoc [solution]        |
	// +==============================+
	else if (StrCompareIgnoreCase(command, "aoc") == 0)
	{
		if (numArguments != 1) { PrintLine_E("Expected 1 argument, got %llu", numArguments); return isValidCommand; }
		if (!IsAppStateInitialized(AppState_AdventOfCode)) { WriteLine_E("This command only works when the AdventOfCode AppState is active!"); return isValidCommand; }
		
		AocSolution_t solution = AocSolution_NumSolutions;
		if (StrCompareIgnoreCase(arguments[0], "prev") == 0 || StrCompareIgnoreCase(arguments[0], "previous") == 0)
		{
			solution = aoc->prevSolution;
			if (aoc->prevSolution >= AocSolution_NumSolutions) { WriteLine_E("No solution has been run yet!"); return isValidCommand; }
		}
		else
		{
			for (u64 sIndex = 0; sIndex < AocSolution_NumSolutions; sIndex++)
			{
				AocSolution_t checkSolution = (AocSolution_t)sIndex;
				if (StrCompareIgnoreCase(arguments[0], GetAocSolutionStr(checkSolution)) == 0)
				{
					solution = checkSolution;
					break;
				}
				else if (StrCompareIgnoreCase(arguments[0], GetAocSolutionDisplayStr(checkSolution)) == 0)
				{
					solution = checkSolution;
					break;
				}
			}
			if (solution >= AocSolution_NumSolutions)
			{
				PrintLine_E("Unknown solution name \"%.*s\"", arguments[0].length, arguments[0].pntr);
				return isValidCommand;
			}
		}
		
		AocAppState_RunAocSolution(solution);
	}
	
	// +==============================+
	// |       Unknown Command        |
	// +==============================+
	else
	{
		isValidCommand = false;
	}
	
	return isValidCommand;
}
