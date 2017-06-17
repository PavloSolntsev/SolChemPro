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

#include "gcl_compound.h"
#include <stdlib.h>

GclCompound* 
gcl_compound_new(){
    GclCompound* res = NULL;
    res = g_try_new(GclCompound,1);
    
    if(res == NULL)
        return NULL;

/* The parent pointer should be NULL. It will be initialized from the function
 * gcl_compound_add_parent
 * */
    res->parent = NULL;

    res->kdis= g_array_new(FALSE,FALSE,sizeof(double));   
    if(!res->parent){
        g_free(res);
        return NULL;
    }

    res->cas = g_string_new("");
    if(!res->cas){
        g_array_free(res->kdis,TRUE);
        g_free(res);
        return NULL;
    } 

    return res; 
}

void 
gcl_compound_free(GclCompound* obj){    
    if(obj){
        g_array_free(obj->kdis,TRUE);   
        if(obj->parent != NULL)
            g_array_free(obj->parent,TRUE);
        g_free(obj);
        g_string_free(obj->cas,TRUE);
    } 
}


GclCompound* 
gcl_compound_copy(GclCompound* dest, 
                  const GclCompound* src)
{
    if(!dest || !src)
        return NULL;

    dest->type = src->type;
    dest->mr = src->mr;
    dest->order = src->order;
             
    if(src->cas != NULL)
        g_string_assign(dest->cas,src->cas->str);
  
    g_array_set_size(dest->kdis,src->kdis->len);
        
    g_array_insert_vals(dest->kdis,0,src->kdis->data,src->kdis->len);    

}

void                  
gcl_vector_compound_add(GclVectorCompound* obj,
                        const GclCompound* cmpd,
                        GclError* error)
{
    GclCompound* new = NULL;
    new = (GclCompound*)realloc(obj->data,(obj->size+1)*sizeof(GclCompound));
    if(new == NULL)
    {
        *error = GCL_ERROR_MEMORY;
        return;
         
    }else{
        free(obj->data);
        obj->data = new;
    }
}
