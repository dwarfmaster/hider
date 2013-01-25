
#ifndef DEF_OPTIONS
#define DEF_OPTIONS

#include <boost/filesystem.hpp>

class Options
{
	public:
		enum Action{HIDE, UNHIDE, NONE};

		Options(char argc, char *argv[]);

		boost::filesystem::path getPath() const;
		Action getAct() const;

	private:
		boost::filesystem::path m_path;
		Action m_act;
};

#endif

