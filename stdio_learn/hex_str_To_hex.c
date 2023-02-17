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

static int oneHexCharToHex(char h)
{
    int x = 0;
    if (isdigit(h))
    {
        x = h - '0';
    }
    else if (isupper(h))
    {
        x = h - 'A' + 10;
    }
    else
    {
        x = h - 'a' + 10;
    }
    return x;
}

/*Chaneg TEXT HEX such as E5BC35 to
 * E5BC35 -->0xe5,0xbc,0x35
 * inStr must >0 otherwise return -1*/
int ChangeTHEX2CPTR(const char *inHexString, char *outHex)
{
    int success = -1;
    int len = 0;
    int i;
    char ch1, ch2;
    do
    {
        if (NULL == inHexString || NULL == outHex)
        {
            printf("error: inHexString or outHex is null!\n");
            break;
        }
        len = strlen(inHexString);
        if (len <= 1)
        {
            printf("error: strlen(inHexString) <= 1!\n");
            break;
        }
        len &= ~1;
        for (i = 0; i < len; i += 2)
        {
            ch1 = inHexString[i];
            ch2 = inHexString[i + 1];
            outHex[i / 2 + 1] = 0;
            if (isxdigit(ch1) && isxdigit(ch2))
            {
                ch1 = oneHexCharToHex(ch1);
                ch2 = oneHexCharToHex(ch2);
                outHex[i / 2] = (ch1 << 4) | ch2;
            }
            else
            {
                printf("error: %c or %c is not hex digit!\n", ch1, ch2);
                goto exit;
            }
        }
        success = 0;  // OK
    } while (0);
exit:
    return success;
}

#define TEST_ChangeTHEX2CPTR
#ifdef TEST_ChangeTHEX2CPTR

static void printf_outHex(const char *outHex)
{
    int len = strlen(outHex);
    int i;
    for (i = 0; i < len; i++)
    {
        printf("0x%x,", outHex[i] & 0xff);
    }
    printf("\n");
}

void test_ChangeTHEX2CPTR(void)
{
    char buffer[256] = {0};

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

int main(int argc, char *argv[])
{
    test_ChangeTHEX2CPTR();
    return 0;
}
//-------------------------------------------------------------------
