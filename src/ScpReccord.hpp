/*
 * ScpReccord.hpp
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

#ifndef _SCP_RECCORD_HPP
#define _SCP_RECCORD_HPP

#include "ScpTime.hpp"

/*! \class ScpReccord 
 *  \brief Base class for all item that should written to database
 * 
 *  Any class you would like to store in DB should be derived from this class. 
 *  This class implements Time when object was created to make sure that data is handled 
 *  in the same way across all class.
 */
class ScpReccord {
    public:
        ScpReccord();
        virtual ~ScpReccord();
        ScpReccord& operator=(const ScpReccord&);
        
        /*! \brief Update modified time for the class
         *
         * This function should be manually colled to update
         * modified time of the derivied classes.
         * 
         */
        void update_time();
        const ScpTime &get_start_time()const;
        const ScpTime &get_modified_time()const;

    protected:
        ScpTime m_time_start;
        ScpTime m_time_modified_last;
    
};



#endif
