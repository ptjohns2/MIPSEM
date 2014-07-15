#ifndef __PARSER_HPP__
#define __PARSER_HPP__

#include "types.hpp"
#include "Literals.hpp"

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;


class Parser{
	public:
		Parser();
		~Parser();
		
		//Methods
		static string trimFront(string);
		static string trimEnd(string);
		static string trim(string);
		static string replaceChar(string str, char before, char after);

		static bool isNestedByParentheses(string);
		static string removeNestedParentheses(string);
		static bool isNestedByApostrophes(string);
		static string removeNestedApostrophes(string);
		static bool isNestedByQuotes(string);
		static string removeNestedQuotes(string);

		static bool isTrailedByComma(string);
		static string removeTrailingComma(string);

		static bool isWhiteSpace(char);
		static string removeComment(string);
		static string sanitizeProgramLine(string);
		static vector<string> tokenizeInstruction(string);
		static vector<string> stringExplode(string);
		static vector<string> stringExplodeAndSanitize(string);
		static string extractAndRemoveFirstToken(string&);

		static string combineTokensToString(vector<string> const &tokens, int from = 0);



		
		

		int getTokenValue(string);


		bool tokenIsRegister(string);
		int getRegisterIndex(string);

			bool tokenIsGPRegister(string);
			int getGPRegisterIndex(string);
			static string getGPRegisterName(int);

			bool tokenIsFPRegister(string);
			int getFPRegisterIndex(string);
			static string getFPRegisterName(int);






		bool tokenIsInstructionMnemonic(string);
		int getInstructionMnemonicNumber(string);

		bool tokenIsDirective(string);
		int getDirectiveNumber(string);

		static bool tokenIsLabel(string);
		static string getLabelName(string);
		






		//Members
		Literals literals;
		#define NUM_GP_REGISTER_NAMES	64
		#define NUM_FP_REGISTER_NAMES	32
		#define NUM_DIRECTIVE_NAMES		20
		#define NUM_INSTRUCTION_NAMES	377
		static string const GPRegisterNames[];
		static string const FPRegisterNames[];
		static string const DirectiveNames[];
		static string const InstructionNames[];
		unordered_map<string, int> GPRegisterNameMap;
		unordered_map<string, int> FPRegisterNameMap;
		unordered_map<string, int> DirectiveMap;
		unordered_map<string, int> InstructionMnemonicMap;
		


	private:






};








#endif