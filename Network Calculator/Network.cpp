#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <bits/stdc++.h>
#include <cmath>

using namespace std;
#include "Network.h"

// -------------------------------------------------------------------------------------- NETWORK CLASS FUNCTIONS -------------------------------------------------------------------------------------- //

// Prints a block of IP addresses for a subnet ---------------------------------------------------------------------------------- [GOOD]
void Network::printSubnetBlock() {
	++subnetCount;
    
        hostOctetMin = octet4 +1;
        hostOctetMax = broadcastOctet4 - 1;

        ostringstream temp2;
        temp2 << octet1 << '.' << octet2 << '.' << octet3 << '.' << hostOctetMin;
        hostMin = temp2.str();

        ostringstream temp3;
        temp3 << broadcastOctet1 << '.' << broadcastOctet2 << '.' << broadcastOctet3 << '.' << hostOctetMax;
        hostMax = temp3.str();

        ostringstream temp4;
        temp4 << hostMin << " - " << hostMax;
        hostRange = temp4.str();

        cout << left << "S" << setw(2) << subnetCount << setw(5) << " | " << setw(20) << networkID << setw(35) << hostRange <<  setw(15) << broadcastAddress << endl
             << setw(79) << setfill('_') << "" << endl
             << setfill (' ');
} 

// Increments subnets untill subnetQty is met ----------------------------------------------------------------------------------- [GOOD]
void Network::incrementSubnet() {
	
	int tO1;
	int tO2;
	int tO3;
	int tO4;
	bool increment = true;
	
	if (broadcastOctet4 == 255) {
        	tO4 = 0;
        	increment = true;
        } else if (increment){
        	tO4 = ++broadcastOctet4;
        	tO3 = broadcastOctet3;
        	tO2 = broadcastOctet2;
        	tO1 = broadcastOctet1;
        	increment = false;
        } 
        
		if (broadcastOctet3 == 255 && increment) {
    		tO3 = 0;
    		increment = true;
    	} else if (increment){
			tO3 = ++broadcastOctet3;
    		tO2 = broadcastOctet2;
    		tO1 = broadcastOctet1;
    		increment = false;
		}
        		
    	if (broadcastOctet2 == 255 && increment) {
    		tO2 = 0;
    		tO1 = ++broadcastOctet1;
    	} else if (increment){
    		tO2 = ++broadcastOctet2;
        	tO1 = broadcastOctet1;
        	increment = false;
		}

		ostringstream temp;
		temp << tO1 << '.' << tO2 << '.' << tO3 << '.' << tO4; 
		networkID = temp.str();

		octet1 = -1;
		octet2 = -1;
		octet3 = -1;
		octet4 = -1;
		
		getUserIPOctets(networkID);
		
		ostringstream temp1;
		temp1 << decToBin(octet1) << '.' << decToBin(octet2) << '.' << decToBin(octet3) << '.' << decToBin(octet4);
		networkIDBinary = temp1.str();
		
		getBroadcastIP(networkIDBinary);
}

// Gets broadcast address from a given wildcard and network ID ------------------------------------------------------------------ [GOOD]
string Network::getBroadcastIP(string networkIDBinary) {
	
	string temp = "00000000.00000000.00000000.00000000";
	string t1 = "00000000";
	string t2 = "00000000";
	string t3 = "00000000";
	string t4 = "00000000";

	for (int i = 0; i < 35; ++i) {
			temp.at(i) = networkIDBinary.at(i) | hostMaskBinary.at(i);
	}
	
	
	for (int i = 0; i < 8; ++i) {
		t1.at(i) = temp.at(i);
	}
	for (int i = 9; i < 17; ++i) {
		t2.at(i-9) = temp.at(i);
	}
	for (int i = 18; i < 26; ++i) {
		t3.at(i - 18) = temp.at(i);
	}
	for (int i = 27; i < 35; ++i) {
		t4.at(i - 27) = temp.at(i);
	}
	
	broadcastOctet1 = binToDec(t1);
	broadcastOctet2 = binToDec(t2);
	broadcastOctet3 = binToDec(t3);
	broadcastOctet4 = binToDec(t4);
	
	ostringstream tempb;
	tempb << t1 << '.' << t2 << '.' << t3 << '.' << t4;
	broadcastAddressBinary = tempb.str();
	
	ostringstream tempa;
	tempa << broadcastOctet1 << '.' << broadcastOctet2 << '.' << broadcastOctet3 << '.' << broadcastOctet4;
	broadcastAddress = tempa.str();
	
return broadcastAddress;	
}
	
