/*
 * SolChemPro ScpSettings.cpp
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
 * */ 
#include "ScpSettings.hpp"
#include <iostream>

ScpSettings::ScpSettings():
    m_keyfilename(DEFAULT_KEYFILE),
    m_objectstate(true)
{
    init();
} /* End of constructor */

ScpSettings::~ScpSettings(){
}

const 
Glib::ustring& ScpSettings::get_filename()
{
    return m_keyfilename;
}

const 
Glib::ustring& ScpSettings::get_filepath()
{
    return m_keyfilepath;
}

const 
Glib::KeyFile& ScpSettings::get_keyfile()
{
    return m_keyfile;
}

bool
ScpSettings::get_boolean(const Group& group, const Key& key)
{
    return get_boolean(group, key);
};

int
ScpSettings::get_integer(const Group& group, const Key& key)
{
    return get_integer(group, key);
};

double
ScpSettings::get_double(const Group& group, const Key& key)
{
    return get_double(group, key);
};

const Glib::ustring 
ScpSettings::get_string(const Group& group, const Key& key)
{
    return get_string(group, key);
};


void
ScpSettings::set_boolean(const Group& group, const Key& key, bool val)
{
    return set_boolean(group, key, val);
};

void
ScpSettings::set_integer(const Group& group, const Key& key, int val)
{
    return set_integer(group, key, val);
};

void
ScpSettings::set_double(const Group& group, const Key& key, double val)
{
    return set_double(group, key, val);
};

void 
ScpSettings::set_string(const Group& group, const Key& key, const Glib::ustring& val)
{
    return set_string(group, key, val);
};


void 
ScpSettings::reset()
{
    m_objectstate = true;
    m_objerror = Error::CLEAN;

}

bool
ScpSettings::init(const Glib::ustring& filename)
{
    m_keyfilepath = Glib::build_filename(Glib::get_user_config_dir(),PACKAGE_TARNAME);
    m_keyfilepath = Glib::build_filename(m_keyfilepath,m_keyfilename);	
	
    auto GFileini = Gio::File::create_for_path(m_keyfilepath);
	
	auto parentdir = GFileini->get_parent();
    
    if(create_ini_dir(parentdir)){
       if(create_ini_file(GFileini))
       {
            try {
                m_keyfile.load_from_file(m_keyfilepath);
                return true;
            }catch(const Glib::FileError& fe) {
			    std::cerr << "Error reading INI file" << std::endl;
                std::cerr << fe.what() << std::endl;            
                std::cerr << "Load file error code is " << fe.code() << std::endl;
                m_objerror = Error::LOAD_FILE;
                m_objectstate = false;
                return false;
            }catch(const Glib::KeyFileError& ke){
                m_objerror = Error::LOAD_FILE;
                m_objectstate = false;
			    std::cerr << "Error reading INI file" << std::endl;
			    std::cerr << __FILE__ << ": " << ke.what() << std::endl;
                std::cerr << "Load file error code is " << ke.code() << std::endl;
                return false;
            }
       }/* END IF*/ 
    } /* END IF */
    return false;
}
bool
ScpSettings::create_ini_dir(const Glib::RefPtr<Gio::File>& dir)
{
    try{
        if(dir->make_directory_with_parents())
            return true;
    }catch(const Gio::Error& e){
        auto errorcode = e.code();
        switch (errorcode)
        {
            case Gio::Error::EXISTS:
            {
                std::cerr << "Directory exists " << std::endl;
                m_objectstate = true;
                return true;
            }
            break;    
            case Gio::Error::NOT_SUPPORTED:
            {
                std::cerr << "File System doesn't support creating directories" << std::endl;
                std::cerr << e.what() << std::endl;
                m_objectstate = false;
                m_objerror = Error::NOT_SUPPORTED;
                return false;
            }
            break;
            case Gio::Error::CANCELLED:
            {
                std::cerr << "Operation was cancelled" << std::endl;
                std::cerr << e.what() << std::endl;
                m_objectstate = false;
                m_objerror = Error::CANCELLED;
                return false;
            }
            break;
            default:
            {
                std::cerr << "Unknown error code. Please report as bug" << std::endl;
                m_objectstate = false;
                m_objerror = Error::UNDEFINED;
                return false;
            }
            break;
        } /* End of switch */
    } /* End of catch */
    return false; 
}

bool
ScpSettings::create_ini_file(const Glib::RefPtr<Gio::File>& file)
{
    try{
        file->create_file(Gio::FILE_CREATE_REPLACE_DESTINATION);
        return true;
    }catch(const Gio::Error& e) {
        auto errorcode = e.code();
        switch (errorcode)
        {
            case Gio::Error::EXISTS:
            {
                std::cerr << "File already exists" << std::endl;
                std::cerr << e.what() << std::endl;
                m_objectstate = true;
                return true;
            }   
            break;    
            case Gio::Error::IS_DIRECTORY:
            {
                std::cerr << "You have directory with the same name as INI file" << std::endl;
                std::cerr << e.what() << std::endl;
                m_objectstate = false;
                m_objerror = Error::IS_DIRECTORY;
                return false;
            }
            break;
            case Gio::Error::FILENAME_TOO_LONG:
            {
                std::cerr << "Filename too long" << std::endl;
                std::cerr << e.what() << std::endl;
                m_objectstate = false;
                m_objerror = Error::FILENAME_TOO_LONG;
                return false;
            }
            break;
            default:
            {
                std::cerr << "Unknown error code. Please report as bug" << std::endl;
                m_objectstate = false;
                m_objerror = Error::UNDEFINED;
                return false;
            }
            break;
        } /* End of switch */
    } /* End of caatch */
    return false;
}

