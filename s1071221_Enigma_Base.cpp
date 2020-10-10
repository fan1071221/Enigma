#include"s1071221_Enigma_Base.h"
#include<iostream>
#include<fstream>
using namespace std;

void Enigma_Files::Read_file(std::string file)//Read text from file into string
{
	fstream test(file, ios::in);//資料寫入檔案，資料寫入檔案
	if (!test)//fail
	{
		cout << "fail" << endl;
	}
	else//success
	{
		test >> data;
	}
	test.close();//關閉檔案
}
void Enigma_Files::Write_file(std::string file)//Write string from file into string
{
	fstream test(file, ios::out);//資料寫入檔案，資料寫入檔案
	if (!test)//fail
	{
		cout << "fail" << endl;
	}
	else//success
	{
		test << data;
	}
	test.close();//關閉檔案
}
void Enigma_Files::Push(char const& c)//Push a character on the end of data string
{
	data.push_back(c);
}
char const& Enigma_Files::operator [] (size_t const& i)// (const) subscript operator
{
	if (i < 0 || i >= Length())
	{
		cerr << "\nError: Subscript " << i << " out of range" << endl;
		exit(1);
	}
	return data[i];
}
std::string Enigma_Files::Data()//get the data string
{
	return data;
}
size_t Enigma_Files::Length()//report # of character
{
	return data.length();
}
Enigma_Component::Enigma_Component()
{
	link_next = nullptr;
	link_previous = nullptr;
}
Enigma_Component::Enigma_Component(std::string file)
{
	link_next = nullptr;
	link_previous = nullptr;
	Read_table(file);
}
char Enigma_Component::Input_signal(char c)//Input a character and start to encode it.
{
	if (c == 0) 
	{
		Spin();
		return 0;
	}
	return Forward(c);
}
void Enigma_Component::Link(Enigma_Component& next)//Link the NEXT ENCODER
{
	link_next = &next;
	link_previous = this;
}
void Enigma_Component::Reset()//Reset wheel's postion!
{

}
void Enigma_Component::Read_table(std::string file)//Read the Ringstellung and generate encode_table & reverse_table
{
	fstream test(file, ios::in);//資料寫入檔案，資料寫入檔案
	if (!test)//fail
	{
		cout << "fail" << endl;
	}
	else//success
	{
		for (char s; !test.eof();) 
		{
			test >> s;
			encode_table.push_back(s);
		}
	}
	test.close();//關閉檔案
}