/* 
 * ScpTime.hpp 
 * Copyright (C) 2017 Pavlo solntsev <pavlo.solntsev@gmail.com>
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

#ifndef __SCP_TIME_HPP__
#define __SCP_TIME_HPP__

#include <libgdamm.h>

using namespace Gnome;

class ScpTime {
    public:
        ScpTime();
        ScpTime(Glib::ustring);
        ~ScpTime();
        void set_string(const Glib::ustring);
        const Glib::ustring get_string();
        const Glib::ustring format(Glib::ustring);
        ScpTime& operator=(const ScpTime &);
        
    protected:
        Glib::TimeVal m_timeval;
        Glib::DateTime m_datetime;
};  

#endif

