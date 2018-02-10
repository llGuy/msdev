#ifndef _LLST
#define _LLST

#include "../../../misc/CNSTMacros.h"

namespace llst {
	template<typename Vlu,typename Src>
	class Node {
	public:
		using U_Node = Node<Vlu,Src>;
		explicit Node(void)
			: m_ptr(nullptr)
		{
		}
		explicit Node(const Src& p_id,const Vlu& p_vlu)
			: m_id(p_id),m_value(p_vlu),m_ptr(nullptr)
		{
		}
		~Node(void) {
			if(m_ptr) delete m_ptr;
		}
	public:
		U_Node*& M_Ptr(void) { return m_ptr; };
		Vlu& M_Val(void) { return m_value; };
		Src& M_ID(void) { return m_id; };
		void M_PreserveNext(void) { m_ptr = nullptr; };
	private:
		U_Node* m_ptr;
		Vlu m_value;
		Src m_id;
	};

	template<typename Vlu,typename Src>
	class LList {
	public:
		using U_Node = Node<Vlu,Src>;
		explicit LList(void)
			: m_head(nullptr)
		{
		}
		~LList(void)
		{
		}
	public:
		void M_Add(const Src& p_id,const Vlu& p_vlu) {
			if(!m_head) m_head = new U_Node(p_id,p_vlu);
			else {
				U_Node* l_newNode = new U_Node(p_id,p_vlu);
				l_newNode->M_Ptr() = m_head;
				m_head = l_newNode;
			}
		}
		U_Node* M_Src(const Src& p_id) {
			U_Node* l_curr = m_head;
			while(l_curr) {
				if(l_curr->M_ID() == p_id) return l_curr;
				else l_curr = l_curr->M_Ptr();
			}
			return &m_invalid;
		}
		void M_Del(const Src& p_id) {
			U_Node* l_curr = m_head;
			U_Node* l_prev = nullptr;
			while(l_curr) {
				if(l_curr->M_ID() == p_id) {
					U_Node* l_next = l_curr->M_Ptr();
					l_curr->M_PreserveNext();
					delete l_curr;
					if(l_prev)
						l_prev->M_Ptr() = l_next;
					else
						m_head = l_next;
					return;
				}
				else {
					l_prev = l_curr;
					l_curr = l_curr->M_Ptr();
				}
			}
		}
	public:
		U_Node* m_head;
		U_Node m_invalid;
	};
}

#endif