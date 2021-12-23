using namespace std;
#include "stdafx.h"
int wmain(int argc, wchar_t* argv[]) {
	setlocale(LC_ALL, "ru");
	Log::LOG	log = Log::INITLOG;
	int colp = 0;
	try
	{
			//Получение параметров
		Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::getlog(parm.log);
		log.errors_cout = 0;
		Log::WriteLine(log.stream, "Тест: ", "без ошибок ", "");
		if(parm.more)
			Log::WriteLine(&std::cout, "Тест: ", "без ошибок ", "");
		Log::WriteLog(log.stream);
		if (parm.more)
			Log::WriteLog(&std::cout);

		Log::WriteParm(log.stream, parm);
		if (parm.more)
			Log::WriteParm(&std::cout, parm);

			//Чтение из файла и сепаратор
		In::IN in = In::getin(parm.in);
		Log::WriteIn(log.stream, in);
		if (parm.more)
			Log::WriteIn(&std::cout, in);

			//Лексический анализ
		Lex::LEX lex = Lex::lexAnaliz(log, in);
		cout << "-----Лексический анализ завершился\n" << endl;

			//Вывод выходных данных лексического анализа
		std::fstream fout;
		fout.open(parm.out, std::ios_base::app);
		if (!fout.is_open())
			throw ERROR_THROW(110);
		LT::showTable(lex.lextable, &fout);//Таблица преобразованного исходного кода
		if (parm.more || parm.Lout)
		LT::showTable(lex.lextable, &std::cout);

		LT::writeLexTable(log.stream, lex.lextable);//Лексической таблицы
		if (parm.more || parm.lt)
			LT::writeLexTable( &std::cout, lex.lextable);

		IT::showITable(lex.idtable, log.stream);//Таблица индетификаторов
		if (parm.more || parm.it)
			IT::showITable(lex.idtable, &std::cout);

			//Синтаксический анализ
		MFST::Mfst mfst(lex.lextable, GRB::getGreibach());//Автомат
		mfst.log = log;
		if (parm.more || parm.lenta) mfst.more = true;
		if (mfst.start()) { //Старт синтаксического анализа
			cout << "-----Синтаксический выполнен без ошибок\n" << endl;
		}
		else {
			cout << "-----Найденны ошибки в коде\n" << endl;
			return 0;
		}
		mfst.savededucation(); // Сохранить вывести правила вывода
		mfst.printrules(); // Отладка: вывести правила вывода
		if (Sem::SemAnaliz(lex.lextable, lex.idtable, log)) cout << "-----Сематичский анализ выполнен без ошибок\n" << endl;
		else {
			Log::WriteLine(log.stream, "-----Сематический анализ обнаружел ошибку(и)\n", "");
			cout << "-----Сематический анализ обнаружел ошибку(и)\n" << endl << "-----Выполнение программы остановлено\n" << endl;
			return 0;
		}

		bool polish_ok = Polish::PolishNotation(lex, log);					//выполнить преобразование выражений в ПОЛИЗ
		if (!polish_ok)
		{
			Log::WriteLine(log.stream, "-----Ошибка при попытке преобразования выражения\n", "");
			cout <<"-----Ошибка при попытке преобразования выражения\n" << endl <<  "-----Выполнение программы остановлено\n" << endl;
			return 0;
		}
		else cout << "-----Преобразование выражений завершено без ошибок\n" << endl;

		LT::writeLexTable(log.stream, lex.lextable);
		fout << "\n-----Преобразованная таблица лексем\n";
		LT::showTable(lex.lextable, &fout);//Таблица преобразованного исходного кода
		if (parm.more || parm.Lout) {
			cout << "\n-----Преобразованная таблица лексем\n";
			LT::showTable(lex.lextable, &std::cout);
		}

			//Генерация когда в Assembler
		Gener::CodeGeneration(lex, parm, log);
		Log::Close(log);
		if (log.errors_cout>0) throw Error::geterror(0);
			//Системные команды для коректоного запуска
		cout << "-----Запуск сгенерированного кода\n" << endl;
		system("msbuild.exe ..\\ASM /t:build  /p:cfg=\"release | x86 -v:q\"");
		system("..\\ASM\\Debug\\Asm.exe");
		return 0;
	}
	catch (Error::ERROR e)
	{
		/*if (log.stream->fail())
			cout << "\nОшибка " << e.id << ": " << e.message << endl;*/
		cout << endl;
		cout << "-----Выполнение программы остановлено\n\n";
		//Log::WriteError(log.stream, e);
		return 0;
	}
}