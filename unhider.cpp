
#include "unhider.hpp"
#include <iostream>

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


