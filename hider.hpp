
#ifndef DEF_HIDER
#define DEF_HIDER

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/fstream.hpp>
#include "picture.hpp"

class Hider
{
	public:
		Hider(boost::filesystem::path src, boost::filesystem::path img);
		bool process();

	private:
		Picture m_pict;
		std::string m_src;
};

#endif
