/* 
 * ScApplication.cpp Copyright (C) 2017 <pavlo.solntsev@gmail.com>
 *
 * gtkmm example Copyright (C) 2002 gtkmm development team
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "ScpApplication.hpp"
#include "ScpMainwindow.hpp"
#include "ScpKeyfile.hpp"
#include <iostream>
#include <config.h>

ScpApplication::ScpApplication()
: Gtk::Application("org.gtkmm.solchempro")
{
	Glib::set_application_name("SolChemPro");
	m_assistant.set_default_size(600,400);
	inifilepath = Glib::build_filename(Glib::get_user_config_dir(),PACKAGE_TARNAME);
	inifilepath = Glib::build_filename(inifilepath,INIFILE);	
}

Glib::RefPtr<ScpApplication> ScpApplication::create()
{
  return Glib::RefPtr<ScpApplication>( new ScpApplication() );
}

void ScpApplication::on_startup()
{
  //Call the base class's implementation:
  Gtk::Application::on_startup();

//Create the Application menu:
//We can use add_action because Gtk::Application derives from ActionMap:
  add_action("connect",
    sigc::mem_fun(*this, &ScpApplication::on_action_connect) );
  add_action("disconnect",
    sigc::mem_fun(*this, &ScpApplication::on_action_disconnect) );
  add_action("quit",
    sigc::mem_fun(*this, &ScpApplication::on_action_quit) );


  auto app_menu = Gio::Menu::create();
  app_menu->append("_Connect", "app.connect");
  app_menu->append("_Disconnect", "app.disconnect");
  app_menu->append("_Quit", "app.quit");

  set_app_menu(app_menu);


  //Create the per-Window menu:
  auto win_menu = Gio::Menu::create();

  auto submenu_file = Gio::Menu::create();
  submenu_file->append("_Connect", "win.connect");
  submenu_file->append("_Disconnect", "win.disconnect");
  win_menu->append_submenu("Network", submenu_file);

  auto submenu_edit = Gio::Menu::create();
  submenu_edit->append("_Cut", "win.cut");
  auto item = Gio::MenuItem::create("_Copy", "win.copy");
  //Setting "accel" works, but might be deprecated soon: See https://bugzilla.gnome.org/show_bug.cgi?id=708908
  //When it is deprecated, use Gtk::Application::set_accel_for_action() instead.
  item->set_attribute_value("accel", Glib::Variant<Glib::ustring>::create("<Primary>c"));
  submenu_edit->append_item(item);
  item = Gio::MenuItem::create("_Paste", "win.paste");
  item->set_attribute_value("accel", Glib::Variant<Glib::ustring>::create("<Primary>v"));
  submenu_edit->append_item(item);
  win_menu->append_submenu("Edit", submenu_edit);

  auto submenu_notification = Gio::Menu::create();
  submenu_notification->append("_Send", "win.send-note");
  submenu_notification->append("_Withdraw", "win.withdraw-note");
  win_menu->append_submenu("Notification", submenu_notification);

  set_menubar(win_menu);

  //Create an action with a parameter. This action can be activated from
  //a Gio::Notification, sent by the Notification/win.send-note menu selection.
  auto action_print =
    Gio::SimpleAction::create("print", Glib::VARIANT_TYPE_STRING);
  action_print->signal_activate().connect(
    sigc::mem_fun(*this, &ScpApplication::on_action_print));
  add_action(action_print);
}

void ScpApplication::create_window()
{
#ifndef INIFILE 
#define INIFILE "solchempro.ini"
#endif
	auto GFileini = Gio::File::create_for_path(inifilepath);
	
	auto parentdir = GFileini->get_parent();
		
	if(!GFileini->query_exists()){
		try{	
			if(!parentdir->query_exists())
				parentdir->make_directory_with_parents();

			GFileini->create_file(Gio::FILE_CREATE_REPLACE_DESTINATION);
			m_keyfile.set_boolean( ScpKeyfile::GROUP_GENERAL,
			                       ScpKeyfile::KEY_STARTCHECK,
                                   true);
			// TODO: check return value for save_to_file() functin
			m_keyfile.save_to_file(inifilepath); 
		}catch (Gio::Error &e){
			std::cerr << "Can't create an INI file. " << std::endl;
			std::cerr << "Check access to the " << Glib::get_user_config_dir() << std::endl;		
			std::cerr << e.what() << std::endl;
			on_action_quit();
		}
	}else
	{
//		m_keyfile.save_to_file(inifilepath); 
		try{
			m_keyfile.load_from_file(inifilepath);
			m_keyfile.set_boolean(ScpKeyfile::GROUP_GENERAL,
                                  ScpKeyfile::KEY_STARTCHECK,
                                  true);	
			// TODO: check return value for save_to_file() functin
			m_keyfile.save_to_file(inifilepath); 
		}catch(Glib::FileError &e){
			std::cerr << "Error reading INI file" << std::endl;
		}catch(Glib::KeyFileError &e){
			std::cerr << "Error reading INI file" << std::endl;
			std::cerr << __FILE__ << ": " << e.what() << std::endl;
			on_action_quit();
		}
	}

  m_refWindow = new ScpMainwindow();
  m_refWindow->set_default_size(800, 600);
  m_refWindow->set_keyfilename(GFileini);

  //Make sure that the application runs for as long this window is still open:
  add_window(*m_refWindow);

  //Delete the window when it is hidden.
  //That's enough for this simple example.
  m_refWindow->signal_hide().connect(sigc::bind(sigc::mem_fun(*this,
    &ScpApplication::on_window_hide), m_refWindow));

  m_refWindow->show();
}

void ScpApplication::on_window_hide(Gtk::Window* window)
{
  delete window;
}

void ScpApplication::on_activate()
{
	try{
		m_keyfile.load_from_file(inifilepath,Glib::KEY_FILE_KEEP_TRANSLATIONS);
		
		if(!m_keyfile.get_boolean(ScpKeyfile::GROUP_GENERAL,
                                  ScpKeyfile::KEY_STARTCHECK))
			first_time_start();

	}catch(Glib::KeyFileError &e)
	{
		std::cerr << "Can't readINI file. " << std::endl;
		std::cerr << "Check access to the " << inifilepath << std::endl;		
		std::cerr << e.what() << std::endl;
		first_time_start();

	}catch(Glib::FileError &e)
	{
		std::cerr << "Can't readINI file. " << std::endl;
		std::cerr << "Check access to the " << inifilepath << std::endl;		
		std::cerr << e.what() << std::endl;
		first_time_start();
	}

  //std::cout << "debug1: " << G_STRFUNC << std::endl;
  // The application has been started, so let's show a window.
  // A real application might want to reuse this "empty" window in on_open(),
  // when asked to open a file, if no changes have been made yet.
	
	if(!m_assistant.is_visible())
		create_window();
}

void ScpApplication::on_action_quit()
{
  std::cout << G_STRFUNC << std::endl;
  quit(); // Not really necessary, when Gtk::Widget::hide() is called.

// Gio::Application::quit() will make Gio::Application::run() return,
// but it's a crude way of ending the program. The window is not removed
// from the application. Neither the window's nor the application's
// destructors will be called, because there will be remaining reference
// counts in both of them. If we want the destructors to be called, we
// must remove the window from the application. One way of doing this
// is to hide the window.
  auto windows = get_windows();
  if (windows.size() > 0)
    windows[0]->hide(); // In this simple case, we know there is only one window.
}

void ScpApplication::on_action_print(const Glib::VariantBase& parameter)
{
  std::cout << G_STRFUNC << " Parameter=" << parameter.print() << std::endl;
}

bool 
ScpApplication::first_time_start()
{
	std::cout << "First time start" << std::endl;
	
//	auto assistant = new ScpAssistant();
	
	add_window(m_assistant);	

	m_assistant.signal_apply().connect(sigc::mem_fun(*this,
		&ScpApplication::write_preferences));
	
	m_assistant.signal_apply().connect(sigc::mem_fun(*this,
		&ScpApplication::create_window));
	
	m_assistant.signal_cancel().connect(sigc::mem_fun(*this,
		&ScpApplication::on_action_quit));
	
	m_assistant.show();

	std::cout << "First time end" << std::endl;
	return true;
}

void
ScpApplication::write_preferences()
{
// dbtype	
	
	const Glib::ustring dbtype = m_assistant.get_dbtype();

	m_keyfile.set_string(ScpKeyfile::GROUP_CONNECTION,
						 ScpKeyfile::KEY_DBTYPE,
						 dbtype);

	if(dbtype == ScpKeyfile::DBTYPE_SQLITE3)
	{
		m_keyfile.set_string(ScpKeyfile::GROUP_CONNECTION,
							 ScpKeyfile::KEY_DBFILE,
							 m_assistant.get_dbfile());
	}
	else
	{
		m_keyfile.set_string(ScpKeyfile::GROUP_CONNECTION,
							 ScpKeyfile::KEY_SERVER,
							 m_assistant.get_server());
	
		m_keyfile.set_string(ScpKeyfile::GROUP_CONNECTION,
							 ScpKeyfile::KEY_USERNAME,
							 m_assistant.get_user());
	}
}


void 
ScpApplication::on_action_connect()
{
// Get password from user
	if(!m_refConnection){
		esteblish_connection_to_db();
	}
	else{
		if(m_refConnection->is_opened()){
			Gtk::MessageDialog dialog(*m_refWindow,
									"Connection already established",
									true,
									Gtk::MESSAGE_INFO,
									Gtk::BUTTONS_CLOSE,
									true);
			int res = dialog.run();
			switch(res){
				case Gtk::RESPONSE_CLOSE:
					break;
				default:
					;
			}
		}
		else{
			esteblish_connection_to_db();
		}
	}
}


void ScpApplication::on_action_disconnect()
{
	if(m_refConnection)
	{
		if(m_refConnection->is_opened())
		{
			m_refConnection->close();
		}
		else
		{
			Gtk::MessageDialog dialog(*m_refWindow,
									"Nothing to disconnect from",
									true,
									Gtk::MESSAGE_INFO,
									Gtk::BUTTONS_CLOSE,
									true);
			int res = dialog.run();
			switch(res){
				case Gtk::RESPONSE_CLOSE:
					break;
				default:
					;
			}
		}
	}
	else
	{
		Gtk::MessageDialog dialog(*m_refWindow,
								"Nothing to disconnect from",
								true,
								Gtk::MESSAGE_INFO,
								Gtk::BUTTONS_CLOSE,
								true);
		int res = dialog.run();
		switch(res){
			case Gtk::RESPONSE_CLOSE:
				break;
			default:
				;
		}
	}
				
}


void 
ScpApplication::esteblish_connection_to_db()
{


}


