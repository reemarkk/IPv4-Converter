//
//  main.m
//  IPv4
//
//  Created by R's MacBook on 19.11.24.
//
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

int main(void)
{
    UINT32 dwAddr = 0;
    const char pIP[] = "1.1.1.1";
    UINT32 status = ConvertIP(pIP, &dwAddr);
    if (status == 0)
    {
        printf("Converted IP: 0x%08X\n", dwAddr);
    }
    else
    {
        printf("Failed to convert IP\n");
    }
    return 0;
}
