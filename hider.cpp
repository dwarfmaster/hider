
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

bool unhide(boost::filesystem::path dest, boost::filesystem::path img)
{
	Picture pict(img);

	std::string str("");
	size_t length = pict.width() * pict.height();

	for(size_t pos = 0; pos < length; ++pos)
	{
		int spos = pos % 4;
		if( spos == 0 )
		{
			str += char(0);
			
			size_t epos = str.find("__EOF__");
			if( epos != std::string::npos )
			{
				str = str.substr(0, epos);
				goto end;
			}
		}
		char c = pict.getPart(pos);
		c <<= (spos * 2);
		str.back() |= c;
	}
end:

	boost::filesystem::ofstream ofs(dest);
	ofs << str;
	ofs.close();

	return true;
}


