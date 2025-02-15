#include <iostream>
import sizeliteral;
int main()
{
	try
	{
		std::cout << 1024_z << '\n' << 3_z;
		return 0;
	}
	catch (const std::exception& xxx)
	{
		std::cerr << xxx.what() << std::endl;
		return 1;
	}
}