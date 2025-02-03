#include <stddef.h>
#include <stdint.h>

#include <stdio.h>//printf
//#include <vector>
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
int encode_frame(const uint8_t *data, uint8_t data_len/*,uint8_t seqNr*/,uint8_t *frame_out) {
uint8_t byte;//data
int cout = 0;//deque or vector
frame_out[cout]=0x7e;cout++;//boundry octet
while (data_len) {
byte = *data++;
//fcs = _crc_ccitt_update(fcs, data);
if ((byte == 0x7d) || (byte == 0x7e)) { frame_out[cout]=0x7d;cout++;byte^=0x20;}
frame_out[cout]=byte;cout++;
data_len--;
}//while
frame_out[cout]=0x7e;cout++;
return cout;
}


int main(){
//uint32_t _table[256];
//char test_str[]="123456789";
//uint8_t test_str[]="123456789";

//build_crc32_table(_table);
//printf ("tableLookUP 123456789: %x\n",crc32_fast(test_str,sizeof(test_str)-1,_table) );
//printf ("tableLess   123456789: %x\n",crc32(test_str,sizeof(test_str)-1) );
//printf("0%x",_table[1]);/*;printf("\u000a");*/printf("\n");
//printf("%x %x %x\n",_table[0],_table[1], _table[2]);
//printf("%x\n",sizeof(test_str));
//const uint8_t data1[] = {
//      0x7e, 1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21,
//      22,   23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 0x7e,};
//std::vector<uint8_t> data0 = {1,2,3,4,5};
uint8_t data0[] = {'a','b','c','d','e','f'}; 
uint8_t out[8];
//std::vector<uint8_t> out;out.reserve(9);out.resize(9);
//int frame_length = encode_frame(data0.data(),5,out.data());
int frame_length = encode_frame(data0,6,out);
printf("%s\n",out);
//for(int n: out) printf("0x%x ",n); printf("\u000a");
return 0;
}
//g++ -g -o app  main.c && ./app && rm ./app
