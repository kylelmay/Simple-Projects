/* A program to calculate network configuration information for an IP Address provided
   by the user.

/* FIXME
		1: We need to come up with  better function to increment the subnets, even if it's just superficial cout wise
		2: We need to add a subnet count variable that tracks the amount of subnets that have been printed
*/


#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <bits/stdc++.h>
#include <cmath>
using namespace std;
#include "Network.h"


// ----------------------------------------------------------------------------- NETWORK CLASS FOR SUBNETTING IPV4 ADDRESSES --------------------------------------------------------------------------- //
	

int main () {
    float version = 0.8;
    char choice = 'y';
    
    cout << "Network Calculator  |  " << version << "\n" << endl  // Header
         << "Author: Kyle May" << endl
         << "Last Update: 11/25/2018\n" << endl
         << "Features of Network Calculator:" << endl
         
         << setw(60) << setfill('-') << "" <<endl           // Line break
         
         << "a.) Takes a user's IP Address" << endl			// Program Details
         << "b.) Determines IP Address Class, and Subnet" << endl
         << "c.) Shows Binary representation of both IP and Subnet Mask, stacked" << endl
         << "d.) Shows the Network ID" << endl
         << "e.) Shows the Network Increment value" << endl
         << "f.) Shows usable host addresses for each subnet" << endl
         << "g.) Shows amount of usable hosts per subnet" << endl
         << "h.) Shows amount of subnets available for that IP address" << endl
         << "i.) Shows the wildcard for the subnet " << endl
         << "j.) Shows the exact subnets and supernets requested by the user" << endl;
        // << "j.) Advanced Mode:" << endl
        // << "   1.) Takes number of DHCP servers per subnet and their static addresses" << endl
        // << "   2.) Recommends scope options and allows user to choose one" << endl
         //<< "   3.) Recommends redundancy options and allows user to choose one" << endl
         //<< "   4.) Option to run a network growth simulation to determine new network information each time DHCP scopes collide" << endl;
    cout << setw(60) << setfill('-') << "" << setfill(' ') << endl;

	do {
		// Declares network object
        Network myNet;

        // Gets the IPv4 address from the user and ensure it's value is legal
        myNet.getUserInfo();
        
        // Separates the string IPv4 into it's specific integer and binary octet values, then prints them to the console
        myNet.getUserIPOctets(myNet.userIP);
        
        // Based on the class, required hosts, required networks, and IP Address, calculates the subnet and network details
        myNet.startSubnetting();
        
        // Calculates the subnets specific integer and binary values, determines CIDR value, and then prints them to the console.
        myNet.getSubnetOctets(myNet.subnetMask);
        
        // Calculates the wildcard's specific decimal and binary values
        myNet.getHostMask(); 
        
        // Uses the CIDR value to determine the host
	    myNet.getNetworkIncrement(myNet.subnetMask);
	    
		// Prints basic IP information for network IP    
	    myNet.printNetInfo();
	    
	    // Gets broadcast IP information
	    myNet.getBroadcastIP(myNet.networkIDBinary);
		
        // Gets class of IP;
        myNet.getClass();
	    
        // Prints Network Information
        myNet.printFinal();
        
        cout << "\nWould you like to enter another IP Address? (Y or N): ";
        cin >> choice;
	} while (choice == 'y' || choice == 'Y');
	
system("pause");
return 0;
}

