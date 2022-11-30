/*
File:   aoc_state.cpp
Author: Taylor Robbins
Date:   11\29\2022
Description: 
	** Holds the AppState_t that facilitates us running advent of code solutions
*/

#include "aoc/aoc.cpp"

#define MULTIPLIER 998

// +--------------------------------------------------------------+
// |                       Access Resources                       |
// +--------------------------------------------------------------+
void AocAppStateAccessResources()
{
	AccessResource(&pig->resources.sounds->click1);
}

// +--------------------------------------------------------------+
// |                            Start                             |
// +--------------------------------------------------------------+
void StartAocAppState(AppState_t oldAppState, bool initialize)
{
	NotNull(aoc);
	
	if (initialize)
	{
		ClearPointer(aoc);
		
		InitMemArena_PagedHeapFuncs(&aoc->aocArena, AOC_ARENA_PAGE_SIZE, PlatAllocFunc, PlatFreeFunc);
		FlagSet(aoc->aocArena.flags, MemArenaFlag_AutoFreePages);
		
		CreateVarArray(&aoc->buttons, mainHeap, sizeof(AocSolutionBtn_t), AocSolution_NumSolutions);
		AocSolution_t prevSolution = AocSolution_First;
		for (u64 sIndex = 0; sIndex < AocSolution_NumSolutions; sIndex++)
		{
			AocSolution_t solution = (AocSolution_t)((u64)AocSolution_First + sIndex);
			if (sIndex == 0 || GetAocSolutionYear(prevSolution) != GetAocSolutionYear(solution))
			{
				AocSolutionBtn_t* newSeparator = VarArrayAdd(&aoc->buttons, AocSolutionBtn_t);
				NotNull(newSeparator);
				ClearPointer(newSeparator);
				newSeparator->displayStr = PrintInArenaStr(mainHeap, "%llu", GetAocSolutionYear(solution));
				newSeparator->isSeparator = true;
			}
			
			AocSolutionBtn_t* newBtn = VarArrayAdd(&aoc->buttons, AocSolutionBtn_t);
			NotNull(newBtn);
			ClearPointer(newBtn);
			newBtn->solution = solution;
			newBtn->isSeparator = false;
			
			prevSolution = solution;
		}
		
		aoc->initialized = true;
	}
	
	AocAppStateAccessResources();
}

// +--------------------------------------------------------------+
// |                             Stop                             |
// +--------------------------------------------------------------+
void StopAocAppState(AppState_t newAppState, bool deinitialize, bool shuttingDown)
{
	UNUSED(newAppState);
	NotNull(aoc);
	
	if (deinitialize && !shuttingDown)
	{
		FreeMemArena(&aoc->aocArena);
		aocArena = nullptr;
		
		VarArrayLoop(&aoc->buttons, bIndex)
		{
			VarArrayLoopGet(AocSolutionBtn_t, btn, &aoc->buttons, bIndex);
			if (!IsEmptyStr(btn->displayStr)) { FreeString(mainHeap, &btn->displayStr); }
		}
		FreeVarArray(&aoc->buttons);
		
		FreeString(mainHeap, &aoc->previousSolutionAnswer);
		
		ClearPointer(aoc);
	}
}

