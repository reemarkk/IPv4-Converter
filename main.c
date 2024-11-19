#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef unsigned int UINT32;
typedef unsigned char UINT8;

UINT32 ConvertIP(const char* pIP, UINT32* pdwAddr)
{
    if (!pIP || *pIP=='\0') return 1;
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
            return 1;
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
        return 1;
}
int runTest(const char* ipAddress, UINT32 expectedResult) {
    
    UINT32 dwAddr = 0;
    UINT32 status = ConvertIP(ipAddress, &dwAddr);

    if (status == 0) {
        if (dwAddr == expectedResult) {
            printf("Test Passed: %s -> 0x%08X\n", ipAddress, dwAddr);
            return 1;
        }
        else {
            printf("Test Failed: %s -> 0x%08X (Expected: 0x%08X)\n", ipAddress, dwAddr, expectedResult);
            return 0;
        }
    }
    else {
        printf("Test Failed: Invalid IP format -> %s\n", ipAddress);
        return 0;
    }
}

int main(void) {
    int testResult = 1;
    
    // Valid test cases
    testResult &= runTest("1.1.1.1", 0x01010101);
    testResult &= runTest("192.168.1.1", 0xC0A80101);
    testResult &= runTest("255.255.255.255", 0xFFFFFFFF);
    testResult &= runTest("0.0.0.0", 0x00000000);
    
    // Invalid test cases
    testResult &= runTest("256.256.256.256", 0);
    testResult &= runTest("1.1.1", 0);
    testResult &= runTest("1.1.1.1.1", 0);
    testResult &= runTest("abc.def.ghi.jkl", 0);
    testResult &= runTest("1.1.1.300", 0);
    testResult &= runTest("", 0);
    testResult &= runTest(NULL, 0);
    
    if (testResult) {
        printf("\nAll tests passed!\n");
    } else {
        printf("\nSome tests failed.\n");
    }

    return 0;
}
