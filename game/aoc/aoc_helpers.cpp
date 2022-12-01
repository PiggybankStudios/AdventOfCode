/*
File:   aoc_helpers.cpp
Author: Taylor Robbins
Date:   11\30\2022
Description: 
	** Holds functions that help us do various common tasks (like opening and parsing a file line-by-line)
	** It makes some assumptions about how aoc solutions normally work to provide very terse APIs that
	** do lots of work for us
*/

#define AocReturnI32(valueI32) return TempPrintStr("%d", valueI32)
#define AocReturnU64(valueU64) return TempPrintStr("%llu", valueU64)

// +--------------------------------------------------------------+
// |                    Enum Parsing Shorthand                    |
// +--------------------------------------------------------------+
#define AocParseEnumFunc(enumBaseName, numWhatSuffix)                              \
enumBaseName##_t Parse##enumBaseName(MyStr_t enumStr)                              \
{                                                                                  \
	for (u64 eIndex = 0; eIndex < enumBaseName##_##numWhatSuffix; eIndex++)        \
	{                                                                              \
		enumBaseName##_t enumValue = (enumBaseName##_t)eIndex;                     \
		if (StrCompareIgnoreCase(enumStr, Get##enumBaseName##Str(enumValue)) == 0) \
		{                                                                          \
			return enumValue;                                                      \
		}                                                                          \
	}                                                                              \
	return enumBaseName##_##numWhatSuffix;                                         \
}

// +--------------------------------------------------------------+
// |                    File Opening Shorthand                    |
// +--------------------------------------------------------------+
#define AocOpenFile(fileVarName, fileName)                                                                \
	PlatFileContents_t fileVarName;                                                                       \
	bool readSuccess = plat->ReadFileContents(TempPrintStr("Resources/Text/%s", fileName), &fileVarName); \
	Assert(readSuccess);

#define AocCloseFile(fileVarName) plat->FreeFileContents(&fileVarName)

#define AocLoopFile(fileVarName, lineParserVarName, lineVarName)                                   \
	LineParser_t lineParserVarName = NewLineParser(NewStr(fileVarName.length, fileVarName.chars)); \
	MyStr_t lineVarName = MyStr_Empty;                                                             \
	while (LineParserGetLine(&lineParserVarName, &lineVarName))

// +--------------------------------------------------------------+
// |                      Var Array Shothand                      |
// +--------------------------------------------------------------+
#define AocVarArrayU64(arrayVarName) VarArray_t arrayVarName; CreateVarArray(&arrayVarName, aocArena, sizeof(u64))

bool AocFindU64(VarArray_t* arrayPntr, u64 number, u64* foundIndexOut = nullptr)
{
	NotNull(arrayPntr);
	VarArrayLoop(arrayPntr, nIndex)
	{
		VarArrayLoopGet(u64, num, arrayPntr, nIndex);
		if (*num == number)
		{
			if (foundIndexOut != nullptr) { *foundIndexOut = nIndex; }
			return true;
		}
	}
	return false;
}
u64 AocFindMaxU64(VarArray_t* arrayPntr, u64* foundIndexOut = nullptr)
{
	NotNull(arrayPntr);
	if (foundIndexOut != nullptr) { *foundIndexOut = arrayPntr->length; }
	u64 maxValue = 0;
	VarArrayLoop(arrayPntr, nIndex)
	{
		VarArrayLoopGet(u64, num, arrayPntr, nIndex);
		if (nIndex == 0 || (*num > maxValue))
		{
			maxValue = *num;
			if (foundIndexOut != nullptr) { *foundIndexOut = nIndex; }
		}
	}
	return maxValue;
}
