
#ifndef DEF_PICTURE
#define DEF_PICTURE

#include <SDL.h>
#include <boost/filesystem/path.hpp>

class Picture
{
	public:
		Picture(const boost::filesystem::path& path);

		char getPart(Uint32 x, Uint32 y, Uint8 p) const; // Les deux bits de poid faible du char sont à prendre en compte
		void setPart(Uint32 x, Uint32 y, Uint8 p, char value);

		void save();

	private:
		SDL_Surface* m_img;
		const boost::filesystem::path& m_path;
};

#endif
