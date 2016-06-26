
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
     * \brief ����url��ȡ��
     *  ��Ե�ǰ������������ַ��������302��תurl������url��©�����ƹ���ͳɱ�����
     * ����ο��������ӣ�http://3g.hebei.com.cn/system/2014/01/06/013162824.shtml
     */
    class ProxyURLExtractor
    {
    public:
        ProxyURLExtractor();

        //! \brief ���ع����ļ�
        //! \param[in] - const std::string & rule_file
        //! \return - bool
        bool Initialize(const std::string& rule_file);

        //! \brief ������ȡ������url�������ȡʧ�ܣ����ؿմ�
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

