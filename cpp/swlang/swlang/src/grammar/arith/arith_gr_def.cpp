#include "arith_gr.h"

namespace sw_lang {
	namespace gr {
		const std::string Arith_Gr::m_addWS = "huurh";
		const std::string Arith_Gr::m_subWS = "aguhwwgggghhh";
		const std::string Arith_Gr::m_mulWS = "huuguughghg";
		const std::string Arith_Gr::m_divWS = "uughghhhgh";
		const std::string Arith_Gr::m_modWS = "aarrragghuuhwuuh";
		const std::string* Arith_Gr::m_arrWS[5] = {
			&m_addWS,
			&m_subWS,
			&m_mulWS,
			&m_divWS,
			&m_modWS
		};
	}
}