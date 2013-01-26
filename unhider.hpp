
#ifndef DEF_UNHIDER
#define DEF_UNHIDER

#include "picture.hpp"
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/fstream.hpp>
		
bool unhide(boost::filesystem::path dest, boost::filesystem::path img);

#endif

