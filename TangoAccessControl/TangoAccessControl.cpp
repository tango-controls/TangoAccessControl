/*----- PROTECTED REGION ID(TangoAccessControl.cpp) ENABLED START -----*/
static const char *RcsId = "$Id$";
//=============================================================================
//
// file :        TangoAccessControl.cpp
//
// description : C++ source for the TangoAccessControl and its commands.
//               The class is derived from Device. It represents the
//               CORBA servant object which will be accessed from the
//               network. All commands which can be executed on the
//               TangoAccessControl are implemented in this file.
//
// project :     Tango Access Control Management.
//
//
// Copyright (C) :      2004,2005,2006,2007,2008,2009,2010,2011,2012,2013,2014
//						European Synchrotron Radiation Facility
//                      BP 220, Grenoble 38043
//                      FRANCE
//
// This file is part of Tango.
//
// Tango is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// Tango is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with Tango.  If not, see <http://www.gnu.org/licenses/>.
//
//
// $Author$
//
// $Revision$
// $Date$
//
//=============================================================================
//                This file is generated by POGO
//        (Program Obviously used to Generate tango Object)
//=============================================================================


#include <tango.h>
#include <TangoAccessControl.h>
#include <TangoAccessControlClass.h>

/*----- PROTECTED REGION END -----*/	//	TangoAccessControl.cpp

/**
 *  TangoAccessControl class description:
 *    This class is a conceate class inherited from AccessControl abstract class.<Br>
 *    <Br>
 *    This class defines how to manage the TANGO access control.<Br>
 *    It implements commands for tool to defines access for users, devices and IP addresses.<Br>
 *    It implements also commands used by client API to check access for specified user, device and address.<Br>
 *    And it implements register and unregister it as TANGO service.
 */

//================================================================
//  The following table gives the correspondence
//  between command and method names.
//
//  Command name                |  Method name
//================================================================
//  State                       |  Inherited (no method)
//  Status                      |  Inherited (no method)
//  AddAddressForUser           |  add_address_for_user
//  AddDeviceForUser            |  add_device_for_user
//  CloneUser                   |  clone_user
//  GetAccess                   |  get_access
//  GetAccessForMultiIP         |  get_access_for_multi_ip
//  GetAddressByUser            |  get_address_by_user
//  GetAllowedCommandClassList  |  get_allowed_command_class_list
//  GetAllowedCommands          |  get_allowed_commands
//  GetDeviceByUser             |  get_device_by_user
//  GetDeviceClass              |  get_device_class
//  GetUsers                    |  get_users
//  RegisterService             |  register_service
//  RemoveAddressForUser        |  remove_address_for_user
//  RemoveDeviceForUser         |  remove_device_for_user
//  RemoveUser                  |  remove_user
//  UnregisterService           |  unregister_service
//================================================================

//================================================================
//  Attributes managed is:
//================================================================
//================================================================

namespace TangoAccessControl_ns
{
/*----- PROTECTED REGION ID(TangoAccessControl::namespace_starting) ENABLED START -----*/

	//	static initializations

