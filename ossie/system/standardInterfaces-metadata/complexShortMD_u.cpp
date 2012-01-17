/****************************************************************************

Copyright 2006, Virginia Polytechnic Institute and State University

This file is part of the OSSIE Core Framework.

OSSIE Core Framework is free software; you can redistribute it and/or modify
it under the terms of the Lesser GNU General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or
(at your option) any later version.

OSSIE Core Framework is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
Lesser GNU General Public License for more details.

You should have received a copy of the Lesser GNU General Public License
along with OSSIE Core Framework; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

****************************************************************************/

#include <iostream>

#include <ossie/ossieSupport.h>

#include "standardinterfaces-metadata/complexShortMD_u.h"
#include "ossie/debug.h"

standardInterfacesMD_i::complexShort_u::complexShort_u(const char* _portName)
{
    portName = _portName;

    data_servant = new complexShort::usesPort(this);
    data_servant_var = data_servant->_this();

// initialize meta data
    InitializeMetaData( metadata );
}

standardInterfacesMD_i::complexShort_u::complexShort_u(const char* _name, const char* _domain) : portName(_name)
{
    ossieSupport::ORB orb;

    data_servant = new complexShort::usesPort(this);
    data_servant_var = data_servant->_this();

    std::string objName;
    objName = _domain;
    objName += "/";
    objName += _name;

    orb.bind_object_to_name((CORBA::Object_ptr) data_servant_var, objName.c_str());

// initialize meta data
    InitializeMetaData( metadata );
}

standardInterfacesMD_i::complexShort_u::~complexShort_u()
{

}

CORBA::Object_ptr standardInterfacesMD_i::complexShort_u::getPort(const char* _portName)
{
    if (portName == _portName)
        return CORBA::Object::_duplicate(data_servant_var);
    else
        return CORBA::Object::_nil();
}


void standardInterfacesMD_i::complexShort_u::pushPacket(
    const PortTypes::ShortSequence &I,
    const PortTypes::ShortSequence &Q,
    const standardInterfacesMD::MetaData &packet_data)
{
// update packet meta data
    metadata = packet_data;

    omni_mutex_lock l(port_mutex);
    for (unsigned int i = 0; i < dest_ports.size(); ++i) {
        dest_ports[i].port_obj->pushPacketMetaData(I, Q, metadata);
    }
}

void standardInterfacesMD_i::complexShort_u::pushPacket(
    const PortTypes::ShortSequence &I,
    const PortTypes::ShortSequence &Q)
{
    omni_mutex_lock l(port_mutex);
    for (unsigned int i = 0; i < dest_ports.size(); ++i) {
        dest_ports[i].port_obj->pushPacket(I, Q);
    }
}

complexShort::usesPort::usesPort(standardInterfacesMD_i::complexShort_u *_base) : base(_base)
{
}

complexShort::usesPort::~usesPort()
{
}

void complexShort::usesPort::connectPort(CORBA::Object_ptr connection, const char* connectionID)
{
    standardInterfacesMD::complexShortMD_ptr p = standardInterfacesMD::complexShortMD::_narrow(connection);
    if (CORBA::is_nil(p)) {
        std::cout << "Print port is not complexShort" << std::endl;
        return;
    }

    omni_mutex_lock l(base->port_mutex);
    for (unsigned int i = 0; i < base->dest_ports.size(); ++i) {
        if (strcmp(base->dest_ports[i].getID(), connectionID) == 0) {
            base->dest_ports[i].setPort(p);
            return;
        }
    }

    complexShort::ConnectionInfo c(p, connectionID);
    base->dest_ports.push_back(c);

}

void complexShort::usesPort::disconnectPort(const char* connectionID)
{
    omni_mutex_lock l(base->port_mutex);
    for (unsigned int i = 0; i < base->dest_ports.size(); ++i) {
        if (strcmp(base->dest_ports[i].getID(), connectionID) == 0) {
            base->dest_ports.erase(base->dest_ports.begin() + i);
            return;
        }
    }

    DEBUG(5, StandardInterfaces, "Attempted to disconnect non-existent connection: " << connectionID);

}
