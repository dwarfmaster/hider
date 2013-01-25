#include <SDL.h>
#include <iostream>
#include "options.hpp"
#include "hider.hpp"

int main(int argc, char *argv[])
{
	if( SDL_Init(SDL_INIT_VIDEO) < 0 )
	{
		std::cerr << "Erreur au chargement de la SDL : " << SDL_GetError() << std::endl;
		return 1;
	}
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
			std::cerr << "Cette options n'a pas encore été implémentée." << std::endl;
			end = 1;
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

	SDL_Quit();
	return end;
}

