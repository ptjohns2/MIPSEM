#include "MIPS32SyntaxHighlighter.hpp"

#include <QStringList>

MIPS32SyntaxHighlighter::MIPS32SyntaxHighlighter(QPlainTextEdit *editor)
    :   QSyntaxHighlighter(editor->document()), editor(editor)
{
    QFont font;
    font.setFamily("Courier");
    font.setFixedPitch(true);
    editor->setFont(font);
    
    if(!instantiated){
        init();
    }
    instantiated = true;
    
}

bool MIPS32SyntaxHighlighter::instantiated = false;

unsigned int MIPS32SyntaxHighlighter::fontSize;
QColor MIPS32SyntaxHighlighter::textColor;
QColor MIPS32SyntaxHighlighter::backgroundColor;
QColor MIPS32SyntaxHighlighter::backgroundHighlightColor;

QTextCharFormat MIPS32SyntaxHighlighter::literalStringFormat;
QTextCharFormat MIPS32SyntaxHighlighter::literalDecimalFormat;
QTextCharFormat MIPS32SyntaxHighlighter::literalOctalFormat;
QTextCharFormat MIPS32SyntaxHighlighter::literalBinFormat;
QTextCharFormat MIPS32SyntaxHighlighter::literalHexFormat;
QTextCharFormat MIPS32SyntaxHighlighter::GPRegisterMnemonicFormat;
QTextCharFormat MIPS32SyntaxHighlighter::GPRegisterNumericFormat;
QTextCharFormat MIPS32SyntaxHighlighter::FPRegisterFormat;
QTextCharFormat MIPS32SyntaxHighlighter::directiveFormat;
QTextCharFormat MIPS32SyntaxHighlighter::labelFormat;
QTextCharFormat MIPS32SyntaxHighlighter::commentSingleFormat;
QTextCharFormat MIPS32SyntaxHighlighter::commentDoubleFormat;

QRegExp MIPS32SyntaxHighlighter::literalStringRegex;
QRegExp MIPS32SyntaxHighlighter::literalDecimalRegex;
QRegExp MIPS32SyntaxHighlighter::literalOctalRegex;
QRegExp MIPS32SyntaxHighlighter::literalBinRegex;
QRegExp MIPS32SyntaxHighlighter::literalHexRegex;
QRegExp MIPS32SyntaxHighlighter::GPRegisterMnemonicRegex;
QRegExp MIPS32SyntaxHighlighter::GPRegisterNumericRegex;
QRegExp MIPS32SyntaxHighlighter::FPRegisterRegex;
QRegExp MIPS32SyntaxHighlighter::directiveRegex;
QRegExp MIPS32SyntaxHighlighter::labelRegex;
QRegExp MIPS32SyntaxHighlighter::commentSingleRegex;
QRegExp MIPS32SyntaxHighlighter::commentDoubleRegex;

QVector<MIPS32SyntaxHighlighter::HighlightingRule> MIPS32SyntaxHighlighter::highlightingRules;


void MIPS32SyntaxHighlighter::init(){ 
    fontSize = DEFAULT_SIZE_FONT;
    textColor = DEFAULT_COLOR_TEXT;
    backgroundColor = DEFAULT_COLOR_BACKGROUND;
    
    setFontSize(DEFAULT_SIZE_FONT);
    setBackgroundColor(DEFAULT_COLOR_BACKGROUND);
    setTextColor(DEFAULT_COLOR_TEXT);
    
    setDefaultHighlightingRules();
    rebuildHighlightingRules();
}

void MIPS32SyntaxHighlighter::refreshEditor(){
    //Font
    QFont font = editor->font();
    font.setPointSize(fontSize);
    editor->setFont(font);
    
    QFontMetrics metrics = QFontMetrics(font);
    editor->setTabStopWidth(6 * metrics.width(' '));
    
    //Background color
    QPalette palette = editor->palette();
    palette.setColor(QPalette::Base, backgroundColor);
    palette.setColor(QPalette::Background, backgroundColor);  
    
    //Text color
    palette.setColor(QPalette::Text, textColor);
    editor->setPalette(palette);  
}

void MIPS32SyntaxHighlighter::setFontSize(unsigned int fontSize){
    MIPS32SyntaxHighlighter::fontSize = fontSize;
}

void MIPS32SyntaxHighlighter::increaseFontSize(){
    if(fontSize < DEFAULT_SIZE_FONT_MAXIMUM){fontSize++;}   
}
void MIPS32SyntaxHighlighter::decreaseFontSize(){
    if(fontSize > DEFAULT_SIZE_FONT_MINIMUM){fontSize--;}  
}

void MIPS32SyntaxHighlighter::setBackgroundColor(QColor const &color){
    MIPS32SyntaxHighlighter::backgroundColor = color;
    
    int red = color.red();
    int blue = color.blue();
    int green = color.green();
    int offset = (int)(DEFAULT_COLOR_BACKGROUND_HIGHLIGHT_RATIO * 256.0);
    
    if(offset < 0){
        if(red+offset < 0){red-=offset;}else{red+=offset;}
        if(green+offset < 0){green-=offset;}else{green+=offset;}
        if(blue+offset < 0){blue-=offset;}else{blue+=offset;}
    }else if(offset > 0){
        if(red+offset > 255){red-=offset;}else{red+=offset;}
        if(green+offset > 255){green-=offset;}else{green+=offset;}
        if(blue+offset > 255){blue-=offset;}else{blue+=offset;}
    }else{
        //don't change color
    }
    QColor tmpColor;
    tmpColor.setRed(red);
    tmpColor.setBlue(blue);
    tmpColor.setGreen(green);
    MIPS32SyntaxHighlighter::backgroundHighlightColor = tmpColor;
}
void MIPS32SyntaxHighlighter::setTextColor(QColor const &color){
    MIPS32SyntaxHighlighter::textColor = color;
}



