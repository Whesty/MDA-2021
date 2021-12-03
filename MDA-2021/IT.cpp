#include "IT.h"
#include "Error.h"
#include "stdafx.h"
namespace IT {
	IdTable Create(int size) {
		if (size > TI_MAXSIZE) throw ERROR_THROW(105);
		IdTable Table;
		Table.max_size = size;
		Table.size = 0;
		Table.table = new Entry[size];
		return Table;
	}
	Entry Create(Entry ITEntry)
	{
		return ITEntry;
	}
	void Add(IdTable& idtable, Entry entry) {
		if (idtable.size > idtable.max_size) throw ERROR_THROW(106);
		idtable.table[idtable.size++] = entry;
	}
	Entry GetEntry(IdTable& idtable, int n) {
		return idtable.table[n];
	}
	int IsId(IdTable& idtable, unsigned char id[ID_MAXSIZE]) {
		bool fl = true;
		for (int i = 0; i < idtable.size; i++) {
			if (_mbscmp(idtable.table[i].id, id) == 0)
				return i;
		}
		return TI_NULLIDX;
	}
	void Delete(IdTable& idtable) {
		delete[] idtable.table;

	}

	void showITable(IdTable& table, Log::LOG log)
	{
		//std::fstream *log.stream;
		//*log.stream.open(parm.log, std::ios::app);//ios::app - дописыввать в конец файла
		*log.stream << "------------------Таблица индетификаторов------------------" << endl << endl;
		*log.stream << "№     | Имя        | тип данных | тип индитификатора  | первое вхождение | содержание " << endl;
		for (int i = 0; i < table.size; i++) {
			*log.stream << setw(6) << left <<i + 1  << "| ";
			*log.stream << setw(11) << left << table.table[i].id << "| ";
			if (table.table[i].idtype == OP || table.table[i].idtype == LO) *log.stream << setw(10) << left << "-" << " | ";
			else
				if (table.table[i].iddatatype == INT) {
					*log.stream << setw(10) << left << "bangou" << " | ";
				}
				else if (table.table[i].iddatatype == STR)  *log.stream << setw(10) << left << "rain" << " | ";
				else if (table.table[i].iddatatype == VOI) *log.stream << setw(10) << left << "void" << " | ";
				else *log.stream << setw(10) << left << "bangou(16)" << " | ";
			switch (table.table[i].idtype)
			{
			case L: {*log.stream << setw(19) << left << "Литерал" << " | "; break; }
			case V: {*log.stream << setw(19) << left << "Переменная" << " | "; break; }
			case P: {*log.stream << setw(19) << left << "Параметр" << " | "; break; }
			case F: {*log.stream << setw(8) << left << "Функция " << setw(11) << right << table.table->parm << " | "; break; }
			case OP: {*log.stream << setw(19) << left << "Оператор" << " | "; break; }
			case LO: {*log.stream << setw(19) << left << "Логический оператор" << " | "; break; }
			default:
				break;
			}
			*log.stream << setw(16) << left << table.table[i].idxfirstLE << " | ";
			if (table.table[i].idtype == L) {
				if (table.table[i].iddatatype == INT) {
					*log.stream << table.table[i].value.vint;
				}
				else if (table.table[i].iddatatype == STR) *log.stream << '[' << table.table[i].value.vstr.len << ']' << table.table[i].value.vstr.str;
				else if (table.table[i].iddatatype == INT16) *log.stream << table.table[i].value.vstr.str;
			}
			else *log.stream << "-";
			*log.stream << endl;
		}
	}


	
}