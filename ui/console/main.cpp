#include <iostream>
#include <hider.hpp>
#include "options.hpp"

int main(int argc, char *argv[])
{
	int end = 0;

	try {
		Options opts(argc, argv);
		if( opts.getAct() == Options::HIDE )
		{
			hide( opts.getTextPath(), opts.getImgPath() );
		}
		else
		{
			unhide( opts.getTextPath(), opts.getImgPath() );
		}
	}
	catch(const std::string& str)
	{
		std::cerr << "Une erreur est survenue :\n\t\"" << str << "\"." << std::endl;
		end = 1;
	}
	catch(const std::exception& e)
	{
		std::cerr << "Une erreur standart est survenue :\n\t\"" << e.what() << "\"." << std::endl;
		end = 1;
	}
	catch(...)
	{
		std::cerr << "Une erreur inconnue est survenue." << std::endl;
		end = 1;
	}

	return end;
}

