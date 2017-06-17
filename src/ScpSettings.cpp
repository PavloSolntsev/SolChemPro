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
#include "ScpKeyfile.hpp"

ScpSettings::ScpSettings():
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
Glib::ustring ScpSettings::get_filepath()
{
    return m_refgfile->get_path();
}

const 
Glib::KeyFile& ScpSettings::get_keyfile()
{
    return m_keyfile;
}

bool
ScpSettings::get_boolean(const Glib::ustring& group, const Glib::ustring& key)
{
    return m_keyfile.get_boolean(group, key);
};

int
ScpSettings::get_integer(const Glib::ustring& group, const Glib::ustring& key)
{
    return m_keyfile.get_integer(group, key);
};

double
ScpSettings::get_double(const Glib::ustring& group, const Glib::ustring& key)
{
    return m_keyfile.get_double(group, key);
};

const Glib::ustring 
ScpSettings::get_string(const Glib::ustring& group, const Glib::ustring& key)
{
    return m_keyfile.get_string(group, key);
};


void
ScpSettings::set_boolean(const Glib::ustring& group, const Glib::ustring& key, bool val)
{
    return m_keyfile.set_boolean(group, key, val);
};

void
ScpSettings::set_integer(const Glib::ustring& group, const Glib::ustring& key, int val)
{
    return m_keyfile.set_integer(group, key, val);
};

void
ScpSettings::set_double(const Glib::ustring& group, const Glib::ustring& key, double val)
{
    return m_keyfile.set_double(group, key, val);
};

void 
ScpSettings::set_string(const Glib::ustring& group, const Glib::ustring& key, const Glib::ustring& val)
{
    return m_keyfile.set_string(group, key, val);
};


void 
ScpSettings::reset()
{
    m_objectstate = true;
    m_objerror = Error::CLEAN;

}

void
ScpSettings::init()
{
    auto keyfilepath = Glib::build_filename(Glib::get_user_config_dir(), DEFAULT_INI_DIR);
    keyfilepath = Glib::build_filename(keyfilepath,DEFAULT_KEYFILE);	
    m_refgfile = Gio::File::create_for_path(keyfilepath);

    std::cout << "INI file is: " << m_refgfile->get_path() << std::endl;
}

bool
ScpSettings::create_ini_dir(const Glib::RefPtr<Gio::File>& dir)
{
    try{
        if(!dir)
            dir->make_directory_with_parents();
        else{
            auto parentdir = m_refgfile->get_parent(); 
            parentdir->make_directory_with_parents();
        }

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
ScpSettings::create_ini_dir()
{
    try{
        auto parentdir = m_refgfile->get_parent(); 
        parentdir->make_directory_with_parents();

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
        if(!file){
            file->create_file(Gio::FILE_CREATE_REPLACE_DESTINATION);
            return true;
        }else{
            m_refgfile->create_file(Gio::FILE_CREATE_REPLACE_DESTINATION);
            return true;
        }
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

bool
ScpSettings::create_ini_file()
{
    try{
        m_refgfile->create_file(Gio::FILE_CREATE_REPLACE_DESTINATION);
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

bool
ScpSettings::file_exists()
{
   return m_refgfile->query_exists(); 
}

bool 
ScpSettings::save_first_start()
{
    if(!m_objectstate){
        std::cerr << "Object is not ready. You need to call reset() to continue" << std::endl;
        return false;
    }else{ 
        try{
            auto kfpath(m_refgfile->get_path());
		    m_keyfile.load_from_file(kfpath);
		    m_keyfile.set_boolean(ScpKeyfile::GROUP_GENERAL,
                                  ScpKeyfile::KEY_STARTCHECK,
                                  true);	
		    if(m_keyfile.save_to_file(kfpath))
                return true;
            else
                return false;
	    }catch(Glib::FileError &e){
			        std::cerr << "Error reading INI file" << std::endl;
                    return false;
		}catch(Glib::KeyFileError &e){
			    std::cerr << "Error reading INI file" << std::endl;
			    std::cerr << __FILE__ << ": " << e.what() << std::endl;
                return false;
		}
    }
    return false; 
    
}

bool 
ScpSettings::first_start()
{
    bool res(false);

    if(file_exists())
        try {
            m_keyfile.load_from_file(m_refgfile->get_path());
            res = get_boolean(ScpKeyfile::GROUP_GENERAL,ScpKeyfile::KEY_STARTCHECK);
        }catch(Glib::KeyFileError& e){
            std::cerr << "1Can't get STARTCHECK" << std::endl;
            std::cerr << e.what() << std::endl;
        }catch(Glib::FileError& e){
            std::cerr << "2Can't get STARTCHECK" << std::endl;
            std::cerr << e.what() << std::endl;
        }catch(Glib::Error& e){
            std::cerr << "3Can't get STARTCHECK" << std::endl;
            std::cerr << e.what() << std::endl;
        }
    else{
        std::cerr << "File doesn't exists. Can't check for first run" << std::endl;
    } 
    
    return res;
}

bool 
ScpSettings::load_from_file(Glib::KeyFileFlags flags)
{
    return m_keyfile.load_from_file(m_refgfile->get_path(),flags);
}

bool 
ScpSettings::save_to_file()
{
    return m_keyfile.save_to_file(m_refgfile->get_path());
}



