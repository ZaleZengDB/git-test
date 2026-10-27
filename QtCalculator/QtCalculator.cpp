#include "QtCalculator.h"

QtCalculator::QtCalculator(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    setWindowTitle(QStringLiteral("Qt 简易计算器"));//起个名，计算器
    ui.progressBar->setValue(0); //初始化
    init();
}

QtCalculator::~QtCalculator()
{

}

void QtCalculator::init()
{
    QObject::connect(ui.bt_test, &QPushButton::clicked, this, &QtCalculator::Test);
    ui.label->setText("Hello, World");
}

void QtCalculator::Test()
{
    QString str = QStringLiteral("测试");
    ui.lineEdit_Test->setText(str);
    ui.textBrowser->setText(QString::asprintf(" "));

    int e = 0;
    ui.progressBar->setMinimum(0); // 最小值
    ui.progressBar->setMaximum(100); // 最大值
    do
    {
        ui.progressBar->setValue(e); // 当前进度
        e++;
        sleep(20);
    } while (e <= 100);

    ui.lineEdit_Test->insert(QString::asprintf("Test Success!"));
    ui.textBrowser->setText(QString::asprintf("成功"));
    ui.statusBar->showMessage(tr("你单击了: ") + ui.bt_test->text());

    ui.label->setText("<h1><a href=\"https://www.baidu.com\">百度一下</a></h1>");
    ui.label->setOpenExternalLinks(true);
}

//延时功能
void QtCalculator::sleep(unsigned int msec) {
    //currnentTime 返回当前时间 用当前时间加上我们要延时的时间msec得到一个新的时刻
    QTime reachTime = QTime::currentTime().addMSecs(msec);
    //用while循环不断比对当前时间与我们设定的时间
    while (QTime::currentTime() < reachTime) {
        //如果当前的系统时间尚未达到我们设定的时刻，就让Qt的应用程序类执行默认的处理，
        //以使程序仍处于响应状态。一旦到达了我们设定的时刻，就跳出该循环，继续执行后面的语句。
        QApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

//清除按键槽函数
void QtCalculator::on_clear_btn_clicked() 
{
    ui.lineEdit->setText("");
    ui.statusBar->showMessage(tr("你单击了: ") + ui.btnC->text());
}

//数字按键槽函数
void QtCalculator::on_num_btn_clicked() 
{
    QPushButton* btn = qobject_cast<QPushButton*>(sender());//得到当前操作的按键
    QString number = btn->text();//获取按键上文本的值
    ui.statusBar->showMessage(tr("你单击了数字键: ") + btn->text());
    ui.lineEdit->insert(number);
}
//符号按键槽函数
void QtCalculator::on_flag_btn_clicked()
{
    QPushButton* btn = qobject_cast<QPushButton*>(sender());//得到当前操作的按键
    QString flag = btn->text();//获取按键上文本的值
    ui.statusBar->showMessage(tr("你单击了符号键: ") + btn->text());
    ui.lineEdit->insert(flag);
}

//等号按键槽函数
void QtCalculator::on_action_btn_equal_clicked()
{
    ui.statusBar->showMessage(tr("你单击了: ") + ui.btn11->text());
    QString result;
    result = ui.lineEdit->text();
    if (result.isEmpty()) {
        return;
    }
    //加法
    if (result.indexOf("+") != -1) {
        double i;
        i = result.indexOf("+");//获取加号位置
        double h;
        h = result.left(i).toDouble();//获取加号左边的值
        double j;
        j = result.right(result.size() - i).toDouble();//获取加号右边的值
        double k;
        k = h + j;
        ui.lineEdit->setText(QString::number(k));//运算结果显示到LineEdit中
    }
    //减法
    if (result.indexOf("-") != -1) {
        double i;
        i = result.indexOf("-");
        double h, j, k;
        h = result.left(i).toDouble();
        ++i;
        j = result.right(result.size() - i).toDouble();
        k = h - j;
        ui.lineEdit->setText(QString::number(k));
    }
    //乘法
    if (result.indexOf("*") != -1) {
        double i, h, j, k;
        i = result.indexOf("*");
        h = result.left(i).toDouble();
        ++i;
        j = result.right(result.size() - i).toDouble();
        k = h * j;
        ui.lineEdit->setText(QString::number(k));
    }
    //除法
    if (result.indexOf("/") != -1) {
        double i, h, j, k;
        i = result.indexOf("/");
        h = result.left(i).toDouble();
        ++i;
        j = result.right(result.size() - i).toDouble();
        k = h / j;
        ui.lineEdit->setText(QString::number(k));
    }
}
