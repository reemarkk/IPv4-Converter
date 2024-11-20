#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INADDR_NONE 0xFFFFFFFF

typedef unsigned int UINT32;
typedef unsigned char UINT8;
UINT32 ConvertIP(const char* pIP)
{
    if (!pIP || *pIP == '\0') return INADDR_NONE;  
    
    UINT32 dwAddr = 0;
    UINT32 dwOctet = 0;
    UINT8 dwCompletedOctetCount = 0;
    
    // Read IP string
    while (*pIP) { 
        dwOctet = 0;
        while (*pIP >= '0' && *pIP <= '9') {  
            dwOctet = dwOctet * 10 + (*pIP - '0');  
            pIP++;
        }
        
        
        if (dwOctet > 255 || dwCompletedOctetCount >= 4) {
            return INADDR_NONE;  
        }
       
        dwAddr = (dwAddr << 8) | dwOctet;
        dwCompletedOctetCount++;  
        
        if (*pIP == '.') {
             if (dwCompletedOctetCount==4){
                  return INADDR_NONE;
             }
            else 
            {
                 pIP++;
                 
            }  
            if (*pIP == '.') {
                return INADDR_NONE; 
            }
        }
    }
    
 
    if (dwCompletedOctetCount == 4 && *pIP == '\0') {
        return dwAddr; 
    } else {
        return INADDR_NONE;  
    }
}

#define GREEN "\033[32m"
#define RED "\033[31m"
#define RESET "\033[0m"

// Test a single IP string
void TestIP(const char* ip, UINT32 expected) {
    UINT32 result = ConvertIP(ip);
    if ((result == expected) || (result == INADDR_NONE && expected == INADDR_NONE)) {
        printf(GREEN "Test Passed: %s -> 0x%08X\n" RESET, ip ? ip : "NULL", result);
    }
    else {
        printf(RED "Test Failed: %s (Expected: 0x%08X, Got: 0x%08X)\n" RESET, ip ? ip : "NULL", expected, result);
    }
}

int main(void) {
    printf("Running IP conversion tests...\n");

    // Valid IP addresses
    TestIP("0.0.0.0", 0x00000000);
    TestIP("255.255.255.255", 0xFFFFFFFF);
    TestIP("1.2.3.4", 0x01020304);
    TestIP("10.0.0.1", 0x0A000001);
    TestIP("172.16.0.1", 0xAC100001);
    TestIP("192.168.100.200", 0xC0A864C8);

    // Boundary cases
    TestIP("255.255.255.256", INADDR_NONE); // Out of range last octet
    TestIP("256.0.0.1", INADDR_NONE);      // Out of range first octet
    TestIP("192.168.1.0.", INADDR_NONE);   // Extra dot at the end
    TestIP("192.168.1", INADDR_NONE);      // Missing an octet
    TestIP("1..1.1", INADDR_NONE);         // Double dots
    TestIP(".1.1.1.1", INADDR_NONE);       // Leading dot
    TestIP("1.1.1.1.", INADDR_NONE);       // Trailing dot

    // Invalid characters
    TestIP("192.abc.1.1", INADDR_NONE);    // Non-numeric character
    TestIP("abcd", INADDR_NONE);           // Non-IP string
    TestIP("1.1.1.one", INADDR_NONE);      // Non-numeric character in octet

    // Empty and NULL cases
    TestIP("", INADDR_NONE);               // Empty string
    TestIP(NULL, INADDR_NONE);             // NULL input

    // Leading/trailing spaces
    TestIP(" 192.168.1.1", INADDR_NONE);   // Leading space
    TestIP("192.168.1.1 ", INADDR_NONE);   // Trailing space
    TestIP(" 192.168.1.1 ", INADDR_NONE);  // Both leading and trailing spaces

    // Special cases
    TestIP("000.000.000.000", 0x00000000); // Leading zeros in octets
    TestIP("001.002.003.004", 0x01020304); // Leading zeros with valid values
    TestIP("127.0.0.1", 0x7F000001);      // Loopback address
    TestIP("8.8.8.8", 0x08080808);        // Public DNS server

    // Overly long inputs
    TestIP("1.1.1.1.1", INADDR_NONE);     // Too many octets
    TestIP("1.1.1.11111", INADDR_NONE);   // Oversized single octet

    // Mixed delimiters
    TestIP("192,168,1,1", INADDR_NONE);   // Comma as a delimiter

    printf("All tests completed.\n");
    return 0;
}
