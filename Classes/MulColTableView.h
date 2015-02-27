//
//  MulColTableView.h
//  PaoPaoTang
//
//  Created by Sheng on 12/17/13.
//
//

#ifndef __PaoPaoTang__MulColTableView__
#define __PaoPaoTang__MulColTableView__

#include <iostream>

#include "CCTableView.h"

NS_CC_EXT_BEGIN


class MulColTableView;

class MulColTableViewDelegate : public CCTableViewDelegate
{
public:
    virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell){};
    
    virtual void tableCellTouched(MulColTableView* table, CCNode* cell, int row, int column) = 0;
    virtual void tableCellHighlight(MulColTableView* table, CCNode* cell, int row, int column){};
    virtual void tableCellUnhighlight(MulColTableView* table, CCNode* cell, int row, int column){};
    
//    virtual void tableCellWillRecycle(MulColTableView* table, CCNode* cell){};
    
};



/**
 * Data source that governs table backend data.
 */
class MulColTableViewDataSource 
{
public:
    
    virtual CCSize cellSizeForTable(MulColTableView *table) = 0;

    virtual CCNode* tableCellAt(MulColTableView *table, unsigned int row,  unsigned int column) = 0;

    virtual unsigned int numberOfRowsInTableView(MulColTableView *table) = 0;
    virtual unsigned int numberOfColsInTableView(MulColTableView *table) = 0;
};


class MulColTableView : public CCTableView, public CCTableViewDataSource 
{
    
protected:
    MulColTableViewDelegate*        m_pMulColDelegate;
    MulColTableViewDataSource*      m_pMulColDataSource;
    
    int    m_nTouchCol;   //// used for touch
    int    m_nTouchRow;
    
    int    m_nColCount;
    
public:
    MulColTableView()
    :m_nTouchCol(-1),
    m_nTouchRow(-1)
    {
        m_pMulColDelegate = NULL;
        m_pMulColDataSource = NULL;
    };
    
    static MulColTableView* create(MulColTableViewDataSource* dataSource, CCSize size);
    static MulColTableView* create(MulColTableViewDataSource* dataSource, CCSize size, CCNode *container);
    
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    
    //// CCTableViewDataSource
    virtual CCSize tableCellSizeForIndex(CCTableView *table, unsigned int idx);
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);
    
    /**
     *  multi delegate
     */
    MulColTableViewDelegate* getMulColDelegate() { return m_pMulColDelegate; }
    void setMulColDelegate(MulColTableViewDelegate* pDelegate)
    {
        m_pMulColDelegate = pDelegate;
        /*CCTableView::setDelegate(pDelegate);*/
    }
    
    void setMulColDataSource(MulColTableViewDataSource* pDataSource){ m_pMulColDataSource = pDataSource; }
    
    
    virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell){};
//    virtual void tableCellWillRecycle(CCTableView* table, CCTableViewCell* cell);
    
    virtual void scrollViewDidScroll(CCScrollView* view);
    virtual void scrollViewDidZoom(CCScrollView* view){};
};

NS_CC_EXT_END



#endif /* defined(__PaoPaoTang__MulColTableView__) */
