#include "stdafx.h"
#include <cstring>

using namespace std;
namespace Polish
{
	int  getPriority(LT::Entry& e, IT::IdTable idtable)
	{
		if(e.idxTI < TI_MAXSIZE)
		switch (idtable.table[e.idxTI].id[0])
		{
		case LEX_LEFTTHESIS: case LEX_RIGHTTHESIS: return 0;
		case '+': case '-': return 1;
		case '*': case '/': return 2;
		case LEX_LEFTBRACE: case LEX_BRACELET: return 3;
		default: return -1;
		}
	}

	bool PolishNotation(Lex::LEX& tbls, Log::LOG& log)
	{
		unsigned curExprBegin = 0;
		ltvec v; // вектор элементов таблицы лексем
		LT::LexTable new_table = LT::Create(tbls.lextable.max_size);
		intvec vpositions = getExprPositions(tbls); // позиции начала выражений

		for (int i = 0; i < tbls.lextable.size; i++)
		{
			if (curExprBegin < vpositions.size() && i == vpositions[curExprBegin]) // дошли до следующего начала выражения
			{
				int lexcount = fillVector(vpositions[curExprBegin], tbls.lextable, v); // заполняем вектор строками ТЛ в прямом порядке
				if (lexcount > 1)
				{
					bool rc = setPolishNotation(tbls.idtable, log, vpositions[curExprBegin], v);   // получаем вектор co строками ТЛ в польской нотации
					if (!rc)
						return false;
				}

				addToTable(new_table, tbls.idtable, v); // добавляем постpоенный вектор к ТЛ + корректировка ТИ
				i += lexcount - 1;
				curExprBegin++;
				continue;
			}
			if (tbls.lextable.table[i].lexema == LEX_ID || tbls.lextable.table[i].lexema == LEX_LITERAL)
			{
				int firstind = Lex::getIndexInLT(new_table, tbls.lextable.table[i].idxTI);
				if (firstind == -1)
					firstind = new_table.size;
				tbls.idtable.table[tbls.lextable.table[i].idxTI].idxfirstLE = firstind;
			}
			LT::Add(new_table, tbls.lextable.table[i]);
		}

		tbls.lextable = new_table;
		return true;
	}

	int __cdecl fillVector(int posExprBegin, LT::LexTable& lextable, ltvec& v)
	{
		v.clear();
		for (int i = posExprBegin; i < lextable.size; i++)
		{
			if (lextable.table[i].lexema == LEX_SEMICOLON || lextable.table[i].lexema == LEX_SEMICOLON || lextable.table[i].lexema == LEX_ENDIF || lextable.table[i].lexema == LEX_LOGOPERATOR)
				break;
			else v.push_back(LT::Entry(lextable.table[i]));
		}
		return v.size();
	}

	void addToTable(LT::LexTable& new_table, IT::IdTable& idtable, ltvec& v)
	{
		for (unsigned i = 0; i < v.size(); i++)
		{
			LT::Add(new_table, v[i]);
			// правильная обратная связь между ТЛ и ТИ
			if (v[i].lexema == LEX_ID || v[i].lexema == LEX_LITERAL)
			{
				int firstind = Lex::getIndexInLT(new_table, v[i].idxTI);
				idtable.table[v[i].idxTI].idxfirstLE = firstind;
			}
		}
	}

	intvec getExprPositions(Lex::LEX& tbls)
	{
		intvec v;
		bool f_begin = false; // признак найденного конца выражения
		bool f_end = false;  // признак найденного начала выражения
		int begin = 0;  int end = 0;

		for (int i = 0; i < tbls.lextable.size; i++)
		{
			if (!f_begin && (tbls.lextable.table[i].lexema == LEX_EQUAL || tbls.lextable.table[i].lexema == LEX_LOGOPERATOR || tbls.lextable.table[i].lexema == LEX_TWOPOINT)) // начало выражения
			{
				begin = i + 1;
				f_begin = true;
				continue;
			}
			if (f_begin && (tbls.lextable.table[i].lexema == LEX_SEMICOLON || tbls.lextable.table[i].lexema == LEX_ENDIF || tbls.lextable.table[i].lexema == LEX_LOGOPERATOR)) // конец выражения
			{
				end = i;
				f_end = true;
				if (tbls.lextable.table[i].lexema == LEX_LOGOPERATOR) i--;
			}
			if (f_begin && f_end)	// добавить начало и конец выражения в вектор
			{
				v.push_back(begin);
				f_begin = f_end = false;
			}
		}
		return v;
	}

	bool __cdecl setPolishNotation(IT::IdTable& idtable, Log::LOG& log, int lextable_pos, ltvec& v)
	{
		//результирующий вектор
		vector < LT::Entry > result;
		// стек для сохранения операторов
		stack < LT::Entry > s;
		// флаг вызова функции
		bool ignore = false;

		for (unsigned i = 0; i < v.size(); i++)
		{
			if (ignore)	// вызов функции считаем подставляемым значением и заносим в результат
			{
				result.push_back(v[i]);
				if (v[i].lexema == LEX_RIGHTTHESIS) {
					ignore = false;
				}
				continue;
			}
			int priority = getPriority(v[i], idtable); // его приоритет

			if (v[i].lexema == LEX_LEFTTHESIS || v[i].lexema == LEX_RIGHTTHESIS || v[i].lexema == LEX_PLUS || v[i].lexema == LEX_MINUS || v[i].lexema == LEX_STAR || v[i].lexema == LEX_DIRSLASH || v[i].lexema == LEX_LEFTBRACE || v[i].lexema == LEX_BRACELET)
			{
				if (s.empty() /*|| v[i].lexema == LEX_LEFTTHESIS*/)
				{
					s.push(v[i]);
					continue;
				}

				if (v[i].lexema == LEX_RIGHTTHESIS)
				{
					//выталкивание элементов до  скобки
					while (!s.empty() && s.top().lexema != LEX_LEFTTHESIS)
					{
						result.push_back(s.top());
						s.pop();
					}
					if (!s.empty() && s.top().lexema == LEX_LEFTTHESIS)
						s.pop();
					continue;
				}
				//выталкивание элем с большим/равным приоритетом в результат
				while (!s.empty() && getPriority(s.top(), idtable) >= priority)
				{
					if(s.top().lexema != LEX_LEFTTHESIS)
					result.push_back(s.top());
					s.pop();
				}
				s.push(v[i]);
			}

			if (v[i].lexema == LEX_LITERAL || v[i].lexema == LEX_ID) // идентификатор, идентификатор функции или литерал
			{
				if (idtable.table[v[i].idxTI].idtype == IT::IDTYPE::F)
					ignore = true;
				result.push_back(v[i]);	// операнд заносим в результирующий вектор
			}
			if (v[i].lexema != LEX_LEFTTHESIS && v[i].lexema != LEX_RIGHTTHESIS && v[i].lexema != LEX_PLUS && v[i].lexema != LEX_MINUS && v[i].lexema != LEX_STAR && v[i].lexema != LEX_DIRSLASH && v[i].lexema != LEX_ID && v[i].lexema != LEX_LITERAL && v[i].lexema != LEX_LEFTBRACE && v[i].lexema != LEX_BRACELET && v[i].lexema != LEX_ENDIF)
			{
				Log::WriteError(log, Error::geterror(1));
				return false;
			}
		}

		while (!s.empty()) { result.push_back(s.top()); s.pop(); }
		v = result;
		return true;
	}

}

