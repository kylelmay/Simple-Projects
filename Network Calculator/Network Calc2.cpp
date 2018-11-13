/* A program to calculate network configuration information for an IP Address provided
   by the user.

Author: Kyle May
Last Update: 10/10/2018

Features of Network Calculator:
--------------------------------------
a.) Takes a user's IP Address (Done)
b.) Determines IP Address Class, and Subnet (Done)
c.) Shows Binary representation of both IP and Subnet Mask, stacked (Done)
d.) Shows the Network ID
e.) Shows the Network Increment value
f.) Shows usable host addresses for each subnet
g.) Shows amount of usable hosts per subnet (Done)
h.) Shows amount of subnets available for that IP
i.) Advanced Mode:
    1.) Takes number of DHCP servers per subnet and their static addresses
    2.) Recommends scope options and allows user to choose one
    3.) Recommends redundancy options and allows user to choose one
    4.) Option to run a network growth simulation to determine new network information each time DHCP scopes collide
*/

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <bits/stdc++.h>
#include <cmath>

using namespace std;

//network is called when entering an IPv4 address for network calculations. It contains the functions and variables associated with performing calculations of IPv4 addresses
class Network {
	
    public:
	    // IP Address Variables and Functions ----------------------------------------------------------------------------------------------
	    
	    string userIP = "";           // User IP is the IP address initialized via standard input from the user.
	    double hostQty = 0;           // Number of hosts required per subnet
	    int subnetQty = 0;            // Number of subnets required for the network
	    double maxHosts = 0;
	
	    int octet1 = -1;              // Decimal Value of Octet1
	    string octet1Binary = "";     // Binary Value of Octet1
	
	    int octet2 = -1;              // Decimal Value of Octet2
	    string octet2Binary = "";     // Binary Value of Octet2
	
	    int octet3 = -1;              // Decimal Value of Octet3
	    string octet3Binary = "";     // Binary Value of Octet3
	
	    int octet4 = -1;              // Decimal Value of Octet4
	    string octet4Binary = "";     // Binary Value of Octet4
	
	    char classIP = '0';           // IP Classification for User IP Legal Values are [A, B, C] If 0, IP isn't useable.
	    string ipType = "None";       // IP Type identifies whether an IP is Public or Private
	
	    bool error = false;           // An error is made true if an error condition is met during any calculation. If true, program exits.
	    
	    void getUserInfo();
	    int getUserIPOctets(string userIP);
	    int getClass();
	    
	
	
	    // --------------------------------- SUBNET VARIABLES AND FUNCTIONS ----------------------------------------------------------------
	
	    vector <int> CIDR_VALUES {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30};
	    vector <int> HOST_POWERS {31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2};
	    vector <string> CIDR_MASKS {
	    "128.0.0.0", "192.0.0.0", "224.0.0.0", "240.0.0.0", "248.0.0.0",
	    "252.0.0.0", "254.0.0.0", "255.0.0.0", "255.128.0.0", "255.192.0.0",
	    "255.224.0.0", "255.240.0.0", "255.248.0.0", "255.252.0.0", "255.254.0.0",
	    "255.255.0.0", "255.255.128.0", "255.255.192.0", "255.255.224.0", "255.255.240.0",
	    "255.255.248.0", "255.255.252.0", "255.255.254.0", "255.255.255.0", "255.255.255.128",
	    "255.255.255.192", "255.255.255.224", "255.255.255.240", "255.255.255.248", "255.255.255.252",
	    };
	
	    // Subnet Mask Variables ---------------------------------------------------------------------
	    string subnetMask = "";
	    string subnetBinary = "";
	    int subnetOctet1 = -1;
	    string subnetOctet1Binary = "";
	    int subnetOctet2 = -1;
	    string subnetOctet2Binary = "";
	    int subnetOctet3 = -1;
	    string subnetOctet3Binary = "";
	    int subnetOctet4 = -1;
	    string subnetOctet4Binary = "";
	    int subnetsMade = 1;
	
	
	    // Network Increment Variables ---------------------------------------------------------------
	    double networkIncrement = 0;
	    string interestingOctet = "";
	    int networkBoundary = 0;
	
