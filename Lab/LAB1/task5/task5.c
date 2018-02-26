#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int hex2int(char c)
{
        int one = (c / 16) - 3;
        int two = c % 16;
        int r = one*10 + two;
        if(r > 9) r--;
        return r;
}
int hex2ascii(char c, char d)
{
        int h = hex2int(c) * 16;
        int l = hex2int(d);
        return h+l;
}

int main(int arc, char *argv[])
{
	int outlen;
	int tmplen;
	int l;
	int i;
	int length;
	int count;
	int found =0;	
	int k = 0;
        unsigned char outbuf[1024];
        unsigned char cipher[1024];
        unsigned char temp, key[16];
        size_t nread, len;
        FILE *in;
        unsigned char iv[17];
        for(i = 0; i < 17; i++)
           iv[i] = 0;
           iv[16] = '\0';
           char intext[] = "This is a top secret.";
           char st[] = "8d20e5056a8d24d0462ce74e4904c1b513e10d1df4a2ef2ad4540fae1ca0aaf9";
           i = 0;
           while(i < 64)
          {
             if(st[i] >= 'a' && st[i] <= 'z')
                 st[i] = st[i] - 32;
             i++;
          }
        length = strlen(st);
        char buf = 0;
        for(i = 0; i < length; i++)
        {
           if(i % 2 != 0)
           {             
              cipher[k] = hex2ascii(buf, st[i]);
              k++;
           }
           else
           {
              buf = st[i];
           }
        }
        cipher[k] = '\0';
        in = fopen("/home/william/CryptoLabs/task5/words.txt", "r");
        if(in == NULL)
        {
          printf("\n cannot open file");
          exit(1);
        }
        EVP_CIPHER_CTX ctx;       
        EVP_CIPHER_CTX_init(&ctx);
        while(fgets(key, sizeof(key), in) != NULL)
        {
            l = 0;
            if(strlen(key) < 16)
            {
                l = strlen(key)-1;
                while(l < 16)
                {
                     key[l] = ' ';
                     l++;
                }
                key[l] = '\0';
            }
            else
                key[16] = '\0';
            EVP_EncryptInit_ex(&ctx, EVP_aes_128_cbc(), NULL, key, iv);
            if(!EVP_EncryptUpdate(&ctx, outbuf, &outlen, intext, strlen(intext)))
              return 0;
           if(!EVP_EncryptFinal_ex(&ctx, outbuf + outlen, &tmplen))
             return 0;
           outlen += tmplen;
           EVP_CIPHER_CTX_cleanup(&ctx);
           count = 0;
           for(i = 0; i < 32; i++)
           {
              if(cipher[i] == outbuf[i])
                   count++;
           }
           if(count == 32)
           {
              printf("\n....key found....\n");
              printf("\n key.........................%s",key);
	      printf("\n");
              found = 1;
              break;
           }
        }
        fclose(in);
        if(found == 0)
            printf("\n\n key cannot be found for the above cipher text\n");
        return 0;
        }




