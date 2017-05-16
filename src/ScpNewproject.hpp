/*
 * ScpNewproject.hpp  
 * Copyright © 2017 Pavlo Solntsev <pavlo.solntsev@gmail.com>
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

#ifndef _SCP_NEWPROJECT_HPP
#define _SCP_NEWPROJECT_HPP

#include <gtkmm.h>

/*! \class ScpNewproject 
 *  \brief This class is responsible for getting new information from the user or modifying 
 *  the existing data  
 * 
 *  Detailed description     
 */
class ScpNewproject : public Gtk::Dialog
{
public:
    ScpNewproject(Gtk::Window &);
    virtual ~ScpNewproject();
    const Glib::ustring get_name()const;
    const Glib::ustring get_discription()const;
    const Glib::ustring get_id_as_string()const;
    const gulong get_id()const;

protected:
    Gtk::Label m_labelid; /*!< Label for ID field */
    Gtk::Entry m_entryid; /*!< Entry for ID field */
    Gtk::Label m_labelname; /*!< Label for Project name */
    Gtk::Label m_labeldiscription; /*!< Label for Project discription */
    Gtk::Entry m_entryname; /*!< Entry for Project name */
    Gtk::TextView m_textviewdiscr; /*!< TextView for discription */
    Gtk::ScrolledWindow m_scrollwin; /*!< Scrollwindow for discription textview */
    Gtk::Grid m_grid; /*!< Grid box for main contant */        
    Gtk::Button *m_buttonok; /*!< OK button */
    Gtk::Button *m_buttoncancel; /*!< CANCEL button */
};

#endif

