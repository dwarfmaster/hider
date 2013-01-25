
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
}

bool Hider::process()
{
}


