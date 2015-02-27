//
//  MulColTableView.cpp
//  PaoPaoTang
//
//  Created by Sheng on 12/17/13.
//
//

#include "MulColTableView.h"

NS_CC_EXT_BEGIN

#define kColCell_Tag       1180


MulColTableView* MulColTableView::create(MulColTableViewDataSource* dataSource, CCSize size)
{
    return MulColTableView::create(dataSource, size, NULL);
}

MulColTableView* MulColTableView::create(MulColTableViewDataSource* dataSource, CCSize size, CCNode *container)
{
    MulColTableView *table = new MulColTableView();
    table->initWithViewSize(size, container);
    table->autorelease();
    table->setMulColDataSource(dataSource);
    table->setDataSource(table);
//    table->setDelegate(table);
    table->_updateCellPositions();
    table->_updateContentSize();
    
//    table->setDirection(kCCScrollViewDirectionVertical);
//    table->setVerticalFillOrder(kCCTableViewFillTopDown);
    
    return table;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
#pragma mark - CCTouchDelegate

void MulColTableView::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    if (!this->isVisible()) {
        return;
    }
    
    if (m_pTouchedCell){
		CCRect bb = this->boundingBox();
		bb.origin = m_pParent->convertToWorldSpace(bb.origin);
        
		if ( bb.containsPoint( pTouch->getLocation() ) && m_pMulColDelegate != NULL)
        {
            CCNode* multiCell = m_pTouchedCell->getChildByTag(kColCell_Tag+m_nTouchCol);
            if (multiCell)
            {
                m_pMulColDelegate->tableCellUnhighlight(this, multiCell, m_nTouchRow, m_nTouchCol);
                m_pMulColDelegate->tableCellTouched(this, multiCell, m_nTouchRow, m_nTouchCol);
            }

        }
        
        m_pTouchedCell = NULL;
        m_nTouchRow = -1;
        m_nTouchCol = -1;
    }
    
    CCScrollView::ccTouchEnded(pTouch, pEvent);
    
    
}



bool MulColTableView::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    if (!this->isVisible()) {
        return false;
    }
    
    bool touchResult = CCScrollView::ccTouchBegan(pTouch, pEvent);
    
    CCPoint           point;
    
    point = this->getContainer()->convertTouchToNodeSpace(pTouch);
    m_nTouchRow = this->_indexFromOffset(point);
    
    if(m_pTouches->count() == 1) {
        
        const CCSize cellSize = m_pMulColDataSource->cellSizeForTable(this);
        
        m_nTouchCol = point.x / cellSize.width;
        
		if (m_nTouchRow == CC_INVALID_INDEX)
		{
			m_pTouchedCell = NULL;
		}
        else
		{
			m_pTouchedCell  = this->cellAtIndex(m_nTouchRow);
		}
        
        if (m_pTouchedCell && m_pMulColDelegate != NULL) {
            
            CCNode* multiCell = m_pTouchedCell->getChildByTag(kColCell_Tag+m_nTouchCol);
            if (multiCell)
            {
                m_pMulColDelegate->tableCellHighlight(this, multiCell, m_nTouchRow, m_nTouchCol);
            }
        }
    }
    else if(m_pTouchedCell)
    {
        if(m_pMulColDelegate != NULL)
        {
            CCNode* multiCell = m_pTouchedCell->getChildByTag(kColCell_Tag+m_nTouchCol);
            if (multiCell)
            {
                m_pMulColDelegate->tableCellUnhighlight(this, multiCell, m_nTouchRow, m_nTouchCol);
            }
        }
        
        m_pTouchedCell = NULL;
        m_nTouchRow = -1;
        m_nTouchCol = -1;
    }
    
    return touchResult;
    
}



void MulColTableView::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    CCScrollView::ccTouchMoved(pTouch, pEvent);
    
    if (m_pTouchedCell && isTouchMoved()) {
        if(m_pMulColDelegate != NULL) {
            CCNode* multiCell = m_pTouchedCell->getChildByTag(kColCell_Tag+m_nTouchCol);
            if (multiCell)
            {
                m_pMulColDelegate->tableCellUnhighlight(this, multiCell, m_nTouchRow, m_nTouchCol);
            }
            
        }
        
        m_pTouchedCell = NULL;
    }
}


void MulColTableView::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    CCScrollView::ccTouchCancelled(pTouch, pEvent);
    
    if (m_pTouchedCell) {
        if(m_pMulColDelegate != NULL) {
            CCNode* multiCell = m_pTouchedCell->getChildByTag(kColCell_Tag+m_nTouchCol);
            if (multiCell)
            {
                m_pMulColDelegate->tableCellUnhighlight(this, multiCell, m_nTouchRow, m_nTouchCol);
            }
            
        }
        
        m_pTouchedCell = NULL;
        m_nTouchRow = -1;
        m_nTouchCol = -1;
    }
    
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
#pragma mark - CCTableViewDelegate


//void MulColTableView::tableCellWillRecycle(CCTableView* table, CCTableViewCell* cell)
//{
//    int c = m_pMulColDataSource->numberOfColsInTableView(this);
//    
//    for (int i = 0; i < c ; i++)
//    {
//        
//        CCNode* multiCell = cell->getChildByTag(kColCell_Tag+i);
//        if (m_pMulColDelegate)
//        {
//            m_pMulColDelegate->tableCellWillRecycle(this,multiCell);
//        }
//        cell->removeChildByTag(kColCell_Tag+i, true);
//        
//    }
//}

void MulColTableView::scrollViewDidScroll(cocos2d::extension::CCScrollView* view)
{
    CCTableView::scrollViewDidScroll(view);
    
    if (m_pMulColDelegate)
    {
        m_pMulColDelegate->scrollViewDidScroll(view);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
#pragma mark - CCTableViewDataSource

CCSize MulColTableView::tableCellSizeForIndex(CCTableView *table, unsigned int idx)
{
    int height = m_pMulColDataSource->cellSizeForTable(this).height;
    int width = m_pMulColDataSource->cellSizeForTable(this).width * m_pMulColDataSource->numberOfColsInTableView(this);
    
    return CCSizeMake(width, height);
}


CCTableViewCell* MulColTableView::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCTableViewCell *cell = this->dequeueCell();
    if (!cell) {
        cell = new CCTableViewCell();
        cell->autorelease();
    }
    cell->removeAllChildren();
    
    int c = m_pMulColDataSource->numberOfColsInTableView(this);
    
    
    for (int i = 0; i < c ; i++)
    {
//        cell->removeChildByTag(kColCell_Tag+i, true);
        
        CCNode* colCell = m_pMulColDataSource->tableCellAt(this, idx, i);
        
        if (colCell)
        {
            colCell->setTag(kColCell_Tag+i);
            
            CCSize size = m_pMulColDataSource->cellSizeForTable(this);
            colCell->setAnchorPoint(ccp(0.5, 0.5));
            colCell->setPosition(size.width * (i+0.5), size.height/2);
            cell->addChild(colCell);
        }

    }
    
    return cell;
}


unsigned int MulColTableView::numberOfCellsInTableView(CCTableView *table)
{
    int count = m_pMulColDataSource->numberOfRowsInTableView(this);
    return count;
}



NS_CC_EXT_END