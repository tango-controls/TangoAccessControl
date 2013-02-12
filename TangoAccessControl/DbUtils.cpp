static const char *RcsId = "$Id$";
//+=============================================================================
//
// file :         DbUtils.cpp
//
// description :  C++ source for the DbUtils.
//
// project :      TANGO Device Server
//
// $Author$
//
// Copyright (C) :      2004,2005,2006,2007,2008,2009,2010,2011,2012
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
// $Revision$
//
//-=============================================================================

#if HAVE_CONFIG_H
#include <ac_config.h>
#endif

#include <tango.h>
#include <TangoAccessControl.h>
#include <TangoAccessControlClass.h>

namespace TangoAccessControl_ns
{

//+------------------------------------------------------------------
/**
 *	Remove the Fully Qualify Domain Name for tango less than 5.2 compatibility
 */
//+------------------------------------------------------------------
string TangoAccessControl::removeFQDN(string s)
{
	string::size_type	pos = s.find('.');
	if (pos == string::npos)
		return s;
	else
		return 	s.substr(0, pos);
}
//+----------------------------------------------------------------------------
//
// method : 		TangoAccessControl::mysql_connection()
// 
// description : 	Execute a SQL query , ignore the result.
//
//-----------------------------------------------------------------------------
void TangoAccessControl::mysql_connection()
{
	// Initialise variables to default values
	//--------------------------------------------
	
#ifndef HAVE_CONFIG_H
	char *database = (char *)"tango";
#else
	char *database = (char *)TANGO_DB_NAME;
#endif
	const char *mysql_user = NULL;
	const char *mysql_password = NULL;
	const char *mysql_host = NULL;
	unsigned int port_num = 0;

	WARN_STREAM << "AccessControl::init_device() create database device " << device_name << endl;

// Initialise mysql database structure and connect to TANGO database

	mysql_init(&mysql);

	DummyDev d;
	string my_user,my_password,my_host;
	string ho,port;
	
	if (d.get_env_var("MYSQL_USER",my_user) != -1)
	{
		mysql_user = my_user.c_str();
	}
	if (d.get_env_var("MYSQL_PASSWORD",my_password) != -1)
	{
		mysql_password = my_password.c_str();
	}
	if (d.get_env_var("MYSQL_HOST",my_host) != -1)
	{
		string::size_type pos = my_host.find(':');
		if (pos != string::npos)
		{
			ho = my_host.substr(0,pos);
			pos++;
			port = my_host.substr(pos);
			stringstream ss(port);
			ss >> port_num;
			if (!ss)
				port_num = 0;
			mysql_host = ho.c_str();
		}
		else
			mysql_host = my_host.c_str();
	}
	
	WARN_STREAM << "AccessControl::init_device() mysql database user =  " << mysql_user 
	            << " , password = " << mysql_password << endl;

	mysql_options(&mysql,MYSQL_READ_DEFAULT_GROUP,"client");

#if   (MYSQL_VERSION_ID > 50000)	
	if(mysql_get_client_version() >= 50013)
	{
		my_bool my_auto_reconnect=1;
		if (mysql_options(&mysql,MYSQL_OPT_RECONNECT,&my_auto_reconnect) !=0)
		{
			ERROR_STREAM << "AccessControl: error setting mysql auto reconnection: " << mysql_error(&mysql) << endl;
		}		
		else
		{
			WARN_STREAM << "AccessControl: set mysql auto reconnect to true" << endl;
		}
	}
#endif
		
	if (!mysql_real_connect(&mysql, mysql_host, mysql_user, mysql_password, database, port_num, NULL, 0))
	{
		TangoSys_MemStream out_stream;
		out_stream << "Failed to connect to TANGO database (error = "
         		   << mysql_error(&mysql) << ")" << ends;
		Tango::Except::throw_exception(
					(const char *)"CANNOT_CONNECT_MYSQL",
					out_stream.str(),
					(const char *)"AccessControl::init_device()");
	}
}
//+----------------------------------------------------------------------------
//
// method : 		TangoAccessControl::simple_query()
// 
// description : 	Execute a SQL query , ignore the result.
//
//-----------------------------------------------------------------------------
void TangoAccessControl::simple_query(string sql_query,const char *method)
{
	
	TangoSys_OMemStream o;
	TangoSys_OMemStream o2;
	
	if (mysql_real_query(&mysql, sql_query.c_str(),sql_query.length()) != 0)
	{
	   WARN_STREAM << "TangoAccessControl::" << method << " failed to query TANGO database:" << endl;
	   WARN_STREAM << "  query = " << sql_query << endl;
	   WARN_STREAM << " (SQL error=" << mysql_error(&mysql) << ")" << endl;
	   o << "Failed to query TANGO database (error=" << mysql_error(&mysql) << ")";
	   o2 << "TangoAccessControl::" << method;
	   Tango::Except::throw_exception((const char *)AC_SQLError,o.str(),o2.str());
	}

}

//+----------------------------------------------------------------------------
//
// method : 		TangoAccessControl::query()
// 
// description : 	Execute a SQL query and return the result.
//
//-----------------------------------------------------------------------------
MYSQL_RES *TangoAccessControl::query(string sql_query,const char *method) {

	TangoSys_OMemStream o;
	TangoSys_OMemStream o2;
	MYSQL_RES *result;
	
	if (mysql_real_query(&mysql, sql_query.c_str(),sql_query.length()) != 0)
	{
	   WARN_STREAM << "TangoAccessControl::" << method << " failed to query TANGO database:" << endl;
	   WARN_STREAM << "  query = " << sql_query << endl;
	   WARN_STREAM << " (SQL error=" << mysql_error(&mysql) << ")" << endl;
	   o << "Failed to query TANGO database (error=" << mysql_error(&mysql) << ")";
	   o2 << "TangoAccessControl::" << method;
	   Tango::Except::throw_exception((const char *)AC_SQLError,o.str(),o2.str());
	}

	if ((result = mysql_store_result(&mysql)) == NULL)
	{
	   WARN_STREAM << "TangoAccessControl:: " << method << " : mysql_store_result() failed  (error=" << mysql_error(&mysql) << ")" << endl;
	   o << "mysql_store_result() failed (error=" << mysql_error(&mysql) << ")";
	   o2 << "TangoAccessControl::" << method;	   
	   Tango::Except::throw_exception((const char *)AC_SQLError,o.str(),o2.str());
	}
	
	return result;

}

//============================================================
/**
 *	split device name in domain faily member in a vector.
 */
//============================================================
vector<string> TangoAccessControl::get_dev_members(string &devname)
{
	vector<string>	v;
	string::size_type	pos = devname.find('/');
	string::size_type	pos2 = devname.find('/', pos+1);
	//	domain 
	v.push_back(devname.substr(0, pos));
	pos++;
	//	family 
	v.push_back(devname.substr(pos, pos2-pos));
	pos2++;
	//	member
	v.push_back(devname.substr(pos2, devname.length()-pos2));
	return v;
}
//============================================================
/**
 *	split IP address in members in a vector.
 */
//============================================================
vector<string> TangoAccessControl::get_ip_add_members(string &devname)
{
	vector<string>	v;
	string::size_type	pos = devname.find('.');
	string::size_type	pos1 = devname.find('.', pos+1);
	string::size_type	pos2 = devname.find('.', pos1+1);

	v.push_back(devname.substr(0, pos));
	pos++;
	v.push_back(devname.substr(pos, pos1-pos));
	pos1++;
	v.push_back(devname.substr(pos1, pos2-pos1));
	pos2++;
	v.push_back(devname.substr(pos2, devname.length()-pos2));
	return v;
}

//============================================================
//============================================================
vector<AccessStruct>
	TangoAccessControl::get_access_for_user_address(string &user, string &ip_add)
{
	vector<string>			v_add = get_ip_add_members(ip_add);
	vector<AccessStruct>	as_read;

	TangoSys_MemStream	sql_query_stream;
	
	//	First, check if something defined for user.
	sql_query_stream << "SELECT count(*) FROM access_address WHERE user=\"" << user << "\"";
	MYSQL_RES *res = query(sql_query_stream.str(), "ac_get_device_by_user()");
	MYSQL_ROW ro = mysql_fetch_row(res);

	sql_query_stream.str("");
	sql_query_stream << 
			"SELECT DISTINCT address FROM access_address WHERE ";
	if ((ro[0])[0] != '0')
	{
		//	Something found.
		//	User definition
		sql_query_stream << 
				"(user=\"" << user << "\")  AND  ";
	}
	else
	{
		//	User definition
		sql_query_stream << 
				"(user=\"" << user << "\" OR user=\"*\")  AND  ";
	}	
	//	IP address definition
	sql_query_stream << 
		"(address=\"*.*.*.*\"  OR  "                            <<
		"address=\"" << v_add[0] << ".*.*.*\" OR "              <<
		"address=\"" << v_add[0] << "." << v_add[1] << ".*.*\" OR " <<
		"address=\"" << v_add[0] << "." << v_add[1] << 
				 "." << v_add[2] <<".*\" OR " <<
		"address=\"" << ip_add << "\" )  ORDER BY address DESC";

	//cout << "ac_get_access(): sql_query " << sql_query_stream.str() << endl;
	MYSQL_RES *result = query(sql_query_stream.str(), "ac_get_device_by_user()");
	int	n_rows = mysql_num_rows(result);
	if (n_rows > 0)
	{
		for (int i=0; i<n_rows; i++)
		{
			MYSQL_ROW	row = mysql_fetch_row(result);
			if (row != NULL)
			{
				AccessStruct	acs;
				acs.user    = user;
				acs.address = row[0];
				as_read.push_back(acs);
			}
		}
	}
	mysql_free_result(result);
	mysql_free_result(res);
	
	return as_read;
}
//============================================================
//============================================================
string TangoAccessControl::get_access_for_user_device(string &user, string &device)
{
	vector<string>			members = get_dev_members(device);
	string	retval("read");

	TangoSys_MemStream	sql_query_stream;
	sql_query_stream << 
		"SELECT DISTINCT user,device,rights FROM access_device WHERE "  <<
				"(user=\"" << user << "\" OR user=\"*\") ORDER BY device";

	//cout << "ac_get_access(): sql_query " << sql_query_stream.str() << endl;
	MYSQL_RES *result = query(sql_query_stream.str(), "ac_get_device_by_user()");
	int	n_rows = mysql_num_rows(result);

	vector<AccessStruct>	as_user;
	vector<AccessStruct>	as_all;
	if (n_rows > 0)
	{
		for (int i=0; i<n_rows; i++)
		{
			MYSQL_ROW	row = mysql_fetch_row(result);
			if (row != NULL)
			{
				AccessStruct	acs;
				acs.user   = row[0];
				acs.device = row[1];
				acs.rights = row[2];
				/*
				cout << "		object[" << i << "} : " << acs.user
					<< "|" << acs.device
					<< "|" << acs.rights << endl;
				*/

				string	tmp(row[0]);
				if (tmp==user)
					as_user.push_back(acs);
				else
					as_all.push_back(acs);
			}
		}
	}
	mysql_free_result(result);

	//	If both empty --> read
	if (as_user.empty() && as_all.empty())
		return retval;

	//	Get user rigths
	string user_rights = get_rigths(as_user, members);
	if (user_rights != "unknown") {
		//cout << user << " " << user_rights << endl;
		//	if right has been matched -> return it
		return user_rights;
	}
	else {
		//	Elese return rights for all users
		string all_rights  = get_rigths(as_all,  members);
		if (all_rights != "unknown") {
			all_rights = "read";
		}
		return all_rights;
	}
}
//============================================================
//============================================================
string TangoAccessControl::get_rigths(vector<AccessStruct> as, vector<string> members)
{
	vector<AccessStruct> matches;
	//	Get list of structure matching device name
	for (unsigned int i=0 ; i<as.size() ; i++) {
		vector<string>	expMembers = get_dev_members(as[i].device);
		bool found = true;
		for (unsigned int j=0 ; found && j<members.size() ; j++) {	
			found = match(expMembers[j], members[j]);
		}
		//	If found for the 3 members, add to vector
		if (found) {
			matches.push_back(as[i]);
		}
	}
	
	//	Not found
	if (matches.empty())
		return "unknown";

	//	if only one, return this one.
	if (matches.size()==1) {
		return matches[0].rights;
	}
	else {
		//	Check if at least one is read only
		for (unsigned int i=0 ; i<matches.size() ; i++) {
			if (matches[i].rights=="read")
				return "read";
		}
		return "write";
	}
}
//============================================================
//============================================================
bool TangoAccessControl::match(string expression, string member)
{
	if (expression=="*" || expression==member)
		return true;
	
	string::size_type	pos = expression.find('*');
	if (pos != string::npos) {
		if (pos==0) {
			//	starts with '*'
			pos++;
			string	s = expression.substr(pos);
			return (member.find(s)!=string::npos);
		}
		else {
			//	get starting before '*'
			string	s1 = expression.substr(0, pos);
			pos++;
			//	get ending after '*'
			string	s2 = expression.substr(pos);
			if (s2.empty())
				return (member.find(s1)==0);
			else
				return (member.find(s1)==0 && member.find(s2)==pos);
		}
	}
	return false;
}
//============================================================
//============================================================
void TangoAccessControl::register_service(string servicename, string instname, string devname)
{
	//	Get service property
	vector<string>	services;
	Tango::DbData	data;
	data.push_back(Tango::DbDatum(SERVICE_PROP_NAME));
	Tango::Util *tg = Tango::Util::instance();
	tg->get_database()->get_property(CONTROL_SYSTEM, data);
	if (data[0].is_empty()==false)		data[0] >> services;

	//	Build what to be searched
	TangoSys_MemStream	new_line;
	new_line << servicename << "/" << instname;
	string 	target(new_line.str());
	transform(target.begin(), target.end(), target.begin(), ::tolower);

	new_line << ":" << devname;

	//	Search if already exists
	bool	exists = false;
	vector<string>::iterator	pos = services.begin();
	for (unsigned int i=0 ; i<services.size() ; i++, pos++)
	{
		string::size_type	spos = services[i].find(':');
		if (spos != string::npos)	// found
		{
			string	s = services[i].substr(0, spos);
			transform(s.begin(), s.end(), s.begin(), ::tolower);
			if (s==target)
			{
				//	If exists --> replace
				pos = services.erase(pos);
				services.insert(pos, new_line.str()); 
				exists = true;
			}
		}
	}
	//	Else add it
	if (!exists)
		services.push_back(new_line.str());
	
	data[0] << services;
	tg->get_database()->put_property(CONTROL_SYSTEM, data);
}
//============================================================
//============================================================
void TangoAccessControl::unregister_service(string servicename, string instname, string devname)
{
	//	Get service property
	vector<string>	services;
	Tango::DbData	data;
	data.push_back(Tango::DbDatum(SERVICE_PROP_NAME));
	Tango::Util *tg = Tango::Util::instance();
	tg->get_database()->get_property(CONTROL_SYSTEM, data);
	if (data[0].is_empty()==false)		data[0] >> services;
	
	//	Build what to be searched
	TangoSys_MemStream	line;
	line << servicename << "/" << instname << ":" << devname;
	string 	target(line.str());
	transform(target.begin(), target.end(), target.begin(), ::tolower);

	//	Search if exists
	vector<string>::iterator	pos = services.begin();
	for (unsigned int i=0 ; i<services.size() ; i++, pos++)
	{
		string	s(services[i]);
		transform(s.begin(), s.end(), s.begin(), ::tolower);
		if (s==target)
		{
			//	If exists --> remove
			services.erase(pos);
		}
	}
	data[0] << services;
	tg->get_database()->put_property(CONTROL_SYSTEM, data);
}


}	//	namespace
