#ifndef NETWORK_H
#define NETWORK_H

class Network {
		
	    public:
		    // IP Address Variables and Functions ----------------------------------------------------------------------------------------------
		    void getUserInfo();
		    int getUserIPOctets(string userIP);
		    int getClass();
		    void printNetInfo();
		    int getNetworkIncrement(string);
		    int binToDec(string binary);
		    string decToBin(int decimal);
		    int startSubnetting();
		    int getSubnetOctets(string);
		    void printFinal();
		    int getHostMask();
		    string getBroadcastIP(string networkID);
		    void printSubnetBlock();
		    void incrementSubnet();
		    
		    
		    string userIP = "";           // User IP is the IP address initialized via standard input from the user.
		    long long hostQty = 0;           // Number of hosts required per subnet
		    long long subnetQty = 0;            // Number of subnets required for the network
		    long long maxHosts = 0;
		    long long totalHosts = 0;
		
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
		    long long maxSubnets = 0;
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
		    int subnetCount = 0;
		    
		    // Host Mask Variables
		    string hostMask = "";
		    string hostMaskBinary = "";
		    int hostMaskOctet1 = -1;
		    string hostMaskOctet1Binary = "";
		    int hostMaskOctet2 = -1;
		    string hostMaskOctet2Binary = "";
		    int hostMaskOctet3 = -1;
		    string hostMaskOctet3Binary = "";
		    int hostMaskOctet4 = -1;
		    string hostMaskOctet4Binary = "";
		
		
		    // Network Increment Variables ---------------------------------------------------------------
		    double networkIncrement = 0;
		    string interestingOctetBinary = "";
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
		    int hostBits;
		    int networkBits;
		
		    // Broadcast Address variables ---------------------------------------------------------------
		    string broadcastAddress = "";
		    string broadcastAddressBinary = "";
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
		

	};


#endif
