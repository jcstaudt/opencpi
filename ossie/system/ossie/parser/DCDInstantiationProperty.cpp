/*******************************************************************************

Copyright 2004, Virginia Polytechnic Institute and State University

This file is part of the OSSIE Parser.

OSSIE Parser is free software; you can redistribute it and/or modify
it under the terms of the Lesser GNU General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or
(at your option) any later version.

OSSIE Parser is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
Lesser GNU General Public License for more details.

You should have received a copy of the Lesser GNU General Public License
along with OSSIE Parser; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

Even though all code is original, the architecture of the OSSIE Parser is based
on the architecture of the CRC's SCA Reference Implementation (SCARI)
see: http://www.crc.ca/en/html/rmsc/home/sdr/projects/scari

*********************************************************************************/

///\todo Figure out what this file is for

#include "ossie/DCDInstantiationProperty.h"

#if 0
DCDInstantiationProperty::DCDInstantiationProperty():
        id(NULL),value(NULL)
{}

DCDInstantiationProperty::
DCDInstantiationProperty(const DCDInstantiationProperty & _dcdIP):
        id(NULL),value(NULL)
{
    this->id = new char[strlen (_dcdIP.id) + 1];
    strcpy (this->id, _dcdIP.id);

    this->value = new char[strlen (_dcdIP.value) + 1];
    strcpy (this->value, _dcdIP.value);
}
#endif

DCDInstantiationProperty::DCDInstantiationProperty(const char *_id, const char *_value)
{
    id = _id;
    value = _value;
}



DCDInstantiationProperty::~DCDInstantiationProperty ()
{
}


const char* DCDInstantiationProperty::getID()
{
    return id.c_str();
}


void DCDInstantiationProperty::setID(char *_id)
{
    id = _id;
}


const char* DCDInstantiationProperty::getValue()
{
    return value.c_str();
}


void DCDInstantiationProperty::setValue(char *_value)
{
    value = _value;
}
