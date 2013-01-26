
#include "unhider.hpp"
#include <iostream>

UnHider::UnHider(boost::filesystem::path dest, boost::filesystem::path img)
	: m_pict(img), m_dest(dest)
{}

bool UnHider::process()
{
	std::string str("");
	size_t length = m_pict.width() * m_pict.height();

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
		char c = m_pict.getPart(pos);
		c <<= (spos * 2);
		str.back() |= c;
	}
end:

	boost::filesystem::ofstream ofs(m_dest);
	ofs << str;
	ofs.close();

	return true;
}


