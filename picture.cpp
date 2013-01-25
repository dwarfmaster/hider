
#include "picture.hpp"
#include <SDL_image.h>

void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
Uint32 getpixel(SDL_Surface *surface, int x, int y);

	Picture::Picture(const boost::filesystem::path& path)
: m_path(path)
{
	m_img = IMG_Load(path.string().c_str());
	if( m_img == NULL )
		throw std::string("Erreur au chargement de l'image.");
}

char Picture::getPart(Uint32 x, Uint32 y, Uint8 p) const
{
	Uint32 pix = getpixel(m_img, x, y);
	Uint8 r, g, b;
	SDL_GetRGB(pix, m_img->format, &r, &g, &b);

	if( p == 0 )
		return r & 3; // 3 == 0b00000011
	else if( p == 1 )
		return b & 3; // 3 == 0b00000011
	else
		return g & 3; // 3 == 0b00000011
}

void Picture::setPart(Uint32 x, Uint32 y, Uint8 p, char value)
{
	Uint32 pix = getpixel(m_img, x, y);
	Uint8 r, g, b;
	SDL_GetRGB(pix, m_img->format, &r, &g, &b);

	value &= 3; // Juste une sécurité
	if( p == 0 )
	{
		r &= 252; // 252 == 0b11111100
		r |= value;
	}
	else if( p == 1 )
	{
		g &= 252; // 252 == 0b11111100
		g |= value;
	}
	else
	{
		b &= 252; // 252 == 0b11111100
		b |= value;
	}

	putpixel(m_img, x, y, SDL_MapRGB(m_img->format, r, g, b));
}

void Picture::save()
{
	SDL_SaveBMP(m_img, m_path.string().c_str());
}

Uint32 getpixel(SDL_Surface *surface, int x, int y)
{
	int bpp = surface->format->BytesPerPixel;
	/* Here p is the address to the pixel we want to retrieve */
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

	switch(bpp) {
		case 1:
			return *p;

		case 2:
			return *(Uint16 *)p;

		case 3:
			if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
				return p[0] << 16 | p[1] << 8 | p[2];
			else
				return p[0] | p[1] << 8 | p[2] << 16;

		case 4:
			return *(Uint32 *)p;

		default:
			return 0;       /* shouldn't happen, but avoids warnings */
	}
}

void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
	int bpp = surface->format->BytesPerPixel;
	/* Here p is the address to the pixel we want to set */
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

	switch(bpp) {
		case 1:
			*p = pixel;
			break;

		case 2:
			*(Uint16 *)p = pixel;
			break;

		case 3:
			if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
				p[0] = (pixel >> 16) & 0xff;
				p[1] = (pixel >> 8) & 0xff;
				p[2] = pixel & 0xff;
			} else {
				p[0] = pixel & 0xff;
				p[1] = (pixel >> 8) & 0xff;
				p[2] = (pixel >> 16) & 0xff;
			}
			break;

		case 4:
			*(Uint32 *)p = pixel;
			break;
	}
}

