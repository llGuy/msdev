#ifndef _RET
#define _RET

#include "../IncludeCLine.h"

namespace CLine {
	namespace func {
		class LineOfCode_Ret : public LineOfCode {
		public:
			explicit LineOfCode_Ret(const std::string& p_retLine) 
				: m_retLine(p_retLine)
			{
			}
		private:
			void M_GetRSV(void) {
				size_t l_rsvInd = 4;
				m_rsv = ::G_BuildString(';',l_rsvInd,m_retLine);
			}
		public:
			void M_Translate(void) override { M_GetRSV(); };
			const bool M_IsRetState(void) override { return true; };
			const std::string* M_RetRSV(void) override { return &m_rsv; };
		private:
			std::string m_retLine;
			std::string m_rsv;
		};
	}
}

#endif