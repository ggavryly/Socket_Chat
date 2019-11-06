#pragma once

#include "main.hpp"

typedef std::unordered_map<int ,std::string> my_unordered_map;

class My_Unordered_Map
{
	public:
		My_Unordered_Map();
		My_Unordered_Map(My_Unordered_Map const &);
		~My_Unordered_Map();
	
	public:
		void						Insert(int key, std::string & value);
		std::string &				GetValue(int key);
		int 						GetMax();
		my_unordered_map::iterator	begin();
		my_unordered_map::iterator	end();
		my_unordered_map::iterator	erase(my_unordered_map::iterator &);
		
	private:
		my_unordered_map	my_map;
		int					max;
};

