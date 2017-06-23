/* 
 * ScpKeyfile.hpp Copyright (C) 2017 <pavlo.solntsev@gmail.com>
 * 
 * This program is free software; you can redistribute it and/or modifyi
 * it under the terms of the GNU General Public License version 3
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * */

#ifndef _SCP_KEYFILE_HPP
#define _SCP_KEYFILE_HPP

/*! \class ScpKeyfile 
 *  \brief Class to work with keyfile in a conveient way
 * 
 *  This class will serve as a from interface for keyfile. It is derived from 
 *	the Glib::Keyfile and thus use all its properties and inherent its interface.
 *
 */
#include <glibmm/ustring.h>

namespace ScpKeyfile
{
	const Glib::ustring GROUP_GENERAL     = "GENERAL";
	const Glib::ustring GROUP_CONNECTION  = "CONNECTION";

	const Glib::ustring KEY_STARTCHECK    = "START_CHECK";
	const Glib::ustring KEY_DBTYPE_STR     = "DBTYPE_STR";
	const Glib::ustring KEY_DBNAME        = "DBNAME";
	const Glib::ustring KEY_SERVER        = "SERVER";
	const Glib::ustring KEY_USERNAME      = "USERNAME";
	const Glib::ustring KEY_DBFILE        = "DBFILE";
	const Glib::ustring KEY_DBTYPE_ID     = "DBTYPE_ID";
	const Glib::ustring KEY_OPTIONS       = "OPTIONS";

	const Glib::ustring DBTYPE_SQLITE3    = "SQLite3";
	const Glib::ustring DBTYPE_MYSQL      = "MySQL";
	const Glib::ustring DBTYPE_POSTGRESQL = "PostgreSQL";
}

#endif

