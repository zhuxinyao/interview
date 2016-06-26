
#include "proxy_url_extractor.h"
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include "tokener.h"

namespace qh
{

    namespace {

        template< class _StringVector, 
        class StringType,
        class _DelimType> 
            inline void StringSplit(  
            const StringType& str, 
            const _DelimType& delims, 
            unsigned int maxSplits, 
            _StringVector& ret)
        {
            unsigned int numSplits = 0;

            // Use STL methods
            size_t start, pos;
            start = 0;

            do
            {
                pos = str.find_first_of( delims, start );

                if ( pos == start )
                {
                    ret.push_back(StringType());
                    start = pos + 1;
                }
                else if ( pos == StringType::npos || ( maxSplits && numSplits + 1== maxSplits ) )
                {
                    // Copy the rest of the string
                    ret.push_back(StringType());
                    *(ret.rbegin()) = StringType(str.data() + start, str.size() - start);
                    break;
                }
                else
                {
                    // Copy up to delimiter
                    //ret.push_back( str.substr( start, pos - start ) );
                    ret.push_back(StringType());
                    *(ret.rbegin()) = StringType(str.data() + start, pos - start);
                    start = pos + 1;
                }

                ++numSplits;

            }
            while ( pos != StringType::npos );
        }
    }

    ProxyURLExtractor::ProxyURLExtractor()
    {
    }

    bool ProxyURLExtractor::Initialize( const std::string& param_keys_path )
    {
        std::ifstream ifs;
        ifs.open(param_keys_path.data(), std::fstream::in);
        typedef std::vector<std::string> stringvector;
        stringvector keysvect;
        
        while (!ifs.eof()) {
            std::string line;
            getline(ifs, line);
            if (ifs.fail() && !ifs.eof()) {
                fprintf(stderr, "SubUrlExtractor::LoadParamKeysFile readfile_error=[%s] error!!", param_keys_path.data());
                ifs.close();
                return false;
            }
            if (line.empty()) continue;

            keysvect.clear();
            StringSplit(line, ",", static_cast<unsigned int>(-1), keysvect);
            assert(keysvect.size() >= 1);
            //keys_set_.insert(keysvect.begin(), keysvect.end());
            //keys_set_.erase("");
			for (size_t i = 0; i < keysvect.size(); i++) {
				if (!keysvect[i].empty()) {
					keys_set_.Insert(keysvect[i].c_str());
				}
			}
        }

        ifs.close();

        return true;
    }

    std::string ProxyURLExtractor::Extract( const std::string& raw_url )
    {
        std::string sub_url;
        ProxyURLExtractor::Extract(keys_set_, raw_url, sub_url);
        return sub_url;
    }

    void ProxyURLExtractor::Extract(const KeyItems& keys, \
									const std::string& raw_url, \
									std::string& sub_url ) {
#if 1
        //TODO 请面试者在这里添加自己的代码实现以完成所需功能
		if (raw_url.empty()) return;
		size_t len = raw_url.length();
		size_t start = raw_url.find_first_of('?');
		if (start + 1 == len || start == std::string::npos) 
			return;
		start += 1;
		size_t stop = raw_url.find_first_of('&', start);
		if (stop == std::string::npos)
			stop = len;		
	
		do {
			size_t key_pos = raw_url.find_first_of('=', start);
			if (start < key_pos && key_pos != std::string::npos && key_pos + 1 < stop) {
				const std::string& key = raw_url.substr(start, key_pos - start);
				if (keys.Find(key.c_str()) != 0) {
					sub_url = raw_url.substr(key_pos + 1, stop - key_pos - 1);
					return;
				}
			}

			start = stop + 1;
			stop = raw_url.find_first_of('&', start);
			if (stop == std::string::npos)
				stop = len;
        } while (start < len);
		
		return;
#else
        //这是一份参考实现，但在特殊情况下工作不能符合预期
        Tokener token(raw_url);
        token.skipTo('?');
        token.next(); //skip one char : '?' 
        std::string key;
        while (!token.isEnd()) {
            key = token.nextString('=');
            if (keys.find(key) != keys.end()) {
                const char* curpos = token.getCurReadPos();
                int nreadable = token.getReadableSize();

                /**
                * case 1: 
                *  raw_url="http://www.microsofttranslator.com/bv.aspx?from=&to=zh-chs&a=http://hnujug.com/&xx=yy"
                *  sub_url="http://hnujug.com/"
                */
                sub_url = token.nextString('&');

                if (sub_url.empty() && nreadable > 0) {
                    /**
                    * case 2: 
                    * raw_url="http://www.microsofttranslator.com/bv.aspx?from=&to=zh-chs&a=http://hnujug.com/"
                    * sub_url="http://hnujug.com/"
                    */
                    assert(curpos);
                    sub_url.assign(curpos, nreadable);
                }
            }
            token.skipTo('&');
            token.next();//skip one char : '&'
        }
#endif
    }

    std::string ProxyURLExtractor::Extract( const KeyItems& keys, const std::string& raw_url )
    {
        std::string sub_url;
        ProxyURLExtractor::Extract(keys, raw_url, sub_url);
        return sub_url;
    }
	
	KeyItems::KeyItems() 
		: m_alloc(0), m_cap(DEFAULT_CAP) {
		Init();
	}

	KeyItems::~KeyItems() {
		free(m_pData);
	}

	void KeyItems::Init() {
		m_pData = (TrieNode* )malloc(sizeof(TrieNode) * m_cap);
		assert(m_pData != NULL);
			
		m_pRoot = CreateNode();
		assert(m_pRoot != NULL);
	}
	
	TrieNode* KeyItems::CreateNode() {
		if (m_alloc >= m_cap)
			return NULL;

		TrieNode* ret = m_pData + m_alloc;
		m_alloc++;
		
		memset(ret, 0, sizeof(TrieNode));
		ret->m_count = 1;
		return ret;
	}
 
	bool KeyItems::Insert(const char *s) {
		if (m_pRoot == NULL || s == NULL)
			return false;
		TrieNode* tmp = m_pRoot;
		
		while (*s != '\0') {
			const int k = *s - 'a';
			if (tmp->m_next[k] != NULL) {
				tmp->m_count++;
			} else {
				tmp->m_next[k] = CreateNode(); 
				if (tmp->m_next[k] == NULL)
					return false;
			}
			tmp = tmp->m_next[k];
			s++;
		}
		tmp->m_word++;
		return true;
	}

	int KeyItems::Find(const char *s) const {
		if (m_pRoot == NULL || s == NULL)
			return 0;
		TrieNode *tmp = m_pRoot;
		
		while (*s != '\0') {
			const int k = *s - 'a';
			if (tmp->m_next[k] != NULL)
				tmp = tmp->m_next[k];
			else
				return 0;
			s++;
		}
		return tmp->m_word;
	}
}

