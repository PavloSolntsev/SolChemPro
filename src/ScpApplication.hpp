/* 
 * ScpApplication.hpp Copyright (C) 2017 <pavlo.solntsev@gmail.com>
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

#ifndef SCP_APPLICATION_HPP_ 
#define SCP_APPLICATION_HPP_

#include <gtkmm.h>
#include "ScpAssistant.hpp"
#include "ScpMainwindow.hpp"
#include "ScpProject.hpp"
#include <libgdamm.h>
#include "ScpEnum.hpp"
#include "ScpTable.hpp"
#include "ScpSettings.hpp"
#include "ScpGUISettings.hpp"
#include <map>

class ScpApplication final: public Gtk::Application
{
	protected:
		ScpApplication();
		
	public:
		static Glib::RefPtr<ScpApplication> create();
        virtual ~ScpApplication();

	//Overrides of default signal handlers:
		void on_activate() override;
		void on_startup() override;
	    void on_action_connect();
	    void on_action_disconnect();
		  
	private:
        enum class Table {
            USERS,
            PROJECT
        };
        /*! TODO: enum class Table should be removed. There is a separate table class was created.
         *  \todo enum class Table should be removed. There is a separate table class was created.
         */
        std::map<Table,Glib::ustring> m_tables;

		Glib::KeyFile m_keyfile;		
		Glib::ustring inifilepath;
		Glib::RefPtr<Gnome::Gda::Connection> m_refConnection;	
		void create_window();
	    void on_window_hide(Gtk::Window* window);
	    void on_action_quit();
	    void on_action_print(const Glib::VariantBase& parameter);
		bool first_time_start();
        void on_settings_gui_hide();
        bool normal_start();
		void write_preferences(ScpGUISettings::ScpSettingsDialog dialog);
		void esteblish_connection_to_db(); 
        bool create_users_table();
        bool table_exists(const Glib::ustring);
        bool table_exists(Table);
        void on_newproject_clicked();
        void save_project(ScpProject &);
        bool create_project_table();
 //       bool check_ini_file();
		ScpAssistant m_assistant;		
		ScpMainwindow *m_refWindow;
        ScpTable alltables;
        ScpSettings *m_refsettings;
        ScpGUISettings *m_refGuisettings;
};
		  
#endif /* SCP_APPLICATION_HPP_ */