	    // Network ID variables ----------------------------------------------------------------------
	    string networkID = "";
	    string networkIDBinary = "";
	    int CIDR = 1;
	    string hostMin;
	    string hostMax;
	    string subnetID;
	    string hostRange;
	    int broadcastOctet = -1;
	    int hostOctetMin;
	    int subnetOctet;
	    int hostOctetMax;
	
	    // Broadcast Address variables ---------------------------------------------------------------
	    string broadcastAddress = "";
	    int broadcastOctet1 = 0;
	    string broadcastOctet1Binary = "";
	    int broadcastOctet2 = 0;
	    string broadcastOctet2Binary = "";
	    int broadcastOctet3 = 0;
	    string broadcastOctet3Binary = "";
	    int broadcastOctet4 = 0;
	    string broadcastOctet4Binary = "";
	
	    // Stream variables for converting octets into IP addresses
	    ostringstream IPStream;
	
	    // Subnetting Function to find subnets and host information based on requirements for hosts and networks
	    int startSubnetting();
	    
	    // Convert Subnet Mask into Binary and Calculate Increment Value for Subnets
	    int getSubnetOctets(string);
	
	
	    void printFinal();
};

int main () {
    char version;
    cout << "Network Calculator  |  Version: 0.6\n" << endl  // Header
         << "Author: Kyle May" << endl
         << "Last Update: 11/04/2018\n" << endl
         << "Features of Network Calculator:" << endl
         
         << setw(60) << setfill('-') << "" <<endl           // Line break
         
         << "a.) Takes a user's IP Address" << endl			// Program Details
         << "b.) Determines IP Address Class, and Subnet" << endl
         << "c.) Shows Binary representation of both IP and Subnet Mask, stacked" << endl
         << "d.) Shows the Network ID" << endl
         << "e.) Shows the Network Increment value" << endl
         << "f.) Shows usable host addresses for each subnet (Class A Only so far)" << endl
         << "g.) Shows amount of usable hosts per subnet" << endl;
        // << "h.) Shows amount of subnets available for that IP Class" << endl
        // << "i.) Show the wildcard for the subnet " << endl
        // << "j.) Advanced Mode:" << endl
        // << "   1.) Takes number of DHCP servers per subnet and their static addresses" << endl
        // << "   2.) Recommends scope options and allows user to choose one" << endl
         //<< "   3.) Recommends redundancy options and allows user to choose one" << endl
         //<< "   4.) Option to run a network growth simulation to determine new network information each time DHCP scopes collide" << endl;
    cout << setw(60) << setfill('-') << "" << setfill(' ') << endl;

		// Declares network object
        Network myNet;

        // Gets the IPv4 address from the user and ensure it's value is legal
        myNet.getUserInfo();
        if (myNet.error == true){
            cout << "Function getUserInfo failed. Ending program.";
            return 1;
        }
        
        // Separates the string IPv4 into it's specific integer and binary octet values, then prints them to the console
        myNet.getUserIPOctets(myNet.userIP);
        if (myNet.error == true){
            cout << "Function getOctets failed. Ending program.";
            return 1;
        }
		
        // Gets class of IP;
        myNet.getClass();
        if (myNet.error == true){
            cout << "Failed to get network classification. Ending program.";
            return 1;
        }
		
        // Based on the class, required hosts, required networks, and IP Address, calculates the subnet and network details
        myNet.startSubnetting();
        if (myNet.error == true){
            cout << "Failed to calculate subnets for given network address. Ending program.";
            return 1;
        }

        // Calculates the subnets specific integer and binary values, determines CIDR value, and then prints them to the console.
        myNet.getSubnetOctets(myNet.subnetMask);
        if (myNet.error == true){
            cout << "Failed to convert subnet mask into octets. Ending program.";
            return 1;
        }

        // Prints Network Information
        myNet.printFinal();
        if (myNet.error == true){
            cout << "Failed to print network information to the console. Ending program.";
            return 1;
        }
// ------------------------------------------------------- END OF PROGRAM --------------------------------------------------
return 0;
}

