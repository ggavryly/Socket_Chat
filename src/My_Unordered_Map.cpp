#include "My_Unordered_Map.hpp"

My_Unordered_Map::My_Unordered_Map() : max(-1)
{}

My_Unordered_Map::My_Unordered_Map(My_Unordered_Map const &)
{}

My_Unordered_Map::~My_Unordered_Map()
{}

int My_Unordered_Map::GetMax()
{
	return max;
}

void My_Unordered_Map::Insert(int key, std::string &value)
{
	my_map[key] = value;
	if (max < key)
		max = key;
}

std::string& My_Unordered_Map::GetValue(int key)
{
	return my_map[key];
}

my_unordered_map::iterator My_Unordered_Map::begin()
{
	return my_map.begin();
}

my_unordered_map::iterator My_Unordered_Map::end()
{
	return my_map.end();
}

my_unordered_map::iterator My_Unordered_Map::erase(my_unordered_map::iterator & ref)
{
	my_unordered_map::iterator res = my_map.erase(ref);
	return res;
}