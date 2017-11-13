#include "Base64P.h"

static char gc_base64[] = "TRONPLAYgBjGV5lXU7r9t2QfmKoC80EF4wqvd1M6WHJ(pyxDZb)aick3sSnIzheu=";

static inline int pos(char c)
{
	char *p;
	for(p = gc_base64; *p; p++)
		if(*p == c)
			return p - gc_base64;
	return -1;
}
int Base64P::base64Encode(const void *data, int size, char **str)
{
	char *s, *p;
	int i;
	int c;
	int buff_size;
	unsigned char *q;

	if (size <= 0)	return -1;

	buff_size = (int)(size*4/3)+4;
	p = s = new char [buff_size];

	if (p == NULL) return -1;

	q = (unsigned char*)data;
	i=0;
	for(i = 0; i < size;){
		c=q[i++];
		c*=256;
		if(i < size)
			c+=q[i];
		i++;
		c*=256;
		if(i < size)
			c+=q[i];
		i++;
		p[0]=gc_base64[(c&0x00fc0000) >> 18];
		p[1]=gc_base64[(c&0x0003f000) >> 12];
		p[2]=gc_base64[(c&0x00000fc0) >> 6];
		p[3]=gc_base64[(c&0x0000003f) >> 0];
		if(i > size)
			p[3]='=';
		if(i > size+1)
			p[2]='=';
		p+=4;
	}
	*p=0;
	*str = s;
	return strlen(s);
}

int Base64P::base64Decode(const char *str, void *data)
{
	const char *p;
	unsigned char *q;
	int c;
	int x;
	int done = 0;
	q=(unsigned char*)data;
	for(p=str; *p && !done; p+=4){
		x = pos(p[0]);
		if(x >= 0)
			c = x;
		else{
			done = 3;
			break;
		}
		c*=64;

		x = pos(p[1]);
		if(x >= 0)
			c += x;
		else
			return -1;
		c*=64;

		if(p[2] == '=')
			done++;
		else{
			x = pos(p[2]);
			if(x >= 0)
				c += x;
			else
				return -1;
		}
		c*=64;

		if(p[3] == '=')
			done++;
		else{
			if(done)
				return -1;
			x = pos(p[3]);
			if(x >= 0)
				c += x;
			else
				return -1;
		}
		if(done < 3)
			*q++=(c&0x00ff0000)>>16;

		if(done < 2)
			*q++=(c&0x0000ff00)>>8;
		if(done < 1)
			*q++=(c&0x000000ff)>>0;
	}

	return q - (unsigned char*)data;
}

string Base64P::enCode(string &data)
{
    string encodeData;
    char* buf = new char[data.size() + 1];
    int bufLen = Base64P::base64Encode(data.c_str(),(int)data.length(),&buf);
    buf[bufLen] = '\0';
    encodeData = buf;
    delete buf;
    return encodeData;
}
string Base64P::enCode(int data)
{
    string dataString = __String::createWithFormat("%d",data)->getCString();
    return enCode(dataString);
}
string Base64P::deCode(string data)
{
    string decodeData;
    char* buf = new char[data.size() + 1];
    buf[data.size()] = '\0';
    int len = Base64P::base64Decode(data.c_str(),buf);
    buf[len] = '\0';
    decodeData = buf;
    delete [] buf;
    return decodeData;
}
int Base64P::deCodeInt(string data)
{
    return  atoi(deCode(data).c_str());
}

