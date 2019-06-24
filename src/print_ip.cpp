// print_ip.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <list>
#include <tuple>
#include "print_ip.h"

using namespace flaber;

int main()
{
	print_ip(std::cout, char(-1));
	std::cout << std::endl;
	print_ip(std::cout, short(0));
	std::cout << std::endl;
	print_ip(std::cout, 2130706433);
	std::cout << std::endl;
	print_ip(std::cout, 8875824491850138409);
	std::cout << std::endl;
	print_ip(std::cout, std::string{ "192.168.0.1" });
	std::cout << std::endl;
	print_ip(std::cout, std::vector<int> {192, 168, 0, 2});
	std::cout << std::endl;
	print_ip(std::cout, std::list<int> {192, 168, 0, 3});
	std::cout << std::endl;
	print_ip(std::cout, std::make_tuple(192, 168, 0, 4));
	std::cout << std::endl;
	print_ip(std::cout,  "192.168.0.5" );

}

