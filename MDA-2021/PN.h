#pragma once
#include "IT.h"
#include "LT.h"
bool PolishNotation(int lextable_pos, LT::LexTable& lextable, IT::IdTable idtable, int j);
void preabr(LT::LexTable& lextable, IT::IdTable idtable);
void ShowPN(LT::LexTable& lextable, IT::IdTable& idtable);