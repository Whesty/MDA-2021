#include "stdafx.h"
namespace GRB {

	Greibach greibach(
		NS('S'), // стартовый символ
		TS('$'), //дно стека      
		10,                    // количество правил
		Rule(
			NS('S'),
			GRB_ERROR_SERIES + 0,    // неверная структура программы
			10,                                // 
			Rule::Chain(6, TS('m'), TS('{'), NS('N'), TS('r'), TS(';'), TS('}')),
			Rule::Chain(13, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), NS('S')),
			Rule::Chain(12, TS('n'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}')),
			Rule::Chain(12, TS('n'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('r'), TS(';'), TS('}'), NS('S')),
			Rule::Chain(11, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('r'), TS(';'), TS('}')),
			Rule::Chain(12, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), TS('r'), NS('E'), TS(';'), TS('}'), NS('S')),
			Rule::Chain(11, TS('n'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), TS('r'), NS('E'), TS(';'), TS('}')),
			Rule::Chain(11, TS('n'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), TS('r'), TS(';'), TS('}'), NS('S')),
			Rule::Chain(10, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), TS('r'), TS(';'), TS('}')),
			Rule::Chain(7, TS('m'), TS('{'), NS('N'), TS('r'), TS(';'), TS('}'), NS('S'))
		),
		Rule(
			NS('N'),
			GRB_ERROR_SERIES + 1,    // конструкции в функциях
			18,                               // 
			Rule::Chain(4, TS('t'), TS('i'), TS(';'), NS('N')),
			Rule::Chain(6, TS('i'), TS('('), NS('W'), TS(')'), TS(';'), NS('N')),
			Rule::Chain(5, TS('i'), TS('('), NS('W'), TS(')'), TS(';')),
			Rule::Chain(6, TS('t'), TS('i'), TS('='), NS('E'), TS(';'), NS('N')),
			Rule::Chain(5, TS('t'), TS('i'), TS('='), NS('E'), TS(';')),
			Rule::Chain(4, TS('i'), TS('='), NS('E'), TS(';')),
			Rule::Chain(5, TS('i'), TS('='), NS('E'), TS(';'), NS('N')),
			Rule::Chain(4, TS('p'), TS('i'), TS(';'), NS('N')),
			Rule::Chain(4, TS('p'), TS('l'), TS(';'), NS('N')),
			Rule::Chain(4, TS('p'), NS('E'), TS(';'), NS('N')),
			Rule::Chain(3, TS('p'), NS('E'), TS(';')),
			Rule::Chain(3, TS('t'), TS('i'), TS(';')),
			Rule::Chain(3, TS('p'), TS('i'), TS(';')),
			Rule::Chain(3, TS('p'), TS('l'), TS(';')),
			Rule::Chain(4, TS('w'), TS(':'), NS('I'), NS('X')),
			Rule::Chain(4, TS('o'), TS(':'), NS('I'), NS('O')),
			Rule::Chain(5, TS('w'), TS(':'), NS('I'), NS('X'), NS('N')),
			Rule::Chain(5, TS('o'), TS(':'), NS('I'), NS('O'), NS('N'))
		),
		Rule(
			NS('B'),
			GRB_ERROR_SERIES + 6,    // конструкции условия
			9,                               // 
			Rule::Chain(5, TS('t'), TS('i'), TS('='), NS('E'), TS(';')),
			Rule::Chain(4, TS('i'), TS('='), NS('E'), TS(';')),
			Rule::Chain(3, TS('p'), NS('E'), TS(';')),
			Rule::Chain(3, TS('t'), TS('i'), TS(';')),
			Rule::Chain(3, TS('p'), TS('i'), TS(';')),
			Rule::Chain(3, TS('p'), TS('l'), TS(';')),
			Rule::Chain(6, TS('w'), TS(':'), NS('I'), TS('{'), NS('N'), TS('}')),
			Rule::Chain(4, TS('o'), TS(':'), NS('I'), NS('O')),
			Rule::Chain(6, TS('o'), TS(':'), NS('I'), TS('{'), NS('N'), TS('}'))
		),
		Rule(
			NS('X'),
			GRB_ERROR_SERIES + 6,    // конструкции условия
			22,                               // 
			Rule::Chain(5, TS('{'), NS('N'), TS('}'), TS('^'), NS('B')),
			Rule::Chain(7, TS('{'), NS('N'), TS('}'), TS('^'), TS('{'), NS('N'), TS('}')),
			Rule::Chain(3, TS('{'), NS('N'), TS('}')),

			Rule::Chain(5, TS('t'), TS('i'), TS('='), NS('E'), TS(';')),
			Rule::Chain(4, TS('i'), TS('='), NS('E'), TS(';')),
			Rule::Chain(3, TS('p'), NS('E'), TS(';')),
			Rule::Chain(3, TS('t'), TS('i'), TS(';')),
			Rule::Chain(3, TS('p'), TS('i'), TS(';')),
			Rule::Chain(3, TS('p'), TS('l'), TS(';')),
			Rule::Chain(6, TS('w'), TS(':'), NS('I'), TS('{'), NS('N'), TS('}')),
			Rule::Chain(4, TS('o'), TS(':'), NS('I'), NS('O')),
			Rule::Chain(6, TS('o'), TS(':'), NS('I'), TS('{'), NS('N'), TS('}')),
			Rule::Chain(7, TS('t'), TS('i'), TS('='), NS('E'), TS(';'), TS('^'), NS('B')),
			Rule::Chain(6, TS('i'), TS('='), NS('E'), TS(';'), TS('^'), NS('B')),
			Rule::Chain(5, TS('p'), NS('E'), TS(';'), TS('^'), NS('B')),
			Rule::Chain(5, TS('t'), TS('i'), TS(';'), TS('^'), NS('B')),
			Rule::Chain(5, TS('p'), TS('i'), TS(';'), TS('^'), NS('B')),
			Rule::Chain(5, TS('p'), TS('l'), TS(';'), TS('^'), NS('B')),
			Rule::Chain(8, TS('w'), TS(':'), NS('I'), TS('{'), NS('N'), TS('}'), TS('^'), NS('B')),
			Rule::Chain(4, TS('o'), TS(':'), NS('I'), NS('O')),
			Rule::Chain(8, TS('o'), TS(':'), NS('I'), TS('{'), NS('N'), TS('}'), TS('^'), NS('B')),
			Rule::Chain(5, TS('{'), NS('N'), TS('}'), TS('^'), NS('B'))
		),
		Rule(
			NS('O'),
			GRB_ERROR_SERIES + 7,    
			10,                               // цикл
										 // 
			Rule::Chain(5, TS('t'), TS('i'), TS('='), NS('E'), TS(';')),
			Rule::Chain(4, TS('i'), TS('='), NS('E'), TS(';')),
			Rule::Chain(3, TS('p'), NS('E'), TS(';')),
			Rule::Chain(3, TS('t'), TS('i'), TS(';')),
			Rule::Chain(3, TS('p'), TS('i'), TS(';')),
			Rule::Chain(3, TS('p'), TS('l'), TS(';')),
			Rule::Chain(6, TS('w'), TS(':'), NS('I'), TS('{'), NS('N'), TS('}')),
			Rule::Chain(4, TS('o'), TS(':'), NS('I'), NS('O')),
			Rule::Chain(6, TS('o'), TS(':'), NS('I'), TS('{'), NS('N'), TS('}')),
			Rule::Chain(3, TS('{'), NS('N'), TS('}'))
		),
		Rule(
			NS('E'),
			GRB_ERROR_SERIES + 2,    // ошибка в выражении
			8,                                // 
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('('), NS('E'), TS(')')),
			Rule::Chain(4, TS('i'), TS('('), NS('W'), TS(')')),
			Rule::Chain(2, TS('i'), NS('M')),
			Rule::Chain(2, TS('l'), NS('M')),
			Rule::Chain(4, TS('('), NS('E'), TS(')'), NS('M')),
			Rule::Chain(5, TS('i'), TS('('), NS('W'), TS(')'), NS('M'))
		),
		Rule(
			NS('F'),
			GRB_ERROR_SERIES + 3,    // ошибка в параметрах функции
			2,                                // 
			Rule::Chain(2, TS('t'), TS('i')),
			Rule::Chain(4, TS('t'), TS('i'), TS(','), NS('F'))
		),
		Rule(
			NS('W'),
			GRB_ERROR_SERIES + 4,    // ошибка в параметрах вызываемой функции 
			4,                                // 
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('i'), TS(','), NS('W')),
			Rule::Chain(3, TS('l'), TS(','), NS('W'))
		),
		Rule(
			NS('M'),
			GRB_ERROR_SERIES + 2,    // оператор
			2,                  //
			Rule::Chain(2, TS('v'), NS('E')),
			Rule::Chain(3, TS('v'), NS('E'), NS('M'))
		),
		Rule(
			NS('I'),
			GRB_ERROR_SERIES + 6,    // условие
			8,                  //
			Rule::Chain(3, TS('i'), TS('q'), TS('i')),
			Rule::Chain(3, TS('l'), TS('q'), TS('l')),
			Rule::Chain(3, TS('i'), TS('q'), TS('l')),
			Rule::Chain(3, TS('l'), TS('q'), TS('i')),
			Rule::Chain(5, TS('i'), TS('q'), TS('i'), TS('&'), NS('I')),
			Rule::Chain(5, TS('l'), TS('q'), TS('l'), TS('&'), NS('I')),
			Rule::Chain(5, TS('i'), TS('q'), TS('l'), TS('&'), NS('I')),
			Rule::Chain(5, TS('l'), TS('q'), TS('i'), TS('&'), NS('I'))
		)
	);
	Rule::Chain::Chain(short psize, GRBALPHABET s, ...)
	{
		nt = new GRBALPHABET[size = psize];
		int* p = (int*)&s;
		for (short i = 0; i < psize; i++) nt[i] = (GRBALPHABET)p[i];
	}
	char* Rule::Chain::getCChain(char* b)
	{
		for (int i = 0; i < size; ++i)
			b[i] = alphabet_to_char(nt[i]);
		b[size] = 0x00;
		return b;
	}
	Rule::Rule(GRBALPHABET pnn, int piderror, short psize, Chain c, ...)
	{
		nn = pnn;
		iderror = piderror;
		chains = new Chain[size = psize];
		Chain* p = &c;
		for (int i = 0; i < size; i++) chains[i] = p[i];
	}
	char* Rule::getCRule(char* b, short nchain)
	{
		char bchain[200];
		b[0] = Chain::alphabet_to_char(nn);
		b[1] = '-';
		b[2] = '>';
		b[3] = 0x00;
		chains[nchain].getCChain(bchain);
		strcat_s(b, sizeof(bchain) + 5, bchain);
		return b;
	}
	short Rule::getNextChain(GRBALPHABET t, Rule::Chain& pchain, short j)
	{
		short rc = -1;
		while (j < size && chains[j].nt[0] != t)
			++j;
		rc = (j < size ? j : -1);
		if (rc >= 0)
			pchain = chains[rc];
		return rc;
	}
	Greibach::Greibach(GRBALPHABET pstartN, GRBALPHABET pstbottom, short psize, Rule r, ...)
	{
		startN = pstartN;
		stbottomT = pstbottom;
		rules = new Rule[size = psize];
		Rule* p = &r;
		for (int i = 0; i < size; ++i)
			rules[i] = p[i];
	}
	short Greibach::getRule(GRBALPHABET pnn, Rule& prule)
	{
		short rc = -1;
		short k = 0;
		while (k < size && rules[k].nn != pnn)
			++k;
		if (k < size)
			prule = rules[rc = k];
		return rc;
	}
	Rule Greibach::getRule(short n)
	{
		Rule rc;
		if (n < size)
			rc = rules[n];
		return rc;
	}
	Greibach getGreibach()
	{
		return greibach;
	}
}