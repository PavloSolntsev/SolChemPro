/* 
 * ScpAssistant.hpp Copyright (C) 2017 <pavlo.solntsev@gmail.com>
 * 
 * This program is free software; you can redistribute it and/or modifyi
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
 *
 * */

#ifndef _SCP_ASSISTANT_HPP_
#define _SCP_ASSISTANT_HPP_

#include <gtkmm.h>
#include <iostream>
#include <map>

class ScpAssistant : public Gtk::Assistant
{
	public:
		ScpAssistant();
		virtual ~ScpAssistant();

		static Glib::RefPtr<ScpAssistant> create();

		void on_assistant_close();
		void on_assistant_cancel();
		void on_assistant_apply();
		void on_assistant_prepare(Gtk::Widget *);
		void on_combobox_page2_changed();
		void on_server_enrty_changed();
		void on_password_enrty_changed();
		void on_entries_server_password_changed();
		Glib::ustring &get_dbtype();
		Glib::ustring get_dbfile();
		Glib::ustring get_server();
		Glib::ustring get_user();

	private:
		Gtk::Label m_label_page1;
		Gtk::Label m_label_page2;
		Gtk::Grid m_grid_page2;
		Gtk::ComboBox m_combobox_page2;
		
		// page3 for SQLite3 
		Gtk::FileChooserButton m_filechbutton_page3;
		// page4 Server database 
		Gtk::Grid m_grid_page4;
		Gtk::Label m_label_server_page4;
		Gtk::Label m_label_username_page4;
		Gtk::Label m_label_password_page4;

		Gtk::Entry m_entry_server_page4;
		Gtk::Entry m_entry_password_page4;
		Gtk::Entry m_entry_username_page4;
		// Page 5

		class ComboModelPage2 : public Gtk::TreeModelColumnRecord
		{
			public:
				ComboModelPage2(){
					add(m_id);
					add(m_name);
				}

				Gtk::TreeModelColumn<int> m_id;
				Gtk::TreeModelColumn<Glib::ustring> m_name;
		}model_columns_page2;

		Glib::RefPtr<Gtk::ListStore> m_refmodel_page2;	
		std::map<int,Glib::ustring> m_vendors_page2;
		
		void print_status();
		
		int m_server_id;
};





#endif

