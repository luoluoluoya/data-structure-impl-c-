//
// Created by 张锐 on 2020/5/19.
//

//节点高度（约定“空树高度为-1”）
#define stature(p) ((p) ? (p)->height : -1)

/**节点基本信息**/
#define IsRoot(x)       ( ! ( (x).parent ) )
#define IsLChild(x)     ( ! IsRoot(x) && ( & (x) == (x).parent->lc ) )
#define IsRChild(x)     ( ! IsRoot(x) && ( & (x) == (x).parent->rc ) )
#define HasParent(x)    ( ! IsRoot(x) )
#define HasLChild(x)    ( (x).lc )
#define HasRChild(x)    ( (x).rc )
#define HasChild(x)     ( HasLChild(x) || HasRChild(x) )
#define HasBothChild(x) ( HasLChild(x) && HasRChild(x) )
#define IsLeaf(x)       ( ! HasChild(x) )

/**与BinNode具有特定关系的节点及指针**/
#define sibling(x)      ( IsRoot( *(x) ) ? NULL : ( IsLChild( *(x) ) ? (x)->parent->rc : (x)->parent->lc ) )
#define uncle(x)        ( IsRoot( *(x) ) ? NULL : sibling(x->parent) )
#define FromParentTo(x) ( IsRoot(x) ? this->_root : ( IsLChild(x) ? (x).parent->lc : (x).parent->rc ) )


/**红黑树宏定义**/
//外部节点也视作黑节点
#define IsBlack(p) ( ! (p) || ( RB_BLACK == (p)->color ) )
//非黑即红
#define IsRed(p) ( ! IsBlack(p) )

//RedBlack高度更新条件
#define BlackHeightUpdated(x) ( \
   ( stature( (x).lc ) == stature( (x).rc ) ) && \
   ( (x).height == ( IsRed(& x) ? stature( (x).lc ) : stature( (x).lc ) + 1 ) ) \
)
