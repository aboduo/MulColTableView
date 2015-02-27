#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "MulColTableView.h"

using namespace cocos2d;
//using namespace CocosDenshion;
using namespace cocos2d::extension;

class HelloWorld : public cocos2d::CCLayer, public MulColTableViewDelegate, public MulColTableViewDataSource
{
    
    MulColTableView*        tableView;
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
    
    
    //////////MulColTableViewDelegate
    
    virtual void tableCellTouched(MulColTableView* table, CCNode* cell, int row, int column);
    virtual void tableCellHighlight(MulColTableView* table, CCNode* cell, int row, int column);
    virtual void tableCellUnhighlight(MulColTableView* table, CCNode* cell, int row, int column);
    
    virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view) {};
    virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view) {};
    
    //////////MulColTableViewDataSource
    
    virtual CCSize cellSizeForTable(MulColTableView *table);
    virtual CCNode* tableCellAt(MulColTableView *table, unsigned int row,  unsigned int column);
    virtual unsigned int numberOfRowsInTableView(MulColTableView *table);
    virtual unsigned int numberOfColsInTableView(MulColTableView *table);
};

#endif // __HELLOWORLD_SCENE_H__