// +--------------------------------------------------------------+
// |                   Layout and CaptureMouse                    |
// +--------------------------------------------------------------+
void LayoutAocAppState()
{
	v2 maxTextSize = Vec2_Zero;
	VarArrayLoop(&aoc->buttons, bIndex)
	{
		VarArrayLoopGet(AocSolutionBtn_t, btn, &aoc->buttons, bIndex);
		// MyStr_t btnText = NewStr(GetAocSolutionDisplayStr(btn->solution));
		MyStr_t btnText = TempPrintStr("Day %llu", GetAocSolutionDay(btn->solution));
		btn->textMeasure = MeasureTextInFont(btnText, &pig->resources.fonts->large, SelectDefaultFontFace());
		if (maxTextSize.width < btn->textMeasure.size.width) { maxTextSize.width = btn->textMeasure.size.width; }
		if (maxTextSize.height < btn->textMeasure.size.height) { maxTextSize.height = btn->textMeasure.size.height; }
	}
	
	if (!IsEmptyStr(aoc->previousSolutionAnswer))
	{
		MyStr_t answerDisplayStr = TempPrintStr("\bDay %llu answer:\b\n%.*s", GetAocSolutionDay(aoc->prevSolution), aoc->previousSolutionAnswer.length, aoc->previousSolutionAnswer.pntr);
		aoc->prevSolutionAnswerMeasure = MeasureTextInFont(answerDisplayStr, &pig->resources.fonts->large, SelectDefaultFontFace(), 1.0f, ScreenSize.width);
		aoc->prevSolutionAnswerRec.size = aoc->prevSolutionAnswerMeasure.size;
		aoc->prevSolutionAnswerRec.x = ScreenSize.width/2 - aoc->prevSolutionAnswerRec.width/2;
		aoc->prevSolutionAnswerRec.y = ScreenSize.height - 10 - aoc->prevSolutionAnswerRec.height;
		RecAlign(&aoc->prevSolutionAnswerRec);
	}
	
	v2 btnSize = maxTextSize + NewVec2(2*AOC_BTN_INNER_PADDING_LEFTRIGHT, 2*AOC_BTN_INNER_PADDING_UP_DOWN);
	u64 numBtnsPerRow = (u64)FloorR32i((ScreenSize.width - AOC_BTNS_MARGIN*2 + AOC_BTNS_PADDING) / (btnSize.width + AOC_BTNS_PADDING));
	v2i gridPos = Vec2i_Zero;
	VarArrayLoop(&aoc->buttons, bIndex)
	{
		VarArrayLoopGet(AocSolutionBtn_t, btn, &aoc->buttons, bIndex);
		if (btn->isSeparator)
		{
			if (gridPos.x > 0)
			{
				gridPos.y++;
				gridPos.x = 0;
			}
			btn->gridPos = gridPos;
			gridPos.y++;
		}
		else
		{
			btn->gridPos = gridPos;
			gridPos.x++;
			if ((u64)gridPos.x >= numBtnsPerRow) { gridPos.y++; gridPos.x = 0; }
		}
		btn->mainRec.size = btnSize;
		btn->mainRec.topLeft = Vec2Fill(AOC_BTNS_MARGIN) + Vec2Multiply(ToVec2(btn->gridPos), btnSize + Vec2Fill(AOC_BTNS_PADDING));
		RecAlign(&btn->mainRec);
		btn->textRec.size = btn->textMeasure.size;
		RecLayoutHorizontalCenter(&btn->textRec, btn->mainRec.width/2);
		RecLayoutVerticalCenter(&btn->textRec, btn->mainRec.height/2);
		RecAlign(&btn->textRec);
	}
}

void CaptureMouseAocAppState()
{
	MouseHitRecNamed(aoc->prevSolutionAnswerRec, "PreviousSolutionAnswer");
	VarArrayLoop(&aoc->buttons, bIndex)
	{
		VarArrayLoopGet(AocSolutionBtn_t, btn, &aoc->buttons, bIndex);
		if (!btn->isSeparator)
		{
			MouseHitRecPrint(btn->mainRec, "AocSolutionBtn_%s", GetAocSolutionStr(btn->solution));
		}
	}
}

// +--------------------------------------------------------------+
// |                            Update                            |
// +--------------------------------------------------------------+
void UpdateAocAppState()
{
	NotNull(aoc);
	AocAppStateAccessResources();
	LayoutAocAppState();
	CaptureMouseAocAppState();
	
	if (KeyPressed(Key_Escape))
	{
		HandleKeyExtended(Key_Escape);
		PopAppState();
	}
	
	// +==============================+
	// |        Update Buttons        |
	// +==============================+
	bool clickedOnBtn = false;
	AocSolution_t clickedBtnSolution = AocSolution_NumSolutions;
	VarArrayLoop(&aoc->buttons, bIndex)
	{
		VarArrayLoopGet(AocSolutionBtn_t, btn, &aoc->buttons, bIndex);
		if (!btn->isSeparator)
		{
			btn->isHovered = IsMouseOverPrint("AocSolutionBtn_%s", GetAocSolutionStr(btn->solution));
			if (btn->isHovered)
			{
				pigOut->cursorType = PlatCursor_Pointer;
				if (MousePressedAndHandleExtended(MouseBtn_Left))
				{
					clickedOnBtn = true;
					clickedBtnSolution = btn->solution;
				}
			}
		}
	}
	
	// +==============================+
	// |    Handle Button Clicked     |
	// +==============================+
	if (clickedOnBtn)
	{
		aocArena = &aoc->aocArena;
		u64 solutionStructSize = GetAocSolutionStructSize(clickedBtnSolution);
		void* solutionStructPntr = AllocMem(mainHeap, solutionStructSize);
		
		PrintLine_Nx(DbgFlag_Inverted, "Running Solution_%s...", GetAocSolutionStr(clickedBtnSolution));
		TempPushMark();
		PerfTime_t solutionStartTime = plat->GetPerfTime();
		
		MyStr_t solutionAnswer = AocSolutionFunc(clickedBtnSolution, solutionStructSize, solutionStructPntr);
		
		PerfTime_t solutionEndTime = plat->GetPerfTime();
		r64 solutionTimeElapsed = plat->GetPerfTimeDiff(&solutionStartTime, &solutionEndTime);
		PrintLine_Nx(DbgFlag_Inverted, "Solution finished in %s", FormatMillisecondsNt((u64)RoundR64i(solutionTimeElapsed), TempArena));
		
		if (!IsEmptyStr(solutionAnswer))
		{
			NotifyPrint_I("Solution to %s: %.*s", GetAocSolutionDisplayStr(clickedBtnSolution), solutionAnswer.length, solutionAnswer.pntr);
			plat->CopyTextToClipboard(solutionAnswer);
			aoc->prevSolution = clickedBtnSolution;
			FreeString(mainHeap, &aoc->previousSolutionAnswer);
			aoc->previousSolutionAnswer = AllocString(mainHeap, &solutionAnswer);
		}
		else
		{
			NotifyPrint_W("No solution to %s", GetAocSolutionDisplayStr(clickedBtnSolution));
			aoc->prevSolution = AocSolution_NumSolutions;
			FreeString(mainHeap, &aoc->previousSolutionAnswer);
		}
		
		ClearMemArena(&aoc->aocArena);
		TempPopMark();
		
	}
	
	// +==============================+
	// |    Handle Answer Clicked     |
	// +==============================+
	if (IsMouseOverNamed("PreviousSolutionAnswer"))
	{
		pigOut->cursorType = PlatCursor_Pointer;
		if (MousePressedAndHandleExtended(MouseBtn_Left))
		{
			plat->CopyTextToClipboard(aoc->previousSolutionAnswer);
			aoc->clickedAnswerAnim = 1.0f;
		}
	}
	
	// +==============================+
	// |  Update Clicked Answer Anim  |
	// +==============================+
	UpdateAnimationDown(&aoc->clickedAnswerAnim, AOC_ANSWER_CLICKED_STR_DISPLAY_TIME);
}

