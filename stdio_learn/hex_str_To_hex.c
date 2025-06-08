/********************************************************************
        created:	2012/02/21
        filename: 	hex_string_to_hex.c
        author:

        purpose:
*********************************************************************/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//-------------------------------------------------------------------

static int oneHexCharToHex(char h_item)
{
	int item = 0;
	if (isdigit(h_item)) {
		item = h_item - '0';
	} else if (isupper(h_item)) {
		item = h_item - 'A' + 10;
	} else {
		item = h_item - 'a' + 10;
	}
	return item;
}

/*Chaneg TEXT HEX such as E5BC35 to
 * E5BC35 -->0xe5,0xbc,0x35
 * inStr must >0 otherwise return -1*/
int ChangeTHEX2CPTR(const char *inHexString, char *outHex)
{
	int success = -1;
	unsigned int len = 0;
	int index;
	int ch1;
	int ch2;
	do {
		if (NULL == inHexString || NULL == outHex) {
			printf("error: inHexString or outHex is null!\n");
			break;
		}
		len = strlen(inHexString);
		if (len <= 1) {
			printf("error: strlen(inHexString) <= 1!\n");
			break;
		}
		len &= ~1;
		for (index = 0; index < len; index += 2) {
			ch1 = (int)inHexString[index];
			ch2 = (int)inHexString[index + 1];
			outHex[index / 2 + 1] = 0;
			if (isxdigit(ch1) && isxdigit(ch2)) {
				ch1 = oneHexCharToHex((char)ch1);
				ch2 = oneHexCharToHex((char)ch2);
				outHex[index / 2] = (char)((ch1 << 4) | ch2);
			} else {
				printf("error: %c or %c is not hex digit!\n",
				       ch1, ch2);
				goto exit;
			}
		}
		success = 0; // OK
	} while (0);
exit:
	return success;
}

#define TEST_ChangeTHEX2CPTR
#ifdef TEST_ChangeTHEX2CPTR

static void printf_outHex(const char *outHex)
{
	unsigned int len = strlen(outHex);
	int index;
	for (index = 0; index < len; index++) {
		printf("0x%x,", outHex[index] & 0xff);
	}
	printf("\n");
}

void test_ChangeTHEX2CPTR(void)
{
	char buffer[256] = { 0 };

	ChangeTHEX2CPTR("E", buffer);
	printf_outHex(buffer);

	ChangeTHEX2CPTR("E5BC35", buffer);
	printf_outHex(buffer);

	ChangeTHEX2CPTR("EX4", buffer);
	printf_outHex(buffer);

	ChangeTHEX2CPTR("E5B", buffer);
	printf_outHex(buffer);
}
#endif

int demo_hexTostr_main(int argc, char *argv[])
{
	test_ChangeTHEX2CPTR();
	return 0;
}
//-------------------------------------------------------------------
