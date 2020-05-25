//
// Created by 张锐 on 2020/5/25.
//


// 插入顶点，返回编号
template<typename Tv, typename Te>
int GraphMatrix<Tv, Te>::insert(Tv const &vertex) {
    for (int j = 0; j < this->n; j++) E[j].insert(NULL);
    this->n++;    //各顶点预留一条潜在的关联边
    E.insert(Vector<Edge<Te> *>(this->n, this->n, (Edge<Te> *) NULL)); //创建新顶点对应的边向量
    return V.insert(Vertex<Tv>(vertex)); //顶点向量增加一个顶点
}


//删除第i个顶点及其关联边（0 <= i < n）
template<typename Tv, typename Te>
Tv GraphMatrix<Tv, Te>::remove(int i) {
    //所有出边逐条删除
    for (int j = 0; j < this->n; j++)
        if (exists(i, j)) {
            delete E[i][j]; V[j].inDegree--;
        }
    E.remove(i); this->n--; //删除第i行

    Tv vBak = vertex(i); V.remove(i); //删除顶点i

    //所有入边逐条删除
    for (int j = 0; j < this->n; j++)
        if (Edge<Te> *e = E[j].remove(i)) {
            delete e; V[j].outDegree--;
        }

    return vBak; //返回被删除顶点的信息
}


// 插入权重为w的边e = (i, j)
template<typename Tv, typename Te>
void GraphMatrix<Tv, Te>::insert(Te const &edge, int w, int i, int j) {
    if (exists(i, j)) return;               //确保该边尚不存在
    E[i][j] = new Edge<Te>(edge, w); this->e++;   //创建新边
    V[i].outDegree++;V[j].inDegree++;       //更新边计数与关联顶点的度数
}


//删除顶点i和j之间的联边（exists(i, j)）
template<typename Tv, typename Te>
Te GraphMatrix<Tv, Te>::remove(int i, int j) {
    Te eBak = edge(i, j);               //备份后删除边记录
    delete E[i][j]; E[i][j] = NULL; this->e--;
    V[i].outDegree--; V[j].inDegree--;  //更新边计数与关联顶点的度数
    return eBak;                        //返回被删除边的信息
}
