#include "widget.h"
#include "ui_widget.h"
#include<QTime>
#include<QTimer>
#include<QPainter>
int num = 0;
int numtmp = 0;

/********************************************************************************************************************/
//2016 6.1  wushengjun
//定义变量
//
unsigned char flagLeft = 1;  //左转
unsigned char countLeft = 0; //左转

unsigned char flagBattery = 1;//电瓶指示灯
unsigned char countBattery = 0;//电瓶指示灯

unsigned char flagWidthlamp = 1; //示宽灯
unsigned char countWidthlamp = 0;//示宽灯

unsigned char  flagYG = 1; //远光灯
unsigned char  countYG = 0;//远光灯

unsigned char  flagSW  = 1; //水温
unsigned char  countSW = 0; //水温

unsigned char  flagJG = 1; //近光灯
unsigned char  countJG = 0; //近光灯


unsigned char  flagJY = 1; //机油
unsigned char  countJY = 0; //机油

unsigned char  flagLCM = 1; //粮仓满
unsigned char  countLCM = 0; //粮仓满

unsigned char   flagFDJYR = 1; //发动机预热
unsigned char   countFDJYR = 0; //发动机预热

unsigned char   flagGL = 1; //过滤
unsigned char   countGL = 0; //过滤

unsigned char   flagYL = 1; //油量
unsigned char    countYL = 0;//油量

unsigned char    flagBSQ = 1;//变速器
unsigned char    countBSQ = 0;//变速器

unsigned char    flagECU = 1;//ecu
unsigned char    countECU = 0;//ecu

unsigned char    flagPark = 1;//停车
unsigned char    countPark = 0; //停车

unsigned char   flagFDJGZ = 1; //发动机故障
unsigned char   countFDJGZ = 0; //发动机故障

unsigned char   flagRight = 1; //右转
unsigned char    countRight = 0;//右转






