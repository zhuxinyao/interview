#include "ini_parser.h"
#include <iostream>
namespace qh
{

    bool INIParser::Parse(const std::string& ini_file_path) {
		FILE *fp = fopen(ini_file_path.c_str(), "r");
		if (fp == NULL)
			return false;

		fseek(fp, 0, SEEK_END);
		size_t fsize = ftell(fp);
		rewind(fp);
		char *buffer = (char *)malloc(sizeof(char) * fsize);
		if (buffer == NULL) {
			fprintf(stderr, "error: malloc error\n");
			fclose(fp);
			return false;
		}
		size_t l = fread(buffer, 1, fsize, fp);
		if (l != fsize) {
			fprintf(stderr, "error: read error %lu\n", l);
			fclose(fp);
			return false;
		}

		bool ret = Parse(buffer, fsize);
		
		free(buffer);
		fclose(fp);
		return ret;
	}
	
	bool INIParser::Parse( \
					const char* ini_data, \
					size_t ini_data_len, \
					const std::string& line_seperator, \
					const std::string& key_value_seperator) {
		const char* begin = ini_data;
		const char* end = NULL;
		bool ret = false;
		while (begin != NULL && *begin != '\0') {
			end = SepToken(begin, NULL, line_seperator);
			assert(end != NULL);
			
			ret = HandleLine(begin, end, key_value_seperator);
				
			begin = SkipSep(end, line_seperator.length());
		}
		return ret;
	}

	//处理行分割符之间的一行
	bool INIParser::HandleLine(const char *begin, \
							   const char *end, \
							   const std::string& key_value_seperator) {
		trim(&begin, &end);
		//ignore comment in ini file
		const char *pos = SepToken(begin, end, m_commentSep);
		assert(pos != NULL);
		if (pos < end) 
			pos = end;
			
		const char* key_sep = SepToken(begin, end, key_value_seperator);
		if (key_sep == end)
			return true;
		const char *trim1 = begin;
		const char *trim2 = key_sep;
		trim(&trim1, &trim2);
		if (trim1 >= trim2)
			return true;
		const std::string key(trim1, trim2 - trim1);

		key_sep = SkipSep(key_sep, key_value_seperator.length());
		if (key_sep == NULL || *key_sep == '\0')
			return true;
		trim1 = key_sep;
		trim2 = end;
		trim(&trim1, &trim2);
		if (trim1 >= trim2)
			return true;
		const std::string value(trim1, trim2 - trim1);
		m_iniMap[key] = value;
		return true;
	}
	
	//去掉字符串前后空格
	void INIParser::trim(const char **begin, const char **end) {
		const char *p1 = *begin, *p2 = *end - 1;
		while (*p1 == ' ' && p1 <= p2) {
			p1++;
		}
		while (*p2 == ' ' && p1 <= p2) {
			p2--;
		}
		*begin = p1;
		*end = p2 + 1;
	}

	//找到并返回从bigin开始，在begin与end之间的第一个出现的分割符 end为空时查找到字符串最后
	const char* INIParser::SepToken(const char *begin, const char *end, const std::string& sep) {
		const char *pos = begin;
		if (end == NULL) {
			while (*pos != '\0') {
				if (sep.compare(0, sep.length(), pos, sep.length()) == 0)
					return pos;
				pos++;
			}
		} else {
			while (pos != end) {
				if (sep.compare(0, sep.length(), pos, sep.length()) == 0)
					return pos;
				pos++;
			}
		}
		return pos;
	}

	//返回指向分割符后下一个字符的指针
	const char* INIParser::SkipSep(const char* pos, size_t len) {
		if (*pos == '\0')
			return NULL;
		else 
			return pos + len;
	}
        
	const std::string& INIParser::Get( \
								const std::string& key, \
								bool* found) {
		m_getValue.clear();
		if (m_iniMap.find(key) == m_iniMap.end()) {
			return m_getValue;
		}
		m_getValue.append(m_iniMap[key]);
		return m_getValue;
	}
}
