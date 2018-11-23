#include <Carbon/Carbon.h>
#include <QAbstractEventDispatcher>
#include <AppKit/AppKit.h>
#include <Foundation/Foundation.h>
#include <AppKit/NSScreen.h>
#include <AppKit/NSApplication.h>

#include "cagorawidget.h"
#include <QDebug>
#include <QLabel>
#include <QWidget>
#include <QHBoxLayout>
#include <QTextEdit>
#include "cljagoralable.h"

void CAgoraWidget::doAdjuest()
{
    m_widget->setStyleSheet("background: #00000000;");
    //        加了tool 貌似lineedit无法正常输入，需要tab切换窗口后正常 mac
    m_widget->setAttribute(Qt::WA_TranslucentBackground);

    NSView* sview = (NSView*)m_widget->winId();
    sview.wantsLayer = YES;
    //    sview.layer.backgroundColor = [NSColor redColor].CGColor;

    QWidget *renderWidget = new QWidget;
    renderWidget->setGeometry(0,0,280,400);
    QHBoxLayout *layout = new QHBoxLayout(m_widget);
    layout->addWidget(renderWidget);


    NSView* renderView = (NSView*)renderWidget->winId();
//    NSView *renderView = [[NSView alloc] init];
//    renderView.frame = CGRectMake(0, 0, 280, 400);
    //    [sview addSubview:renderView];
    renderView.translatesAutoresizingMaskIntoConstraints = NO;
//    renderView.backgroundColor = [NSColor clearColor];

//    renderView.backgroundColor = [NSColor clearColor];

//    NSTextField *text = [[NSTextField alloc] init];
//    text.frame = CGRectMake(0, 0, 100, 100);
//    text.stringValue = @"test";
//    [sview addSubview:text];

    {
        NSColor *color= [NSColor colorWithRed:0.9f green:0.0f blue:0.0f alpha:0.9];
        NSColor *bgcolor= [NSColor colorWithRed:0.0f green:0.8f blue:0.0f alpha:0.5f];

        NSTextView *text = [[NSTextView alloc] init];
//        NSTextField *text = [[NSTextField alloc] init];
        text.frame = CGRectMake(50, 50, 100, 100);
//        text.stringValue = @"test";

        text.backgroundColor = bgcolor;
//        text.layer.backgroundColor = [NSColor clearColor].CGColor;
        text.translatesAutoresizingMaskIntoConstraints = NO;
        text.textColor = color;
//        text.font = [NSFontboldSystemFontOfSize:16];
        [sview addSubview:text];
    }

    {
//        QTextEdit *label = new QTextEdit("aaaaaaaaaaa",m_widget);
//        QLabel *label = new QLabel("aaaaaaaaaaa",m_widget);
        CLJAgoraLable *label = new CLJAgoraLable("aaaaaaaaaaa",m_widget);
//        label->setStyleSheet("QLabel{background-color: rgba(0, 0, 88, 0);color:#ff0000;font-size:23px;}");
        label->move(QPoint(50,100));
        label->raise();
        NSView *view = (NSView*)label->winId();;
//        NSTextView *view = (NSTextView*)label->winId();;
//        view.layer.backgroundColor = [NSColor redColor].CGColor;

        NSLog(@"view=%d",[view isKindOfClass:[NSView class]]);

        NSLog(@"class name>> %@",NSStringFromClass([view class]));

        for (NSView *aview in [view subviews])
        {
            NSLog(@"aview class name>> %@",NSStringFromClass([aview class]));
        }

//        view.layer.backgroundColor = [NSColor clearColor];
//        [sview addSubview:view];
    }
    {
        for (NSView *aview in [sview subviews])
        {
            NSLog(@"sview aview class name>> %@",NSStringFromClass([aview class]));
        }

    }
//   m_id = (WId)renderView;
   m_id = renderWidget->winId();
}