// Prints out subnets, associated IP addresses, and network information to the user
void Network::printFinal() {

    cout << setfill(' ') << endl
         << setw(22) << left << " IP Address: " << setw(20) << userIP << octet1Binary <<  "." << octet2Binary << "." << octet3Binary << "." << octet4Binary << endl
         << setw(22) << left << " Netmask: " << setw(20) << subnetMask << subnetOctet1Binary <<  "." << subnetOctet2Binary << "." << subnetOctet3Binary << "." << subnetOctet4Binary << endl
       //<< setw(22) << left << " Wildcard:" << setw(20) << wildcard << binaryWildcard << endl
         << setw(22) << left << " Network: " << setw(20) << networkID << networkIDBinary << " (Class " << classIP << " " << ipType << ")" << endl
         << setw(22) << left << " Network Boundary " << "Octet " << networkBoundary << endl
    //   << setw(22) << left << " HostMin: " << setw(30) << hostMinIP << " " << setw(20) << right << binaryNetworkAddress <<  endl
    //   << setw(22) << left << " HostMax: " << setw(30) << hostMaxIP << " " << setw(20) << right << binaryNetworkAddress <<  endl */
         << setw(22) << left << " Network Increment: " << networkIncrement << endl
         << setw(22) << left << " Hosts/Net: " << setprecision(12) << maxHosts << endl;

    if (networkBoundary == 3) {
        cout << endl << endl;
        cout << setw(7) << left << "NET #" <<setw(20) << "NETWORK ADDRESS" << setw(35) << "HOST IPV4 RANGE" << setw(15) << "BROADCAST ADDRESS" << endl;
        cout << setw(79) << setfill('_') << "" << endl;
        cout << setfill (' ');
        for (int i = 0; i < subnetQty; i++) {
            subnetOctet = broadcastOctet + 1;
            broadcastOctet = (subnetOctet + networkIncrement) - 1;
            hostOctetMin = subnetOctet +1;
            hostOctetMax = broadcastOctet - 1;

            ostringstream temp0;
            temp0 << octet1 << '.' << octet2 << '.' << octet3 << '.' << subnetOctet;
            subnetID = temp0.str();

            ostringstream temp1;
            temp1 << octet1 << '.' << octet2 << '.' << octet3 << '.' << broadcastOctet;
            broadcastAddress = temp1.str();

            ostringstream temp2;
            temp2 << octet1 << '.' << octet2 << '.' << octet3 << '.' << hostOctetMin;
            hostMin = temp2.str();

            ostringstream temp3;
            temp3 << octet1 << '.' << octet2 << '.' << octet3 << '.' << hostOctetMax;
            hostMax = temp3.str();

            ostringstream temp4;
            temp4 << hostMin << " - " << hostMax;
            hostRange = temp4.str();

            cout << left << "S" << i + 1 << setw(5) << " | " << setw(20) << subnetID << setw(35) << hostRange <<  setw(15) << broadcastAddress << endl
                 << setw(79) << setfill('_') << "" << endl
                 << setfill (' ');
            if (broadcastOctet == 255) {
                break;
            }
        }
    }

    else if (networkBoundary == 2) {
        cout << endl << endl;
        cout << setw(7) << left << "NET #" <<setw(20) << "NETWORK ADDRESS" << setw(35) << "HOST ADDRESS RANGE" << setw(15) << "BROADCAST ADDRESS" << endl;
        cout << setw(79) << setfill('_') << "" << endl;
        cout << setfill (' ');

        for (octet3; octet3 < 256; ++octet3) {
                if (broadcastOctet == 255) {
                    broadcastOctet = -1;
                }
            for (int i = 0; i < subnetQty && broadcastOctet < 255; ++i) {
                subnetOctet = broadcastOctet + 1;
                broadcastOctet = (subnetOctet + networkIncrement) - 1;
                hostOctetMin = subnetOctet +1;
                hostOctetMax = broadcastOctet - 1;

                ostringstream temp0;
                temp0 << octet1 << '.' << octet2 << '.' << octet3 << '.' << subnetOctet;
                subnetID = temp0.str();

                ostringstream temp1;
                temp1 << octet1 << '.' << octet2 << '.' << octet3 << '.' << broadcastOctet;
                broadcastAddress = temp1.str();

                ostringstream temp2;
                temp2 << octet1 << '.' << octet2 << '.' << octet3 << '.' << hostOctetMin;
                hostMin = temp2.str();

                ostringstream temp3;
                temp3 << octet1 << '.' << octet2 << '.' << octet3 << '.' << hostOctetMax;
                hostMax = temp3.str();

                ostringstream temp4;
                temp4 << hostMin << " - " << hostMax;
                hostRange = temp4.str();

                cout << left << "S" << subnetsMade << setw(5) << " | " << setw(20) << subnetID << setw(35) << hostRange <<  setw(15) << broadcastAddress << endl
                     << setw(79) << setfill('_') << "" << endl
                     << setfill (' ');
                subnetsMade = subnetsMade + 1;
                if (subnetsMade > subnetQty) {
                    return;
                }
            }
        }
    }
}

