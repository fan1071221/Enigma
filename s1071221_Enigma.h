#pragma once
#include "s1071221_Enigma_Base.h"

class Plugboard : public Enigma_Component 
{
public:
	Plugboard(std::string encode_table);
	virtual size_t Forward(size_t const& i);
	void Reset();
};

class Rotor : public Enigma_Component
{
public:
	Rotor(std::string encode_table, char const& start_, char const& arrows_);
	size_t Forward(size_t const& i);
	void Spin();
	void Reset();
	char arrow;
	char start;
	char now;
};

class Special_Rotor : public Rotor
{
public:
	Special_Rotor(std::string encode_table, char const& start_, char const& arrows_);
	size_t Forward(size_t const& i);
	void Spin();
	void Reset();
	bool CheckSpin;
};

class Reflector : public Enigma_Component
{
public:
	Reflector(std::string encode_table);
	size_t Forward(size_t const& i);
};