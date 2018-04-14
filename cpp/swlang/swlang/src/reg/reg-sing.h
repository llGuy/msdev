#ifndef _REG_SINGLETON_HEADER
#define _REG_SINGLETON_HEADER

#include <unordered_map>
#include <iostream>
#include <string>

namespace sw_lang {
	namespace rs {
		class Regs {
		private:
			explicit Regs(void)
				: m_hothPtr(new int),m_endorPtr(new int),m_tatooinePtr(new int),m_nabooPtr(new int)
			{
			}
		private:
			int* m_hothPtr;
			int* m_endorPtr;
			int* m_tatooinePtr;
			int* m_nabooPtr;
		public:
			static Regs& M_Shared(void) {
				static Regs* l_reg = nullptr;
				if(l_reg == nullptr) {
					l_reg = new Regs();

					l_reg->m_strPlanetMap["hoth"] = new Hoth();
					l_reg->m_strPlanetMap["endor"] = new Endor();
					l_reg->m_strPlanetMap["tatooine"] = new Tatooine();
					l_reg->m_strPlanetMap["naboo"] = new Naboo();
				}				
				return *l_reg;
			}
		public:
			//planets contain a pointer to a "register"
			struct Planet { 
				int* m_regPtr; 
			};
			struct Hoth : public Planet { 
				explicit Hoth(void)
				{
					m_regPtr = Regs::M_Shared().m_hothPtr;
				}
			};
			struct Endor : public Planet { 
				explicit Endor(void)
				{
					m_regPtr = Regs::M_Shared().m_endorPtr;
				}
			};
			struct Tatooine : public Planet {
				explicit Tatooine(void)
				{
					m_regPtr = Regs::M_Shared().m_endorPtr;
				}
			};
			struct Naboo : public Planet{
				explicit Naboo(void)
				{	
					m_regPtr = Regs::M_Shared().m_nabooPtr;
				}
			};
		public:
			std::unordered_map<std::string,Planet*> m_strPlanetMap;
		};
	}
}

#endif