/********************************************************************************************************************/

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    QTimer *timer = new QTimer(this);   //声明一个定时器
    QTimer *timertst = new QTimer(this);

    //update()会自动产生重绘消息，调用paintEvent()
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));  //连接信号槽，定时器超时触发窗体更新
    connect(timertst, SIGNAL(timeout()), this, SLOT(func()));  //连接信号槽，定时器超时触发窗体更新
    timer->start(500);   //启动定时器
    timertst->start(1000);
    setWindowTitle(tr("Haovel"));  //设置窗体名称
    resize(800,600);
    //setWindowFlags(windowFlags()|Qt::FramelessWindowHint|Qt::WindowTitleHint); //删除 最小化、最大化、关闭按钮
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{

    QTime time = QTime::currentTime();   //获取当前的时间
    QPainter painter(this);
    QPixmap pix;
    pix.load("./img2/xingzou.bmp");
    painter.drawPixmap(0,0,800,600,pix);



    int side = qMin(width(), height());  //绘制的范围(宽、高中最小值)

    painter.setRenderHint(QPainter::Antialiasing);//绘制的图像反锯齿
    //painter.translate(width() / 2, height() / 2);//重新定位坐标起始点，把坐标原点放到窗体的中央

    painter.translate(405, 284);//重新定位坐标起始点，把坐标原点放到窗体的中央
    //painter.scale(side / 400.0, side / 300.0);//设定画布的边界,用窗体宽高的最小值来计算时钟的大小，防止窗体拉伸导致的时钟变形以及显示不全




    //下面两个数组用来定义表针的两个顶点，以便后面的填充
    static const QPoint hourHand[3] = {
        QPoint(5, 0),
        QPoint(-5,0),
        QPoint(0, -180)
    };
    static const QPoint minuteHand[3] = {
        QPoint(4, 0),
        QPoint(-4, 0),
        QPoint(0, -100)
    };

    //km r/mini

    painter.setPen(Qt::NoPen);//填充时针，不需要边线所以NoPen
    painter.setBrush(Qt::red);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.save();
    //painter.rotate(6.0 *time.second());  //设旋转(角度 = 6° * (分钟 + 秒 / 60))
    painter.rotate(-124);
    //painter.rotate(6.0 *numtmp);  //设置旋转(6° * 秒)
    painter.rotate(numtmp++);  //设置旋转(6° * 秒)


    painter.drawConvexPolygon(hourHand, 3);  //填充分针部分

    painter.restore();

    painter.setBrush(Qt::black);             //画上中心原点/home/vmuser/qtworkplace/chanpin/img2
    painter.save();
    painter.drawEllipse(QPoint(0,0),8,8);
    painter.restore();


    //km/h
    painter.translate(0,148);//重新定位坐标起始点，把坐标原点放到窗体的中央
    //painter.scale(side / 400.0, side / 300.0);

    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::red);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.save();
    painter.rotate(6.0 *time.second());  //设旋转(角度 = 6° * (分钟 + 秒 / 60))
    painter.drawConvexPolygon(minuteHand, 3);  //填充分针部分
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.restore();

    painter.setBrush(Qt::black);
    painter.save();//画上中心原点
    painter.drawEllipse(QPoint(0,0),5,5);
    painter.restore();


    //chuli pupian shansuo
    painter.translate(-405,-432);//平移到左上角


    //加载上方图标 闪烁用到
    //zuo zhuandeng
    QPainter paintLeft(this);
    QPixmap pixLeft;


    if(flagLeft) //闪烁
    {
        countLeft++;
        if (countLeft>2)
            countLeft = 0;
        switch(countLeft)
        {
            case 1:pixLeft.load("./img2/27.png");//14.jpg
            break;
        }
        paintLeft.drawPixmap(0,0,43,34,pixLeft);
    }


    //电瓶指示灯
    QPainter paintBattery(this);
    QPixmap pixBattery;


    if(flagBattery) //闪烁
    {
        countBattery++;
        if (countBattery>2)
            countBattery = 0;
        switch(countBattery)
        {
            case 1:pixLeft.load("./img2/21.png");//14.jpg
            break;
        }
        paintLeft.drawPixmap(51,0,43,34,pixLeft);
    }

    //示宽灯
    QPainter paintWidthlamp(this);
    QPixmap pixWidthlamp;
    if(flagWidthlamp) //闪烁
    {
        countWidthlamp++;
        if (countWidthlamp>2)
            countWidthlamp = 0;
        switch(countWidthlamp)
        {
            case 1:pixWidthlamp.load("./img2/25.png");//14.jpg
            break;
        }
        paintWidthlamp.drawPixmap(102,0,43,34,pixWidthlamp);
    }

    //远光灯
    QPainter paintYG(this);
    QPixmap pixYG;
    if(flagYG) //闪烁
    {
        countYG++;
        if (countYG>2)
            countYG = 0;
        switch(countYG)
        {
            case 1:pixYG.load("./img2/24.png");//14.jpg
            break;
        }
        paintYG.drawPixmap(153,0,43,34,pixYG);
    }

    //水温
    QPainter paintSW(this);
    QPixmap pixSW;
    if(flagSW) //闪烁
    {
        countSW++;
        if (countSW>2)
            countSW = 0;
        switch(countSW)
        {
            case 1:pixSW.load("./img2/12.png");//14.jpg
            break;
        }
        paintSW.drawPixmap(204,0,35,35,pixSW);
    }

    //近光灯flagJG

    QPainter paintJG(this);
    QPixmap pixJG;
    if(flagJG) //闪烁
    {
        countJG++;
        if (countJG>2)
            countJG = 0;
        switch(countJG)
        {
            case 1:pixJG.load("./img2/15.png");//14.jpg
            break;
        }
        paintJG.drawPixmap(255,0,38,41,pixJG);
    }

    //机油
    QPainter paintJY(this);
    QPixmap pixJY;
    if(flagJY) //闪烁
    {
        countJY++;
        if (countJY>2)
            countJY = 0;
        switch(countJY)
        {
            case 1:pixJY.load("./img2/22.png");//14.jpg
            break;
        }
        paintJY.drawPixmap(306,0,43,43,pixJY);
    }

    //flagLCM = 1; //粮仓满
    QPainter paintLCM(this);
    QPixmap pixLCM;
    if(flagLCM) //闪烁
    {
        countLCM++;
        if (countLCM>2)
            countLCM = 0;
        switch(countLCM)
        {
            case 1:pixLCM.load("./img2/7.png");//14.jpg
            break;
        }
        paintLCM.drawPixmap(357,0,43,43,pixLCM);
    }

    //flagFDJYR = 1; //发动机预热
    QPainter paintFDJYR(this);
    QPixmap pixFDJYR;
    if(flagFDJYR) //闪烁
    {
        countFDJYR++;
        if (countFDJYR>2)
            countFDJYR = 0;
        switch(countFDJYR)
        {
            case 1:pixFDJYR.load("./img2/17.png");//14.jpg
            break;
        }
        paintFDJYR.drawPixmap(357,0,43,43,pixFDJYR);
    }

    // flagGL = 1; //过滤
    QPainter paintGL(this);
    QPixmap pixGL;
    if(flagGL)
    {
        countGL++;
        if (countGL>2)
            countGL = 0;
        switch(countGL)
        {
            case 1:pixGL.load("./img2/20.png");//14.jpg
            break;
        }
        paintGL.drawPixmap(408,0,43,43,pixGL);
    }

    //flagYL = 1; //油量
    QPainter paintYL(this);
    QPixmap pixYL;
    if(flagYL)
    {
        countYL++;
        if (countYL>2)
            countYL = 0;
        switch(countYL)
        {
            case 1:pixYL.load("./img2/23.png");//14.jpg
            break;
        }
        paintYL.drawPixmap(459,0,43,43,pixYL);
    }


    //以上比例都是 + 51

    //flagBSQ = 1;//变速器
    QPainter paintBSQ(this);
    QPixmap pixBSQ;
    if(flagBSQ)
    {
        countBSQ++;
        if (countBSQ>2)
            countBSQ = 0;
        switch(countBSQ)
        {
            case 1:pixBSQ.load("./img2/16.png");//14.jpg
            break;
        }
        paintBSQ.drawPixmap(523,0,43,43,pixBSQ);

        //ecu
        QPainter paintECU(this);
        QPixmap pixECU;
        if(flagECU)
        {
            countECU++;
            if (countECU>2)
                countECU = 0;
            switch(countECU)
            {
                case 1:pixECU.load("./img2/91.png");//14.jpg
                break;
            }
            paintECU.drawPixmap(585,0,43,32,pixECU);
        }


        //flagPark = 1;//停车
        QPainter paintPark(this);
        QPixmap pixPark;
        if(flagPark)
        {
            countPark++;
            if (countPark>2)
                countPark = 0;
            switch(countPark)
            {
                case 1:pixPark.load("./img2/18.png");//14.jpg
                break;
            }
            paintPark.drawPixmap(640,0,43,34,pixPark);
        }

        //
        //flagFDJGZ = 1; //发动机故障
        QPainter paintFDJGZ(this);
        QPixmap pixFDJGZ;
        if(flagFDJGZ)
        {
            countFDJGZ++;
            if (countFDJGZ>2)
                countFDJGZ = 0;
            switch(countFDJGZ)
            {
                case 1:pixFDJGZ.load("./img2/8.png");//14.jpg
                break;
            }
            paintFDJGZ.drawPixmap(697,0,43,37,pixFDJGZ);
        }

        //flagRight = 1; //右转
        QPainter paintRight(this);
        QPixmap pixRight;
        if(flagRight)
        {
            countRight++;
            if (countRight>2)
                countRight = 0;
            switch(countRight)
            {
                case 1:pixRight.load("./img2/right.png");//14.jpg
                break;
            }
            paintRight.drawPixmap(752,0,48,48,pixRight);
        }

    }



}

//界面切换




void Widget::func()
{

     QString timeStr= QTime::currentTime().toString();     //绘制当前的时间

     ui->lineEdit->setText(timeStr);
}

void Widget::on_lineEdit_2_textEdited(const QString &arg1)
{
    bool ok = true;
    numtmp = arg1.toInt(&ok,10);

}

void Widget::on_pushButton_clicked()
{
    this->hide();
    dialog.show();
    dialog.exec();
    this->show();
}