// Gets host mask from subnet mask using bitwise operator ----------------------------------------------------------------------- [GOOD]
int Network::getHostMask() {
	
	ostringstream temp;
    temp << ~bitset<8>(subnetOctet1);
    hostMaskOctet1Binary = temp.str();
    hostMaskOctet1 = binToDec(hostMaskOctet1Binary);
        
    ostringstream temp2;
    temp2 << ~bitset<8>(subnetOctet2);
    hostMaskOctet2Binary = temp2.str();
    hostMaskOctet2 = binToDec(hostMaskOctet2Binary);
        
    ostringstream temp3;
    temp3 << ~bitset<8>(subnetOctet3);
    hostMaskOctet3Binary = temp3.str();
    hostMaskOctet3 = binToDec(hostMaskOctet3Binary);
    
    ostringstream temp4;
    temp4 << ~bitset<8>(subnetOctet4);
    hostMaskOctet4Binary = temp4.str();
    hostMaskOctet4 = binToDec(hostMaskOctet4Binary);
    
    ostringstream temp5;
    temp5 << hostMaskOctet1Binary << '.' << hostMaskOctet2Binary << '.' << hostMaskOctet3Binary << '.' << hostMaskOctet4Binary;
    hostMaskBinary = temp5.str();
    
    ostringstream temp6;
    temp6 << hostMaskOctet1 << '.' << hostMaskOctet2<< '.' << hostMaskOctet3 << '.' << hostMaskOctet4;
    hostMask = temp6.str();
    
return 0;   
}

// Gets the network increment, network bits, and host bits using the subnet mask. ------------------------------ Step 5 --------- [GOOD] 
int Network::getNetworkIncrement(string) {

        if (subnetOctet1 != 255) {
            interestingOctetBinary = subnetOctet1Binary;
            networkBoundary = 0;

            networkIncrement = pow(2, hostBits);
            IPStream << 0 << '.' << 0 << '.' << 0 << '.' << 0;
            networkID = IPStream.str();
            IPStream.str("");
            IPStream << bitset<8>(0) << '.' << bitset<8>(0) << '.' << bitset<8>(0) << '.' << bitset<8>(0);
            networkIDBinary = IPStream.str();
        }
        else if (subnetOctet2 != 255) {
            interestingOctetBinary = subnetOctet2Binary;
            networkBoundary = 1;

            networkIncrement = pow(2, hostBits);
            IPStream << octet1 << '.' << 0 << '.' << 0 << '.' << 0;
            networkID = IPStream.str();
            IPStream.str("");
            IPStream << bitset<8>(octet1) << '.' << bitset<8>(0) << '.' << bitset<8>(0) << '.' << bitset<8>(0);
            networkIDBinary = IPStream.str();

        }
        else if (subnetOctet3 != 255) {
            interestingOctetBinary = subnetOctet3Binary;
            networkBoundary = 2;
            
            networkIncrement = pow(2, hostBits);
            IPStream << octet1 << '.' << octet2 << '.' << 0 << '.' << 0;
            networkID = IPStream.str();
            IPStream.str("");
            IPStream << bitset<8>(octet1) << '.' << bitset<8>(octet2) << '.' << bitset<8>(0) << '.' << bitset<8>(0);
            networkIDBinary = IPStream.str();
        }
        else if (subnetOctet4 != 255) {
            interestingOctetBinary = subnetOctet4Binary;
            networkBoundary = 3;
            
            networkIncrement = pow(2, hostBits);
            IPStream << octet1 << '.' << octet2 << '.' << octet3 << '.' << 0;
            networkID = IPStream.str();
            IPStream.str("");
            IPStream << bitset<8>(octet1) << '.' << bitset<8>(octet2) << '.' << bitset<8>(octet3) << '.' << bitset<8>(0);
            networkIDBinary = IPStream.str();
        }
}

// Gets IP, subnetQty, and hostQty from user and validates them for legal values. ------------------------------ Step 1 --------- [GOOD]
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
            cout << "Please Enter the number of subnets required for this network (For max type '9'): ";
            cin >> subnetQty;
            if (subnetQty == 9) {
            	subnetQty = 65536;
			}
        } while (subnetQty < 1 && subnetQty > 65536);

        // Gets required number of hosts from user and ensures legal input
        do {
            cout << "Please Enter the total number of hosts needed per network: ";
            cin >> hostQty;
            hostQty;
        } while (hostQty < 2 && hostQty > 16777216 && cin.fail());
        
    // End of function getUserInfo()
    }

//Separates user ip string into integer octets then calculates octet values in binary -------------------------- Step 2 --------- [GOOD]
int Network::getUserIPOctets(string IP) {
    	
        int dotLocation = 0;
		
        //Iterates through each char in the IP, pulls out the octets, and converts them to integers.
        for (int i = 0; i < IP.size(); ++i) { // Once Octet4 is complete, end loop.
            // Get octet 1 from user IP and initialize
            if (IP.at(i) == '.' && octet1 == -1) {
                octet1 = stoi(IP.substr(dotLocation, i));
                octet1Binary = decToBin(octet1);
                dotLocation = i;
            }
            // Get octet 2 from user IP and initialize
            else if (IP.at(i) == '.' && octet2 == -1) {
                octet2 = stoi(IP.substr(dotLocation +1, i));
                octet2Binary = decToBin(octet2);
                dotLocation = i;
            }
            // Get octet 3 from user IP and initialize
            else if (IP.at(i) == '.' && octet3 == -1) {
                octet3 = stoi(IP.substr(dotLocation +1, i));
                octet3Binary = decToBin(octet3);
                dotLocation = i;
            }
            // Get octet 4 from user IP and initialize
            else if (octet3 > -1) {
                octet4 = stoi(IP.substr(dotLocation +1, IP.size()));
                octet4Binary = decToBin(octet4);
                break;
            }
        }     
    }

