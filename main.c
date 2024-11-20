#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define INADDR_NONE 0xffffffff

typedef unsigned int UINT32;
typedef unsigned char UINT8;


UINT32 ConvertIP(const char* pIP, UINT32* pdwAddr)
{
    if (!pIP || *pIP=='\0') return INADDR_NONE;
    printf("ConvertIP(pIP: %s, pdwAddr: 0x%p)\n", pIP, pdwAddr);
    
    UINT32 dwAddr = 0;
    UINT32 dwOctet = 0;
    UINT8 dwCompletedOctetCount = 0;
    
    // read IP string
    while (*pIP ){      // while pIP is not equal to '\0'
        
        dwOctet = 0;    //each time for new value
        
        while (*pIP>='0' && *pIP<='9'){
            dwOctet = dwOctet * 10 + (*pIP - '0');  //as long as character is digit char into integer
            pIP++;
            }
        
        if(dwOctet > 255 || dwCompletedOctetCount >= 4){    //invalid cases
            return INADDR_NONE;
            }
        
        dwAddr = (dwAddr<<8)| dwOctet;
        dwCompletedOctetCount++;
        
        if(*pIP=='.')
            pIP++;
    }
    
    if (dwCompletedOctetCount==4){
        *pdwAddr=dwAddr;
        return 0;
    }
    
    else
        return INADDR_NONE;
}


int Tests(void) {
    UINT32 dwAddr = 0;
    UINT32 result;

    // Test 1
    result = ConvertIP("1.1.1.1", &dwAddr);
    if (result != 0) {
        printf("Test Failed: 1.1.1.1 (Expected: 0x01010101, Got: 0x%08X)\n", dwAddr);
    } else if (dwAddr != 0x01010101) {
        printf("Test Failed: 1.1.1.1 (Expected: 0x01010101, Got: 0x%08X)\n", dwAddr);
    } else {
        printf("Test Passed: 1.1.1.1 -> 0x%08X\n", dwAddr);
    }

    // Test 2
    result = ConvertIP("192.168.1.1", &dwAddr);
    if (result != 0) {
        printf("Test Failed: 192.168.1.1 (Expected: 0xC0A80101, Got: 0x%08X)\n", dwAddr);
    } else if (dwAddr != 0xC0A80101) {
        printf("Test Failed: 192.168.1.1 (Expected: 0xC0A80101, Got: 0x%08X)\n", dwAddr);
    } else {
        printf("Test Passed: 192.168.1.1 -> 0x%08X\n", dwAddr);
    }

    // Test 3
    result = ConvertIP("256.256.256.256", &dwAddr);
    if (result == 0) {
        printf("Test Failed: 256.256.256.256 (Expected: INADDR_NONE, Got: 0x%08X)\n", dwAddr);
    } else {
        printf("Test Passed: 256.256.256.256 is invalid as expected\n");
    }

    // Test 4
    result = ConvertIP("1.1.1", &dwAddr);
    if (result == 0) {
        printf("Test Failed: 1.1.1 (Expected: INADDR_NONE, Got: 0x%08X)\n", dwAddr);
    } else {
        printf("Test Passed: 1.1.1 is invalid as expected\n");
    }

    // Test 5
    result = ConvertIP("abc.def.ghi.jkl", &dwAddr);
    if (result == 0) {
        printf("Test Failed: abc.def.ghi.jkl (Expected: INADDR_NONE, Got: 0x%08X)\n", dwAddr);
    } else {
        printf("Test Passed: abc.def.ghi.jkl is invalid as expected\n");
    }

    // Test 6
    result = ConvertIP("", &dwAddr);
    if (result == 0) {
        printf("Test Failed: Empty string (Expected: INADDR_NONE, Got: 0x%08X)\n", dwAddr);
    } else {
        printf("Test Passed: Empty string is invalid as expected\n");
    }

    // Test 7: NULL string
    result = ConvertIP(NULL, &dwAddr);
    if (result == 0) {
        printf("Test Failed: NULL (Expected: INADDR_NONE, Got: 0x%08X)\n", dwAddr);
    } else {
        printf("Test Passed: NULL is invalid as expected\n");
    }

    return 0;
}

int main(void){
    Tests();
}
