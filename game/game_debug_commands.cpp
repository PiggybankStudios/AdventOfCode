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
	if (StrEqualsIgnoreCase(command, "test"))
	{
		WriteLine_D("Nothing to test right now");
	}
	
	// +==============================+
	// |     aoc [solution] {a/b}     |
	// +==============================+
	else if (StrEqualsIgnoreCase(command, "aoc"))
	{
		if (numArguments != 1 && numArguments != 2) { PrintLine_E("Expected 1-2 arguments, got %llu", numArguments); return isValidCommand; }
		if (!IsAppStateInitialized(AppState_AdventOfCode)) { WriteLine_E("This command only works when the AdventOfCode AppState is active!"); return isValidCommand; }
		
		AocSolution_t solution = AocSolution_NumSolutions;
		bool doSolutionB = false;
		if (StrEqualsIgnoreCase(arguments[0], "prev") || StrEqualsIgnoreCase(arguments[0], "previous"))
		{
			solution = aoc->prevSolution;
			doSolutionB = aoc->prevSolutionIsB;
			if (aoc->prevSolution >= AocSolution_NumSolutions) { WriteLine_E("No solution has been run yet!"); return isValidCommand; }
		}
		else
		{
			if (numArguments != 2) { WriteLine_E("Expected a second argument to choose a or b solution"); return isValidCommand; }
			
			for (u64 sIndex = 0; sIndex < AocSolution_NumSolutions; sIndex++)
			{
				AocSolution_t checkSolution = (AocSolution_t)sIndex;
				if (StrEqualsIgnoreCase(arguments[0], GetAocSolutionStr(checkSolution)))
				{
					solution = checkSolution;
					break;
				}
				else if (StrEqualsIgnoreCase(arguments[0], GetAocSolutionDisplayStr(checkSolution)))
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
			
			bool parseBoolValue = false;
			if (StrEqualsIgnoreCase(arguments[1], "a")) { doSolutionB = false; }
			else if (StrEqualsIgnoreCase(arguments[1], "b")) { doSolutionB = true; }
			else if (TryParseBool(arguments[1], &parseBoolValue)) { doSolutionB = parseBoolValue; }
			else { PrintLine_E("Invalid second argument. Should be \"a\" or \"b\" not \"%.*s\"", arguments[1].length, arguments[1].pntr); return isValidCommand; }
		}
		
		
		AocAppState_RunAocSolution(solution, doSolutionB);
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
