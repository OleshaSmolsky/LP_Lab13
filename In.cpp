#include "In.h"
#include <iostream>
#include "Error.h"
#include <fstream>

namespace In
{
	IN getin(wchar_t infile[])
	{
		IN stat;
		int pos = -1, count = 0;
		stat.size = 0;
		stat.lines = 1;
		stat.ignor = 0;
		stat.text = NULL;
		int array[256]IN_CODE_TABLE;
		for (int i = 0; i < 256; i++)// ������ ������� ��������� � ��������� IN
			stat.code[i] = array[i];
		unsigned char ch;
		std::ifstream fin(infile);

		while (!fin.eof())
		{
			fin.get();
			count++;
		}
		fin.close();
		fin.clear();
		unsigned char* buf = new unsigned char[count];
		for (int i = 0; i < count; i++)// ������� ������
			buf[i] = NULL;

		fin.open(infile);
		if (!fin.is_open())
		{
			throw ERROR_THROW(110);
		}
		ch = fin.get();
		while (!fin.eof())	//������ ����� �� EOF
		{
			if (stat.code[ch] == IN::F) // ����������� ������
			{
				throw ERROR_THROW_IN(111, stat.lines - 1, pos);
			}
			else if (stat.code[ch] == IN::T) // ����������� ������
			{
				if (ch == '\n')// �������� ��������� ������
				{
					pos = -1;
					stat.lines++;
				}
				pos++;
				buf[stat.size] = ch;
				stat.size++;
			}
			else if (stat.code[ch] == IN::I) // ������������ ������
			{
				stat.ignor++;
			}
			else // ���������� ������
			{
				pos++;
				buf[stat.size] = stat.code[ch];
				stat.size++;
			}
			ch = fin.get();
		}
		stat.text = buf;
		fin.close();
		fin.clear();
		return stat;
	}
}