//Separates subnet mask into decimal integer values then calculates octet values in binary
int Network::getSubnetOctets(string) {
    int dotLocation = 0;

    //Iterates through each char in the subnetIP, pulls out the octets, and converts them to integers.
    for (int i = 0; i < subnetMask.size(); ++i) { // Once Octet4 is complete, end loop.
        // Get subnetOctet1 from user IP and initialize
        if (subnetMask.at(i) == '.' && subnetOctet1 == -1) {
            subnetOctet1 = stoi(subnetMask.substr(dotLocation, i));
            ostringstream temp;
            temp << bitset<8>(subnetOctet1);
            subnetOctet1Binary = temp.str();
            dotLocation = i;
        }
        // Get octet 2 from user IP and initialize
        else if (subnetMask.at(i) == '.' && subnetOctet2 == -1) {
            subnetOctet2 = stoi(subnetMask.substr(dotLocation +1, i));
            ostringstream temp;
            temp << bitset<8>(subnetOctet2);
            subnetOctet2Binary = temp.str();
            dotLocation = i;
        }
        // Get octet 3 from user IP and initialize
        else if (subnetMask.at(i) == '.' && subnetOctet3 == -1) {
            subnetOctet3 = stoi(subnetMask.substr(dotLocation +1, i));
            ostringstream temp;
            temp << bitset<8>(subnetOctet3);
            subnetOctet3Binary = temp.str();
            dotLocation = i;
        }
        // Get octet 4 from user IP and initialize
        else if (subnetOctet3 > -1) {
            subnetOctet4 = stoi(subnetMask.substr(dotLocation +1, subnetMask.size()));
            ostringstream temp;
            temp << bitset<8>(subnetOctet4);
            subnetOctet4Binary = temp.str();
            break;
        }
        ostringstream temp;
        temp << subnetOctet1Binary << subnetOctet2Binary << subnetOctet3Binary << subnetOctet4Binary;
        subnetBinary = temp.str();
    }

    if (networkIncrement == 0) {
        int bitCount = 0;

        if (subnetOctet1 != 255) {
            interestingOctet = subnetOctet1Binary;
            networkBoundary = 0;
            for (int i = 0; i < interestingOctet.length(); ++i) {
                if (interestingOctet.at(i) == '0') {
                    ++bitCount;
                }
            }
            networkIncrement = pow(2, bitCount);
            IPStream << 0 << '.' << 0 << '.' << 0 << '.' << 0 << " /" << CIDR;
            networkID = IPStream.str();
            IPStream.str("");
            IPStream << bitset<8>(0) << '.' << bitset<8>(0) << '.' << bitset<8>(0) << '.' << bitset<8>(0);
            networkIDBinary = IPStream.str();
        }
        else if (subnetOctet2 != 255) {
            interestingOctet = subnetOctet2Binary;
            networkBoundary = 1;
            for (int i = 0; i < interestingOctet.length(); ++i) {
                if (interestingOctet.at(i) == '0') {
                    ++bitCount;
                }
            }
            networkIncrement = pow(2, bitCount);
            IPStream << octet1 << '.' << 0 << '.' << 0 << '.' << 0 << " /" << CIDR;
            networkID = IPStream.str();
            IPStream.str("");
            IPStream << bitset<8>(octet1) << '.' << bitset<8>(0) << '.' << bitset<8>(0) << '.' << bitset<8>(0);
            networkIDBinary = IPStream.str();

        }
        else if (subnetOctet3 != 255) {
            interestingOctet = subnetOctet3Binary;
            networkBoundary = 2;
            for (int i = 0; i < interestingOctet.length(); ++i) {
                if (interestingOctet.at(i) == '0') {
                    ++bitCount;
                }
            }
            networkIncrement = pow(2, bitCount);
            IPStream << octet1 << '.' << octet2 << '.' << 0 << '.' << 0 << " /" << CIDR;
            networkID = IPStream.str();
            IPStream.str("");
            IPStream << bitset<8>(octet1) << '.' << bitset<8>(octet2) << '.' << bitset<8>(0) << '.' << bitset<8>(0);
            networkIDBinary = IPStream.str();
        }
        else if (subnetOctet4 != 255) {
            interestingOctet = subnetOctet4Binary;
            networkBoundary = 3;
            for (int i = 0; i < interestingOctet.length(); ++i) {
                if (interestingOctet.at(i) == '0') {
                    ++bitCount;
                }
            }
            networkIncrement = pow(2, bitCount);
            IPStream << octet1 << '.' << octet2 << '.' << octet3 << '.' << 0 << " /" << CIDR;
            networkID = IPStream.str();
            IPStream.str("");
            IPStream << bitset<8>(octet1) << '.' << bitset<8>(octet2) << '.' << bitset<8>(octet3) << '.' << bitset<8>(0);
            networkIDBinary = IPStream.str();
        }
    }

    // Output Table of Octets Stacked Horizontally
    cout  << setw(110) << setfill('_') << "" << endl << endl;
    cout  << setw(57) << setfill(' ') << "SUBNET MASK INFORMATION FOR: " << subnetMask << setw(10) << "CIDR /" << CIDR << endl << endl;

    cout << setw(9) << "" << setw(7) << "OCTET 1" << setw(11) << ""
	     << setw(9) << "" << setw(7) << "OCTET 2" << setw(11) << ""
		 << setw(9) << "" << setw(7) << "OCTET 3" << setw(11) << ""
		 << setw(9) << "" << setw(7) << "OCTET 4" << setw(11) << "" << endl
		 
         << setw(25) << setfill('-') << "" << "  " << setw(25) << "" << "  " << setw(25) << "" << "  " << setw(25) << "" << endl << setfill(' ') 
         
         << setw(2) << "" << setw(10) << left  << "Decimal" << "|" << setw(9) << right << "Binary" << setw(5) << ""
         << setw(2) << "" << setw(10) << left  << "Decimal" << "|" << setw(9) << right << "Binary" << setw(5) << ""
         << setw(2) << "" << setw(10) << left  << "Decimal" << "|" << setw(9) << right << "Binary" << setw(5) << ""
         << setw(2) << "" << setw(10) << left  << "Decimal" << "|" << setw(9) << right << "Binary" << endl
         
         << setw(25) << setfill('-') << "" << "  " << setw(25) << "" << "  " << setw(25) << "" << "  " << setw(25) << "" << endl << setfill(' ');
         
    cout << setw(2) << "" << setw(10) << left  << subnetOctet1 << "|" << setw(10) << right << subnetOctet1Binary << setw(4) << ""
         << setw(2) << "" << setw(10) << left  << subnetOctet2 << "|" << setw(10) << right << subnetOctet2Binary << setw(4) << ""
         << setw(2) << "" << setw(10) << left  << subnetOctet3 << "|" << setw(10) << right << subnetOctet3Binary << setw(4) << ""
         << setw(2) << "" << setw(10) << left  << subnetOctet4 << "|" << setw(10) << right << subnetOctet4Binary << setw(4) << "" << endl;
         
    cout << setw(110) << setfill('_') << "" << endl;

    return 0;
}

