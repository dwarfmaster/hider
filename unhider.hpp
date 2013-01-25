
#ifndef DEF_UNHIDER
#define DEF_UNHIDER

#include "picture.hpp"
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/fstream.hpp>

class UnHider
{
	public:
		UnHider(boost::filesystem::path dest, boost::filesystem::path img);
		bool process();

	private:
		Picture m_pict;
		boost::filesystem::path m_dest;
};

#endif

