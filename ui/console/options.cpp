#include "options.hpp"
#include <boost/program_options.hpp>

typedef boost::filesystem::path path_t;
namespace opt = boost::program_options;

Options::Options(char argc, char *argv[])
{
	opt::options_description opts("Options autorisées");
	opts.add_options()
		("path,p", opt::value<path_t>(), "Le chemin vers le fichier texte.")
		("hide,h", opt::value<path_t>(), "Le chemin vers l'image dans laquelle va être caché le texte.")
		("unhide,u", opt::value<path_t>(), "Le chemin vers l'image dont le texte va être extrait.")
		;

	opt::parsed_options parsed = opt::command_line_parser(argc, argv)
		.options(opts)
		.run();
	opt::variables_map vm;
	opt::store(parsed, vm);
	opt::notify(vm);

	if( vm.count("path") )
		m_text = vm["path"].as<path_t>();
	else
		throw std::string("Chemin vers fichier non précisé.");

	if( vm.count("hide") && vm.count("unhide") )
		throw std::string("Hide et unhide sont incompatibles.");
	if( vm.count("hide") )
	{
		m_img = vm["hide"].as<path_t>();
		m_act = HIDE;
	}
	else if( vm.count("unhide") )
	{
		m_img = vm["unhide"].as<path_t>();
		m_act = UNHIDE;
	}
	else
		throw std::string("Hide ou unhide doit être précisé.");
}

path_t Options::getTextPath() const
{
	return m_text;
}

path_t Options::getImgPath() const
{
	return m_img;
}

Options::Action Options::getAct() const
{
	return m_act;
}


