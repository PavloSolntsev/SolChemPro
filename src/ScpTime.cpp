/*
 * ScpTime.cpp
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

#include "ScpTime.hpp"
#include <ctime>

ScpTime::ScpTime()
{
    m_timeval.assign_current_time();             
    m_datetime = Glib::DateTime::create_now_utc(m_timeval);
}

ScpTime::ScpTime(Glib::ustring str)
{
    this->set_string(str);
}

ScpTime::~ScpTime()
{

}

const Glib::ustring 
ScpTime::get_string()
{
    return m_timeval.as_iso8601();
}
        
void 
ScpTime::set_string(Glib::ustring str)
{
    m_timeval.assign_from_iso8601(str);
}

const Glib::ustring 
ScpTime::format(Glib::ustring format_str)
{
    return m_datetime.format(format_str);
}

ScpTime& 
ScpTime::operator=(const ScpTime &obj)
{
    this->m_timeval = obj.m_timeval;
    this->m_datetime = obj.m_datetime;
    return *this;
}
