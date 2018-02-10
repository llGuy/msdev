#ifndef _HASH_SINGLETON
#define _HASH_SINGLETON

#include "../../base/CLine.h"
#include "../func-class/Func.h"
#include "../../../var-storage/dat-struct/HTable.h"

namespace CLine {
	namespace func {
		class Func_HashT {
		private:
			explicit Func_HashT(void)
			{
			}
		public:
			static Func_HashT& M_Shared(void) {
				static Func_HashT* l_hash = nullptr;
				if(!l_hash) l_hash = new Func_HashT();
				return *l_hash;
			}
		public:
			htble::HTable<Func> m_funcHashT;
		};
	}
}

#endif