// Subnetting Function to find subnets and host information based on requirements for hosts and networks
int Network::startSubnetting() {

        if (error == true){
            return 1;
        }
        if (classIP == 'A') {
            for (int i = HOST_POWERS.size() -1; i >= 7; --i) {
                if ((pow(2, HOST_POWERS.at(i)) -2) >= hostQty) {
                    maxHosts = pow(2, HOST_POWERS.at(i)) -2;
                    subnetMask = CIDR_MASKS.at(i);
                    CIDR = CIDR_VALUES.at(i);
                    return 0;
                }
                else if (i == 7 && ((pow(2, HOST_POWERS.at(i)) -2) < hostQty)){
                    maxHosts = pow(2, HOST_POWERS.at(7)) -2;
                    error = true;
                    return 0;
                }
            }
        }
        else if (classIP == 'B') {
            for (int i = HOST_POWERS.size() -1; i >= 15; --i) {
                if ((pow(2, HOST_POWERS.at(i)) -2) >= hostQty) {
                    maxHosts = pow(2, HOST_POWERS.at(i)) -2;
                    subnetMask = CIDR_MASKS.at(i);
                    CIDR = CIDR_VALUES.at(i);
                    return 0;
                }
                 else if (i == 15 && ((pow(2, HOST_POWERS.at(i)) -2) < hostQty)){
                    maxHosts = pow(2, HOST_POWERS.at(15)) -2;
                    error = true;
                    return 0;
                }
            }
        }
        else if (classIP == 'C') {
            for (int i = HOST_POWERS.size() -1; i >= 23; --i) {
                if ((pow(2, HOST_POWERS.at(i)) -2) >= hostQty) {
                    maxHosts = pow(2, HOST_POWERS.at(i)) -2;
                    subnetMask = CIDR_MASKS.at(i);
                    CIDR = CIDR_VALUES.at(i);
                    return 0;
                }
                 else if (i == 23 && ((pow(2, HOST_POWERS.at(i)) -2) < hostQty)){
                    maxHosts = pow(2, HOST_POWERS.at(23)) -2;
                    cout << "This network address is incapable of providing the " << hostQty << " hosts required." << endl
                         << "The max number of hosts this IP address can provide is: " << maxHosts << endl
                         << "Please use a different IPv4. Goodbye.";
                    error = true;
                    return 0;
                }
            }
        }
    }

