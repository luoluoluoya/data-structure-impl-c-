//
// Created by ���� on 2020/5/21.
//

/**AVL���궨��**/
#define HeightUpdated(x)    ( (x).height = 1 + max( stature( (x).lc ), stature( (x).rc ) )  )
//����ƽ������
#define Balanced(x)         ( (x).lc->height == (x).rc->height )
//ƽ������
#define BalFac(x)           ( (x).lc->height - (x).rc->height )
//AVLƽ������
#define AvlBalanced(x)      ( (-2 < BalFac(x)) && (BalFac(x) < 2) )

/**�����Һ�����ȡ�����ߣ� ��AVLƽ�����ǰ�����ȷ���ع�����**/
#define tallerChild(x) ( \
   stature( (x)->lc ) > stature( (x)->rc ) ? (x)->lc : ( /*���*/ \
   stature( (x)->lc ) < stature( (x)->rc ) ? (x)->rc : ( /*�Ҹ�*/ \
   IsLChild( * (x) ) ? (x)->lc : (x)->rc /*�ȸߣ��븸��xͬ���ߣ�zIg-zIg��zAg-zAg������*/ \
   ) \
   ) \
)
