#include "ini_parser.h"
#include <iostream>
#include <string.h>
#include <assert.h>

void test1()
{
    const char* ini_text= "a=1\nb=2\n"; 
    qh::INIParser parser;
    if (!parser.Parse(ini_text, strlen(ini_text), "\n", "=")) {
        assert(false);
    }

	const std::string& a = parser.Get("a", NULL);
    assert(a == "1");

    std::string b = parser.Get("b", NULL);
	assert(b == "2");

	const std::string& c = parser.Get("c", NULL);
    assert(c == "");
}

void test2()
{
    const char* ini_text= "a=1||b=2||c=3"; 
    qh::INIParser parser;
    if (!parser.Parse(ini_text, strlen(ini_text), "||", "=")) {
        assert(false);
    }

    const std::string& a = parser.Get("a", NULL);
    assert(a == "1");

    std::string b = parser.Get("b", NULL);
    assert(b == "2");

    const std::string& c = parser.Get("c", NULL);
    assert(c == "3");
}

void test3()
{
    const char* ini_text= "||||a:1||b:2||||c:3||||||"; 
    qh::INIParser parser;
    if (!parser.Parse(ini_text, strlen(ini_text), "||", ":")) {
        assert(false);
    }

    const std::string& a = parser.Get("a", NULL);
    assert(a == "1");

    std::string b = parser.Get("b", NULL);
    assert(b == "2");

    const std::string& c = parser.Get("c", NULL);
    assert(c == "3");
}

void test4()
{
    const char* ini_text= "||||a :1||b:2 |||| c :3 ||||||"; 
    qh::INIParser parser;
    if (!parser.Parse(ini_text, strlen(ini_text), "||", ":")) {
        assert(false);
    }

    const std::string& a = parser.Get("a", NULL);
    assert(a == "1");

    std::string b = parser.Get("b", NULL);
    assert(b == "2");

    const std::string& c = parser.Get("c", NULL);
    assert(c == "3");
}

void test5()
{
    const char* ini_text= "[1]\na=1\nb=2\nxyz=./zxy\n[2]\n\nyy= "; 
    qh::INIParser parser;
    if (!parser.Parse(ini_text, strlen(ini_text), "\n", "=")) {
        assert(false);
    }

	const std::string& a = parser.Get("a", NULL);
    assert(a == "1");

    std::string b = parser.Get("b", NULL);
	assert(b == "2");

	const std::string& xyz = parser.Get("xyz", NULL);
    assert(xyz == "./zxy");

	const std::string& yy = parser.Get("yy", NULL);
	assert(yy == "");
}

void test6()
{
    const char* ini_text= ";c=3\na=1\nb=2\nxyz=./zxy\n\nyy= \n"; 
    qh::INIParser parser;
    if (!parser.Parse(ini_text, strlen(ini_text), "\n", "=")) {
        assert(false);
    }

	const std::string& a = parser.Get("a", NULL);
    assert(a == "1");

    std::string b = parser.Get("b", NULL);
	assert(b == "2");
	
	const std::string& xyz = parser.Get("xyz", NULL);
    assert(xyz == "./zxy");
	
	const std::string& c = parser.Get("c", NULL);
    assert(c == "");

	const std::string& yy = parser.Get("yy", NULL);
	assert(yy == "");
}

int main(int argc, char* argv[])
{
    //TODO 在这里添加单元测试，越多越好，代码路径覆盖率越全越好
	std::string a;
	assert(a == "" );

	test1();
	test2();
    test3();
	test4();
	test5();
	test6();
    return 0;
}


