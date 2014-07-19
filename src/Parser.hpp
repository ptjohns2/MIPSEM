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
		static string toLower(string);
		static string toUpper(string);
		
		static int indexOf(string _str, string target);
		static int indexOf(string _str, string target, int fromIndex);
		static string replace(string _str, string target, string replacement);

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
		static string combineInstructionTokens(vector<string> const&);
		static vector<string> stringExplode(string);
		static vector<string> collectableLiteralListExplode(string);

		static string extractFirstToken(string);
		static bool extractAndRemoveFirstToken(string &src, string &token);


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






		bool tokenIsInstructionName(string);
		int getInstructionNameNumber(string);

		bool tokenIsBranchInstructionName(string);
		int getBranchInstructionNameNumber(string);

		bool tokenIsJumpInstructionName(string);
		int getJumpInstructionNameNumber(string);

		bool tokenIsPseudoInstructionName(string);
		int getPseudoInstructionNameNumber(string);
		int getPseudoInstructionNumberOfLinesToInsert(string);


		bool tokenIsDirective(string);
		int getDirectiveNumber(string);
		string getDirectiveName(int);

		static bool tokenIsLabel(string);
		static string getLabelName(string);
		






		//Members
		Literals literals;

		#define NUM_GP_REGISTER_NAMES			64
		static string const GPRegisterNames[];
		unordered_map<string, int> GPRegisterNameMap;

		#define NUM_FP_REGISTER_NAMES			32
		static string const FPRegisterNames[];
		unordered_map<string, int> FPRegisterNameMap;

		#define NUM_DIRECTIVE_NAMES				20
		static string const DirectiveNames[];
		unordered_map<string, int> DirectiveMap;

		#define NUM_INSTRUCTION_NAMES			377
		static string const InstructionNames[];
		unordered_map<string, int> InstructionNameMap;

		#define NUM_BRANCH_INSTRUCTION_NAMES	26
		static string const BranchInstructionNames[];
		unordered_map<string, int> BranchInstructionNameMap;

		#define NUM_JUMP_INSTRUCTION_NAMES		3
		static string const JumpInstructionNames[];
		unordered_map<string, int> JumpInstructionNameMap;

		#define NUM_PSEUDO_INSTRUCTION_NAMES	18
		static pair<string, int> const PseudoInstructionNamesAndNumberOfLinesToInsert[];
		unordered_map<string, int> PseudoInstructionNameMap;


	private:






};








#endif