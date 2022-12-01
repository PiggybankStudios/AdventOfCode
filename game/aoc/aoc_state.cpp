/*
File:   aoc_state.cpp
Author: Taylor Robbins
Date:   11\29\2022
Description: 
	** Holds the AppState_t that facilitates us running advent of code solutions
*/

MemArena_t* aocArena = nullptr;

#include "aoc/aoc_helpers.cpp"
#include "aoc/aoc2021.cpp"
#include "aoc/aoc2022.cpp"
#include "aoc/aoc_enum.cpp"

void AocAppState_RunAocSolution(AocSolution_t solution, bool doSolutionB)
{
	aocArena = &aoc->aocArena;
	u64 solutionStructSize = GetAocSolutionStructSize(solution);
	void* solutionStructPntr = AllocMem(mainHeap, solutionStructSize);
	
	PrintLineAtx(DbgFlag_Inverted, (doSolutionB ? DbgLevel_Other : DbgLevel_Info), "Running Solution_%s %s...", GetAocSolutionStr(solution), (doSolutionB ? "(B)" : "(A)"));
	TempPushMark();
	PerfTime_t solutionStartTime = plat->GetPerfTime();
	
	MyStr_t solutionAnswer = AocSolutionFunc(solution, solutionStructSize, solutionStructPntr, doSolutionB);
	
	PerfTime_t solutionEndTime = plat->GetPerfTime();
	r64 solutionTimeElapsed = plat->GetPerfTimeDiff(&solutionStartTime, &solutionEndTime);
	
	aoc->prevSolution = solution;
	aoc->prevSolutionIsB = doSolutionB;
	FreeString(mainHeap, &aoc->previousSolutionAnswer);
	
	if (!IsEmptyStr(solutionAnswer))
	{
		PrintLine_I("Solution to %s %s: %.*s", GetAocSolutionDisplayStr(solution), (doSolutionB ? "(B)" : "(A)"), solutionAnswer.length, solutionAnswer.pntr);
		PrintLineAtx(DbgFlag_Inverted, (doSolutionB ? DbgLevel_Other : DbgLevel_Info), "Solution finished in %s", FormatMillisecondsNt((u64)RoundR64i(solutionTimeElapsed), TempArena));
		plat->CopyTextToClipboard(solutionAnswer);
		aoc->clickedAnswerAnim = 1.0f;
		aoc->previousSolutionAnswer = AllocString(mainHeap, &solutionAnswer);
	}
	else
	{
		NotifyPrint_W("No solution to %s %s", GetAocSolutionDisplayStr(solution), (doSolutionB ? "(B)" : "(A)"));
	}
	
	ClearMemArena(&aoc->aocArena);
	TempPopMark();
}

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
		
		aoc->prevSolution = AocSolution_NumSolutions;
		
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
				newSeparator->displayStr = PrintInArenaStr(mainHeap, "\b%llu\b", GetAocSolutionYear(solution));
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
	aoc->buttonsRec.width = ScreenSize.width - (2*AOC_BTNS_MARGIN);
	aoc->buttonsRec.height = ScreenSize.height - (AOC_BTNS_MARGIN);
	aoc->buttonsRec.topLeft = Vec2Fill(AOC_BTNS_MARGIN);
	if (aoc->buttonsRec.y < pig->debugConsole.mainRec.y + pig->debugConsole.mainRec.height)
	{
		r32 change = (pig->debugConsole.mainRec.y + pig->debugConsole.mainRec.height) - aoc->buttonsRec.y;
		aoc->buttonsRec.y += change;
		aoc->buttonsRec.height -= change;
	}
	
	v2 maxTextSize = Vec2_Zero;
	VarArrayLoop(&aoc->buttons, bIndex)
	{
		VarArrayLoopGet(AocSolutionBtn_t, btn, &aoc->buttons, bIndex);
		// MyStr_t btnText = NewStr(GetAocSolutionDisplayStr(btn->solution));
		MyStr_t btnText = TempPrintStr("Day %llu", GetAocSolutionDay(btn->solution)+1);
		btn->textMeasure = MeasureTextInFont(btnText, &pig->resources.fonts->large, SelectDefaultFontFace());
		if (maxTextSize.width < btn->textMeasure.size.width) { maxTextSize.width = btn->textMeasure.size.width; }
		if (maxTextSize.height < btn->textMeasure.size.height) { maxTextSize.height = btn->textMeasure.size.height; }
	}
	
	if (!IsEmptyStr(aoc->previousSolutionAnswer))
	{
		MyStr_t answerDisplayStr = TempPrintStr("\bDay %llu answer %s:\b\n%.*s", GetAocSolutionDay(aoc->prevSolution)+1, (aoc->prevSolutionIsB ? "B" : "A"), aoc->previousSolutionAnswer.length, aoc->previousSolutionAnswer.pntr);
		aoc->prevSolutionAnswerMeasure = MeasureTextInFont(answerDisplayStr, &pig->resources.fonts->large, SelectDefaultFontFace(), 1.0f, ScreenSize.width);
		aoc->prevSolutionAnswerRec.size = aoc->prevSolutionAnswerMeasure.size;
		aoc->prevSolutionAnswerRec.x = ScreenSize.width/2 - aoc->prevSolutionAnswerRec.width/2;
		aoc->prevSolutionAnswerRec.y = ScreenSize.height - 10 - aoc->prevSolutionAnswerRec.height;
		RecAlign(&aoc->prevSolutionAnswerRec);
	}
	
	v2 btnSize = maxTextSize + NewVec2(2*AOC_BTN_INNER_PADDING_LEFTRIGHT, 2*AOC_BTN_INNER_PADDING_UP_DOWN);
	u64 numBtnsPerRow = (u64)FloorR32i((aoc->buttonsRec.width + AOC_BTNS_PADDING) / (btnSize.width + AOC_BTNS_PADDING));
	r32 gridTotalWidth = ((r32)numBtnsPerRow * (btnSize.width + AOC_BTNS_PADDING)) - AOC_BTNS_PADDING;
	r32 buttonsOffsetX = (aoc->buttonsRec.width - gridTotalWidth) / 2;
	v2i gridPos = Vec2i_Zero;
	aoc->buttonsScrollMax = 0;
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
		btn->mainRec.topLeft = Vec2Multiply(ToVec2(btn->gridPos), btnSize + Vec2Fill(AOC_BTNS_PADDING));
		btn->mainRec.x += buttonsOffsetX;
		RecAlign(&btn->mainRec);
		btn->textRec.size = btn->textMeasure.size;
		RecLayoutHorizontalCenter(&btn->textRec, btn->mainRec.width/2);
		RecLayoutVerticalCenter(&btn->textRec, btn->mainRec.height/2);
		RecAlign(&btn->textRec);
		if (aoc->buttonsScrollMax < btn->mainRec.y + btn->mainRec.height)
		{
			aoc->buttonsScrollMax = btn->mainRec.y + btn->mainRec.height;
		}
	}
	
	aoc->buttonsScrollMax = MaxR32(0, aoc->buttonsScrollMax - btnSize.height);
	aoc->buttonsScroll = ClampR32(aoc->buttonsScroll, 0, aoc->buttonsScrollMax);
}