	/*----- PROTECTED REGION END -----*/	//	TangoAccessControl::namespace_starting

//--------------------------------------------------------
/**
 *	Method      : TangoAccessControl::TangoAccessControl()
 *	Description : Constructors for a Tango device
 *                implementing the classTangoAccessControl
 */
//--------------------------------------------------------
TangoAccessControl::TangoAccessControl(Tango::DeviceClass *cl, string &s)
 : AccessControl(cl, s.c_str())
{
	/*----- PROTECTED REGION ID(TangoAccessControl::constructor_1) ENABLED START -----*/

	init_device();

	/*----- PROTECTED REGION END -----*/	//	TangoAccessControl::constructor_1
}
//--------------------------------------------------------
TangoAccessControl::TangoAccessControl(Tango::DeviceClass *cl, const char *s)
 : AccessControl(cl, s)
{
	/*----- PROTECTED REGION ID(TangoAccessControl::constructor_2) ENABLED START -----*/

	init_device();

	/*----- PROTECTED REGION END -----*/	//	TangoAccessControl::constructor_2
}
//--------------------------------------------------------
TangoAccessControl::TangoAccessControl(Tango::DeviceClass *cl, const char *s, const char *d)
 : AccessControl(cl, s, d)
{
	/*----- PROTECTED REGION ID(TangoAccessControl::constructor_3) ENABLED START -----*/

	init_device();

	/*----- PROTECTED REGION END -----*/	//	TangoAccessControl::constructor_3
}

//--------------------------------------------------------
/**
 *	Method      : TangoAccessControl::delete_device()
 *	Description : will be called at device destruction or at init command
 */
//--------------------------------------------------------
void TangoAccessControl::delete_device()
{
	DEBUG_STREAM << "TangoAccessControl::delete_device() " << device_name << endl;
	/*----- PROTECTED REGION ID(TangoAccessControl::delete_device) ENABLED START -----*/

	//	Delete device allocated objects
	//	Delete device's allocated object

	/*----- PROTECTED REGION END -----*/	//	TangoAccessControl::delete_device

	if (Tango::Util::instance()->is_svr_shutting_down() == false  &&
		Tango::Util::instance()->is_device_restarting(device_name)==false)
	{
		//	If not shutting down call delete device for inherited object
		AccessControl_ns::AccessControl::delete_device();
	}
}

//--------------------------------------------------------
/**
 *	Method      : TangoAccessControl::init_device()
 *	Description : will be called at device initialization.
 */
//--------------------------------------------------------
void TangoAccessControl::init_device()
{
	DEBUG_STREAM << "TangoAccessControl::init_device() create device " << device_name << endl;
	/*----- PROTECTED REGION ID(TangoAccessControl::init_device_before) ENABLED START -----*/
	
	//	Initialization before get_device_property() call
	
	/*----- PROTECTED REGION END -----*/	//	TangoAccessControl::init_device_before
	
	if (Tango::Util::instance()->is_svr_starting() == false  &&
		Tango::Util::instance()->is_device_restarting(device_name)==false)
	{
		//	If not starting up call init device for inherited object
		AccessControl_ns::AccessControl::init_device();
	}
	//	No device property to be read from database
	

	/*----- PROTECTED REGION ID(TangoAccessControl::init_device) ENABLED START -----*/

	//	Initialize device
	// Initialise variables to default values
	//--------------------------------------------

	mysql_connection();

	set_state(Tango::ON);
	set_status("Device is OK");

	/*----- PROTECTED REGION END -----*/	//	TangoAccessControl::init_device
}


//--------------------------------------------------------
/**
 *	Method      : TangoAccessControl::always_executed_hook()
 *	Description : method always executed before any command is executed
 */
//--------------------------------------------------------
void TangoAccessControl::always_executed_hook()
{
	INFO_STREAM << "TangoAccessControl::always_executed_hook()  " << device_name << endl;
	/*----- PROTECTED REGION ID(TangoAccessControl::always_executed_hook) ENABLED START -----*/

	//	code always executed before all requests
	

	/*----- PROTECTED REGION END -----*/	//	TangoAccessControl::always_executed_hook
}

//--------------------------------------------------------
/**
 *	Method      : TangoAccessControl::read_attr_hardware()
 *	Description : Hardware acquisition for attributes
 */
//--------------------------------------------------------
void TangoAccessControl::read_attr_hardware(TANGO_UNUSED(vector<long> &attr_list))
{
	DEBUG_STREAM << "TangoAccessControl::read_attr_hardware(vector<long> &attr_list) entering... " << endl;
	/*----- PROTECTED REGION ID(TangoAccessControl::read_attr_hardware) ENABLED START -----*/
	
	//	Add your own code
	
	/*----- PROTECTED REGION END -----*/	//	TangoAccessControl::read_attr_hardware
}


//--------------------------------------------------------
/**
 *	Method      : TangoAccessControl::add_dynamic_attributes()
 *	Description : Create the dynamic attributes if any
 *                for specified device.
 */
//--------------------------------------------------------
void TangoAccessControl::add_dynamic_attributes()
{
	/*----- PROTECTED REGION ID(TangoAccessControl::add_dynamic_attributes) ENABLED START -----*/
	
	//	Add your own code to create and add dynamic attributes if any
	
	/*----- PROTECTED REGION END -----*/	//	TangoAccessControl::add_dynamic_attributes
}

//--------------------------------------------------------
/**
 *	Command AddAddressForUser related method
 *	Description: Add an address for the specified user..
 *
 *	@param argin user name, address
 *	@returns 
 */
//--------------------------------------------------------
void TangoAccessControl::add_address_for_user(const Tango::DevVarStringArray *argin)
{
	DEBUG_STREAM << "TangoAccessControl::AddAddressForUser()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(TangoAccessControl::add_address_for_user) ENABLED START -----*/

	if (argin->length() < 2)
		Tango::Except::throw_exception((const char *)AC_IncorrectArguments,
	   				  (const char *)"Needs at least 2 input arguments",
					  (const char *)"AccessControl::add_address_for_user()");
	int	x = 0;
	string	username((*argin)[x++]);
	string	ip_add  ((*argin)[x++]);

	//	Check before if already exists
	TangoSys_MemStream	tms;
	tms << "SELECT DISTINCT address FROM access_address WHERE "  <<
				"user=\""    << username << "\" AND  "    <<
				"address=\"" << ip_add   << "\"";

	DEBUG_STREAM << "add_address_for_user(): sql_query " << tms.str() << endl;
	MYSQL_RES *check = query(tms.str(), "add_address_for_user()");
	int	n_rows = mysql_num_rows(check);
	bool	already_exists = (n_rows > 0);
	mysql_free_result(check);
	if (already_exists)
		Tango::Except::throw_exception((const char *)AC_AlreadyExists,
	   				  (const char *)"This record already exists in database",
					  (const char *)"AccessControl::add_address_for_user()");


	//	If not exists, insert it
	tms.str("");
	tms << "INSERT INTO access_address SET user=\"" << username
										<< "\",address=\""      << ip_add
										<< "\"";
	DEBUG_STREAM << "AccessControl::add_address_for_user(): sql_query " << tms.str() << endl;
	simple_query(tms.str(),"add_address_for_user()");

	/*----- PROTECTED REGION END -----*/	//	TangoAccessControl::add_address_for_user
}
//--------------------------------------------------------
/**
 *	Command AddDeviceForUser related method
 *	Description: Add a device and rights for the specified user..
 *
 *	@param argin user name, device adn value
 *	@returns 
 */
//--------------------------------------------------------
void TangoAccessControl::add_device_for_user(const Tango::DevVarStringArray *argin)
{
	DEBUG_STREAM << "TangoAccessControl::AddDeviceForUser()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(TangoAccessControl::add_device_for_user) ENABLED START -----*/

	if (argin->length() < 3)
		Tango::Except::throw_exception((const char *)AC_IncorrectArguments,
	   				  (const char *)"Needs at least 3 input arguments",
					  (const char *)"AccessControl::ac_add_device_for_user()");
	int	x = 0;
	string	username((*argin)[x++]);
	string	device  ((*argin)[x++]);
	string	rights  ((*argin)[x++]);

	//	Check before if already exists
	TangoSys_MemStream	tms;
	tms << "SELECT DISTINCT device FROM access_device WHERE "  <<
				"user=\""    << username << "\" AND  "    <<
				"device=\""  << device   << "\" AND  "    <<
				"rights=\""  << rights   << "\"";

	DEBUG_STREAM << "ac_add_device_for_user(): sql_query " << tms.str() << endl;
	MYSQL_RES *check = query(tms.str(), "ac_add_device_for_user()");
	int	n_rows = mysql_num_rows(check);
	bool	already_exists = (n_rows > 0);
	mysql_free_result(check);
	if (already_exists)
		Tango::Except::throw_exception((const char *)AC_AlreadyExists,
	   				  (const char *)"This record already exists in database",
					  (const char *)"AccessControl::ac_add_device_for_user()");


	//	If not exists, insert it
	tms.str("");
	tms << "INSERT INTO access_device SET user=\"" << username
										<< "\",device=\""       << device
										<< "\",rights=\""       << rights
										<< "\"";
	DEBUG_STREAM << "AccessControl::ac_add_device_for_user(): sql_query " << tms.str() << endl;
	simple_query(tms.str(),"ac_add_device_for_user()");

	/*----- PROTECTED REGION END -----*/	//	TangoAccessControl::add_device_for_user
}
//--------------------------------------------------------
/**
 *	Command CloneUser related method
 *	Description: Copy addresses and devices from source user to target user.
 *
 *	@param argin [0] - source user name.\n[1] - target user name.
 *	@returns 
 */
//--------------------------------------------------------
void TangoAccessControl::clone_user(const Tango::DevVarStringArray *argin)
{
	DEBUG_STREAM << "TangoAccessControl::CloneUser()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(TangoAccessControl::clone_user) ENABLED START -----*/

	if (argin->length() < 2)
		Tango::Except::throw_exception((const char *)AC_IncorrectArguments,
	   				  (const char *)"Needs at least 2 input arguments",
					  (const char *)"AccessControl::clone_user()");	
	int	x = 0;
	string	src_user((*argin)[x++]);
	string	new_user((*argin)[x++]);

	//	remove new user if already exists
	remove_user((char *)new_user.c_str());

	//	Get address for source user
	TangoSys_MemStream	tms;
	tms << "SELECT DISTINCT address FROM access_address WHERE user"
			<< "=\"" << src_user <<  "\" ORDER BY address";
	DEBUG_STREAM << "AccessControl::clone_user(): sql_query " << tms.str() << endl;
	
	MYSQL_RES *result = query(tms.str(), "clone_user()");
	int	n_rows = mysql_num_rows(result);
	vector<string>	v_add;
	if (n_rows > 0)
		for (int i=0; i<n_rows; i++)
		{
			MYSQL_ROW	row = mysql_fetch_row(result);
			if (row != NULL)
			{
				string	s(row[0]);
				v_add.push_back(s);
			}
		}
	mysql_free_result(result);

	//	Write with new user.
	unsigned int	i;
	for (i=0 ; i<v_add.size() ; i++)
	{
		tms.str("");
		tms << "INSERT INTO access_address SET user=\"" << new_user
								<< "\",address=\""      << v_add[i]
								<< "\"";
		DEBUG_STREAM << "AccessControl::clone_user(): sql_query " << tms.str() << endl;
		simple_query(tms.str(),"clone_user()");
	}


	//	Get Device for source user
	tms.str("");
	tms << "SELECT DISTINCT device, rights FROM access_device WHERE user"
			<< "=\"" << src_user <<  "\" ORDER BY device";
	DEBUG_STREAM << "AccessControl::clone_user(): sql_query " << tms.str() << endl;
	
	result = query(tms.str(), "clone_user()");

	n_rows = mysql_num_rows(result);
	vector<string>	v_dev;
	if (n_rows > 0)
		for (int j=0; j<n_rows; j++)
		{
			MYSQL_ROW	row = mysql_fetch_row(result);
			if (row != NULL)
			{
				string	device(row[0]);
				string	rights(row[1]);
				v_dev.push_back(device);
				v_dev.push_back(rights);
			}
		}
	mysql_free_result(result);

	//	Write with new user	
	for (i=0 ; i<v_dev.size()/2 ; i++)
	{
		tms.str("");
		tms << "INSERT INTO access_device SET user=\"" << new_user
								<< "\",device=\""      << v_dev[2*i]
								<< "\",rights=\""      << v_dev[2*i+1]
								<< "\"";
		DEBUG_STREAM << "AccessControl::clone_user(): sql_query " << tms.str() << endl;
		simple_query(tms.str(),"clone_user()");
	}

	/*----- PROTECTED REGION END -----*/	//	TangoAccessControl::clone_user
}
//--------------------------------------------------------
/**
 *	Command GetAccess related method
 *	Description: Check access for specified user, device, address
 *                    and returns access (read or write).
 *
 *	@param argin [0] - User name
 *               [1] - IP Address
 *               [2] - Device
 *	@returns access for specified inputs  read/write.
 */
//--------------------------------------------------------
Tango::DevString TangoAccessControl::get_access(const Tango::DevVarStringArray *argin)
{
	Tango::DevString argout;
	DEBUG_STREAM << "TangoAccessControl::GetAccess()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(TangoAccessControl::get_access) ENABLED START -----*/

	if (argin->length() < 3)
		Tango::Except::throw_exception((const char *)AC_IncorrectArguments,
	   				  (const char *)"Needs at least 3 input arguments",
					  (const char *)"AccessControl::get_access()");	
	int	x = 0;
	string	user((*argin)[x++]);
	string	ip_add((*argin)[x++]);
	string	device((*argin)[x++]);

	//	First pass, Check if User,address is defined (autorized)
	vector<AccessStruct>	as_read =
				get_access_for_user_address(user, ip_add);

	//	Check if first pass has results
	if (as_read.empty()==true)
	{
		argout = CORBA::string_dup("read");
		return argout;
	}

	/* 
	for (int i=0 ; i<as_read.size() ; i++)
		cout << "	object["<< i << "] : " 
					 << as_read[i].user << "|" << as_read[i].address << endl;
	 */

	//	Couple: user, address is autorized  -->
	//	second pass, Check if User,device is defined
	string	result = get_access_for_user_device(user, device);;

	argout = CORBA::string_dup(result.c_str());

	/*----- PROTECTED REGION END -----*/	//	TangoAccessControl::get_access
	return argout;
}
//--------------------------------------------------------
/**
 *	Command GetAccessForMultiIP related method
 *	Description: Check access for specified user, device and addresses
 *                    and returns access (read or write).
 *
 *	@param argin [0] - User name
 *               [1] - Device
 *               [2] - IP Address #1
 *               [3] - IP Address #2
 *               [4] - IP Address #3
 *               [5] - IP Address #4
 *               ......
 *	@returns access for specified inputs  read/write.
 */
//--------------------------------------------------------
Tango::DevString TangoAccessControl::get_access_for_multi_ip(const Tango::DevVarStringArray *argin)
{
	Tango::DevString argout;
	DEBUG_STREAM << "TangoAccessControl::GetAccessForMultiIP()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(TangoAccessControl::get_access_for_multi_ip) ENABLED START -----*/

	if (argin->length() < 3)
		Tango::Except::throw_exception((const char *)AC_IncorrectArguments,
	   				  (const char *)"Needs at least 3 input arguments",
					  (const char *)"AccessControl::get_access()");	
	unsigned int	x = 0;
	string	user((*argin)[x++]);
	string	device((*argin)[x++]);
	
	
	//	First pass, Check if User and at least one of the addresses is defined (autorized)
	bool	ip_found = false;
	while (x < argin->length() && !ip_found)
	{
		string	ip_add((*argin)[x++]);
		vector<AccessStruct>	as_read =
					get_access_for_user_address(user, ip_add);

		//	Check if first pass has results
		if (as_read.empty()==false)
		{
			ip_found = true;
			/* 
			for (int i=0 ; i<as_read.size() ; i++)
				cout << "	found  for "<< as_read[i].address << endl;
			 */
		 }
		 /*
		 else
			cout << "	NOT found  for "<< ip_add << endl;
		*/
		 	
	}
	
	if (!ip_found)
	{
		argout = CORBA::string_dup("read");
		return argout;
	}

	//	Couple: user, address is autorized  -->
	//	second pass, Check if User,device is defined
	string	result = get_access_for_user_device(user, device);;
	argout = CORBA::string_dup(result.c_str());

	/*----- PROTECTED REGION END -----*/	//	TangoAccessControl::get_access_for_multi_ip
	return argout;
}
//--------------------------------------------------------
/**
 *	Command GetAddressByUser related method
 *	Description: Returns address list  found for the specified user.
 *
 *	@param argin user name.
 *	@returns Addresses found for the specified user.
 */
//--------------------------------------------------------
Tango::DevVarStringArray *TangoAccessControl::get_address_by_user(Tango::DevString argin)
{
	Tango::DevVarStringArray *argout;
	DEBUG_STREAM << "TangoAccessControl::GetAddressByUser()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(TangoAccessControl::get_address_by_user) ENABLED START -----*/

	string	username(argin);
	TangoSys_MemStream	tms;
	tms << "SELECT DISTINCT address FROM access_address WHERE user"
			<< "=\"" << username <<  "\" ORDER BY address";
	DEBUG_STREAM << "AccessControl::get_address_by_user(): sql_query " << tms.str() << endl;
	
	MYSQL_RES *result = query(tms.str(), "get_address_by_user()");
	int	n_rows = mysql_num_rows(result);

	argout = new Tango::DevVarStringArray;

	if (n_rows > 0)
	{
		int nb_col = 1;
		argout->length(n_rows*nb_col);
		int		nb=0;
		for (int i=0; i<n_rows; i++)
		{
			MYSQL_ROW	row = mysql_fetch_row(result);
			if (row != NULL)
			{
				for (int c=0 ; c <nb_col ; c++)
					(*argout)[nb++]   = CORBA::string_dup(row[c]);
			}
		}
	}
	else
		argout->length(0);
	mysql_free_result(result);

	/*----- PROTECTED REGION END -----*/	//	TangoAccessControl::get_address_by_user
	return argout;
}
//--------------------------------------------------------
/**
 *	Command GetAllowedCommandClassList related method
 *	Description: Returns the class names which have AllowedAccessCmd property defined.
 *
 *	@param argin 
 *	@returns Class names which have AllowedAccessCmd property defined.
 */
//--------------------------------------------------------
Tango::DevVarStringArray *TangoAccessControl::get_allowed_command_class_list()
{
	Tango::DevVarStringArray *argout;
	DEBUG_STREAM << "TangoAccessControl::GetAllowedCommandClassList()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(TangoAccessControl::get_allowed_command_class_list) ENABLED START -----*/

	TangoSys_MemStream	tms;
	tms << "SELECT DISTINCT class FROM property_class WHERE name = \"AllowedAccessCmd\" ORDER BY class";
	DEBUG_STREAM << "AccessControl::get_allowed_commands(): sql_query " << tms.str() << endl;
	   
	MYSQL_RES	*result = query(tms.str(),"get_allowed_commands_class_list()");
	int	n_rows = mysql_num_rows(result);

	argout = new Tango::DevVarStringArray;
	argout->length(n_rows);
	if (n_rows > 0)
	{
		for (int i=0; i<n_rows; i++)
		{
			MYSQL_ROW	row = mysql_fetch_row(result);
			if (row != NULL)
			{
				DEBUG_STREAM << "AccessControl::get_allowed_commands(): property[ "<< i << "] " << row[0] << endl;
				(*argout)[i] = CORBA::string_dup(row[0]);
			}
		}
	}
	mysql_free_result(result);

	/*----- PROTECTED REGION END -----*/	//	TangoAccessControl::get_allowed_command_class_list
	return argout;
}
//--------------------------------------------------------
/**
 *	Command GetAllowedCommands related method
 *	Description: Returns allowed command list found in database for specified device
 *               It search the class of the specified device and then uses the class property <b>AllowedAccessCmd</b>
 *
 *	@param argin Device name OR Device Class name
 *	@returns Allowed commands found in database for specified device
 */
//--------------------------------------------------------
Tango::DevVarStringArray *TangoAccessControl::get_allowed_commands(Tango::DevString argin)
{
	Tango::DevVarStringArray *argout;
	DEBUG_STREAM << "TangoAccessControl::GetAllowedCommands()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(TangoAccessControl::get_allowed_commands) ENABLED START -----*/

	string classname;
	string full_dev_name(argin);
	
	if (full_dev_name.find('/') == string::npos)
		classname = argin;
	else
		classname = get_device_class(argin);
	
	TangoSys_MemStream	tms;
	tms << "SELECT value FROM property_class WHERE class = \"" 
			<< classname.c_str() << "\" AND name =\"AllowedAccessCmd\"  ORDER by value";
	DEBUG_STREAM << "AccessControl::get_allowed_commands(): sql_query " << tms.str() << endl;
	   
	MYSQL_RES	*result = query(tms.str(),"get_allowed_commands()");
	int	n_rows = mysql_num_rows(result);

	argout = new Tango::DevVarStringArray;
	argout->length(n_rows+2);
	//	Add State and Status commands for all classe and devices
	(*argout)[0] = CORBA::string_dup("State");
	(*argout)[1] = CORBA::string_dup("Status");
	if (n_rows > 0)
	{
		for (int i=0; i<n_rows; i++)
		{
			MYSQL_ROW	row = mysql_fetch_row(result);
			if (row != NULL)
			{
				DEBUG_STREAM << "AccessControl::get_allowed_commands(): property[ "<< i << "] " << row[0] << endl;
				(*argout)[i+2] = CORBA::string_dup(row[0]);
			}
		}
	}
	mysql_free_result(result);

	/*----- PROTECTED REGION END -----*/	//	TangoAccessControl::get_allowed_commands
	return argout;
}
//--------------------------------------------------------
/**
 *	Command GetDeviceByUser related method
 *	Description: Returns devices and rights found for the specified user.
 *
 *	@param argin user name.
 *	@returns devices and rights found for the specified user.
 */
//--------------------------------------------------------
Tango::DevVarStringArray *TangoAccessControl::get_device_by_user(Tango::DevString argin)
{
	Tango::DevVarStringArray *argout;
	DEBUG_STREAM << "TangoAccessControl::GetDeviceByUser()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(TangoAccessControl::get_device_by_user) ENABLED START -----*/

	string	username(argin);
	TangoSys_MemStream	tms;
	tms << "SELECT DISTINCT device,rights FROM access_device WHERE user"
			<< "=\"" << username <<  "\" ORDER BY device";
	DEBUG_STREAM << "AccessControl::get_device_by_user(): sql_query " << tms.str() << endl;
	
	MYSQL_RES *result = query(tms.str(), "get_device_by_user()");
	int	n_rows = mysql_num_rows(result);

	argout = new Tango::DevVarStringArray;

	if (n_rows > 0)
	{
		int nb_col = 2;

		argout->length(n_rows*nb_col);
		int		nb=0;
		for (int i=0; i<n_rows; i++)
		{
			MYSQL_ROW	row = mysql_fetch_row(result);
			if (row != NULL)
			{
				for (int c=0 ; c <nb_col ; c++)
					(*argout)[nb++]   = CORBA::string_dup(row[c]);
			}
		}
	}
	else
		argout->length(0);
	mysql_free_result(result);

	/*----- PROTECTED REGION END -----*/	//	TangoAccessControl::get_device_by_user
	return argout;
}
//--------------------------------------------------------
/**
 *	Command GetDeviceClass related method
 *	Description: Returns class for specified device.
 *
 *	@param argin Device name
 *	@returns Class found in database for specified device
 */
//--------------------------------------------------------
Tango::DevString TangoAccessControl::get_device_class(Tango::DevString argin)
{
	Tango::DevString argout;
	DEBUG_STREAM << "TangoAccessControl::GetDeviceClass()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(TangoAccessControl::get_device_class) ENABLED START -----*/

	argout = NULL;
	//	Get class for device
	TangoSys_MemStream	tms;
	tms << "SELECT DISTINCT class FROM device WHERE name=\""
				<< argin <<  "\"";
	DEBUG_STREAM << "AccessControl::get_device_class(): sql_query " << tms.str() << endl;
	
	MYSQL_RES *result = query(tms.str(), "get_device_class()");
	int	n_rows = mysql_num_rows(result);
	if (n_rows==0)
	{
		TangoSys_MemStream	tms;
		tms << "Class not found for " << argin;
		Tango::Except::throw_exception((const char *)AC_IncorrectArguments,
	   				  (const char *)tms.str().c_str(),
					  (const char *)"AccessControl::get_device_class()");	
	}

	if (n_rows > 0)
		for (int i=0; i<n_rows; i++)
		{
			MYSQL_ROW	row = mysql_fetch_row(result);
			if (row != NULL)
			{
				argout = CORBA::string_dup(row[0]);
			}
		}
	mysql_free_result(result);

	DEBUG_STREAM << "Class " << argout << " found for " << argin << endl;

	/*----- PROTECTED REGION END -----*/	//	TangoAccessControl::get_device_class
	return argout;
}
//--------------------------------------------------------
/**
 *	Command GetUsers related method
 *	Description: Returns user list found in table access_address.
 *
 *	@param argin 
 *	@returns Users find in table access_address.
 */
//--------------------------------------------------------
Tango::DevVarStringArray *TangoAccessControl::get_users()
{
	Tango::DevVarStringArray *argout;
	DEBUG_STREAM << "TangoAccessControl::GetUsers()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(TangoAccessControl::get_users) ENABLED START -----*/

	//	Search in address table
	TangoSys_MemStream	tms;
	tms << "SELECT DISTINCT user FROM access_address "
			<< " WHERE user like \"%\" ORDER BY user";
	DEBUG_STREAM << "AccessControl::get_users(): sql_query " << tms.str() << endl;
	
	MYSQL_RES *result = query(tms.str(), "get_users()");
	int	n_rows = mysql_num_rows(result);

	vector<string>	users;
	if (n_rows > 0)
		for (int i=0; i<n_rows; i++)
		{
			MYSQL_ROW	row = mysql_fetch_row(result);
			if (row != NULL)
			{
				string	s(row[0]);
				users.push_back(s);
			}
		}
	mysql_free_result(result);

	//	Search in device table
	tms.str("");
	tms << "SELECT DISTINCT user FROM access_device "
			<< " WHERE user like \"%\" ORDER BY user";
	DEBUG_STREAM << "AccessControl::get_users(): sql_query " << tms.str() << endl;
	
	result = query(tms.str(), "get_users()");
	n_rows = mysql_num_rows(result);
	if (n_rows > 0)
		for (int i=0; i<n_rows; i++)
		{
			MYSQL_ROW	row = mysql_fetch_row(result);
			if (row != NULL)
			{
				string	s(row[0]);
				//	Check if exists
				bool exists = false;
				for (unsigned int j=0 ; !exists && j<users.size() ; j++)
					exists = (users[j]==s);
				if (!exists)
					users.push_back(s);
			}
		}
	mysql_free_result(result);

	argout = new Tango::DevVarStringArray;
	argout->length(users.size());
	for (unsigned int i=0 ; i<users.size() ; i++)
		(*argout)[i] = CORBA::string_dup(users[i].c_str());

	/*----- PROTECTED REGION END -----*/	//	TangoAccessControl::get_users
	return argout;
}
//--------------------------------------------------------
/**
 *	Command RegisterService related method
 *	Description: Register device as a TANGO service.
 *
 *	@param argin 
 *	@returns 
 */
//--------------------------------------------------------
void TangoAccessControl::register_service()
{
	DEBUG_STREAM << "TangoAccessControl::RegisterService()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(TangoAccessControl::register_service) ENABLED START -----*/

	register_service(ServiceName, InatanceName, device_name);

	/*----- PROTECTED REGION END -----*/	//	TangoAccessControl::register_service
}
//--------------------------------------------------------
/**
 *	Command RemoveAddressForUser related method
 *	Description: Remove an address for the specified user..
 *
 *	@param argin user name, address
 *	@returns 
 */
//--------------------------------------------------------
void TangoAccessControl::remove_address_for_user(const Tango::DevVarStringArray *argin)
{
	DEBUG_STREAM << "TangoAccessControl::RemoveAddressForUser()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(TangoAccessControl::remove_address_for_user) ENABLED START -----*/

	if (argin->length() < 2)
		Tango::Except::throw_exception((const char *)AC_IncorrectArguments,
	   				  (const char *)"Needs at least 2 input arguments",
					  (const char *)"AccessControl::remove_address_for_user()");	
	int	x = 0;
	string	username((*argin)[x++]);
	string	ip_add  ((*argin)[x++]);

	TangoSys_MemStream	tms;
	tms << "DELETE FROM access_address WHERE user=\"" << username
							<< "\" AND address=\""     << ip_add
							<< "\"";
	DEBUG_STREAM << "AccessControl::remove_address_for_user(): sql_query " << tms.str() << endl;
	simple_query(tms.str(),"remove_address_for_user()");

	/*----- PROTECTED REGION END -----*/	//	TangoAccessControl::remove_address_for_user
}
//--------------------------------------------------------
/**
 *	Command RemoveDeviceForUser related method
 *	Description: Remove a device and its rights for the specified user..
 *
 *	@param argin user name, device and value
 *	@returns 
 */
//--------------------------------------------------------
void TangoAccessControl::remove_device_for_user(const Tango::DevVarStringArray *argin)
{
	DEBUG_STREAM << "TangoAccessControl::RemoveDeviceForUser()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(TangoAccessControl::remove_device_for_user) ENABLED START -----*/

	if (argin->length() < 3)
		Tango::Except::throw_exception((const char *)AC_IncorrectArguments,
	   				  (const char *)"Needs at least 3 input arguments",
					  (const char *)"AccessControl::remove_device_for_user()");	
	int	x = 0;
	string	username((*argin)[x++]);
	string	device  ((*argin)[x++]);
	string	rights  ((*argin)[x++]);

	TangoSys_MemStream	tms;
	tms << "DELETE FROM access_device WHERE user=\"" << username
							<< "\" AND device=\""    << device
							<< "\" AND rights=\""    << rights
							<< "\"";
	DEBUG_STREAM << "AccessControl::remove_device_for_user(): sql_query " << tms.str() << endl;
	simple_query(tms.str(),"remove_device_for_user()");

	/*----- PROTECTED REGION END -----*/	//	TangoAccessControl::remove_device_for_user
}
//--------------------------------------------------------
/**
 *	Command RemoveUser related method
 *	Description: Remove all records for specified user.
 *
 *	@param argin user name
 *	@returns 
 */
//--------------------------------------------------------
void TangoAccessControl::remove_user(Tango::DevString argin)
{
	DEBUG_STREAM << "TangoAccessControl::RemoveUser()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(TangoAccessControl::remove_user) ENABLED START -----*/

	//	remove user if already exists in address table
	TangoSys_MemStream	tms;
	tms << "DELETE FROM access_device WHERE user=\"" << argin
										<< "\" AND device LIKE \"%\""
										<<   " AND rights LIKE \"%\"";
	DEBUG_STREAM << "AccessControl::clone_user(): sql_query " << tms.str() << endl;
	simple_query(tms.str(),"clone_user()");

	//	remove user if already exists in device table
	tms.str("");
	tms << "DELETE FROM access_address WHERE user=\"" << argin
										<< "\" AND address LIKE \"%\"";
	DEBUG_STREAM << "AccessControl::clone_user(): sql_query " << tms.str() << endl;
	simple_query(tms.str(),"clone_user()");

	/*----- PROTECTED REGION END -----*/	//	TangoAccessControl::remove_user
}
//--------------------------------------------------------
/**
 *	Command UnregisterService related method
 *	Description: Unregister device as a TANGO service.
 *
 *	@param argin 
 *	@returns 
 */
//--------------------------------------------------------
void TangoAccessControl::unregister_service()
{
	DEBUG_STREAM << "TangoAccessControl::UnregisterService()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(TangoAccessControl::unregister_service) ENABLED START -----*/

	unregister_service(ServiceName, InatanceName, device_name);

	/*----- PROTECTED REGION END -----*/	//	TangoAccessControl::unregister_service
}

/*----- PROTECTED REGION ID(TangoAccessControl::namespace_ending) ENABLED START -----*/

	//	Additional Methods

	/*----- PROTECTED REGION END -----*/	//	TangoAccessControl::namespace_ending
} //	namespace
