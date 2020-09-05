#include <iostream>
#include "FST.h"
#include "Error.h"
#include "In.h"
#include "Log.h"
#include "Parm.h"
#include <tchar.h>
#include <locale>
#include <cwchar>
#include <fstream>
int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "rus");
	Log::LOG log = Log::INITLOG;
	char str[50], newTry[] = "Проверка цепочки: ", yes[] = "Цепочка распознана", no[] = "Цепочка не распознана", prb[] = " ", title[] = "---- Разбор цепочек ----";
	try
	{
		Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::getlog(parm.log);
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		In::IN in = In::getin(parm.in);
		Log::WriteIn(log, in);
		int tempPos = 0, begin = 0;
		Log::WriteLine(log, title, "");
		for (int i = 0; i < in.size; i++)
		{
			if (in.text[i] == '|' || i == in.size-1)
			{
				for (int j = 0; j < 50; j++)
					str[j] = NULL;
				for (int j = 0, k = begin; j < tempPos; j++, k++)
					str[j] = in.text[k];
				FST::FST fst(
					str,
					7,
					FST::NODE(1, FST::RELATION('a', 1)),
					FST::NODE(2, FST::RELATION('b', 1), FST::RELATION('b', 2)),
					FST::NODE(4, FST::RELATION('c', 3), FST::RELATION('d', 3), FST::RELATION('e', 3), FST::RELATION('g', 4)),
					FST::NODE(2, FST::RELATION('b', 3), FST::RELATION('b', 4)),
					FST::NODE(3, FST::RELATION('b', 4), FST::RELATION('b', 5), FST::RELATION('g', 2)),
					FST::NODE(1, FST::RELATION('f', 6)),
					FST::NODE()
				);
				Log::WriteLine(log,newTry, str, "");
				if (FST::execute(fst, log))
					Log::WriteLine(log, yes, "");
				else
					Log::WriteLine(log, no, "");
				Log::WriteLine(log,prb, "");
				begin = i + 1;
				tempPos = -1;
			}
			tempPos++;
		}
		Log::Close(log);
	}
	catch (Error::ERROR e)
	{
		Log::WriteError(log, e);
	}
	system("pause");
	return 0;
}