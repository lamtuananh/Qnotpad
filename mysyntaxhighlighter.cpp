#include "mysyntaxhighlighter.h"
#include <QTextCharFormat>
#include <QMap>
#include <QFont>
#include <iostream>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include "checkthread.h"
//inicialization fonts

//static const QFont TEXTFONT = QFont("Courier",12);




MySyntaxHighlighter::MySyntaxHighlighter(QObject *parent) : QSyntaxHighlighter(parent)
{
    //keywords
 //   identifierRule.pattern = QRegExp("/^([a-z]+)(,\s*[a-z]+)*$/i");
//  /^([a-z]+)(,\s*[a-z]+)*$/i


     HighlightingRule rule;
    QFont errorFont  = QFont("Courier",12);
    defaultFormat.setFont(errorFont);
    // defaultFormat.setUnderlineStyle(QTextCharFormat::);
    QFont normalFont  = QFont("Courier",12);
    blankFormat.setFont(normalFont);
    defaultFormat.setFont(normalFont);

    keywordFormat.setForeground(Qt::blue);
       keywordFormat.setFontWeight(QFont::Bold);
       QStringList keywordPatterns;

       QString path = QDir::currentPath() +"/keywords.txt";
       QFile file(path);
       if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
             {
            std::cout<<path.toStdString();
           std::cout<<"errow while reading file";
           return;
       }
       QTextStream in(&file);
        QString line = in.readLine();
   while (!line.isNull()) {
       // CheckThread::listWords.append(line);
        keywordPatterns.append("\\b"+line+"\\b");
              line = in.readLine();
          }




       foreach (const QString &pattern, keywordPatterns) {
           rule.pattern = QRegExp(pattern);
           rule.format = keywordFormat;
           highlightingRules.append(rule);
       }
       foreach (const QString &pattern, datatypes) {
           rule.pattern = QRegExp(pattern);
           rule.format = keywordFormat;
           highlightingRules.append(rule);
       }
       errorFont.setBold(true);
       errorFont.setItalic(true);
        variableFormat.setFont(errorFont);
       initVariableRule.pattern = QRegExp("\\b(input\\s+|output\\s+)?(wire|supply0|supply1|wand|trior|wor|shortint|int|longint|byte|bit|logic|reg|integer|time)\\s+[_a-zA-Z0-9$]+\s\*(\\[[0-9]\*:[0-9]\*\\])?\\s\*(,\\s\*[_a-zA-Z0-9$]+\\s\*\s\*(\\[[0-9]\*:[0-9]\*\\])?\\s\*)\*;");
       initVariableRule.format = variableFormat;
       variableRule.pattern = QRegExp("\\b[a-z]+\\b");
       variableRule.format = variableFormat;
       classFormat.setFontWeight(QFont::Bold);
       classFormat.setForeground(Qt::darkMagenta);
       classRule.pattern = QRegExp("\\bQ[A-Za-z]+\\b");
       classRule.format = classFormat;
    //   highlightingRules.append(classRule);

       //Include
       includeFormat.setFontWeight(QFont::Bold);
       includeFormat.setForeground(Qt::green);
       includeRule.pattern = QRegExp("^\`include ");
       includeRule.format = includeFormat;

       //single line comment format
        QFont font= QFont("Courier",12);
       font.setUnderline(false);
       singleLineCommentFormat.setFont(font);
       singleLineCommentFormat.setForeground(Qt::red);
       singleLineCommentRule.pattern = QRegExp("//[^\n]*");
       singleLineCommentRule.format = singleLineCommentFormat;
  //     highlightingRules.append(singleLineCommentRule);

       multiLineCommentFormat.setForeground(Qt::red);

       //String format
       quotationFormat.setForeground(Qt::darkGreen);
       quotationRule.pattern = QRegExp("\".*\"");
       quotationRule.format = quotationFormat;
     //  highlightingRules.append(quotationRule);

       //Number format
       numberFormat.setForeground(Qt::black);
       numberFormat.setFontWeight(QFont::Bold);
       decimalNumberRule.pattern = QRegExp("\\b[0-9]+\\b");
       decimalNumberRule.format = numberFormat;
     //  highlightingRules.append(numberRule);

       //Hex Number format
       hexNumberRule.pattern = QRegExp("\\b0[xX][0-9a-fA-F]+\\b");
       hexNumberRule.format = numberFormat;

       //identifier format

       identifierFormat.setForeground(Qt::blue);
       identifierRule.pattern = QRegExp("[_a-zA-Z][_a-zA-Z0-9]{0,30}");
       identifierRule.format = keywordFormat;

    //      highlightingRules.append(identifierRule);

       //blank characters format
       blankFormat.setForeground(Qt::green);
       blankFormat.setFontWeight(QFont::Bold);
       //blankRule.pattern = QRegExp("[a-zA-Z0-9+-*/,./_]+");
       blankRule.pattern = QRegExp("/^$|\s+/");


       blankRule.format = defaultFormat;
    //   highlightingRules.append(blankRule);

       // function name format
       functionNameFormat.setFontItalic(true);
       functionNameFormat.setForeground(Qt::blue);

       functionNameRule.pattern = QRegExp("\\b[A-Za-z0-9_]+(?=\\()");
       functionNameRule.format = functionNameFormat;
    //   highlightingRules.append(functionNameRule);

       commentStartExpression = QRegExp("/\\*");
       commentEndExpression = QRegExp("\\*/");

       functionStartExpression = QRegExp("function;");
       functionEndExpression = QRegExp("end;");

}