// +--------------------------------------------------------------+
// |                            Render                            |
// +--------------------------------------------------------------+
void RenderAocAppState(FrameBuffer_t* renderBuffer, bool bottomLayer)
{
	UNUSED(bottomLayer);
	NotNull(aoc);
	AocAppStateAccessResources();
	LayoutAocAppState();
	
	RcBegin(pig->currentWindow, renderBuffer, &pig->resources.shaders->main2D, MonokaiDarkGray);
	RcBindFont(&pig->resources.fonts->debug, SelectDefaultFontFace());
	
	// +==============================+
	// |        Render Buttons        |
	// +==============================+
	RcBindFont(&pig->resources.fonts->large, SelectDefaultFontFace());
	r32 btnsAlpha = 1.0f; //TODO: Animate me!
	Color_t btnsBackColor = MonokaiWhite;
	Color_t btnsTextColor = ColorTransparent(Black, btnsAlpha);
	VarArrayLoop(&aoc->buttons, bIndex)
	{
		VarArrayLoopGet(AocSolutionBtn_t, btn, &aoc->buttons, bIndex);
		if (btn->isSeparator)
		{
			v2 btnTextPos = btn->mainRec.topLeft + btn->textRec.topLeft + btn->textMeasure.offset;
			Vec2Align(&btnTextPos);
			
			RcDrawText(btn->displayStr, btnTextPos, MonokaiWhite);
		}
		else
		{
			MyStr_t buttonText = TempPrintStr("Day %llu", GetAocSolutionDay(btn->solution));
			v2 btnTextPos = btn->mainRec.topLeft + btn->textRec.topLeft + btn->textMeasure.offset;
			Vec2Align(&btnTextPos);
			
			RcDrawRoundedRectangle(btn->mainRec, 10.0f, ColorTransparent(btnsBackColor, btnsAlpha * (btn->isHovered ? 0.95f: 0.7f)));
			RcDrawText(buttonText, btnTextPos, btnsTextColor);
		}
	}
	
	// +==============================+
	// |      Render Prev Answer      |
	// +==============================+
	if (!IsEmptyStr(aoc->previousSolutionAnswer))
	{
		MyStr_t answerDisplayStr = TempPrintStr("\bDay %llu answer:\b\n%.*s", GetAocSolutionDay(aoc->prevSolution), aoc->previousSolutionAnswer.length, aoc->previousSolutionAnswer.pntr);
		v2 answerPos = aoc->prevSolutionAnswerRec.topLeft + aoc->prevSolutionAnswerMeasure.offset;
		answerPos.x = aoc->prevSolutionAnswerRec.x + aoc->prevSolutionAnswerRec.width/2;
		
		RcDrawRectangle(RecInflate(aoc->prevSolutionAnswerRec, 5, 5), ColorTransparent(Black, 0.5f));
		RcBindFont(&pig->resources.fonts->large, SelectDefaultFontFace());
		RcDrawText(answerDisplayStr, answerPos, MonokaiWhite, TextAlignment_Center, ScreenSize.width);
		
		if (aoc->clickedAnswerAnim > 0.0f)
		{
			RcBindFont(&pig->resources.fonts->debug, SelectFontFace(24, true));
			r32 clickedStrAlpha = SubAnimAmountR32(aoc->clickedAnswerAnim, 0.0f, 0.2f);
			v2 clickedTextPos = NewVec2(aoc->prevSolutionAnswerRec.x + aoc->prevSolutionAnswerRec.width, aoc->prevSolutionAnswerRec.y);
			RcDrawText("Copied to clipboard!", clickedTextPos, ColorTransparent(MonokaiWhite, clickedStrAlpha), TextAlignment_Right);
		}
	}
}
