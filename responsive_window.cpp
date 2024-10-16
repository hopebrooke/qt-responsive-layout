//
// Created by twak on 14/10/2019.
//

#include "responsive_window.h"
#include "responsive_layout.h"
#include "screenshot.h"
#include <iostream>
#include <QApplication>


ResponsiveWindow::ResponsiveWindow() {

    setWindowTitle("2811: Coursework 1");
    setMinimumSize(320, 320);
    setMaximumSize(1280, 720);

    createWidgets();
}

void ResponsiveWindow::createWidgets() {

    //create new responsive layout:
    ResponsiveLayout * rl = new ResponsiveLayout();
    //add all the responsive labels required:
    rl->addWidget(new ResponsiveLabel(kNavTabs));
    rl->addWidget(new ResponsiveLabel(kMenu));
    rl->addWidget(new ResponsiveLabel(kHomeLink));
    rl->addWidget(new ResponsiveLabel(kSignIn));
    rl->addWidget(new ResponsiveLabel(kShoppingBasket));
    rl->addWidget(new ResponsiveLabel(kWishlist));
    rl->addWidget(new ResponsiveLabel(kSearchText));
    rl->addWidget(new ResponsiveLabel(kSearchButton));
    rl->addWidget(new ResponsiveLabel(kSearchOptions));
    rl->addWidget(new ResponsiveLabel(kAdvert));
    rl->addWidget(new ResponsiveLabel(kAdvert));
    rl->addWidget(new ResponsiveLabel(kSearchBackward));
    rl->addWidget(new ResponsiveLabel(kSearchForward));


    //make a new responsive layout:
    ResponsiveLayout * scrollLayout = new ResponsiveLayout();

    //make a new widget:
    QWidget * scrollWidget = new QWidget();
    //set height of widget to enable scrolling:
    scrollWidget->setMinimumHeight(1400);

    //make a new scroll area
    QScrollArea * scrollArea = new QScrollArea();
    //make scrolling section resizable
    scrollArea->setWidgetResizable(true);
    //turn on vertical scrolling:
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    //turn off horizontal scrolling:
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //add search labels to new layout
    for(int i=0; i < 17; i++){
        scrollLayout->addWidget(new ResponsiveLabel(kSearchResult));
        scrollLayout->addWidget(new ResponsiveLabel(kSResultImage));
        scrollLayout->addWidget(new ResponsiveLabel(kSResultText));
        scrollLayout->addWidget(new ResponsiveLabel(kSResultPrice));
    }

    //set widget to the new layout of search results
    scrollWidget->setLayout(scrollLayout);

    //set scroll area to widget made from layout
    scrollArea->setWidget(scrollWidget);

    //add scroll area widget to responsive layout
    rl->addWidget(scrollArea);

    //set responsive layout
    setLayout(rl);
}
