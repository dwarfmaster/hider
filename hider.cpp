
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
	for(size_t pos = 0; pos < m_src.size(); ++pos)
	{
		for(size_t spos = 0; spos < 4; ++spos)
		{
			int dec = spos * 2;
			char c = m_src[pos];
			c &= (3 << dec);
			c >>= dec;

			m_pict.setPart(pos * 4 + spos, c);
		}
	}

	m_pict.save();
	return true;
}


