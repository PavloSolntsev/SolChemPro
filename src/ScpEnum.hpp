/*
 * SolChemPro.hpp
 *
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

#ifndef _SCP_ENUM_HPP
#define _SCP_ENUM_HPP

namespace Scp {
    enum DatabaseType {
        UNDEFINED = 0,
        SQLITE3,
        MYSQL,
        POSTGRESQL
    };
    
    enum Table {
        TABLE_USER
    };    

}



#endif

