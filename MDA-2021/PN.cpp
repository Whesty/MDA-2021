#include "PN.h"
#include <iostream>
#define LEX_COMMA2 '@'
using namespace std;
bool PolishNotation(int lextable_pos, LT::LexTable& lextable, IT::IdTable idtable, int j) {
	LT::Entry* stek = new LT::Entry[255];
	int idstek = 0;
	int idlex = j;
	bool r = false;
	int comma = 0;
	int idx = 0;
	/*cout << "1\n";*/
	for (int i = j; i < lextable.size; i++)
	{
		if (lextable.table[i].sn == lextable_pos || lextable.table[i].lexema=='&') {
			if ((lextable.table[i].lexema == LEX_OPERATOR) || (lextable.table[i].lexema == LEX_LEFTTHESIS) || (lextable.table[i].lexema == LEX_COMMA)) {
				cout << "stek + " << lextable.table[i].lexema << " size " << idstek << endl;

				stek[idstek++] = lextable.table[i];
			}
			else { 
				if (lextable.table[i].lexema == LEX_RIGHTTHESIS || lextable.table[i].lexema ==LEX_SEMICOLON || lextable.table[i].lexema == LEX_LOGOPERATOR) {
					cout << comma << " " << idstek << " выгрузка из стека:\n";
					
					idstek--;
					while (idstek >= 0) {
						if (stek[idstek].lexema == LEX_LEFTTHESIS) {
							if (r) {
								lextable.table[idlex].comm = comma;
								lextable.table[idlex].lexema = LEX_COMMA2;
								lextable.table[idlex++].sn = lextable_pos;
								if (r) lextable.table[idlex - 1].idxTI = idx;
								cout << "1slex + " << LEX_COMMA << comma << " size " << idlex << endl;
								comma = 0;
								r = false;
							}
							idstek--;
							break; }
						if (stek[idstek].lexema == LEX_COMMA) {
							
							idstek--; continue;
						}
						else {
							cout << "slex + " << stek[idstek].lexema << " size " << idlex << endl;
							lextable.table[idlex++] = stek[idstek--];
							//if(prior(stek[idstek], lextable.table[idlex])) continue;
						}
						
					}
					if (lextable.table[i].lexema == LEX_SEMICOLON || lextable.table[i].lexema == LEX_LOGOPERATOR) {
						lextable.table[idlex++] = lextable.table[i];
						
					}continue;
					idstek = 0;
				}
				cout << "lex + " << lextable.table[i].lexema << " size " << idlex << endl;
				if(r)comma++;
				if (lextable.table[i].lexema == LEX_ID && idtable.table[lextable.table[i].idxTI].idtype == 2) {
					r = true;
					comma = 0;
					idx = lextable.table[i].idxTI;
				}
				else lextable.table[idlex++] = lextable.table[i];
			}
		}
		else {
			idstek--;
			while (idstek >= 0) {
				if (stek[idstek].lexema == LEX_LEFTTHESIS) {
					if (comma > 1 || r) {
						if (comma >= 1) comma++;
						lextable.table[idlex].comm = comma;
						lextable.table[idlex].lexema = LEX_COMMA2;
						lextable.table[idlex++].sn = lextable_pos;
						if (r) lextable.table[idlex - 1].idxTI = idx;
						//cout << "1slex + " << LEX_COMMA << comma << " size " << idlex << endl;
						comma = 0;
						r = false;
					}
					idstek--;
					break;
				}
				if (stek[idstek].lexema == LEX_COMMA) {

					idstek--; continue;
				}
				else {
					//cout << "slex + " << stek[idstek].lexema << " size " << idlex << endl;
					lextable.table[idlex++] = stek[idstek--];
				}
			}
			idstek = 0;
			if (lextable.table[i].lexema == LEX_SEMICOLON) lextable.table[idlex++] = lextable.table[i];

				while (lextable.table[idlex].sn == lextable_pos)
				{
					lextable.table[idlex++].lexema = NULL;
					lextable.table[idlex - 1].sn = lextable_pos;

					//cout << "lex + " << NULL << " size" << idlex << endl;

				}
				i = idlex - 1;
				//lextable_pos++;
				comma = 1;
				if (idstek > 0) {
					cout << "Произошла ошибка приобразования в польскую запись " << lextable.table[i].sn << endl;
					return false;
				}
				idstek = 0;
				//cout << lextable_pos << endl;
				return true;
		}
	}
	//lextable = newlextable;

	return true;
}
void preabr(LT::LexTable& lextable, IT::IdTable idtable) {
	int lextable_pos = 0;
	for (int i = 0; i < lextable.size; i++) {
		if (lextable.table[i].sn > lextable_pos) {
			lextable_pos++;
		}
		if (lextable.table[i + 1].lexema == '=') PolishNotation(lextable_pos, lextable, idtable, i);
		if (lextable.table[i].lexema == 'i' && lextable.table[i + 1].lexema == '(') PolishNotation(lextable_pos, lextable, idtable, i);
		if (lextable.table[i].lexema == ':')  PolishNotation(lextable_pos, lextable, idtable, i);

	}
}
void ShowPN(LT::LexTable& lextable, IT::IdTable& idtable) {
	int sni=1;
	cout << "01.";
	for (int i = 0; i < lextable.size-1; i++)
	{
		if (lextable.table[i].sn > sni) {
			cout << endl;
			sni = lextable.table[i].sn;
			if (sni <= 9) cout << '0' << sni << ".";
			else cout << sni << ".";
		}
		if (lextable.table[i].lexema == NULL) {
			cout << "null";
			continue;
		}
		if (lextable.table[i].lexema == LEX_COMMA2) {
			cout << "@" << lextable.table[i].comm;
		}
		else
		cout << lextable.table[i].lexema;
	}
}
bool prior(LT::Entry i, LT::Entry j) {
	string arr1 = "+-";
	string arr2 = "*/";
	int f1=1, f2=1;
	for (int k=0; k < 2; k++) {
		if (arr1[k] == i.lexema) {
			f1 = 2;
		}
		if (arr2[k] == i.lexema) {
			f1 = 3;
		}
		if (arr1[k] == j.lexema) {
			f2 = 2;
		}
		if (arr2[k] == j.lexema) {
			f2 = 3;
		}
	}
	if (f1 > f2) {
		return true;
	}
	return false;
}