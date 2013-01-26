
#include "hider.hpp"

#include <boost/filesystem/fstream.hpp>
#include "picture.hpp"

namespace fs = boost::filesystem;

bool hide(boost::filesystem::path srcPath, boost::filesystem::path img)
{
	std::string src;
	fs::ifstream ifs(srcPath);
	if( !ifs )
		throw std::string("Erreur : fichier invalide.");

	std::string line;
	while( std::getline(ifs, line) )
		src += line;
	src += "__EOF__";

	Picture pict(img);

	for(size_t pos = 0; pos < src.size(); ++pos)
	{
		for(size_t spos = 0; spos < 4; ++spos)
		{
			int dec = spos * 2;
			char c = src[pos];
			c &= (3 << dec);
			c >>= dec;

			pict.setPart(pos * 4 + spos, c);
		}
	}

	pict.save();
	return true;
}