// Prints out basic information for NetworkID Octets ----------------------------------------------------------- Step 3 --------- [GOOD]
void Network::printNetInfo() {
	// Output Table of Octets Stacked Horizontally
        cout << "\n\n" << setw(110) << setfill('_') << "" << endl << endl;
        cout << setw(60) << setfill(' ') << "NETWORK IPv4 INFORMATION FOR: " << userIP << endl << endl;

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
             << setw(2) << "" << setw(10) << left  << octet4 << "|" << setw(10) << right << octet4Binary << setw(4) << "" << endl;
             
        // Output Table of Subnet Octets Stacked Horizontally
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
}	

// Prints out subnets, associated IP addresses, and network information to the user ---------------------------- Step 7 --------- [GOOD]
void Network::printFinal() {
    
    cout << setfill(' ') << endl
         << setw(22) << left << " IP Address: " << setw(20) << userIP << octet1Binary <<  "." << octet2Binary << "." << octet3Binary << "." << octet4Binary << endl
         << setw(22) << left << " Netmask: " << setw(20) << subnetMask << subnetOctet1Binary <<  "." << subnetOctet2Binary << "." << subnetOctet3Binary << "." << subnetOctet4Binary << endl
         << setw(22) << left << " Wildcard:" << setw(20) << hostMask << hostMaskBinary << endl
         << setw(22) << left << " Network: " << setw(20) << networkID << networkIDBinary << " (Class " << classIP << " " << ipType << ")" << endl
         << setw(22) << left << " Network Boundary " << "Octet " << networkBoundary << endl
         << setw(22) << left << " Network Increment: " << networkIncrement << endl
         << setw(22) << left << " Network Bits: " << networkBits << endl
         << setw(22) << left << " Host Bits: " << hostBits << endl
         << setw(22) << left << " Max Subnets: " << setprecision(12) << maxSubnets  << endl
         << setw(22) << left << " Max Hosts: " << setprecision(12) << maxHosts  << endl << endl;
         
        cout << setw(8) << left << "NET #" <<setw(20) << "NETWORK ADDRESS" << setw(35) << "HOST IPV4 RANGE" << setw(15) << "BROADCAST ADDRESS" << endl;
        cout << setw(79) << setfill('_') << "" << endl;
        cout << setfill (' ');

	for (int i = 0; i < subnetQty; ++i) {
		printSubnetBlock();
		incrementSubnet();
	}
        
}

//Separates subnet mask into decimal integer values then calculates octet values in binary --------------------- Step 5 --------- [GOOD]
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

    return 0;
}

// Find subnets and host information based on requirements for hosts and networks ------------------------------ Step 4 --------- [GOOD]
int Network::startSubnetting() {

        for (int i = HOST_POWERS.size() -1; i >= 1; --i) {
            if ((pow(2, HOST_POWERS.at(i)) -2) >= hostQty && (pow(2, CIDR_VALUES.at(i))) >= subnetQty) {
                maxHosts = (pow(2, HOST_POWERS.at(i)) - 2);
                maxSubnets = (pow(2, CIDR_VALUES.at(i)));
                subnetMask = CIDR_MASKS.at(i);
                CIDR = CIDR_VALUES.at(i);
                networkBits = CIDR;
                hostBits = 32 - CIDR;
                
                return 0;
            }
        }
    }
        
// Initializes class value based on octet1 --------------------------------------------------------------------- Step 5 --------- [GOOD]
int Network::getClass() {

        if (octet1 == 0) {
            classIP = '0';
            cout << "Octet 0 is reserved for default gateways and cannot be used. Goodbye.";
            error = true;
            return 1;
        }
        else if (octet1 >= 1 && octet1 <= 126) {
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
                 << "The IPv4 range of 127.0.0.0 - 127.255.255.255 is reserved for loop-back addresses and should not be subnetted. Goodbye." << endl;
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

// Converts an 8 bit binary string into a decimal value ------------------------------------------------------------------------- [GOOD]
int Network::binToDec(string binary) {
	int decimal = 0;
	vector <int> DECIMAL_VALUES = {128,64,32,16,8,4,2,1};
	
		for (int j = 0; j < binary.length(); ++j) {
			if (binary.at(j) == '1') {
				decimal = decimal + DECIMAL_VALUES.at(j);
			}
		}
return decimal;
}

// Converts an 8 bit decimal value into a binary string ------------------------------------------------------------------------- [GOOD]
string Network::decToBin(int decimal) {

	string binary = "00000000";
		vector <int> DECIMAL_VALUES = {128,64,32,16,8,4,2,1};
		
		for (int j = 0; j < binary.length(); ++j) {
				if (decimal - DECIMAL_VALUES.at(j) >= 0) {
					binary.at(j) = '1';
					decimal -= DECIMAL_VALUES.at(j);
				}
		}
		
return binary;	
}
