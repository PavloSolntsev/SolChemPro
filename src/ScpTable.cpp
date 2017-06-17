/*
 * ScpTable.cpp
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
 * 
 */

#include "ScpTable.hpp"

ScpTable::ScpTable()
{
    m_tables.insert(std::make_pair<Tables,Glib::ustring>(Tables::USERS,"users"));
    m_tables.insert(std::make_pair<Tables,Glib::ustring>(Tables::PROJECT,"project"));

    m_users.insert(std::make_pair<Users,Glib::ustring>(Users::ID,"id"));
    m_users.insert(std::make_pair<Users,Glib::ustring>(Users::NAME,"name"));

    m_project.insert(std::make_pair<Project,Glib::ustring>(Project::ID,"id"));
    m_project.insert(std::make_pair<Project,Glib::ustring>(Project::NAME,"name"));
    m_project.insert(std::make_pair<Project,Glib::ustring>(Project::DISCRIPTION,"discription"));

}

ScpTable::~ScpTable()
{

}

const Glib::ustring & 
ScpTable::get_name(const Users key)const
{
   return m_users.at(key);
}

const Glib::ustring & 
ScpTable::get_name(const Project prj)const
{
    return m_project.at(prj);
}

const Glib::ustring &
ScpTable::get_table(const Tables tbl)const
{
    return m_tables.at(tbl);
}

