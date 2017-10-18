#ifndef _PROGRAM
#define _PROGRAM

#include "Misc.h"
#include "IncludeCLine.h"


class Program {
public:
	explicit Program(void)
	{
		LineCompilation::M_Shared().M_InitLineCompilation();
	}
	explicit Program(std::fstream& p_stream) {
		while(p_stream) {
			std::string l_tempLine;
			std::getline(p_stream,l_tempLine);
			if(l_tempLine != "" && l_tempLine[0] != '#') {
				size_t l_index = 0;
				std::string l_actualLine = "";
				while(l_tempLine[l_index] == ' ')
					l_index++;
				l_actualLine = l_tempLine.substr(l_index);
				m_vecLineStr.M_PushBack(l_actualLine);
			}
		}
	}
	explicit Program(const Vector<std::string>& p_vecLineStr)
		: m_vecLineStr(p_vecLineStr)
	{
	}
public:
	void M_Execute(void) {
		Methods::M_Parse(m_vecLineStr,m_vecLine);
		for(size_t l_vecIter = 0; l_vecIter < m_vecLine.m_size; l_vecIter++)
			m_vecLine[l_vecIter]->M_Translate();
	}
private:
	Vector<std::string> m_vecLineStr;
	Vector<CLine::LineOfCode*> m_vecLine;
private:
	struct LineCompilation {
		std::unordered_map<std::string,std::function<void(size_t&,Vector<std::string>&,Vector<CLine::LineOfCode*>&)>> m_exeMap;
	public:
		void M_InitLineCompilation(void) {
			m_exeMap["begin"] = [&](size_t &p_index,Vector<std::string> &p_vecLineStr,Vector<CLine::LineOfCode*> &p_vecLine)->void {};
			m_exeMap["end"] = [&](size_t &p_index,Vector<std::string> &p_vecLineStr,Vector<CLine::LineOfCode*> &p_vecLine)->void {};
			m_exeMap["endif"] = [&](size_t &p_index,Vector<std::string> &p_vecLineStr,Vector<CLine::LineOfCode*> &p_vecLine)->void {};
			m_exeMap["set"] = [&](size_t &p_index,Vector<std::string> &p_vecLineStr,Vector<CLine::LineOfCode*> &p_vecLine)->void {
				p_vecLine.M_PushBack(new CLine::LineOfCode_Set(p_vecLineStr[p_index])); };
			m_exeMap["mod"] = [&](size_t &p_index,Vector<std::string> &p_vecLineStr,Vector<CLine::LineOfCode*> &p_vecLine)->void {
				p_vecLine.M_PushBack(new CLine::LineOfCode_Mod(p_vecLineStr[p_index])); };
			m_exeMap["print"] = [&](size_t &p_index,Vector<std::string> &p_vecLineStr,Vector<CLine::LineOfCode*> &p_vecLine)->void {
				p_vecLine.M_PushBack(new CLine::LineOfCode_Print(p_vecLineStr[p_index])); };
			m_exeMap["println"] = [&](size_t &p_index,Vector<std::string> &p_vecLineStr,Vector<CLine::LineOfCode*> &p_vecLine)->void {
				p_vecLine.M_PushBack(new CLine::LineOfCode_Print(p_vecLineStr[p_index],true)); };
			m_exeMap["input"] = [&](size_t &p_index,Vector<std::string> &p_vecLineStr,Vector<CLine::LineOfCode*> &p_vecLine)->void {
				p_vecLine.M_PushBack(new CLine::LineOfCode_Input(p_vecLineStr[p_index])); };
			m_exeMap["for"] = [&](size_t &p_index,Vector<std::string> &p_vecLineStr,Vector<CLine::LineOfCode*> &p_vecLine)->void {
				Vector<std::string> l_body(Methods::M_BuildBody(p_vecLineStr,p_index));
				CLine::LineOfCode* l_for = new CLine::LineOfCode_For(l_body);
				p_vecLine.M_PushBack(l_for);
				Methods::M_Parse(*(l_for->M_GetBodyStringLines()),
					*(l_for->M_GetBodyLineObj())); };
			m_exeMap["while"] = [&](size_t &p_index,Vector<std::string> &p_vecLineStr,Vector<CLine::LineOfCode*> &p_vecLine)->void {
				Vector<std::string> l_body(Methods::M_BuildBody(p_vecLineStr,p_index));
				CLine::LineOfCode* l_for = new CLine::LineOfCode_While(l_body);
				p_vecLine.M_PushBack(l_for);
				Methods::M_Parse(*(l_for->M_GetBodyStringLines()),
					*(l_for->M_GetBodyLineObj())); };
		}
		static LineCompilation& M_Shared(void) {
			static LineCompilation* l_lc = nullptr;
			if(l_lc == nullptr) {
				l_lc = new LineCompilation();
				l_lc->M_InitLineCompilation();
			}
			return *l_lc;
		}
	};
	struct Methods {
		inline static std::string M_GetKeyword(const std::string& p_line) {
			std::string l_keyword;
			size_t l_index = 0;
			while(p_line[l_index] != ' ' && l_index < p_line.length()) {
				l_keyword += p_line[l_index];
				l_index++;
			}
			return l_keyword;
		}
		inline static Vector<std::string> M_BuildBody(Vector<std::string> &p_vecLineStr,size_t &p_index) {
			bool l_end = false;
			size_t l_quantEnds = 0;
			size_t l_quantBegins = 0;
			Vector<std::string> l_newVecBody;
			while(!l_end) {
				if(p_vecLineStr[p_index] == "begin") l_quantBegins++;
				else if(p_vecLineStr[p_index] == "end") l_quantEnds++;

				if(l_quantBegins == l_quantEnds && l_quantBegins > 0) l_end = true;
				else {
					l_newVecBody.M_PushBack(p_vecLineStr[p_index]);
					p_index++;
				}
			}
			return l_newVecBody;
		}
		static void M_Parse(Vector<std::string> &p_vecLineStr,Vector<CLine::LineOfCode*> &p_vecLine) {
			for(size_t l_index = 0; l_index < p_vecLineStr.m_size; l_index++) {
				LineCompilation::M_Shared().m_exeMap[Methods::M_GetKeyword(p_vecLineStr[l_index])](l_index,
					p_vecLineStr,p_vecLine);
			}
		}
	};
};

#endif
