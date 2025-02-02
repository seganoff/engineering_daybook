#include <stddef.h>
#include <stdint.h>

#include <stdio.h>//printf
//#include <locale.h>
//uint32_t crc32_table[256];

uint32_t crc32(const /*char*/ uint8_t *s,size_t n) {
	uint32_t crc=0xFFFFFFFF;
	
	for(size_t i=0;i<n;i++) {
		/*char*/ uint8_t ch=s[i];
		for(size_t j=0;j<8;j++) {
			uint32_t b=(ch^crc)&1;
			crc>>=1;
			if(b) crc=crc^0xEDB88320;
			ch>>=1;
		}
	}
	
	return ~crc;
}

void build_crc32_table(/*void*/uint32_t *table) {
	for(uint32_t i=0;i<256;i++) {
		uint32_t ch=i;
		uint32_t crc=0;
		for(size_t j=0;j<8;j++) {
			uint32_t b=(ch^crc)&1;
			crc>>=1;
			if(b) crc=crc^0xEDB88320;
			ch>>=1;
		}
		table[i]=crc;
	}
}

uint32_t crc32_fast(const /*char*/ uint8_t *s,size_t n, const uint32_t *table) {
	uint32_t crc=0xFFFFFFFF;
	
	for(size_t i=0;i<n;i++) {
		char ch=s[i];
		uint32_t t=(ch^crc)&0xFF;
		crc=(crc>>8)^table[t];
	}
	
	return ~crc;
}

int main(){
uint32_t _table[256];
//char test_str[]="123456789";
uint8_t test_str[]="123456789";

build_crc32_table(_table);
printf ("tableLookUP 123456789: %x\n",crc32_fast(test_str,sizeof(test_str)-1,_table) );
printf ("tableLess   123456789: %x\n",crc32(test_str,sizeof(test_str)-1) );
//printf("0%x",_table[1]);/*;printf("\u000a");*/printf("\n");
//printf("%x %x %x\n",_table[0],_table[1], _table[2]);
//printf("%x\n",sizeof(test_str));
}
