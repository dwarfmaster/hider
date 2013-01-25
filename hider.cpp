
#include "hider.hpp"

namespace fs = boost::filesystem;

Hider::Hider(boost::filesystem::path src, boost::filesystem::path img)
	: m_pict(img), m_src("")
{
	fs::ifstream ifs(src); // TODO continue
	if( !ifs )
		throw std::string("Erreur : fichier invalide.");

	std::string line;
	while( std::getline(ifs, line) )
		m_src += line;

	m_src += "__EOF__";
}

bool Hider::process()
{
	unsigned long pos = 0;
	bool end = false;
	for(Uint32 x = 0; x < m_pict.width(); ++x)
	{
		for(Uint32 y = 0; y < m_pict.height(); ++y)
		{
			for(int i = 0; i < 3; ++i)
			{
				size_t cpos = pos / 4; // Position du caractère
				if( cpos >= m_src.size() ) // On sort de la boucle en cas de fin
				{
					i = 4;
					y = m_pict.height();
					x = m_pict.width();
					end = true;
				}
				else
				{
					int dec = pos % 4; // Le bloc de bit
					dec *= 2;

					char c = m_src[cpos];
					c &= (3 << dec); // 0b11 << dec
					c >>= dec;

					m_pict.setPart(x, y, i, c);
					++pos;
				}
			}
		}
	}
	m_pict.save();
	return end;
}


