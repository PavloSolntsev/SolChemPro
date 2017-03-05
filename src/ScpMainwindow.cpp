/* 
 * ScpMainwindow.cpp Copyright (C) 2017 <pavlo.solntsev@gmail.com>
 * gtkmm example Copyright (C) 2002 gtkmm development team
 * 
 * This file is based on the example file from gtkmm-doc package
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

#include <iostream>

#include "ScpMainwindow.hpp" 
#include "ScpApplication.hpp"

ScpMainwindow::ScpMainwindow():
m_paned_main(Gtk::ORIENTATION_HORIZONTAL),
m_paned_right(Gtk::ORIENTATION_VERTICAL),
m_button_new_project("New project"),
m_button_add_version("Add Version")
{
	set_title("SolChemPro");
// Setup header bar
	m_headerbar.set_title(this->get_title());	
	m_headerbar.set_show_close_button(true);
	m_headerbar.add(m_button_new_project);

	this->set_titlebar(m_headerbar);		
// Setup main paned
	m_scrolledwindow_project.add(m_treeview_project);	
	m_paned_right.pack1(m_grid_sheet);
//	m_grid_sheet.set_hexpand(true);
	m_paned_right.pack2(m_notebook);
	m_notebook.append_page(m_scrolledwindow_details,"Details");
	m_notebook.append_page(m_scrolledwindow_log,"Log");

	m_scrolledwindow_details.add(m_textview_details);
	m_scrolledwindow_log.add(m_textview_log);

	m_grid_sheet.attach(m_actionbar_sheet,0,0,1,1);
//	m_actionbar_sheet.property_vexpand_set() = true;
	m_grid_sheet.attach(m_scrolledwindow_sheet,0,1,1,1);
	m_scrolledwindow_sheet.add(m_treeview_sheet);	
	m_scrolledwindow_sheet.set_hexpand(true);
	m_scrolledwindow_sheet.set_vexpand(true);
	
	m_paned_main.pack1(m_scrolledwindow_project);
	m_paned_main.pack2(m_paned_right);
	
	m_actionbar_sheet.add(m_button_add_version);

	this->add(m_paned_main);

  // We can use add_action because Gtk::ApplicationWindow derives from ActionMap.
  // This Action Map uses a "win." prefix for the actions.
  // Therefore, for instance, "win.new", is used in ExampleApplication::on_startup()
  // to layout the menu.
/*	add_action("connect",
		sigc::mem_fun(*this, &ScpApplication::on_action_connect) );
	add_action("disconnect",
		sigc::mem_fun(*this, &ScpApplication::on_action_disconnect) );*/
	add_action("send-note",
		sigc::mem_fun(*this, &ScpMainwindow::on_action_send_notification) );
	add_action("withdraw-note",
		sigc::mem_fun(*this, &ScpMainwindow::on_action_withdraw_notification) );

	



	show_all_children();
}

void ScpMainwindow::on_action_send_notification()
{
  std::cout << G_STRFUNC << std::endl;

  auto note = Gio::Notification::create("Unimportant message!");
  note->set_body("Notification from " + Glib::get_application_name());
  note->add_button("Print", "app.print", Glib::ustring("Hello, world!"));
  note->add_button("Quit Application", "app.quit");
  get_application()->send_notification("note", note);
}

void ScpMainwindow::on_action_withdraw_notification()
{
  std::cout << G_STRFUNC << std::endl;

  get_application()->withdraw_notification("note");
}

void
ScpMainwindow::set_keyfilename(const Glib::RefPtr<Gio::File> file)
{
	if(file->query_exists())
		m_reffile = file;	
	else
		m_reffile = file;
}





