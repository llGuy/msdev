#ifndef _HTABLE
#define _HTABLE

#include "CNSTMacros.h"
#include "LList.h"
#include "Vector.h"

namespace htble {
	const size_t g_VAL_TO_SHIFT = 3;
	struct Hash {
		explicit Hash(const std::string& p_strToHash)
			: m_strToHash(p_strToHash)
		{
		}
		~Hash(void)
		{
		}
	public:
		size_t M_PerformHash(void) const {
			if(m_strToHash.length() == 1) 
				return (size_t)(_ROTL(m_strToHash[0],_NULL,g_VAL_TO_SHIFT));
			else {
				size_t l_resultOfHash = 0;
				size_t l_indexOfStr = 0;
				for(; l_indexOfStr < m_strToHash.length(); l_indexOfStr++)
					l_resultOfHash = _ROTL(l_resultOfHash,m_strToHash[l_indexOfStr],g_VAL_TO_SHIFT);
				return l_resultOfHash;
			}
		}
	private:
		std::string m_strToHash;
	};
	template<typename T>
	class HTable {
	private:
		using var_ptr = Variable<T>*;
		using var = Variable<T>;

		size_t m_quantOfLList;
		size_t m_capacityOfLList;
		size_t m_quantOfItemsInLists;
		size_t m_quantOfItemsInHTable;
		Vector<llst::LList<T>> m_vecOfLList;
	public:
		explicit HTable(void)
			: m_quantOfLList(_DEF_SIZE_HTABLE),m_quantOfItemsInLists(_SIZE_OF_LLIST),
			m_quantOfItemsInHTable(_NULL)
		{
		}
		~HTable(void) 
		{
		}
	public:
		//public utility functions
		size_t M_GetQuantOfHTable(void) const { return m_quantOfLList; };
		var_ptr M_FindVariable(const std::string& p_nameOfVar) const {
			Hash l_hash(p_nameOfVar);
			size_t l_valueOfHash = l_hash.M_PerformHash() % m_quantOfLList;
			
			var_ptr l_rv = m_vecOfLList[l_valueOfHash].M_FindNodeWithStr(
				p_nameOfVar,
				m_vecOfLList[l_valueOfHash].m_head
			);
			std::cout << "Find " << p_nameOfVar << ":" << l_valueOfHash << " = " << l_rv << std::endl;
			return l_rv;
		} 
		void M_AppendVar(const T p_valOfVar,const std::string& p_nameOfVar) {
			if(m_quantOfItemsInHTable == m_quantOfLList) {
				for(size_t l_indexOfVec = 0; l_indexOfVec < m_quantOfLList; l_indexOfVec++) 
					m_vecOfLList.M_PushBack(llst::LList<T>());
				m_quantOfLList *= 2;
			}
			Hash l_hash(p_nameOfVar);
			size_t l_valueOfHash = l_hash.M_PerformHash() % m_quantOfLList;
			std::cout << "Append " << p_nameOfVar << ":" << l_valueOfHash << "linked list at " << &m_vecOfLList[l_valueOfHash] << " hash " << this << std::endl;
			m_vecOfLList[l_valueOfHash].M_AppendInitializedVar(p_valOfVar,p_nameOfVar);
			m_quantOfItemsInHTable++;
		}
		void M_Delete(const std::string& p_nameOfVar) {
			Hash l_hash(p_nameOfVar);
			size_t l_valueOfHash = l_hash.M_PerformHash() % m_quantOfLList;
			m_vecOfLList[l_valueOfHash].M_DeleteVar(p_nameOfVar);
			m_quantOfItemsInHTable--;
		}
	};
}
#endif