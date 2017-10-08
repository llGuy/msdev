#ifndef _PROGRAM
#define _PROGRAM

#include "Misc.h"
#include "IncludeCLine.h"

class Program {
public:
	explicit Program(void)
	{
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
	~Program(void)
	{
	}
private:
	inline Vector<std::string> M_BuildBody(Vector<std::string> &p_vecLineStr,size_t &p_index) {
		Vector<std::string> l_newVecBody;
		bool l_end = false;
		size_t l_quantBegins = 0;
		size_t l_quantEnds = 0;
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
	inline std::string M_GetKeyword(const std::string& p_line) {
		std::string l_keyword;
		size_t l_index = 0;
		while(p_line[l_index] != ' ' && l_index < p_line.length()) {
			l_keyword += p_line[l_index];
			l_index++;
		}
		return l_keyword;
	}
private:
	void M_Parse(Vector<std::string> &p_vecLineStr,Vector<CLine::LineOfCode*> &p_vecLine) {
		size_t l_quantBegins = 0;
		size_t l_quantEnds = 0;

		auto l_doNoth = [&](size_t &p_index)->void {};
		auto l_endifLam = [&](size_t &p_index)->void {};
		auto l_setLam = [&](size_t &p_index)->void {
			p_vecLine.M_PushBack(new CLine::LineOfCode_Set(p_vecLineStr[p_index])); };
		auto l_modLam = [&](size_t &p_index)->void {
			p_vecLine.M_PushBack(new CLine::LineOfCode_Mod(p_vecLineStr[p_index])); };
		auto l_printLam = [&](size_t &p_index)->void {
			p_vecLine.M_PushBack(new CLine::LineOfCode_Print(p_vecLineStr[p_index])); };
		auto l_printlnLam = [&](size_t &p_index)->void {
			p_vecLine.M_PushBack(new CLine::LineOfCode_Print(p_vecLineStr[p_index],true)); };
		auto l_inputLam = [&](size_t &p_index)->void {
			p_vecLine.M_PushBack(new CLine::LineOfCode_Input(p_vecLineStr[p_index])); };
		auto l_forLam = [&](size_t &p_index)->void {
			CLine::LineOfCode* l_for = new CLine::LineOfCode_For(M_BuildBody(p_vecLineStr,p_index));
			p_vecLine.M_PushBack(l_for);
			M_Parse(*(l_for->M_GetBodyStringLines()),
				*(l_for->M_GetBodyLineObj()));
		};
		std::unordered_map<std::string,std::function<void(size_t&)>> l_lineExe;
		l_lineExe["begin"] = l_doNoth;
		l_lineExe["end"] = l_doNoth;
		l_lineExe["endif"] = l_endifLam;
		l_lineExe["set"] = l_setLam;
		l_lineExe["mod"] = l_modLam;
		l_lineExe["print"] = l_printLam;
		l_lineExe["println"] = l_printlnLam;
		l_lineExe["input"] = l_inputLam;
		l_lineExe["for"] = l_forLam;

		for(size_t l_index = 0; l_index < p_vecLineStr.m_size; l_index++) {
			std::string l_keyword = M_GetKeyword(p_vecLineStr[l_index]);
			l_lineExe[l_keyword](l_index);
		}
	}
public:
	void M_Execute(void) {
		M_Parse(m_vecLineStr,m_vecLine);
		for(size_t l_vecIter = 0; l_vecIter < m_vecLine.m_size; l_vecIter++)
			m_vecLine[l_vecIter]->M_Translate();
	}
private:
	Vector<std::string> m_vecLineStr;
	Vector<CLine::LineOfCode*> m_vecLine;
};

#endif