// Gets IP from user in a string and validates it for legal format.
void Network::getUserInfo() {
    	
        int dotCount = 0; //Count the number of '.' in the IP

        // Gets IP Address from User and ensures legal input
        do {
            dotCount = 0;
            cout << "Please Enter the IP Address for this network: ";
            cin >> userIP;
            for (int i = 0; i < userIP.size(); ++i) {
                if (userIP.at(i) == '.') {
                    ++dotCount;
                }
            }
        } while (userIP.size() < 7 || userIP.find('.') == string::npos || userIP.size() > 15 || dotCount > 3 || dotCount < 3);

        // Gets subnetQty from the user and ensures legal input
        do {
            cout << "Please Enter the number of subnets required for this network: ";
            cin >> subnetQty;
        } while (subnetQty < 1 && subnetQty > 65536);

        // Gets required number of hosts from user and ensures legal input
        do {
            cout << "Please Enter the number of hosts required for this network: ";
            cin >> hostQty;
        } while (hostQty < 2 && hostQty > 16777216 && cin.fail());
        
    // End of function getUserInfo()
    }

//Separates user ip into decimal integer values then calculates octet values in binary
int Network::getUserIPOctets(string userIP) {
    	cout << "Start of getUserIPOctets()" << endl;
    	
        int dotLocation = 0;
		
        //Iterates through each char in the userIP, pulls out the octets, and converts them to integers.
        for (int i = 0; i < userIP.size(); ++i) { // Once Octet4 is complete, end loop.
            // Get octet 1 from user IP and initialize
            if (userIP.at(i) == '.' && octet1 == -1) {
                octet1 = stoi(userIP.substr(dotLocation, i));
                ostringstream temp;
                temp << bitset<8>(octet1);
                octet1Binary = temp.str();
                dotLocation = i;
            }
            // Get octet 2 from user IP and initialize
            else if (userIP.at(i) == '.' && octet2 == -1) {
                octet2 = stoi(userIP.substr(dotLocation +1, i));
                ostringstream temp;
                temp << bitset<8>(octet2);
                octet2Binary = temp.str();
                dotLocation = i;
            }
            // Get octet 3 from user IP and initialize
            else if (userIP.at(i) == '.' && octet3 == -1) {
                octet3 = stoi(userIP.substr(dotLocation +1, i));
                ostringstream temp;
                temp << bitset<8>(octet3);
                octet3Binary = temp.str();
                dotLocation = i;
            }
            // Get octet 4 from user IP and initialize
            else if (octet3 > -1) {
                octet4 = stoi(userIP.substr(dotLocation +1, userIP.size()));
                ostringstream temp;
                temp << bitset<8>(octet4);
                octet4Binary = temp.str();
                break;
            }
        }
             
             
        // Output Table of Octets Stacked Horizontally
        cout << "\n\n" << setw(110) << setfill('_') << "" << endl << endl;
        cout << setw(60) << setfill(' ') << "IPv4 INFORMATION FOR: " << userIP << endl << endl;

        cout << setw(9) << "" << setw(7) << "OCTET 1" << setw(11) << ""
		     << setw(9) << "" << setw(7) << "OCTET 2" << setw(11) << ""
			 << setw(9) << "" << setw(7) << "OCTET 3" << setw(11) << ""
			 << setw(9) << "" << setw(7) << "OCTET 4" << setw(11) << "" << endl
			 
             << setw(25) << setfill('-') << "" << "  " << setw(25) << "" << "  " << setw(25) << "" << "  " << setw(25) << "" << endl << setfill(' ') 
             
             << setw(2) << "" << setw(10) << left  << "Decimal" << "|" << setw(9) << right << "Binary" << setw(5) << ""
             << setw(2) << "" << setw(10) << left  << "Decimal" << "|" << setw(9) << right << "Binary" << setw(5) << ""
             << setw(2) << "" << setw(10) << left  << "Decimal" << "|" << setw(9) << right << "Binary" << setw(5) << ""
             << setw(2) << "" << setw(10) << left  << "Decimal" << "|" << setw(9) << right << "Binary" << endl << flush
             
             << setw(25) << setfill('-') << "" << "  " << setw(25) << "" << "  " << setw(25) << "" << "  " << setw(25) << "" << endl << setfill(' ');
             
        cout << setw(2) << "" << setw(10) << left  << octet1 << "|" << setw(10) << right << octet1Binary << setw(4) << ""
             << setw(2) << "" << setw(10) << left  << octet2 << "|" << setw(10) << right << octet2Binary << setw(4) << ""
             << setw(2) << "" << setw(10) << left  << octet3 << "|" << setw(10) << right << octet3Binary << setw(4) << ""
             << setw(2) << "" << setw(10) << left  << octet4 << "|" << setw(10) << right << octet4Binary << setw(4) << "" << endl << endl;
             
    }

