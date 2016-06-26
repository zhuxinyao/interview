
#ifndef PROXY_URL_EXTRACTOR_H_
#define PROXY_URL_EXTRACTOR_H_

#include <stdlib.h>
#include <memory.h>
#include <assert.h>
#include <string>
#include <set>

namespace qh
{
	#define DEFAULT_CAP 100

	class TrieNode {
	public:
		int m_count;
		int m_word;
		TrieNode* m_next[26];
	};
	
	class KeyItems {
	public:
		KeyItems();
		~KeyItems();
		bool Insert(const char *s);
		int Find(const char *s) const;	

	private:
		void Init();
		TrieNode* CreateNode();
		
		TrieNode* m_pRoot;
		TrieNode* m_pData;
		size_t m_alloc;
		size_t m_cap;
	};

    /**
     * \brief 代理url提取类
     *  针对当前互联网恶意网址作者利用302跳转url或翻译类url的漏洞来绕过传统杀毒软件
     * 详情参考新闻链接：http://3g.hebei.com.cn/system/2014/01/06/013162824.shtml
     */
    class ProxyURLExtractor
    {
    public:
        ProxyURLExtractor();

        //! \brief 加载规则文件
        //! \param[in] - const std::string & rule_file
        //! \return - bool
        bool Initialize(const std::string& rule_file);

        //! \brief 返回提取出来的url。如果提取失败，返回空串
        //! \param[in] - const std::string & url
        //! \return - std::string
        std::string Extract(const std::string& url);

        static void Extract(const KeyItems& keys, const std::string& raw_url, std::string& sub_url);
        static std::string Extract(const KeyItems& keys, const std::string& raw_url);

    private:

        KeyItems keys_set_;
    };
}

#endif //PROXY_URL_EXTRACTOR_H_

