/*
 * gcl_compound.h
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

#ifndef _GCL_COMPOUND_H
#define _GCL_COMPOUND_H

#ifdef __cplusplus
extern "C" {
#endif

#define CASSTR_SIZE 20
#include <glib.h>
#include "gcl_error.h"

enum _GclCompountType {
    NONE = 0,
    STRONG_ACID,
    STRONG_BASE,
    WEAK_ACID,
    WEAK_BASE
};

typedef enum _GclCompountType GclCompoundType;

typedef struct _GclVectorCompound GclVectorCompound;

struct _GclCompound {
    GclCompoundType type;
    GArray* parent; /* Vector of GclCompound */
    GArray* kdis; /* Vector of doubles  */
    double mr;
    GString* cas; 
    int order;
};

typedef struct _GclCompound GclCompound;

struct _GclVectorCompound {
    GclCompound* data;
    size_t size;
};

GclCompound* gcl_compound_new();
void         gcl_compound_free(GclCompound* obj);
GclCompound* gcl_compound_copy(GclCompound* dest, 
                               const GclCompound* src);

GclVectorCompound* gcl_vector_compound_new();
void                  gcl_vector_compound_free(GclVectorCompound* obj);
const GclCompound*    gcl_vector_compound_at(GclVectorCompound* obj,
                                             size_t pos,
                                             GclCompound* res,
                                             GclError* error);

void                  gcl_vector_compound_add(GclVectorCompound* obj,
                                              const GclCompound* cmpd,
                                              GclError* error);

#ifdef __cplusplus
}
#endif

#endif

