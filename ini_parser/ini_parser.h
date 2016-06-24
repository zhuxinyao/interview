#ifndef QIHOO_INI_PARSER_H_
#define QIHOO_INI_PARSER_H_

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string>
#include <map>

namespace qh
{

    class INIParser
    {
    public:
        INIParser() {
			m_commentSep = ";";	
		}

        ~INIParser() {
		}

        //! \brief ����һ�������ϵ�INI�ļ�
        //! \param[in] - const std::string & ini_file_path
        //! \return - bool
        bool Parse(const std::string& ini_file_path);

        //! \brief ����һ������INI��ʽ���ڴ����ݡ�
        //!   ���磺ini_data="a:1||b:2||c:3"
        //!         ����<code>Parse(ini_data, ini_data_len, "||", ":")</code>���ɽ�����������ݡ�
        //!         �������֮�� 
        //!         Get("a")=="1" && Get("b")=="2" && Get("c")=="3"
        //! \param[in] - const char * ini_data
        //! \param[in] - size_t ini_data
        //! \param[in] - const std::string & line_seperator
        //! \param[in] - const std::string & key_value_seperator
        //! \return - bool
        bool Parse(const char* ini_data, size_t ini_data_len, const std::string& line_seperator = "\n", const std::string& key_value_seperator = "=");

        //! \brief ��Ĭ��section�в���ĳ��key���������ҵ���value������Ҳ���������һ���մ�
        //! \param[in] - const std::string & key
        //! \param[in] - bool * found - ���������true�����ҵ����key
        //! \return - const std::string& - ���صľ���key��Ӧ��value
        const std::string& Get(const std::string& key, bool* found);

        const std::string& Get(const std::string& section, const std::string& key, bool* found);

    private:
		bool HandleLine(const char *begin, const char *end, const std::string& key_value_seperator);
		void trim(const char **begin, const char **end); 
		const char* SepToken(const char *begin, const char *end, const std::string& sep);
		const char* SkipSep(const char* pos, size_t len); 

		std::string m_commentSep;
		std::string m_getValue;
		std::map<std::string, std::string> m_iniMap;
    };
}

#endif

