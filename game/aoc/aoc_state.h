/*
File:   aoc_state.h
Author: Taylor Robbins
Date:   11\29\2022
*/

#ifndef _AOC_STATE_H
#define _AOC_STATE_H

#define AOC_ARENA_PAGE_SIZE Megabytes(1)

#define AOC_ANSWER_CLICKED_STR_DISPLAY_TIME 1000 //ms

#define AOC_BUTTONS_SCROLL_SPEED 20

#define AOC_BTNS_MARGIN                 50 //px
#define AOC_BTNS_PADDING                10 //px
#define AOC_BTN_INNER_PADDING_LEFTRIGHT 15 //px
#define AOC_BTN_INNER_PADDING_UP_DOWN   20 //px

#include "aoc/aoc_enum.h"
#include "aoc/aoc2021.h"
#include "aoc/aoc2022.h"

struct AocSolutionBtn_t
{
	bool isSeparator;
	AocSolution_t solution;
	MyStr_t displayStr;
	bool isHovered;
	v2i gridPos;
	rec mainRec;
	TextMeasure_t textMeasure;
	rec textRec;
};

struct AdventOfCodeState_t
{
	bool initialized;
	
	MemArena_t aocArena;
	AocSolution_t prevSolution;
	bool prevSolutionIsB;
	MyStr_t previousSolutionAnswer;
	r32 clickedAnswerAnim;
	
	rec buttonsRec;
	r32 buttonsScroll;
	r32 buttonsScrollMax;
	VarArray_t buttons; //AocSolutionBtn_t
	TextMeasure_t prevSolutionAnswerMeasure;
	rec prevSolutionAnswerRec;
};

#endif //  _AOC_STATE_H
