#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <stdarg.h>
#include <iostream>
#include <time.h>
#include "In.h"
#include "Parm.h"
#include "Error.h"
namespace Log	// работа с протоколом
{
	struct LOG		// протокол
	{
		wchar_t logfile[PARM_MAX_SIZE];	// имя файла протокола
		std::ofstream* stream;			// выходной поток протокола
	};

	static const LOG INITLOG = { L"", NULL };		// структра для начальной инициализации LOG
	LOG getlog(wchar_t logfile[]);					// сформировать структуру LOG
	void WriteLine(LOG log, char* c, ...);			// вывести в протокол конкатенацию строк
	void WriteLine(LOG log, const wchar_t* c, ...);		// вывести в протокол конкатенацию строк
	void WriteLog(LOG log);							// вывести в протокол заголовок
	void WriteParm(LOG log, Parm::PARM parm);		// вывести в протокол информацию о входных параметрах
	void WriteIn(LOG log, In::IN in);				// вывести в протокол информацию о входном потоке
	void WriteError(LOG log, Error::ERROR error);	// вывести в протокол информацию об ошибке
	void Close(LOG log);							// закрыть протокол
}