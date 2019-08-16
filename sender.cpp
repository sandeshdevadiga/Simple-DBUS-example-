

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include<iostream>
using namespace std;

#include <dbus/dbus.h>


const char *const INTERFACE_NAME = "in.softprayog.dbus_example";
const char *const SERVER_BUS_NAME = "in.softprayog.add_server";
const char *const CLIENT_BUS_NAME = "in.softprayog.add_client";
const char *const SERVER_OBJECT_PATH_NAME = "/in/softprayog/adder";
const char *const CLIENT_OBJECT_PATH_NAME = "/in/softprayog/add_client";
const char *const METHOD_NAME = "add_numbers";

DBusError dbus_error;
void print_dbus_error (char *str);

int main (int argc, char **argv)
{
    DBusConnection *conn;
    int ret;
    dbus_error_init (&dbus_error);
    conn = dbus_bus_get (DBUS_BUS_SESSION, &dbus_error);

    if (dbus_error_is_set (&dbus_error))
        print_dbus_error ("dbus_bus_get");

    if (!conn) 
        exit (1);

	
	int value;
   
    while (1)
 {
  	  cout<<" Enter a value:";
 	  cin>>value;
  
	  if(value==0)
	   {
	     cout<<"invalid value\n";
	     break;
	   }
	else
	   {
	   cout<<"valid value\n";
	   }
	  
        // Get a well known name
        while (value>0) 
        {

              cout<<"getting connected\n";
              ret = dbus_bus_request_name (conn, CLIENT_BUS_NAME, 0, &dbus_error);

            if (ret == DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER) 
               {
                     break;
               }

           else if (ret == DBUS_REQUEST_NAME_REPLY_IN_QUEUE)
              {
               fprintf (stderr, "Waiting for the bus ... \n");
               sleep (1);
               continue;
              }
              //  else if(ret==4){
               //break;
                  //}
            if (dbus_error_is_set (&dbus_error))
               print_dbus_error ("dbus_bus_get");
        }
        
      DBusMessage *request;

        if ((request = dbus_message_new_method_call (SERVER_BUS_NAME, SERVER_OBJECT_PATH_NAME, INTERFACE_NAME, METHOD_NAME)) == NULL) 
         {
            fprintf (stderr, "Error in dbus_message_new_method_call\n");
            exit (1);
        }

      
       
        if (!dbus_connection_send (conn, request,NULL)) 
	{
            fprintf (stderr, "Error in dbus_connection_send_with_reply\n");
            exit (1);
        }


        dbus_connection_flush (conn);
	dbus_message_unref (request);	
                
      
       cout<<"after flushing conf\n";
      if (dbus_bus_release_name (conn, CLIENT_BUS_NAME, &dbus_error) == -1)
	 {
             fprintf (stderr, "Error in dbus_bus_release_name\n");
             exit (1);
        }

      cin>>value;
    }

    return 0;
}

void print_dbus_error (char *str) 
{
    fprintf (stderr, "%s: %s\n", str, dbus_error.message);
    dbus_error_free (&dbus_error);
}
