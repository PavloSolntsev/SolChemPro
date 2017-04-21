/*
 * ScpNewproject.cpp
 * Copyright (C) 2017 Pavlo Solntsev <pavlo.solntsev@gmail.com>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "ScpNewproject.hpp"
#include <string>

ScpNewproject::ScpNewproject(Gtk::Window &parent):
    Gtk::Dialog("New Project Initialization",parent,true),
    m_labelid("Project ID"),
    m_labelname("Project name"),
    m_labeldiscription("Discription")
{
    auto pbox = this->get_content_area();
    auto pbuttonbox = this->get_action_area();

    if(!pbox || !pbuttonbox)
        return;

    set_default_size(600,400);
    pbox->set_border_width(8);
    
    m_scrollwin.add(m_textviewdiscr);
    
    m_scrollwin.set_policy(Gtk::POLICY_AUTOMATIC,Gtk::POLICY_AUTOMATIC);

    m_grid.set_row_spacing(5);
    m_grid.set_column_spacing(3);

    m_grid.attach(m_labelid,0,0,1,1);
    m_grid.attach(m_entryid,1,0,1,1);

    m_grid.attach(m_labelname,0,1,1,1);
    m_labeldiscription.set_valign(Gtk::ALIGN_START);
    m_labeldiscription.set_vexpand(false);
    m_labeldiscription.set_hexpand(false);
   
    m_grid.attach(m_entryname,1,1,1,1);
    m_grid.attach(m_labeldiscription,0,2,1,1);
    m_grid.attach(m_scrollwin,1,2,1,1);
    m_scrollwin.set_halign(Gtk::ALIGN_FILL);
    m_scrollwin.set_valign(Gtk::ALIGN_FILL);
    m_scrollwin.set_border_width(3);
 //   m_scrollwin.set_hexpand(true);
 //   m_scrollwin.set_vexpand(true);
    m_textviewdiscr.set_hexpand(true);
    m_textviewdiscr.set_vexpand(true);

    pbox->add(m_grid);

    pbuttonbox->set_layout(Gtk::BUTTONBOX_SPREAD);
    pbuttonbox->set_spacing(3);
    
    m_buttonok = add_button("_OK",Gtk::RESPONSE_OK);
    m_buttoncancel = add_button("_Cancel",Gtk::RESPONSE_CANCEL);
    if(!m_buttonok || !m_buttoncancel)
        return ;

    show_all_children();
}

ScpNewproject::~ScpNewproject()
{
}

const Glib::ustring 
ScpNewproject::get_name()const
{
    return m_entryname.get_text();
}
const Glib::ustring 
ScpNewproject::get_discription()const
{
    return m_textviewdiscr.get_buffer()->get_text();
}

const Glib::ustring 
ScpNewproject::get_id_as_string()const
{
    return m_entryid.get_text();
}

const long
ScpNewproject::get_id()const
{
   return std::stol(m_entryid.get_text().c_str()); 
}





