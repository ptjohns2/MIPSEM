#ifndef MIPS32SYNTAXHIGHLIGHTER_HPP
#define MIPS32SYNTAXHIGHLIGHTER_HPP

#include <QSyntaxHighlighter>
#include <QPlainTextEdit>

#define DEFAULT_SIZE_FONT_MINIMUM               (4)
#define DEFAULT_SIZE_FONT_MAXIMUM               (100)
#define DEFAULT_SIZE_FONT                       (10)
#define DEFAULT_COLOR_TEXT                      (QColor(255, 255, 255))
#define DEFAULT_COLOR_BACKGROUND                (QColor(0, 0, 0))

#define DEFAULT_COLOR_LITERAL                   (QColor(255, 0, 255))
#define DEFAULT_COLOR_LITERAL_STRING            DEFAULT_COLOR_LITERAL
#define DEFAULT_COLOR_LITERAL_DECIMAL           (QColor(255, 127, 127))
#define DEFAULT_COLOR_LITERAL_OCTAL             (QColor(100, 255, 126))
#define DEFAULT_COLOR_LITERAL_BIN               (QColor(255, 126, 255))
#define DEFAULT_COLOR_LITERAL_HEX               (QColor(220, 175, 50))

#define DEFAULT_COLOR_GPREGISTER_MNEMONIC       (Qt::cyan)
#define DEFAULT_COLOR_GPREGISTER_NUMERIC        (Qt::darkCyan)
#define DEFAULT_COLOR_FPREGISTER                (Qt::gray)      

#define DEFAULT_COLOR_DIRECTIVE                 (Qt::cyan)
#define DEFAULT_COLOR_LABEL                     (Qt::red)

#define DEFAULT_COLOR_COMMENT                   (Qt::green)


class MIPS32SyntaxHighlighter: public QSyntaxHighlighter{
        Q_OBJECT

    public:
        MIPS32SyntaxHighlighter(QPlainTextEdit *editor = 0);
        void init();
        
        void refreshEditor();
        
        static void setBackgroundColor(QColor const &color);
        static void setTextColor(QColor const &color);
        static void setFontSize(unsigned int fontSize);
        static void increaseFontSize();
        static void decreaseFontSize();
        static void setDefaultHighlightingRules();
        
        static bool instantiated;
        QPlainTextEdit *editor;
        
        void rebuildHighlightingRules();
        
        static unsigned int fontSize;
        static QColor textColor;
        static QColor backgroundColor;
        
        static QTextCharFormat 
            literalStringFormat,
            literalDecimalFormat, literalOctalFormat, literalBinFormat, literalHexFormat,
            GPRegisterMnemonicFormat, GPRegisterNumericFormat,
            FPRegisterFormat,
            directiveFormat, 
            labelFormat, 
            commentFormat
        ;

    protected:
        void highlightBlock(QString const &text);

    private:
        class HighlightingRule{
            public:
                HighlightingRule(){}
                HighlightingRule(QRegExp &regex, QTextCharFormat &format)
                    :   regex(regex), format(format)    {}
                
                QRegExp regex;
                QTextCharFormat format;
        };
        
        static QRegExp
            literalStringRegex,
            literalDecimalRegex, literalOctalRegex, literalBinRegex, literalHexRegex,
            GPRegisterMnemonicRegex, GPRegisterNumericRegex,
            FPRegisterRegex, 
            directiveRegex, 
            labelRegex,  
            commentRegex
        ;
       
        
        
        static QVector<HighlightingRule> highlightingRules;
        
        //string constants
        #define NUM_DIRECTIVE_NAMES				20
        static std::string const DirectiveNames[];
};























#endif // MIPS32SYNTAXHIGHLIGHTER_HPP
