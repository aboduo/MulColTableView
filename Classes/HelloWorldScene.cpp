#include "HelloWorldScene.h"


USING_NS_CC;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);

//    // add "HelloWorld" splash screen"
//    CCSprite* pSprite = CCSprite::create("HelloWorld.png");
//
//    // position the sprite on the center of the screen
//    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
//
//    // add the sprite as a child to this layer
//    this->addChild(pSprite, 0);
//    
    
    ////// tableview
    tableView = MulColTableView::create(this, CCSizeMake(600, 400));
    tableView->setTouchPriority(-129);
    tableView->setDirection(kCCScrollViewDirectionVertical);
    tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
//    tableView->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    tableView->setPosition(ccp(100, 100));
    tableView->setMulColDelegate(this);
    tableView->setClippingToBounds(true);
    this->addChild(tableView, 100);
    
    
    return true;
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
#pragma mark - MulColTableViewDelegate && MulColTableViewDataSource

void HelloWorld::tableCellTouched(MulColTableView* table, CCNode* cell, int row, int column)
{
    
    int cols = this->numberOfColsInTableView(table);
    int idx = row*cols+column;

    CCLOG("cell %d be touched.", idx);
}



void HelloWorld::tableCellHighlight(MulColTableView* table, CCNode* cell, int row, int column)
{
    CCLOG("%s",__FUNCTION__);
    
    CCSprite* pItemBG = (CCSprite*)cell;
    CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage("bg_b.png");
    pItemBG->setTexture(pTexture);
    
}


void HelloWorld::tableCellUnhighlight(MulColTableView* table, CCNode* cell, int row, int column)
{
    CCLOG("%s",__FUNCTION__);

    CCSprite* pItemBG = (CCSprite*)cell;
    CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage("bg_a.png");
    pItemBG->setTexture(pTexture);
    
}


//////////MulColTableViewDataSource

CCSize HelloWorld::cellSizeForTable(MulColTableView *table)
{
    ////
    return CCSizeMake(100, 100);

}


CCNode* HelloWorld::tableCellAt(MulColTableView *table, unsigned int row,  unsigned int column)
{
    
//    int index = this->numberOfColsInTableView(table) * row + column;
    
    
    CCSprite* sp = CCSprite::create("bg_a.png");
    
    return sp;
}


unsigned int HelloWorld::numberOfRowsInTableView(MulColTableView *table)
{
    
    return 10;
}


unsigned int HelloWorld::numberOfColsInTableView(MulColTableView *table)
{
    return 4;

}


