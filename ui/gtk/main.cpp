#include <iostream>
#include <gtkmm.h>

int main(int argc, char *argv[])
{
	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "Bitmap text hider");
	Gtk::ApplicationWindow window;
	return app->run(window);
}

