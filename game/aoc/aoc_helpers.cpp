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
#define AocReturnI64(valueI64) return TempPrintStr("%lld", valueI64)

// +--------------------------------------------------------------+
// |                    Enum Parsing Shorthand                    |
// +--------------------------------------------------------------+
#define AocParseEnumFunc(enumBaseName, numWhatSuffix)                        \
enumBaseName##_t Parse##enumBaseName(MyStr_t enumStr)                        \
{                                                                            \
	for (u64 eIndex = 0; eIndex < enumBaseName##_##numWhatSuffix; eIndex++)  \
	{                                                                        \
		enumBaseName##_t enumValue = (enumBaseName##_t)eIndex;               \
		if (StrEqualsIgnoreCase(enumStr, Get##enumBaseName##Str(enumValue))) \
		{                                                                    \
			return enumValue;                                                \
		}                                                                    \
	}                                                                        \
	return enumBaseName##_##numWhatSuffix;                                   \
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

// +--------------------------------------------------------------+
// |                           FourU64                            |
// +--------------------------------------------------------------+
// 999,999,999 * 999,999,999 = 999,999,998,000,000,001 
// which is less than UINT64_MAX at 18,446,744,073,709,551,615
// This allows us to do mulitplication in a single chunk
#define FOUR_U64_BASE            999999999
#define FOUR_U64_BASE_NUM_DIGITS 9
struct FourU64_t
{
	u64 values[4];
	bool overflow;
};

void FourU64Set(FourU64_t* four, u64 value)
{
	four->overflow = false;
	four->values[0] = (value % FOUR_U64_BASE);
	four->values[1] = (value / FOUR_U64_BASE);
	four->values[2] = 0;
	four->values[3] = 0;
}

i32 FourU64Compare(const FourU64_t* left, const FourU64_t* right)
{
	if (left->values[3] > right->values[3]) { return 1; }
	if (left->values[3] < right->values[3]) { return -1; }
	
	if (left->values[2] > right->values[2]) { return 1; }
	if (left->values[2] < right->values[2]) { return -1; }
	
	if (left->values[1] > right->values[1]) { return 1; }
	if (left->values[1] < right->values[1]) { return -1; }
	
	if (left->values[0] > right->values[0]) { return 1; }
	if (left->values[0] < right->values[0]) { return -1; }
	
	return 0;
}
i32 FourU64Compare(const FourU64_t* left, u64 right)
{
	FourU64_t rightFour;
	FourU64Set(&rightFour, right);
	return FourU64Compare(left, &rightFour);
}

void FourU64Add(FourU64_t* four, u64 operand)
{
	Assert(operand <= FOUR_U64_BASE);
	four->values[0] += operand;
	if (four->values[0] > FOUR_U64_BASE)
	{
		four->values[0] -= FOUR_U64_BASE;
		four->values[1]++;
		if (four->values[1] > FOUR_U64_BASE)
		{
			four->values[1] -= FOUR_U64_BASE;
			four->values[2]++;
			if (four->values[2] > FOUR_U64_BASE)
			{
				four->values[2] -= FOUR_U64_BASE;
				four->values[3]++;
				if (four->values[3] > FOUR_U64_BASE)
				{
					four->values[3] -= FOUR_U64_BASE;
					four->overflow = true;
				}
			}
		}
	}
}

void FourU64Add(FourU64_t* four, const FourU64_t* operand)
{
	u64 carry = 0;
	
	four->values[0] += operand->values[0] + carry;
	if (four->values[0] > FOUR_U64_BASE)
	{
		four->values[0] -= FOUR_U64_BASE;
		carry = 1;
	}
	else { carry = 0; }
	
	four->values[1] += operand->values[1] + carry;
	if (four->values[1] > FOUR_U64_BASE)
	{
		four->values[1] -= FOUR_U64_BASE;
		carry = 1;
	}
	else { carry = 0; }
	
	four->values[2] += operand->values[2] + carry;
	if (four->values[2] > FOUR_U64_BASE)
	{
		four->values[2] -= FOUR_U64_BASE;
		carry = 1;
	}
	else { carry = 0; }
	
	four->values[3] += operand->values[3] + carry;
	if (four->values[3] > FOUR_U64_BASE)
	{
		four->values[3] -= FOUR_U64_BASE;
		four->overflow = true;
	}
}

void FourU64Sub(FourU64_t* four, u64 operand)
{
	Assert(operand <= FOUR_U64_BASE);
	
	if (four->values[0] < operand)
	{
		if (four->values[1] == 0)
		{
			if (four->values[2] == 0)
			{
				if (four->values[3] > 0) { four->values[3]--; }
				else { four->overflow = true; }
				four->values[2] = FOUR_U64_BASE;
			}
			four->values[2]--;
			four->values[1] = FOUR_U64_BASE;
		}
		four->values[1]--;
		four->values[0] += FOUR_U64_BASE;
	}
	
	four->values[0] -= operand;
	Assert(four->values[0] <= FOUR_U64_BASE);
}

void FourU64Sub(FourU64_t* four, const FourU64_t* operand)
{
	if (four->values[0] < operand->values[0])
	{
		if (four->values[1] == 0)
		{
			if (four->values[2] == 0)
			{
				if (four->values[3] > 0) { four->values[3]--; }
				else { four->overflow = true; }
				four->values[2] = FOUR_U64_BASE;
			}
			four->values[2]--;
			four->values[1] = FOUR_U64_BASE;
		}
		four->values[1]--;
		four->values[0] += FOUR_U64_BASE;
	}
	four->values[0] -= operand->values[0];
	
	if (four->values[1] < operand->values[1])
	{
		if (four->values[2] == 0)
		{
			if (four->values[3] > 0) { four->values[3]--; }
			else { four->overflow = true; }
			four->values[2] = FOUR_U64_BASE;
		}
		four->values[2]--;
		four->values[1] += FOUR_U64_BASE;
	}
	four->values[1] -= operand->values[1];
	
	if (four->values[2] < operand->values[2])
	{
		if (four->values[3] > 0) { four->values[3]--; }
		else { four->overflow = true; }
		four->values[2] = FOUR_U64_BASE;
	}
	four->values[2] -= operand->values[2];
	
	if (four->values[3] < operand->values[3])
	{
		four->overflow = true;
		four->values[3] = 0;
	}
	else
	{
		four->values[3] -= operand->values[3];
	}
}

#if 0
u64 MultiplyU64WithOverflow(u64 left, u64 right, u64* overflowOut)
{
	u64 overflowCount = 0;
	u64 result = 0;
	for (u64 addIndex = 0; addIndex < right; addIndex++)
	{
		u64 addAmount = left;
		if (result > FOUR_U64_BASE - addAmount)
		{
			overflowCount++;
			addAmount -= (FOUR_U64_BASE - result);
			result = 0;
		}
		result += addAmount;
	}
	if (overflowOut != nullptr) { *overflowOut = overflowCount; }
	return result;
}
#endif

//returns false on overflow
bool FourU64Multiply(FourU64_t* four, u64 operand)
{
	Assert(operand <= FOUR_U64_BASE);
	
	#if 1
	
	u64 carry = 0;
	for (u64 uIndex = 0; uIndex < 4; uIndex++)
	{
		four->values[uIndex] = (four->values[uIndex] * operand) + carry;
		carry = (four->values[uIndex] / FOUR_U64_BASE);
		four->values[uIndex] = four->values[uIndex] - (carry * FOUR_U64_BASE);
	}
	return (carry == 0);
	
	#else
	u64 valueOverflow0 = 0;
	four->values[0] = MultiplyU64WithOverflow(four->values[0], operand, &valueOverflow0);
	u64 valueOverflow1 = 0;
	four->values[1] = MultiplyU64WithOverflow(four->values[1], operand, &valueOverflow1);
	u64 valueOverflow2 = 0;
	four->values[2] = MultiplyU64WithOverflow(four->values[2], operand, &valueOverflow2);
	u64 valueOverflow3 = 0;
	four->values[3] = MultiplyU64WithOverflow(four->values[3], operand, &valueOverflow3);
	
	if (four->values[1] > FOUR_U64_BASE - valueOverflow0)
	{
		if (valueOverflow1 == FOUR_U64_BASE)
		{
			if (valueOverflow2 == FOUR_U64_BASE)
			{
				valueOverflow3++;
				valueOverflow2 = 0;
			}
			else { valueOverflow2++; }
			valueOverflow1 = 0;
		}
		else { valueOverflow1++; }
		valueOverflow0 -= (FOUR_U64_BASE - four->values[1]);
		four->values[1] = 0;
	}
	four->values[1] += valueOverflow0;
	
	if (four->values[2] > FOUR_U64_BASE - valueOverflow1)
	{
		if (valueOverflow2 == FOUR_U64_BASE)
		{
			valueOverflow3++;
			valueOverflow2 = 0;
		}
		else { valueOverflow2++; }
		valueOverflow1 -= (FOUR_U64_BASE - four->values[2]);
		four->values[2] = 0;
	}
	four->values[2] += valueOverflow1;
	
	if (four->values[3] > FOUR_U64_BASE - valueOverflow2)
	{
		valueOverflow3++;
		valueOverflow2 -= (FOUR_U64_BASE - four->values[3]);
		four->values[3] = 0;
	}
	four->values[3] += valueOverflow2;
	
	return (valueOverflow3 > 0);
	#endif
}

void FourU64FindMaxDivisor(const FourU64_t* four, u64 divisor, FourU64_t* divisorFourOut)
{
	if (FourU64Compare(four, divisor) <= 0) { FourU64Set(divisorFourOut, 0); return; }
	FourU64Set(divisorFourOut, divisor);
	if (four->values[1] > 0) { FourU64Multiply(divisorFourOut, FOUR_U64_BASE); }
	if (four->values[2] > 0) { FourU64Multiply(divisorFourOut, FOUR_U64_BASE); }
	if (four->values[3] > 0) { FourU64Multiply(divisorFourOut, FOUR_U64_BASE); }
	while (FourU64Compare(four, divisorFourOut) > 0)
	{
		FourU64_t power = *divisorFourOut;
		FourU64Multiply(&power, 2);
		if (FourU64Compare(four, &power) <= 0) { break; }
		*divisorFourOut = power;
	}
	while (FourU64Compare(four, divisorFourOut) > 0) { FourU64Add(divisorFourOut, divisor); }
	while (FourU64Compare(four, divisorFourOut) < 0 && FourU64Compare(divisorFourOut, divisor) > 0) { FourU64Sub(divisorFourOut, divisor); }
}

u64 FourU64Modulo(const FourU64_t* four, u64 divisor)
{
	#if 1
	
	FourU64_t result;
	MyMemCopy(&result, four, sizeof(FourU64_t));
	while (FourU64Compare(&result, divisor) > 0)
	{
		FourU64_t divisorFour;
		FourU64FindMaxDivisor(&result, divisor, &divisorFour);
		if (FourU64Compare(&divisorFour, (u64)0) == 0) { break; }
		FourU64Sub(&result, &divisorFour);
	}
	return result.values[0];
	
	#else
	Assert(divisor <= FOUR_U64_BASE);
	u64 baseRemainder = (FOUR_U64_BASE % divisor);
	u64 powerOffset = (baseRemainder > 0) ? (baseRemainder - 1) : (divisor - 1);
	// PrintLine_D("powerOffset of FOUR_U64_BASE and %llu is %llu (%llu)", divisor, powerOffset, baseRemainder);
	u64 remainder0 = (four->values[0] % divisor);
	u64 remainder1 = (four->values[1] % divisor);
	u64 remainder2 = (four->values[2] % divisor);
	u64 remainder3 = (four->values[3] % divisor);
	u64 result = remainder0;
	if (remainder1 > 0) { result = (result + ((remainder1 + powerOffset) % divisor)) % divisor; }
	if (remainder2 > 0) { result = (result + ((remainder2 + powerOffset) % divisor)) % divisor; }
	if (remainder3 > 0) { result = (result + ((remainder3 + powerOffset) % divisor)) % divisor; }
	return result;
	#endif
}

MyStr_t GetFourU64Str(MemArena_t* memArena, const FourU64_t* four)
{
	if (four->values[3] == 0)
	{
		if (four->values[2] == 0)
		{
			if (four->values[1] == 0)
			{
				return PrintInArenaStr(memArena, "%llu", four->values[0]);
			}
			else
			{
				return PrintInArenaStr(memArena, "%llu%09llu", four->values[1], four->values[0]);
			}
		}
		else
		{
			return PrintInArenaStr(memArena, "%llu%09llu%09llu", four->values[2], four->values[1], four->values[0]);
		}
	}
	else
	{
		return PrintInArenaStr(memArena, "%llu%09llu%09llu%09llu", four->values[3], four->values[2], four->values[1], four->values[0]);
	}
}
