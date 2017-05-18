/*
 * SolChemPro ScpSettings.hpp
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
 * */ 

#ifndef SCP_SETTINGS_HPP
#define SCP_SETTINGS_HPP
#include <libgdamm.h>
#include <config.h>
#include <giomm.h>
#define DEFAULT_KEYFILE "solchempro.ini"


/*! \class ScpSettings 
 *  \brief Class to read and write all settings for the program 
 * 
 *  The purpose of this class is to read and write settings information to the INI file.
 */
class ScpSettings {
    public:
        ScpSettings();
        ScpSettings(const ScpSettings&)=default;
        virtual ~ScpSettings();
        const Glib::KeyFile& get_keyfile();
        const Glib::ustring& get_filename();
        const Glib::ustring& get_filepath();

        struct Group {
	        const Glib::ustring GENERAL     = "GENERAL";
	        const Glib::ustring CONNECTION  = "CONNECTION";
        };

        struct Key {
	        const Glib::ustring STARTCHECK  = "START_CHECK";
	        const Glib::ustring DBTYPE      = "DBTYPE";
	        const Glib::ustring DBNAME      = "DBNAME";
	        const Glib::ustring SERVER      = "SERVER";
	        const Glib::ustring USERNAME    = "USERNAME";
	        const Glib::ustring DBFILE      = "DBFILE";
	        const Glib::ustring DBTYPE_ID   = "DBTYPE_ID";
        };
    
        struct DBType {
            const Glib::ustring SQLITE     = "SQLite3";         
	        const Glib::ustring MYSQL      = "MySQL";
	        const Glib::ustring POSTGRESQL = "PostgreSQL";
        };
       
        enum class Error {
            CLEAN = 0,
            NOT_SUPPORTED,
            EXISTS,
            CANCELLED,
            UNDEFINED,
            IS_DIRECTORY,
            FILENAME_TOO_LONG,
            LOAD_FILE,
            INIT
        };

        bool          get_boolean(const Group&, const Key&);
        int           get_integer(const Group&, const Key&);
        double        get_double(const Group&, const Key&);
        const Glib::ustring get_string(const Group&, const Key&);
        
        void set_boolean(const Group&, const Key&, bool);
        void set_integer(const Group&, const Key&, int);
        void set_double(const Group&, const Key&, double);
        void set_string(const Group&, const Key&, const Glib::ustring& );

        void reset();
        bool init(const Glib::ustring& filename = DEFAULT_KEYFILE);
        explicit operator bool()const{return m_objectstate;}
    protected:

        Glib::KeyFile m_keyfile; /*!< Key file to store all settings */
        Glib::ustring m_keyfilename; /*!< name of the INI file */
        Glib::ustring m_keyfilepath; /*!< full path of the INI file */
        bool m_objectstate; /*!< State of the object: true is good, false is bad */
        Error m_objerror; /*!< type of error, if any, for the object */
        bool create_ini_file(const Glib::RefPtr<Gio::File>& file); /*!< Create INI file */
        bool create_ini_dir(const Glib::RefPtr<Gio::File>& dir); /*!< Create directory and INI file */

};

#endif