// Initializes class value based on octet1
int Network::getClass() {

        if (octet1 == 0) {
            classIP = '0';
            cout << "Octet 0 is reserved for default gateways and cannot be used. Goodbye.";
            error = true;
            return 1;
        }
        else if (octet1 >= 1 && octet1 <= 126) {
            cout << octet1;
            classIP = 'A';
            if (octet1 == 10) {
                ipType = "Private";
            }
            else {
                ipType = "Public";
            }
            return 0;
        }
        else if (octet1 == 127) {
            classIP = '0';
            cout << "\n\n" << setw(60) << "\tERROR!\n\n"
                 << "The IPv4 range of 127.0.0.0 - 127.255.255.255 is reserved for loop-back addresses and cannot be subnetted. Goodbye." << endl;
            error = true;
            return 1;
        }
        else if (octet1 <= 191) {
            classIP = 'B';
            if (octet1 == 172 && (octet2 >= 16 && octet2 <= 31)) {
                ipType = "Private";
                }
            else {
                ipType = "Public";
            }
            return 0;
        }
        else if (octet1 <=223) {
            classIP = 'C';
            if (octet1 == 192 && octet2 == 168) {
                ipType = "Private";
                }
            else {
                ipType = "Public";
            }
            return 0;
        }
        else {
            cout << "Only Class A - C IP Addresses should be used for a network. Goodbye";
            error = true;
            return 1;
        }
        return classIP;
    }
