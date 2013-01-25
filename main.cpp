#include <iostream>
#include "options.hpp"
#include "hider.hpp"
#include "unhider.hpp"

int main(int argc, char *argv[])
{
	int end = 0;

	try {
		Options opts(argc, argv);
		if( opts.getAct() == Options::HIDE )
		{
			Hider hider( opts.getTextPath(), opts.getImgPath() );
			hider.process();
		}
		else
		{
			UnHider unhider( opts.getTextPath(), opts.getImgPath() );
			unhider.process();
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

