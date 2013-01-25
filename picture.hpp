
#ifndef DEF_PICTURE
#define DEF_PICTURE

#include <boost/filesystem/path.hpp>

class Picture
{
	public:
		Picture(const boost::filesystem::path& path);
		~Picture();

		char getPart(size_t pos) const; // Les deux bits de poid faible du char sont à prendre en compte
		void setPart(size_t pos, char value);

		void save();

		uint32_t width() const;
		uint32_t height() const;

	private:
		const boost::filesystem::path& m_path;

		char *m_data;
		char *m_pixBeg;
		size_t m_length;
		size_t m_raw;
		size_t m_beg;
		uint32_t m_width;
		uint32_t m_height;

		size_t idToPos(size_t id) const;
};

#endif
