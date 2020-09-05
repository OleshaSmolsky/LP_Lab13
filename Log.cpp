#include "Log.h"
namespace Log
{
	LOG getlog(wchar_t logfile[])
	{
		LOG log;
		log.stream = new std::ofstream;
		log.stream->open(logfile);
		if (!log.stream->is_open())
		{
			throw ERROR_THROW(112);
		}
		wcscpy_s(log.logfile, logfile);
		return log;
	}
	void WriteLine(LOG log, char* c, ...)
	{
		va_list args;
		va_start(args, c);
		const char* buf = c;
		*(log.stream) << buf;
		while ((buf = va_arg(args, char*)) != "")
		{
			*(log.stream) << buf;
		}
		va_end(args);
		*(log.stream) <<'\n';
		log.stream->flush();
	}
	void WriteLine(LOG log, const wchar_t* c, ...)
	{
		const wchar_t** ptr = &c;
		char buf[100];
		while (*ptr != L"")
		{
			wcstombs(buf, *ptr++, sizeof(buf));
			*(log.stream) << buf;
			++ptr;
		}
		log.stream->flush();
	}
	void WriteLog(LOG log)
	{
		*(log.stream) << "---- �������� ---- ����:";
		time_t now = time(0);
		tm date;
		localtime_s(&date, &now);
		char buf[100];
		strftime(buf, sizeof(buf), "%c", &date);
		*(log.stream) << buf << " ----" << std::endl;
		log.stream->flush();
	}
	void WriteParm(LOG log, Parm::PARM parm)
	{
		*(log.stream) << "---- ��������� ----" << std::endl;
		char buf[100];
		wcstombs(buf, parm.log, sizeof(parm.log));
		*(log.stream) << "-log: " << buf << std::endl;
		wcstombs(buf, parm.out, sizeof(parm.out));
		*(log.stream) << "-out: " << buf << std::endl;
		wcstombs(buf, parm.in, sizeof(parm.in));
		*(log.stream) << "-in: " << buf << std::endl;
	}
	void WriteIn(LOG log, In::IN in)
	{
		*(log.stream) << "---- �������� ������ ----" << std::endl;
		*(log.stream) <<"���������� ��������: " <<in.size << std::endl;
		*(log.stream) <<"���������������    : " <<in.ignor << std::endl;
		*(log.stream) <<"���������� �����   : " <<in.lines << std::endl;
	}
	void WriteError(LOG log, Error::ERROR error)
	{
		if (log.stream->is_open())
		{
			*(log.stream) << "������ " << error.id << " : " << error.message << ", ������ " << error.inext.line << ", ������� " << error.inext.col << std::endl;
		}
		else
		{
			std::cout << "������ " << error.id << " : " << error.message << ", ������ " << error.inext.line << ", ������� " << error.inext.col << std::endl;
		}
	}
	void Close(LOG log)
	{
		log.stream->close();
	}
}