void MIPS32SyntaxHighlighter::setDefaultHighlightingRules(){    //Build regexes
    literalStringRegex = QRegExp("\".*\"");
    literalDecimalRegex = QRegExp("0|[1-9]|[1-9][0-9]+");
    literalOctalRegex = QRegExp("(^|[^1-9])0[0-9]+");
    literalBinRegex = QRegExp("0b[0-1]+");
    literalHexRegex = QRegExp("0x[0-9a-fA-F]+");
    
    GPRegisterMnemonicRegex = QRegExp("\\$zero|\\$at|\\$v[0-1]|\\$a[0-3]|\\$t[0-9]|\\$s[0-7]|\\$k[0-1]|\\$gp|\\$sp|\\$fp|\\$ra");
    GPRegisterNumericRegex = QRegExp("\\$[0-9]|\\$[1-2][0-9]|\\$3[0-1]");
    
    FPRegisterRegex = QRegExp("\\$f[0-9]|\\$f[1-2][0-9]|\\$f3[0-1]");
    
    QString directiveRegexString = "";
    for(int i=0; i<NUM_DIRECTIVE_NAMES; i++){
        directiveRegexString += QString("\\") + QString(DirectiveNames[i].c_str());
        if(i<NUM_DIRECTIVE_NAMES-1){
            directiveRegexString += QString("|");
        }
    }
    directiveRegex = QRegExp(directiveRegexString);
    
    labelRegex = QRegExp("[0-9a-zA-Z_]+:");
    commentSingleRegex = QRegExp("#[^\n]*");
    commentDoubleRegex = QRegExp("##[^\n]*");
    
    //Build formats
    literalStringFormat.setForeground(DEFAULT_COLOR_LITERAL_STRING);
    
    literalDecimalFormat.setForeground(DEFAULT_COLOR_LITERAL_DECIMAL);
    literalOctalFormat.setForeground(DEFAULT_COLOR_LITERAL_OCTAL);
    literalBinFormat.setForeground(DEFAULT_COLOR_LITERAL_BIN);
    literalHexFormat.setForeground(DEFAULT_COLOR_LITERAL_HEX);
    
    GPRegisterMnemonicFormat.setForeground(DEFAULT_COLOR_GPREGISTER_MNEMONIC);
    GPRegisterNumericFormat.setForeground(DEFAULT_COLOR_GPREGISTER_NUMERIC);
    
    FPRegisterFormat.setForeground(DEFAULT_COLOR_FPREGISTER);
    
    directiveFormat.setForeground(DEFAULT_COLOR_DIRECTIVE);
    labelFormat.setForeground(DEFAULT_COLOR_LABEL);
    
    commentSingleFormat.setForeground(DEFAULT_COLOR_COMMENT_SINGLE);
    commentDoubleFormat.setForeground(DEFAULT_COLOR_COMMENT_DOUBLE);
    
}

void MIPS32SyntaxHighlighter::rebuildHighlightingRules(){
    highlightingRules.clear();
    
    //use correct order for nested matches
    highlightingRules.push_back(HighlightingRule(literalDecimalRegex, literalDecimalFormat)); 
    highlightingRules.push_back(HighlightingRule(literalOctalRegex, literalOctalFormat));    
    highlightingRules.push_back(HighlightingRule(literalBinRegex, literalBinFormat));    
    highlightingRules.push_back(HighlightingRule(literalHexRegex, literalHexFormat));  
            
    highlightingRules.push_back(HighlightingRule(GPRegisterMnemonicRegex, GPRegisterMnemonicFormat));    
    highlightingRules.push_back(HighlightingRule(GPRegisterNumericRegex, GPRegisterNumericFormat)); 
            
    highlightingRules.push_back(HighlightingRule(FPRegisterRegex, FPRegisterFormat));  
            
    highlightingRules.push_back(HighlightingRule(directiveRegex, directiveFormat));    
    highlightingRules.push_back(HighlightingRule(labelRegex, labelFormat));    
            
    highlightingRules.push_back(HighlightingRule(literalStringRegex, literalStringFormat));  
            
    highlightingRules.push_back(HighlightingRule(commentSingleRegex, commentSingleFormat));    
    highlightingRules.push_back(HighlightingRule(commentDoubleRegex, commentDoubleFormat));    
    
            
}


void MIPS32SyntaxHighlighter::highlightBlock(QString const &text){
    refreshEditor();
    for(int i=0; i<highlightingRules.size(); i++){
        HighlightingRule rule = highlightingRules[i];
        int start = rule.regex.indexIn(text);
        while(start >= 0){
            int len = rule.regex.matchedLength();
            setFormat(start, len, rule.format);
            start = rule.regex.indexIn(text, start + len);
        }
    }
    setCurrentBlockState(0);
}




std::string const MIPS32SyntaxHighlighter::DirectiveNames[] = {
	".data",
	".text",
	".kdata",
	".ktext",
	".byte",
	".half",
	".word",
	".float",
	".double",
	".ascii",
	".asciiz",
	".align",
	".space",
	".include",
	".extern",
	".globl",
	".set",
	".macro",
	".end_macro",
	".eqv",
};




