#ifndef _LLST
#define _LLST

#include "Variable.h"
#include "CNSTMacros.h"

namespace llst {
	template<typename T>
	class LList {
	public:
		using var_ptr = Variable<T>*;
		using var = Variable<T>;

		var_ptr m_head;
		size_t m_quantInitializedVar;
		size_t m_capacity;
	private:
		//functions called at initialization of the linked list
		void M_LinkInitialNodes(size_t& p_destSize,size_t p_currentSize,var_ptr p_currentVar) {
			if(p_currentSize == p_destSize) {
				p_currentVar->m_isEndOfList = true;
				return;
			}
			else if(p_currentSize == 0) {
				m_head->m_ptrNextVar = new var;
				p_currentSize++;
				M_LinkInitialNodes(p_destSize,p_currentSize,m_head->m_ptrNextVar);
			}
			else if(p_currentSize > 0 && p_currentSize < p_destSize) {
				p_currentVar->m_ptrNextVar = new var;
				p_currentSize++;
				M_LinkInitialNodes(p_destSize,p_currentSize,p_currentVar->m_ptrNextVar);
			}
		}
		void M_InitializeList() { M_LinkInitialNodes(m_capacity,_NULL,m_head); };
	private:
		//utility functions
		var_ptr M_FindNode(size_t p_destIndex,size_t p_iterator,var_ptr p_currentVar) const {
			if(p_iterator == p_destIndex) return p_currentVar;
			else {
				p_iterator++;
				return M_FindNode(p_destIndex,p_iterator,p_currentVar->m_ptrNextVar);
			}
		}
		void M_AppendUninitVar() {
			M_FindNode(m_capacity - 1,0,m_head)->m_ptrNextVar = new var;
			m_capacity++;
		}
		signed int M_GetPositionOfVar(const std::string& p_name,var_ptr p_currentVar,signed int p_position) {
			if(p_currentVar->m_name == p_name) return p_position;
			else if(p_currentVar->m_name == _STR_NULL) return -1;
			else {
				p_position++;
				return M_GetPositionOfVar(p_name,p_currentVar->m_ptrNextVar,p_position);
			}
		}
	public:
		//constructors / destructors
		explicit LList(void)
			: m_head(new var),m_quantInitializedVar(_NULL),m_capacity(_SIZE_OF_LLIST)
		{
			M_InitializeList();
		}
		explicit LList(size_t p_capacity)
			: m_head(new var),m_quantInitializedVar(_NULL),m_capacity(p_capacity)
		{
			M_InitializeList();
		}
		~LList(void)
		{
		}
	public:
		//public utility functions
		var_ptr M_FindNodeWithStr(const std::string& p_nameOfVar,var_ptr p_currentVar) const {
			if(p_currentVar->m_name == p_nameOfVar) return p_currentVar;
			else if(p_currentVar->m_name == _STR_NULL) return p_currentVar;
			else return M_FindNodeWithStr(p_nameOfVar,p_currentVar->m_ptrNextVar);
		}
		void M_AppendInitializedVar(const T& p_value,const std::string& p_name) {
			if(m_quantInitializedVar < m_capacity) {
				var_ptr l_destVar = M_FindNode(m_quantInitializedVar,_NULL,m_head);
				l_destVar->m_value = p_value;
				l_destVar->m_name = p_name;
				m_quantInitializedVar++;
			}
			else {
				M_AppendUninitVar();
				var_ptr l_destVar = M_FindNode(m_quantInitializedVar,0,m_head);
				l_destVar->m_value = p_value;
				l_destVar->m_name = p_name;
			}
		}
		void M_DeleteVar(const std::string& p_name) {
			signed int l_position = M_GetPositionOfVar(p_name,m_head,0);
			if(l_position < 0) return;
			signed int l_positionBefore = l_position - 1;
			signed int l_positionAfter = l_position + 1;
			if(l_positionBefore != 0) l_positionBefore = l_positionAfter + 1;
			if(l_position + 1 == m_capacity) M_FindNode(l_positionBefore,0,m_head)->m_ptrNextVar = new var;
			else if(l_position == 0) {
				var_ptr l_varAfterHead = m_head->m_ptrNextVar;
				m_head = l_varAfterHead;
			}
			else M_FindNode(l_positionBefore,0,m_head)->m_ptrNextVar = M_FindNode(l_positionAfter,0,m_head);
			m_quantInitializedVar--;
			m_capacity--;
		}
	};
};

#endif