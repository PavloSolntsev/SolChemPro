/*
 * ScpProject.cpp      
 * 
 * Copyright (c) 2017 Pavlo Solntsev <pavlo.solntsev@gmail>
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

#include "ScpProject.hpp"

const Glib::ustring& 
ScpProject::get_name()const
{
    return m_name;
}

void
ScpProject::set_name(const Glib::ustring &name)
{
    m_name = name;
}

const Glib::ustring& 
ScpProject::get_description()const
{
    return m_description;
}

void
ScpProject::set_description(const Glib::ustring &descr)
{
    m_description = descr;
}

const long &
ScpProject::get_id()const
{
    return m_id;
}

void 
ScpProject::set_id(const long &id)
{
   m_id = id; 
}


