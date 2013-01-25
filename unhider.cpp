
#include "unhider.hpp"
#include <iostream>

UnHider::UnHider(boost::filesystem::path dest, boost::filesystem::path img)
	: m_pict(img), m_dest(dest)
{}

bool UnHider::process()
{
	unsigned long pos = 0;
	bool end = false;
	std::string str("");

	for(Uint32 x = 0; x < m_pict.width(); ++x)
	{
		for(Uint32 y = 0; y < m_pict.height(); ++y)
		{
			for(int i = 0; i < 3; ++i)
			{
				int dec = pos % 4;
				dec *= 2;

				char c = m_pict.getPart(x, y, i);
				c <<= dec;
				str.back() |= c;

				++pos;

				size_t pos = str.find("__EOF__");
				if( pos != std::string::npos )
				{
					i = 4;
					y = m_pict.height();
					x = m_pict.width();
					end = true;

					str = str.substr(0, pos);
				}
			}
		}
	}

	// TODO enregistrer dans fichier
	std::cout << str << std::endl;
	return end;
}


