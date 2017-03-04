/* 
 * ScpMainwindow.hpp Copyright (C) 2017 <pavlo.solntsev@gmail.com>
 * 
 * This file is based on the example file from gtkmm-doc package
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

#ifndef SCP_MAINWINDOW_HPP_ 
#define SCP_MAINWINDOW_HPP_ 

#include <gtkmm.h>

class ScpMainwindow: public Gtk::ApplicationWindow
{
	public:
		explicit ScpMainwindow();
		
		void set_keyfilename(const Glib::ustring& );
		void set_keyfilename(const char *);
		void set_keyfilename(const Glib::RefPtr<Gio::File> );

	private:
		Gtk::Paned m_paned_main;
		Gtk::Paned m_paned_right;
		Gtk::Button m_button_new_project;
		Gtk::Button m_button_add_version;

		Gtk::HeaderBar m_headerbar;
		Gtk::ScrolledWindow m_scrolledwindow_project;
		Gtk::TreeView m_treeview_project;
		
		Gtk::Grid m_grid_sheet;
		Gtk::ActionBar m_actionbar_sheet;
		Gtk::ScrolledWindow m_scrolledwindow_sheet;
		Gtk::TreeView m_treeview_sheet;


		Gtk::Notebook m_notebook;
		Gtk::ScrolledWindow m_scrolledwindow_details;
		Gtk::ScrolledWindow m_scrolledwindow_log;
		Gtk::TextView m_textview_details;
		Gtk::TextView m_textview_log;


		void on_action_something();
		void on_action_close();
		void on_action_send_notification();
		void on_action_withdraw_notification();
		Glib::RefPtr<Gio::File> m_reffile;

};

#endif /* GTKMM_EXAMPLEWINDOW_H */
