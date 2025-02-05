#include <stddef.h>
#include <stdint.h>
//\u000a invalid character gcc; g++ ok
//printf("\u20ac\U0001F333 %lx \x0a",(size_t)256);
#include <stdio.h>
#include <cstdlib>//malloc
#include <vector>
#include <cassert>
//#include <locale.h>

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
	return ~crc;}

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
	return ~crc;}
//----------------------------------------------------------------
void appendCookedByte(uint8_t byte, uint8_t *dest,int &position)
{if ((byte == 0x7d) || (byte == 0x7e)){dest[position]=0x7d;position++;byte^=0x20;}
dest[position]=byte;position++;}
int encode_frame(const uint8_t *data, uint8_t data_len/*,uint8_t seqNr*/,uint8_t *frame_out) {
uint8_t byte;//data
int cout = 0;//deque or vector
frame_out[cout]=0x7e;cout++;//boundry octet
while (data_len) {
byte = *data++;
//fcs = _crc_ccitt_update(fcs, data);
//if ((byte == 0x7d) || (byte == 0x7e)) { frame_out[cout]=0x7d;cout++;byte^=0x20;}
//frame_out[cout]=byte;cout++;
appendCookedByte(byte,frame_out,cout);
data_len--;
}//while
frame_out[cout]=0x7e;cout++;//boundry octet
return cout;
}
void appendCookedByte(uint8_t byte, std::vector<uint8_t>& dest)
{if (byte == 0x7e||byte== 0x7d){ dest.push_back(0x7d); byte ^= 0x20; }
dest.push_back(byte);
}
int encode_frame(const uint8_t * data, uint32_t data_len, std::vector<uint8_t>& dest)
{uint8_t byte; uint32_t crc32;
	dest.push_back(0x7e);
	while(data_len--)
	{byte = *data++;appendCookedByte(byte,dest);
	}
	//append escaped crc32
	dest.push_back(0x7e);
	return dest.size();
}
void decode_frame(uint8_t * source, uint32_t source_len, std::vector<uint8_t> &dest)
{
uint8_t byte = *source++;source_len--;
uint8_t escaped {0};
assert(byte==0x7e);
while(source_len--)
{
byte = *source++;
switch (byte)
{
case 0x7e:{assert(source_len==0);break;}
case 0x7d:{escaped = 1;break;}
default: {if(escaped){byte ^= 0x20;escaped = 0;}dest.push_back(byte);break;}
}//switch
}//while loop
}

typedef struct _Buff {uint8_t *pBuf;uint32_t len;} Buff;


int main(){
//Buff * b0 = (Buff*) malloc( 10 *  sizeof(Buff)  );
//uint32_t _table[256];
//build_crc32_table(_table);
//printf ("tableLookUP 123456789: %x\n",crc32_fast(test_str,sizeof(test_str)-1,_table) );
//printf ("tableLess   123456789: %x\n",crc32(test_str,sizeof(test_str)-1) );
std::vector<uint8_t> datav = {1,2,3,4,5};
uint8_t data0[] = {'a','b','c','~','e','f'}; 
std::vector<uint8_t> original (data0,data0 + sizeof(data0)/sizeof(uint8_t));
uint8_t out[20];
std::vector<uint8_t> encv;//outv.reserve(3);
uint32_t enc0=encode_frame(data0, 6, encv);
uint32_t enc1=encode_frame(data0, 6, out);
for(int n: out/*encv*/) printf("0x%x ",n); printf("\u000a encoded; dest.size: %x \u000a", /*enc0*/enc1);
std::vector<uint8_t> decv;
decode_frame(encv.data(), encv.size(),decv);
for(int n: decv) printf("0x%x ",n); printf("\u000a decoded; decv.size: %lx \u000a", decv.size());
for(int n: original) printf("0x%x ",n); printf("\u000a original data0 \u000a");
//b0[0].pBuf = data0;b0[0]->len = 6;
//std::vector<uint8_t> out;out.reserve(9);out.resize(9);
//int frame_length = encode_frame(data0.data(),5,out.data());
  //int frame_length = encode_frame(data0,6,out);
  //printf("%s\n",out);
//uint32_t _delimit = 0xccddeeff;
//printf("%x into bytes: %x %x %x %x \u000a",_delimit,(_delimit&0xff000000) >> 24, (_delimit&0x00ff0000) >> 16, (_delimit&0x0000ff00) >>8, (_delimit&0x000000ff)>>0);
//printf("%x into bytes: %x %x %x %x \u000a",_delimit,_delimit>>24&0xff , _delimit>>16&0xff, _delimit>>8&0xff, _delimit>>0&0xff);

return 0;
}
//g++ -g -o app  main.c && ./app && rm ./app
