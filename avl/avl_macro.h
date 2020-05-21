//
// Created by 张锐 on 2020/5/21.
//

/**AVL树宏定义**/
#define HeightUpdated(x)    ( (x).height = 1 + max( stature( (x).lc ), stature( (x).rc ) )  )
//理想平衡条件
#define Balanced(x)         ( (x).lc->height == (x).rc->height )
//平衡因子
#define BalFac(x)           ( (x).lc->height - (x).rc->height )
//AVL平衡条件
#define AvlBalanced(x)      ( (-2 < BalFac(x)) && (BalFac(x) < 2) )

/**在左、右孩子中取更高者； 在AVL平衡调整前，借此确定重构方案**/
#define tallerChild(x) ( \
   stature( (x)->lc ) > stature( (x)->rc ) ? (x)->lc : ( /*左高*/ \
   stature( (x)->lc ) < stature( (x)->rc ) ? (x)->rc : ( /*右高*/ \
   IsLChild( * (x) ) ? (x)->lc : (x)->rc /*等高：与父亲x同侧者（zIg-zIg或zAg-zAg）优先*/ \
   ) \
   ) \
)
