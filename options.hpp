
#ifndef DEF_OPTIONS
#define DEF_OPTIONS

#include <boost/filesystem.hpp>

class Options
{
	public:
		enum Action{HIDE, UNHIDE, NONE};

		Options(char argc, char *argv[]);

		boost::filesystem::path getTextPath() const;
		boost::filesystem::path getImgPath() const;
		Action getAct() const;

	private:
		boost::filesystem::path m_text;
		boost::filesystem::path m_img;
		Action m_act;
};

#endif

