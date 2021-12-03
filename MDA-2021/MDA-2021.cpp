﻿using namespace std;
#include "stdafx.h"
int wmain(int argc, wchar_t* argv[]) {
	setlocale(LC_ALL, "ru");
	Log::LOG	log = Log::INITLOG;
	int colp = 0;
	try
	{
		Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::getlog(parm.log);
		Log::WriteLine(log, "Тест: ", "без ошибок ", "");
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		In::IN in = In::getin(parm.in);
		Log::WriteIn(log, in);
		Lex::LEX lex = Lex::lexAnaliz(log, in);
		LT::showTable(lex.lextable, parm);
		IT::showITable(lex.idtable, log);
		MFST::Mfst mfst(lex.lextable, GRB::getGreibach());//Автомат
		mfst.log = log;
		mfst.start(); //Старт синтаксического анализа
		mfst.savededucation(); // Сохранить вывести правила вывода
		mfst.printrules(); // Отладка: вывести правила вывода
		if (Sem::SemAnaliz(lex.lextable, lex.idtable, log)) cout << "Сематичский анализ выполнен без ошибок" << endl;
		bool polish_ok = Polish::PolishNotation(lex, log);					//выполнить преобразование выражений в ПОЛИЗ
		if (!polish_ok)
		{
			Log::WriteLine(log, "Ошибка при попытке преобразования выражения", "");
			cout << "Ошибка при попытке преобразования выражения" << endl << "Выполнение программы остановлено" << endl;
			return 0;
		}
		else cout << "Преобразование выражений завершено без ошибок" << endl;

		LT::writeLexTable(log.stream, lex.lextable);
		//preabr(lex.lextable, lex.idtable);
		//ShowPN(lex.lextable, lex.idtable);
		Log::Close(log);
		return 0;
	}
	catch (Error::ERROR e)
	{
		cout << endl;
		cout << "Завершилось с ошибкой\n\n";
		Log::WriteError(log, e);
		return 0;
	}
}