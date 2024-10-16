//
// Created by twak on 07/10/2019.
//

#include "responsive_layout.h"
#include "responsive_label.h"
#include <iostream>


void ResponsiveLayout::setGeometry(const QRect &r /* our layout should always fit inside r */ ) {

    QLayout::setGeometry(r);

    //integer to count how many adverts included:
    int ads = 0;

    //search result count:
    int results = 0;
    int resultsImage = 0;
    int resultsText = 0;
    int resultsPrice = 0;

    // for all the Widgets added in ResponsiveWindow.cpp
    for (int i = 0; i < list_.size(); i++) {

        QLayoutItem *o = list_.at(i);

        //cast the widget to a scroll area:
        QScrollArea *scroll = dynamic_cast<QScrollArea*>(o->widget());

        //SET GEOMETRY OF SCROLL AREA
        if(scroll != nullptr){
            //COMPACT:
            if(r.width() < 500 && r.height()<500){
                //geometry of scroll area withing layout:
                scroll->setGeometry(r.x()+r.width()*0.025, r.y()+100, r.width()*0.95, r.height()-155);
                //geometry of widgets within scroll area:
                scroll->widget()->setGeometry(0+r.x(), 0+r.y(), r.width(), r.height());
            }
            //VERTICAL:
            else if(r.width()<500) {
                //geometry of scroll area withing layout:
                scroll->setGeometry(r.width()*0.025+r.x(), 150+r.y(), r.width()*0.95, r.height()-205);
                //geometry of widgets within scroll area:
                scroll->widget()->setGeometry(r.x()+0, r.y()+0, r.width(), r.height());
            }
            //HORIZONTAL:
            else {
                //geometry of scroll area withing layout:
                scroll->setGeometry(r.width()*0.175+r.x(), 100+r.y(), r.width()*0.65, r.height()-105);
                //geometry of widgets within scroll area:
                scroll->widget()->setGeometry(r.x()+0, r.y()+0, r.width(), r.height());
            }
        }

        //SET GEOMETRY OF RESPONSIVE LABELS:
        else {
            try {
                // cast the widget to one of our responsive labels
                ResponsiveLabel *label = static_cast<ResponsiveLabel *>(o->widget());


                //determine whether scroll area layout is horizontal or vertical/compact:
                //compact and vertical have same layout of scroll area, so only two options for this
                int scrollLay = 0;
                if(r.width() < 325 ) //it is compact or vertical when the  scroll area of results < 325
                    scrollLay = 1;


                //HORIZONTAL SCROLL AREA:
                if (scrollLay == 0){
                    if (label -> text() == kSearchResult ){ //display search results as 3 per row
                        int row = results / 3;
                        label -> setGeometry( r.x()+(r.width()*0.025)+((results%3)*(r.width()*0.325)), r.y() + row*(125), r.width()*0.3, 120);
                        results ++; //add to counter of results
                    }
                    else if (label->text() == kSResultImage ){ //display result image on top of search result
                        int row = resultsImage / 3;
                        label -> setGeometry( r.x()+(r.width()*0.045)+((resultsImage%3)*(r.width()*0.325)), r.y() + 5 +row*(125), r.width()*0.26, 80);
                        resultsImage ++; //add to counter of result images
                    }
                    else if (label->text() == kSResultText ){ //display result text under result image
                        int row = resultsText / 3;
                        label -> setGeometry( r.x()+(r.width()*0.045)+((resultsText%3)*(r.width()*0.325)), r.y() +90 + row*(125), r.width()*0.18, 25);
                        resultsText ++; //add to counter of result texts
                    }
                    else if (label->text() == kSResultPrice ){ //display result price under result image
                        int row = resultsPrice / 3;
                        label -> setGeometry( r.x()+(r.width()*0.245)+((resultsPrice%3)*(r.width()*0.325)), r.y() + 90 + row*(125), r.width()*0.06, 25);
                        resultsPrice ++; //add to counter of result prices
                    }
                }

                //VERTICAL AND COMPACT SCROLL AREA:
                else if (scrollLay == 1){
                    if (label -> text() == kSearchResult ){ //search result displays as one per row, with horizontal formatting of data
                        label -> setGeometry( r.x(), r.y() + results*(80), r.width()*0.95, 75);
                        results ++;
                    }
                    else if (label->text() == kSResultImage ){ //result image on left of result
                        label -> setGeometry( r.x()+(r.width()*0.02), r.y() + 5 + resultsImage*(80), r.width()*0.40, 65);
                        resultsImage ++;
                    }
                    else if (label->text() == kSResultText ){ //result text to the right of image
                        label -> setGeometry( r.x()+(r.width()*0.44), r.y() + 5 + resultsText*(80), r.width()*0.44, 40);
                        resultsText ++;
                    }
                    else if (label->text() == kSResultPrice ){ //result price
                        label -> setGeometry( r.x()+(r.width()*0.44), r.y() + 50 + resultsPrice*(80), r.width()*0.22, 20);
                        resultsPrice ++;
                    }
                }


                //value to determine whether main layout is horizontal, vertical or compact:
                int mainLay = 0;
                if(r.width() < 500 && r.height()<500) //compact if both width and height < 500
                    mainLay = 1;
                else if(r.width()<500) //vertical if width < 500
                    mainLay = 2;
                else //horizontal otherwise
                    mainLay = 3;


                //HORIZONTAL LAYOUT:
                if(mainLay == 3){
                    if (label == NULL) // null: cast failed on pointer
                        std::cout << "warning, unknown widget class in layout" << std::endl;

                    else if (label -> text() == kNavTabs ) // navbar goes at the top
                        label -> setGeometry(0+r.x(),0+r.y(),r.width(), 50);

                    else if (label->text() == kMenu ) //menu button on top left of navbar
                        label->setGeometry(5+r.x(), 5+r.y(), 45, 40);

                    else if (label->text() == kHomeLink ) //home button on right of menu
                        label->setGeometry(55+r.x(), 5+r.y(), 45, 40);

                    else if (label->text() == kSignIn) //sign in at top right of nav bar
                        label->setGeometry( r.width()-50, 5+r.y(), 45, 40);

                    else if (label->text() == kShoppingBasket) //shopping basket to left of sign in
                        label->setGeometry( r.width()- 100, 5+r.y(), 45, 40);

                    else if (label->text() == kWishlist) //wishlist to left of shopping basket
                        label->setGeometry( r.width()- 150, 5+r.y(), 45, 40);

                    else if(label->text() == kSearchText) //search bar in the middle on nav bar
                        label->setGeometry(r.x() +r.width()*0.3, r.y()+5, r.width()*0.3, 40);

                    else if (label -> text() == kSearchButton) //search button to the right of search bar
                        label -> setGeometry(r.x()+r.width()*0.605, 5+r.y(), r.width()*0.05, 40);

                    else if (label->text() == kSearchOptions) //search options below nav bar
                        label->setGeometry(r.x()+(r.width()*0.225), r.y()+55, r.width()*0.55, 40);

                    else if (label->text() == kSearchBackward) //backword page button on left of search options
                        label->setGeometry(r.x()+(r.width()*0.175), r.y()+55, r.width()*0.0475, 40);

                    else if (label->text() == kSearchForward) //forward page button on right of search options
                        label->setGeometry(r.x()+(r.width()*0.7775), r.y()+55, r.width()*0.0475, 40);

                    else if (label->text() == kAdvert){
                        if (ads == 0){
                            //first advert on left of screen
                            label->setGeometry(r.x()+r.width()*0.0025, r.y()+55, r.width()*0.17, r.height()-60);
                            ads = 1;
                        }
                        else
                            //second advert on right of screen
                            label->setGeometry(r.x()+r.width()*0.8275, r.y()+55, r.width()*0.17, r.height()-60);
                    }
                }


                //VERTICAL LAYOUT:
                if(mainLay == 2){
                    if (label == NULL) // null: cast failed on pointer
                        std::cout << "warning, unknown widget class in layout" << std::endl;

                    else if (label -> text() == kNavTabs ) // navbar goes at the top
                        label -> setGeometry(0+r.x(),0+r.y(),r.width(), 50);

                    else if (label->text() == kMenu ) //menu button on top left of navbar
                        label->setGeometry(5+r.x(), 5+r.y(), 45, 40);

                    else if (label->text() == kHomeLink ) //home button to the right of menu
                        label->setGeometry(55+r.x(), 5+r.y(), 45, 40);

                    else if (label->text() == kSignIn) //sign in at top right of nav bar
                        label->setGeometry( r.width()-50, 5+r.y(), 45, 40);

                    else if (label->text() == kShoppingBasket) //shopping basket to left of sign in
                        label->setGeometry( r.width()- 100, 5+r.y(), 45, 40);

                    else if (label->text() == kWishlist) //wishlist to left of shopping basket
                        label->setGeometry( r.width()- 150, 5+r.y(), 45, 40);

                    else if(label->text() == kSearchText) //search bar below navbar
                        label->setGeometry(r.x() +r.width()*0.05, r.y()+55, r.width()*0.75, 40);

                    else if (label -> text() == kSearchButton) //search button to the right of search bar
                        label -> setGeometry(r.x()+r.width()*0.825, 55+r.y(), r.width()*0.15, 40);

                    else if (label->text() == kSearchOptions) //search options below search bar
                        label->setGeometry(r.x()+(r.width()*0.15), r.y()+105, r.width()*0.7, 40);

                    else if (label->text() == kSearchBackward) //backward page button on left of search options
                        label->setGeometry(r.x()+(r.width()*0.025), r.y()+105, r.width()*0.1, 40);

                    else if (label->text() == kSearchForward) //forward page button on right of search options
                        label->setGeometry(r.x()+(r.width()*0.875), r.y()+105, r.width()*0.1, 40);

                    else if (label->text() == kAdvert) //advert at bottom of screen
                        label->setGeometry(r.x()+r.width()*0.025, r.height()-50, r.width()*0.95, 45);
                }


                //COMPACT LAYOUT:
                //similar to vertical, with search bar and search options reduced to one line
                if(mainLay == 1){
                    if (label == NULL) // null: cast failed on pointer
                        std::cout << "warning, unknown widget class in layout" << std::endl;

                    else if (label -> text() == kNavTabs ) // navbar goes at the top
                        label -> setGeometry(0+r.x(),0+r.y(),r.width(), 50);

                    else if (label->text() == kMenu ) //menu button on top left of navbar
                        label->setGeometry(5+r.x(), 5+r.y(), 45, 40);

                    else if (label->text() == kHomeLink ) //home button on right of menu
                        label->setGeometry(55+r.x(), 5+r.y(), 45, 40);

                    else if (label->text() == kSignIn) //sign in at top right of nav bar
                        label->setGeometry( r.width()-50, 5+r.y(), 45, 40);

                    else if (label->text() == kShoppingBasket) //shopping basket to left of sign in
                        label->setGeometry( r.width()- 100, 5+r.y(), 45, 40);

                    else if (label->text() == kWishlist) //Wishlist to left of shopping basket
                        label->setGeometry( r.width()- 150, 5+r.y(), 45, 40);

                    else if(label->text() == kSearchText) //search bar not visible - would show up on click of search button
                        label->setGeometry(r.x() +r.width()*0.05, r.y()+55, 0, 0);

                    else if (label -> text() == kSearchButton) //search button to the right of search options
                        label -> setGeometry(r.x()+r.width()*0.82, 55+r.y(), r.width()*0.15, 40);

                    else if (label->text() == kSearchOptions) //search options immediately below navbar
                        label->setGeometry(r.x()+(r.width()*0.29), r.y()+55, r.width()*0.5, 40);

                    else if (label->text() == kSearchBackward) //backward page button on left below navbar
                        label->setGeometry(r.x()+(r.width()*0.03), r.y()+55, r.width()*0.1, 40);

                    else if (label->text() == kSearchForward) //forward page button next to backward
                        label->setGeometry(r.x()+(r.width()*0.16), r.y()+55, r.width()*0.1, 40);

                    else if (label->text() == kAdvert) //advert at bottom of page
                        label->setGeometry(r.x()+r.width()*0.025, r.height()-50, r.width()*0.95, 45);
                }

            }
            catch (std::bad_cast) {
                // bad_case: cast failed on reference...
                std::cout << "warning, unknown widget class in layout" << std::endl;
            }
        }
    }
}

// following methods provide a trivial list-based implementation of the QLayout class
int ResponsiveLayout::count() const {
    return list_.size();
}

QLayoutItem *ResponsiveLayout::itemAt(int idx) const {
    return list_.value(idx);
}

QLayoutItem *ResponsiveLayout::takeAt(int idx) {
    return idx >= 0 && idx < list_.size() ? list_.takeAt(idx) : 0;
}

void ResponsiveLayout::addItem(QLayoutItem *item) {
    list_.append(item);
}

QSize ResponsiveLayout::sizeHint() const {
    return minimumSize();
}

QSize ResponsiveLayout::minimumSize() const {
    return QSize(320,320);
}

ResponsiveLayout::~ResponsiveLayout() {
    QLayoutItem *item;
    while ((item = takeAt(0)))
        delete item;
}
