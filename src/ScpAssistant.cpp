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

enum PAGES {
	LAST = -1,
	WELCOME = 0,
	DBSELECTION,

};


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
	append_page(m_grid_page3);
	append_page(m_grid_page4);	
	append_page(m_label_confirm);

	set_page_title(*get_nth_page(0),"Welcome!");
	set_page_title(*get_nth_page(1),"Database Selection");
	set_page_title(*get_nth_page(2),"SQLite database");
	set_page_title(*get_nth_page(3),"Multi-user databases");
	set_page_title(*get_nth_page(4),"Summary");

	set_page_complete(m_label_page1,true);
	set_page_complete(m_grid_page2, true);
	set_page_complete(m_grid_page3, false);
	set_page_complete(m_grid_page4, false);
	set_page_complete(m_label_confirm, false);

	set_page_type(m_label_page1,   Gtk ::ASSISTANT_PAGE_INTRO   );
	set_page_type(m_grid_page2,    Gtk ::ASSISTANT_PAGE_CONTENT );
	set_page_type(m_grid_page3,    Gtk ::ASSISTANT_PAGE_CONTENT );
	set_page_type(m_grid_page4,    Gtk ::ASSISTANT_PAGE_CONTENT );
	set_page_type(m_label_confirm, Gtk ::ASSISTANT_PAGE_CONFIRM );

	signal_apply().connect(sigc::mem_fun(*this,
			    &ScpAssistant::on_assistant_apply));
	signal_cancel().connect(sigc::mem_fun(*this,
				&ScpAssistant::on_assistant_cancel));
    signal_close().connect(sigc::mem_fun(*this,
				&ScpAssistant::on_assistant_close));
	signal_prepare().connect(sigc::mem_fun(*this,
				&ScpAssistant::on_assistant_prepare));
// Page 2 	
	m_vendors_page2.insert(std::pair<Scp::DatabaseType,Glib::ustring>(Scp::UNDEFINED,
                                                                      "<Select Item>"));
	m_vendors_page2.insert(std::pair<Scp::DatabaseType,Glib::ustring>(Scp::SQLITE3,
                                                                      "SQLite3"));
	m_vendors_page2.insert(std::pair<Scp::DatabaseType,Glib::ustring>(Scp::MYSQL,
                                                                      "MySQL"));
	m_vendors_page2.insert(std::pair<Scp::DatabaseType,Glib::ustring>(Scp::POSTGRESQL,
                                                                      "PostgreSQL"));

	m_refmodel_page2 = Gtk::ListStore::create(model_columns_page2);
	m_combobox_page2.set_model(m_refmodel_page2);

	Gtk::TreeModel::Row row;
	
	for(auto &i : m_vendors_page2)
	{
		row = *(m_refmodel_page2->append());
		row[model_columns_page2.m_id] = i.first;
		row[model_columns_page2.m_name] = i.second;
		if(i.first == Scp::UNDEFINED)
		{
			m_combobox_page2.set_active(row);
			m_server_id = Scp::UNDEFINED;
		}
	}
	
	m_combobox_page2.signal_changed().connect(sigc::mem_fun(*this,
				&ScpAssistant::on_combobox_page2_changed));

	m_filechbutton_page3.signal_file_set().connect(sigc::mem_fun(*this,
				&ScpAssistant::on_file_set_page3_changed));


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
	m_grid_page3.attach(m_label_page3,0,0,1,1);
	m_filechbutton_page3.set_hexpand(true);
	m_filechbutton_page3.set_vexpand(true);
	m_filechbutton_page3.set_halign(Gtk::ALIGN_CENTER);
	m_filechbutton_page3.set_valign(Gtk::ALIGN_END);
	
	m_grid_page3.attach(m_filechbutton_page3,0,1,1,1);
	m_filechbutton_page3.set_hexpand(true);
//	m_filechbutton_page3.set_vexpand(true);
	m_filechbutton_page3.set_halign(Gtk::ALIGN_CENTER);
	m_filechbutton_page3.set_valign(Gtk::ALIGN_END);
	
	m_grid_page3.attach(m_checkbutton_connect_page3,0,2,1,1);
	m_checkbutton_connect_page3.set_hexpand(true);
	m_checkbutton_connect_page3.set_vexpand(true);
	m_checkbutton_connect_page3.set_halign(Gtk::ALIGN_CENTER);
	m_checkbutton_connect_page3.set_valign(Gtk::ALIGN_START);

	m_checkbutton_connect_page3.set_label("Auto-connect?");
	m_grid_page3.set_row_spacing(10);	
	m_grid_page3.set_column_spacing(10);	
	m_label_page3.set_text("Please skeep this step if you shose non SQLite3 Database");
// Page 4
	m_grid_page4.attach(m_label_massage_page4,0,0,2,1);
	m_label_massage_page4.set_hexpand(true);
	m_label_massage_page4.set_vexpand(true);
	m_label_massage_page4.set_halign(Gtk::ALIGN_CENTER);
	m_label_massage_page4.set_valign(Gtk::ALIGN_END);
		
	m_grid_page4.attach(m_label_server_page4,0,1,1,1);
	m_label_server_page4.set_hexpand(true);
	m_label_server_page4.set_vexpand(true);
	m_label_server_page4.set_halign(Gtk::ALIGN_END);
	m_label_server_page4.set_valign(Gtk::ALIGN_END);

	m_grid_page4.attach(m_label_dbname_page4,0,2,1,1);
	m_label_dbname_page4.set_hexpand(true);
	m_label_dbname_page4.set_halign(Gtk::ALIGN_END);
	m_label_dbname_page4.set_valign(Gtk::ALIGN_START);

	m_grid_page4.attach(m_label_username_page4,0,3,1,1);
	m_label_username_page4.set_hexpand(true);
