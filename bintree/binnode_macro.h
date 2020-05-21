//
// Created by ���� on 2020/5/19.
//

//�ڵ�߶ȣ�Լ���������߶�Ϊ-1����
#define stature(p) ((p) ? (p)->height : -1)

/**�ڵ������Ϣ**/
#define IsRoot(x)       ( ! ( (x).parent ) )
#define IsLChild(x)     ( ! IsRoot(x) && ( & (x) == (x).parent->lc ) )
#define IsRChild(x)     ( ! IsRoot(x) && ( & (x) == (x).parent->rc ) )
#define HasParent(x)    ( ! IsRoot(x) )
#define HasLChild(x)    ( (x).lc )
#define HasRChild(x)    ( (x).rc )
#define HasChild(x)     ( HasLChild(x) || HasRChild(x) )
#define HasBothChild(x) ( HasLChild(x) && HasRChild(x) )
#define IsLeaf(x)       ( ! HasChild(x) )

/**��BinNode�����ض���ϵ�Ľڵ㼰ָ��**/
#define sibling(x)      ( IsRoot( *(x) ) ? NULL : ( IsLChild( *(x) ) ? (x)->parent->rc : (x)->parent->lc ) )
#define uncle(x)        ( IsRoot( *(x) ) ? NULL : sibling(x->parent) )
#define FromParentTo(x) ( IsRoot(x) ? this->_root : ( IsLChild(x) ? (x).parent->lc : (x).parent->rc ) )


/**������궨��**/
//�ⲿ�ڵ�Ҳ�����ڽڵ�
#define IsBlack(p) ( ! (p) || ( RB_BLACK == (p)->color ) )
//�Ǻڼ���
#define IsRed(p) ( ! IsBlack(p) )

//RedBlack�߶ȸ�������
#define BlackHeightUpdated(x) ( \
   ( stature( (x).lc ) == stature( (x).rc ) ) && \
   ( (x).height == ( IsRed(& x) ? stature( (x).lc ) : stature( (x).lc ) + 1 ) ) \
)
