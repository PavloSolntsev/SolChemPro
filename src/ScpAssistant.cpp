/* 
 * ScpAssistant.cpp Copyright (C) 2017 <pavlo.solntsev@gmail.com>
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

#include "ScpAssistant.hpp"

ScpAssistant::ScpAssistant():
	m_label_page1(
		Glib::ustring("Welcom to SolChemPro. We will guid you throug step-by-step\n" 
		"installation. You will be asked to provide information about \n"
		"you dadabase configuration. Don't worry it is easy. \n"
		"Contact Pavlo Solntsev <pavlo.solntsev@gmail.com>")),
	m_label_page2(Glib::ustring("Provide what databse you want to use for the data storage\n"
			"SQLite3 is designed only for single user. If you have \n"
			"more then 1 user, you should consider other databases\n"
			"with the approprite server configuration"))
{
	set_title("SolChemPro Assistant");
	set_border_width(12);

	append_page(m_label_page1);
	append_page(m_grid_page2);
	append_page(m_filechbutton_page3);
	append_page(m_grid_page4);

	set_page_title(*get_nth_page(0),"Welcome!");
	set_page_title(*get_nth_page(1),"Database Selection");
	set_page_title(*get_nth_page(2),"SQLite database");
	set_page_title(*get_nth_page(3),"Multi-user databases");

	set_page_complete(m_label_page1,true);
	set_page_complete(m_grid_page2, true);
	set_page_complete(m_filechbutton_page3, false);
	set_page_complete(m_grid_page4, false);

	set_page_type(m_label_page1,Gtk::ASSISTANT_PAGE_INTRO);
	set_page_type(m_grid_page2,Gtk::ASSISTANT_PAGE_CONTENT);
	set_page_type(m_filechbutton_page3,Gtk::ASSISTANT_PAGE_CONTENT);
	set_page_type(m_grid_page4,Gtk::ASSISTANT_PAGE_CONFIRM);

	signal_apply().connect(sigc::mem_fun(*this,
			    &ScpAssistant::on_assistant_apply));
	signal_cancel().connect(sigc::mem_fun(*this,
				&ScpAssistant::on_assistant_cancel));
    signal_close().connect(sigc::mem_fun(*this,
				&ScpAssistant::on_assistant_close));
	signal_prepare().connect(sigc::mem_fun(*this,
				&ScpAssistant::on_assistant_prepare));
// Page 2 	
	m_vendors_page2.insert(std::pair<int,Glib::ustring>(1,"SQLite3"));
	m_vendors_page2.insert(std::pair<int,Glib::ustring>(2,"MySQL"));
	m_vendors_page2.insert(std::pair<int,Glib::ustring>(3,"PostgreSQL"));

	m_refmodel_page2 = Gtk::ListStore::create(model_columns_page2);
	m_combobox_page2.set_model(m_refmodel_page2);

	Gtk::TreeModel::Row row;
	
	for(auto &i : m_vendors_page2)
	{
		row = *(m_refmodel_page2->append());
		row[model_columns_page2.m_id] = i.first;
		row[model_columns_page2.m_name] = i.second;
		if(i.first == 1)
		{
			m_combobox_page2.set_active(row);
			m_server_id = 1;
		}
	}
	
	m_combobox_page2.signal_changed().connect(sigc::mem_fun(*this,
				&ScpAssistant::on_combobox_page2_changed));

	m_combobox_page2.pack_start(model_columns_page2.m_name);

	m_grid_page2.attach(m_label_page2,0,0,1,1);
	m_grid_page2.attach(m_combobox_page2,0,1,1,1);
	m_label_page2.set_hexpand(true);
	m_label_page2.set_vexpand(true);
	m_label_page2.set_halign(Gtk::ALIGN_CENTER);
	m_label_page2.set_valign(Gtk::ALIGN_CENTER);
	m_combobox_page2.set_hexpand(true);
	m_combobox_page2.set_vexpand(true);
	m_combobox_page2.set_halign(Gtk::ALIGN_CENTER);
	m_combobox_page2.set_valign(Gtk::ALIGN_CENTER);

	m_grid_page2.set_row_spacing(10);
// Page 3
	m_filechbutton_page3.set_hexpand(true);
	m_filechbutton_page3.set_vexpand(true);
	m_filechbutton_page3.set_halign(Gtk::ALIGN_CENTER);
	m_filechbutton_page3.set_valign(Gtk::ALIGN_CENTER);
// Page 4
	m_grid_page4.attach(m_label_server_page4,0,0,1,1);
	m_label_server_page4.set_hexpand(true);
	m_label_server_page4.set_vexpand(true);
	m_label_server_page4.set_halign(Gtk::ALIGN_END);
	m_label_server_page4.set_valign(Gtk::ALIGN_END);

	m_grid_page4.attach(m_label_username_page4,0,1,1,1);
	m_label_username_page4.set_hexpand(true);
	m_label_username_page4.set_halign(Gtk::ALIGN_END);
	m_label_username_page4.set_valign(Gtk::ALIGN_END);

	m_grid_page4.attach(m_label_password_page4,0,2,1,1);
	m_label_password_page4.set_hexpand(true);
	m_label_password_page4.set_vexpand(true);
	m_label_password_page4.set_halign(Gtk::ALIGN_END);
	m_label_password_page4.set_valign(Gtk::ALIGN_START);

	m_grid_page4.attach(m_entry_server_page4,1,0,1,1);
	m_entry_server_page4.set_hexpand(true);
	m_entry_server_page4.set_vexpand(true);
	m_entry_server_page4.set_halign(Gtk::ALIGN_START);
	m_entry_server_page4.set_valign(Gtk::ALIGN_END);

	m_grid_page4.attach(m_entry_username_page4,1,1,1,1);
	m_entry_username_page4.set_hexpand(true);
	m_entry_username_page4.set_halign(Gtk::ALIGN_START);
	m_entry_username_page4.set_valign(Gtk::ALIGN_END);

	m_grid_page4.attach(m_entry_password_page4,1,2,1,1);
	m_entry_password_page4.set_hexpand(true);
	m_entry_password_page4.set_vexpand(true);
	m_entry_password_page4.set_halign(Gtk::ALIGN_START);
	m_entry_password_page4.set_valign(Gtk::ALIGN_START);

	m_grid_page4.set_row_spacing(10);	
	m_grid_page4.set_column_spacing(10);	
	m_label_server_page4.set_text("Database server");
	m_label_password_page4.set_text("Password");
	m_label_username_page4.set_text("Username");
	m_entry_password_page4.set_visibility(false);	
	m_entry_password_page4.set_invisible_char('*');

	m_entry_server_page4.signal_changed().connect(sigc::mem_fun(*this,
				&ScpAssistant::on_entries_server_password_changed));
	
	m_entry_password_page4.signal_changed().connect(sigc::mem_fun(*this,
				&ScpAssistant::on_entries_server_password_changed));
// page 5
	show_all_children();
}

ScpAssistant::~ScpAssistant()
{


}

Glib::RefPtr<ScpAssistant> 
ScpAssistant::create()
{
	return Glib::RefPtr<ScpAssistant>(new ScpAssistant());
}


void
ScpAssistant::on_assistant_apply()
{
	std::cout << "Apply was clicked";
	print_status();
}

void 
ScpAssistant::on_assistant_cancel()
{
	std::cout << "Cancel was clicked";
	print_status();
	hide();
}

void
ScpAssistant::on_assistant_close()
{
	std::cout << "Assistant was closed";
    print_status();
	hide();
}

void
ScpAssistant::on_assistant_prepare(Gtk::Widget *widget)
{
	set_title(Glib::ustring::compose("Gtk::Assistant example (Page %1 of %2)",
	     get_current_page() + 1, get_n_pages()));

	// Settings for page 2
	if(get_current_page() == 2 && m_server_id != 1)
		next_page();
}

void
ScpAssistant::print_status()
{
//	std::cout << ", entry contents: \"" << m_entry.get_text()
//	      << "\", checkbutton status: " << m_check.get_active() << std::endl;
}

void
ScpAssistant::on_combobox_page2_changed()
{
	Gtk::TreeModel::iterator it = m_combobox_page2.get_active();

	if(it)
	{
		Gtk::TreeModel::Row row = *it;

		m_server_id = row[model_columns_page2.m_id]; 			
	
	std::cout << "Selected id item is " << m_server_id 
		<< " Name: " << m_vendors_page2.at(m_server_id) << std::endl;
	}
}

void
ScpAssistant::on_entries_server_password_changed()
{
	if(	m_entry_password_page4.get_text_length() > 0 && 
		m_entry_server_page4.get_text_length() > 0 &&
		m_entry_username_page4.get_text_length() > 0)
	{
		set_page_complete(m_grid_page4,true);
	}
	else
	{
		set_page_complete(m_grid_page4,false);
	}
}

Glib::ustring& 
ScpAssistant::get_dbtype()
{
	return m_vendors_page2.at(m_server_id);
}

Glib::ustring
ScpAssistant::get_dbfile()
{
	return m_filechbutton_page3.get_filename();
}

Glib::ustring
ScpAssistant::get_server()
{
	return m_entry_server_page4.get_text();
}

Glib::ustring
ScpAssistant::get_user()
{
	return m_entry_username_page4.get_text(); 
}