void CaptureMouseAocAppState()
{
	MouseHitRecNamed(aoc->prevSolutionAnswerRec, "PreviousSolutionAnswer");
	if (IsMouseInsideRec(aoc->buttonsRec))
	{
		v2 buttonsBasePos = aoc->buttonsRec.topLeft - NewVec2(0, aoc->buttonsScroll);
		VarArrayLoop(&aoc->buttons, bIndex)
		{
			VarArrayLoopGet(AocSolutionBtn_t, btn, &aoc->buttons, bIndex);
			rec mainRec = btn->mainRec + buttonsBasePos;
			if (!btn->isSeparator)
			{
				MouseHitRecPrint(mainRec, "SolutionListBtn_%s", GetAocSolutionStr(btn->solution));
			}
		}
	}
	MouseHitRecNamed(aoc->buttonsRec, "SolutionList");
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
	// |       Handle Scrolling       |
	// +==============================+
	if (MouseScrolledY() && IsMouseOverNamedPartial("SolutionList"))
	{
		HandleMouseScrollY();
		aoc->buttonsScroll -= pigIn->scrollDelta.y * AOC_BUTTONS_SCROLL_SPEED;
	}
	
	// +==============================+
	// |        Update Buttons        |
	// +==============================+
	bool leftClickedOnBtn = false;
	bool rightClickedOnBtn = false;
	AocSolution_t clickedBtnSolution = AocSolution_NumSolutions;
	VarArrayLoop(&aoc->buttons, bIndex)
	{
		VarArrayLoopGet(AocSolutionBtn_t, btn, &aoc->buttons, bIndex);
		if (!btn->isSeparator)
		{
			btn->isHovered = IsMouseOverPrint("SolutionListBtn_%s", GetAocSolutionStr(btn->solution));
			if (btn->isHovered)
			{
				pigOut->cursorType = PlatCursor_Pointer;
				if (MousePressedAndHandleExtended(MouseBtn_Left))
				{
					leftClickedOnBtn = true;
					clickedBtnSolution = btn->solution;
				}
				if (MousePressedAndHandleExtended(MouseBtn_Right))
				{
					rightClickedOnBtn = true;
					clickedBtnSolution = btn->solution;
				}
			}
		}
	}
	
	// +==============================+
	// |    Handle Button Clicked     |
	// +==============================+
	if (leftClickedOnBtn)
	{
		AocAppState_RunAocSolution(clickedBtnSolution, false);
	}
	if (rightClickedOnBtn)
	{
		AocAppState_RunAocSolution(clickedBtnSolution, true);
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
	// RcDrawRectangle(aoc->buttonsRec, MonokaiPurple);
	RcSetViewport(aoc->buttonsRec);
	v2 buttonsBasePos = aoc->buttonsRec.topLeft - NewVec2(0, aoc->buttonsScroll);
	RcBindFont(&pig->resources.fonts->large, SelectDefaultFontFace());
	r32 btnsAlpha = 1.0f; //TODO: Animate me!
	VarArrayLoop(&aoc->buttons, bIndex)
	{
		VarArrayLoopGet(AocSolutionBtn_t, btn, &aoc->buttons, bIndex);
		rec mainRec = btn->mainRec + buttonsBasePos;
		if (btn->isSeparator)
		{
			v2 btnTextPos = mainRec.topLeft + btn->textRec.topLeft + btn->textMeasure.offset;
			Vec2Align(&btnTextPos);
			
			RcDrawText(btn->displayStr, btnTextPos, MonokaiWhite);
		}
		else
		{
			MyStr_t buttonText = TempPrintStr("Day %llu", GetAocSolutionDay(btn->solution)+1);
			v2 btnTextPos = mainRec.topLeft + btn->textRec.topLeft + btn->textMeasure.offset;
			Vec2Align(&btnTextPos);
			Color_t successFailureColor = (IsEmptyStr(aoc->previousSolutionAnswer) ? MonokaiRed : (aoc->prevSolutionIsB ? MonokaiBlue : MonokaiGreen));
			Color_t btnColor = ((btn->solution == aoc->prevSolution) ? Black : MonokaiWhite);
			Color_t textColor = ((btn->solution == aoc->prevSolution) ? successFailureColor : Black);
			
			if (btn->solution == aoc->prevSolution)
			{
				RcDrawRoundedRectangle(RecInflate(mainRec, 2, 2), 10.0f, ColorTransparent(successFailureColor, btnsAlpha));
			}
			RcDrawRoundedRectangle(mainRec, 10.0f, ColorTransparent(btnColor, btnsAlpha * (btn->isHovered ? 0.95f: 0.7f)));
			RcDrawText(buttonText, btnTextPos, ColorTransparent(textColor, btnsAlpha));
		}
	}
	RcSetViewport(NewRec(Vec2_Zero, ScreenSize));
	
	// +==============================+
	// |      Render Prev Answer      |
	// +==============================+
	if (!IsEmptyStr(aoc->previousSolutionAnswer))
	{
		MyStr_t answerDisplayStr = TempPrintStr("\bDay %llu answer %s:\b\n%.*s", GetAocSolutionDay(aoc->prevSolution)+1, (aoc->prevSolutionIsB ? "B" : "A"), aoc->previousSolutionAnswer.length, aoc->previousSolutionAnswer.pntr);
		v2 answerPos = aoc->prevSolutionAnswerRec.topLeft + aoc->prevSolutionAnswerMeasure.offset;
		answerPos.x = aoc->prevSolutionAnswerRec.x + aoc->prevSolutionAnswerRec.width/2;
		Color_t textColor = (aoc->prevSolutionIsB ? MonokaiBlue : MonokaiGreen);
		
		RcDrawRectangle(RecInflate(aoc->prevSolutionAnswerRec, 5, 5), ColorTransparent(Black, 0.5f));
		RcBindFont(&pig->resources.fonts->large, SelectDefaultFontFace());
		RcDrawText(answerDisplayStr, answerPos, textColor, TextAlignment_Center, ScreenSize.width);
		
		if (aoc->clickedAnswerAnim > 0.0f)
		{
			RcBindFont(&pig->resources.fonts->debug, SelectFontFace(24, true));
			r32 clickedStrAlpha = SubAnimAmountR32(aoc->clickedAnswerAnim, 0.0f, 0.2f);
			v2 clickedTextPos = NewVec2(aoc->prevSolutionAnswerRec.x + aoc->prevSolutionAnswerRec.width, aoc->prevSolutionAnswerRec.y);
			RcDrawText("Copied to clipboard!", clickedTextPos + NewVec2(0, 2), ColorTransparent(Black, clickedStrAlpha), TextAlignment_Right);
			RcDrawText("Copied to clipboard!", clickedTextPos, ColorTransparent(MonokaiWhite, clickedStrAlpha), TextAlignment_Right);
		}
	}
}
