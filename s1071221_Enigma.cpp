#include "s1071221_Enigma.h"
using namespace std;

Plugboard::Plugboard(std::string encode_table) :Enigma_Component(encode_table)
{

}

size_t Plugboard::Forward(size_t const& i)
{
	char k = 'A';
	char c = encode_table[char(i - 65)];
	if (link_next != nullptr)
	{
		link_next->Spin();
		k = link_next->Input_signal(c);
	}
	for (int i = 0; i < encode_table.size(); i++)
	{
		if (k == encode_table[i])
		{
			k = char(65 + i);
			break;
		}
	}
	return k;
}

void Plugboard::Reset()
{
	link_next->Reset();
}
Rotor::Rotor(std::string encode_table, char const& start_, char const& arrows_) :Enigma_Component(encode_table)
{
	start = start_;
	arrow = arrows_;
	now = 'A';
	Reset();
}

size_t Rotor::Forward(size_t const& i)
{
	char c = 'A';
	for (int i = 0; i < 26;i++)
	{
		if (char(now + i) <= char(90))
		{
			number[i] = char(now + i);
		}
		else
		{
			number[i] = char(now + i -26);
		}
	}
	c = encode_table[number[i - 65] -65];
	for (int i = 0; i < 26; i++) 
	{
		if (c == number[i])
		{
			c = char(65 +i);
			break;
		}
	}
	c = number[link_next->Input_signal(c) - 65];

	for (int i = 0; i < encode_table.size(); i++) 
	{
		if (c == encode_table[i])
		{
			c = char(65 + i);
			break;
		}
	}
	for (int i = 0; i < 26; i++)
	{
		if (c == number[i]) 
		{
			c = char(65 + i);
			break;
		}
	}
	return c;
}

void Rotor::Spin()
{
	now++;//char
	if (now > char(90))
	{
		now = 'A';
	}
	if (now == arrow)
	{
		link_next->Spin();
	}

}

void Rotor::Reset()
{
	now = start;
	if (link_next != nullptr)
	{
		link_next->Reset();
	}
}
Special_Rotor::Special_Rotor(std::string encode_table, char const& start_, char const& arrows_) :Rotor(encode_table, start_, arrows_)
{

}

size_t Special_Rotor::Forward(size_t const& i)
{
	if (CheckSpin == true)
	{
		CheckSpin = false;
		Spin();
	}
	return ::Rotor::Forward(i);
}

void Special_Rotor::Spin()
{
	if (++now > char(90))
	{
		now = 'A';
	}
	if (arrow - 1 == now && link_next != nullptr)
	{
		CheckSpin = true;
	}
	if (arrow == now && link_next != nullptr)
	{
		link_next->Input_signal(0);
	}
}

void Special_Rotor::Reset()
{
	now = start;
	if (link_next != nullptr)
	{
		link_next->Reset();
	}
}
Reflector::Reflector(std::string encode_table) :Enigma_Component(encode_table) 
{

}

size_t Reflector::Forward(size_t const& i) 
{
	char c = encode_table[i - 65];
	return c;
}
