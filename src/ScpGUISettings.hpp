/*
 * ScpGUISettings.hpp
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
 * 
 */

#ifndef _SCP_GUISETTINGS_HPP
#define _SCP_GUISETTINGS_HPP 

#include <libgdamm.h>
#include <gtkmm.h>



class ScpGUISettings final : public Gtk::Window {
    public:
        ScpGUISettings()=default;
        ScpGUISettings(BaseObjectType*,const Glib::RefPtr<Gtk::Builder>&);
        ~ScpGUISettings();
        ScpGUISettings(const ScpGUISettings&)=default; 

        enum DBType {
            NONE = 0,
            SQLITE,
            MYSQL,
            POSTGRESQL
        };

        struct ScpSettingsDialog {
            DBType m_dbtype;
            Glib::ustring m_dbname;
            Glib::ustring m_dbfile;
            Glib::ustring m_user;
            Glib::ustring m_server;
        };

        DBType get_dbtype();

/* SIGNALS */
        typedef sigc::signal<void,ScpSettingsDialog> type_signal_button_ok_clicked;
        type_signal_button_ok_clicked signal_button_ok_clicked();
/* End of signals */

        void on_button_ok_clicked();
        void on_button_cancel_clicked();

        void on_combo_dbtype_changed();
    private:
        type_signal_button_ok_clicked m_signal_new_project_button;
        
        class ModelColumn : public Gtk::TreeModel::ColumnRecord {
            public:
                ModelColumn(){
                    add(m_id);
                    add(m_name);
                }
                Gtk::TreeModelColumn<DBType> m_id;
                Gtk::TreeModelColumn<Glib::ustring> m_name;
        };

        ModelColumn m_columns;


        Glib::RefPtr<Gtk::Builder> m_refGlade;
        Gtk::ComboBox* m_refComboboxdb;
        Glib::RefPtr<Gtk::ListStore> m_refTreemodeldb;
        Gtk::Button* m_refButton_ok;
        Gtk::Button* m_refButton_cancel;
        Gtk::FileChooserButton* m_refFilechoosesqlite;


};

#endif

