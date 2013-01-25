
#include "picture.hpp"
#include <boost/filesystem/fstream.hpp>

namespace fs = boost::filesystem;

	Picture::Picture(const fs::path& path)
: m_path(path), m_data(NULL), m_pixBeg(NULL), m_length(0), m_raw(0), m_beg(0), m_width(0), m_height(0)
{
	fs::ifstream ifs;
	ifs.open(path, std::ios::binary);

	// Compute length
	ifs.seekg(0, std::ios::end);
	m_length = ifs.tellg();
	ifs.seekg(0, std::ios::beg);

	// Read
	m_data = new char[m_length];
	ifs.read(m_data, m_length);
	ifs.close();

	// Beginning pixel data
	m_beg = size_t(m_data[10]) + size_t(m_data[11]) * 256 + size_t(m_data[12]) * 256 * 256 + size_t(m_data[13]) * 256 * 256 * 256;
	m_pixBeg = m_data + m_beg;

	// Raw size
	m_raw = size_t(m_data[30]) + size_t(m_data[31]) * 256 + size_t(m_data[32]) * 256 * 256 + size_t(m_data[33]) * 256 * 256 * 256;

	// Size
	m_width = size_t(m_data[18]) + size_t(m_data[19]) * 256;
	m_height = size_t(m_data[20]) + size_t(m_data[21]) * 256;
	std::cout << "Size : (" << m_width << ";" << m_height << ")." << std::endl;

	// Check bpp
	int bpp = int(m_data[24]) + int(m_data[25]) * 256;
	if( bpp != 24 )
		throw std::string("Profondeur de l'image invalide : seule les images 24 bits sont autorisées.");
}

Picture::~Picture()
{
	delete[] m_data;
}

char Picture::getPart(size_t pos) const
{
	return (m_pixBeg[ idToPos(pos) ] & 3); // 3 == 0x11
}

void Picture::setPart(size_t pos, char value)
{
	pos = idToPos(pos);
	char c = m_pixBeg[pos];

	c &= ~char(3); // ~3 == 0x11111100
	value &= 3; // juste par sécurité
	c |= value;
	m_pixBeg[pos] = c;
}

void Picture::save()
{
	fs::ofstream ofs;
	ofs.open(m_path, std::ios::binary);

	// On réécrit les pixels
	ofs.seekp(m_beg);
	ofs.write(m_pixBeg, m_length - m_beg);

	ofs.close();
}

uint32_t Picture::width() const
{
	return m_width;
}

uint32_t Picture::height() const
{
	return m_height;
}

size_t Picture::idToPos(size_t id) const
{
	int nbPad = id / m_width;
	return id + m_raw * nbPad;
}

