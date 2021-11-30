#include "Sem.h"

bool Sem::SemAnaliz(LT::LexTable lextable, IT::IdTable idtable, Log::LOG log)
{

	bool sem_ok = true;

	for (int i = 0; i < lextable.size; i++)
	{
		switch (lextable.table[i].lexema)
		{
		case LEX_DIRSLASH:
		{
			int k = i;
			if (lextable.table[i + 1].lexema == LEX_ID)
			{
				for (k; k > 0; k--)
				{
					if (lextable.table[k].lexema == LEX_ID)
					{
						if (idtable.table[lextable.table[k].idxTI].id == idtable.table[lextable.table[i + 1].idxTI].id)
						{
							if (lextable.table[k + 2].lexema == LEX_LITERAL && idtable.table[lextable.table[k + 2].idxTI].value.vint == 0)
							{
								sem_ok = false;
								Log::WriteError(log, Error::geterrorin(318, lextable.table[k].sn, 0));//Деление на нуль
							}
						}
					}
				}
			}
			if (lextable.table[i + 1].lexema == LEX_LITERAL)
			{
				if (idtable.table[lextable.table[i + 1].idxTI].value.vint == 0)
				{
					sem_ok = false;
					Log::WriteError(log, Error::geterrorin(318, lextable.table[k].sn, 0));//Деление на нуль
				}
			}
			break;
		}
		case LEX_EQUAL: // выражение
		{
			if (i > 0 && lextable.table[i - 1].idxTI != LT_TI_NULLIDX) // левый операнд
			{
				IT::IDDATATYPE lefttype = idtable.table[lextable.table[i - 1].idxTI].iddatatype;
				bool ignore = false;

				for (int k = i + 1; lextable.table[k].lexema != LEX_SEMICOLON; k++)
				{
					if (k == lextable.size)
						break; // синтакс ошибка - нет ;
					if (lextable.table[k].idxTI != LT_TI_NULLIDX) // если ид - проверить совпадение типов
					{
						if (!ignore)
						{
							IT::IDDATATYPE righttype = idtable.table[lextable.table[k].idxTI].iddatatype;
							if (righttype == IT::IDDATATYPE::INT16) righttype = IT::IDDATATYPE::INT;
							if (lefttype != righttype) // типы данных в выражении не совпадают
							{
								Log::WriteError(log, Error::geterrorin(314, lextable.table[k].sn, 0));
								sem_ok = false;
								break;
							}
						}
						// если лексема сразу после идентиф скобка - это вызов функции
						if (lextable.table[k + 1].lexema == LEX_LEFTTHESIS)
						{
							ignore = true;
							continue;
						}
						// закрывающая скобка после списка параметров
						if (ignore && lextable.table[k + 1].lexema == LEX_RIGHTTHESIS)
						{
							ignore = false;
							continue;
						}
					}
					if (lefttype == IT::IDDATATYPE::STR) // справа только литерал, ид или вызов строковой ф-ции
					{
						char l = lextable.table[k].lexema;
						if (l == LEX_PLUS || l == LEX_MINUS || l == LEX_STAR) // выражения недопустимы
						{
							Log::WriteError(log, Error::geterrorin(316, lextable.table[k].sn, 0));
							sem_ok = false;
							break;
						}
					}
				}
			}
			break;
		}
		case LEX_ID: // проверка типа возвращаемого значения  
		{
			IT::Entry e = idtable.table[lextable.table[i].idxTI];

			if (i > 0 && lextable.table[i - 1].lexema == LEX_FUNCTION)
			{
				if (e.idtype == IT::IDTYPE::F && e.iddatatype != IT::IDDATATYPE::VOI) //функция, не процедура
				{
					for (int k = i + 1; ; k++)
					{
						char l = lextable.table[k].lexema;
						if (l == LEX_RETURN)
						{
							int next = lextable.table[k + 1].idxTI; // след. за return
							if (next != LT_TI_NULLIDX)
							{
								// тип функции и возвращаемого значения не совпадают
								if (idtable.table[next].iddatatype != e.iddatatype)
								{
									Log::WriteError(log, Error::geterrorin(315, lextable.table[k].sn, 0));
									sem_ok = false;
									break;
								}
							}
							break; // нашли exit
						}

						if (k == lextable.size) break;
					}
				}
			}
			if (lextable.table[i + 1].lexema == LEX_LEFTTHESIS && lextable.table[i - 1].lexema != LEX_FUNCTION) // именно вызов
			{
				if (e.idtype == IT::IDTYPE::F) // точно функция
				{
					int paramscount = NULL;
					// проверка передаваемых параметров
					for (int j = i + 1; j<= i+e.parm; j++)
					{
						// проверка соответствия передаваемых параметров прототипам
						if (lextable.table[j].lexema == LEX_ID || lextable.table[j].lexema == LEX_LITERAL)
						{
							paramscount++;
							if (e.parm == NULL)
								break;
							IT::IDDATATYPE ctype = idtable.table[lextable.table[j].idxTI].iddatatype;
							if (ctype != idtable.table[lextable.table[i].idxTI + paramscount].iddatatype)
							{
								// Несовпадение типов передаваемых параметров
								Log::WriteError(log, Error::geterrorin(309, lextable.table[i].sn, 0));
								sem_ok = false;
								break;
							}
						}
						if (j == lextable.size)
							break;
					}
					if (paramscount != e.parm)
					{
						// Количество передаваемых и принимаемых параметров не совпадает
						Log::WriteError(log, Error::geterrorin(308, lextable.table[i].sn, 0));
						sem_ok = false;
					}
					if (paramscount > 3)
					{
						// Слишком много параметров в вызове
						Log::WriteError(log, Error::geterrorin(307, lextable.table[i].sn, 0));
						sem_ok = false;
					}
				}
			}
			break;
		}
		case LEX_LOGOPERATOR:
		{
			// левый и правый операнд - числовой тип
			bool flag = true;
			if (i > 1 && lextable.table[i - 1].idxTI != LT_TI_NULLIDX)
			{
				if (idtable.table[lextable.table[i - 1].idxTI].iddatatype != IT::IDDATATYPE::INT)
					flag = false;
			}
			if (lextable.table[i + 1].idxTI != LT_TI_NULLIDX)
			{
				if (idtable.table[lextable.table[i + 1].idxTI].iddatatype != IT::IDDATATYPE::INT)
					flag = false;
			}
			if (!flag)
			{
				// строка или неизвестный ид в условии
				Log::WriteError(log, Error::geterrorin(317, lextable.table[i].sn, 0));//Неверное условие вырожения
				sem_ok = false;
			}
			break;
		}
		}
	}
	return sem_ok;
}
