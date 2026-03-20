# Description
This C program converts *IPv4* addresses from string format (like "192.168.1.1") into *32-bit unsigned integers* (UINT32).
It validates the IP string, ensuring each octet is 0–255, and detects errors such as missing octets, extra dots, non-numeric characters, or NULL/empty input.
Invalid IPs return `INADDR_NONE` (0xFFFFFFFF). 
The program includes a set of test cases with colored output (green for pass, red for fail) to quickly verify correctness, and it supports leading zeros in octets.
