#include <QtTest>
#include <QCoreApplication>

//#include "../gui/types.h"

//#include "../antios-gui/application.h"
//#include "../antios-gui/application.cpp"

//#include "../antios-gui/ui/mainwindow.h"
//#include "../antios-gui/ui/mainwindow.cpp"

//#include "../antios-gui/models/comboboxmodel.h"
//#include "../antios-gui/models/infotablemodel.h"

class CPPTest : public QObject
{
    Q_OBJECT

public:
    CPPTest();
    ~CPPTest();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();

private:
//    Application app;

};

CPPTest::CPPTest()
//    : app(this)
{

}

CPPTest::~CPPTest()
{

}

void CPPTest::initTestCase()
{

}

void CPPTest::cleanupTestCase()
{

}

void CPPTest::test_case1()
{

}

QTEST_MAIN(CPPTest)

#include "tst_cpptest.moc"
