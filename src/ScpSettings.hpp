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
#define DEFAULT_KEYFILE INIFILE 
#define DEFAULT_INI_DIR PACKAGE_TARNAME

/*! \class ScpSettings 
 *  \brief Class to read and write all settings for the program 
 * 
 *  The purpose of this class is to read and write settings information to the INI file.
 *  
 */
class ScpSettings {
    public:
        ScpSettings();
        ScpSettings(const ScpSettings&)=default;
        virtual ~ScpSettings();
        const Glib::KeyFile& get_keyfile();
        const Glib::ustring& get_filename();
        const Glib::ustring get_filepath();

/*	    const Glib::ustring GROUP_GENERAL     = "GENERAL";
	    const Glib::ustring GROUP_CONNECTION  = "CONNECTION";
                                 
	    const Glib::ustring KEY_STARTCHECK  = "START_CHECK";
	    const Glib::ustring KEY_DBTYPE      = "DBTYPE";
	    const Glib::ustring KEY_DBNAME      = "DBNAME";
	    const Glib::ustring KEY_SERVER      = "SERVER";
	    const Glib::ustring KEY_USERNAME    = "USERNAME";
	    const Glib::ustring KEY_DBFILE      = "DBFILE";
	    const Glib::ustring KEY_DBTYPE_ID   = "DBTYPE_ID";
    
        const Glib::ustring SQLITE     = "SQLite3";         
	    const Glib::ustring MYSQL      = "MySQL";
	    const Glib::ustring POSTGRESQL = "PostgreSQL";
  */     
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
     
        /* 
         * GET methods 
         * */
        bool                get_boolean(const Glib::ustring&, const Glib::ustring&);
        int                 get_integer(const Glib::ustring&, const Glib::ustring&);
        double              get_double(const Glib::ustring&, const Glib::ustring&);
        const Glib::ustring get_string(const Glib::ustring&, const Glib::ustring&);
        
        /* 
         * SET methods 
         * */
        void set_boolean(const Glib::ustring&, const Glib::ustring&, bool);
        void set_integer(const Glib::ustring&, const Glib::ustring&, int);
        void set_double(const Glib::ustring&, const Glib::ustring&, double);
        void set_string(const Glib::ustring&, const Glib::ustring&, const Glib::ustring& );
        
        void reset();

        bool file_exists();
        bool save_first_start(); /* This function create reccord about first start */
        bool first_start(); /* Check if first recor is present in INI file */
        bool create_ini_file(const Glib::RefPtr<Gio::File>& file); /*!< Create INI file */
        bool create_ini_file(); /*!< Create INI file */
        bool create_ini_dir(const Glib::RefPtr<Gio::File>& dir); /*!< Create directory for INI file */
        bool create_ini_dir(); /*!< Create directory for INI file */
        bool load_from_file(Glib::KeyFileFlags flags = Glib::KEY_FILE_NONE);
        bool save_to_file();
        explicit operator bool()const{return m_objectstate;}

    protected:

        Glib::KeyFile m_keyfile; /*!< Key file to store all settings */
        Glib::ustring m_keyfilename; /*!< name of the INI file */
//        Glib::ustring m_keyfilepath; /*!< full path of the INI file */
        Glib::RefPtr<Gio::File> m_refgfile; /*GFile object for INI file */

        bool m_objectstate; /*!< State of the object: true is good, false is bad */
        Error m_objerror; /*!< type of error, if any, for the object */
        void init();
};

#endif

