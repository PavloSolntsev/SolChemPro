/*
 * ScpGUISettings.cpp
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

#include "ScpGUISettings.hpp"
#include <iostream>

ScpGUISettings::ScpGUISettings(BaseObjectType* obj, const Glib::RefPtr<Gtk::Builder>& builder):
Gtk::Window(obj),
m_refGlade(builder),
m_refComboboxdb(nullptr),
m_refButton_ok(nullptr),
m_refButton_cancel(nullptr)
{
    builder->get_widget("filechoose_sqlite",m_refFilechoosesqlite);
    builder->get_widget("combobox_dbtype",m_refComboboxdb);
    builder->get_widget("button_ok",m_refButton_ok);
    builder->get_widget("button_cancel",m_refButton_cancel);

    m_refTreemodeldb = Gtk::ListStore::create(m_columns);
    m_refComboboxdb->set_model(m_refTreemodeldb);

    Gtk::TreeModel::Row row = *(m_refTreemodeldb->append());

    row[m_columns.m_id] = NONE; 
    row[m_columns.m_name] = "<Select database>";
    m_refComboboxdb->set_active(row);

    row = *(m_refTreemodeldb->append());

    row[m_columns.m_id] = SQLITE; 
    row[m_columns.m_name] = "SQLite3";
    
    row = *(m_refTreemodeldb->append());

    row[m_columns.m_id] = MYSQL; 
    row[m_columns.m_name] = "MySQL";

    row = *(m_refTreemodeldb->append());

    row[m_columns.m_id] = POSTGRESQL; 
    row[m_columns.m_name] = "PostgreSQL";

    m_refComboboxdb->pack_start(m_columns.m_name);
    
    m_refButton_ok->signal_clicked().connect(
            sigc::mem_fun(*this,&ScpGUISettings::on_button_ok_clicked));
    m_refButton_cancel->signal_clicked().connect(
            sigc::mem_fun(*this,&ScpGUISettings::on_button_cancel_clicked));
    
//    m_refComboboxdb->signal_changed().connect(
//            sigc::mem_fun(*this,&ScpGUISettings::on_combo_dbtype_changed));

    show_all_children();
}

ScpGUISettings::~ScpGUISettings()
{

}


ScpGUISettings::DBType 
ScpGUISettings::get_dbtype()
{
    Gtk::TreeModel::iterator iter = m_refComboboxdb->get_active();
    if(iter)
    {
        Gtk::TreeModel::Row row = *iter;
        if(row)
        {
            DBType id = row[m_columns.m_id];
            Glib::ustring name = row[m_columns.m_name];
            std::cout << " ID=" << id << ", name=" << name << std::endl;
            return id;
        }
    }else
        std::cout << "invalid iter" << std::endl; 

}

void
ScpGUISettings::on_combo_dbtype_changed()
{
    get_dbtype();
}

ScpGUISettings::type_signal_button_ok_clicked
ScpGUISettings::signal_button_ok_clicked()
{
    return m_signal_new_project_button;
}

void
ScpGUISettings::on_button_ok_clicked()
{
    ScpSettingsDialog settings_data;

    settings_data.m_dbtype = get_dbtype();

    m_signal_new_project_button.emit(settings_data);
    this->hide();
}

void 
ScpGUISettings::on_button_cancel_clicked()
{
    this->hide();
}

