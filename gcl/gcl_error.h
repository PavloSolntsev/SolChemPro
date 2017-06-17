/*
 * gcl_error.h
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
 * 
 */

#ifndef __GCL_ERROR_H
#define __GCL_ERROR_H

#ifdef __cplusplus
extern "C" {
#endif

enum _GclError {
    GCL_ERROR_NORMAL = 0,
    GCL_ERROR_WRONG_INDEX,
    GCL_ERROR_MEMORY,
    GCL_ERROR_NULL_ARG
};

typedef enum _GclError GclError;


#ifdef __cplusplus
}
#endif

#endif

