#ifndef MIPSEM_DBG_HPP
#define MIPSEM_DBG_HPP

#include <QSplitter> 

class MIPSEM_DBG : public QWidget{
    Q_OBJECT
    
    public:
        MIPSEM_DBG(QString objectFileDir, QWidget *parent = NULL);
        
        QString objectFileDir;




};




#endif // MIPSEM_DBG_HPP
