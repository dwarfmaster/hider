
#ifndef DEF_HIDER
#define DEF_HIDER

#include <boost/filesystem/path.hpp>

bool hide(boost::filesystem::path src, boost::filesystem::path img);
bool unhide(boost::filesystem::path dest, boost::filesystem::path img);

#endif
