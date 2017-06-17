/*
 * ScpTable.hpp
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

#ifndef _SCP_TABLE_HPP
#define _SCP_TABLE_HPP

#include <glibmm/ustring.h>
#include <map>

/*! \brief Class to access table's columns. 
 *
 * Once instance of this class should be created and used to access table columns.
 * It hould be type safe.
 *
 * */
class ScpTable 
{
    public:
        ScpTable();
        ~ScpTable();
        enum class Tables {USERS, PROJECT};        
        enum class Users {ID, NAME};
        enum class Project {ID, NAME, DISCRIPTION};

        const Glib::ustring &get_name(const Users)const;
        const Glib::ustring &get_name(const Project)const;
        const Glib::ustring &get_table(const Tables)const;

    protected:
        std::map<Tables,Glib::ustring> m_tables;            
        std::map<Users,Glib::ustring> m_users;            
        std::map<Project,Glib::ustring> m_project;            
};


#endif