void MySyntaxHighlighter::highlightBlock(const QString &text)
{
 /*   qInfo() << "C++ Style Info Message";
    qInfo( "C Style Info Message" );

    qDebug() << "C++ Style Debug Message";
    qDebug( "C Style Debug Message" );

    qWarning() << "C++ Style Warning Message";
    qWarning( "C Style Warning Message" );

    qCritical() << "C++ Style Critical Error Message";
    qCritical( "C Style Critical Error Message" );*/
    QTextStream out(stdout);
 //   out<< "text changed!!" <<endl;
    int index;
   /* QRegExp blankexpression(blankRule.pattern);
       index = blankexpression.indexIn(text);
       while (index >= 0) {
           int length = blankexpression.matchedLength();
           setFormat(index, length,defaultFormat);
           index = blankexpression.indexIn(text, index + length);
       }
  */
    setFormat(0,text.length(),defaultFormat);
    QRegExp blankexpression(blankRule.pattern);
           index = blankexpression.indexIn(text);
           while (index >= 0) {
                 out<< "errorrrrrrrrrrr text matched changed!!" <<endl;
               int length = blankexpression.matchedLength();
               setFormat(index, length,blankRule.format);
               index = blankexpression.indexIn(text, index + length);
           }

    foreach (const HighlightingRule &rule, highlightingRules) {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);
        while (index >= 0) {
           // out<< "datatypes !!" <<endl;

            int length = expression.matchedLength();
            setFormat(index, length, rule.format);
            index = expression.indexIn(text, index + length);
        }
    }


    QRegExp includerexpression(includeRule.pattern);
index = includerexpression.indexIn(text);
while (index >= 0) {
     out<< "error text matched changed!!" <<endl;
    int length = includerexpression.matchedLength();
    setFormat(index, length, includeRule.format);
    index = includerexpression.indexIn(text, index + length);
}

 /*
    QRegExp blankexpression(blankRule.pattern);
    index = blankexpression.indexIn(text);
    while (index >= 0) {
        int length = blankexpression.matchedLength();
        setFormat(index, length, blankRule.format);
        index = blankexpression.indexIn(text, index + length);
    }
*/

        QRegExp numberexpression(decimalNumberRule.pattern);
    index = numberexpression.indexIn(text);
    while (index >= 0) {
        int length = numberexpression.matchedLength();
        setFormat(index, length, decimalNumberRule.format);
        index = numberexpression.indexIn(text, index + length);
    }

        QRegExp hexnumberexpression(hexNumberRule.pattern);
    index = hexnumberexpression.indexIn(text);
    while (index >= 0) {
      int length = hexnumberexpression.matchedLength();
      setFormat(index, length, hexNumberRule.format);
      index = hexnumberexpression.indexIn(text, index + length);
    }
        QRegExp functionNameexpression(functionNameRule.pattern);
    index = functionNameexpression.indexIn(text);
    while (index >= 0) {
        int length = functionNameexpression.matchedLength();
        setFormat(index, length, functionNameRule.format);
        index = functionNameexpression.indexIn(text, index + length);
    }
    QRegExp initVariableExpression(initVariableRule.pattern);
    index = initVariableExpression.indexIn(text);
    while (index >= 0) {
    int length = initVariableExpression.matchedLength();
    QString pom = text.right(text.length() - index).left(length);
    QRegExp variableExpression(variableRule.pattern);
    int varindex = variableExpression.indexIn(pom);
    //out<<"pom: "<<pom<<endl;
    while(varindex>=0)
    {
        int varlength = variableExpression.matchedLength();
        out<< "variable index: "<<varindex <<endl;
        out<< "variable length: "<<varlength <<endl;
        setFormat(varindex,varlength,variableRule.format);
        varindex = variableExpression.indexIn(pom, varindex+varlength);
    }
 //   setFormat(index, length, initVariableRule.format);
    index = initVariableExpression.indexIn(text, index + length);
}


foreach (const HighlightingRule &rule, highlightingRules) {
    QRegExp expression(rule.pattern);
    int index = expression.indexIn(text);
    while (index >= 0) {
       // out<< "datatypes !!" <<endl;

        int length = expression.matchedLength();
        setFormat(index, length, rule.format);
        index = expression.indexIn(text, index + length);
    }
}

    //highlight comment line last
  if(currentBlockState()!= 1){
    QRegExp singleLineCommentexpression(singleLineCommentRule.pattern);
    index = singleLineCommentexpression.indexIn(text);
    while (index >= 0) {
        int length = singleLineCommentexpression.matchedLength();
        setCurrentBlockState(3);
        setFormat(index, length, singleLineCommentRule.format);
        index = singleLineCommentexpression.indexIn(text, index + length);
    }
}
   if(currentBlockState()!= 3)
   {
       setCurrentBlockState(0);

    int startIndex = 0;
    if (previousBlockState() != 1)
        startIndex = commentStartExpression.indexIn(text);

    while (startIndex >= 0) {
        int endIndex = commentEndExpression.indexIn(text, startIndex);
        int commentLength;
        if (endIndex == -1) {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        } else {
            commentLength = endIndex - startIndex
                            + commentEndExpression.matchedLength();
        }
        setFormat(startIndex, commentLength, multiLineCommentFormat);
        startIndex = commentStartExpression.indexIn(text, startIndex + commentLength);
    }
}
    //String highlight
        QRegExp quotationexpression(quotationRule.pattern);
    index = quotationexpression.indexIn(text);
    while (index >= 0) {
        int length = quotationexpression.matchedLength();
        if(currentBlockState()!=3)
        setFormat(index, length, quotationRule.format);
        index = quotationexpression.indexIn(text, index + length);
    }
}