//	m_label_username_page4.set_vexpand(true);
	m_label_username_page4.set_halign(Gtk::ALIGN_END);
	m_label_username_page4.set_valign(Gtk::ALIGN_START);

	m_grid_page4.attach(m_entry_server_page4,1,1,1,1);
	m_entry_server_page4.set_hexpand(true);
	m_entry_server_page4.set_vexpand(true);
	m_entry_server_page4.set_halign(Gtk::ALIGN_START);
	m_entry_server_page4.set_valign(Gtk::ALIGN_END);

	m_grid_page4.attach(m_entry_dbname_page4,1,2,1,1);
	m_entry_dbname_page4.set_hexpand(true);
	m_entry_dbname_page4.set_halign(Gtk::ALIGN_START);
	m_entry_dbname_page4.set_valign(Gtk::ALIGN_START);

	m_grid_page4.attach(m_entry_username_page4,1,3,1,1);
	m_entry_username_page4.set_hexpand(true);
//	m_entry_username_page4.set_vexpand(true);
	m_entry_username_page4.set_halign(Gtk::ALIGN_START);
	m_entry_username_page4.set_valign(Gtk::ALIGN_START);

	m_grid_page4.attach(m_checkbutton_connect_page4,1,4,1,1);
	m_checkbutton_connect_page4.set_hexpand(true);
	m_checkbutton_connect_page4.set_vexpand(true);
	m_checkbutton_connect_page4.set_halign(Gtk::ALIGN_START);
	m_checkbutton_connect_page4.set_valign(Gtk::ALIGN_START);

	m_grid_page4.set_row_spacing(10);	
	m_grid_page4.set_column_spacing(10);	
	m_label_server_page4.set_text("Database server");
	m_label_dbname_page4.set_text("Database name");
	m_label_username_page4.set_text("Username");
	m_label_massage_page4.set_text("Skip this step if you chose SQLite3");
	m_checkbutton_connect_page4.set_label("Auto-connect?");
	m_entry_dbname_page4.set_editable(false);
	m_entry_server_page4.set_editable(false);
	m_entry_username_page4.set_editable(false);

	m_entry_server_page4.signal_changed().connect(sigc::mem_fun(*this,
				&ScpAssistant::on_entries_server_dbname_changed));
	
	m_entry_dbname_page4.signal_changed().connect(sigc::mem_fun(*this,
				&ScpAssistant::on_entries_server_dbname_changed));
	
	m_entry_username_page4.signal_changed().connect(sigc::mem_fun(*this,
				&ScpAssistant::on_entries_server_dbname_changed));
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
	std::cout << "Current page = " << get_current_page() << std::endl;

	set_title(Glib::ustring::compose("Gtk::Assistant example (Page %1 of %2)",
	     get_current_page() + 1, get_n_pages()));

    if(get_current_page() == 2 && m_server_id == Scp::SQLITE3)
    {
		set_page_complete(m_grid_page4,true);
    }


	// Settings for page 5(Last page)
	if((get_current_page()+1) == get_n_pages())
	{
        Glib::ustring buffer; 
       
        buffer = Glib::ustring::compose("You will be using %1 database\n",
                m_vendors_page2.at(m_server_id));

        if(m_server_id == Scp::SQLITE3)
        {
            buffer += Glib::ustring::compose("Database will be taken from file %1\n",
                    Glib::path_get_basename(m_filechbutton_page3.get_filename()));
                    
            buffer += Glib::ustring::compose("DB folder %1\n",
                    Glib::path_get_dirname(m_filechbutton_page3.get_filename()));
        }
        else
        {
            buffer += Glib::ustring::compose("Server %1\n",m_entry_server_page4.get_text());
            buffer += Glib::ustring::compose("DB name %1\n",m_entry_dbname_page4.get_text());
            buffer += Glib::ustring::compose("User name %1\n",m_entry_username_page4.get_text());
        
        }

        m_label_confirm.set_text(buffer);
	    set_page_complete(m_label_confirm,true);
        
	}
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

	set_page_complete(m_grid_page3,false);
	set_page_complete(m_grid_page4,false);
	set_page_complete(m_label_confirm,false);

	if(m_server_id != Scp::SQLITE3)/* Insert SQLite3 db selection table */
	{
		m_filechbutton_page3.set_sensitive(false);
		m_checkbutton_connect_page3.set_sensitive(false);
		set_page_complete(m_grid_page3,true);
		m_entry_dbname_page4.set_editable(true);
		m_entry_server_page4.set_editable(true);
		m_entry_username_page4.set_editable(true);
	}
	else
	{
		// DB is SQLite3
		std::cout << "Applying changes for SQLite3" << std::endl;
		m_filechbutton_page3.set_sensitive(true);
		m_checkbutton_connect_page3.set_sensitive(true);
//		set_page_complete(m_grid_page4,true);
		m_entry_dbname_page4.set_editable(false);
		m_entry_server_page4.set_editable(false);
		m_entry_username_page4.set_editable(false);
	}
}

void
ScpAssistant::on_entries_server_dbname_changed()
{
	if(	m_entry_dbname_page4.get_text_length() > 0 && 
		m_entry_server_page4.get_text_length() > 0 &&
		m_entry_username_page4.get_text_length() > 0 &&
		m_server_id != Scp::SQLITE3)
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

void
ScpAssistant::on_file_set_page3_changed()
{
	set_page_complete(m_grid_page3,true);

}


Scp::DatabaseType 
ScpAssistant::get_server_id()
{
    return m_server_id;
}



